/**
 * \file SAE.c
 * \brief Fichier contenant les fonctions du programme de gestion des stages.
 * \authors MIOTTO Quentin, PICHOT-MOÏSE Mathéo
 * \date 15 Octobre 2024
 */
#include "SAE.h"


/**
 * \brief Remplit les tableaux avec les informations des offres de stages à partir du fichier "offrestage.don".
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \param tmax Taille physique du tableau.
 * \return 0 si tout s'est bien passé, -1 en cas d'erreur de lecture.
 */
int remplirOffreStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    FILE *flot;
    int ref, dept, pourvu, candid, etu1, etu2, etu3;
    int i=0;

    flot = fopen("DATA/offrestage.don", "r");
    
    if (flot  == NULL) return -1; // Erreur lors du chargement
    
    while(i < tmax && fscanf(flot, "%d", &ref) == 1) {
        if (ref >= 1000) {
            tRef[i] = ref;
            if (fscanf(flot, "%d%d%d", &dept, &pourvu, &candid) != 3) {
                break;
            }

            if (candid==3) {
                if (fscanf(flot, "%d%d%d", &etu1, &etu2, &etu3) != 3) {
                    break;
                }
            }
            else if (candid==2) {
                if (fscanf(flot, "%d%d", &etu1, &etu2) != 2) {
                    break;
                }
                etu3=0;
            }
            else if  (candid==1) {
                if (fscanf(flot, "%d", &etu1) != 1) {
                    break;
                }
                etu2=0; 
                etu3=0;
            }
            else {
                etu1=0;
                etu2=0;
                etu3=0;
            }
            
            tDpt[i] = dept;
            tPourvu[i] = pourvu;
            tCandid[i] = candid;
            tEtu1[i] = etu1;
            tEtu2[i] = etu2;
            tEtu3[i] = etu3;

            i++;
            (*tlog)++;
        }
    }
    fclose(flot);
    return 1; // Fonction réussi
}

/**
 * \brief Remplit les tableaux avec les informations des étudiants à partir d'un fichier.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlog Taille logique du tableau.
 * \param tmax Taille physique du tableau.
 * \return 0 si tout s'est bien passé, -1 ou -2 en cas d'erreur de lecture.
 */
int remplirListeEtudiants(int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlog, int tmax) {
    int i=0, num, ref;
    float note;
    FILE *flot;
    flot = fopen("DATA/etudiants.don", "r");

    if (flot == NULL) return -1; // Erreur lors du chargement

    fscanf(flot, "%d %d %f", &num, &ref, &note);
    while(!feof(flot)) {
        if (i < tmax) {
            tNumEtu[i] = num;
            tRefStage[i] = ref;
            tNoteFinal[i] = note;
            (*tlog)++;
            i++;
            fscanf(flot,"%d%d%f", &num, &ref, &note);
        }
        else {
            fclose(flot);
            return -2; 
        }
    }
    fclose(flot);
    return 1; // Fonction réussi
}


/**
 * \brief Sauvegarde les modifications apportées aux stages et aux étudiants dans un fichier.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \return 1 si la sauvegarde s'est bien effectuée, -1 en cas d'erreur.
 */
int modificationFichier(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    FILE *flot;
    flot = fopen("DATA/offrestage.don", "w");
    if (flot == NULL) return -1;

    for (int i = 0; i < *tlog; i++) {
        fprintf(flot, "\n%d %d\n%d\n%d", tRef[i], tDpt[i], tPourvu[i], tCandid[i]);
        if (tPourvu[i] == 0) {
            if (tCandid[i] == 3) fprintf(flot, "\n%d\n%d\n%d", tEtu1[i], tEtu2[i], tEtu3[i]);
            else if (tCandid[i] == 2) fprintf(flot, "\n%d\n%d", tEtu1[i], tEtu2[i]);
            else if (tCandid[i] == 1) fprintf(flot, "\n%d", tEtu1[i]);
        }
    }

    fclose(flot);
    
    flot = fopen("DATA/etudiants.don", "w");
    if (flot == NULL) return -1; // Problème ouverture fichier

    if (*tlogEtu > 0) {
        for (int i = 0; i < *tlogEtu; i++) {
            fprintf(flot, "%d %d %.2f\n", tNumEtu[i], tRefStage[i], tNoteFinal[i]);
        }
    }

    fclose(flot);
    return 1; // Fonction réussi
}


