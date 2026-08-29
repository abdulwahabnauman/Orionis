#include <SFML/Graphics.hpp>
#include "./Screens/mainMenu.h"
#include "./Screens/gamePlay.h"
#include "./Screens/leaderBoards.h"
#include "./Screens/settings.h"
#include "./Screens/login.h"
#include "./Screens/gameOver.h"
#include "./Screens/smallPopup.h"


int main()
{
    RenderWindow window(sf::VideoMode({1000, 700}), "Game Menu", Style::Close);
    mainMenu_Initial(window);
    leaderBoards_Initial(window);
    game_Initial(window);
    settings_Initializer(window);
    login_Initial(window);
    pauseScreen_Initial(window);
    gameOverInitializer(window);
    popUp_Initializer(window);


    extern int switcher; // Declared in pauseScreen.h
    bool justEntered = true;
    extern Clock timeElapsedInGame; // Declared in gamePlay.h;
    extern bool hasLoggedIn;
    extern bool isPlaying; // Declared in mainMenu.h

    while (window.isOpen())
    {

        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                if(isPlaying && !gameOver){
                    referenceFuncionToStoreNames();
                }
                window.close();
            }

            int result = 40;
            if(!switcher){
                result = mainMenuEventHandler(window, *event , switcher); // result = 10
            }
            else if(switcher==5){
                popupEventHandler(window, *event);
            }
            else if(switcher == 10){
                gEvHandler(window , *event);
            }
            else if(switcher == 20){
                leaderBoards_eventHandler(window , *event);
            }
            else if(switcher == 30){
                settingsEventHandler(window , *event);
            }

            if (result != 40){
                switcher = result; // 10 in switcher
            }
        }


        window.clear();
        if (switcher == 10)
        {
            gameDrawer(window , timeElapsedInGame);
        }
        else if (switcher == 20)
        {
            lbDrawer(window);
        }
        else if (switcher == 30)
        {
            settingsDrawer(window);
        }
        else
        {
            WindowDrawer(window);
            if(switcher==5){
                popupDrawer(window);
            }
        }
        window.display();
    }
}
