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
    int bateauxCoul�s;

public:
    // Constructeur qui initialise la grille, par exemple avec des cases vides.
    CoreGame();

    // Retourne la case de la grille � la position sp�cifi�e.
    typeCase getCase(int ligne, int colonne) const;

    // D�finit la case de la grille � la position sp�cifi�e avec le type donn�.
    void setCase(int ligne, int colonne, typeCase type);

    // Affiche la grille dans la console ou l'interface utilisateur.
    void afficheGrille() const;

    char getRepresentationCaractere(typeCase caseType) const;

    // Permet au joueur de saisir une position sur la grille.
    static std::pair<int, int> saisieJoueur();

    bool partiePerdu() const;
    // Serialise l'�tat de la grille en cha�ne de caract�res.
    std::string serialisation() const;

    // Deserialise l'�tat de la grille � partir d'une cha�ne de caract�res.
    bool deserialisation(std::string trame);

    // Ajout de nouvelles m�thodes publiques pour le d�roulement du jeu
    void placerBateaux(); // Pour placer les bateaux de l'IA et du joueur

    bool attaqueJoueur(int ligne, int colonne); // Pour que le joueur attaque l'IA

    void attaqueIA(); // Pour que l'IA attaque le joueur

    void jouer(); // Pour d�marrer la boucle de jeu

    bool estFinDuJeu() const; // Pour v�rifier si la partie est termin�e

    // Nouvelle m�thode pour v�rifier et mettre � jour l'�tat du bateau coul�
    void verifierBateauCoule(int ligne, int colonne);

    // M�thode pour afficher le nombre de bateaux coul�s
    void afficherBateauxCoules() const;

};

