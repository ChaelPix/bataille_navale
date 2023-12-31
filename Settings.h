#pragma once

#include <SFML/Graphics.hpp>


//Local
//struct NetworkSettings {
//    const bool isLocal = true;
//    const std::string bddSchema = "batailleNavale_b";
//    const std::string bddIp = "tcp://10.187.52.4:3306";
//    const std::string bddLogin = "batailleNavale";
//    const std::string bddMdp = "batailleNavale";
//
//    const std::string serverIp = "";
//    const int serverPort = 12345;
//};

//Public
struct NetworkSettings {
    const bool isLocal = false;
    const std::string bddSchema = "bataille";
    const std::string bddIp = "tcp://135.125.103.133:3306";
    const std::string bddLogin = "bataille";
    const std::string bddMdp = "batailleSNIR";

    const std::string serverIp = "135.125.103.133";
    const int serverPort = 55555;
};

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

struct GameSettings
{
    const int timeToPlaceBoat = 15;
    const int timeToSync = 1;
    const int timeToPlay = 10;
};

struct BackgroundSettings
{
    const int nbMenuImgs = 50;
    const int nbGameImgs = 59;

    const std::string menupath = "ressources/UI/backgrounds/menuBg/menu_";
    const std::string gamepath = "ressources/UI/backgrounds/waterBg/water_";
};

struct GameMenuSettings {

    const WindowSettings ws;
    const sf::Vector2f timerBgSize = sf::Vector2f(523, 179);
    sf::Vector2f timerBgPos = sf::Vector2f(ws.gameWindowSize.x / 2 - timerBgSize.x / 2, 0);
    const std::string timerbgPath = "ressources/UI/ui_timer_bg.png";

    const int timerTxtSize = 75;
    sf::Vector2f txtCenter = sf::Vector2f(ws.gameWindowSize.x / 2, 0);

    const int nbTurnSize = 35;
    const int gameInfoTxtSize = 50;
    const sf::Color txtColor = sf::Color(200, 200, 200);
   /* sf::Vector2f nbTurnpos = sf::Vector2f(ws.gameWindowSize.x / 2, 0);
    sf::Vector2f gameInfoTxtpos = sf::Vector2f(ws.gameWindowSize.x / 2, 0);*/

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
    const sf::Vector2f textBoxSize = sf::Vector2f(430, 50);
    const sf::Vector2f selectBoxSize = sf::Vector2f(450, 5);
    const sf::Vector2f selectBoxOffset = sf::Vector2f(0, 5);
    const sf::Color selectBoxColor = sf::Color::Blue;
    const sf::Color defaultTextColor = sf::Color(124, 124, 124, 200);
    const int maxCharacterSize = 40;
    const int minCharacterSize = 3;
    const int timeCooldownTyping = 100;
};

struct LoginMenuSettings {
    const sf::Vector2f usernameTextBoxPos = sf::Vector2f(400, 200);
    const sf::Vector2f passwordTextBosPos = sf::Vector2f(400, 300);

    const sf::Vector2f backgroundMenuPos = sf::Vector2f(350, 50);
    const sf::Vector2f backgroundMenuSize = sf::Vector2f(600, 400);
    const std::string backgroundMenuPath = "ressources/UI/ui_menuBg.png";

    const sf::Vector2f buttonPos = sf::Vector2f(530, 365);
    const sf::Vector2f buttonSize = sf::Vector2f(228, 80);
    const std::string buttonImagePaths[2] = {
      "ressources/UI/ui_menu_loginbutton_off.png",
      "ressources/UI/ui_menu_loginbutton_on.png"
    };

    const sf::Vector2f textPosition = sf::Vector2f(400, 100);
    const int characterSize = 40;

    const sf::Vector2f startTextPos = sf::Vector2f(300, 500);
    const int startTextCharacterSize = 72;
};


struct EndMenuSettings {

    const sf::Vector2f panelSize = sf::Vector2f(1600, 850);
    const sf::Color panelColor = sf::Color(0, 0, 0, 200);

    const sf::Vector2f imagePos = sf::Vector2f(400, 50);
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

    const int scoreSize = 35;
    const sf::Vector2f scorePos = sf::Vector2f(542, 550);

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
    const int nbMiss = 3;
    const std::string attackMissPath = "ressources/UI/vfx/vfx_Miss_";

