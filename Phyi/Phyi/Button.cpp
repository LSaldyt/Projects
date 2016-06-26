#include "Button.hpp"



Button::Button()
{
}

Button::Button(const sf::Texture & set_text, sf::Vector2f set_position)
{
	setPosition(set_position);
	setTexture(set_text);
}


Button::~Button()
{
}
