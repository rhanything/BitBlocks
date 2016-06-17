#include "Player.h"
#include "Edge.h"
#include <iostream>
#include <vector>
#include <algorithm>

void Player::Create(sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
	//seta caracteristicas iniciais do personagem
	gameOver = false;
	jmpSpeed = 0.1f;
	moveSpeed = 1.0f;
	velocity.x = 0;
	velocity.y = 0;

	rect.setPosition(position);
	rect.setSize(size);
	rect.setFillColor(color);

	sf::Image image; 
	sf::RenderTexture rTexture; 
	sf::Texture texture;

	rTexture.create(size.x, size.y);
	sf::RectangleShape tempRect(rect);
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
 }

void Player::Update() //atualiza a cada frame
{
	bottom = rect.getPosition().y + rect.getSize().y;
	left = rect.getPosition().x;
	right = rect.getPosition().x + rect.getSize().x;
	top = rect.getPosition().y;

}
void Player:: IsCollide(Edge *  ed, int j)
{
	if (rect.getGlobalBounds().intersects(ed->edge.getLocalBounds())) //colisao com edge esquerda
	Collide(j);

	if (rect.getGlobalBounds().intersects(ed->par->edge.getGlobalBounds())) //colisao com edge direita
		Collide(j);

	else //colisao pixel a pixel
	{ 
		float colBottom, colTop, colLeft, colRight;
		colBottom = std::min(bottom, ed->lados[0]);
		colTop = std::max(top, ed->lados[2]);
		colLeft = std::max(left, ed->lados[1]);
		colRight = std::min(right, ed->lados[3]);
		for (int i = colTop; i < colBottom; i++)
		{
			for (int k = colLeft; k < colRight; k++)
			{
				if (mask[k - left][i - top] && ed->mask[k - ed->lados[1]][i - ed->lados[2]])
					Collide(j);
				
			}
		}


	}
	

}

 void Player:: Collide(int j) //colisao
{
	jmpSpeed = 0;
	gameOver = true;

}


