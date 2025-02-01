# 🎮 SAE 1.02 - Jeu de Combat Tour par Tour

## 📜 Description

**SAE 1.02** est un projet en langage **C** qui implémente un jeu de combat tour par tour entre un joueur et des monstres. Le jeu inclut un système de gestion des duels, un scoreboard et la possibilité de créer des parties personnalisées.

## ⚡ Fonctionnalités

- 🏆 **Combat Tour par Tour** : Affrontez des monstres avec différentes stratégies.
- 📊 **Scoreboard** : Suivez les meilleurs scores et statistiques des joueurs.
- 📝 **Création de Parties** : Enregistrez et chargez vos propres parties prédéfinies.
- 📂 **Sauvegarde des Scores** : Stockage des performances des joueurs.

## 🛠️ Prérequis

Assurez-vous d'avoir un compilateur **C** installé sur votre machine (GCC recommandé).

## 🚀 Compilation et exécution

1. Clonez ce repository ou téléchargez les fichiers du projet.
2. Compilez le programme avec :
   ```sh
   gcc SAE.c TestSAE.c -o jeu_combat
   ```
3. Exécutez le programme avec :
   ```sh
   ./jeu_combat
   ```

## 📂 Organisation des fichiers

- `SAE.c` : Contient les fonctions principales du jeu.
- `SAE.h` : Déclarations des structures et prototypes de fonctions.
- `TestSAE.c` : Fichier principal contenant la fonction `main()` et des tests de duel.
- `Parties/partie1.txt` : Exemple de scénario de combat.
- `Parties/scoreboard.txt` : Fichier stockant les meilleurs scores.

## 📜 Licence

Ce projet est sous licence MIT. Vous êtes libre de le modifier et de le redistribuer.