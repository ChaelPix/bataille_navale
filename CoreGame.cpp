#include "CoreGame.h"
#include <iostream>


//CoreGame::CoreGame(const std::string& ipServeur, ushort portServeur)
//    : client(ipServeur, portServeur), nombreTotalBateaux(4), bateauxCoul�s(0) {
//    // Initialisation de la grille
//    for (int i = 0; i < nbLig; ++i) {
//        for (int j = 0; j < nbCol; ++j) {
//            grille[i][j] = typeCase::vide;
//            grilleAdversaire[i][j] = typeCase::vide;
//        }
//    }
//    // Placer les bateaux
//    placerBateaux(false); // Place un bateau pour le joueur
//    placerBateaux(true);  // Place un bateau pour l'IA
//}


CoreGame::CoreGame() : client(nullptr) {
    // Initialisation de la grille
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            grille[i][j] = typeCase::vide;
            grilleAdversaire[i][j] = typeCase::vide;
        }
    }
    // Placer les bateaux
    placerBateaux(false); // Place un bateau pour le joueur
    placerBateaux(true);  // Place un bateau pour l'IA
}

CoreGame::CoreGame(TCPClient* tcpClient) : client(tcpClient) {
    // Initialisation de la grille
    // ...
}



void CoreGame::connexion()
{
}

void CoreGame::afficheGrille() const {
    std::cout << espace << "Votre Grille:" << "           Grille Adversaire:\n";

    // Afficher les rep�res de colonne
    std::cout << espace << "  ";
    for (int i = 0; i < nbCol; ++i) {
        std::cout << "\033[90m" << i << "\033[0m" << " ";
    }
    std::cout << "    ";
    for (int i = 0; i < nbCol; ++i) {
        std::cout << "\033[90m" << i << "\033[0m" << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < nbLig; ++i) {
        // Afficher le rep�re de ligne
        std::cout << espace << "\033[90m" << i << "\033[0m" << " ";

        // Afficher la grille du joueur
        for (int j = 0; j < nbCol; ++j) {
            afficherCaractereAvecCouleur(grille[i][j], false);
            std::cout << " ";
        }

        std::cout << "\t" << "\033[90m" << i << "\033[0m" << " "; // Rep�re de ligne pour la grille de l'adversaire

        // Afficher la grille de l'adversaire
        for (int j = 0; j < nbCol; ++j) {
            // Afficher seulement les tirs effectu�s sur la grille de l'adversaire
            if (grilleAdversaire[i][j] == typeCase::touche || grilleAdversaire[i][j] == typeCase::eau) {
                afficherCaractereAvecCouleur(grilleAdversaire[i][j], true);
            }
            else {
                // Afficher 'O' pour les cases vides et celles contenant des bateaux non d�couverts
                afficherCaractereAvecCouleur(typeCase::vide, true);
            }
            std::cout << " ";
        }

        std::cout << std::endl;
    }
}


void CoreGame::afficherCaractereAvecCouleur(typeCase caseType, bool estGrilleAdversaire) const {

    // Codes de couleur ANSI
    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";     // Pour "touche"
    const std::string BLUE = "\033[34m";    // Pour "bateau"
    const std::string CYAN = "\033[36m";    // Pour "eau"
    const std::string VERT = "\033[32m";  // Pour "vide"
    const std::string GREY = "\033[90m";    // Pour un caract�re inconnu
    const std::string YELLOW = "\033[33m";    // Pour un caract�re inconnu

    std::string couleur;
    char caractere;

    switch (caseType) {
    case typeCase::vide:
        couleur = estGrilleAdversaire ? YELLOW : VERT; // YELLOW pour adversaire, VERT pour joueur
        caractere = 'O';
        break;
    case typeCase::bateau:
        couleur = RESET;
        caractere = 'B';
        break;
    case typeCase::touche:
        couleur = RED;
        caractere = 'X';
        break;
    case typeCase::eau:
        couleur = CYAN;
        caractere = '~';
        break;
    default:
        couleur = GREY;
        caractere = '?';
        break;
    }

    std::cout << couleur << caractere << RESET;
}

std::pair<int, int> CoreGame::saisieJoueur() {
    int ligne, colonne;
    do {
        std::cout << std::endl << espace << "Entrez la ligne: ";
        std::cin >> ligne;
        std::cout << espace << "Entrez la colonne: ";
        std::cin >> colonne;

        if (ligne < 0 || ligne >= nbLig || colonne < 0 || colonne >= nbCol) {
            std::cout << "Coordonn�es invalides. Veuillez r�essayer." << std::endl;
        }
    } while (ligne < 0 || ligne >= nbLig || colonne < 0 || colonne >= nbCol);

    return { ligne, colonne };
}


