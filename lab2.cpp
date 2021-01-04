#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event>
#include "Tpoint.hpp"

short getRandom(short from, short to) {
    short number;
    number = std::rand() % (to - from) + from;
    return number;
}
namespace PointEvent {
    enum List {
        IsOver
    }
}

class PointMover {
public:
    using Color = sf::Color;
    using Vec2f = sf::Vector2f;
    using Vec2u = sf::Vector2u;
    using Window = sf::RenderWindow;
    
private:
    Tpoint** points = nullptr;
    short pointCount = 0; 
    Window* window = nullptr;
    Vec2u windowSize = {800, 600};
    std::string title = "Point mover!";
    Tpoint::MoveSettings::Mode moveMode;

    void handleAnswer(short answer) {
        switch (answer) { 
        case 1:
            run(Tpoint::MoveSettings::Straight);
            break;
        case 2:
            run(Tpoint::MoveSettings::Arbitrarily);
            break;
        }
        return;
    }

    void handleEvent(PointEvent::List e) {
        switch (e) {
        case PointEvent::IsOver:
            
            break;
        }
        return;
    }

    void run(Tpoint::MoveSettings::Mode moveMode) {
        sf::VideoMode videoMode(windowSize.x, windowSize.y);
        window->create(videoMode, title);
        
        while (window->isOpen()) {
            sf::Event event;
            while (w->pollEvent(e)) handleEvent(e); 
            short n = pointCount;
            for (short i = 0; i < n; i++) 
                
        }
        return;
    }

public:
    void printMenu() {
        std::cout << "1. Прямолинейное движение с отражением от стенок экрана" << std::endl;
        std::cout << "2. Случайное движение с отражением" << std::endl;
        return;
    }

    void setSize(Vec2u windowSize) {
        this->windowSize = windowSize;
        return;
    }

    void setPoints(Tpoint** points, short pointCount) {
        this->points = points;
        this->pointCount = pointCount;
        return;
    }

    PointMover(Window* window, Tpoint** points, short* pointCount) {
      this->window = window;
      setPoints(points, *pointCount);
      return; 
    }
};

int main() {
    short count = 100;
    Tpoint** points = new Tpoint*[count];

    Tpoint::Vec2u size = {800, 600};
    // sf::VideoMode videoMode = new sf::VideoMode::getDesktopMode();
    Tpoint::Window window;

    for (short i = 0; i < count; i++) {
        Tpoint::Vec2f position;
        position.x = getRandom(0, size.x);
        position.y = getRandom(0, size.y);
        points[i] = new Tpoint(position, &window);
    }

    PointMover app(&window, points, &count);
    app.setSize(size);
    app.printMenu();
    short answer;
    std::cout << ":: Your answer: ";
    std::cin >> answer;
    app.handleAnswer(answer);
    for (short i = 0; i < count; i++) delete points[i];
}
