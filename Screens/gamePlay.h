#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "spawnFunctions.h"
#include "pauseScreen.h"
#include "gameOver.h"
#include <random>
#include "dataSaver.h"
#include "leaderBoards.h"

extern bool gameOver;   // VVIP         <<<-----------  Declared in gameOver.h
extern Text scoreTextGO;
Clock timeElapsedInGame;

random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> enemyBulletRand(5, 10);
using namespace std;
using namespace sf;

bool gamePaused = false;
float bgScollSpeed = 1.0;
float bulletSpeed = -5.0;
float enemyBulletSPeed = 1.5;

// Clock mainTimerForGamePlay;
RectangleShape spaceShip({90.0, 100.0});
RectangleShape spaceShip2({90.0, 100.0});
RectangleShape bulletMagazine[500];
RectangleShape maxEnemies[100];
RectangleShape enemyBullets[500];
Clock enemyShootTimer[100];
float enemyShootDelay[100] = {0};
float shootInterval = 900;
int maxEnemyBullets = 500;
int maxBullets = 500;
int maxEnemiesNumber = 100;
int waveLevel = 1;

int focusedSpaceship = 'a';
//  'a' means spaceShip  .  'b' means spaceship2;
Clock enemyShootClock;

// Wahab's Code .

Texture backgroundTextureGame("./Assets/Gemini_Generated_Image_xu5f95xu5f95xu5f.png");
Sprite backgroundSprite(backgroundTextureGame);
Texture spaceshipTexture("./Assets/allspaceships.png");
Sprite spaceshipSprite(spaceshipTexture);
Texture bulletTexture("./Assets/bullet.png");
Texture enemyBulletTexture("./Assets/enemyBullet.png");
RectangleShape hearts[10];
bool heartsActive[10];
int maxHearts = 10;


Texture heartTexture;
Texture starField("./Assets/starfield.png");
Sprite copy1(starField);
Sprite copy2(starField);
Clock bgMovementClock;

Font fontStyle;
Text scoreText(fontStyle);

int playerScore = 0;

const float heartWidth = 40.f; /*Both can be changed*/
const float heartHeight = 40.f;
const int eachHeartSpriteWidth = 50;
const int eachHeartSpriteHeight = 50;
int rectHX = eachHeartSpriteWidth;
int rectHY = eachHeartSpriteHeight;
float scaleFactorHX = heartWidth / eachHeartSpriteWidth;
float scaleFactorHY = heartHeight / eachHeartSpriteHeight;

int heartDisplayHelper = 20; // start for heart display

// Implementing the phase-through-walls feature

Sprite spaceshipSprite2(spaceshipTexture);

// ---------

Texture resumeTexture("./Assets/pauseTexture.png");
Texture pauseTexture("./Assets/resumeTexture.png");
Sprite pauseButton(pauseTexture);

