#ifndef ITEM_H
#define ITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <algorithm>

enum ItemID{
    Null = -1,
    Bois = 0, // Wood
    Brindille, // Twig
    Pierre, // Stone
    Caillou, // Pebble
    Houe, // Hoe(Farming)
    Arrosoir, // Watering Can
    Arroseur, // Sprinkler
    Graines_de_Citrouille, //[#7] Pumpkin Seeds
    Graines_de_pomme_de_terre, // Potato Seeds
    Graines_de_Tomate, // Tomato Seeds
    Graines_d_aubergine, // Eggplant Seeds
    Graines_de_Panais, // Parsnip Seeds
    Graines_de_fraise, // Strawberry Seeds
    Graines_de_carotte, // Carrot Seeds
    Graines_de_chu, //[#14] Cabbage Seeds
    Citrouille, //[#15]
    Pomme_de_Terre,
    Tomate,
    Aubergine,
    Panais,
    Fraise,
    Carotte,
    Chu // [#22]
};

class Item{
    public:
        std::string name;
        sf::Texture tex;
        int stackSize;
        ItemID ID;
        bool inInventory = false;
        float x, y;
        Item();
        Item(ItemID _id, int _size);
        Item(ItemID _id, float _x, float _y, int _size);
        void draw(sf::RenderWindow* window);
        bool loadedTexture = true;
        bool operator==(Item item){
            return ((int)this->ID == (int)item.ID) && this->x == item.x && this->y == item.y && this->stackSize == item.stackSize;
        }
};

#endif
