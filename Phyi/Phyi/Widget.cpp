#include "Widget.hpp"



Widget::Widget()
{
}

Widget::Widget(const sf::Texture & set_text, sf::Vector2f set_position)
{
	setPosition(set_position);
	setTexture(set_text);
}

Widget::~Widget()
{
}

void Widget::update()
{
}

void Widget::doDraw(sf::RenderTarget & target)
{
	target.draw(*this);
}

const bool Widget::clickedOn(sf::Vector2f coords)
{
	return getGlobalBounds().contains(coords);
}
