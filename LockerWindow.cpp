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
    //menuBackground = new AnimatedEntity("ressources/UI/backgrounds/menuBg/menu_", 50, 28, true, windowSettings.menuWindowSize);
    // 
    //entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(523, 749), sf::Vector2f(windowSettings.gameWindowSize.x - 780, 0), "ressources/UI/ui_menu_sideMenu.png"));
    //menuButtonsManager = new MenuButtonsManager(application->getGameFont());
    // Boucle pour initialiser 8 clés à 'true'

    // Chargement et configuration des textures et sprites des boutons
    if (!buttonPrevTexture.loadFromFile("ressources/UI/ui_menu_playbutton_on.png") ||
        !buttonNextTexture.loadFromFile("ressources/UI/ui_menu_playbutton_on.png")) {
        std::cout << "error loading: ressources/UI/ui_menu_playbutton_on.png" << std::endl;
    }

    buttonPrevSprite.setTexture(buttonPrevTexture);
    buttonPrevSprite.setPosition(sf::Vector2f(50, 374));

    buttonNextSprite.setTexture(buttonNextTexture);
    buttonNextSprite.setPosition(sf::Vector2f(950, 374));

    for (int i = 0; i < 9; ++i) {
        std::string key = "section" + std::to_string(i + 1);
        lockerSection[key] = false;
    }
    lockerSection["section1"] = true;
    //la section 1 va de 0 a 4, ce qui vaux l = 5 boucle, l pour loop, les sections ressemblent donc a ça: [0-4], [5-8], [9-10], [11-17], [18-22], [23-27], [28-30], [31-38]

    // Définitions des marges et taille des images
    float new_image_width = 304.8f;  // Largeur de l'image après la mise à l'échelle
    float new_image_height = 304.8f; // Hauteur de l'image après la mise à l'échelle
    float margin_each_side = 27.8f;  // Marge sur les côtés
    float margin_each_top_bottom = 49.8f; // Marge en haut et en bas

    // Tableau indiquant l'indice de début de chaque section
    int section_starts[] = { 0, 5, 9, 13, 19, 23, 29, 32, 40 };

    // Boucle sur toutes les images
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
        entitiesPtr.push_back(new EntityRectangle(sf::Vector2f(280, 280), sf::Vector2f(pos_x, pos_y), LckSettings.path[i]));
    }
    
}

void LockerWindow::HandleEvents(sf::Event& event) {

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Vérifier le clic sur le bouton précédent
            if (buttonPrevSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::max(0, currentSectionIndex - 1); // Ne pas aller en dessous de 0
                UpdateSectionState();
            }
            // Vérifier le clic sur le bouton suivant
            else if (buttonNextSprite.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
                currentSectionIndex = std::min(8, currentSectionIndex + 1); // Ne pas dépasser 8
                UpdateSectionState();
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

    if (lockerSection["section1"]) {
        p = 0; l = 5;
    }
    else if (lockerSection["section2"]) {
        p = 5; l = 4;
    } 
    else if (lockerSection["section3"])
        p = 9, l = 3;
    else if (lockerSection["section4"])
        p = 13, l = 6;
    else if (lockerSection["section5"])
        p = 19, l = 4;
    else if (lockerSection["section6"])
        p = 23, l = 6;
    else if (lockerSection["section7"])
        p = 29, l = 3;
    else if (lockerSection["section8"])
        p = 32, l = 8;
    else if (lockerSection["section9"])
        p = 40, l = 8;

    for (int i = p; i < p + l; ++i) {
        if (i < entitiesPtr.size()) {
            entitiesPtr.at(i)->draw(window);
        }
    }
}


void LockerWindow::Update(sf::Event& event) {
    
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
        return;

    LockerManagement();

    // Dessiner les boutons
    window.draw(buttonPrevSprite);
    window.draw(buttonNextSprite);

}
