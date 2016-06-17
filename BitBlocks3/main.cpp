

/*Assinatura dos metodos*/
void CriaEdges();
void VerificaColisao();
void funcRead();
void funcWrite();


/*Classes*/
#include "Player.h"
#include "GamePhysics.h"
#include "Edge.h"
#include "GameStatus.h"
#include "GameScreen.h"
#include "Timer.h"
#include <list>
#include <vector>
#include <cmath>


/*Instancias Globais*/
Player p1; //player   	   
GamePhysics gamePhysics(0.1, 440); //Fisica do Game
GameStatus gameStatus; //status atual do game
GameScreen gameScreen(800, 600, gameStatus.stage); //gameScreen
Timer timer; //timer
int readPointer, writePointer; //ponteiros buffer
float * CircularBuffer; //buffer circular
sf::Mutex mutex1; //mutex
int aux = 0;
/*FIM*/



/*GAME MAIN*/
int main()
{
	/*Inicialização*/
	gameScreen.Initialize();
	p1.Create(sf::Vector2f(50, 6), sf::Vector2f(20, 20), sf::Color::Red);
	CriaEdges();
	readPointer = -1;
	writePointer = 0;
	CircularBuffer = new float[1000];
	double ValorLido;

	for (int i = 0; i < 1000; i++)
	{
		CircularBuffer[i] = 99;
	}
	CircularBuffer[0] = 1;
	aux = -1;
	/*FIM*/

	/*Concorrente*/
	sf::Thread T1(&funcRead);
	sf::Thread T2(&funcWrite);
	T2.launch();
	sf::sleep(sf::milliseconds(500));
	T1.launch();
	sf::sleep(sf::milliseconds(500));
	/*FIM*/

	/*Game Loop (Quadros)*/
	while (gameScreen.window.isOpen())
	{
		sf::Event event;
		while (gameScreen.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				T1.terminate();
				T2.terminate();
				gameScreen.window.close();
			}
				

		}


		if (!p1.gameOver) //!isGameOver
		{

			/*Confiruações de entrada do teclado*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				p1.velocity.x = p1.moveSpeed;
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				p1.velocity.x = -p1.moveSpeed;
			else
				p1.velocity.x = 0;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && aux != 1)
				gamePhysics.gravity = 2;
			else if (event.KeyReleased && aux != 1)
				gamePhysics.gravity = p1.jmpSpeed;
			/*FIM*/


			/*Configurações da Gravidade*/
			if (p1.rect.getPosition().y + p1.rect.getSize().y < gamePhysics.groundHeight || p1.velocity.y < 0)
				p1.velocity.y = gamePhysics.gravity;
			/*FIM*/

			/*MUDA A SCENE(cena)*/
			if (p1.rect.getPosition().y >= gameScreen.sizeY - 20 && aux != 1)
			{

				p1.rect.setPosition(sf::Vector2f(50, 6));
				p1.Create(sf::Vector2f(50, 6), sf::Vector2f(20, 20), sf::Color::Red);
				gameStatus.edges.clear();
				CriaEdges();
				aux = 1;
				gameStatus.stage++; //stage sobe em toda mudança de cena
				gameStatus.cont_stage++;



			}


			else
				aux = 0;

			if (p1.rect.getPosition().x > gameScreen.sizeX - 2)
				p1.rect.setPosition(sf::Vector2f(2, p1.rect.getPosition().y));
			else if (p1.rect.getPosition().x < 2)
				p1.rect.setPosition(sf::Vector2f(gameScreen.sizeX - 2, p1.rect.getPosition().y));
			/*FIM*/

			/*Updates*/
			timer.IntervalFunction(CircularBuffer[readPointer]); //chama função de intervalo do timer
			p1.Update();
			p1.rect.move(p1.velocity.x, p1.velocity.y); //movimenta player
			if (!(p1.rect.getPosition().y >= gameScreen.sizeY - 10 && p1.rect.getPosition().y <= 0))
			{
				for (Edge *i : gameStatus.edges)
				{

					i->Update();
					i->par->Update();

				}
			}
			VerificaColisao();
			/*FIM*/


			/*Desenha na Tela*/
			gameScreen.window.clear(sf::Color(0, 240, 255)); //limpa tela a cada frame
			gameScreen.window.draw(p1.rect); //desenha player
			gameScreen.GameStageScreen(gameStatus.stage);
			gameScreen.window.draw(timer.scoreText); //desenha scoreText
			if (!(p1.rect.getPosition().y >= gameScreen.sizeY - 10 && p1.rect.getPosition().y <= 0))
			{

				for (Edge *i : gameStatus.edges)
				{
					gameScreen.window.draw(i->edge);
					gameScreen.window.draw(i->par->edge);


				}

			}
			/*FIM*/

			gameScreen.window.display(); //mostra a gameScreen



		}

		else //isGameOver
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				p1.Create(sf::Vector2f(50, 6), sf::Vector2f(20, 20), sf::Color::Red);
			}

			gameScreen.window.clear(sf::Color(0, 240, 255)); //limpa tela a cada frame
			gameScreen.GameOverScreen(); //mostra gameoverScreen
			gameScreen.window.display(); //mostra a gameScreen

		}

	}
	/*FIM GAMELOOP*/




	return 0;
}
/*FIM GAME MAIN*/


