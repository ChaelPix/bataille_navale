#pragma once

#include <SFML/Graphics.hpp>

struct GridSettings {
    const int squareSize = 500;
    const int nbPixels = 10;
    const int fps = 15;
    const sf::Color lineColor = sf::Color(255, 0, 0, 255);

    const sf::Vector2f playerGridPosition = sf::Vector2f(100, 200);
    const sf::Vector2f ennemyGridPosition = sf::Vector2f(700, 200);

    const int boatTolerance = 15;
};

struct WindowSettings {
    const sf::Vector2f gameWindowSize = sf::Vector2f(1600, 850);
    const sf::Vector2f menuWindowSize = sf::Vector2f(1333, 749);
    const sf::Color bgColor = sf::Color::Black;
};

struct MenuButtonsSettings {
    const sf::Vector2f buttonsSize = sf::Vector2f(228, 80);
    const sf::Vector2f buttonsStartPos = sf::Vector2f(990, 420);
    const int distanceBetweenButtons = 25;

    const std::string buttonImagePaths[8] = {
    "ressources/UI/ui_menu_playbutton_off.png",
    "ressources/UI/ui_menu_playbutton_on.png",
    "ressources/UI/ui_menu_shopbutton_off.png",
    "ressources/UI/ui_menu_shopbutton_on.png",
    "ressources/UI/ui_menu_exitbutton_off.png",
    "ressources/UI/ui_menu_exitbutton_on.png",
    "ressources/UI/ui_menu_matchbutton_off.png",
    "ressources/UI/ui_menu_matchbutton_on.png"
    };

    const sf::Vector2f matchmakingTxtPos = sf::Vector2f(150, 200);
    const int matchmakingTxtFontSize = 120;

    const int matchmakingPointTimer = 500;
};

struct MenuServerInfoTextSettings
{
    const sf::Vector2f textPosition = sf::Vector2f(50, 650);
    const int characterSize = 50;
};

struct PlayerInfoSettings {

    const int characterSize = 39;

    const sf::Vector2f textPosition = sf::Vector2f(1000, 110);
    const sf::Vector2f textOffset = sf::Vector2f(0, 40);

    const sf::Color textColors[6] =
    {
        sf::Color(192, 192, 192),
        sf::Color(204, 102, 0),
        sf::Color(180, 180, 180),
        sf::Color(0, 150, 0),
        sf::Color(150, 0, 0),
        sf::Color(192, 192, 192)
    };
};

struct CloudSettings {
    const sf::Vector2f cloudSize = sf::Vector2f(2500, 2500);
    const sf::Vector2f Origin = sf::Vector2f(cloudSize.x/ 2, cloudSize.y / 2);
    float anglesDegresAnimate = 0;
    const sf::Vector2f cloudPositionAnimate[2] = { sf::Vector2f(0, -400), sf::Vector2f(2100, -400) };

     const int explodeOpacitySpeed = 10;
    const float minExplodeOpacity = 0;

    const std::string cloudImgPath = "ressources/UI/cloud.png";
    const std::string cloudImgPath2 = "ressources/UI/cloud2.png";
    };

struct SplashSettings {
    const std::string SplashImgPath[2] = {
        "ressources/logo/logo_stein.png",
        "ressources/logo/logo_chaelPix.png",
    };
};

struct FontSettings {
    const std::string fontPath = "ressources/fonts/AGENCYB.TTF";
};

struct BoatSettings {
    const std::string boatTexturePaths[4] = {
   "ressources/UI/ui_boat_aircraftcarrier.png",
   "ressources/UI/ui_boat_croisor.png",
   "ressources/UI/ui_boat_antitorpillor.png",
   "ressources/UI/ui_boat_destroyer.png"
    };
};

struct TextBoxSettings {
    const sf::Vector2f textBoxSize = sf::Vector2f(500, 50);
    const sf::Vector2f selectBoxSize = sf::Vector2f(500, 5);
    const sf::Vector2f selectBoxOffset = sf::Vector2f(0, 5);
    const sf::Color selectBoxColor = sf::Color::Blue;
    const sf::Color defaultTextColor = sf::Color(124, 124, 124, 200);
    const int maxCharacterSize = 40;
    const int minCharacterSize = 3;
    const int timeCooldownTyping = 75;
};

struct LoginMenuSettings {
    const sf::Vector2f usernameTextBoxPos = sf::Vector2f(400, 300);
    const sf::Vector2f passwordTextBosPos = sf::Vector2f(400, 400);

    const sf::Vector2f backgroundMenuPos = sf::Vector2f(350, 150);
    const sf::Vector2f backgroundMenuSize = sf::Vector2f(600, 500);
    const std::string backgroundMenuPath = "ressources/UI/ui_menuBg.png";

    const sf::Vector2f buttonPos = sf::Vector2f(530, 500);
    const sf::Vector2f buttonSize = sf::Vector2f(228, 80);
    const std::string buttonImagePaths[2] = {
      "ressources/UI/ui_menu_loginbutton_off.png",
      "ressources/UI/ui_menu_loginbutton_on.png"
    };

    const sf::Vector2f textPosition = sf::Vector2f(400, 200);
    const int characterSize = 40;

    const sf::Vector2f startTextPos = sf::Vector2f(300, 500);
    const int startTextCharacterSize = 72;
};


struct EndMenuSettings {

    const sf::Vector2f panelSize = sf::Vector2f(1300, 850);
    const sf::Color panelColor = sf::Color(0, 0, 0, 200);

    const sf::Vector2f imagePos = sf::Vector2f(400, 100);
    const sf::Vector2f imageSize = sf::Vector2f(512, 512);
    const std::string endImagesPath[2] = {
      "ressources/UI/ui_defeat.png",
      "ressources/UI/ui_victory.png"
    };

    const sf::Vector2f buttonPos = sf::Vector2f(542, 700);
    const sf::Vector2f buttonSize = sf::Vector2f(228, 80);
    const std::string buttonImagePaths[2] = {
      "ressources/UI/ui_menu_exitbutton_off.png",
      "ressources/UI/ui_menu_exitbutton_on.png"
    };
};

struct GameVFXSettings
{
    const std::string missImagePath = "ressources/UI/ui_miss.png";
    const int attacksTimer = 125;
    const std::string attacksPath = "ressources/UI/vfx/vfx_attack";
    const int fireTimer = 350;
    const int nbEnemyFire = 2;
    const std::string enemyFirePath = "ressources/UI/vfx/vfx_ennemyFire";
    const int nbPlayerFire = 8;
    const std::string playerFirePath = "ressources/UI/vfx/vfx_playerFire";
    const sf::Vector2f attackTextureSize = sf::Vector2f(112, 112);
};

struct LockerSettings {

    const int nbImages = 48;
    std::string path[48];
    sf::Font font;

    LockerSettings() {
        font.loadFromFile("ressources/fonts/AGENCYB.TTF");
        for (int i = 0; i < nbImages; i++)
            path[i] = "ressources/profilPictures/caractere" + std::to_string(i + 1) + ".png";
    }
    std::string sectionName[9] = {
        "   air forces",
        "Tactical armies",
        "pilot in command",
        "     crews",
        "force of armies",
        "   miliary",
        "   hostages",
        "   soldiers",
        "   specials",
    };

    const sf::Vector2f textPosition = sf::Vector2f(580, 5);
    const int characterSize = 40;

    const sf::Vector2f startTextPos = sf::Vector2f(300, 500);
    const int startTextCharacterSize = 72;

};