/**
 * \brief Affiche les informations de tous les stages présents dans les tableaux.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \param tmax Taille physique du tableau.
 * \return 1 si tout s'est bien passé.
 */
int afficherTableau(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    int code;

    printf("\nREF\tDPT\tPOURVU\tCANDID\tETU1\tETU2\tETU3\n");
    for (int i=0; i < *tlog; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", tRef[i], tDpt[i], tPourvu[i], tCandid[i], tEtu1[i], tEtu2[i], tEtu3[i]);
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche uniquement les stages qui ont été pourvus.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \return 1 si tout s'est bien passé.
 */
int afficherStagesPourvus(int tRef[], int tDpt[], int tPourvu[], int *tlogOffre, int tNumEtu[], int tRefStage[], int *tlogEtu) {
    int stagePourvu = 0;

    printf("\nREF\tDPT\tETU\n");

    for (int i = 0; i < *tlogOffre; i++) {
        if (tPourvu[i] == 1) {
            printf("%d\t%d", tRef[i], tDpt[i]);

            int etudiantAffecte = 0;
            for (int j = 0; j < *tlogEtu; j++) {
                if (tRefStage[j] == tRef[i]) {
                    etudiantAffecte = tNumEtu[j];
                    break;
                }
            }
            printf("\t%d\n", etudiantAffecte);
            stagePourvu = 1;
        }
    }

    if (stagePourvu == 0) {
        printf("\nAucun stage pourvu pour le moment.\n");
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche uniquement les stages qui n'ont pas encore été pourvus.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tlog Taille logique du tableau.
 * \return 1 si tout s'est bien passé.
 */
int afficherStagesNonPourvus(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog) {
    printf("\nStages non pourvus :\n");
    printf("REF\tDPT\tNB CANDID\n");
    for (int i = 0; i < *tlog; i++) {
        if (tPourvu[i] == 0) {
            printf("%d\t%d\t%d\n", tRef[i], tDpt[i], tCandid[i]);
        }
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche les étudiants qui n'ont pas encore de stage.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tlogEtu Taille logique du tableau.
 * \return 1 si tout s'est bien passé.
 */
int afficherEtudiantsSansStage(int tNumEtu[], int tRefStage[], int *tlogEtu) {
    printf("\nÉtudiants sans stage :\n");
    for (int i = 0; i < *tlogEtu; i++) {
        if (tRefStage[i] == -1) {
            printf("ID Étudiant: %d\n", tNumEtu[i]);
        }
    }
    return 1; // Fonction réussi
}

/**
 * \brief Affiche les détails d'un stage particulier.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \return 1 si tout s'est bien passé, -1 si le stage n'a pas été trouvé.
 */
int afficherInfoStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog) {
    int ref;
    printf("\nNuméro de référence du stage à afficher: ");
    scanf("%d", &ref);

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            printf("\nInformations du stage :\n");
            printf("REF: %d, DPT: %d, Pourvu: %d, Candidats: %d, ETU1: %d, ETU2: %d, ETU3: %d\n", tRef[i], tDpt[i], tPourvu[i], tCandid[i], tEtu1[i], tEtu2[i], tEtu3[i]);
            return 1; // Fonction réussi
        }
    }
    return -1; // Stage non trouver
}

/**
 * \brief Recherche et affiche un ou des stage(s) à partir d'une référence ou d'un département.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tlog Taille logique du tableau.
 * \return 1 si le stage a été trouvé et affiché, -1 si le stage n'existe pas.
 */
int rechercherStage(int tRef[], int tDpt[], int tCandid[], int *tlog) {
    int choix, valeurRecherchee;
    printf("\nRecherche de stage par :\n");
    printf("\t1. Numéro de référence\n");
    printf("\t2. Département\n");
    printf("Votre choix: ");
    scanf("%d", &choix);

    if (choix == 1) {
        printf("Numéro de référence: ");
        scanf("%d", &valeurRecherchee);
        for (int i = 0; i < *tlog; i++) {
            if (tRef[i] == valeurRecherchee) {
                printf("Stage trouvé : REF: %d, DPT: %d, NB CANDID: %d\n", tRef[i], tDpt[i], tCandid[i]);
                return 1; // Fonction réussi
            }
        }
    } else if (choix == 2) {
        printf("Département: ");
        scanf("%d", &valeurRecherchee);
        for (int i = 0; i < *tlog; i++) {
            if (tDpt[i] == valeurRecherchee) {
                printf("Stage trouvé : REF: %d, DPT: %d, NB CANDID: %d\n", tRef[i], tDpt[i], tCandid[i]);
            }
        }
        return 1; // Fonction réussi
    }
    return -1; // Aucun stage trouvé
}

/**
 * \brief Ajoute une nouvelle offre de stage dans les tableaux.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \param tmax Taille physique du tableau.
 * \return 1 si le stage a été ajouté avec succès, -1 ou -2 si il y a eu une erreur.
 */
int ajoutStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tmax) {
    int ref, dept;
    
    printf("\nNuméro de référence du stage: ");
    scanf("%d", &ref);
    printf("Département du stage: ");
    scanf("%d", &dept);

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) return -1; // Stage existe déjà
    }
    
    if (*tlog < tmax) {
        tRef[*tlog] = ref;
        tDpt[*tlog] = dept;
        tPourvu[*tlog] = 0;
        tCandid[*tlog] = 0;
        tEtu1[*tlog] = 0;
        tEtu2[*tlog] = 0;
        tEtu3[*tlog] = 0;
        (*tlog)++;
        return 1; // Fonction réussi
    }
    else {
        return -2; // Tableau trop petit
    }
}

