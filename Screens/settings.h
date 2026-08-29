#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

extern int switcher; // VVIP                    <<----------
extern Texture starField;
extern Sprite copy1;
extern Sprite copy2;
extern Sprite spaceshipSprite;
extern Sprite spaceshipSprite2;

Texture backgroundTexture1("./Assets/settingBG.png");
// Sprite for background picture
Sprite backgroundSpriteST(backgroundTexture1);
RectangleShape goBackBtn({139, 43});

// Get the local bounds
Font font("./Fonts/scorefont.ttf");
Text heading(font);
Text subheading(font);
Text word(font);

const int ShipCount = 5;
float spaceshipWidth = 90.f;   // changespaceship width
float spaceshipHeight = 100.f; // changespaceship height
Texture spaceshipTexture1("./Assets/allspaceships.png");
Sprite spaceshipspriteST(spaceshipTexture1);
int selectedShip = 0;

RectangleShape SettingsSpaceShip[5];
int eachspaceshipSpriteWidth = 92;   // 368/4
int eachspaceshipSpriteHeight = 122; // 368/3
int spaceshipXindex = 3;             // Horizontally make chanhes to change ship
int spaceshipYindex = 1;             // Vertically make chanhes to change ship
float scaleFactorX = spaceshipWidth / eachspaceshipSpriteWidth;
float scaleFactorY = spaceshipHeight / eachspaceshipSpriteHeight;

int selectedbg = -1;

Texture bgTex1("./Assets/starfield.png");
Texture bgTex2("./Assets/starfieldV2.png");
Texture bgTex3("./Assets/startfieldV3.png");
Texture bgTex4("./Assets/starfieldV4.png");
Texture bgTex5("./Assets/bgsample7.jpeg");

sf::Sprite bg1s(bgTex1);
sf::Sprite bg2s(bgTex2);
sf::Sprite bg3s(bgTex3);
sf::Sprite bg4s(bgTex4);
sf::Sprite bg5s(bgTex5);

RectangleShape bgBorder[5]; // selection border for backgrounds

