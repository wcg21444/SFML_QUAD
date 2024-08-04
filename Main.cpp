#include "App.h"
#include "Grid.h"
#include "Object.h"
#include "Physics.h"
int main()
{
    Physics::dt = (float)1/60;

    App app;
    app.createWindow(1920, 1080, "QUAD");
    sf::RenderWindow& window = app.getWindow();
    float interval = 50;//¼ä¸ô
    Grid g(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f, 1080.f), interval);
    
    std::vector<Object*> boxes;

    std::vector<Box> boxes2;

    for(int i = 1;i<=10;++i)
    {
        boxes.emplace_back(new Box(sf::Vector2f(25 * i, 25 * i), sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(25, 25))));
        boxes2.push_back(Box(sf::Vector2f(25 * i, 25 * i), sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(25, 25))));
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                float zoom_direction = event.mouseWheelScroll.delta;
                float zoom_factor = 1.05;

                if(interval + zoom_direction * interval / 10>1)
                {
                    interval += zoom_direction * interval / 10;
                }
                printf("%f\n", interval);
;
                g.update(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f, 1080.f), interval);
            }
        }

        window.clear(sf::Color(66, 66, 66, 255));

        g.draw(window);
        for (auto& box : boxes)
        {
            box->update(app);
            box->draw(window);
        }
        for (auto& box : boxes2)
        {
            box.update(app);
        }
        window.display();
    }


    return 0;
}