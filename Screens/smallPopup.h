#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

extern int switcher;
extern int backUpIndex;

bool restored = false;

RectangleShape popupBG({450, 300});
RectangleShape popupShadow({470, 320});
RectangleShape btn1({300, 70});
Font myFont;
RectangleShape btn2({300, 70});
Text btn1Text(myFont);
Text btn2Text(myFont);
Text popupTitle(myFont);

void popUp_Initializer(RenderWindow &window)
{
    if (!myFont.openFromFile("./Fonts/scorefont.ttf"))
    {
        cout << "Yo";
    }

    float winWidth = 1000;
    float winHeight = 700;

    float W = window.getSize().x;
    float H = window.getSize().y;

    popupShadow.setSize({560, 420});
    popupShadow.setFillColor(Color(0, 10, 30, 160));
    popupShadow.setPosition({(W - 560) / 2, (H - 420) / 2});

    popupBG.setSize({540, 400});
    popupBG.setFillColor(Color(15, 20, 35, 235));
    popupBG.setOutlineThickness(3);
    popupBG.setOutlineColor(Color(0, 200, 255, 120));
    popupBG.setPosition({(W - 540) / 2, (H - 400) / 2});
    Vector2f buttonPositions = {popupBG.getPosition().x + 75, popupBG.getPosition().y + 100};

    popupTitle.setString("Unfinished Game Found");
    popupTitle.setCharacterSize(32);
    popupTitle.setFillColor(Color(255, 255, 255));
    popupTitle.setLetterSpacing(2);
    popupTitle.setPosition({popupBG.getPosition().x + (popupBG.getSize().x - popupTitle.getLocalBounds().size.x) / 2,
                            popupBG.getPosition().y + 20});

    btn1.setFillColor(Color(100, 100, 250));
    btn1.setPosition({popupBG.getPosition().x + (popupBG.getSize().x - btn1.getSize().x) / 2,
                      popupBG.getPosition().y + 140});

    btn1Text.setFont(myFont);
    btn1Text.setString("Restore");
    btn1Text.setCharacterSize(24);
    btn1Text.setFillColor(Color::White);
    btn1Text.setPosition({btn1.getPosition().x + (btn1.getSize().x - btn1Text.getLocalBounds().size.x) / 2,
                          btn1.getPosition().y + (btn1.getSize().y - btn1Text.getCharacterSize()) / 2});

    btn2.setFillColor(Color(245, 54, 54));
    btn2.setPosition({popupBG.getPosition().x + (popupBG.getSize().x - btn2.getSize().x) / 2,
                      btn1.getPosition().y + btn1.getSize().y + 20});

    btn2Text.setFont(myFont);
    btn2Text.setString("Discard");
    btn2Text.setCharacterSize(24);
    btn2Text.setFillColor(Color::White);
    btn2Text.setPosition({btn2.getPosition().x + (btn2.getSize().x - btn2Text.getLocalBounds().size.x) / 2,
                          btn2.getPosition().y + (btn2.getSize().y - btn2Text.getCharacterSize()) / 2});
}

void popupEventHandler(RenderWindow &window, Event &event)
{
    if (auto mousePressed = event.getIf<Event::MouseButtonPressed>())
    {
        if (mousePressed->button == Mouse::Button::Left)
        {

            Vector2i mousePosPopup = Mouse::getPosition(window);
            Vector2f mousePosLocal(static_cast<float>(mousePosPopup.x),
                                   static_cast<float>(mousePosPopup.y));

            if (btn1.getGlobalBounds().contains(mousePosLocal))
            {
                loadBackedUpGame(backUpIndex);
                clearBackupAfterLoading(backUpIndex);
                restored = true;
                switcher = 10;
            }
            else if (btn2.getGlobalBounds().contains(mousePosLocal))
            {
                restored = true;
                clearBackupAfterLoading(backUpIndex);
                switcher = 10;
            }
        }
    }

    Vector2i mousePos = Mouse::getPosition(window);
    Vector2f mouseFloat(static_cast<float>(mousePos.x),
                   static_cast<float>(mousePos.y));

    if(btn1.getGlobalBounds().contains(mouseFloat))
    {
        btn1.setFillColor(Color(47, 47, 150)); // hover color
        btn1.setOutlineColor(Color(255, 255, 255));
        btn1.setOutlineThickness(0.7);   
    }
    else if (!(btn1.getGlobalBounds().contains(mouseFloat)))
    {
        btn1.setFillColor(Color(100 , 100, 250));
        btn1.setOutlineThickness(0);
    }

    if (btn2.getGlobalBounds().contains(mouseFloat))
    {   
        btn2.setFillColor(Color(176, 42, 42)); // hover color
        btn2.setOutlineColor(Color(255, 255, 255));
        btn2.setOutlineThickness(0.7); 
    }
    else if (!(btn2.getGlobalBounds().contains(mouseFloat)))
    {
        btn2.setFillColor(Color(245,54,54));
        btn2.setOutlineThickness(0); 
    }
}

void popupDrawer(RenderWindow &window)
{
    window.draw(popupBG);
    window.draw(btn1);
    window.draw(btn1Text);
    window.draw(btn2);
    window.draw(btn2Text);
    window.draw(popupTitle);
}