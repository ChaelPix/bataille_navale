#include"LockerWindow.h"

LockerWindow::LockerWindow(GameApplication& application, const sf::Vector2i& windowPos)
    :
    SfmlWindow("BattleShip locker", WindowSettings().menuWindowSize, windowPos), application(&application)
{
    Initialize();
}

LockerWindow::~LockerWindow()
{
    running = false;
}

void LockerWindow::Initialize()
{
    //entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(523, 749), sf::Vector2f(windowSettings.gameWindowSize.x - 780, 0), "ressources/UI/ui_menu_sideMenu.png"));
    //menuButtonsManager = new MenuButtonsManager(application->getGameFont());
    // Boucle pour initialiser 8 cl�s � 'true'

    //Music
    if (!music.openFromFile("ressources/UI/sfx/sfx_boatLocker.wav")) {
    }
    music.play();
    music.setLoop(true);

    BackgroundTexture.loadFromFile(LckSettings.backgroundImgPath);
    Background = new EntityRectangle(ws.gameWindowSize, sf::Vector2f(0, 0), BackgroundTexture);

    validPos = sf::Vector2f(100, 100);

    //img valide
    valideTexture.loadFromFile(LckSettings.valideTextureImgPath);
    valide = new EntityRectangle(sf::Vector2f(30, 30), validPos, valideTexture);


    //movement
    initialPosition = sf::Vector2f(0, 0); // Replace with actual initial position
    swaySpeed = 1.0f;                     // Replace with desired speed
    swayMagnitude = 10.0f;                // Replace with desired magnitude



      for (int i = 0; i < 9; i++){
          textInfo.push_back(new EntityText(LckSettings.font, LckSettings.textPosition, LckSettings.characterSize, LckSettings.sectionName[i]));
      }

    // Chargement et configuration des textures et sprites des boutons
    if (!buttonPrevTexture.loadFromFile("ressources/UI/ui_locker_previousbutton_on.png") ||
        !buttonNextTexture.loadFromFile("ressources/UI/ui_locker_nextbutton_on.png")) {
        std::cout << "error loading: ressources/UI/ui_menu_playbutton_on.png" << std::endl;
    }

    buttonPrevSprite.setTexture(buttonPrevTexture);
    buttonPrevSprite.setPosition(sf::Vector2f(50, 370));
    buttonPrevSprite.setScale(sf::Vector2f(0.5, 0.5));

    buttonNextSprite.setTexture(buttonNextTexture);
    buttonNextSprite.setPosition(sf::Vector2f(1220, 370));
    buttonNextSprite.setScale(sf::Vector2f(0.5, 0.5));

    for (int i = 0; i < 9; ++i) {
        std::string key = "section" + std::to_string(i + 1);
        lockerSection[key] = false;
    }
    lockerSection["section1"] = true;
    //la section 1 va de 0 a 4, ce qui vaux l = 5 boucle, l pour loop, les sections ressemblent donc a �a: [0-4], [5-8], [9-10], [11-17], [18-22], [23-27], [28-30], [31-38]

    // D�finitions des marges et taille des images
    float new_image_width = 304.8f;  // Largeur de l'image apr�s la mise � l'�chelle
    float new_image_height = 304.8f; // Hauteur de l'image apr�s la mise � l'�chelle
    float margin_each_side = 27.8f;  // Marge sur les c�t�s
    float margin_each_top_bottom = 65.8f; // Marge en haut et en bas

    // Tableau indiquant l'indice de d�but de chaque section
    //int section_starts[] = { 0, 5, 9, 12, 19, 23, 29, 32, 40 };

    // Boucle sur toutes les images
    for (int i = 0; i < 48; ++i) {
        // Trouvez la section actuelle en fonction de l'indice 'i'
        int section = 0;
        while (i >= section_starts[section + 1]) {
            section++;
        }

        // Calculez la position dans la section (l'indice relatif � la section)
        int index_in_section = i - section_starts[section];

        // Calculez la position en x et y en tenant compte du d�but d'une nouvelle section
        float pos_x = (index_in_section % 4) * (new_image_width + margin_each_side) + margin_each_side;
        float pos_y = (index_in_section / 4) * (new_image_height + margin_each_top_bottom) + margin_each_top_bottom;

        // Ajoutez la nouvelle entit� � la fin du vecteur
        entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(280, 280), sf::Vector2f(pos_x, pos_y), LckSettings.path[i]));
    }
    
}

