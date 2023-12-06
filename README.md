
# IA pour le jeu d'Othello

Un jeu d'Othello avec l'IA en utilse le langage C et openGL GLUT. Il existe 2 modes de jeu: jouer avec l'humain et jouer avec l'intelligence artificielle.

Pour savoir comment jouer l'Othello, cliquer sur l'image suivant:

[![alt text](othello_start.png)](https://www.eothello.com/)

## Compilation

### Prérequis :
- Installer Make et Glut avec la commande:
    ```
    sudo apt-get install make
    ```
  et
    ```
    sudo apt-get install libglut3-dev
    ```

- Cloner le projet de [mon GitHub](https://github.com/Viet281101/OthelloAI) sur votre ordinateur:
  ```
  git clone https://github.com/Viet281101/OthelloAI.git
  ```

### Pour compiler le jeu :
- Aller dans la répertoire du projet "AI_Player" ou "Human_Player"
    ```
    cd Human_Player/
    ```
    ou
    ```
    cd AI_Player/
    ```
- Compiler avec le Makefile:
    ```
    make
    ```

## Lancement :
- Lancez le fichier **othello**
    ```
    ./othello
    ```

## Nettoyer :
- Nettoyez les fichiers avec make:
  ```
  make clean
  ```
