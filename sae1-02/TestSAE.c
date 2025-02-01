/**
 * \file TestSAE.c
 * \brief Contient la fonction main et un test spécifique pour le fonctionnement des duels.
 * 
 * \authors CABARET Benjamin, MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 5 décembre 2024 -> 10 janvier 2025
 */
#include "SAE.h"

/**
 * \brief Fonction qui permet de tester les duels
 * \author PICHOT-MOÏSE Mathéo
 */
void testDuel(void) {
    Joueur joueur = {"Chevalier", 20, 3, {0}, 0, 0, 0};
    Monstre monstre = {"Dragon", 10, 2, 2, 3, 1, "PFC"};

    printf("Test du duel entre %s (PV: %d) et %s (PV: %d)\n", joueur.pseudo, joueur.pointsDeVie, monstre.nom, monstre.pointsDeVie);

    char choixJoueur = attaqueJoueur();
    int attaqueMonstreResult = attaqueMonstre(monstre);
    int resultat = victoireDuel(attaqueMonstreResult, choixJoueur, monstre);

    if (resultat == 1) {
        printf("Le joueur %s remporte l'attaque !\n", joueur.pseudo);
        monstre.pointsDeVie -= joueur.degatsParAttaque;
        if (monstre.pointsDeVie <= 0) {
            printf("Le monstre %s est vaincu !\n", monstre.nom);
        } else {
            printf("Il reste %d PV au monstre %s.\n", monstre.pointsDeVie, monstre.nom);
        }
    } else if (resultat == 0) {
        printf("Le monstre %s remporte l'attaque !\n", monstre.nom);
        joueur.pointsDeVie -= monstre.degatsParAttaque;
        if (joueur.pointsDeVie <= 0) {
            printf("Le joueur %s est vaincu...\n", joueur.pseudo);
        } else {
            printf("Il reste %d PV au joueur %s.\n", joueur.pointsDeVie, joueur.pseudo);
        }
    } else {
        printf("C'est une égalité ! Personne ne perd de PV.\n");
    }

    printf("Fin du test du duel.\n");
}

/**
 * \brief Permet de lancer le programme
 */
int main(void) {
    global();
    return 0;
}