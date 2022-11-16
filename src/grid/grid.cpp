#include "grid.hpp"

Tile::Tile(){
    // error handling
}

Tile::Tile(bool allFalse, std::string texPath){
    if(allFalse){
        tilled = false;
        planted = false;
        crop = Null;
        stage = 0;
    }
    path = texPath;
}

void Tile::setCrop(ItemID cropType){
    crop = cropType;
    // add switch statement for crop texturing
    stage = 0;
    switch(crop){
        case Graines_de_Citrouille:
            cropTex.loadFromFile("../../resources/crops/pumpkin/stage1.png");
            break;
        case Graines_de_Tomate:
            cropTex.loadFromFile("../../resources/crops/tomato/stage1.png");
            break;
        case Graines_de_chu:
            cropTex.loadFromFile("../../resources/crops/cabbage/stage1.png");
            break;
        case Graines_de_carotte:
            cropTex.loadFromFile("../../resources/crops/carrot/stage1.png");
            break;
        case Graines_d_aubergine:
            cropTex.loadFromFile("../../resources/crops/eggplant/stage1.png");
            break;
        case Graines_de_pomme_de_terre:
            cropTex.loadFromFile("../../resources/crops/potato/stage1.png");
            break;
        case Graines_de_fraise:
            cropTex.loadFromFile("../../resources/crops/strawberry/stage1.png");
            break;
        case Graines_de_Panais:
            cropTex.loadFromFile("../../resources/crops/parsnip/stage1.png");
            break;
        default:
            break;
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
            Tile temp(true, "NULL");
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
            if(grid::gridSquares.at(i).at(j).path != "NULL"){
                sf::Sprite sprite;
                sprite.setPosition(x, y);
                sprite.setTexture(grid::gridSquares.at(i).at(j).tex);
                window->draw(sprite);
                std::cout << "Drew sprite\n";
            }
            else{
                std::cout << "Drew square\n";
                window->draw(gridSquare);
            }
            if(grid::gridSquares.at(i).at(j).stage == 0){
                sf::Sprite crop;
                crop.setPosition(x, y);
                crop.setTexture(grid::gridSquares.at(i).at(j).cropTex);
                window->draw(crop);
                std::cout << "Drew crop\n";
            }
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

