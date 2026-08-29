    #pragma once
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <SFML/System.hpp>
    #include <random>

    using namespace std;
    using namespace sf;
    Texture proto_ship("./Assets/protoType.png");
    extern int maxEnemiesNumber;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 950);
    uniform_int_distribution<> colorDist(0, 255);
    uniform_int_distribution<> snakeDistr(11, 19);
    Clock spawnDelay;
    Clock moveDelay;
    Clock levelFourSpawnDelay;

    // Remember to change the lengths of these arrays manually if you changed the maxEnemiesNumber ;
    float rectSelf[100] = {0};          // Level 3
    float rectOpp[100] = {0};          // Level 3
    float gradient[100] = {0};        // Level 3
    float snakeGradient[100] = {0};  // Level 4
    bool jumped[100] = {0};         // Level 4
    // float spawnPositions[100];  // For Level 5

    void enemyTranslator(RectangleShape maxEnemies[])
    {
        if (moveDelay.getElapsedTime().asMilliseconds() >= 2.5f)
        {
            moveDelay.restart();
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x > 0.0f && maxEnemies[i].getPosition().y < 700)
                {
                    maxEnemies[i].move({0.0f, 1.0f});
                }
                else{
                    maxEnemies[i].setSize({0.0f , 0.0f});
                }
            }
        }
    }

    void levelOneWaves(RectangleShape maxEnemies[])
    {
        // cerr<<" Level One was Called !\n";
        if (spawnDelay.getElapsedTime().asMilliseconds() >= 700.0f)  // 0.7seconds
        {
            spawnDelay.restart();
            int activeRightNow = 0;
            for(int i=0 ; i<maxEnemiesNumber ; i++){
                if (maxEnemies[i].getSize().x != 0.0)
                {
                    activeRightNow ++;
                }
            }

            if(activeRightNow >5){
                return;
            }

            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x == 0.0)
                {
                    // cerr << "Enemy Index [" << i << "] is available.\n";
                    maxEnemies[i].setSize({50.0, 50.0});
                    float randomX = distr(gen);
                    maxEnemies[i].setPosition({randomX, -80.0});
                    maxEnemies[i].setTexture(&proto_ship);
                    // cerr << "Enemy Sized Up!\n";
                    // maxEnemies[i].setFillColor(Color(colorDist(gen) , colorDist(gen) , colorDist(gen)));
                    break;
                }
            }
        }
    }

    void levelTwoWaves(RectangleShape maxEnemies[])
    {
        if (spawnDelay.getElapsedTime().asMilliseconds() >= 900.0f) // 0.9sec
        {
            spawnDelay.restart();
            
            int counter = 0;
            float randomX = distr(gen);
            while (randomX + 151 >= 1000)
            {
                randomX = distr(gen);
            }
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x == 0.0)
                {
                    maxEnemies[i].setSize({50.0, 50.0});
                    maxEnemies[i].setPosition({randomX, -80.0});
                    maxEnemies[i].setTexture(&proto_ship);
                    randomX += 50;
                    counter++;
                    if (counter == 3)
                    {
                        break;
                    }
                }
            }
        }
    }

    void enemyTranslatorLvl3(RectangleShape maxEnemies[])
    {
        if (moveDelay.getElapsedTime().asMilliseconds() > 50.0f)
        {
            moveDelay.restart();
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x == 0)
                {
                    continue;
                }
                if (maxEnemies[i].getPosition().y >= 700)
                {
                    maxEnemies[i].setPosition({0.0, -80.0});
                    maxEnemies[i].setSize({0.0, 0.0});
                    continue;
                }

                float rectPosX = maxEnemies[i].getPosition().x;
                if (rectSelf[i] + 50 < rectOpp[i])
                {
                    if (rectPosX <= rectOpp[i] && gradient[i] != -10)
                    {
                        maxEnemies[i].move({5.0, 2.0});
                        if (maxEnemies[i].getPosition().x >= rectOpp[i])
                        {
                            gradient[i] = -10;
                        }
                    }
                    else if (gradient[i] == -10)
                    {
                        maxEnemies[i].move({-5.0, 2.0});
                        if (maxEnemies[i].getPosition().x <= rectSelf[i])
                        {
                            gradient[i] = 10;
                        }
                    }
                }
                else
                {
                    if (rectPosX >= rectOpp[i] && gradient[i] != 10)
                    {
                        maxEnemies[i].move({-5.0, 2.0});
                        if (maxEnemies[i].getPosition().x <= rectOpp[i])
                        {
                            gradient[i] = 10;
                        }
                    }
                    else if (gradient[i] == 10)
                    {
                        maxEnemies[i].move({5.0, 2.0});
                        if (maxEnemies[i].getPosition().x >= rectSelf[i])
                        {
                            gradient[i] = -10;
                        }
                    }
                }
            }
        }
    }

    void levelThree(RectangleShape maxEnemies[])
    {
        if (spawnDelay.getElapsedTime().asSeconds() >= 7.0f)  
        {
            spawnDelay.restart();
            float X = 0; // spawn position of first enemy
            for (int m = 0; m < 5; m++)
            {
                float opposite = X + 200.f; // opposite boundary
                int spawned = 0;
                for (int i = 0; i < maxEnemiesNumber; i++)
                {
                    if (spawned == 2) // spawn exactly 2 enemies ( one pair of two )
                        break;

                    if (maxEnemies[i].getSize().x == 0.0f)
                    {
                        if (spawned == 0)
                        {
                            // FIRST OF PAIR
                            maxEnemies[i].setSize({50.f, 50.f});
                            maxEnemies[i].setPosition({X, -80.f});
                            maxEnemies[i].setTexture(&proto_ship);

                            rectSelf[i] = X;       // spawn point
                            rectOpp[i] = opposite; // opposite boundary
                            gradient[i] = +10.f;   // moving right first
                        }
                        else // spawned == 1
                        {
                            // SECOND OF PAIR
                            maxEnemies[i].setSize({50.f, 50.f});
                            maxEnemies[i].setPosition({opposite, -80.f});
                            maxEnemies[i].setTexture(&proto_ship);

                            rectSelf[i] = opposite; // spawn point (X+200)
                            rectOpp[i] = X;         // target boundary (X)
                            gradient[i] = -10.f;    // moving left first
                        }
                        spawned++;
                    }
                }
                X = opposite + 50;
            }
        }
    }


    void enemyTranslatorLvl4(RectangleShape maxEnemies[])
    {
        // First we check if the spawn point is closer to left or to righ border . Then we decide which direction to start moving.
        if (moveDelay.getElapsedTime().asMilliseconds() > 2.0f)
        {
            moveDelay.restart();
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if(maxEnemies[i].getSize().x==0){
                    continue;
                }
                Vector2f Pos = maxEnemies[i].getPosition();
                if (snakeGradient[i] != -10)
                {

                    if (jumped[i])
                    {
                        maxEnemies[i].move({0.0, 50});
                        jumped[i] = false;
                    }
                    else
                    {
                        maxEnemies[i].move({1.0, 0});
                    }

                    if (Pos.x + 50 >= 1000)
                    {
                        maxEnemies[i].move({-1.0, 50});
                        snakeGradient[i] = -10;
                        jumped[i] = true;
                    }
                }
                else if (snakeGradient[i] == -10)
                {

                    if (jumped[i])
                    {
                        maxEnemies[i].move({0.0, 50.0});
                        jumped[i] = false;
                    }
                    else
                    {
                        maxEnemies[i].move({-1.0, 0.0});
                    }
                    if (Pos.x <= 0)
                    {
                        maxEnemies[i].move({1.0, 50});
                        snakeGradient[i] = 10;
                        jumped[i] = true;
                    }
                }
            }
        }
    }

    void levelFour(RectangleShape maxEnemies[])
    {
        // float x = levelFourSpawnDelay.getElapsedTime().asSeconds();
        //     cerr<<"Clock has hit : "<<x<<"\n";
        if (levelFourSpawnDelay.getElapsedTime().asSeconds() > 5)
        {
            // cerr<<"Clock has hit : "<<x<<"\n";
            levelFourSpawnDelay.restart();

            int batchStrength = 0;
            int snakeSpawn = 450;
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x == 0)
                {
                    maxEnemies[i].setSize({50.0, 50.0});
                    maxEnemies[i].setPosition({(float)snakeSpawn, 0.0f});
                    maxEnemies[i].setTexture(&proto_ship);
                    snakeSpawn -= 50;
                    batchStrength++;
                    // cerr<<snakeGradient[i]<<" ";
                    if(batchStrength == 10){
                        // cerr<<"\nTail at x = "<<snakeSpawn+50<<endl;
                        break;
                    }
                }
            }
        }
    }


    void levelFive(RectangleShape maxEnemies[] , Vector2f spaceShipPos){
        if(spawnDelay.getElapsedTime().asSeconds() < 2.0f){
            return;
        }
        else{
            spawnDelay.restart();
        }
        int batchStrength= 0;
        int maxPerWave = 11;   // Only Set 11 , 21, 31 etc. We will need to adjust coordinates too.
        int availableNow = 0;
        for(int i=0; i < maxEnemiesNumber; i++){
            if(maxEnemies[i].getSize().x == 0.0f){
                availableNow++;
            }
        }
        // cerr<<"Only "<<availableNow<<" enemies available\n";
        if(availableNow<maxPerWave){   // Only Spawn if we have enemies available for a full batch;
            return;
        }


        float xDistance = 90.0;
        float sx = spaceShipPos.x;
        float startingXCords = -((maxPerWave/2)*xDistance)+ sx;
        Vector2f vPos = {startingXCords ,-300.0f};
        for(int i=0 ; i<maxEnemiesNumber ; i++){
            if(maxEnemies[i].getSize().x == 0.0f){

                maxEnemies[i].setSize({50.0f , 50.0f});
                maxEnemies[i].setPosition(vPos);
                maxEnemies[i].setTexture(&proto_ship);
                // spawnPositions[i] = vPos.x;
                // cerr<<spawnPositions[i]<<" ";
                if(batchStrength< maxPerWave/2){
                    vPos = {vPos.x + xDistance , vPos.y +50};
                }
                else{
                    vPos = {vPos.x + xDistance , vPos.y -50};
                }

                // Now we predict the distance of this enemy from the one at the middle of formation
                batchStrength++;
            }
            if(batchStrength >= maxPerWave){
                break;
            }
        }
    
    }

    void enemyTranslatorLvl5(RectangleShape maxEnemies[])
    {
        if (moveDelay.getElapsedTime().asMilliseconds() >= 2.5f)
        {
            moveDelay.restart();
            for (int i = 0; i < maxEnemiesNumber; i++)
            {
                if (maxEnemies[i].getSize().x > 0.0f && maxEnemies[i].getPosition().y < 700)
                {
                    maxEnemies[i].move({0.0f, 2.0f});   
                }
                else{
                    maxEnemies[i].setSize({0.0f , 0.0f});
                }
            }
        }
    }