#include "Edge.h"
#include <cmath>

void Edge::Create(int sizeX, int sizeY, int i, int score, sf::Vector2f pSize, int tamanho, int posicY, int posicX)
{
	id = i;
	int aux = 20; //distancia de segurança do  tamanho do player

		int tamx, tamy = 5;
		int posx, posy;

		/*CRIA EDGES ALEATORIAMENTE*/
		if (tamanho == 1 && posicX == 1)//edge lado esquerdo
			posicao = 'l';
		else //edge lado direito
			posicao = 'r';

		if (posicao == 'l')
		{
			posx = 5;
			tamx = rand() % (sizeX - (aux*4)) + 1; //tamanho x do edge
			posy = posicY;
			par = new Edge();
			par->Create(sizeX, sizeY, i, score, pSize, tamx, posy, posx);
		}

		else // se for lado direito
		{
			srand(time(NULL));
			tamx = tamanho;
			tamx = sizeX - tamx - pSize.x - aux;
			posy = posicY;
			posx = posicX + tamanho + pSize.x + aux + (rand()%70 + 20);
		}
		
		edge.setSize(sf::Vector2f(tamx, tamy)); //xtop
		edge.setPosition(sf::Vector2f(posx, posy));
		edge.setOutlineThickness(1);
		edge.setOutlineColor(sf::Color::White);
		edge.setFillColor(sf::Color::Black);

	/*--------------*/



	/*COLISAO*/
	sf::Image image;
	sf::RenderTexture rTexture;
	sf::Texture texture;

	rTexture.create(edge.getSize().x, edge.getSize().y);
	sf::RectangleShape tempRect(edge);
	tempRect.setPosition(0, 0);
	rTexture.draw(tempRect);
	rTexture.display();

	texture = rTexture.getTexture();
	image = texture.copyToImage();

	for (int i = 0; i < image.getSize().x; i++)
	{
		std::vector<bool> tempMask;
		for (int j = 0; j < image.getSize().y; j++)
		{
			if (image.getPixel(i, j).a > 0)
				tempMask.push_back(true);
			else
				tempMask.push_back(false);
		}
		mask.push_back(tempMask);
	}
	/*FIM*/



}
void Edge::Update() //atualiza a cada frame
{
	
	lados[0] = edge.getPosition().y + edge.getSize().y; //bottom
	lados[1] = edge.getPosition().x; //left
	lados[2] = edge.getPosition().y; //top
	lados[3] = edge.getPosition().x + edge.getSize().x; //right
	
}

 Edge :: Edge()
{
}
/*FIM*/