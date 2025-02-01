/**
 * \file SAE.c
 * \brief Fichier d'en-tête contenant les déclarations des structures de données et des prototypes de fonctions.
 * 
 * \authors CABARET Benjamin, MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 5 décembre 2024 -> 10 janvier 2025
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARMES 5

/**
 * \struct Joueur
 * \brief Structure contenant les informations des joueurs
 * 
 * \param pseudo Pseudo du joueur
 * \param pointsDeVie Points de vie du joueur
 * \param degatsParAttaque Dégâts par attaque du joueur
 * \param scores Tableau des scores du joueur
 * \param partiesJouees Nombre de parties jouées
 * \param partiesGagnees Nombre de parties gagnée
 * \param partiesPerdues Nombre de parties perdues
 */
typedef struct {
    char pseudo[50]; 
    int pointsDeVie;
    int degatsParAttaque;
    int scores[100];
    int partiesJouees;
    int partiesGagnees;
    int partiesPerdues;
} Joueur;

/**
 * \struct Monstre
 * \brief Structure contenant les informations des joueurs
 * 
 * \param nom Nom du monstre
 * \param pointsDeVie Points de vie du joueur
 * \param niveau Niveau du monstre
 * \param degatsParAttaque Dégâts par attaque du joueur
 * \param nombreArmes Nombre d'arme disponible pour le monstre
 * \param groupe Le groupe auquel il appartient
 * \param armes Tableau contenant ses armes
 */
typedef struct {
    char nom[50];
    int pointsDeVie;
    int niveau;
    int degatsParAttaque;
    int nombreArmes;
    int groupe;
    char armes[MAX_ARMES];
} Monstre;

/**
 * \enum ArmeType
 * \brief Toutes les armes disponibles
 */
typedef enum {
    PIERRE = 'P',
    FEUILLE = 'F',
    CISEAUX = 'C',
    ARME_BONNE_A_RIEN = 'O',
    SUPER_ARME = '#'
} ArmeType;

/**
 * \struct Stats
 * \brief Permet de récupérer les statistiques des joueurs
 * 
 * \param pseudo Pseudo du joueur
 * \param meilleurScore Meilleur score du joueur
 * \param moyenneScores Moyenne des scores du joueur
 * \param nbParties Nombre de parties jouées par le joueur
 * \param victoire Nombre de victoire
 * \param defaite Nombre de défaite
 */
typedef struct {
    char pseudo[50];
    int meilleurScore;
    float moyenneScores;
    int nbParties;
    int victoire;
    int defaite;
} Stats;

/**
 * \brief Fonction qui redirige l'utilisateur en fonction de son choix dans le menu
 * \author PICHOT-MOÏSE Mathéo  
 */
void global(void);

/**
 * \brief Fonction qui affiche le menu principal du jeu et demande ce que l'utilisateur veut faire
 * \author CABARET Benjamin
 * 
 * \return Le choix de l'utilisateur
 */
int menu(void);

/**
 * \brief Fonction qui gère entièrement la partie
 * \authors CABARET Benjamin, PICHOT-MOÏSE Mathéo
 * 
 * \param nomFichier Nom du fichier de la partie prédéfinie
 * \param pseudo Pseudo du joueur
 */
void deroulerPartie(char* nomFichier, char* pseudo);

/**
 * \brief Fonction qui permet de créer une partie prédéfinie qui sera stockée dans un fichier
 * \author PICHOT-MOÏSE Mathéo
 * 
 * \param nomFichier Nom du fichier dans lequel la partie sera stockée
 */
void creerNouvellePartie(char* nomFichier);

/**
 * \brief Fonction qui permet de gérer les duels
 * \author CABARET Benjamin
 * 
 * \param attaque L'attaque du monstre
 * \param choix Le choix du joueur
 * \param m Structure du monstre correspondant au duel
 */
int victoireDuel(int attaque, char choix, Monstre m);

/**
 * \brief Fonction qui permet de récuprer le choix du joueur
 * \author CABARET Benjamin
 */
char attaqueJoueur(void);

