#pragma once
#include "Button.hpp"
class ShipButton :
	public Button
{
public:
	ShipButton();
	ShipButton(const sf::Texture&, const sf::Texture&, sf::Vector2f = sf::Vector2f(0.0f, 0.0f));
	~ShipButton();

	virtual void doDraw(sf::RenderTarget& target);

private:
	sf::Sprite ship;
};