/*GameMain Metodos*/
void VerificaColisao()
{
	int j = 0;
	for (Edge *i : gameStatus.edges)
	{
		j++;
		p1.IsCollide(i, j);
	}
}

void CriaEdges()
{
	int *  dist = new int[gameStatus.max_Edges];
	int distMinima = 100;
	int aux = 30;
	bool error = false;

	for (int i = 0; i < gameStatus.max_Edges; i++) //numeração do vertice criado
	{

		if (i == 0)
		{
			dist[i] = rand() % (gameScreen.sizeY / 2) + 50;
		}


		else
		{
			dist[i] = rand() % (gameScreen.sizeY - 30) + (dist[i - 1] + distMinima);

		}

		if (dist[i] >= gameScreen.sizeY) //se edge passar do tamanho y da tela
		{
			std::cout << "error\n";
			error = true;
			// dist[i] = dist[i - 1] - 70;
		}

		if (dist[i] < 150)
			dist[i] += 100;

	}

	for (int i = 0; i < gameStatus.max_Edges; i++)
	{
		if (error)
		{
			if (i == 0)
				dist[i] = rand() % 150 + 50;

			else if (i == gameStatus.max_Edges - 1)
			{
				//int min = 350, max = gameScreen.sizeY - 5;
				dist[i] = 450;
				dist[i] += rand() % 150;
			}


			else
				dist[i] = dist[i - 1] + 100;
		}

		std::cout << "\n" << dist[i] << "  - " << i << " SIZEY->" << gameScreen.sizeY;
		Edge * edge = new Edge();
		edge->Create(gameScreen.sizeX, gameScreen.sizeY, i, gameStatus.stage, p1.rect.getSize(), 1, dist[i], 1);
		gameStatus.edges.push_back(edge);
	}
	error = false;




}
/*FIM*/



/*THREADS METODOS*/
void funcRead()
{
	double ValorLido;
	while (true)
	{
		mutex1.lock();

		if (readPointer < 0)
		{


			if (readPointer < (writePointer))
			{
				readPointer++;

				if (readPointer == 1000)
					readPointer = 0;

			}
		}

		else
		{
			if (readPointer < (writePointer - 1))
			{
				readPointer++;

				if (readPointer == 1000)
					readPointer = 0;

			}
		}
		mutex1.unlock();
		sf::sleep(sf::milliseconds(2000));
	}

}

void funcWrite()
{
	timer.SetTimeInterval(1000);
	timer.Start();
	sf::Int32 sec;
	while (true)
	{
		mutex1.lock();


		sec = timer.GetElapsedTime().asMilliseconds();

		if (gameStatus.cont_stage == 2)
		{
			p1.jmpSpeed += 0.1;
			gameStatus.score++;
			CircularBuffer[writePointer] = gameStatus.score;
			writePointer++;
			gameStatus.cont_stage = 0;
		}


		if (writePointer == 1000)
			writePointer = 0;
		mutex1.unlock();
	}

}
/*FIM*/