void LockerWindow::HandleEvents(sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            
            for (int i = p; i < p + l; ++i) {
                if (i < entitiesPtr.size()) {
                    auto entity = entitiesPtr.at(i);
                    if (entity->getShape().getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                        pictureChoose = i; 
                        std::cout << "Image " << i << " cliqu�e" << std::endl;

                        // Mettre � jour validPos avec la position de l'image cliqu�e
                        validPos = entity->getPosition(); // Assurez-vous que votre entit� a une m�thode getPosition()

                        // Mettre � jour la position de l'entit� 'valide' avec la nouvelle position
                        valide->setPosition(validPos);
                        imageSelected = true;
                        break;
                    }
                }
            }


            // V�rifier le clic sur le bouton pr�c�dent
            if (buttonPrevSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::max(0, currentSectionIndex - 1); // Ne pas aller en dessous de 0
                UpdateSectionState();
            }
            // V�rifier le clic sur le bouton suivant
            else if (buttonNextSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::min(8, currentSectionIndex + 1); // Ne pas d�passer 8
                UpdateSectionState();
            }
            
        }
    }
}

void LockerWindow::UpdateSectionState() {
    // Mettre toutes les cl�s � false
    for (auto& pair : lockerSection) {
        pair.second = false;
    }

    // Mettre la cl� de la section actuelle � true
    std::string key = "section" + std::to_string(currentSectionIndex + 1);
    lockerSection[key] = true;
}

void LockerWindow::LockerManagement() {

    if (lockerSection["section1"]) {
        p = 0; l = 5, s = 1;
    }
    else if (lockerSection["section2"]) {
        p = 5; l = 4, s = 2;
    } 
    else if (lockerSection["section3"])
        p = 9, l = 3, s = 3;
    else if (lockerSection["section4"])
        p = 12, l = 7, s = 4;
    else if (lockerSection["section5"])
        p = 19, l = 4, s = 5;
    else if (lockerSection["section6"])
        p = 23, l = 6, s = 6;
    else if (lockerSection["section7"])
        p = 29, l = 3, s = 7;
    else if (lockerSection["section8"])
        p = 32, l = 8, s = 8;
    else if (lockerSection["section9"])
        p = 40, l = 8, s = 9;

    for (int i = p; i < p + l; ++i) {
        if (i < entitiesPtr.size()) {
            entitiesPtr.at(i)->draw(window);
        }
    }

    textInfo.at(s - 1)->draw(window);

}


void LockerWindow::Update(sf::Event& event) {
    
}

//movement
void LockerWindow::UpdatePos(sf::Time deltaTime) {
    static float time = 0.0f;
    time += deltaTime.asSeconds();

    float swayAmount = sin(time * swaySpeed) * swayMagnitude;
    Background->setPosition(initialPosition + sf::Vector2f(swayAmount, 0));
}

void LockerWindow::debug() {
    // R�initialisation de l'�tat des sections
    for (auto& pair : lockerSection) {
        pair.second = false;
    }

    int debug = 0;
    std::cout << "Enter section number to display: ";
    std::cin >> debug; // Assurez-vous que cette entr�e fonctionne correctement dans votre environnement.

    // Utilisation d'une structure switch pour plus de clart�
    switch (debug) {
    case 1: lockerSection["section1"] = true; break;
    case 2: lockerSection["section2"] = true; break;
    case 3: lockerSection["section3"] = true; break;
    case 4: lockerSection["section4"] = true; break;
    case 5: lockerSection["section5"] = true; break;
    case 6: lockerSection["section6"] = true; break;
    case 7: lockerSection["section7"] = true; break;
    case 8: lockerSection["section8"] = true; break;
    case 9: lockerSection["section9"] = true; break;
    default: std::cout << "Invalid section number." << std::endl;
    }
}

void LockerWindow::Render()
{
    Background->draw(window);

    if (!running)
        return;
    LockerManagement();

    //movement
    sf::Time deltaTime = clock.restart();
    UpdatePos(deltaTime);

    // Dessiner les boutons
    window.draw(buttonPrevSprite);
    window.draw(buttonNextSprite);

    if (imageSelected) {
        int sectionStartIndex = section_starts[currentSectionIndex];
        int sectionEndIndex = (currentSectionIndex < 8) ? section_starts[currentSectionIndex + 1] - 1 : 47;

        if (pictureChoose >= sectionStartIndex && pictureChoose <= sectionEndIndex) {
            valide->draw(window);
        }
        // Pas de r�initialisation de imageSelected ici
    }


}
