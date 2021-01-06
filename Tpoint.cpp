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

void Tpoint::reflectHorisontal() {
    unsigned a = moveSettings.scale;
    unsigned b = (unsigned) ((abs(a) + 90) % 180);
    if (a < 0) b = -b;
    setScale(b);
    return;
}

void Tpoint::reflectVertical() {
    unsigned a = moveSettings.scale;
    unsigned b = (unsigned) ((a + 90) % 180);
    setScale(b);
    return;
}

void Tpoint::reflect() {
    bool horisontal = false;
    bool virtical = false;
    Tpoint::Vec2u windowSize = window->getSize();
    float wx = (float) windowSize.x;
    float wy = (float) windowSize.y;
    float px = pos.x;
    float py = pos.y;
    float rx = wx - px;
    float ry = wy - py;
    if (rx < 0 || rx > wx) virtical = true;
    if (ry < 0 || ry > wy) horisontal = true;

    if (virtical) reflectVertical();
    if (horisontal) reflectHorisontal();
    return;
}

bool Tpoint::update() {
    if (!window) return false;
    updatePosition();
    idleTime.restart();
    return true;
}

void Tpoint::updatePosition() {
    auto speed = moveSettings.speed;
    auto scale = moveSettings.scale;
    pos.x += speed * cos(scale);
    pos.y += speed * sin(scale);

    if (isOver()) {
        reflect();
        pos.x += speed * cos(scale);
        pos.y += speed * sin(scale);
    }
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

void Tpoint::setScale(unsigned scale) {
    moveSettings.scale = scale;
    return;
}
void Tpoint::setSettings(Tpoint::MoveSettings settings) {
    this->moveSettings = settings;
    return;
}