void game_Initial(RenderWindow &window)
{
    pauseButton.setTexture(pauseTexture);
    pauseButton.setTextureRect(IntRect({158, 42}, {184, 188}));
    pauseButton.setScale({0.3, 0.3});
    pauseButton.setPosition({10, 15});

    spaceShip.setFillColor(Color(12, 93, 232));
    spaceShip.setPosition({455.0, 580.0});
    spaceShip2.setFillColor(Color(12, 93, 232));
    spaceShip2.setPosition({455.0 - 1000.0, 580.0});
    for (int i = 0; i < 500; i++)
    {
        bulletMagazine[i].setSize({0.0f, 0.0f});
        bulletMagazine[i].setTexture(&bulletTexture);
    }
    FloatRect sfBounds = copy1.getLocalBounds();
    float scaleX = window.getSize().x / sfBounds.size.x;
    copy1.setScale({scaleX, 1});
    copy2.setScale({scaleX, 1});
    copy2.setPosition({0, (sfBounds.size.y)});
    copy1.setPosition({0, 0});

    //  Wahab's Code -------

    // FloatRect bounds = backgroundSprite.getLocalBounds();
    // float scaleX = window.getSize().x / bounds.size.x;
    // float scaleY = window.getSize().y / bounds.size.y;
    // backgroundSprite.setScale(Vector2f(scaleX, scaleY));

    const int eachSpacespaceshipSpriteWidth = 92;   // 368/4
    const int eachSpacespaceshipSpriteHeight = 122; // 368/3
    int spaceshipXindex = 2;                        // Horizontally make changes to change ship
    int spaceshipYindex = 2;                        // Vertically make changes to change ship
    int rectX = spaceshipXindex * eachSpacespaceshipSpriteWidth;
    int rectY = spaceshipYindex * eachSpacespaceshipSpriteHeight;

    spaceshipSprite.setTextureRect(IntRect(Vector2i(rectX, rectY), Vector2i(eachSpacespaceshipSpriteWidth, eachSpacespaceshipSpriteHeight)));
    spaceshipSprite2.setTextureRect(IntRect(Vector2i(rectX, rectY), Vector2i(eachSpacespaceshipSpriteWidth, eachSpacespaceshipSpriteHeight)));

    float scaleFactorX = 90.f / eachSpacespaceshipSpriteWidth;
    float scaleFactorY = 100.f / eachSpacespaceshipSpriteHeight;

    spaceShip.setScale({scaleFactorX, scaleFactorY});
    spaceShip2.setScale({scaleFactorX, scaleFactorY});

    spaceshipSprite.setScale({scaleFactorX, scaleFactorY});
    spaceshipSprite2.setScale({scaleFactorX, scaleFactorY});

    spaceshipSprite.setPosition({455, 580});
    spaceshipSprite2.setPosition({455 - 1000, 580});

    // Wahab's Code for Hearts
    if (!heartTexture.loadFromFile("./Assets/heart.png"))
    {
        cerr << "Error: Could not load heart.png" << endl;
    }

    for (int k = 0; k < maxHearts; k++)
    {
        hearts[k].setSize(Vector2f(heartWidth, heartHeight));
        hearts[k].setScale(Vector2f{scaleFactorHX, scaleFactorHY});
        hearts[k].setTexture(&heartTexture);
        hearts[k].setPosition(Vector2f(heartDisplayHelper, 660));
        heartDisplayHelper += 40;
    }

    if (!fontStyle.openFromFile("./Fonts/scorefont.ttf")) // open not load
    {
        cout << "Error loading scorefont.ttf";
    }
    scoreText.setCharacterSize(22);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(Vector2f(840, 660));
    scoreText.setString("Score: 0");

    // ----------

    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        maxEnemies[i].setPosition({0, -100});
    }
    for (int i = 0; i < maxEnemyBullets; i++)
    {
        enemyBullets[i].setSize({0.0f, 0.0f});
    }
    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        enemyShootDelay[i] = enemyBulletRand(generator) * 100 + shootInterval;
        // cerr<<enemyShootDelay[i]<<" , ";
    }
}

// void spaceShipPositionManager(RenderWindow &window, Event &event)
// {

//     if (auto *key = event.getIf<Event::KeyPressed>())
//     {
//         Vector2f currentPos = spaceShip.getPosition();
//         Vector2f currentPos2 = spaceShip2.getPosition();
//         if (currentPos.x + (spaceShip.getSize().x) / 2 > 1000 || currentPos.x + (spaceShip.getSize().x) / 2 < 0)
//         {
//             focusedSpaceship = 'b';
//         }
//         else
//         {
//             focusedSpaceship = 'a';
//         }

//         if (focusedSpaceship == 'a')
//         {
//             if (currentPos.x > 500)
//             {
//                 spaceShip2.setPosition({currentPos.x - 1000.0f, 580.0f}); // If main spaceship is in right half of screen , put the secondary ship to the left of screen.
//             }
//             else
//             {
//                 spaceShip2.setPosition({currentPos.x + 1000.0f, 580.0f});
//             }
//         }
//         else if (focusedSpaceship == 'b')
//         {
//             if (currentPos2.x > 500)
//             {
//                 spaceShip.setPosition({currentPos2.x - 1000.0f, 580.0f}); // If secondary spaceship is in right half of screen , put the main ship to the left of screen.
//             }
//             else
//             {
//                 spaceShip.setPosition({currentPos2.x + 1000.0f, 580.0f});
//             }
//         }

