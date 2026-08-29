#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
#include <string>
#include<optional>
#include<cstring>
#include "dataSaver.h"


bool hasLoggedIn = false;
bool backUpFound = false;
int backUpIndex = 0;
char currentPlayer[30] = "";

Texture backgroundTexture2("./Assets/background.jpeg");
Sprite backgroundSpriteLG(backgroundTexture2);

RectangleShape loginbox(Vector2f(500, 400));

Texture boxTexture("./Assets/settingsBackground.png");

Font font2("./Fonts/settingsfont.ttf");
Text title(font2);
Text sub(font2);

RectangleShape InputBox(Vector2f(430, 40));

Text name(font2);

string userInput;
Clock cursorClock;

RectangleShape cursor(Vector2f(2, 28));

RectangleShape button(Vector2f(100, 80));

Text buttontext(font2);

bool showCursor = true;
bool boxActive = false;
int maxNameCharacters = 30;


void login_Initial(RenderWindow& window) {

    // Background scaling (kept same, just cleaner)
    FloatRect bounds = backgroundSpriteLG.getLocalBounds();
    backgroundSpriteLG.setScale({
        (float)window.getSize().x / bounds.size.x,
        (float)window.getSize().y / bounds.size.y}
    );


    loginbox.setSize({ 520.f, 420.f });
    loginbox.setPosition({ 240.f, 140.f });
    loginbox.setFillColor(Color(255, 255, 255, 200)); // soft glass
    loginbox.setOutlineColor(Color(180, 120, 255, 180));
    loginbox.setOutlineThickness(4);
    loginbox.setTexture(&boxTexture);

    title.setString("LOGIN");
    title.setCharacterSize(80);
    title.setFillColor(Color(240, 225, 255));
    title.setOutlineThickness(3);
    title.setOutlineColor(Color(60, 30, 120));
    title.setPosition({ 360.f, 150.f });


    sub.setString("NAME:");
    sub.setCharacterSize(42);
    sub.setFillColor(Color(230, 225, 255));
    sub.setOutlineThickness(2);
    sub.setOutlineColor(Color(80, 40, 150));
    sub.setPosition({ 280.f, 290.f });


    InputBox.setSize({ 440, 50 });
    InputBox.setPosition({ 280.f, 350.f });
    InputBox.setFillColor(Color(245, 245, 255));
    InputBox.setOutlineColor(Color(120, 80, 200));
    InputBox.setOutlineThickness(3);


    name.setFont(font2);
    name.setCharacterSize(30);
    name.setFillColor(Color(40, 0, 70));
    name.setPosition({ 295.f, 357.f });


    cursor.setSize({ 3, 34 });
    cursor.setFillColor(Color(60, 20, 120));   // softer purple tone


    button.setSize({ 180, 80 });
    button.setPosition({ 420.f, 430.f });
    button.setFillColor(Color(155, 90, 230));
    button.setOutlineColor(Color::White);
    button.setOutlineThickness(4);

    buttontext.setString("GO!");
    buttontext.setCharacterSize(48);
    buttontext.setFillColor(Color::White);
    buttontext.setOutlineThickness(3);
    buttontext.setOutlineColor(Color(30, 20, 60));
    buttontext.setPosition({ 450.f, 440.f });
}

void loginEventHandler(RenderWindow& window, Event& event)
{
  
   if (const auto mouseEvent = event.getIf<Event::MouseButtonPressed>())
   {
       if (mouseEvent->button == Mouse::Button::Left)
       {
           Vector2f mouse(Mouse::getPosition(window));

           
           boxActive = InputBox.getGlobalBounds().contains(mouse);

           
           if (button.getGlobalBounds().contains(mouse))
           {

            if(!userInput.empty()){
                strcpy(currentPlayer, userInput.c_str());
                userInput.clear();
                hasLoggedIn = true;
                backUpIndex = nameSearch(currentPlayer);
                if(backUpIndex != -1){
                    backUpFound = true;
                }
                else{
                    cerr<<"No Backup found for the user "<<currentPlayer<<endl;
                }
            }
            //    return 10;   // OPTIONAL ? return page code like your example
           }
       }
   }
   if(const auto textEntered = event.getIf<Event::TextEntered>())
   {
       if (boxActive)
       {
           uint32_t unicode = textEntered->unicode;

           if (unicode == 8) // backspace
           {
               if (!userInput.empty())
                   userInput.pop_back();
           }
           else if (unicode >= 32 && unicode <= 126)
           {
               if (userInput.size() < maxNameCharacters)
                   userInput += static_cast<char>(unicode);
           }
       }
   }

}

void loginHoverHandler(RenderWindow& window) {
    Vector2i mousePixel = Mouse::getPosition(window);
    Vector2f mouse(mousePixel.x, mousePixel.y);

    if (button.getGlobalBounds().contains(mouse))
        button.setFillColor(Color(175, 110, 255));
    else
        button.setFillColor(Color(155, 90, 230));

    if (InputBox.getGlobalBounds().contains(mouse))
        InputBox.setFillColor(Color(255, 255, 255));
    else
        InputBox.setFillColor(Color(245, 245, 255));
}

void loginCursorUpdate(){
   if (boxActive && showCursor)
   {
       float cursorX = name.findCharacterPos(userInput.size()).x;
       cursor.setPosition(Vector2f{ cursorX,name.getPosition().y });


   }
   else
       name.setString(userInput);
   if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
       showCursor = !showCursor;
       cursorClock.restart();
   }
}


void loginDrawer(RenderWindow& window) {

    // window.draw(backgroundSpriteLG);

    window.draw(loginbox);
    window.draw(title);
    window.draw(sub);
    window.draw(InputBox);
    window.draw(name);
    window.draw(button);
    window.draw(buttontext);

    if (showCursor && boxActive)
        window.draw(cursor);

    loginCursorUpdate();
    window.display();
}

