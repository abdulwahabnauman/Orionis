#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
using namespace sf;

extern Texture proto_ship;
extern Clock timeElapsedInGame;

extern char currentPlayer[];
extern RectangleShape maxEnemies[];
extern int maxEnemiesNumber;
extern int maxHearts;
extern int waveLevel;
extern int playerScore;
extern RectangleShape spaceShip;
extern RectangleShape spaceShip2;
extern Sprite spaceshipSprite;
extern Sprite spaceshipSprite2;
extern Text scoreText;

void scoreSaverForLB(string userName, int score)
{
    fstream file("./TextFiles/namesORIONIS.txt", ios::in);
    if (!file.is_open())
    {
        cerr << "Unable to Open names file";
    }

    char nString[11][100];
    int iter1 = 0;
    bool alreadyPresent = false;
    while (file.getline(nString[iter1], 100))
    {
        iter1++;
    }
    file.close();


    //  Now first check the score on 11th row .
    fstream scoreRead("./TextFiles/scoresORIONIS.txt", ios::in);
    char myText[11][100];
    int iterator = 0;
    while (scoreRead.getline(myText[iterator], 100))
    {
        iterator++;
    }
    scoreRead.close();

    int integerScore = 0;
    for (int i = 0; myText[10][i] != '\0'; i++)
    {
        integerScore = integerScore * 10 + (myText[10][i] - '0');
    }

    if (score > integerScore)
    {
        fstream scoreFile("./TextFiles/scoresORIONIS.txt", ios::out);
        for(int i=0 ; i< 11; i++){

            if (!i)
            {
                scoreFile << myText[i];
            }
            else if(i==10){
                scoreFile << "\n"
                << to_string(score);
            }
            else{
                scoreFile << "\n"
                << myText[i];
            }
            
        }
        scoreFile.close();

        fstream nameFile("./TextFiles/namesORIONIS.txt" , ios::out);
        for(int i=0; i<11; i++){
            if (!i)
            {
                nameFile << nString[i];
            }
            else if(i==10){
                nameFile<< "\n"<<userName;
            }
            else{
                nameFile<< "\n"
                << nString[i];
            }
        }
        nameFile.close();

    }
}

// Updates a specific line in a file with newData
void updateSingleFile(const char *fileName, const char *newData, int indexAT)
{
    char line[1000];
    fstream file(fileName, ios::in);
    ofstream tempFile("./TextFiles/GameState/tempDummy.txt");
    int lineCount = 0;

    while (file.getline(line, 1000))
    {
        lineCount++;
        if (lineCount == indexAT)
            tempFile << newData << "\n"; // replace line
        else
            tempFile << line << "\n"; // copy existing line
    }

    file.close();
    tempFile.close();

    remove(fileName);
    rename("./TextFiles/GameState/tempDummy.txt", fileName);
}

void updateFile(char name[30], int score, float ship1Xpos, float ship2Xpos, int heartsCount,
                int enemiesActiveCount, char enemyXpos[1000], char enemyYpos[1000], int waveLevel,
                int indexAT)
{
    char line[1000];
    char data[1024]; // temp buffer
    int lineCount = 0;

    auto updateSingleFile = [&](const char *fileName, const char *newData)
    {
        fstream file(fileName, ios::in);
        ofstream tempFile("./TextFiles/GameState/tempDummy.txt");
        lineCount = 0;
        while (file.getline(line, 1000))
        {
            lineCount++;
            if (lineCount == indexAT)
                tempFile << newData << "\n";
            else
                tempFile << line << "\n";
        }
        file.close();
        tempFile.close();
        remove(fileName);
        rename("./TextFiles/GameState/tempDummy.txt", fileName);
    };

    // --- mainNames.txt ---
    updateSingleFile("./TextFiles/GameState/mainNames.txt", name);

    // --- mainScores.txt ---
    sprintf(data, "%d", score);
    updateSingleFile("./TextFiles/GameState/mainScores.txt", data);

    // --- ship1pos.txt ---
    sprintf(data, "%d", (int)ship1Xpos);
    updateSingleFile("./TextFiles/GameState/ship1pos.txt", data);

    // --- ship2pos.txt ---
    sprintf(data, "%d", (int)ship2Xpos);
    updateSingleFile("./TextFiles/GameState/ship2pos.txt", data);

    // --- heartsCount.txt ---
    sprintf(data, "%d", heartsCount);
    updateSingleFile("./TextFiles/GameState/heartsCount.txt", data);

    // --- enemiesActive.txt ---
    sprintf(data, "%d", enemiesActiveCount);
    updateSingleFile("./TextFiles/GameState/enemiesActive.txt", data);

    // --- enemiesXpos.txt ---
    updateSingleFile("./TextFiles/GameState/enemiesXpos.txt", enemyXpos);

    // --- enemiesYpos.txt ---
    updateSingleFile("./TextFiles/GameState/enemiesYpos.txt", enemyYpos);

    // --- level.txt ---
    sprintf(data, "%d", waveLevel);
    updateSingleFile("./TextFiles/GameState/level.txt", data);
}

