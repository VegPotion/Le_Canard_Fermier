#include "grid.hpp"

Tile::Tile(){
    // error handling
}

Tile::Tile(bool allFalse){
    if(allFalse){
        tilled = false;
        planted = false;
        crop = Null;
        stage = 0;
    }
}

void grid::setGrid(int maxWidth, int maxHeight, sf::RenderWindow* window){
    grid::width = window->getSize().x / maxWidth;
    grid::height = window->getSize().x / maxHeight;
    MAXW = maxWidth;
    MAXH = maxHeight;
    gridSquares.resize(maxWidth);
    for(int i = 0; i < gridSquares.size(); i++){
        gridSquares.at(i).resize(maxHeight);
    }
    for(int j = 0; j < gridSquares.size(); j++){
        for(int n = 0; n < gridSquares.at(j).size(); n++){
            Tile temp(true);
            gridSquares.at(j).at(n) = temp;
        }
    }
}

void grid::draw(sf::RenderWindow* window){
    bool white = false;
    int i = 0;
    int j = 0;
    for(float x = 0.0f; x < grid::MAXW*grid::width; x += width){
        for(float y = 0.0f; y < grid::MAXH*grid::height; y += height){
            sf::RectangleShape gridSquare(sf::Vector2f(grid::width, grid::height));
            gridSquare.setPosition(x, y);
            if(white){
                gridSquare.setFillColor(sf::Color::White);
            }
            else{
                gridSquare.setFillColor(sf::Color::Black);
            }
            if(grid::gridSquares.at(i).at(j).tilled){
                gridSquare.setFillColor(sf::Color::Red);
            }
            window->draw(gridSquare);
            white = !white;
            j++;
        }
        white = !white;
        i++;
        j = 0;
    }
}

sf::Vector2i grid::xyToGridSquare(float _x, float _y){
    sf::Vector2i result(0, 0);
    for(float x = 0.0f; x < grid::MAXW*grid::width; x += width){
           for(float y = 0.0f; y < grid::MAXH*grid::height; y += height){
               if(_x > x && _x < x+grid::width && _y > y && _y < y+grid::height){
                   std::cout << "result.x = " << result.x << ", result.y = " << result.y << std::endl;
                   return result;
               }
               result.y++;
           }
           result.x++;
           result.y = 0;
       }
}

