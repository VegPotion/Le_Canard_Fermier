#include "item.hpp"

Item::Item(){
    // to fix an error?
}

Item::Item(ItemID _id, int _size){
    ID = _id;
    stackSize = _size;
    switch(_id){
         case Bois:
             name = "Bois";
             tex.loadFromFile("resources/wood/wood.png");
             break;
         case Brindille:
             name = "Brindille";
             tex.loadFromFile("resources/stick/stick.png");
             break;
         case Pierre:
             name = "Pierre";
             tex.loadFromFile("resources/stone/stone.png");
             break;
         case Caillou:
             name = "Caillou";
             tex.loadFromFile("resources/pebble/pebble.png");
             break;
         case Arrosoir:
             name = "Arrosoir";
             tex.loadFromFile("resources/watering-can/arrosoir.png");
             break;
         case Houe:
             name = "Houe";
             tex.loadFromFile("resources/hoe/hoe.png");
             break;
         default:
             name = "Undefined";
             loadedTexture = false;
             break;
     }
}

Item::Item(ItemID _id, float _x, float _y, int _size){
    ID = _id;
    stackSize = _size;
    switch(_id){
        case Bois:
            name = "Bois";
            tex.loadFromFile("resources/wood/wood.png");
            break;
        case Brindille:
            name = "Brindille";
            tex.loadFromFile("resources/stick/stick.png");
            break;
        case Pierre:
            name = "Pierre";
            tex.loadFromFile("resources/stone/stone.png");
            break;
        case Caillou:
            name = "Caillou";
            tex.loadFromFile("resources/pebble/pebble.png");
            break;
        case Arrosoir:
            name = "Arrosoir";
            tex.loadFromFile("resources/watering-can/arrosoir.png");
            break;
        case Houe:
            name = "Houe";
            tex.loadFromFile("resources/hoe/hoe.png");
            break;
        default:
            name = "Undefined";
            loadedTexture = false;
            break;
    }
    x = _x;
    y = _y;
}

void Item::draw(sf::RenderWindow* window){
    if(loadedTexture){
        sf::Sprite sprite;
        sprite.setTexture(tex);
        sprite.setPosition(x, y);
        window->draw(sprite);
    }
    else{
        sf::CircleShape shape(10.0f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
        window->draw(shape);
    }
}