void infoSaver(char name[30], int score, float ship1Xpos, float ship2Xpos, int heartsCount)
{
    cerr << "Storing....." << name << endl;

    fstream file("./TextFiles/GameState/mainNames.txt", ios::in | ios::app);
    if (!file.is_open())
    {
        cerr << "Unable to Open mainNames.txt file";
        return;
    }

    char nString[30];
    bool alreadyPresent = false;
    int noOfLines = 0;
    int indexAt = -1;

    while (file.getline(nString, 30))
    {
        if (strcmp(currentPlayer, nString) == 0)
        { // strcmp is used to compare two c-strings[]
            alreadyPresent = true;
            indexAt = noOfLines + 1;
        }
        noOfLines++;
    }

    file.clear(); // clear EOF before writing

    if (!alreadyPresent)
    {
        file << "\n"
             << name;
        file.close();

        // Now storing the scores.

        fstream scoreFile("./TextFiles/GameState/mainScores.txt", ios::in | ios::app);
        if (!scoreFile.is_open())
        {
            cerr << "Unable to Open mainScores.txt file";
            return;
        }
        scoreFile.clear();
        if (!alreadyPresent)
        {
            scoreFile << "\n"
                      << to_string(score);
        }
        scoreFile.close();

        // Now Storing the spaceShip Position;

        fstream spPosition("./TextFiles/GameState/ship1pos.txt", ios::in | ios::app);
        fstream spPosition2("./TextFiles/GameState/ship2pos.txt", ios::in | ios::app);
        if (!spPosition.is_open() || !spPosition2.is_open())
        {
            cerr << "Unable to Open spaceshipPositions.txt file";
            return;
        }
        spPosition << "\n"
                   << to_string(ship1Xpos);
        spPosition2 << "\n"
                    << to_string(ship2Xpos);

        spPosition.close();
        spPosition2.close();

        // Now Store the number of hearts the user has.

        fstream heartsFile("./TextFiles/GameState/heartsCount.txt", ios::in | ios::app);
        if (!heartsFile.is_open())
        {
            cerr << "Unable to Open heartsCount.txt file";
        }
        heartsFile << "\n"
                   << heartsCount;
        heartsFile.close();

        // Now Store how many enemies are there on screen

        fstream enemiesActive("./TextFiles/GameState/enemiesActive.txt", ios::in | ios::app);
        fstream enemiesXpos("./TextFiles/GameState/enemiesXpos.txt", ios::in | ios::app);
        fstream enemiesYpos("./TextFiles/GameState/enemiesYpos.txt", ios::in | ios::app);
        if (!enemiesActive.is_open() || !enemiesXpos.is_open() || !enemiesYpos.is_open())
        {
            cerr << "Unable to Open one of the three enemy files";
        }
        enemiesXpos << "\n";
        enemiesYpos << "\n";
        int num = 0;
        for (int i = 0; i < maxEnemiesNumber; i++)
        {
            if (maxEnemies[i].getSize().x > 0)
            {
                enemiesXpos << to_string((int)maxEnemies[i].getPosition().x) + ",";
                enemiesYpos << to_string((int)maxEnemies[i].getPosition().y) + ",";
                num++;
            }
        }
        enemiesActive << "\n"
                      << to_string(num);
        enemiesActive.close();
        enemiesXpos.close();
        enemiesYpos.close();

        fstream level("./TextFiles/GameState/level.txt", ios::in | ios::app);
        if (!level.is_open())
        {
            cerr << "Unable to Open level.txt file";
        }
        level << "\n"
              << to_string(waveLevel);
        level.close();
    }
    else
    {
        // --- Prepare enemy positions ---
        char enemyXpos[1000] = "";
        char enemyYpos[1000] = "";
        char temp[20]; // temp buffer for sprintf
        int enemiesAlive = 0;

        for (int i = 0; i < maxEnemiesNumber; i++)
        {
            if (maxEnemies[i].getSize().x > 0)
            {
                sprintf(temp, "%d,", (int)maxEnemies[i].getPosition().x);
                strcat(enemyXpos, temp);

                sprintf(temp, "%d,", (int)maxEnemies[i].getPosition().y);
                strcat(enemyYpos, temp);

                enemiesAlive++;
            }
        }
        cerr << "Enemy Positions" << enemyXpos << "\n : " << enemyXpos;
        // --- Call the new updateFile() ---
        updateFile(
            name,         // user's name
            score,        // score
            ship1Xpos,    // ship1 X pos
            ship2Xpos,    // ship2 X pos
            heartsCount,  // hearts count
            enemiesAlive, // number of alive enemies
            enemyXpos,    // X positions
            enemyYpos,    // Y positions
            waveLevel,    // wave level
            indexAt       // line number of current player
        );
    }
}