bool CoreGame::partiePerdu() const {
    // Impl\202mentation de la v\202rification pour voir si la partie est perdue.
    // Par exemple, v\202rifier s'il reste des cases 'bateau'.
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            if (grille[i][j] == typeCase::bateau) {
                return false; // Il reste encore des bateaux.
            }
        }
    }
    return true; // Plus de bateaux, la partie est perdue.
}

std::string CoreGame::serialisationJoueur() const {
    std::string result;
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            switch (grille[i][j]) {
            case typeCase::vide: result += 'V'; break;
            case typeCase::bateau: result += 'B'; break;
            case typeCase::touche: result += 'T'; break;
            case typeCase::eau: result += 'E'; break;
            default: result += '?'; break;
            }
        }
        result += "\n";
    }
    return result;
}


std::string CoreGame::serialisationAdversaire() const {
    std::string result;
    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            switch (grilleAdversaire[i][j]) {
            case typeCase::vide: result += 'V'; break;
            case typeCase::bateau: result += 'B'; break;
            case typeCase::touche: result += 'T'; break;
            case typeCase::eau: result += 'E'; break;
            default: result += '?'; break;
            }
        }
        result += "\n";
    }
    return result;
}


//std::string CoreGame::serialisationAdversaire() const {
//    // Convertit l'\202tat actuel de la grille en une cha�ne de caract�res.
//    std::string result;
//    for (int i = 0; i < nbLig; ++i) {
//        for (int j = 0; j < nbCol; ++j) {
//            result += std::to_string(static_cast<int>(grilleAdversaire[i][j])) + " ";
//        }
//        result += "\n";
//    }
//    return result;
//}

bool CoreGame::deserialisationAdversaire(const std::string& trame) {
    std::istringstream iss(trame);
    std::string ligneTrame;
    int numLigne = 0;

    while (std::getline(iss, ligneTrame) && numLigne < nbLig) {
        if (ligneTrame.size() != nbCol) {
            std::cerr << "Erreur de format de trame: longueur incorrecte." << std::endl;
            return false;
        }

        for (int numColonne = 0; numColonne < nbCol; ++numColonne) {
            char caractere = ligneTrame[numColonne];
            typeCase caseType;

            switch (caractere) {
            case 'V': caseType = typeCase::vide; break;
            case 'B': caseType = typeCase::bateau; break;
            case 'T': caseType = typeCase::touche; break;
            case 'E': caseType = typeCase::eau; break;
            default:
                std::cerr << "Caract�re inconnu dans la trame: " << caractere << std::endl;
                return false;
            }

            grille[numLigne][numColonne] = caseType;
        }

        ++numLigne;
    }

    return (numLigne == nbLig);
}


//bool CoreGame::deserialisationAdversaire(const std::string& trame) {
//    std::istringstream iss(trame);
//    std::string ligneTrame;
//    int numLigne = 0;
//
//    while (std::getline(iss, ligneTrame) && numLigne < nbLig) {
//        std::istringstream issLigne(ligneTrame);
//        int valeur;
//        int numColonne = 0;
//
//        while (issLigne >> valeur && numColonne < nbCol) {
//            grilleAdversaire[numLigne][numColonne] = static_cast<typeCase>(valeur);
//            numColonne++;
//        }
//
//        numLigne++;
//    }
//
//    return (numLigne == nbLig);
//}


bool CoreGame::caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol]) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int l = ligne + i;
            int c = colonne + j;
            if (l >= 0 && l < nbLig && c >= 0 && c < nbCol) {
                if (grilleCible[l][c] != typeCase::vide) {
                    return false; // Une case adjacente n'est pas vide
                }
            }
        }
    }
    return true; // Toutes les cases adjacentes sont libres
}

void CoreGame::setBonus() {

}

void CoreGame::Appel() const {
}

void CoreGame::placerBateaux(bool pourAdversaire) {
    typeCase(*grilleCible)[nbCol] = pourAdversaire ? grilleAdversaire : grille; // Expression conditionnelle. Si pourAdversaire est vrai (true), alors la valeur grilleAdversaire est utilis�e ; sinon, la valeur grille est utilis�e.
    const std::vector<int> taillesBateaux = { 3, 2, 4, 5 }; // Les bateaux disponible par joueurs, il doit y avoir un bateau avec 2 cases, 3 cases, 4 cases et enfin 5 cases selon wikipedia : https:// fr.wikipedia.org/wiki/Bataille_navale_(jeu)

    for (int tailleBateau : taillesBateaux) {

        bool placementValide = false;

        while (!placementValide) {

            //placement random
            int direction = std::rand() % 2; // 0 pour horizontal, 1 pour vertical
            int ligne = std::rand() % nbLig;
            int colonne = std::rand() % nbCol;

            //check placement
            placementValide = true;
            for (int i = 0; i < tailleBateau; ++i) {
                int l = ligne + (direction == 0 ? 0 : i);
                int c = colonne + (direction == 1 ? 0 : i);
                if (l >= nbLig || c >= nbCol || grilleCible[l][c] != typeCase::vide || !caseAdjacenteLibre(l, c, grilleCible)) {
                    placementValide = false;
                    break;
                }
            }

            //place le bateau
            if (placementValide) {
                for (int i = 0; i < tailleBateau; ++i) {
                    int l = ligne + (direction == 0 ? 0 : i);
                    int c = colonne + (direction == 1 ? 0 : i);
                    grilleCible[l][c] = typeCase::bateau;
                }
            }
        }
    }
}