/**
 * \brief Décalle à gauche tout les tableaux des stages.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \param ref Numéro de référence du stage à décaler.
 * \return 1 si le stage a été supprimé avec succès, -1 si le stage n'a pas été trouvé.
 */
int decalerAgauche(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int ref) {
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            for (int j = i; j < *tlog - 1; j++) {
                tRef[j] = tRef[j + 1];
                tDpt[j] = tDpt[j + 1];
                tPourvu[j] = tPourvu[j + 1];
                tCandid[j] = tCandid[j + 1];
                tEtu1[j] = tEtu1[j + 1];
                tEtu2[j] = tEtu2[j + 1];
                tEtu3[j] = tEtu3[j + 1];
            }
            (*tlog)--;
            printf("Stage supprimé avec succès!\n");
            return 1; // Fonction réussi
        }
    }
    return -1; // Problème
}

/**
 * \brief Supprime une offre de stage du tableau.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau.
 * \return 1 si le stage a été supprimé avec succès, -1 si le stage n'a pas été trouvé.
 */
int supprimerStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog) {
    int ref, dept, code;
    printf("\nNuméro de référence du stage à supprimer: ");
    scanf("%d", &ref);

    code = decalerAgauche(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlog, ref);
    if (code == 1) return 1; // Aucun problème
    else return -1; // Stage non trouvé
}

/**
 * \brief Affiche les stages disponibles
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tlog Taille logique du tableau des offres de stages.
 */
void StagesDispo(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlog) {
    for (int i = 0; i < *tlog; i++) {
        if (tPourvu[i] == 0 && tCandid[i] >= 1) {
            printf("Référence: %d, Département: %d, Nombre de candidature: %d\n", tRef[i], tDpt[i], tCandid[i]);
        }
    }
}

/**
 * \brief Affecte un étudiant à un stage spécifique.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlog Taille logique du tableau des offres de stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \return 1 si l'affectation a réussi, -1 si pas candidat, -2 si le stage existe pas.
 */
int affecterEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlog, int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    int ref, place, x;

    printf("\nStages disponibles :\n");
    StagesDispo(tRef, tDpt, tPourvu, tCandid, tlog);

    printf("\nNuméro de référence du stage: ");
    scanf("%d", &ref);

    int stageTrouve = -1;
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            stageTrouve = i;
            break;
        }
    }

    if (stageTrouve == -1) return -2; // Stage non trouver

    printf("\nÉtudiants candidats pour ce stage :\n");
    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            for (x = 0; x < *tlogEtu; x++) {
                if (tEtu1[i] == tNumEtu[x] || tEtu2[i] == tNumEtu[x] || tEtu3[i] == tNumEtu[x]) {
                    printf("ID Étudiant: %d, Note: %d\n", tNumEtu[x], tNoteFinal[x]);
                    place = x;
                }
            }
        }
    }

    int etu;
    printf("ID de l'étudiant à affecter (ou 0 pour revenir en arrière): ");
    scanf("%d", &etu);

    if (etu == 0) return -3;

    for (int i = 0; i < *tlog; i++) {
        if (tRefStage[i] != ref) {
            if (tEtu1[i] == etu) {
                tEtu1[i] = tEtu2[i];
                tEtu2[i] = tEtu3[i];
                tEtu3[i] = 0;
                tCandid[i]--;
            }
            else if (tEtu2[i] == etu) {
                tEtu2[i] = tEtu3[i];
                tEtu3[i] = 0;
                tCandid[i]--;
            }
            else if (tEtu3[i] == etu) {
                tEtu3[i] = 0;
                tCandid[i]--;
            }
        }
    }

    for (int j = 0; j < *tlogEtu; j++) {
        if (tNumEtu[j] == etu) {
            tRefStage[j] = ref; 
            break;
        }
    }

    for (int i = 0; i < *tlog; i++) {
        if (tRef[i] == ref) {
            tPourvu[i] = 1;
            tCandid[i] = 0;
            tEtu1[i] = 0;
            tEtu2[i] = 0;
            tEtu3[i] = 0;
            return 1; // Fonction réussi
        }
    }
    return -1; // L'étudiant n'est pas candidat pour ce stage
}

/**
 * \brief Affiche le menu du responsable.
 * 
 * \return Le choix de l'utilisateur.
 */