int nameSearch(char name[30])
{
    fstream file("./TextFiles/GameState/mainNames.txt", ios::in | ios::app);
    if (!file.is_open())
    {
        cerr << "Unable to Open mainNames.txt file";
    }

    char nString[30];
    bool alreadyPresent = false;
    int noOfLines = 0;
    int indexAt = -1;

    while (file.getline(nString, 30))
    {
        if (strcmp(currentPlayer, nString) == 0)
        { // strcmp is used to compare two c-strings[]
            alreadyPresent = true;
            indexAt = noOfLines + 1;
        }
        noOfLines++;
    }

    if (alreadyPresent)
    {
        return indexAt;
    }
    else
    {
        return -1;
    }
    file.close();

    return -1;
}

void loadScore(int rowNumber)
{
    fstream scoreFile("./TextFiles/GameState/mainScores.txt", ios::in);
    if (!scoreFile.is_open())
    {
        cerr << "Unable to open the scores txt\n";
        return;
    }

    char score[30];
    int iterator = 0;

    while (scoreFile.getline(score, 30))
    {
        iterator++;
        if (iterator == rowNumber)
            break;
    }

    scoreFile.close();

    playerScore = 0;
    for (int i = 0; score[i] != '\0'; i++)
    {
        if (score[i] >= '0' && score[i] <= '9')
            playerScore = playerScore * 10 + (score[i] - '0');
    }

    scoreText.setString("Score : " + to_string(playerScore));
}

void loadHearts(int rowNumber)
{
    fstream heartsFile("./TextFiles/GameState/heartsCount.txt", ios::in);
    if (!heartsFile.is_open())
    {
        cerr << "Unable to open hearts file\n";
        return;
    }

    char hearts[10];
    int iterator = 0;

    while (heartsFile.getline(hearts, 10))
    {
        iterator++;
        if (iterator == rowNumber)
            break;
    }

    heartsFile.close();

    maxHearts = 0;
    for (int i = 0; hearts[i] != '\0'; i++)
    {
        if (hearts[i] >= '0' && hearts[i] <= '9')
            maxHearts = maxHearts * 10 + (hearts[i] - '0');
    }
}

float loadShip1Pos(int rowNumber, char path[200])
{
    fstream ship1pos(path, ios::in);
    if (!ship1pos.is_open())
    {
        cerr << "Unable to open ship1pos file\n";
    }
    int iterator = 0;
    char position[50];
    while (ship1pos.getline(position, 50))
    {
        iterator++;
        if (iterator == rowNumber)
        {
            break;
        }
    }

    int decimalPart = 0;
    float floatPart = 0;
    int i = 0;
    for (i = 0; position[i] != '.' && position[i] != '\0'; i++)
    {
        decimalPart = decimalPart * 10 + (position[i] - '0');
    }

    if (position[i] == '.')
    {
        floatPart = (position[i + 1] - '0') / 10;
    }

    float totalPos = floatPart + (float)decimalPart;
    ship1pos.close();

    return totalPos;
}

int loadEnemiesNumber(int rowNumber)
{
    fstream enemiesNum("./TextFiles/GameState/enemiesActive.txt", ios::in);
    if (!enemiesNum.is_open())
    {
        cerr << "Unable to open enemiesActive file\n";
    }

    int iterator = 0;
    char line[10];
    while (enemiesNum.getline(line, 50))
    {
        iterator++;
        if (iterator == rowNumber)
        {
            break;
        }
    }

    int number = 0;
    for (int i = 0; line[i] != '\0'; i++)
    {
        number = number * 10 + (line[i] - '0');
    }

    enemiesNum.close();
    return number;
}

void setEnemyXpos(int rowNumber, int count)
{
    fstream enemiesXpos("./TextFiles/GameState/enemiesXpos.txt", ios::in);
    if (!enemiesXpos.is_open())
    {
        cerr << "Unable to open enemiesXpos file\n";
        return;
    }

    int iterator = 0;
    char line[500];

    while (enemiesXpos.getline(line, 500))
    {
        iterator++;
        if (iterator == rowNumber)
            break;
    }

    enemiesXpos.close();

    int enemyIndex = 0;
    int xPosition = 0;
    char positionString[50];
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != ',')
        {
            positionString[j++] = line[i];
        }
        else
        {
            positionString[j] = '\0';
            xPosition = 0;
            for (int k = 0; positionString[k] != '\0'; k++)
            {
                xPosition = xPosition * 10 + (positionString[k] - '0');
            }

            // cerr<<"Positions: "<<xPosition<<endl;
            if (enemyIndex < count)
            {
                maxEnemies[enemyIndex].setSize({50.0f, 50.0f});
                maxEnemies[enemyIndex].setPosition({(float)xPosition, -100.0f});
                maxEnemies[enemyIndex].setTexture(&proto_ship);
                enemyIndex++;
            }

            j = 0;
            xPosition = 0;
        }
    }
}

