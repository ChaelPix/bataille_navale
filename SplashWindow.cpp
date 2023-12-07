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

void SplashWindow::Update(sf::Event& event) {
    if (started) {
        application->ChangeState(GameApplication::State::Menu);
        return;
    }

    SplashAnim();

    // Vérifier si les deux logos ont été affichés
    if (L1 && L2) {
        started = true;
    }
}

void SplashWindow::Render() {
    // Render the black background
    for (auto& entity : entitiesPtr)
        entity->draw(window);

    // Render only the current logo
    Logo.at(currentLogoIndex).draw(window);
}

void SplashWindow::SplashAnim() {
    float timeElapsed = clockSplash.getElapsedTime().asSeconds();

    // Gérer le changement de logo
    if (timeElapsed >= 5.0f) {
        clockSplash.restart();
        if (currentLogoIndex == 0) {
            L1 = true;  // Marquer le premier logo comme affiché
        }
        if (currentLogoIndex == 1) {
            L2 = true;  // Marquer le deuxième logo comme affiché
        }
        currentLogoIndex = (currentLogoIndex + 1) % 2;
    }

    // Gérer l'opacité pour le fondu
    float alpha;
    if (timeElapsed < fadeDuration) {
        alpha = (timeElapsed / fadeDuration) * 255;
    }
    else if (timeElapsed > 5.0f - fadeDuration) {
        alpha = ((5.0f - timeElapsed) / fadeDuration) * 255;
    }
    else {
        alpha = 255;
    }

    // Appliquer l'opacité aux logos
    for (int i = 0; i < Logo.size(); i++) {
        sf::Color color = Logo[i].getColor();
        color.a = (i == currentLogoIndex) ? alpha : 255 - alpha;
        Logo[i].setColor(color);
    }
}