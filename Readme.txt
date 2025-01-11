# SFMSim - Simulateur de gestion de fichiers en mémoire secondaire

SFMSim est un simulateur de gestion de fichiers en mémoire secondaire, permettant de gérer des fichiers stockés dans un système de mémoire secondaire avec différentes méthodes d'organisation (contiguë et chaînée). Le programme offre diverses fonctionnalités permettant de manipuler les enregistrements, effectuer des recherches, des suppressions et gérer la mémoire de manière efficace.

## Table des matières
1. [Fichiers sources](#fichiers-sources)
2. [Fichiers de configuration](#fichiers-de-configuration)
3. [Fonctionnalités principales](#fonctionnalités-principales)
4. [Démarrage du projet](#démarrage-du-projet)

## Fichiers sources

Le projet contient les fichiers sources suivants :

### `main.c`
Ce fichier contient la fonction principale `main()`, qui est le point d'entrée du programme. Il gère l'affichage du menu principal, l'interaction avec l'utilisateur et l'appel des différentes fonctions du projet selon les choix de l'utilisateur. Il sert de contrôleur pour orchestrer l'exécution des opérations de gestion de la mémoire secondaire, des fichiers et des enregistrements.
- **Fonctionnalités principales** :
  - Affichage du menu avec les options disponibles pour l'utilisateur.
  - Prise des entrées de l'utilisateur et redirection vers les fonctions appropriées.
  - Initialisation et gestion des ressources nécessaires à l'exécution du programme.

### `structures.h`
Ce fichier contient toutes les structures de données essentielles pour la gestion de la mémoire et des fichiers. Il définit la manière dont les informations sont organisées dans le programme, telles que les enregistrements, les blocs et les fichiers.
- **Contenu** :
  - Déclaration des structures comme `Enregistrement`, `Bloc`, `Metadonnee`, etc.
  - Définition des tailles maximales pour certaines variables (par exemple, `MAX_DATA_SIZE`).
  - Déclaration des types et des variables globales nécessaires pour la gestion de la mémoire et des fichiers.

### `FunctionsContigues.h`
Ce fichier contient les déclarations des fonctions liées à la gestion de la mémoire secondaire en mode **contigu**. Les opérations sur les fichiers, tels que la création, l'insertion, le tri et la gestion des enregistrements dans un fichier contigu, sont définies ici.
- **Fonctionnalités principales** :
  - Fonctions pour initialiser, charger et manipuler des fichiers en mode contigu.
  - Gestion des opérations comme l'insertion, la recherche, la suppression d'enregistrements, et la gestion du tri dans les fichiers.

### `FunctionsChaine.h`
Ce fichier contient les déclarations des fonctions relatives à la gestion de la mémoire secondaire en mode **chaîné**. Il définit des fonctions similaires à celles de `FunctionsContigues.h`, mais pour les fichiers où les blocs sont liés entre eux de manière dynamique (chaînée).
- **Fonctionnalités principales** :
  - Fonctions pour gérer la création, l'insertion et la recherche d'enregistrements dans un fichier chaîné.
  - Gestion des opérations sur les blocs chaînés, telles que l'ajout de blocs et la gestion des pointeurs entre les blocs.

### `Buffer.h`
Ce fichier contient les déclarations des fonctions relatives à la gestion du **buffer** en mémoire. Le buffer sert à stocker temporairement les blocs de données pour éviter des accès fréquents à la mémoire secondaire. 
- **Fonctionnalités principales** :
  - Initialisation du buffer.
  - Ajout, lecture et écriture des blocs dans le buffer.
  - Gestion de l'éviction des blocs en cas de dépassement de la capacité du buffer (par exemple, en utilisant la stratégie FIFO).
  - Synchronisation entre le buffer et la mémoire secondaire.

## Fichiers de configuration

Le projet contient les fichiers de configuration suivants :

### `lunch.json`
Ce fichier de configuration est utilisé pour définir les paramètres d'exécution de l'application, comme les options de démarrage, les chemins des fichiers de mémoire secondaire, ou d'autres réglages essentiels pour initialiser correctement le programme.
- **Contenu typique** :
  - Paramètres de configuration pour le démarrage de l'application.
  - Variables liées aux ressources, comme la taille de la mémoire ou des blocs, et les chemins des fichiers à utiliser.

### `tasks.json`
Ce fichier de configuration est utilisé pour spécifier les tâches ou les opérations à exécuter dans le cadre du programme. Il peut contenir des informations sur les opérations à effectuer sur les fichiers ou les enregistrements (par exemple, insérer des enregistrements, rechercher des fichiers, etc.).
- **Contenu typique** :
  - Liste de tâches ou d'opérations avec les paramètres nécessaires pour chaque tâche.
  - Informations sur l'ordre des opérations ou les priorités.

## Fonctionnalités principales

Le programme offre un menu interactif avec les options suivantes :

1. **Initialiser la mémoire secondaire** : Initialise la mémoire secondaire pour la gestion des fichiers.
2. **Créer un fichier et le charger** : Crée un fichier et charge les données dans la mémoire secondaire.
3. **Afficher l’état de la mémoire secondaire** : Affiche l’état actuel de la mémoire secondaire, y compris la disponibilité des blocs et des fichiers.
4. **Afficher les métadonnées des fichiers** : Affiche les métadonnées associées aux fichiers, telles que le nombre de blocs et d'enregistrements.
5. **Insérer un nouvel enregistrement** : Permet d’ajouter un enregistrement dans un fichier en mémoire.
6. **Rechercher un enregistrement par ID** : Recherche un enregistrement spécifique en utilisant son identifiant unique.
7. **Supprimer un enregistrement** : Supprime un enregistrement du fichier.
8. **Défragmenter un fichier** : Optimise l'organisation des blocs dans un fichier pour réduire la fragmentation.
9. **Supprimer un fichier** : Supprime un fichier de la mémoire secondaire.
10. **Renommer un fichier** : Modifie le nom d'un fichier dans le système de gestion de mémoire.
11. **Compactage de la mémoire secondaire** : Réorganise la mémoire secondaire pour optimiser l'espace utilisé.
12. **Vider la mémoire secondaire** : Supprime toutes les données et réinitialise la mémoire secondaire.
13. **Changer mode global** : Permet de changer le mode global (chaîné ou contigu) pour l’organisation des fichiers.
14. **Afficher le contenu d'un fichier** : Affiche le contenu d'un fichier spécifique.
15. **Quitter** : Quitte le programme.

## Démarrage du projet

Pour démarrer le projet, suivez ces étapes :

1. Clonez le repository ou téléchargez les fichiers sources.
2. Assurez-vous que les dépendances nécessaires sont installées sur votre système (par exemple, compilateur C).
3. Ouvrez le projet dans un éditeur de texte ou un environnement de développement intégré (IDE).
4. Compilez le projet et exécutez-le.
5. Utilisez le menu interactif pour effectuer les opérations souhaitées.
