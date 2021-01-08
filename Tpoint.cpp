#include "Tpoint.hpp"

Tpoint::Vec2f Tpoint::getPos() {
    auto pos = this->pos;
    return pos;
}

bool Tpoint::isOver() {
    if (!window) return true;
    Tpoint::Vec2u win = window->getSize();
    if (pos.x < 0 || pos.y < 0) return true;
    if (win.x < pos.x || win.y < pos.y) return true;
    return false;
}

bool Tpoint::setPos(Tpoint::Vec2f pos) {
    this->pos = pos;
    return true;
}

void Tpoint::connect(Tpoint::Window* window) {
    this->window = window;
    return;
}

void Tpoint::disconnect() {
    this->window = nullptr;
    return;
}

void Tpoint::reflect(Tpoint::WindowSide windowSide) {
    short a = moveSettings.scale;
    short b;

    switch (windowSide) {
        case Tpoint::Top: {
            b = -a;
            //std::cout << "Reflection::topSide (";
            //std::cout << "a = " << a << "; b = " << b;
            //std::cout << std::endl;
            break;
        }
        case Tpoint::Bottom: {
            b = -a;
            //std::cout << "Reflection::BottomSide (";
            //std::cout << "a = " << a << "; b = " << b;
            //std::cout << std::endl;
            break;
        }
        case Tpoint::Left: {
            if (a) b = a / abs(a) * 180 - a;
            else b = 180 - a;
            //std::cout << "Reflection::LeftSide (";
            //std::cout << "a = " << a << "; b = " << b;
            //std::cout << std::endl;
            break;
        }
        case Tpoint::Right: {
            if (a) b = a / abs(a) * 180 - a;
            else b = 180 - a;
            //std::cout << "Reflection::RightSide (";
            //std::cout << "a = " << a << "; b = " << b;
            //std::cout << std::endl;
            break;
        }
    }
    setScale(b);
    return;
}

void Tpoint::reflect() {
    Tpoint::Vec2u windowSize = window->getSize();
    float ww = (float) windowSize.x;
    float wh = (float) windowSize.y;

    if (pos.x < 0) reflect(Tpoint::Left);
    if (pos.x > ww) reflect(Tpoint::Right);
    if (pos.y < 0) reflect(Tpoint::Top);
    if (pos.y > wh) reflect(Tpoint::Bottom);
}

bool Tpoint::update() {
    if (!window) return false;
    updatePosition();
    idleTime.restart();
    return true;
}

short Tpoint::getRandom(short from, short to) {
    short number;
    number = std::rand() % (to - from) + from;
    return number;
}

void Tpoint::updatePosition() {
    auto speed = moveSettings.speed;
    auto scale = moveSettings.scale;

    switch (moveSettings.moveType) {
    case Tpoint::Arbitrarily:
        scale += Tpoint::getRandom(-6, 8);
        if (scale >= 180) scale = 179;
        if (scale <= -180) scale = -179;
        moveSettings.scale = scale;
        break;
    case Tpoint::Straight:
        // .. do something
        break;
    }
    pos.x += speed * cos(scale * 3.14 / 180);
    pos.y += speed * sin(scale * 3.14 / 180);

    if (isOver()) {
        reflect();
        scale = moveSettings.scale;
        pos.x += speed * cos(scale * 3.14 / 180);
        pos.y += speed * sin(scale * 3.14 / 180);

        // report
        Tpoint::Vec2u win = window->getSize();
        float ww = (float) win.x;
        float wh = (float) win.y;

        // std::cout << "pos.x = " << pos.x << "; pos.y = " << pos.y << std::endl;
        // std::cout << "win.x = " << ww << "; win.y = " << wh << std::endl;
        // std::cout << "scale = " << scale;
        // std::cout << std::endl << std::endl;
    }
}

void Tpoint::setColor(Tpoint::Color color) {
    this->color = color;
    return;
}

Tpoint::Color Tpoint::getColor() {
    // ...
    return color;
}

Tpoint::Vec2f Tpoint::getPosition() {
    // ...
    return pos;
}

Tpoint::Tpoint(Tpoint::Vec2f pos) {
    setPos(pos);
    return;
}

Tpoint::Tpoint(Tpoint::Vec2f pos, Tpoint::Window* window) {
    connect(window);
    setPos(pos);
    return;
}

void Tpoint::setScale(short scale) {
    moveSettings.scale = scale;
    return;
}
void Tpoint::setSettings(Tpoint::MoveSettings settings) {
    this->moveSettings = settings;
    return;
}
