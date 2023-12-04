#include "SplashWindow.h"

SplashWindow::SplashWindow(GameApplication& application)
    :
    SfmlWindow("BattleShip", WindowSettings().menuWindowSize),
    application(&application)
{
    Initialize();
}

SplashWindow::~SplashWindow()
{
    running = false;
}

void SplashWindow::Initialize()
{
    entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(1333, 749), sf::Vector2f(0, 0)));
    entitiesPtr.at(0)->setColor(sf::Color::Black);
    for (int i = 0; i < 2; i++)
    {
        SplashTexture[i].loadFromFile(splashObj.SplashImgPath[i]);
    }
    
    for (int i = 0; i < 2; i++)
    {
        Logo.push_back(EntityRectangle(sf::Vector2f(350, 350), sf::Vector2f(666, 374), splashObj.SplashImgPath[i], sf::Vector2f(175, 175)));
        Logo.at(i).setTexture(&SplashTexture[i]);
    }
}

void SplashWindow::HandleEvents(sf::Event& event) {
   
}

void SplashWindow::Update() {

    if (started)
        return;

    started = true;
    SplashAnim();
}

void SplashWindow::Render() {
    // Render the black background
    for (auto& entity : entitiesPtr)
        entity->draw(window);

    // Render only the current logo
    Logo.at(currentLogoIndex).draw(window);
}

void SplashWindow::SplashAnim()
{
    float timeElapsed = clockSplash.getElapsedTime().asSeconds();
    bool L1 = false; // logo 1 pas encore passé
    bool L2 = false; // logo 2 pas encore passé

    if (timeElapsed >= 5.0f) {
        clockSplash.restart();
        currentLogoIndex = (currentLogoIndex + 1) % 2;
    }

    // Calcul de l'opacité pour le fondu
    float alpha;
    if (timeElapsed < fadeDuration) {
        // Fondu entrant sur le nouveau logo
        alpha = (timeElapsed / fadeDuration) * 255;
    }
    else if (timeElapsed > 5.0f - fadeDuration) {
        // Fondu sortant sur l'ancien logo
        alpha = ((5.0f - timeElapsed) / fadeDuration) * 255;
    }
    else {
        // Opacité complète en dehors du fondu
        alpha = 255;
    }

    // Application de l'opacité aux logos
    for (int i = 0; i < Logo.size(); i++) {
        sf::Color color = Logo[i].getColor();
        color.a = (i == currentLogoIndex) ? alpha : 255 - alpha;
        Logo[i].setColor(color);
    }
    L1 = true; // logo 1  passé
    L2 = true; // logo 2 passé

    if (L1 && L2) {
        running = false;
        application->ChangeState(GameApplication::State::Menu);
    }
}