int menuResponsable(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Ajouter une offre de stage\n");
    printf("\t2. Supprimer une offre de stage\n");
    printf("\t3. Affecter un stage à un étudiant\n");
    printf("Affichage :\n");
    printf("\t4. Afficher tous les stages\n");
    printf("\t5. Afficher les stages pourvus avec étudiants\n");
    printf("\t6. Afficher les stages non pourvus\n");
    printf("\t7. Afficher les étudiants sans stage\n");
    printf("\t8. Rechercher un stage (par numéro ou département)\n");
    printf("\t9. Afficher les informations d'un stage donné\n");
    printf("\t10. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions du responsable de stage.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tmaxOffre Taille physique du tableau des offres de stages.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tmaxEtu Taille physique du tableau d'étudiants.
 * \return 1 si toutes les actions ont été effectuées avec succès, -1 si une erreur est survenue.
 */
int globalResponsable(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
    int choix, code;
    choix = menuResponsable();
    while (choix != 10) {
        switch (choix) {
        // Action :
            case 1: // Ajouter une offre de stage
                code = ajoutStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tmaxOffre);
                if (code == 1) printf("\nLe stage a été ajouté avec succès !\n");
                if (code == -1) printf("\nLe stage avec ce numéro de référence et ce département existe déjà !\n");
                if (code == -2) printf("\nLe tableau est trop petit !\n");
                break;

            case 2: // Supprimer une offre de stage
                code = supprimerStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre);
                if (code == 1) printf("\nLe stage a été supprimé avec succès !\n");
                if (code == -1) printf("\nAucun stage trouvé avec ce numéro de référence !\n");
                break;

            case 3: // Affecter un stage à un étudiant
                code = affecterEtudiant(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
                if (code == 1) printf("\nL'étudiant a été affecté avec succès !\n");
                if (code == -1) printf("\nL'étudiant n'est pas candidat pour ce stage.\n");
                if (code == -2) printf("\nStage non trouvé.\n");
                break;

        // Affichage :
            case 4: // Afficher tous les stages
                code = afficherTableau(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tmaxOffre);
                break;

            case 5: // Afficher les stages pourvus avec étudiants affectés
                code = afficherStagesPourvus(tRef, tDpt, tPourvu, tlogOffre, tNumEtu, tRefStage, tlogEtu);
                break;

            case 6: // Afficher les stages non pourvus
                code = afficherStagesNonPourvus(tRef, tDpt, tPourvu, tCandid, tlogOffre);
                break;

            case 7: // Afficher les étudiants sans stage
                code = afficherEtudiantsSansStage(tNumEtu, tRefStage, tlogEtu);
                break;

            case 8: // Rechercher un stage par numéro ou département
                code = rechercherStage(tRef, tDpt, tCandid, tlogOffre);
                if (code == -1) printf("\nStage non trouvé !\n");
                break;

            case 9: // Afficher les informations d'un stage donné
                code = afficherInfoStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre);
                if (code == -1) printf("\nStage non trouvé !\n");
                break;

            default: // Choix invalide
                printf("\nChoix non valide !\n");
                break;
        }
        choix = menuResponsable();
    }
    code = modificationFichier(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
    if (code == 1) return 1; // Fonction réussi
    else return -1; // Problème ouverture fichier
}


/**
 * \brief Affiche la liste des stages disponibles.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tlogOffre Taille logique du tableau des offres de stages
 * \return 1 si l'affichage s'est bien déroulé.
 */
int listeStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int *tlogOffre) {
    printf("\nListe des stages disponibles :\n");
    int stageTrouve = 0;

    for (int i = 0; i < *tlogOffre; i++) {
        if (tPourvu[i] == 0 && tCandid[i] < 3) {
            printf("Référence: %d, Département: %d, Nombre de candidatures: %d\n", tRef[i], tDpt[i], tCandid[i]);
            stageTrouve = 1;
        }
    }
    if (stageTrouve == 0) return -1;
    return 1; // Fonction réussi 
}

/**
 * \brief Permet à un étudiant de candidater à un stage.
 *
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlogOffre Taille logique du tableau des offres de stages
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param etudiantID ID de l'étudiant qui candidate.
 */
int candidaterStage(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlogOffre, int *tlogEtu, int tNumEtu[], int etudiantID) {
    int refStage, foundStage = 0;
    int nbCandidatures = 0;

    for (int i = 0; i < *tlogEtu; i++) {
        if (tNumEtu[i] == etudiantID) {
            nbCandidatures++;
        }
    }

    if (nbCandidatures >= 3) return -1;

    printf("\nEntrez la référence du stage pour candidater (0: Annuler): ");
    scanf("%d", &refStage);

    if (refStage == 0) return -2;

    for (int i = 0; i < *tlogOffre; i++) {
        if (tRef[i] == refStage) {
            if (tPourvu[i] == 1) return -3;
            if (tEtu1[i] == etudiantID || tEtu2[i] == etudiantID || tEtu3[i] == etudiantID) return -4;

            if (tCandid[i] < 3) {
                if (tEtu1[i] == 0) {
                    tEtu1[i] = etudiantID;
                } else if (tEtu2[i] == 0) {
                    tEtu2[i] = etudiantID;
                } else if (tEtu3[i] == 0) {
                    tEtu3[i] = etudiantID;
                }
                tCandid[i]++;

                return 1; // Fonction réussi
            } 
            else return -5;
        }
    }
    return -6;
}

/**
 * \brief Permet de voir les candidatures d'un étudiant.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param etudiantID Identifiant de l'étudiant concerné.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \return 0 si la consultation s'est bien déroulée, -1 en cas d'erreur.
 */
