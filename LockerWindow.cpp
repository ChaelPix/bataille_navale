#include"LockerWindow.h"

LockerWindow::LockerWindow(GameApplication& application, const sf::Vector2i& windowPos)
    :
    SfmlWindow("Valiant", WindowSettings().menuWindowSize, windowPos), application(&application)
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
    // Boucle pour initialiser 8 clés à 'true'
    phaseOffset = 3.14159f / 2;
    bdd = &application->getBddObj();
    ////Music
    //if (!music.openFromFile("ressources/UI/sfx/sfx_boatLocker.wav")) {
    //}
    //music.play();
    //music.setLoop(true);

    scoreText = new EntityText(LckSettings.font, sf::Vector2f(1200, 5), LckSettings.characterSize, bdd->getScore());

    BackgroundTexture.loadFromFile(LckSettings.backgroundImgPath);
    Background = new EntityRectangle(ws.gameWindowSize, sf::Vector2f(-50, -50), BackgroundTexture);

    validPos = sf::Vector2f(100, 100);

    //img valide
    valideTexture.loadFromFile(LckSettings.valideTextureImgPath);
    valide = new EntityRectangle(sf::Vector2f(30, 30), validPos, valideTexture);


    //movement
    initialPosition = sf::Vector2f(0, 0); // Replace with actual initial position
    swaySpeed = 1.0f;                     // Replace with desired speed
    swayMagnitude = 10.0f;                // Replace with desired magnitude



      for (int i = 0; i < 10; i++){
          textInfo.push_back(new EntityText(LckSettings.font, LckSettings.textPosition[i], LckSettings.characterSize, LckSettings.sectionName[i]));
      }

      //float new_image_width = 304.8f; 
      //float new_image_height = 304.8f; 
      //float margin_each_side = 27.8f; 
      //float margin_each_top_bottom = 65.8f;

      //charactersImgs = &application->getCharactersImgs();

      //for (int i = 0; i < 48; ++i) {
      //    int section = 0;
      //    while (i >= section_starts[section + 1]) {
      //        section++;
      //    }

      //    int index_in_section = i - section_starts[section];

      //    float pos_x = (index_in_section % 4) * (new_image_width + margin_each_side) + margin_each_side;
      //    float pos_y = (index_in_section / 4) * (new_image_height + margin_each_top_bottom) + margin_each_top_bottom;
      //}

    // Chargement et configuration des textures et sprites des boutons
    if (!buttonPrevTexture.loadFromFile("ressources/UI/ui_locker_previousbutton_on.png") ||
        !buttonNextTexture.loadFromFile("ressources/UI/ui_locker_nextbutton_on.png") || !exitButtonTexture.loadFromFile("ressources/UI/ui_locker_backbutton_on.png")) {
        std::cout << "error loading: ressources/UI/ui_menu_playbutton_on.png" << std::endl;
    }

    buttonPrevSprite.setTexture(buttonPrevTexture);
    buttonPrevSprite.setPosition(sf::Vector2f(50, 370));
    buttonPrevSprite.setScale(sf::Vector2f(0.5, 0.5));

    buttonNextSprite.setTexture(buttonNextTexture);
    buttonNextSprite.setPosition(sf::Vector2f(1220, 370));
    buttonNextSprite.setScale(sf::Vector2f(0.5, 0.5));

    exitButtonSprite.setTexture(exitButtonTexture);
    exitButtonSprite.setPosition(sf::Vector2f(2, 2));
    exitButtonSprite.setScale(sf::Vector2f(0.5, 0.5));

    for (int i = 0; i < 10; ++i) {
        std::string key = "section" + std::to_string(i);
        lockerSection[key] = false;
    }
    lockerSection["section0"] = true;
    //la section 1 va de 0 a 4, ce qui vaux l = 5 boucle, l pour loop, les sections ressemblent donc a ça: [0-4], [5-8], [9-10], [11-17], [18-22], [23-27], [28-30], [31-38]

     // Définitions des marges et taille des images
    float new_image_width = 304.8f;  // Largeur de l'image après la mise à l'échelle
    float new_image_height = 304.8f; // Hauteur de l'image après la mise à l'échelle
    float margin_each_side = 27.8f;  // Marge sur les côtés
    float margin_each_top_bottom = 65.8f; // Marge en haut et en bas

    // Tableau indiquant l'indice de début de chaque section
    //int section_starts[] = { 0, 5, 9, 12, 19, 23, 29, 32, 40 };
    std::vector<sf::Vector2f> imagePositions;

    // Boucle sur toutes les images
    charactersImgs = &application->getCharactersImgs();
    for (int i = 0; i < 48; ++i) {
        // Trouvez la section actuelle en fonction de l'indice 'i'
        int section = 0;
        while (i >= section_starts[section + 1]) {
            section++;
        }

        // Calculez la position dans la section (l'indice relatif à la section)
        int index_in_section = i - section_starts[section];

        // Calculez la position en x et y en tenant compte du début d'une nouvelle section
        float pos_x = (index_in_section % 4) * (new_image_width + margin_each_side) + margin_each_side;
        float pos_y = (index_in_section / 4) * (new_image_height + margin_each_top_bottom) + margin_each_top_bottom;


        // Ajoutez la nouvelle entité à la fin du vecteur
        entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(280, 280), sf::Vector2f(pos_x, pos_y), charactersImgs->at(i)));
        textInfoShop.push_back(new EntityText(LckSettings.font, sf::Vector2f(pos_x, pos_y), LckSettings.characterSize, std::to_string(imageNumbers[i])));

        pictureChoose = application->getBddObj().getIdPicture();
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
                        std::cout << "Le prix de la requete vaux : " << imageNumbers[i] << " a l'emplacement: " << i << " du vecteur, et le score de la bdd vaux: " << stoi(application->getBddObj().getScore()) << std::endl;
                        if (imageNumbers[i] <= stoi(application->getBddObj().getScore())) {
                            pictureChoose = i;
                            bdd->setIdPicture(pictureChoose);
                            std::cout << "Image " << pictureChoose << " cliquée" << std::to_string(bdd->getIdPicture()) << std::endl;
                            // Mettre à jour validPos avec la position de l'image cliquée
                            validPos = entity->getPosition(); // Assurez-vous que votre entité a une méthode getPosition()
                            application->fxobj->createSfx(SfxManager::sfx::click);
                            application->fxobj->setSfxVolume(100);
                            // Mettre à jour la position de l'entité 'valide' avec la nouvelle position
                            valide->setPosition(validPos);
                            imageSelected = true;
                            break;
                        }
                        else 
                            application->fxobj->createSfx(SfxManager::sfx::wrong);
                    }
                }
            }


            // Vérifier le clic sur le bouton précédent
            if (buttonPrevSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::max(-1, currentSectionIndex - 1); // Ne pas aller en dessous de 0
                UpdateSectionState();
            }
            // Vérifier le clic sur le bouton suivant
            else if (buttonNextSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::min(8, currentSectionIndex + 1); // Ne pas dépasser 8
                UpdateSectionState();
            }
            // Vérifier le clic sur le back button
            else if (exitButtonSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::min(8, currentSectionIndex + 1);
                running = false;
                application->ChangeState(GameApplication::State::Menu);
                bdd->setIdPicture(pictureChoose);
                if(bdd->getIdPlayers() != "Guest")
                    bdd->saveToText();
            }
        }
    }
}