//         // After Comitting all the poistion changes we update the variables.
//         currentPos2 = spaceShip2.getPosition();
//         currentPos = spaceShip.getPosition();

//         if (key->code == Keyboard::Key::A)
//         {
//             spaceShip.setPosition({currentPos.x - 35, currentPos.y});
//             spaceShip2.setPosition({currentPos2.x - 35, currentPos2.y});

//             spaceshipSprite.setPosition({currentPos.x - 35, currentPos.y});
//             spaceshipSprite2.setPosition({currentPos2.x - 35, currentPos2.y});
//         }
//         else if (key->code == Keyboard::Key::D)
//         {
//             spaceShip.setPosition({currentPos.x + 35, currentPos.y});
//             spaceShip2.setPosition({currentPos2.x + 35, currentPos2.y});

//             spaceshipSprite.setPosition({currentPos.x + 35, currentPos.y});
//             spaceshipSprite2.setPosition({currentPos2.x + 35, currentPos2.y});
//         }
//     }
// }


void spaceShipPositionManager(RenderWindow &window, Event &event)
{
    // --- SMOOTH MOVEMENT: compute dt (time since last call)
    static Clock moveClock;
    float dt = moveClock.restart().asSeconds();
    dt = min(dt, 0.036f); 
    if (dt <= 0.0f) dt = 0.0001f; // safety

    // movement speed in pixels per second (tweak this value if you want faster/slower)
    const float speed = 600.0f;


    Vector2f currentPos = spaceShip.getPosition();
    Vector2f currentPos2 = spaceShip2.getPosition();

    if (currentPos.x + (spaceShip.getSize().x) / 2 > 1000 || currentPos.x + (spaceShip.getSize().x) / 2 < 0)
    {
        focusedSpaceship = 'b';
    }
    else
    {
        focusedSpaceship = 'a';
    }


    if (focusedSpaceship == 'a')
    {
        if (currentPos.x > 500)
        {
            spaceShip2.setPosition({currentPos.x - 1000.0f, 580.0f});
        }
        else
        {
            spaceShip2.setPosition({currentPos.x + 1000.0f, 580.0f});
        }
    }
    else if (focusedSpaceship == 'b')
    {
        if (currentPos2.x > 500)
        {
            spaceShip.setPosition({currentPos2.x - 1000.0f, 580.0f});
        }
        else
        {
            spaceShip.setPosition({currentPos2.x + 1000.0f, 580.0f});
        }
    }


    currentPos2 = spaceShip2.getPosition();
    currentPos  = spaceShip.getPosition();


    float moveDelta = 0.0f;
    if (Keyboard::isKeyPressed(Keyboard::Key::A))
        moveDelta -= speed * dt;
    if (Keyboard::isKeyPressed(Keyboard::Key::D))
        moveDelta += speed * dt;

    if (moveDelta != 0.0f)
    {
        spaceShip.setPosition({ currentPos.x + moveDelta, currentPos.y });
        spaceShip2.setPosition({ currentPos2.x + moveDelta, currentPos2.y });

        spaceshipSprite.setPosition({ currentPos.x + moveDelta, currentPos.y });
        spaceshipSprite2.setPosition({ currentPos2.x + moveDelta, currentPos2.y });
    }
}


void bulletTranslator(RectangleShape &bullet)
{
    if (bullet.getPosition().y >= -10)
    {
        bullet.move({0.0f, bulletSpeed});
    }
    else
    {
        bullet.setSize({0.0f, 0.0f});
        bullet.setPosition({455.0f, 580.0f});
    }
}

void bulletSelector(RectangleShape bulletMagazine[], Event &event)
{
    if (auto *key = event.getIf<Event::MouseButtonPressed>())
    {

        if (key->button == Mouse::Button::Left)
        {

            int i = 0;
            while (i < 500 && bulletMagazine[i].getSize().x != 0.0f)
                i++;

            if (i >= 500)
            {
                cerr << "No bullet slots empty!\n";
                return;
            }

            bulletMagazine[i].setSize({25.0f, 45.0f});
            if (focusedSpaceship == 'a')
            {
                float bulletX = spaceShip.getPosition().x + spaceShip.getSize().x / 2 - 12.5;
                bulletMagazine[i].setPosition({bulletX, 580.0f});
            }
            else if (focusedSpaceship == 'b')
            {
                float bulletX = spaceShip2.getPosition().x + spaceShip2.getSize().x / 2 - 12.5;
                bulletMagazine[i].setPosition({bulletX, 580.0f});
            }
        }
    }
}

