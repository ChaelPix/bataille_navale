#pragma once
#include <utility> // Pour std::pair
#include <string>
#include <windows.h>
#define espace "\t\t\t\t\t"
#define espace2 "\t\t\t\t\t\t      "
#define espace3 "\t\t\t\t\t\t   "
#define espace4 "\t\t\t\t\t\t         "

class CoreGame {
public:
    enum class typeCase { vide, bateau, touche, eau, erreur = 99};
    static const int nbLig = 10;
    static const int nbCol = 10;

private:
    typeCase grille[nbLig][nbCol];
    typeCase grilleAdversaire[nbLig][nbCol];
    int nombreTotalBateaux;
    int bateauxCoulés;

public:
    // Constructeur qui initialise la grille, par exemple avec des cases vides.
    CoreGame();

    // Retourne la case de la grille à la position spécifiée.
    typeCase getCase(int ligne, int colonne) const;

    // Définit la case de la grille à la position spécifiée avec le type donné.
    void setCase(int ligne, int colonne, typeCase type);

    // Affiche la grille dans la console ou l'interface utilisateur.
    void afficheGrille() const;

    char getRepresentationCaractere(typeCase caseType) const;

    // Permet au joueur de saisir une position sur la grille.
    static std::pair<int, int> saisieJoueur();

    bool partiePerdu() const;
    // Serialise l'état de la grille en chaîne de caractères.
    std::string serialisation() const;

    // Deserialise l'état de la grille à partir d'une chaîne de caractères.
    bool deserialisation(std::string trame);

    // Ajout de nouvelles méthodes publiques pour le déroulement du jeu
    void placerBateaux(); // Pour placer les bateaux de l'IA et du joueur

    bool attaqueJoueur(int ligne, int colonne); // Pour que le joueur attaque l'IA

    void attaqueIA(); // Pour que l'IA attaque le joueur

    void jouer(); // Pour démarrer la boucle de jeu

    bool estFinDuJeu() const; // Pour vérifier si la partie est terminée

    // Nouvelle méthode pour vérifier et mettre à jour l'état du bateau coulé
    void verifierBateauCoule(int ligne, int colonne);

    // Méthode pour afficher le nombre de bateaux coulés
    void afficherBateauxCoules() const;

};