bool CoreGame::attaqueJoueur(int ligne, int colonne) {
    // Si la case a d�j� �t� attaqu�e, ne rien faire
    if (grilleAdversaire[ligne][colonne] == typeCase::touche || grilleAdversaire[ligne][colonne] == typeCase::eau) {
        return false;
    }

    // V�rification simple de la case attaqu�e
    if (grilleAdversaire[ligne][colonne] == typeCase::bateau) {
        grilleAdversaire[ligne][colonne] = typeCase::touche; // Marquer la case comme touch�e sur la grille de l'adversaire
        verifierBateauCoule(ligne, colonne, true); // V�rifier si un bateau a �t� coul� sur la grille de l'adversaire
        return true;
    }
    else {
        grilleAdversaire[ligne][colonne] = typeCase::eau; // Marquer la case comme eau (manqu�) sur la grille de l'adversaire
        return false;
    }
}




void CoreGame::attaqueIA() {
    int ligne, colonne;
    do {
        ligne = std::rand() % nbLig;
        colonne = std::rand() % nbCol;
    } while (grille[ligne][colonne] == typeCase::touche || grille[ligne][colonne] == typeCase::eau); // �viter les cases d�j� attaqu�es
    // L'IA attaque une case
    if (grille[ligne][colonne] == typeCase::bateau) {
        std::cout << espace3 << "\033[31mL'IA a touch\202 un bateau !\033[0m" << std::endl << std::endl;
        grille[ligne][colonne] = typeCase::touche;
    }
    else {
        std::cout << espace2 << "\033[34mL'IA a manqu\202.\033[0m" << std::endl << std::endl;
        grille[ligne][colonne] = typeCase::eau;
    }
}

void CoreGame::jouer() {

    do {
        obj.Connexion();
        system("cls");
    } while (!obj.isConnect());

    SautaLaLigne
        obj.displayPlayerInfo();
    std::cout << std::endl;

    while (/*!estFinDuJeu()*/ true) {

        afficheGrille();

        // Le joueur effectue une attaque
        std::pair<int, int> saisie = saisieJoueur();
        int ligne = saisie.first;
        int colonne = saisie.second;
        attaqueJoueur(ligne, colonne);
        envoyerAttaque(saisie.first, saisie.second); // Envoie l'attaque et l'�tat actuel de la grille

        // Attendre et traiter l'attaque de l'adversaire
        recevoirAttaque(); // Re�oit l'attaque de l'adversaire et met � jour les grilles

        system("cls");
        std::cout << "MOI: " << std::endl << serialisationJoueur() << std::endl;
        std::cout << "ADVERSAIRE: " << std::endl << serialisationAdversaire();
        std::cout << std::endl;

        // Affichage du r�sultat de l'attaque
        if (grilleAdversaire[saisie.first][saisie.second] == typeCase::touche) {
            std::cout << espace4 << "\033[34mTouch�!\033[0m" << std::endl << std::endl;
        }
        else {
            std::cout << espace4 << "\033[31mManqu�!\033[0m" << std::endl << std::endl;
        }

        //int time = 0;
        //while (time <= 15) {
        //    Sleep(1000);
        //    time++;
        //    std::cout << "Vous pouvez rejouer dans " << time << " secondes si l'adversaire ne joue pas." << std::endl;
        //    system("cls");
        //}
    }
    obj.incrementNbGames();
}



bool CoreGame::estFinDuJeu() {
    bool joueurPerdu = true, adversairePerdu = true;

    for (int i = 0; i < nbLig; ++i) {
        for (int j = 0; j < nbCol; ++j) {
            if (grille[i][j] == typeCase::bateau) {
                joueurPerdu = false;
            }
            if (grilleAdversaire[i][j] == typeCase::bateau) {
                adversairePerdu = false;
            }
        }
    }

    if (joueurPerdu) {
        std::cout << espace << "         Vous avez perdu la partie." << std::endl;
        obj.incrementNbLostGames();
    }
    else if (adversairePerdu) {
        std::cout << espace << "         Vous avez gagn\202 la partie !" << std::endl;
        obj.BonusWin();
        obj.incrementNbWonGames();
    }

    return joueurPerdu || adversairePerdu;
}