void clearPreviousWave()
{
    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        if (maxEnemies[i].getSize().x > 0)
        {
            maxEnemies[i].setSize({0.0, 0.0});
            maxEnemies[i].setPosition({0.0, -100.0});
        }
    }
}

bool waveOver(Clock &timeElapsed)
{
    // Checks if Time is Over For Previous Wave
    int timeGranted = 0;
    if (waveLevel == 1)
        timeGranted = 20;
    else if (waveLevel == 2)
        timeGranted = 20;
    else if (waveLevel == 3)
        timeGranted = 20;
    else if (waveLevel == 4)
        timeGranted = 20;
    else if (waveLevel == 5)
        timeGranted = 20;

    if (timeElapsed.getElapsedTime().asSeconds() > timeGranted)
    {
        // cerr<<"Haluting because times up! \n";
        waveLevel++;
        if(waveLevel >5){
            waveLevel = 1;
        }
        cerr << "Wave Level : " << waveLevel << endl;
        timeElapsed.restart();
        clearPreviousWave();
        return true;
    }

    // If Time is Not Over Yet , Check if all the enemies have been destroyed in current wave;
    bool isWaveOver = true;
    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        if (maxEnemies[i].getSize().x > 0)
        {
            isWaveOver = false;
            break;
        }
    }

    if (isWaveOver && timeElapsed.getElapsedTime().asSeconds() > 30.0f)
    {
        // cerr<<"Haluting because All enemies dead ! \n";
        waveLevel++;
        cerr << "Wave Level : " << waveLevel << endl;
        clearPreviousWave();
        timeElapsed.restart(); // restart timer for next wave
        return true;
    }

    return false;
}

bool isItOver = false;
void enemySpawner(RenderWindow &window, Clock &timeElapsed)
{
    // Handle the "fast travel" effect after a wave
    if (isItOver)
    {
        float t = timeElapsed.getElapsedTime().asSeconds();

        if (t < 5.0f)
        {
            bgScollSpeed = 5;
        }
        else if (t < 8.0f)
        {
            bgScollSpeed = 3;
        }
        else if (t < 9.5f)
        {
            bgScollSpeed = 1.5;
        }
        else
        {
            bgScollSpeed = 1;
            isItOver = false;
            timeElapsed.restart();
        }

        return;
    }

    if (waveLevel == 1)
    {
        levelOneWaves(maxEnemies);
    }
    else if (waveLevel == 2)
    {
        levelTwoWaves(maxEnemies);
    }
    else if (waveLevel == 3)
    {
        levelThree(maxEnemies);
    }
    else if (waveLevel == 4)
    {
        levelFour(maxEnemies);
    }
    else if (waveLevel == 5)
    {
        if (focusedSpaceship == 'a')
            levelFive(maxEnemies, spaceShip.getPosition());
        else
            levelFive(maxEnemies, spaceShip2.getPosition());
    }

    // Check if the wave is over
    isItOver = waveOver(timeElapsed);
    if (isItOver)
    {
        bgScollSpeed = 5;      // trigger initial fast speed
        timeElapsed.restart(); // start timing for the "fast travel" effect
    }
}

// Wahaab's Function .
void collisionDetector(RectangleShape bulletMagazine[], RectangleShape maxEnemies[])
{
    for (int i = 0; i < maxBullets; i++)
    {
        bool bulletActive = bulletMagazine[i].getSize().x != 0;
        if (!bulletActive)
            continue;
        for (int j = 0; j < maxEnemiesNumber; j++) // Collision of bullet and enemy
        {

            bool enemyActive = maxEnemies[j].getSize().x != 0;
            if (enemyActive)
            {
                FloatRect bullet = bulletMagazine[i].getGlobalBounds();
                FloatRect enemy = maxEnemies[j].getGlobalBounds();

                if (bullet.findIntersection(enemy)) // find intersection finction to detect collision
                {
                    maxEnemies[j].setSize({0.0, 0.0});     // enemy destroyed
                    bulletMagazine[i].setSize({0.0, 0.0}); // bullet detroyed
                    playerScore += 10;
                    scoreText.setString("Score: " + to_string(playerScore));
                    break;
                }
            }
        }
    }
}

