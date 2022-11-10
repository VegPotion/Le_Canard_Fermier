#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "../item/item.hpp"

class Tile{
    public:
        Tile();
        Tile(bool allFalse);
        bool tilled;
        bool planted;
        ItemID crop;
        int stage;
};

namespace grid{
    inline float width;
    inline float height;
    inline int MAXW, MAXH;
    inline std::vector<std::vector<Tile> > gridSquares;
    void setGrid(int maxWidth, int maxHeight, sf::RenderWindow* window);
    void draw(sf::RenderWindow* window);
    sf::Vector2i xyToGridSquare(float x, float y);
}

#endif
