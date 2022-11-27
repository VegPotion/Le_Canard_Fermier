#include "player.hpp"

Player::Player(float _x, float _y, float _speed, std::string path){
	x = _x;
	y = _y;
    monogram.loadFromFile("resources/fonts/monogram.ttf");
	speed = _speed;
    if(path != "NULL"){
        if(tex.loadFromFile(path)){
            std::cout << "Loaded texture from " << path << std::endl;
        }
        loadedTexture = true;
    }
    else if(path == "NULL"){
        std::cout << "WARNING: Given null texture path\n";
        loadedTexture = false;
    }
}

void Player::draw(sf::RenderWindow* window){
    if(loadedTexture){
	    sf::Sprite sprite;
        sprite.setPosition(x, y);
    	sprite.setTexture(tex);
    	window->draw(sprite);   
    }
    else{
        sf::CircleShape shape(20.f);
        shape.setPosition(x, y);
        shape.setFillColor(sf::Color::Green);
        window->draw(shape);
    }
    if(!inventory.empty()){
        for(int i = 0; i < inventory.size(); i++){
            Item invItem = inventory.at(i);
            if(i < 9){
                invItem.x = (30 * i);
                invItem.y = 30;
                sf::Text num;
                num.setString(std::to_string(invItem.stackSize));
                num.setFont(monogram);
                num.setPosition(invItem.x, invItem.y);
                if(invItem.loadedTexture){
                    sf::Sprite sprite;
                    sprite.setPosition(invItem.x, invItem.y);
                    sprite.setTexture(invItem.tex);
                    window->draw(sprite);
                }
                else{
                    sf::CircleShape shape(10.0f);
                    shape.setPosition(invItem.x, invItem.y);
                    shape.setFillColor(sf::Color::Red);
                    window->draw(shape);
                }
                if(i == hotbarIndex){
                    sf::RectangleShape select;
                    select.setSize(sf::Vector2f(invItem.tex.getSize().x, invItem.tex.getSize().y));
                    select.setPosition(invItem.x, invItem.y);
                    select.setFillColor(sf::Color(235, 240, 108, 127));
                    select.setOutlineColor(sf::Color::Black);
                    window->draw(select);
                }
		sf::Text name;
		name.setString("NULL");
		sf::RectangleShape textBox;
                if(std::abs(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x - invItem.x) <= 10.0f && std::abs(window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y - invItem.y) <= 10.0f){
                    name.setFont(monogram);
                    name.setFillColor(sf::Color::Black);
                    name.setPosition(invItem.x+invItem.tex.getSize().x,invItem.y/2);
                    name.setString(invItem.name);
                    textBox.setSize(sf::Vector2f(name.getGlobalBounds().width, name.getGlobalBounds().height));
                    textBox.setPosition(name.getPosition().x, name.getPosition().y + name.getGlobalBounds().height+4);
                }
                window->draw(num);
		if(name.getString() != "NULL"){
			window->draw(textBox);
			window->draw(name);
		}
            }
        }
    }
}

