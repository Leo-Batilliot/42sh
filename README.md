# 42sh - A Shell Project

## Description
42sh est un shell développé dans le cadre du projet 42sh d'Epitech.  
Inspiré de `tcsh`, il offre plusieurs fonctionnalités permettant d'exécuter des commandes, de gérer des variables d'environnement, de traiter des redirections, et plus encore.  
Ce projet a été réalisé en C, en respectant les contraintes imposées par les normes d'EPITECH et les attentes du projet.  

## Compilation

### Prérequis
Avant de compiler le projet, assurez-vous d'avoir les outils suivants installés :
- GCC
- Make

### Instructions
1. Clonez le dépôt sur votre machine :
   `git clone git@github.com:Leo-Batilliot/42sh.git`

2. Accédez au répertoire du projet :
   `cd 42sh`

3. Compilez le projet avec la commande suivante :
   `make`

4. L'exécutable sera généré sous le nom `42sh`.

5. Pour nettoyer les fichiers objets générés lors de la compilation :
   `make clean`

6. Pour supprimer tous les fichiers générés, y compris l'exécutable :
   `make fclean`

7. Pour nettoyer et recompiler le projet :
   `make re`

### Exemple d'utilisation

Après avoir compilé le projet, vous pouvez lancer 42sh en exécutant la commande `./42sh`

Une fois dans le shell, vous pouvez utiliser des commandes classiques ainsi que les fonctionnalités suivantes :  

## Fonctionnalités

### Commandes Supportées
- `cd` : Change le répertoire de travail.
- `alias` : Permet d'afficher ou de créer/remplacer un alias.
- `unalias` : Permet de supprimer des alias (`unalias *` supprime tous les alias comme `clean alias`).  
- `env` : Affiche les variables d'environnement.
- `setenv` : Modifie ou ajoute une variable d'environnement.
- `unsetenv` : Supprime une variable d'environnement.
- `history` : Affiche l'historique des commandes.
- `clean` : Permet de supprimer/nettoyer certaines variables (exemple : `clean history`, `clean alias`)  
- `color` : Permet d'afficher les différentes couleurs ou de changer celle du prompt.
- `exit` : Quitte le shell.
- `echo` : Affiche du texte ou la valeur d’une variable.  
- `which` :  Affiche le chemin absolu de la première occurrence d’une commande trouvée dans le `PATH`  
- `where` :  Affiche toutes les occurrences d’une commande dans le `PATH`, y compris les alias.  
- `repeat` :  Exécute une commande un certain nombre de fois.  

### Redirections, pipes, operateurs
Le 42sh prend en charge :
    -les redirections standards `>`, `>>`, `<`, `<<`, permettant de rediriger l'entrée/sortie vers/depuis des fichiers.  
    -les pipes `|` pour chaîner plusieurs commandes ensemble.  
    -les operateurs `||`(= ou) et `&&`(= et) pour executer une commande si celle d'avant à reussi, ou stopper a la première qui réussi, etc... 
    -les parenthèses `()` pour executer leur contenu dans un sous-shell.  
    -les guillemets `""` pour regrouper plusieurs arguments (pour donner une phrase en un seul morceau par exemple).  

### Couleur du prompt
Il est possible de changer la couleur du prompt a tout moment en utilisant la commande `color` avec : `color [couleur]`  

### Autocomplétion  
Une fonctionnalité d'autocomplétion est intégrée pour faciliter l'exécution des commandes.    
flèche haut et bas pour naviguer dans l'historique    
Tabulation pour autocompléter les commandes, fichiers ou dossiers  

### Historique des commandes
Le shell garde une trace des commandes précédemment exécutées et permet de les consulter à tout moment en utilisant la commande `history`.  

### Alias
Le shell retient les alias definis et les remplace par leur valeur.  
(exemple : la commande `alias ll ls -l` fera en sorte qu'à chaque fois que vous écrivez `ll`, `ls -l` le remplacera)  

## Structure du Code

### Structures des dossiers :

- `include` :  Contient les fichiers .h contenant les définitions de fonctions, de structures et les define.  
- `lib` : Contient les fonctions utilitaires (souvent recodées et modifiées) pour de divers projets.  
- `src/commands/` : Contient les commandes intégrées au shell telles que `cd`, `exit`, `setenv`, etc...  
- `src/utils/` : Contient des fonctions utilitaires pour le parsing, la gestion des redirections, des fichiers, et des processus.  
- `src/termios/` : Contient des fonctions liées à l'interface terminal, telles que la gestion de l'autocomplétion et de l'historique.

### Documentation

Les fonctions sont documentées de la manière suivante :
```
// nom :   nom_de_fonction
// arguments :   arguments + explications (les arguments peuvent etre N.A si il n'y a pas d'arguments)
// fonctionnalité : explications (peut etre S.E (self explanatory) si le nom de fonction est assez clair)
type_de_fonction nom_de_fonction (arguments)
```