int voirCandidature(int tNumEtu[], int tRefStage[], int tRef[], int tDpt[], int tPourvu[], int tEtu1[], int tEtu2[], int tEtu3[], int *tlogEtu, int *tlogOffre, int etudiantID, int tCandid[]) {
    int indexEtu = -1;
    for (int i = 0; i < *tlogEtu; i++) {
        if (tNumEtu[i] == etudiantID) {
            indexEtu = i;
            break;
        }
    }
    
    if (indexEtu == -1) return -1; // Étudiant non trouvé

    int refStage = tRefStage[indexEtu];

    if (refStage == -1) {
        printf("\nMes candidatures :\n");
        printf("REF\tDPT\tNB CANDID\n");
        for (int i = 0; i < *tlogOffre; i++) {
            if (tEtu1[i] == etudiantID || tEtu2[i] == etudiantID || tEtu3[i] == etudiantID) {
                printf("%d\t%d\t%d\n", tRef[i], tDpt[i], tCandid[i]);
            }
        }
        return 1; // Fonction réussi
    } else {
        for (int j = 0; j < *tlogOffre; j++) {
            if (tRef[j] == refStage) {
                printf("\nVous avez été affecter à un stage :\n");
                printf("Référence: %d, Département: %d\n", tRef[j], tDpt[j]);
                return 1; // Fonction réussi
            }
        }
        return -2; // Aucun stage trouvé
    }

    return 1; // Fonction réussie
}

/**
 * \brief Vérifie si l'étudiant existe à partir de son identifiant.
 * 
 * \param id Identifiant de l'étudiant.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tlogEtu Taille logique du tableau.
 * \return 1 si l'étudiant est trouvé, -1 sinon.
 */
int verifieLogin(int id, int tNumEtu[], int tlogEtu) {
    for (int i = 0; i < tlogEtu; i++) {
        if (tNumEtu[i] == id) {
            return 1; // Fonction réussi
        }
    }
    return -1;
}

/**
 * \brief Gère la connexion des étudiants.
 * 
 * \return L'identifiant de l'étudiant.
 */
int login(void) {
    int id;
    printf("\nQuel est votre identifiant : ");
    scanf("%d", &id);
    return id;
}

/**
 * \brief Affiche le menu pour les étudiants.
 * 
 * \return Le choix de l'étudiant.
 */