void collisionForEnemies(RectangleShape enemyBullets[], RectangleShape spaceShipX, RectangleShape spaceShipX2)
{
    for (int i = 0; i < maxEnemyBullets; i++)
    {
        bool bulletActive = enemyBullets[i].getSize().x != 0.0f;
        if (!bulletActive)
        {
            continue;
        }
        FloatRect bullet = enemyBullets[i].getGlobalBounds();
        FloatRect ship1 = spaceShipX.getGlobalBounds();
        FloatRect ship2 = spaceShipX2.getGlobalBounds();
        if (bullet.findIntersection(ship1) || bullet.findIntersection(ship2))
        {
            enemyBullets[i].setSize({0.0f, 0.0f});
            enemyBullets[i].setPosition({0.0f, -100.0f});
            maxHearts--;
            if(maxHearts < 1){
                gameOver = true;
                spaceShip.setSize({0,0});
                spaceShip2.setSize({0,0});
                scoreSaverForLB(currentPlayer , playerScore);
                LeaderboardUtilityFunc();
                scoreTextGO.setString(scoreText.getString());
            }
        }
    }
    for(int i=0; i<maxEnemiesNumber ;i++){
        bool enemyActive = maxEnemies[i].getSize().x != 0.0f;
        if(!enemyActive){
            continue;
        }
        FloatRect theEnemy = maxEnemies[i].getGlobalBounds();
        FloatRect ship1 = spaceShipX.getGlobalBounds();
        FloatRect ship2 = spaceShipX2.getGlobalBounds();
        if(theEnemy.findIntersection(ship1) || theEnemy.findIntersection(ship2)){
            maxEnemies[i].setSize({0.0f , 0.0f});
            maxEnemies[i].setPosition({0.0f , -100.0f});
            maxHearts--;
            if(maxHearts < 1){
                gameOver = true;
                spaceShip.setSize({0,0});
                spaceShip2.setSize({0,0});
                scoreSaverForLB(currentPlayer , playerScore);
                LeaderboardUtilityFunc();
                scoreTextGO.setString(scoreText.getString());
            }
        }
    }
}

void enemyBulletTranslator(RectangleShape &bullet)
{
    if (bullet.getPosition().y <= 700)
    {
        bullet.move({0.0f, enemyBulletSPeed});
    }
    else
    {
        bullet.setSize({0.0f, 0.0f});
        bullet.setPosition({455.0f, 580.0f});
    }
}

void enemyBulletSelector(RectangleShape enemyBullets[], RectangleShape maxEnemies[])
{
    if (enemyShootClock.getElapsedTime().asMilliseconds() < 500)
    {
        return;
    }
    else
    {
        enemyShootClock.restart();
    }
    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        if (maxEnemies[i].getSize().x > 0 && maxEnemies[i].getPosition().y > 0)
        {
            int j = 0;
            while (j < maxEnemyBullets && enemyBullets[j].getSize().x != 0.0f)
            {
                j++;
            }
            if (j >= maxEnemyBullets)
            {
                cerr << "Limit : No Enemy Bullets available.";
                return;
            }
            if (enemyShootTimer[i].getElapsedTime().asMilliseconds() >= enemyShootDelay[i])
            {
                enemyBullets[j].setSize({25.0, 40.0});
                enemyBullets[j].setTexture(&enemyBulletTexture);
                enemyBullets[j].setPosition({maxEnemies[i].getPosition().x + 25, maxEnemies[i].getPosition().y + 50});
                enemyShootTimer[i].restart();
            }
        }
    }
}
void gEvHandler(RenderWindow &window, Event &event)
{


    if(gameOver){
        gameOverEventHandler(window , event);
        return;
    }

    if (gamePaused)
    {
        pauseScreen_EventHandler(window, event);
        return;
    }

    if (auto *key = event.getIf<Event::MouseButtonPressed>())
    {
        Vector2f mousePosition = {(float)Mouse::getPosition(window).x, (float)Mouse::getPosition(window).y};
        if (pauseButton.getGlobalBounds().contains(mousePosition))
        {
            gamePaused = true;
            pauseButton.setTexture(resumeTexture);
            return;
        }
    }

    if (auto *key = event.getIf<Event::KeyPressed>())
    {
        if (key->code == Keyboard::Key::P)
        {
            gamePaused = !gamePaused;
            return;
        }
    }

    if (!gamePaused)
    {
        spaceShipPositionManager(window, event);
        bulletSelector(bulletMagazine, event);
    }
}

