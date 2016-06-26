#include "TextureMap.hpp"
#include <iostream>

TextureMap::TextureMap()
{
	textures = std::make_unique< std::unordered_map<std::string, sf::Texture> >();
}

TextureMap::~TextureMap(){}

const sf::Texture& TextureMap::get(std::string file)
{
	return textures->at(file);
}

void TextureMap::load(std::string file)
{
	sf::Texture texture;
	if (!texture.loadFromFile(file))
	{
		std::cout << "Couldn't find image" << std::endl;
	}

	stripEnding(file);

	textures->insert(std::make_pair(file, texture));
}

void TextureMap::stripEnding(std::string& string)
{
	string = string.substr(0, string.find("."));
}