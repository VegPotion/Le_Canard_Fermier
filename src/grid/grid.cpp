#include "grid.hpp"

Tile::Tile(){
    // error handling
}

Tile::Tile(bool allFalse, std::string texPath){
    if(allFalse){
        tilled = false;
        planted = false;
        crop = Null;
        stage = -1;
    }
    path = texPath;
}

void Tile::setCrop(ItemID cropType, int stage){
    crop = cropType;
    // add switch statement for crop texturing
    this->stage = stage;
    if(stage > 3){
        std::cerr << "Given too high of a stage\n";
        return;
    }
    switch(crop){
        case Graines_de_Citrouille:
            cropTex.loadFromFile("resources/crops/pumpkin/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_Tomate:
            cropTex.loadFromFile("resources/crops/tomato/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_chu:
            cropTex.loadFromFile("resources/crops/cabbage/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_carotte:
            cropTex.loadFromFile("resources/crops/carrot/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_d_aubergine:
            cropTex.loadFromFile("resources/crops/eggplant/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_pomme_de_terre:
            cropTex.loadFromFile("resources/crops/potato/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_fraise:
            cropTex.loadFromFile("resources/crops/strawberry/stage" + std::to_string(stage+1) + ".png");
            break;
        case Graines_de_Panais:
            cropTex.loadFromFile("resources/crops/parsnip/stage" + std::to_string(stage+1) + ".png");
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
            if(grid::gridSquares.at(i).at(j).clock.getElapsedTime().asSeconds() > 10.0f){
                grid::gridSquares.at(i).at(j).stage++;
                grid::gridSquares.at(i).at(j).setCrop(grid::gridSquares.at(i).at(j).crop, grid::gridSquares.at(i).at(j).stage);
                grid::gridSquares.at(i).at(j).clock.restart();
            }
			if(grid::gridSquares.at(i).at(j).tilled){
				sf::RectangleShape soil(sf::Vector2f(40, 40));
				soil.setFillColor(sf::Color(150, 75, 0, 255));
				soil.setPosition(x, y);
				window->draw(soil);
			}
            if(grid::gridSquares.at(i).at(j).stage >= 0){
                sf::Sprite crop;
                crop.setScale(2, 2);
                crop.setPosition(x, y);
                crop.setTexture(grid::gridSquares.at(i).at(j).cropTex);
                window->draw(crop);
                // std::cout << "Drew crop at: " << i << ", " << j << "\n";
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
                //    std::cout << "result.x = " << result.x << ", result.y = " << result.y << std::endl;
                   return result;
               }
               result.y++;
           }
           result.x++;
           result.y = 0;
	}
	return sf::Vector2i(-1, -1);
}