int menuEtudiant(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Afficher la liste de stage\n");
    printf("\t2. Candidater à un stage\n");
    printf("\t3. Voir vos candidatures\n");
    printf("\t4. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions de l'étudiant.

 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tmaxOffre Taille physique du tableau des offres de stages.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tmaxEtu Taille physique du tableau d'étudiants.
 * \return 1 si toutes les actions ont été effectuées avec succès, -1 en cas d'erreur.
 */
int globalEtudiant(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
    int choix, code, id;
    
    id = login();
    code = verifieLogin(id, tNumEtu, *tlogEtu);
    if (code == 1) {
        choix = menuEtudiant();
        while(choix!=4) {
            switch (choix)
            {
            case 1: // Afficher la liste de stage
                code = listeStage(tRef, tDpt, tPourvu, tCandid, tlogOffre);
                if (code == -1) printf("\nAucun stage n'a été trouver !\n");
                break;
            
            case 2: // Candidater à un stage
                code = candidaterStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tlogEtu, tNumEtu, id);
                if (code == 1) printf("\nCandidature réussie pour le stage !\n");
                if (code == -1) printf("\nVous avez atteint le nombre maximum de candidatures (3).\n");
                if (code == -2) printf("\nAucun candidature n'a été faites !\n");
                if (code == -3) printf("\nLe stage a déjà été pourvu !\n");
                if (code == -4) printf("\nVous êtes déjà candidat pour ce stage.\n");
                if (code == -5) printf("\nLe stage que vous avez demandé possède déjà 3 candidats.\n");
                if (code == -6) printf("\nStage non trouvé.\n");
                break;
            
            case 3: // Voir vos candidatures
                code = voirCandidature(tNumEtu, tRefStage, tRef, tDpt, tPourvu, tEtu1, tEtu2, tEtu3, tlogEtu, tlogOffre, id, tCandid);
                if (code == -1) printf("Étudiant non trouvé.\n");
                if (code == -2) printf("Aucun stage affecté trouvé.\n");
                break;
            
            default: // Choix invalide
                printf("\nChoix non valide !\n");
                break;
            }
            choix = menuEtudiant();
        }
        code = modificationFichier(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
        if (code == 1) return 1; // Fonction réussi
        if (code == -1) return -1;
    }
    else return -2;
}


/**
 * \brief Ajoute les notes pour un étudiant dans le tableau.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogEtu Taille logique du tableau.
 * \return La moyenne calculée si tout s'est bien passé, sinon -1.
 */
int ajouterNotes(int tNumEtu[], float tNoteFinal[], int *tlogEtu) { 
    int idEtu;
    float noteEntreprise, noteRapport, noteSoutenance;
    float moyenne; 
    int place = -1; 

    printf("\nEntrez l'ID de l'étudiant : "); 
    scanf("%d", &idEtu); 

    for (int i = 0; i < *tlogEtu; i++) { 
        if (tNumEtu[i] == idEtu) { 
            place = i; 
            break; 
        } 
    } 
    if (place == -1) return -1; // Etudiant non trouvé 

    printf("Entrez la note d'entreprise : "); 
    scanf("%f", &noteEntreprise);
    if (noteEntreprise <  0 || noteEntreprise > 20) return -2;
    printf("Entrez la note du rapport : "); 
    scanf("%f", &noteRapport);
    if (noteRapport <  0 || noteRapport > 20) return -3;
    printf("Entrez la note de soutenance : "); 
    scanf("%f", &noteSoutenance);
    if (noteSoutenance <  0 || noteSoutenance > 20) return -4;

    moyenne = (noteEntreprise + noteRapport + noteSoutenance) / 3;
    tNoteFinal[place] = moyenne; 

    return moyenne; 
}

/**
 * \brief Affiche les notes des étudiants.
 * 
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogEtu Taille logique du tableau.
 * \return 1 si l'affichage a été effectué correctement, -1 si aucun étudiant n'est à afficher.
 */
int afficherNotes(int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogEtu) {
    if (*tlogEtu <= 0) return -1;

    printf("\nNUM\tNOTE\n");
    for (int i = 0; i < *tlogEtu; i++) {
        printf("%d\t%.2f\n", tNumEtu[i], tNoteFinal[i]);
    }
    return 1;
}

/**
 * \brief Affiche le menu pour le jury.
 * 
 * \return Le choix de l'utilisateur.
 */
int menuJury(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Ajouter des notes\n");
    printf("\t2. Afficher les notes\n");
    printf("\t3. Quitter\n");
    printf("Votre choix: ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions du jury.
 * 
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tmaxOffre Taille physique du tableau des offres de stages.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tmaxEtu Taille physique du tableau d'étudiants.
 * \return 1 si toutes les actions ont été effectuées avec succès, -1 en cas d'erreur.
 */
int globalJury(int tRef[], int tDpt[], int tPourvu[], int tCandid[], int tEtu1[], int tEtu2[], int tEtu3[], int tNumEtu[], int tRefStage[], float tNoteFinal[], int *tlogOffre, int tmaxOffre, int *tlogEtu, int tmaxEtu) {
   int choix, code;
    choix = menuJury();
    while (choix!=3) {
        switch (choix) {
        case 1: // Ajouter une offre de stage
            code = ajouterNotes(tNumEtu, tNoteFinal, tlogEtu);
            if (code == -1) printf("\nL'étudiant n'a pas été trouver !\n");
            if (code == -2) printf("\nLa note d'entreprise est incorrecte !\n");
            if (code == -3) printf("\nLa note de rapport est incorrecte !\n");
            if (code == -4) printf("\nLa note de soutenance est incorrecte !\n");
            break;
        
        case 2: // Afficher notes
            code = afficherNotes(tNumEtu, tRefStage, tNoteFinal, tlogEtu);
            if (code == -1) printf("Aucun étudiant à afficher.\n");
            break;

        default: // Choix invalide
            printf("\nChoix non valide !\n");
            break;
        }
        choix = menuJury();
    }
    code = modificationFichier(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tlogOffre, tNumEtu, tRefStage, tNoteFinal, tlogEtu);
    if (code == 1) return 1; // Fonction réussi
    else return -1; 
}


/**
 * \brief Affiche le menu principal du programme.
 * 
 * \return Le choix de l'utilisateur.
 */
int menuGlobal(void) {
    int choix;
    printf("\nAction :\n");
    printf("\t1. Responsable\n");
    printf("\t2. Elève\n");
    printf("\t3. Jury\n");
    printf("\t4. Quitter\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}

/**
 * \brief Gère les actions principales de l'application.
 * 
 * \param choix Le choix de l'utilisateur.
 * \param code Le code de retour des différentes fonctions
 * \param tRef[] Tableau des références des stages.
 * \param tDpt[] Tableau des départements associés aux stages.
 * \param tPourvu[] Tableau indiquant si un stage est pourvu.
 * \param tCandid[] Tableau contenant le nombre de candidatures pour chaque stage.
 * \param tEtu1[] Tableau contenant l'ID 1 de l'étudiant qui candidate aux stages.
 * \param tEtu2[] Tableau contenant l'ID 2 de l'étudiant qui candidate aux stages.
 * \param tEtu3[] Tableau contenant l'ID 3 de l'étudiant qui candidate aux stages.
 * \param tNumEtu[] Tableau des numéros des étudiants.
 * \param tRefStage[] Tableau des références de stages associés aux étudiants.
 * \param tNoteFinal[] Tableau des moyennes finales des étudiants.
 * \param tlogOffre Taille logique du tableau des offres de stages.
 * \param tmaxOffre Taille physique du tableau des offres de stages.
 * \param tlogEtu Taille logique du tableau d'étudiants.
 * \param tmaxEtu Taille physique du tableau d'étudiants.
 */
void global(void) {
    int choix, code;
    // Tableaux Offres De Stages
    int tRef[200]={0}, tDpt[200]={0}, tPourvu[200]={0}, tCandid[200]={0}, tEtu1[200]={0}, tEtu2[200]={0}, tEtu3[200]={0}, tmaxOffre=200, tlogOffre=0;
    // Tableaux Liste Etudiants
    int tNumEtu[200]={0}, tRefStage[200]={0}, tmaxEtu=200, tlogEtu=0;
    float tNoteFinal[200];

    code = remplirOffreStage(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, &tlogOffre, tmaxOffre);
    if (code == -1) {
        printf("\nUne erreur est survenue lors du chargement du fichier (Offre Stage) !\n");
        exit(1); // Termine tout
    }

    code = remplirListeEtudiants(tNumEtu, tRefStage, tNoteFinal, &tlogEtu, tmaxEtu);
    if (code == -1) {
        printf("\nUne erreur est survenue lors du chargement du fichier (Liste) !\n");
        exit(1);
    } else if (code == -2) {
        printf("\nLe fichier étudiant est vide !\n");
        exit(1);
    }

    choix = menuGlobal();
    while(choix!=4) {
        switch (choix) {
            case 1: // Partie Responsable
                code = globalResponsable(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;
            
            case 2: // Partie Etudiants
                code = globalEtudiant(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;
            
            case 3: // Partie Jury
                code = globalJury(tRef, tDpt, tPourvu, tCandid, tEtu1, tEtu2, tEtu3, tNumEtu, tRefStage, tNoteFinal, &tlogOffre, tmaxOffre, &tlogEtu, tmaxEtu);
                break;

            default: // Choix invalide
                printf("\nChoix non valide !\n");
                break;
        }
        choix = menuGlobal();
    }
}