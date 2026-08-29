#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;


bool gameOver = false;
extern bool isItOver; 
extern int switcher;
extern bool isPlaying;

// ALl Variables that are to be resetted in the great reset ( ---- From gamePlay.h  ---- );

extern bool gamePaused;
extern float bgScollSpeed;
extern RectangleShape bulletMagazine[];
extern int maxBullets;
extern RectangleShape enemyBullets[];
extern int maxEnemyBullets;
extern RectangleShape maxEnemies[];
extern int maxEnemiesNumber;
extern int waveLevel;
extern int focusedSpaceship;
extern RectangleShape spaceShip;
extern RectangleShape spaceShip2;

extern int playerScore;

extern RectangleShape hearts[];
extern int maxHearts;
extern bool heartsActive[];

extern Clock timeElapsedInGame; // The timer that Resets the waves;
extern Text scoreText;

// ALl Variables that are to be resetted in the great reset ( ---- From gamePlay.h  ---- );

extern bool jumped[];

// -------------------

RectangleShape GOrect(Vector2f(450, 300));
RectangleShape GOshadow(Vector2f(470, 320));

RectangleShape playAgainButton({260, 70});
RectangleShape backToMenuButton({260, 70});

Font gameOverFont;
Text playText(gameOverFont);
Text backToMenuText(gameOverFont);
Text titleText(gameOverFont);
Text scoreTextGO(gameOverFont);

void gameOverInitializer(RenderWindow &window)
{
    float W = window.getSize().x;
    float H = window.getSize().y;

    GOshadow.setSize({560, 420});
    GOshadow.setFillColor(Color(0, 10, 30, 160));
    GOshadow.setPosition({(W - 560) / 2, (H - 420) / 2});

    GOrect.setSize({540, 400});
    GOrect.setFillColor(Color(15, 20, 35, 210));
    GOrect.setOutlineThickness(3);
    GOrect.setOutlineColor(Color(0, 200, 255, 120));
    GOrect.setPosition({(W - 540) / 2, (H - 400) / 2});

    if (!gameOverFont.openFromFile("./Fonts/scorefont.ttf")){
        cerr << "Unable to load font\n";
    }

    titleText.setString("GAME OVER");
    titleText.setCharacterSize(54);
    titleText.setFillColor(Color(255, 255, 255, 240));
    titleText.setLetterSpacing(2.5);
    titleText.setPosition({W / 2 - titleText.getLocalBounds().size.x / 2,
                           GOrect.getPosition().y + 30});


    scoreTextGO.setString("SCORE : 9999");
    scoreTextGO.setCharacterSize(40);
    scoreTextGO.setFillColor(Color(0, 200, 255, 230));
    scoreTextGO.setLetterSpacing(2);
    scoreTextGO.setPosition({W / 2 - scoreTextGO.getLocalBounds().size.x / 2 + 15,
                             titleText.getPosition().y + 90});


    playAgainButton.setSize({330, 78});
    backToMenuButton.setSize({330, 78});

    playAgainButton.setFillColor(Color(33, 40, 64, 160));
    backToMenuButton.setFillColor(Color(33, 40, 64, 160));

    playAgainButton.setPosition({W / 2 - 165, scoreTextGO.getPosition().y + 70});
    backToMenuButton.setPosition({W / 2 - 165, playAgainButton.getPosition().y + 95});

    playText.setString("PLAY AGAIN");
    playText.setCharacterSize(34);
    playText.setFillColor(Color::White);
    playText.setLetterSpacing(1.5);
    playText.setPosition({playAgainButton.getPosition().x + (playAgainButton.getSize().x - playText.getLocalBounds().size.x) / 2,
                          playAgainButton.getPosition().y + 20});

    backToMenuText.setString("MAIN MENU");
    backToMenuText.setCharacterSize(34);
    backToMenuText.setFillColor(Color::White);
    backToMenuText.setLetterSpacing(1.5);
    backToMenuText.setPosition({backToMenuButton.getPosition().x + (backToMenuButton.getSize().x - backToMenuText.getLocalBounds().size.x) / 2,
                                backToMenuButton.getPosition().y + 20});
}

void theGreatReset()
{
    //  Resetting the gamePlay.h Variables;
    gamePaused = false;
    isItOver = false;
    bgScollSpeed = 1.0;
    waveLevel = 1;
    focusedSpaceship = 'a';
    playerScore = 0;
    scoreText.setString("-");
    timeElapsedInGame.restart();
    maxHearts = 10;
    spaceShip.setSize({90.0,100});
    spaceShip2.setSize({90.0,100});

    for (int i = 0; i < maxBullets; i++)
    {
        bulletMagazine[i].setSize({0.0f, 0.0f});
        bulletMagazine[i].setPosition({0.0f, -299});
    }

    for (int i = 0; i < maxEnemyBullets; i++)
    {
        enemyBullets[i].setSize({0.0f, 0.0f});
        enemyBullets[i].setPosition({0.0f, -299});
    }

    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        maxEnemies[i].setSize({0.0f, 0.0f});
        maxEnemies[i].setPosition({0.0f, -299});
    }
    for (int i = 0; i < maxHearts; i++)
    {
        heartsActive[i] = true;
    }

    //
    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        jumped[i] = false;
    }
}

void gameOverEventHandler(RenderWindow &window, Event &event)
{

    Vector2i mousePixelGO = Mouse::getPosition(window);
    Vector2f mouseGO(static_cast<float>(mousePixelGO.x),
                   static_cast<float>(mousePixelGO.y));

    if (backToMenuButton.getGlobalBounds().contains(mouseGO))
        backToMenuButton.setFillColor(Color(11, 14, 23 , 160)); // hover color
    else if (!(backToMenuButton.getGlobalBounds().contains(mouseGO)))
        backToMenuButton.setFillColor(Color(33, 40, 64, 160));

    if (playAgainButton.getGlobalBounds().contains(mouseGO))
        playAgainButton.setFillColor(Color(11, 14, 23 , 160)); // hover color
    else if (!(playAgainButton.getGlobalBounds().contains(mouseGO)))
        playAgainButton.setFillColor(Color(33, 40, 64, 160));

    if (auto mouseButton = event.getIf<Event::MouseButtonPressed>())
    {

        if (mouseButton->button == Mouse::Button::Left)
        {
            Vector2f mousePositionForGOver = {(float)(Mouse::getPosition(window).x), (float)(Mouse::getPosition(window).y)};

            // cerr<<"Mouse Was clicked";
            if (playAgainButton.getGlobalBounds().contains(mousePositionForGOver))
            {
                theGreatReset();
                isPlaying = true;
                gameOver = false;
            }
            else if (backToMenuButton.getGlobalBounds().contains(mousePositionForGOver))
            {
                theGreatReset();
                switcher = 0;
                isPlaying = false;
                gameOver = false;
            }
        }
    }
}

void gameOverDrawer(RenderWindow &window)
{
    window.draw(GOshadow);
    window.draw(GOrect);

    window.draw(titleText);
    window.draw(scoreTextGO);

    window.draw(playAgainButton);
    window.draw(backToMenuButton);

    window.draw(playText);
    window.draw(backToMenuText);
}