void settings_Initializer(RenderWindow &window)
{

    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;
    FloatRect bounds = backgroundSpriteST.getLocalBounds();
    float scaleX = windowWidth / bounds.size.x;
    float scaleY = windowHeight / bounds.size.y;

    backgroundSpriteST.setScale(Vector2f(scaleX, scaleY));
    // backgroundSprite.setPosition({0.0 , 0.0});
    goBackBtn.setPosition({815, 34});
    goBackBtn.setFillColor(Color(0, 0, 0, 0));

    // // Size for small preview
    bg1s.setScale(Vector2f(125.f / bgTex1.getSize().x, 105.f / bgTex1.getSize().y));
    bg2s.setScale(Vector2f(125.f / bgTex2.getSize().x, 105.f / bgTex2.getSize().y));
    bg3s.setScale(Vector2f(125.f / bgTex3.getSize().x, 105.f / bgTex3.getSize().y));
    bg4s.setScale(Vector2f(125.f / bgTex4.getSize().x, 105.f / bgTex4.getSize().y));
    bg5s.setScale(Vector2f(125.f / bgTex5.getSize().x, 105.f / bgTex5.getSize().y));

    // Position in grid
    bg1s.setPosition(Vector2f(130, 500));
    bg2s.setPosition(Vector2f(280, 500));
    bg3s.setPosition(Vector2f(430, 500));
    bg4s.setPosition(Vector2f(580, 500));
    bg5s.setPosition(Vector2f(730, 500));

    heading.setString("SETTINGS");
    heading.setCharacterSize(80);
    heading.setFillColor(sf::Color(230, 230, 230));
    heading.setPosition({280.f, 80.f});

    subheading.setString("SHIPS");
    subheading.setCharacterSize(40);
    subheading.setFillColor(sf::Color(230, 230, 230));
    subheading.setPosition({(window.getSize().x - subheading.getGlobalBounds().size.x) / 2, 170.f});

    word.setString("BACKGROUND");
    word.setCharacterSize(39);
    word.setFillColor(sf::Color(230, 230, 230));
    word.setPosition({(window.getSize().x - word.getGlobalBounds().size.x) / 2, 400.f});

    int rectX = spaceshipXindex * eachspaceshipSpriteWidth;
    int rectY = spaceshipYindex * eachspaceshipSpriteHeight;

    for (int i = 0; i < ShipCount; i++)
    {
        int rectX = spaceshipXindex * eachspaceshipSpriteWidth;
        int rectY = spaceshipYindex * eachspaceshipSpriteHeight;

        SettingsSpaceShip[i].setSize(Vector2f(spaceshipWidth, spaceshipHeight));
        SettingsSpaceShip[i].setScale(Vector2f{scaleFactorX, scaleFactorY});
        SettingsSpaceShip[i].setTexture(&spaceshipTexture1);
        SettingsSpaceShip[i].setTextureRect(IntRect(Vector2i(rectX, rectY), Vector2i(eachspaceshipSpriteWidth, eachspaceshipSpriteHeight)));
        SettingsSpaceShip[i].setPosition(Vector2f((170.f + i * 140.f), 240.f)); // spread enemies horizontally
        // change enemies Total 5 are available in sprite

        if (spaceshipXindex == 3 && spaceshipXindex != 2)
        {
            spaceshipYindex++;
            spaceshipXindex = -1;
        }
        spaceshipXindex++;
        float scaleFactorX = spaceshipWidth / eachspaceshipSpriteWidth;
        float scaleFactorY = spaceshipHeight / eachspaceshipSpriteHeight;
    }

    int n = 0;

    for (int i = 0; i < 5; i++)
    {
        bgBorder[i].setSize({130.f, 110.f});
        bgBorder[i].setFillColor(Color::Transparent);
        bgBorder[i].setOutlineThickness(3);
        bgBorder[i].setOutlineColor(Color::White);
    }

    // Match with each sprite
    bgBorder[0].setPosition(bg1s.getPosition());
    bgBorder[1].setPosition(bg2s.getPosition());
    bgBorder[2].setPosition(bg3s.getPosition());
    bgBorder[3].setPosition(bg4s.getPosition());
    bgBorder[4].setPosition(bg5s.getPosition());
}

