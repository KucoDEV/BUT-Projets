/**
 * \file SAE.h
 * \brief Fichier contenant les déclarations des fonctions du programme de gestion des stages.
 *
 * \authors MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 15 Octobre 2024
 */
#include <stdio.h>
#include <stdlib.h>

// Remplir Tableaux
    int remplirOffreStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
    int remplirListeEtudiants(int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlog, int tmax);

// Sauvegarde
    int modificationFichier(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogEtu);

// Responsable
    int afficherTableau(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
    int afficherStagesPourvus(int tRef[], int tDpt[], int tPourvu[], int *tlogOffre, int tNumEtu[], int tRefStage[], int *tlogEtu);
    int afficherStagesNonPourvus(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog);
    int afficherEtudiantsSansStage(int tNumEtu[], int tRefStage[], int *tlogEtu);
    int rechercherStage(int tRef[], int tDpt[], int tCandid[], int *tlog);
    int afficherInfoStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog);
    int ajoutStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax);
    int decalerAgauche(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int ref);
    int supprimerStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog);
    void StagesDispo(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog);
    int affecterEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogEtu);
    int menuResponsable(void);
    int globalResponsable(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Etudiant
    int listeStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlogOffre);
    int candidaterStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlogOffre, int *tlogEtu, int tNumEtu[], int etudiantID);
    int verifieLogin(int id, int tNumEtu[], int tlogEtu);
    int login(void);
    int menuEtudiant(void);
    int globalEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Jury
    int ajouterNotes(int tNumEtu[], float tNoteFInal[], int *tlogEtu);
    int afficherNotes(int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogEtu);
    int voirCandidature(int tNumEtu[], int tRefStage[], int tRef[], int tDpt[], int tPourvu[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlogEtu, int *tlogOffre, int etudiantID, int tCandid[]);
    int menuJury(void);
    int globalJury(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFInal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu);

// Global
    int menuSelection(void);
    void global(void);