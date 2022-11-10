#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "../item/item.hpp"
#include "../grid/grid.hpp"

enum dir{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

class Player{
	public:
		float x, y, speed;
		sf::Texture tex;
        std::vector<Item> inventory;
		Player(float _x, float _y, float _speed, std::string path);
		void draw(sf::RenderWindow* window);
		void input(sf::Time delta);
        void PickupItem(std::vector<Item>* items);
    private:
        dir facing;
        Item heldItem;
        int hotbarIndex = -1;
        bool loadedTexture = false;
};
inline sf::Font monogram;

#endif
