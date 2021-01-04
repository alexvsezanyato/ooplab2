#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Tpoint {
public:
    using Color = sf::Color;
    using Vec2f = sf::Vector2f;
    using Vec2u = sf::Vector2u;
    using Window = sf::RenderWindow;
    Tpoint() = delete;
    struct MoveSettings;

private:
    Vec2f pos{0.f, 0.f};
    sf::RenderWindow* window = nullptr;
    Color color{255, 255, 255};
    void move(MoveSettings* settings);

public:
    Color getRandomColor();
    Vec2f getPos();
    bool isOver();
    bool setPos(Vec2f pos);
    void connect(Window* window);
    void disconnect();
    void moveStraight();
    void moveArbitrarily();
    Tpoint(Vec2f pos);
    Tpoint(Vec2f pos, Window* window);
};

struct Tpoint::MoveSettings {
    enum Mode { 
        Straight,
        Arbitrarily
    };
};
