#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
class Edge
{
	private: char posicao;
			 int id;
    public: Edge * par;
	 std::vector<std::vector<bool> > mask; // mascara de colisao
	 sf::RectangleShape edge; //Borda Vertical
	 void Create(int sizeX, int sizeY, int i, int score, sf::Vector2f pSize, int tamanho, int posicY, int posicX); //psize = tamanho do player
	 void Update(); //atualiza a cada frame
	 float lados[4]; //lados da borda
	 Edge();





};

