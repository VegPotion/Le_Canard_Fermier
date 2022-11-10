#include <iostream>

#include <SFML/Graphics.hpp>
#include "player/player.hpp"
#include "grid/grid.hpp"

#include <vector>

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 450), "La Maisonnette de Agriculture");
    window.setVerticalSyncEnabled(true);
    Player p(0, 0, 200, "NULL");

    grid::setGrid(20, 20, &window);

    sf::CircleShape relativeMouse(5.0f);
    sf::CircleShape mouse(5.0f);
    sf::CircleShape mappedMouse(5.0f);
    relativeMouse.setFillColor(sf::Color::Blue);
    mouse.setFillColor(sf::Color::Cyan);
    mappedMouse.setFillColor(sf::Color::Magenta);

    std::vector<Item> items;
    Item i(Bois, 100, 30, 1);
    Item i2(Pierre, 100, 90, 12);
    Item i3(Pierre, 200, 100, 10);
    Item i4(Brindille, 200, 30, 12);
    Item i5(Caillou, 100, 150, 19);
    Item i6(Arrosoir, 300, 120, 20);
    Item i7(Houe, 400, 111, 31);
    items.push_back(i);
    items.push_back(i2);
    items.push_back(i3);
    items.push_back(i4);
    items.push_back(i5);
    items.push_back(i6);
    items.push_back(i7);

    sf::Clock deltaClock;

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                 window.close();   
            }
        }
        p.input(deltaClock.restart());
        p.PickupItem(&items);

        window.clear(sf::Color(20, 130, 10, 255));
        grid::draw(&window);
        p.draw(&window);
        relativeMouse.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
        mouse.setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
        mappedMouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y);
        window.draw(relativeMouse);
        window.draw(mappedMouse);
        window.draw(mouse);
        for(int iter = 0; iter < items.size(); iter++){
                items.at(iter).draw(&window);
        }
            window.display();
        }
        return 0;
    }