void setEnemyYpos(int rowNumber, int count)
{
    fstream enemiesYpos("./TextFiles/GameState/enemiesYpos.txt", ios::in);
    if (!enemiesYpos.is_open())
    {
        cerr << "Unable to open enemiesYpos file\n";
        return;
    }

    int iterator = 0;
    char line[500];

    while (enemiesYpos.getline(line, 500))
    {
        iterator++;
        if (iterator == rowNumber)
            break;
    }

    enemiesYpos.close();

    int enemyIndex = 0;
    int yPosition = 0;
    char positionString[50];
    int j = 0;

    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] != ',')
        {
            positionString[j++] = line[i];
        }
        else
        {
            positionString[j] = '\0';
            yPosition = 0;
            for (int k = 0; positionString[k] != '\0'; k++)
            {
                yPosition = yPosition * 10 + (positionString[k] - '0');
            }

            // cerr<<"Positions: "<<xPosition<<endl;
            if (enemyIndex < count)
            {
                maxEnemies[enemyIndex].setSize({50.0f, 50.0f});
                maxEnemies[enemyIndex].setPosition({maxEnemies[enemyIndex].getPosition().x, (float)yPosition});
                maxEnemies[enemyIndex].setTexture(&proto_ship);
                enemyIndex++;
            }

            j = 0;
            yPosition = 0;
        }
    }
}

void loadLevel(int rowNumber)
{
    fstream levelFile("./TextFiles/GameState/level.txt", ios::in);
    if (!levelFile.is_open())
    {
        cerr << "Unable to open the level txt\n";
        return;
    }

    char level[30];
    int iterator = 0;

    while (levelFile.getline(level, 30))
    {
        iterator++;
        if (iterator == rowNumber)
        {
            break;
        }
    }

    int wLevel = 0;
    for (int i = 0; level[i] != '\0'; i++)
    {
        wLevel = wLevel * 10 + (level[i] - '0');
    }
    waveLevel = wLevel;
}

void loadBackedUpGame(int rowNumber)
{
    loadScore(rowNumber);
    loadHearts(rowNumber);

    char path[200] = "./TextFiles/GameState/ship1pos.txt";
    float ship1Pos = loadShip1Pos(rowNumber, path);
    spaceShip.setPosition({ship1Pos, 580.0});
    spaceshipSprite.setPosition({ship1Pos, 580.0});
    cerr << "\n\n Ship 1 pos : " << ship1Pos << " and currently at : " << spaceShip.getPosition().x;

    char path2[200] = "./TextFiles/GameState/ship2pos.txt";
    float ship2Pos = loadShip1Pos(rowNumber, path2);
    spaceShip2.setPosition({ship2Pos, 580.0});
    spaceshipSprite2.setPosition({ship2Pos, 580.0});
    cerr << "\n\n Ship 2 pos : " << ship2Pos;

    int enemiesActive = loadEnemiesNumber(rowNumber);
    setEnemyXpos(rowNumber, enemiesActive);
    setEnemyYpos(rowNumber, enemiesActive);

    loadLevel(rowNumber);

    timeElapsedInGame.restart(); // MOST IMPORTANT
}

void deleteRowFromFile(const char *filePath, int rowNumber)
{
    fstream file(filePath, ios::in);
    if (!file.is_open())
    {
        cerr << "Unable to open file: " << filePath << endl;
        return;
    }

    char lines[500][500];
    int totalLines = 0;

    while (file.getline(lines[totalLines], 500))
    {
        totalLines++;
    }
    file.close();

    fstream outFile(filePath, ios::out | ios::trunc);
    if (!outFile.is_open())
    {
        cerr << "Unable to rewrite file: " << filePath << endl;
        return;
    }

    for (int i = 0, currentRow = 1; i < totalLines; i++, currentRow++)
    {
        if (currentRow == rowNumber)
            continue;

        outFile << lines[i] << endl;
    }
    outFile.close();
}

void clearBackupAfterLoading(int rowNumber)
{
    deleteRowFromFile("./TextFiles/GameState/mainNames.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/mainScores.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/heartsCount.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/ship1pos.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/ship2pos.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/enemiesXpos.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/enemiesYpos.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/enemiesActive.txt", rowNumber);
    deleteRowFromFile("./TextFiles/GameState/level.txt", rowNumber);
}
