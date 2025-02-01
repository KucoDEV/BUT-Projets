# 📚 Projet SAE 1.01 - Gestion des Stages

## 📜 Description

**SAE 1.01** est un programme en langage **C** permettant la gestion des offres de stages et des candidatures d'étudiants. Ce projet a été conçu pour faciliter l'affectation des stages aux étudiants en fonction de leurs candidatures et des critères définis par les entreprises.

## ⚡ Fonctionnalités

- 📌 **Gestion des stages** : ajout, suppression et modification des offres de stage.
- 👩‍🎓 **Gestion des étudiants** : suivi des candidatures et affectation des stages.
- 📊 **Affichage des statistiques** : stages disponibles, stages pourvus, étudiants sans stage.
- 🏆 **Attribution des notes** aux étudiants après le stage.
- 💾 **Sauvegarde et chargement** des données dans des fichiers.

## 🛠️ Prérequis

Assurez-vous d'avoir un compilateur **C** (GCC recommandé) installé sur votre machine.

## 🚀 Compilation et exécution

1. Clonez ce repository ou téléchargez les fichiers du projet.
2. Compilez le programme avec :
   ```sh
   gcc SAE.c TestSAE.c -o gestion_stages
   ```
3. Exécutez le programme avec :
   ```sh
   ./gestion_stages
   ```

## 📂 Organisation des fichiers

- `SAE.c` : Contient les fonctions principales de gestion des stages et des étudiants.
- `SAE.h` : Contient les déclarations des fonctions et les structures de données.
- `TestSAE.c` : Fichier principal contenant la fonction `main()`.
- `index.html` : Documentation générée avec **Doxygen**.
- `etudiants.don` / `offrestage.don` : Fichiers contenant les données des étudiants et des stages.

## ⚠️ État du projet

Ce projet n'a pas été mis à jour depuis près d'un an. Son bon fonctionnement actuel n'est pas garanti.

## 📜 Licence

Ce projet est sous licence MIT. Vous êtes libre de le modifier et de le redistribuer.