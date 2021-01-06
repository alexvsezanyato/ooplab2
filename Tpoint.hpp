#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

class Tpoint {
public:
    using Color = sf::Color;
    using Vec2f = sf::Vector2f;
    using Vec2u = sf::Vector2u;
    using Window = sf::RenderWindow;
    using Time = sf::Time;
    using Clock = sf::Clock;
    using Rectangle = sf::RectangleShape;
    using Circle = sf::CircleShape;
    Tpoint() = delete;

    enum MoveType {
        Straight,
        Arbitrarily
    };

    struct MoveSettings {
        MoveType moveType = Straight;
        float speed = 1.f; // relative to default
        unsigned scale = 0; // degrees
        unsigned sleepTime = 1000000; // how long it doesn't update
    };

private:
    Vec2f pos{0.f, 0.f};
    sf::RenderWindow* window = nullptr;
    Color color{255, 255, 255};
    MoveSettings moveSettings;
    Clock idleTime;
    // bool rerender(); deprecated
    void updatePosition();
    void setScale(unsigned scale); // in degrees
    Time getIdleTime();
    void reflectHorisontal();
    void reflectVertical();
    void reflect();
    bool setPos(Vec2f pos);

public:
    Vec2f getPosition();
    Vec2f getPos(); // alias
    Color getRandomColor();
    bool isOver();
    void connect(Window*); // connect to window
    void disconnect(); // disconnect from window
    void moveStraight(); // change move type
    void moveArbitrarily(); // change move type
    bool update();
    void setSettings(MoveSettings);
    Tpoint(Vec2f pos);
    Tpoint(Vec2f pos, Window*);
};