void settingsEventHandler(RenderWindow &window, Event &event)
{
    Vector2i mousePixelSettings = Mouse::getPosition(window);
    Vector2f mouseST(static_cast<float>(mousePixelSettings.x),
                     static_cast<float>(mousePixelSettings.y));

    if (goBackBtn.getGlobalBounds().contains(mouseST))
        goBackBtn.setFillColor(Color(29, 58, 105, 50));
    else if (!(goBackBtn.getGlobalBounds().contains(mouseST)))
        goBackBtn.setFillColor(Color(0, 0, 0, 0));

    if (const auto mouseEvent = event.getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseEvent->button == sf::Mouse::Button::Left)
        {
            Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
            for (int i = 0; i < ShipCount; i++)
            {
                if (SettingsSpaceShip[i].getGlobalBounds().contains(mousePos))
                {
                    const int eachSpacespaceshipSpriteWidth = 92;   // 368/4
                    const int eachSpacespaceshipSpriteHeight = 122; // 368/3
                    int spaceshipXindexFORGAMEPLAY = 2;             // Horizontally make changes to change ship
                    int spaceshipYindexFORGAMEPLAY = 2;             // Vertically make changes to change ship
                    selectedShip = i;
                    int x = selectedShip;
                    cerr << x << endl;
                    switch (x)
                    {
                    case 0:
                    {
                        spaceshipXindexFORGAMEPLAY = 2;
                        spaceshipYindexFORGAMEPLAY = 1;
                        break;
                    }
                    case 1:
                    {
                        spaceshipXindexFORGAMEPLAY = 0;
                        spaceshipYindexFORGAMEPLAY = 2;
                        break;
                    }
                    case 2:
                    {
                        spaceshipXindexFORGAMEPLAY = 1;
                        spaceshipYindexFORGAMEPLAY = 2;
                        break;
                    }
                    case 3:
                    {
                        spaceshipXindexFORGAMEPLAY = 2;
                        spaceshipYindexFORGAMEPLAY = 2;
                        break;
                    }
                    case 4:
                    {
                        spaceshipXindexFORGAMEPLAY = 3;
                        spaceshipYindexFORGAMEPLAY = 2;
                        break;
                    }

                    default:
                        break;
                    }
                    int rectX = spaceshipXindexFORGAMEPLAY * eachSpacespaceshipSpriteWidth;
                    int rectY = spaceshipYindexFORGAMEPLAY * eachSpacespaceshipSpriteHeight;
                    spaceshipSprite.setTextureRect(IntRect(Vector2i(rectX, rectY), Vector2i(eachSpacespaceshipSpriteWidth, eachSpacespaceshipSpriteHeight)));
                    spaceshipSprite2.setTextureRect(IntRect(Vector2i(rectX, rectY), Vector2i(eachSpacespaceshipSpriteWidth, eachSpacespaceshipSpriteHeight)));

                    for (int j = 0; j < ShipCount; j++)
                    {
                        SettingsSpaceShip[j].setOutlineThickness(0.f); // no border
                        SettingsSpaceShip[j].setOutlineColor(Color::Transparent);
                    }

                    SettingsSpaceShip[i].setOutlineThickness(4.f);
                    SettingsSpaceShip[i].setOutlineColor(Color::Cyan);
                }
                if (goBackBtn.getGlobalBounds().contains(mousePos))
                {
                    switcher = 0;
                }
            }

            Sprite *bgArr[5] = {&bg1s, &bg2s, &bg3s, &bg4s, &bg5s};
            RectangleShape bgBox[5];
            for (int i = 0; i < 5; i++)
            {
                if (bgArr[i]->getGlobalBounds().contains(mousePos)) // clicked background
                {
                    selectedbg = i;
                    int y = selectedbg;
                    bool succesfull = false;
                    if (y == 0)
                    {
                        if (starField.loadFromFile("./Assets/starfield.png"))
                            succesfull = true;
                    }
                    else if (y == 1)
                    {
                        if (starField.loadFromFile("./Assets/starfieldV2.png"))
                            succesfull = true;
                    }
                    else if (y == 2)
                    {
                        if (starField.loadFromFile("./Assets/starfieldV3.png"))
                            succesfull = true;
                    }
                    else if (y == 3)
                    {
                        if (starField.loadFromFile("./Assets/starfieldV4.png"))
                            succesfull = true;
                    }
                    else if (y == 4)
                    {
                        if (starField.loadFromFile("./Assets/bgsample7.jpeg"))
                            succesfull = true;
                    }

                    copy1.setTexture(starField);
                    copy2.setTexture(starField);

                    FloatRect sfBounds = copy1.getLocalBounds();
                    float scaleX = window.getSize().x / sfBounds.size.x;

                    // copy1.setScale({scaleX, 1});
                    // copy2.setScale({scaleX, 1});

                    for (int j = 0; j < 5; j++)
                        bgBorder[j].setOutlineColor(Color::White);

                    bgBorder[i].setOutlineColor(Color::Cyan);
                }
            }
        }
    }
    else if (auto key = event.getIf<Event::KeyPressed>())
    {
    }
}

int shipDecider()
{
    return selectedShip;
}
int bgDecider()
{
    return selectedbg;
}

void settingsDrawer(RenderWindow &window)
{
    // cerr<<"Hello";
    window.draw(backgroundSpriteST);
    // window.draw(heading);
    window.draw(subheading);
    window.draw(word);

    for (int i = 0; i < ShipCount; i++)
        window.draw(SettingsSpaceShip[i]);

    window.draw(bg1s);
    window.draw(bg2s);
    window.draw(bg3s);
    window.draw(bg4s);
    window.draw(bg5s);
    for (int i = 0; i < 5; i++)
        window.draw(bgBorder[i]);

    window.draw(goBackBtn);
}
