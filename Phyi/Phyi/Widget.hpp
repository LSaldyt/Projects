#pragma once
#include "Includes.hpp"

class Widget :
	public sf::Sprite
{
public:
	Widget();
	Widget(const sf::Texture& text, sf::Vector2f = sf::Vector2f(0.0f, 0.0f));
	~Widget();

	virtual void update();
	virtual void doDraw(sf::RenderTarget& target);

	const bool clickedOn(sf::Vector2f coords);
};

