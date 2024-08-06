#include "App.h"
#include "Grid.h"
#include "Object.h"
#include "Physics.h"
#include "Quadtree.h"
#include "Base.h"
int main()
{
    Physics::dt = (float)1/60;

    Random<float> rnd_pos_x(650.f, 1000.f);
    Random<float> rnd_pos_y(250.f, 600.f);

    App app;
    app.createWindow(1920, 1080, "QUAD");
    sf::RenderWindow& window = app.getWindow();
    float interval = 50;//间隔
    Grid g(sf::Vector2f(0.f, 0.f), sf::Vector2f(1920.f, 1080.f), interval);
    
    std::vector<Object*> boxes;


    for(int i = 1;i<=360;++i)
    {
        boxes.emplace_back(new Box(sf::Vector2f(rnd_pos_x.getNum(),rnd_pos_y.getNum()), sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(5, 5))));
    }

    Quadtree quadTree(boxes, 10/*最大深度*/, 2/*最多物体个数*/, sf::Rect<float>(sf::Vector2f(400,200),sf::Vector2f(800,800.f)));

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
        quadTree.draw(window);
        for (auto& box : boxes)
        {
            box->update(app);
            box->draw(window);
        }
        
        window.display();
    }


    return 0;
}