void LockerWindow::UpdateSectionState() {
    // Mettre toutes les clés à false
    for (auto& pair : lockerSection) {
        pair.second = false;
    }

    // Mettre la clé de la section actuelle à true
    std::string key = "section" + std::to_string(currentSectionIndex + 1);
    lockerSection[key] = true;
}

void LockerWindow::LockerManagement() {

    if (lockerSection["section0"]) {
        p = 0; l = 5, s = 0;
    }
    else if (lockerSection["section1"]) {
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

    if (lockerSection["section1"] || lockerSection["section2"] ||
        lockerSection["section3"] || lockerSection["section4"] ||
        lockerSection["section5"] || lockerSection["section6"] ||
        lockerSection["section7"] || lockerSection["section8"] ||
        lockerSection["section9"]) {
        for (int i = p; i < p + l; ++i) {
            if (i < entitiesPtr.size()) {
                entitiesPtr.at(i)->draw(window);
                if (i < textInfoShop.size()) {
                    textInfoShop.at(i)->draw(window);
                }
            }
        }
        textInfo.at(s - 1)->draw(window);
    }

    if (lockerSection["section0"])
    textInfo.at(9)->draw(window);
}


void LockerWindow::Update(sf::Event& event) {

}
//movement
void LockerWindow::UpdatePos(sf::Time deltaTime) {
    static float time = 0.0f;
    time += deltaTime.asSeconds();

    // Swaying side to side
    float swayAmountX = cos(time * swaySpeed) * swayMagnitude; // cos pour commencer au centre

    // Creating an arc movement
    float arcHeight = 2.0f; // hauteur de l'arc
    float a = -4 * arcHeight / (swayMagnitude * swayMagnitude);
    float b = arcHeight;
    float swayAmountY = a * swayAmountX * swayAmountX + b;

    // Adding a rotation that is in sync with the swayAmountX
    float rotationAmount = swayAmountX / swayMagnitude * maxRotationAngle; // maxRotationAngle est l'angle de rotation maximal

    // Update the position of the background with the new sway values
    Background->setPosition(initialPosition + sf::Vector2f(swayAmountX, swayAmountY));

    // Set the rotation of the background
    Background->setRotation(rotationAmount);
}





void LockerWindow::debug() {
    // Réinitialisation de l'état des sections
    for (auto& pair : lockerSection) {
        pair.second = false;
    }

    int debug = 0;
    std::cout << "Enter section number to display: ";
    std::cin >> debug; // Assurez-vous que cette entrée fonctionne correctement dans votre environnement.

    // Utilisation d'une structure switch pour plus de clarté
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
    if (!running)
    {
        music.stop();
        return;
    }

    Background->draw(window);
    LockerManagement();

    //movement
    sf::Time deltaTime = clock.restart();
    UpdatePos(deltaTime);

    // Dessiner le bouton précédent uniquement si pas dans la première section
    if (currentSectionIndex > -1) {
        window.draw(buttonPrevSprite);
    }

    // Dessiner le bouton suivant uniquement si pas dans la dernière section
    if (currentSectionIndex < 8) {
        window.draw(buttonNextSprite);
    }
    window.draw(exitButtonSprite);

    if (imageSelected) {
        int sectionStartIndex = section_starts[currentSectionIndex];
        int sectionEndIndex = (currentSectionIndex < 8) ? section_starts[currentSectionIndex + 1] - 1 : 47;

        if (pictureChoose >= sectionStartIndex && pictureChoose <= sectionEndIndex) {
            valide->draw(window);
        }
        // Pas de réinitialisation de imageSelected ici
    }
    //for (int i = 0; i < 20; i++)
    //    textInfoShop.at(i)->draw(window);
    scoreText->draw(window);


}
