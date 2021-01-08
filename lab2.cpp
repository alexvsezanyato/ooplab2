#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include "Tpoint.hpp"

short getRandom(short from, short to) {
    short number;
    number = std::rand() % (to - from) + from;
    return number;
}

class PointMover {
public:
    using Color = sf::Color;
    using Vec2f = sf::Vector2f;
    using Vec2u = sf::Vector2u;
    using Window = sf::RenderWindow;
    using KeyboardEvent = sf::Event;
    using SfmlEvent = sf::Event;
    using Keyboard = sf::Keyboard;

    enum TimeFormat {
        Microseconds,
        Milliseconds,

        // will work in the future
        // Seconds,
        // Minutes,
        // Hours
    };

    enum WindowStyle {
        Windowed,
        Fullscreen,
    };

    struct Waiting {
        unsigned count = 0;
        TimeFormat format = Milliseconds;
    };

private:
    Tpoint** points = nullptr;
    short pointCount = 0;
    Window* window = nullptr;
    Vec2u windowSize = {800, 600};
    std::string title = "Point mover!";
    Tpoint::MoveType moveType = Tpoint::Straight;
    Tpoint::Clock clock;
    Waiting waitingTime{5, Milliseconds}; // don't render for
    std::string appName = "Point mover";

    void handleEvent(SfmlEvent e) {
        switch (e.type) {
        case SfmlEvent::Closed:
            window->close();
            break;
        }
        return;
    }

    void drawPoint(Tpoint* point) {
        Tpoint::Circle circle(1.f, 4);
        Tpoint::Vec2f pos = point->getPosition();
        circle.setPosition(pos);
        circle.setFillColor(point->getColor());
        window->draw(circle);
        return;
    }

    unsigned getTime(TimeFormat format = Milliseconds) {
        Tpoint::Time time = clock.getElapsedTime();
        unsigned formattedTime;

        switch (format) {
        case Microseconds:
            formattedTime = time.asMicroseconds();
            break;
        case Milliseconds:
            formattedTime = time.asMilliseconds();
            break;
        default:
            formattedTime = -1;
            break;
        }

        return formattedTime;
    }

    void run() {
        sf::VideoMode videoMode(windowSize.x, windowSize.y);
        window->create(videoMode, title, sf::Style::Close);
        short n = pointCount;
        Window* w = this->window;

        for (short i = 0; i < n; i++) {
            Tpoint::MoveSettings moveSettings;
            moveSettings.moveType = moveType;
            moveSettings.speed = 1.f;
            moveSettings.scale = getRandom(-179, 179);
            points[i]->setSettings(moveSettings);
            short a = Tpoint::getRandom(150, 255);
            short b = Tpoint::getRandom(150, 255);
            short c = Tpoint::getRandom(150, 255);
            points[i]->setColor(Tpoint::Color(a, b, c));
        }
        while (w->isOpen()) {
            // check sfml events
            SfmlEvent e;
            while (w->pollEvent(e)) handleEvent(e);

            // time format, time number
            auto tf = waitingTime.format;
            auto tc = waitingTime.count;

            // if time came, update
            if (getTime(tf) < tc) continue;
            else clock.restart();
            for (short i = 0; i < n; i++) points[i]->update();

            // and render
            w->clear();
            for (short i = 0; i < n; i++) drawPoint(points[i]);
            w->display();
        }
        return;
    }

public:
    void handleAnswer(short answer) {
        switch (answer) {
        case 1:
            moveType = Tpoint::Straight;
            run();
            break;
        case 2:
            moveType = Tpoint::Arbitrarily;
            run();
            break;
        }
        return;
    }

    std::string getName() {
        // ..
        return this->appName;
    }

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
    short count = 1000;
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
