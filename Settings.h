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
    "ressources/UI/ui_menu_cancelbutton_off.png",
    "ressources/UI/ui_menu_cancelbutton_on.png"
    };

    const sf::Vector2f matchmakingTxtPos = sf::Vector2f(150, 200);
    const int matchmakingTxtFontSize = 120;

    const int matchmakingPointTimer = 500;
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
    const sf::Vector2f usernameTextBoxPos = sf::Vector2f(200, 300);
    const sf::Vector2f passwordTextBosPos = sf::Vector2f(200, 400);
    const sf::Vector2f buttonPos = sf::Vector2f(200, 500);

    const sf::Vector2f buttonSize = sf::Vector2f(228, 80);

    const std::string buttonImagePaths[2] = {
  "ressources/UI/ui_menu_playbutton_off.png",
  "ressources/UI/ui_menu_playbutton_on.png"
    };
};