#include <SFML/Graphics.hpp>
#include<iostream>
#include <vector>
#include <random>
using namespace sf;
using namespace std;

#define scr_w = 450;


int var1 = 1;

sf::Text circle(int row, int col, const sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setString("O");
    text.setFillColor(Color::Red);
    text.setCharacterSize(110);

    int sizex = 150 * row + (150 - 110) / 2;
    int sizey = 150 * col + ((150 - 110) / 2) - 10;
    text.setPosition(sf::Vector2f(sizex, sizey));

    return text;
}

sf::Text cross(int row, int col, const sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setString("X");
    text.setFillColor(Color::Green);
    text.setCharacterSize(110);

    int sizex = 150 * row + (150 - 110) / 2;
    int sizey = 150 * col + ((150 - 110) / 2) - 10;
    text.setPosition(sf::Vector2f(sizex, sizey));

    return text;
}

int mousePos(sf::Event& event)
{
    srand(time(NULL));
    int val = 0;

    if (event.type == sf::Event::MouseButtonPressed)
    {
  
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            int x = event.mouseButton.x;
            int y = event.mouseButton.y;


            if (x < 150)
            {
                val += 10;
            }
            else if (x < 300)
            {
                val += 20;
            }
            else
            {
                val += 30;
            }


            if (y < 150)
            {
                val += 1;
            }
            else if (y < 300)
            {
                val += 2;
            }
            else
            {
                val += 3;
            }
        }
    }

    return val;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(450, 450), "Tic Tac Toe");
    int random = (rand() % 3 + 1) * 10 + (rand() % 3 + 1);
    cout << random << endl;

    window.setVerticalSyncEnabled(1);

    sf::RectangleShape grid(sf::Vector2f(150, 150));
    grid.setFillColor(Color::Transparent);
    grid.setOutlineThickness(2.0f);
    grid.setOutlineColor(Color::Blue);

    sf::Font MyFont;
    if (!MyFont.loadFromFile("mvboli.ttf"))
    {
        cout << "error loading font";
    }

    std::vector<Text> circles;
    std::vector<Text> crosses;
    std::vector<int> positions_covered;
    int turns = 0;

    sf::Event event;
    while (window.isOpen())
    {
      
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (positions_covered.size() != 9)
        {
            if (find(positions_covered.begin(), positions_covered.end(), mousePos(event)) == positions_covered.end())
            {
                while (find(positions_covered.begin(), positions_covered.end(), random) != positions_covered.end())
                {
                    random = (rand() % 3 + 1) * 10 + (rand() % 3 + 1);
                }
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
                {
                    if (turns % 2 == 0)
                    {
                        circles.push_back(circle(mousePos(event) / 10 - 1,
                            mousePos(event) % 10 - 1, MyFont));
                        turns++;
                        positions_covered.push_back(mousePos(event));
                    }


                }
                else
                {
                    if (turns % 2 == 1)
                    {
                        crosses.push_back(cross(random / 10 - 1,
                            random % 10 - 1, MyFont));
                        turns++;
                        positions_covered.push_back(random);
                    }
                }

            }
        }
        else
        {
            sleep(seconds(1));
            circles.clear();
            crosses.clear();
            positions_covered.clear();
        }



        window.clear(Color::Black);
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                grid.setPosition(sf::Vector2f(150 * i, 150 * j));
                window.draw(grid);
            }
        }

      

        for (int i = 0; i < circles.size(); i++)
        {
            window.draw(circles.at(i));
        }

        for (int i = 0; i < crosses.size(); i++)
        {
            window.draw(crosses.at(i));
        }

       
        window.display();
    }

    return 0;
}

