#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "login.h"

using namespace std;
using namespace sf;

extern bool hasLoggedIn;
extern bool backUpFound;
bool isPlaying = false;
extern bool restored;

Texture backgroundTexture("./Assets/Orionis_Premium_HiRes_Fixed.png");
Texture playT("./Assets/gptButton1.png");
Texture leadT("./Assets/gptButton2.png");
Texture customT("./Assets/gptButton3.png");
Sprite bgSprite(backgroundTexture);
RectangleShape play({337.0, 68.0});
RectangleShape leaderBoards({337.0, 68.0});
RectangleShape customize({337.0, 68.0});

void mainMenu_Initial(RenderWindow &Window)
{

    //  Setting Background

    Vector2u bgTextureSize = backgroundTexture.getSize();
    // bgSprite.setTextureRect(IntRect({0,0} , {2000,700}));
    Vector2u windowSize = Window.getSize();
    float scaleX = (float)windowSize.x / bgTextureSize.x;
    float scaleY = (float)windowSize.y / bgTextureSize.y;
    bgSprite.setScale({scaleX, scaleY});

    // Working on the buttons ( the rectanglems )
    play.setFillColor(Color(0, 0, 0,0));
    leaderBoards.setFillColor(Color(0, 0, 0 ,0));
    customize.setFillColor(Color(0, 0, 0));

    play.setPosition({331.0, 218.0});
    leaderBoards.setPosition({331.0, 316.0});
    customize.setPosition({331.0, 412.0});


    // play.setOutlineColor(Color(255,255,255));
    // play.setOutlineThickness(5);
}

int mainMenuEventHandler(RenderWindow &window, Event &event, int switcher)
{
    if (!hasLoggedIn)
    {
        loginEventHandler(window, event);
        loginHoverHandler(window);
        return 40;
    }

    // if(const auto key = event.getIf<Event::KeyPressed>()){
    //     if(key->code == Keyboard::Key::A){
    //         play.move({-1,0});
    //         cerr<<play.getPosition().x<<" , "<<play.getPosition().y<<endl;
    //     }
    //     if(key->code == Keyboard::Key::D){
    //         play.move({1,0});
    //         cerr<<play.getPosition().x<<" , "<<play.getPosition().y<<endl;

    //     }
    //     if(key->code == Keyboard::Key::S){
    //         play.move({0,1});
    //         cerr<<play.getPosition().x<<" , "<<play.getPosition().y<<endl;

    //     }
    //     if(key->code == Keyboard::Key::W){
    //         play.move({0,-1});
    //         cerr<<play.getPosition().x<<" , "<<play.getPosition().y<<endl;
    //     }
    //     if(key->code == Keyboard::Key::Up){
    //         play.setSize({play.getGlobalBounds().size.x  , play.getGlobalBounds().size.y-1});
    //         cerr<<"Size : "<< play.getGlobalBounds().size.x <<" , "<<play.getGlobalBounds().size.y<<endl;
    //     }
    //     if(key->code == Keyboard::Key::Down){
    //         play.setSize({play.getGlobalBounds().size.x  , play.getGlobalBounds().size.y+1});
    //         cerr<<"Size : "<< play.getGlobalBounds().size.x <<" , "<<play.getGlobalBounds().size.y<<endl;

    //     }
    //     if(key->code == Keyboard::Key::Left){
    //         play.setSize({play.getGlobalBounds().size.x-1  , play.getGlobalBounds().size.y});
    //         cerr<<"Size : "<< play.getGlobalBounds().size.x <<" , "<<play.getGlobalBounds().size.y<<endl;

    //     }
    //     if(key->code == Keyboard::Key::Right){
    //         play.setSize({play.getGlobalBounds().size.x+1  , play.getGlobalBounds().size.y});
    //         cerr<<"Size : "<< play.getGlobalBounds().size.x <<" , "<<play.getGlobalBounds().size.y<<endl;

    //     }
    // }

    Vector2i mousePixel = Mouse::getPosition(window);
    Vector2f mouse(static_cast<float>(mousePixel.x),
                   static_cast<float>(mousePixel.y));

    if (play.getGlobalBounds().contains(mouse))
        play.setFillColor(Color(29, 58, 105 , 50)); // hover color
    else if (!(play.getGlobalBounds().contains(mouse)))
        play.setFillColor(Color(0, 0, 0 ,0)); // normal color

    if (leaderBoards.getGlobalBounds().contains(mouse))
        leaderBoards.setFillColor(Color(29, 58, 105 , 50));
    else if (!(leaderBoards.getGlobalBounds().contains(mouse)))
        leaderBoards.setFillColor(Color(0, 0, 0 ,0));

    if (customize.getGlobalBounds().contains(mouse))
        customize.setFillColor(Color(29, 58, 105 , 50));
    else if (!(customize.getGlobalBounds().contains(mouse)))
        customize.setFillColor(Color(0, 0, 0 , 0));



    if (const auto mouseButtonEvent = event.getIf<Event::MouseButtonPressed>())
    {

        if (mouseButtonEvent->button == Mouse::Button::Left)
        {
            Vector2f mousePos = {(float)(Mouse::getPosition(window).x), (float)(Mouse::getPosition(window).y)};
            if (play.getGlobalBounds().contains(mousePos) && switcher == 0)
            {
                cerr<<"Clicked Play...\n";
                isPlaying = true;
                if(backUpFound){
                    if(!restored){
                        return 5;
                    }
                    else{
                        return 10;
                    }
                }
                else{
                    cerr<<"Backup Not Found....\n";
                    return 10;
                }
            }
            else if (leaderBoards.getGlobalBounds().contains(mousePos) && switcher == 0)
            {
                return 20;
            }
            else if (customize.getGlobalBounds().contains(mousePos) && switcher == 0)
            {
                return 30;
            }
        }
    }
    return 40;
}

void WindowDrawer(RenderWindow &Window)
{
    Window.draw(bgSprite);
    // Window.draw(blurRect);
    Window.draw(play);
    Window.draw(leaderBoards);
    Window.draw(customize);
    if (!hasLoggedIn)
    {
        loginDrawer(Window);
    }
}