/**
 * \brief Fonction qui génére aléatoirement une arme pour le monstre
 * \author CABARET Benjamin
 * 
 * \param m Structure du monstre correspondant
 */
int attaqueMonstre(Monstre m);

/**
 * \brief Fonction qui permet de préparer la sauvegarde
 * \author MIOTTO Quentin
 * 
 * \param pseudo Pseudo du joueur
 * \param score Score du joueur
 * \param victoire Permet de savoir si le joueur a gagné ou non
 */
void sauvegarde(char * pseudo, int score, int victoire);

/**
 * \brief Fonction qui permet d'écrire dans le fichier de score
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des scores
 * \param nbJoueurs Nombre de joueurs dans le fichier
 * \param newJ Sert a savoir si c'est un nouveau joueur ou non
 * \param pseudo Pseudo du joueur
 * \param score Score du joueur
 * \param victoire Permet de savoir si le joueur a gagné ou non
 */
void sauvegardeTableau(Stats ts[],int nbJoueurs, int newJ,char pseudo[],int score,int victoire);

/**
 * \brief Fonction qui permet de charger les joueurs dans le scoreboard
 * \author MIOTTO Quentin
 * 
 * \param choix Le choix du joueur
 */
int ChargeTabAffichage(int choix);

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par nom
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 */
void tabParNom(Stats ts[],int tlog);

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par score
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 */
void tabParScore(Stats ts[],int tlog);

/**
 * \brief Fonction qui permet de rechercher un joueur dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 */
void rechercherJoueur(Stats ts[],int tlog);

/**
 * \brief Fonction qui permet de renvoyer l'indice (place dans le tableau) du pseudo d'un joueur le plus petit (dans l'ordre alphabetique)
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueurs dans le tableau
 * 
 * \return l'indice du plus petit pseudo d'un joueur
 */
int plusGrandNom(Stats tab[], int n);

/**
 * \brief Fonction qui permet de renvoyer l'indice (place dans le tableau) du Joueur ayant le grand Score
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 * 
 * \return l'indice du Joueur ayant le plus grand Score
 */
int plusGrandScore(Stats tab[],int n);

/**
 * \brief Fonction qui permet d'échanger 2 éléments dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param i Le premier élément à échanger
 * \param j Le second élément à échanger
 */
void echanger(Stats tab[], int i, int j);

/**
 * \brief Fonction qui permet de trier le tableau des statistiques par nom
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueurs dans le tableau
 */
void triEchangeNom(Stats tab[], int n);

/**
 * \brief Fonction qui permet de trier le tableau des statistiques par score
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueurs dans le tableau
 */
void triEchangeScore(Stats tab[], int n);

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par score
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 */
void afficherTableauScore(Stats tab[], int tlog);

/**
 * \brief Fonction qui permet d'afficher le tableau des scores par nom
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 */
void afficherTableauNom(Stats tab[], int tlog);

/**
 * \brief Fonction qui permet d'effectuer une recherche dichomatique dans le tableau des scores
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param n Nombre de joueurs dans le tableau
 * \param cible Le joueur voulu
 */
int rechercheDichomatique(Stats tab[],int n,char cible[]);

/**
 * \brief Fonction qui permet d'afficher les statistiques d'un joueur
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlo Nombre de joueurs dans le tableau
 * \param trouve La place du joueur
 * \param cible Le pseudo du joueur
 */
void affichageJoueur(Stats ts[],int tlo, int trouve, char cible[]);

/**
 * \brief Fonction qui permet d'afficher tout les pseudo en fonction d'une lettre
 * \author MIOTTO Quentin
 * 
 * \param tab Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 * \param Lettre La lettre que l'on souhaite chercher
 */
void affichageLettre(Stats tab[], int tlog, char Lettre);

/**
 * \brief Fonction qui permet d'afficher le tableau des scores à partir du bas et limiter la taille du tableau afficher en fonction de x
 * \author MIOTTO Quentin
 * 
 * \param ts Tableau des stats
 * \param tlog Nombre de joueurs dans le tableau
 * \param x taille du tableau afficher choisis dans le menu par l'utilisateur (10 ou 25)
 */
void afficherDerniers(Stats tab[], int tlog, int x);