void backgroundMover(float moveY)
{
    if (bgMovementClock.getElapsedTime().asMilliseconds() > 3)
    {
        copy1.move({0.0f, moveY});
        copy2.move({0.0f, moveY});

        float bgHeight = copy1.getLocalBounds().size.y * copy1.getScale().y;
        float windowHeight = 700.0f;

        if (copy1.getPosition().y >= windowHeight)
            copy1.setPosition({0.0f, copy2.getPosition().y - bgHeight});

        if (copy2.getPosition().y >= windowHeight)
            copy2.setPosition({0.0f, copy1.getPosition().y - bgHeight});

        bgMovementClock.restart();
    }
}

void referenceFuncionToStoreNames(){
    cerr<<"Sending Data......\n";
    infoSaver(currentPlayer , playerScore , spaceShip.getPosition().x , spaceShip2.getPosition().x , maxHearts);
}

void gameDrawer(RenderWindow &window, Clock &timeElapsed)
{
    // window.draw(backgroundSprite);
    // window.draw(spaceShip);                    // Draw these only when you want to see the hitbox of spaceShip
    // window.draw(spaceShip2);

    cerr<<"Drawing Game....\n";
    if (!gamePaused)
    {
        backgroundMover(bgScollSpeed);
    }
    window.draw(copy1);
    window.draw(copy2);

    if(!gameOver){
        window.draw(spaceshipSprite);
        window.draw(spaceshipSprite2);
    }

    for (int i = 0; i < 500; i++)
    {
        if (bulletMagazine[i].getSize().x > 0.0f)
        {
            if (!gamePaused)
            {
                bulletTranslator(bulletMagazine[i]);
            }
            window.draw(bulletMagazine[i]);
        }
    }

    if (!gamePaused)
    {
        enemySpawner(window, timeElapsed);
    }

    for (int i = 0; i < maxEnemiesNumber; i++)
    {
        if (maxEnemies[i].getSize().x > 0.0f)
        {
            if ((waveLevel == 1 || waveLevel == 2) && !gamePaused)
            {
                enemyTranslator(maxEnemies);
            }
            else if (waveLevel == 3 && !gamePaused)
            {
                enemyTranslatorLvl3(maxEnemies);
            }
            else if (waveLevel == 4 && !gamePaused)
            {
                enemyTranslatorLvl4(maxEnemies);
            }
            else if (waveLevel == 5 && !gamePaused)
            {
                enemyTranslatorLvl5(maxEnemies);
            }

            window.draw(maxEnemies[i]);
        }
    }

    if (!gamePaused)
    {
        enemyBulletSelector(enemyBullets, maxEnemies);
    }

    for (int i = 0; i < maxEnemyBullets; i++)
    {
        if (enemyBullets[i].getSize().x > 0)
        {
            if (!gamePaused)
            {
                enemyBulletTranslator(enemyBullets[i]);
            }
            window.draw(enemyBullets[i]);
        }
    }
    collisionDetector(bulletMagazine, maxEnemies);
    collisionForEnemies(enemyBullets, spaceShip, spaceShip2);

    for (int i = 0; i < maxHearts; i++)
    {
        window.draw(hearts[i]);
    }

    window.draw(scoreText);

    if (gamePaused)
    {
        pauseScreen_Drawer(window);
    }
    if(!gameOver){
        window.draw(pauseButton);
    }

    if(gameOver){
        gameOverDrawer(window);
    }
}