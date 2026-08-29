#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <fstream>
#include <cstring>

using namespace std;
using namespace sf;
extern int switcher;

const int MAX = 11;


Texture backgroundTextureLB("./Assets/leaderboardbg.png");
Sprite backgroundSpriteLB(backgroundTextureLB);

void leaderBoards_Initial(RenderWindow &window)
{

    // To store size of Present Window
    float windowWidth = (float)window.getSize().x;
    float windowHeight = (float)window.getSize().y;

    //Load Texture for background
    if (!(backgroundTextureLB.loadFromFile("./Assets/leaderboardbg.png")))
    {
        cout << "Error: Could not load leaderboard.jpg" << endl;
    }

    backgroundSpriteLB.setTexture(backgroundTextureLB);
    //Sprite for background picture

    // Get the local bounds 
    FloatRect bounds = backgroundSpriteLB.getLocalBounds();

    // Calculate scale factors using the new bounds members (.size.x, .size.y)
    // The explicit float cast ensures the division results in a float scale factor.
    float scaleX = windowWidth / bounds.size.x;
    float scaleY = windowHeight / bounds.size.y;

    // Apply the scale factors
    backgroundSpriteLB.setScale(Vector2f(scaleX, scaleY));
}


void NamesLoader(char names[][30])           //2D char array
{
    ifstream file("./TextFiles/namesORIONIS.txt");   //reading stream

    if (!file.is_open())
    {
        cout << "Unable to open namesORIONIS.txt" << endl;
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        if (file.getline(names[i], 30));
    }
    file.close();
}

void ScoresLoader(int scores[])               //int array
{
    ifstream file("./TextFiles/scoresORIONIS.txt");

    if (!file.is_open())
    {
        cout << "Unable to open open scoresORIONIS.txt" << endl;
        return;
    }

    for (int i = 0; i < MAX; i++)
    {
        if (!(file >> scores[i]))
            scores[i] = 0;
    }

    file.close();
}

void Sorter(char names[][30], int scores[])
{
    for (int i = 0; i < MAX; i++)
    {
        for (int j = i; j < MAX; j++)
        {
            if (scores[j] > scores[i])
            {
                swap(scores[i], scores[j]);

                char tempname[30];
                strcpy(tempname, names[i]);
                strcpy(names[i], names[j]);
                strcpy(names[j], tempname);
            }
        }
    }
}

void Saver(char names[][30], int scores[])
{
    ofstream nameFile("./TextFiles/namesORIONIS.txt", ios::out);
    ofstream scoreFile("./TextFiles/scoresORIONIS.txt", ios::out);

    for (int i = 0; i < MAX; i++)
    {
            nameFile << names[i] << "\n";
            scoreFile << scores[i] << "\n";
    }
}

void Displayer(RenderWindow& window, char names[][30], int scores[])
{
    Font fontLB;
    if(!fontLB.openFromFile("./Fonts/settingsfont.ttf")){
        cerr<<"ERRORR";
    }

    int SnNdisplayHelper = 205;

    Color gold(255, 215, 0);
    Color silver(230, 240, 240);
    Color bronze(205, 127, 50);

    //Color normal = Color::Cyan;
    //Color normal(140, 180, 255);
    //Color normal(135, 206, 250);
    //Color normal(0, 191, 255);   ok
    //Color normal(150, 210, 255);
    //Color normal(120, 170, 220);

    Color normal(135, 206, 250);  // LightSkyBlue
    for (int i = 0; i < 10; i++)
    {
        Text nameLB(fontLB, names[i], 23);
        Text scoreLB(fontLB, to_string(scores[i]), 22);
        Text rankLB(fontLB, to_string(i + 1), 22);

        //scoreLB.setFillColor(Color::Cyan);
        //nameLB.setFillColor(Color::Cyan);
        //rankLB.setFillColor(Color::Cyan);

        if (i == 0) {  
            nameLB.setFillColor(gold);
            scoreLB.setFillColor(gold);
            rankLB.setFillColor(gold);
        }
        else if (i == 1) {  
            nameLB.setFillColor(silver);
            scoreLB.setFillColor(silver);
            rankLB.setFillColor(silver);
        }
        else if (i == 2) {  
            nameLB.setFillColor(bronze);
            scoreLB.setFillColor(bronze);
            rankLB.setFillColor(bronze);
        }
        else {              
            nameLB.setFillColor(normal);
            scoreLB.setFillColor(normal);
            rankLB.setFillColor(normal);
        }

        nameLB.setPosition(Vector2f(445,  SnNdisplayHelper));
        scoreLB.setPosition(Vector2f(725, SnNdisplayHelper));
        rankLB.setPosition(Vector2f(185,  SnNdisplayHelper));
        
        SnNdisplayHelper += 37;
       
        
        

        window.draw(nameLB);
        window.draw(scoreLB);
        window.draw(rankLB);
    }
}

void Leaderboard(RenderWindow& window)
{
    char names[MAX][30];
    int scores[MAX];

    NamesLoader(names);
    ScoresLoader(scores);

    Sorter(names, scores);

    Saver(names, scores);

    Displayer(window, names, scores);
}

void LeaderboardUtilityFunc(){  // Will only be used to update the values in the files;
    char names[MAX][30];
    int scores[MAX];

    NamesLoader(names);
    ScoresLoader(scores);

    Sorter(names, scores);

    Saver(names, scores);
}



void lbDrawer(RenderWindow &window) // Call this function from main.cpp it has all func connected
{

    window.draw(backgroundSpriteLB);
    Leaderboard(window);
}

void leaderBoards_eventHandler(RenderWindow &window, Event &event)
{
    if (auto key = event.getIf<Event::KeyPressed>())
    {
        if (key->code == Keyboard::Key::Escape)
        {
            switcher = 0;
        }
    }
}
