#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Edge.h"

/*CLASSE PLAYER*/
class Player
{
private: void Collide(int j); //colisao
		 std::vector<std::vector<bool>> mask; // mascara de colisao
		 float bottom, left, right, top; //lados
		 
public:sf::RectangleShape rect; //personagem
	   
	   sf::Vector2f velocity; //guarda velocidades
	   float jmpSpeed; //velocidade do pulo
	   float moveSpeed; //velocidade do movimento (esquerda/direita
	   void Create(sf::Vector2f position, sf::Vector2f size, sf::Color color);
	   void Update(); //atualiza a cada frame
	   void IsCollide(Edge *  ed, int j);
	   bool gameOver;



};
/*FIM*/