    const sf::Vector2f attackTextureSize = sf::Vector2f(112, 112);
};

struct LockerSettings {

    const int nbImages = 48;
    std::string path[48];
    sf::Font font;

    LockerSettings() {
        font.loadFromFile("ressources/fonts/AGENCYB.TTF");
        for (int i = 0; i < nbImages; i++)
            path[i] = "ressources/profilPictures/caractere" + std::to_string(i + 1) + ".jpg";
    }
    std::string sectionName[10] = {
        "   Air forces",
        "Tactical armies",
        "Pilot in command",
        "     Crews",
        "Force of armies",
        "   Military",
        "   Hostages",
        "   Soldiers",
        "   Specials",
        "This place is your locker, you can change clothes whenever you like"
    };

    const sf::Vector2f textPosition[10] = {
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(580, 5), 
        sf::Vector2f(200, 260), 
    };
    const int characterSize = 40;

    const sf::Vector2f startTextPos = sf::Vector2f(300, 500);
    const int startTextCharacterSize = 72;

    std::string backgroundImgPath = "ressources/UI/backgroundLocker2.png";
    std::string valideTextureImgPath = "ressources/UI/valide.png";

};

struct PlayerHUDSettings {

    const sf::Vector2f hudSize = sf::Vector2f(1600, 213);
    const std::string hudPath = "ressources/UI/ui_playersPanel.png";

    const int nameSize = 80;
    const int kdSize = 25;
    const int scoreSize = 30;

    const int pictureSize = 70;
    const sf::Vector2f picturePos = sf::Vector2f(25, 25);

    const sf::Color nameColor = sf::Color(255, 255, 255);
    const sf::Color kdColor = sf::Color(180, 180, 180);
    const sf::Color scoreColor = sf::Color(200, 200, 200);

    const sf::Vector2f namePos = sf::Vector2f(180, 0);
    const sf::Vector2f scorePos = sf::Vector2f(180, 120);
    const sf::Vector2f kdPos = sf::Vector2f(180, 95);

};

struct sfxSettings {

    std::string pathBGM = "ressources/UI/sfx/music_background.wav";
    std::string pathGME = "ressources/UI/sfx/music_game2.wav";
    std::string pathLocker = "ressources/UI/sfx/sfx_boatLocker.wav";

    std::string pathClick = "ressources/UI/sfx/sfx_click.wav";
    std::string pathExplosion = "ressources/UI/sfx/sfx_explosion.wav"; 
    std::string pathsinkBoat = "ressources/UI/sfx/sfx_sinkBoat_voice.wav"; 
    std::string pathVictory = "ressources/UI/sfx/sfx_victory.wav";
    std::string pathDefeat = "ressources/UI/sfx/sfx_defeat.wav";
    std::string pathVoicVictory = "ressources/UI/sfx/sfx_congratulation_voice.wav";
    std::string pathVoicDefeat = "ressources/UI/sfx/sfx_defeat_voice.wav";
    std::string pathWater = "ressources/UI/sfx/sfx_water-explosion.wav";
    std::string pathWrong = "ressources/UI/sfx/sfx_wrong.wav";
    const sf::Vector2f namePos = sf::Vector2f(0, 25);
    const sf::Vector2f kdPos = sf::Vector2f(0, 25);
    const sf::Vector2f scorePos = sf::Vector2f(0, 25);

};

struct GameChatSettings {
    const sf::Vector2f chatPos = sf::Vector2f(1220, 350);
    const sf::Vector2f chatSize = sf::Vector2f(380, 480);
    const sf::Vector2f textBoxPosFromChat = sf::Vector2f(0, 450);

    const sf::Vector2f messageSize = sf::Vector2f(360, 100);
    const sf::Vector2f messageOffset = sf::Vector2f(0, -20);
    const sf::Vector2f messageOffsetFromName = sf::Vector2f(0, 25);
    const sf::Vector2f firsMessagePosFromtxtBox = sf::Vector2f(15, -100);
    const float maxY = 350;
    const int nameFSize = 20;
    const int messageFSize = 30;
    std::string pathChatBox = "ressources/UI/ui_chatbox.png";
    sf::Color nameEColor = sf::Color(153, 0, 0);
    sf::Color namePColor = sf::Color(255, 198, 7);
    sf::Color messageColor = sf::Color(255, 255, 255);
};