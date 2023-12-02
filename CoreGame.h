#ifndef _COREGAME_H
#define _COREGAME_H
#define SautaLaLigne std::cout<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
#define espace "\t\t\t\t\t"
#define espace2 "\t\t\t\t\t\t      "
#define espace3 "\t\t\t\t\t\t   "
#define espace4 "\t\t\t\t\t\t         "
#define espace5 "\t\t\t\t\t\t      "
#define effacer system("cls");
#include "TCPClient.h"

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
    enum class typeCase { vide, bateau, touche, eau, erreur = 99 };
    enum class typeBateau { PorteAvion = 5, Croiseur = 4, ContreTorpilleur = 3, Torpilleur = 2 };
    enum class boatTypes { PorteAvion = 5, Croiseur = 4, ContreTorpilleur = 3, Torpilleur = 2 };
    static const int nbLig = 10;
    static const int nbCol = 10;
    BsBDD obj;
private:
    typeCase grille[nbLig][nbCol];
    typeCase grilleAdversaire[nbLig][nbCol];
    int nombreTotalBateaux; // obselete
    int bateauxCoul�s; //obselete
    TCPClient* client = nullptr;

public:



    // Constructeur qui initialise la grille, par exemple avec des cases vides.
    CoreGame();
    CoreGame(TCPClient* tcpClient);
    //// Retourne la case de la grille � la position sp�cifi�e.
    //typeCase getCase(int ligne, int colonne) const;

    //// D�finit la case de la grille � la position sp�cifi�e avec le type donn�.
    //void setCase(int ligne, int colonne, typeCase type);

    // Affiche la grille dans la console ou l'interface utilisateur.

    void connexion();
    void afficheGrille() const;

    void afficherCaractereAvecCouleur(typeCase caseType, bool estGrilleAdversaire) const;

    // Permet au joueur de saisir une position sur la grille.
    static std::pair<int, int> saisieJoueur();

    bool partiePerdu() const;
    // Serialise l'�tat de la grille en cha�ne de caract�res.
    std::string serialisationJoueur() const;

    // Serialise l'�tat de la grille en cha�ne de caract�res de l'adversaire.
    std::string serialisationAdversaire() const;

    // Deserialise l'�tat de la grille � partir d'une cha�ne de caract�res.
    bool deserialisation(const std::string& trame);

    bool deserialisationAdversaire(const std::string& trame);

    bool caseAdjacenteLibre(int ligne, int colonne, typeCase(*grilleCible)[nbCol]);

    // Ajout de nouvelles m�thodes publiques pour le d�roulement du jeu
    void placerBateaux(bool pourAdversaire); // Pour placer les bateaux de l'IA et du joueur

    bool attaqueJoueur(int ligne, int colonne); // Pour que le joueur attaque l'IA

    void attaqueIA(); // Pour que l'IA attaque le joueur

    void jouer(); // Pour d�marrer la boucle de jeu

    bool estFinDuJeu(); // Pour v�rifier si la partie est termin�e

    // Nouvelle m�thode pour v�rifier et mettre � jour l'�tat du bateau coul�
    void verifierBateauCoule(int ligne, int colonne, bool grilleAdversaire);

    // M�thode pour afficher le nombre de bateaux coul�s
    void afficherBateauxCoules() const;

    void setBonus();
    void Appel() const;

    void envoyerAttaque(int ligne, int colonne);
    bool traiterAttaqueAdversaire(int ligne, int colonne);
    void recevoirAttaque();
};
#endif