#include "ShipButton.hpp"



ShipButton::ShipButton()
{
}

ShipButton::ShipButton(const sf::Texture & back_texture, const sf::Texture & ship_texture, sf::Vector2f pos)
{
	setPosition(pos);
	setTexture(back_texture);
	ship.setTexture(ship_texture);
	ship.setScale(getGlobalBounds().width  / (ship.getGlobalBounds().width  * 2.0f),
				  getGlobalBounds().height / (ship.getGlobalBounds().height * 2.0f));
	ship.setPosition(sf::Vector2f(pos.x + ship.getGlobalBounds().width / 2.0f, pos.y + ship.getGlobalBounds().height / 2.0f));
}


ShipButton::~ShipButton()
{
}

void ShipButton::doDraw(sf::RenderTarget & target)
{
	target.draw(*this);
	target.draw(ship);
}
