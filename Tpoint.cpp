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

Tpoint::Tpoint(Tpoint::Vec2f pos) {
    setPos(pos);
    return;
}

Tpoint::Tpoint(Tpoint::Vec2f pos, Tpoint::Window* window) {
    connect(window);
    setPos(pos);
    return;
}
