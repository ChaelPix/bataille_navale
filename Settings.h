#pragma once

#include <SFML/Graphics.hpp>

struct GridSettings {
    const int squareSize = 500;
    const int nbPixels = 10;
    const int fps = 15;
    const sf::Color lineColor = sf::Color(0, 0, 0, 255);

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
    float anglesDegres[40] = {
        15,
        58,
        45,
        25,
        38,
        46,
        95,
        71,
        82,
        5,
        45,
        285,
        586,
        142,
        567,
        156,
        75,
        665,
        152,
        574,
        15,
        58,
        45,
        25,
        38,
        46,
        95,
        71,
        82,
        5,
        45,
        285,
        586,
        142,
        567,
        156,
        75,
        665,
        152,
        574,
    };
    const sf::Vector2f cloudPosition[40] = {
         sf::Vector2f(1500, 80),
         sf::Vector2f(1448, 756),
         sf::Vector2f(1246, 2),
         sf::Vector2f(1472, 452),
         sf::Vector2f(1528, 856),
         sf::Vector2f(1329, 80),
         sf::Vector2f(1483, 58),
         sf::Vector2f(1327, 452),
         sf::Vector2f(1272, 185),
         sf::Vector2f(137, 681),
         sf::Vector2f(1600, 80),
         sf::Vector2f(1348, 624),
         sf::Vector2f(1285, 2),
         sf::Vector2f(1354, 284),
         sf::Vector2f(1501, 146),
         sf::Vector2f(1385, 146),
         sf::Vector2f(1443, 158),
         sf::Vector2f(1685, 274),
         sf::Vector2f(1354, 345),
         sf::Vector2f(1124, 457), //
sf::Vector2f(783, 626),
sf::Vector2f(910, 68),
sf::Vector2f(855, 196),
sf::Vector2f(970, 721),
sf::Vector2f(803, 145),
sf::Vector2f(1062, 417),
sf::Vector2f(1251, 427),
sf::Vector2f(1256, 11),
sf::Vector2f(705, 87),
sf::Vector2f(1287, 811),
sf::Vector2f(1161, 333),
sf::Vector2f(936, 847),
sf::Vector2f(1175, 270),
sf::Vector2f(949, 656),
sf::Vector2f(1236, 352),
sf::Vector2f(867, 96),
sf::Vector2f(818, 699),
sf::Vector2f(1143, 570),
sf::Vector2f(1286, 538),
sf::Vector2f(826, 307),


    };

struct SplashSettings {

    const std::string SplashImgPath[2] = {
        "ressources/logo/logo_stein.png",
        "ressources/logo/logo_chaelPix.png",
    };
    const int explodeOpacitySpeed = 10;
    const float minExplodeOpacity = 0;

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