void CoreGame::verifierBateauCoule(int ligne, int colonne, bool pourAdversaire) {
    typeCase(*grilleCible)[nbCol] = pourAdversaire ? grilleAdversaire : grille;

    // V�rifier d'abord si la case contient un bateau touch�
    if (grilleCible[ligne][colonne] != typeCase::touche) {
        return; // Si la case n'est pas un bateau touch�, aucune v�rification suppl�mentaire n'est n�cessaire
    }

    // V�rifiez s'il reste des parties de bateau non touch�es autour de cette case
    bool bateauCoul� = true;

    // V�rifier les cases adjacentes
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int voisinLigne = ligne + i;
            int voisinColonne = colonne + j;

            // V�rifier les limites de la grille
            if (voisinLigne >= 0 && voisinLigne < nbLig && voisinColonne >= 0 && voisinColonne < nbCol) {
                if (grilleCible[voisinLigne][voisinColonne] == typeCase::bateau) {
                    bateauCoul� = false; // Il reste des parties non touch�es du bateau
                    break;
                }
            }
        }
        if (!bateauCoul�) break;
    }

    // Mettre � jour le compteur si un bateau a �t� coul�
   /* if (bateauCoul�) {
        ++bateauxCoul�s;
    }*/
}

// obselete
void CoreGame::afficherBateauxCoules() const {
    //std::cout << espace << "Bateaux coul\202s: " << bateauxCoul�s << " sur " << nombreTotalBateaux << std::endl;
}

void CoreGame::envoyerAttaque(int ligne, int colonne) {
    try {
        std::string etatGrille = serialisationAdversaire();
        client->sendMessage(etatGrille);
    }
    catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'envoi de l'attaque : " << e.what() << std::endl;
        // Gestion de la reconnexion ou notification � l'utilisateur ici
    }
}



void CoreGame::recevoirAttaque() {
    std::string message = client->receiveMessage();
    std::istringstream iss(message);
    int ligne, colonne;
    iss >> ligne >> colonne;

    // Traiter l'attaque
    traiterAttaqueAdversaire(ligne, colonne);

    // Recevoir et d�s�rialiser l'�tat de la grille de l'adversaire
    std::string trameGrilleAdversaire = client->receiveMessage();
    deserialisationAdversaire(trameGrilleAdversaire);
}


bool CoreGame::traiterAttaqueAdversaire(int ligne, int colonne) {
    // V�rifier si la case a d�j� �t� attaqu�e
    if (grille[ligne][colonne] == typeCase::touche || grille[ligne][colonne] == typeCase::eau) {
        return false; // L'attaque a d�j� �t� effectu�e sur cette case
    }

    // V�rifier si l'attaque touche un bateau
    if (grille[ligne][colonne] == typeCase::bateau) {
        grille[ligne][colonne] = typeCase::touche; // Marquer la case comme touch�e
        verifierBateauCoule(ligne, colonne, false); // V�rifier si un bateau a �t� coul�
        return true; // L'attaque a touch� un bateau
    }
    else {
        grille[ligne][colonne] = typeCase::eau; // Marquer la case comme manqu�e (eau)
        return false; // L'attaque a manqu�
    }
}



//CoreGame::typeCase CoreGame::getCase(int ligne, int colonne) const { //a supprimer
//    return grille[ligne][colonne];
//}
//
//void CoreGame::setCase(int ligne, int colonne, CoreGame::typeCase type) { //a supprimer
//    grille[ligne][colonne] = type;
//}

//// Fonction pour changer la couleur du texte en rouge
//void setRedText() {
//    std::cout << "\033[33m"; // Code ANSI pour le texte en rouge
//}
//
//// Fonction pour r�initialiser la couleur du texte � sa valeur par d�faut
//void resetTextColor() {
//    std::cout << "\033[0m"; // Code ANSI pour r�initialiser la couleur
//}
//
//// Fonction pour changer la couleur du texte en rouge
//void setGreenText() {
//    std::cout << "\033[32m"; // Code ANSI pour le texte en rouge
//}

//char CoreGame::getRepresentationCaractere(typeCase caseType) const { // a supprimer
//    switch (caseType) {
//    case typeCase::vide: return 'O';
//    case typeCase::bateau: return 'B';
//    case typeCase::touche: return 'X';
//    case typeCase::eau: return '~';
//    default: return '?';
//    }
//}