#pragma once
#define SautaLaLigne std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
#define espace "\t\t\t\t\t"
#define espace2 "\t\t\t\t\t\t      "
#define espace3 "\t\t\t\t\t\t   "
#define espace4 "\t\t\t\t\t\t         "
#define espace5 "\t\t\t\t\t\t      "
#define effacer system("cls");
#include <utility> // Pour std::pair
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include "BsBDD.h"
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

class CoreGame {
public:
    enum class typeCase { vide, bateau, touche, eau, erreur = 99};
    static const int nbLig = 10;
    static const int nbCol = 10;
    BsBDD obj;

private:
    typeCase grille[nbLig][nbCol];
    typeCase grilleAdversaire[nbLig][nbCol];
    int nombreTotalBateaux; // obselete
    int bateauxCoulés; //obselete

public:
    // Constructeur qui initialise la grille, par exemple avec des cases vides.
    CoreGame();

    //// Retourne la case de la grille à la position spécifiée.
    //typeCase getCase(int ligne, int colonne) const;

    //// Définit la case de la grille à la position spécifiée avec le type donné.
    //void setCase(int ligne, int colonne, typeCase type);

    // Affiche la grille dans la console ou l'interface utilisateur.
    void afficheGrille() const;

    void afficherCaractereAvecCouleur(typeCase caseType, bool estGrilleAdversaire) const;

    char getRepresentationCaractere(typeCase caseType) const;

    // Permet au joueur de saisir une position sur la grille.
    static std::pair<int, int> saisieJoueur();

    bool partiePerdu() const;
    // Serialise l'état de la grille en chaîne de caractères.
    std::string serialisationJoueur() const;

    // Serialise l'état de la grille en chaîne de caractères de l'adversaire.
    std::string serialisationAdversaire() const;

    // Deserialise l'état de la grille à partir d'une chaîne de caractères.
    bool deserialisation(const std::string& trame);

    bool deserialisationAdversaire(const std::string& trame);

    bool caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol]);


    // Ajout de nouvelles méthodes publiques pour le déroulement du jeu
    void placerBateaux(bool pourAdversaire); // Pour placer les bateaux de l'IA et du joueur

    bool attaqueJoueur(int ligne, int colonne); // Pour que le joueur attaque l'IA

    void attaqueIA(); // Pour que l'IA attaque le joueur

    void jouer(); // Pour démarrer la boucle de jeu

    bool estFinDuJeu() const; // Pour vérifier si la partie est terminée

    // Nouvelle méthode pour vérifier et mettre à jour l'état du bateau coulé
    void verifierBateauCoule(int ligne, int colonne, bool grilleAdversaire);

    // Méthode pour afficher le nombre de bateaux coulés
    void afficherBateauxCoules() const;

};

