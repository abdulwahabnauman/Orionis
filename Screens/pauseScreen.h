#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int switcher = 0; // VVIP;

extern Texture resumeTexture;
extern Texture pauseTexture;
extern Sprite pauseButton;
extern bool gamePaused;
extern Clock timeElapsedInGame; // Declared in gamePlay.h;


float stoppedAt =0;


Texture pauseScreenBGTex("./Assets/pauseScreenBackground.png");
Sprite bgRect(pauseScreenBGTex);
Texture menuButtonTexture("./Assets/homeTexture.png");
Sprite menuButtonSprite(menuButtonTexture);
Texture quitButtonTexture("./Assets/crossTexture.png");
Sprite quitButtonSprite(quitButtonTexture);
// Sprite ResumeButtonSprite;


void pauseScreen_Initial(RenderWindow &Window)
{
    bgRect.setPosition({10 , 90});
    bgRect.setScale({0.3 ,0.4});

    menuButtonSprite.setPosition({10, 95});
    menuButtonSprite.setTextureRect(IntRect({158, 42}, {184, 188}));
    menuButtonSprite.setScale({0.3, 0.3});

    quitButtonSprite.setPosition({95,  15});
    quitButtonSprite.setTextureRect(IntRect({158, 42}, {184, 188}));
    quitButtonSprite.setScale({0.3, 0.3});
}

void pauseScreen_EventHandler(RenderWindow &window, Event &event)
{
    if (Mouse::isButtonPressed(Mouse::Button::Left))
    {
        Vector2f mousePositionForPP = {(float)(Mouse::getPosition(window).x),
                                       (float)(Mouse::getPosition(window).y)};

        if (quitButtonSprite.getGlobalBounds().contains(mousePositionForPP))
        {
            gamePaused = false;
            window.close();
        }

        else if (menuButtonSprite.getGlobalBounds().contains(mousePositionForPP))
        {

            switcher = 0;
            gamePaused = true;
            cerr<<switcher;
        }
        else if(pauseButton.getGlobalBounds().contains(mousePositionForPP)){
            if(gamePaused){
                gamePaused = false;
                timeElapsedInGame.restart();
                pauseButton.setTexture(pauseTexture);

            }
            else{
                gamePaused = true;
                pauseButton.setTexture(resumeTexture);
            }
        }
    }
    else if (Keyboard::isKeyPressed(Keyboard::Scan::P))
    {
        if(gamePaused){
            gamePaused = false;
        }
        else{
            gamePaused = true;
        }
    }
}

void pauseScreen_Drawer(RenderWindow &pauseWindow)
{


    // pauseWindow.draw(bgRect);
    pauseWindow.draw(menuButtonSprite);
    pauseWindow.draw(quitButtonSprite);
    // pauseWindow.draw(ResumeButtonSprite);
    // pauseWindow.draw(MainMenuButtonSprite);


}