void Player::input(sf::Time delta){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
		y -= speed * delta.asSeconds();
        facing = UP;
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
		y += speed * delta.asSeconds();
        facing = DOWN;
	}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        x -= speed * delta.asSeconds();
        facing = LEFT;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        x += speed * delta.asSeconds();
        facing = RIGHT;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        sf::Vector2i currentSquare(0, 0);
        if(loadedTexture){
            // I don't have a texture width yet
        }
        else{
            currentSquare = grid::xyToGridSquare(x + 20, y + 20);
        }
        if(heldItem.ID == Houe){
            sf::Vector2i nextSquare(-1, -1);
            switch(facing){
                case UP:
                    nextSquare.x = currentSquare.x - 1;
                    nextSquare.y = currentSquare.y;
                    break;
                case DOWN:
                    nextSquare.x = currentSquare.x + 1;
                    nextSquare.y = currentSquare.y;
                    break;
                case LEFT:
                    nextSquare.x = currentSquare.x;
                    nextSquare.y = currentSquare.y - 1;
                case RIGHT:
                    nextSquare.x = currentSquare.x;
                    nextSquare.y = currentSquare.y + 1;
                default:
                    break;
            }
            if(nextSquare.x >= 0 && nextSquare.x <= 19 && nextSquare.y <= 19 &&  nextSquare.y >= 0){
                if(!grid::gridSquares.at(nextSquare.x).at(nextSquare.y).tilled){
                    grid::gridSquares.at(nextSquare.x).at(nextSquare.y).tilled = true;
                    // std::cout << "Tilled\n";
                }
                else{
                    // std::cout << "Already Tilled\n";
                }
            }
            else{
                // std::cout << "Next Square out of range\n";
                // std::cout << "x: " << nextSquare.x << " y: " << nextSquare.y << std::endl;
            }
        }
        else if(heldItem.ID >= Graines_de_Citrouille && heldItem.ID <= Graines_de_chu){
            if(grid::gridSquares.at(currentSquare.x).at(currentSquare.y).tilled && !grid::gridSquares.at(currentSquare.x).at(currentSquare.y).planted){
                heldItem.stackSize--;
                grid::gridSquares.at(currentSquare.x).at(currentSquare.y).clock.restart();
                grid::gridSquares.at(currentSquare.x).at(currentSquare.y).planted = true;
                grid::gridSquares.at(currentSquare.x).at(currentSquare.y).setCrop(heldItem.ID, 0);
                std::cout << "Set grid square at (" << currentSquare.x << ", " << currentSquare.y << ") to have crop " << heldItem.name << "\n";
            }
        }
    }
    // Select Slots
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
        if(hotbarIndex == 0){
            hotbarIndex = -1;
        }
        if(!inventory.empty()){
            heldItem = inventory.at(0);
            hotbarIndex = 0;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
        if(hotbarIndex == 1){
            hotbarIndex = -1;
        }
        if(2 <= inventory.size()){
            heldItem = inventory.at(1);
            hotbarIndex = 1;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
        if(hotbarIndex == 2){
            hotbarIndex = -1;
        }
        if(3 <= inventory.size()){
            heldItem = inventory.at(2);
            hotbarIndex = 2;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
        if(hotbarIndex == 3){
            hotbarIndex = -1;
        }
        if(4 <= inventory.size()){
            heldItem = inventory.at(3);
            hotbarIndex = 3;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
        if(hotbarIndex == 4){
            hotbarIndex = -1;
        }
        if(5 <= inventory.size()){
            heldItem = inventory.at(4);
            hotbarIndex = 4;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
        if(hotbarIndex == 5){
            hotbarIndex = -1;
        }
        if(6 <= inventory.size()){    
            heldItem = inventory.at(5);
            hotbarIndex = 5;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)){
        if(hotbarIndex == 6){
            hotbarIndex = -1;
        }
        if(7 <= inventory.size()){
            heldItem = inventory.at(6);
            hotbarIndex = 6;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)){
        if(hotbarIndex == 7){
            hotbarIndex = -1;
        }
        if(8 <= inventory.size()){
            heldItem = inventory.at(7);
            hotbarIndex = 7;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)){
        if(hotbarIndex == 8){
            hotbarIndex = -1;
        }
        if(9 <= inventory.size()){    
            heldItem = inventory.at(8);
            hotbarIndex = 8;
        }
    }
}

void Player::PickupItem(std::vector<Item>* items){
    for(int i = 0; i < items->size(); i++){
        Item item = items->at(i);
        if((std::abs(x - item.x) <= 25.0f) && (std::abs(y - item.y) <= 25.0f)){
            items->erase(items->begin() + i);
            if(inventory.empty()){
                // std::cout << "added to empty inventory\n";
                inventory.push_back(item);
            }
            else{
                bool addedToStack = false;
                for(int j = 0; j < inventory.size(); j++){
                    Item invItem = inventory.at(j);
                    // std::cout << "invItem.ID = " << invItem.ID << std::endl;
                    // std::cout << "item.ID = " << item.ID << std::endl;
                    if(invItem.ID == item.ID){
                        // std::cout << "Combined with " << invItem.name << " x" << invItem.stackSize << std::endl;
                        inventory.at(j).stackSize += item.stackSize;
                        addedToStack = true;
                        break;
                    }
                }
                if(!addedToStack){
                    inventory.push_back(item);
                }
            }
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
        if(hotbarIndex != -1){
            int index = -1;
            for(int i = 0; i < inventory.size(); i++){
                Item invItem = inventory.at(i);
                if(invItem==heldItem){
                    index = i;
                }
            }
            heldItem.y = y-35.0f;
            heldItem.x = x;
            inventory.erase(inventory.begin()+index);
            items->push_back(heldItem);
            heldItem = Item();
            hotbarIndex = -1;
        }
    }
}

