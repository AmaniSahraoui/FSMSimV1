#ifndef FUNCTIONSCONTIGUE_H
#define FUNCTIONSCONTIGUE_H

 #include "structures.h"  // un fichier d'en-tête avec les définitions de Bloc, Metadonnee, Enregistrement// Prototypes des fonctions///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 #include "Buffer.h"      // les fonctions de gestion des buffers intermédiaires entre la RAM et la mémoire secondaire


void initialiserMemoireSecondaire(MemoireSecondaire *memoire, int mode);
void creer_FichierContigue(MemoireSecondaire *memoire, const char *nom, int taille_en_blocs);
void afficher_Metadonnees(MemoireSecondaire *memoire, int mode);
int inserer_EnregistrementContigue(MemoireSecondaire *memoire, const char *nom, Enregistrement *enregistrement);
void rechercher_EnregistrementContigue(const char* nom_fichier, int id_enregistrement, MemoireSecondaire* memoire);
void renommer_Fichier(MemoireSecondaire *memoire, const char* nom_fichier, const char* nouveau_nom);
void afficher_contenu_du_fichier(MemoireSecondaire* memoire, const char *nom_fichier);
void supprimer_enregistrementContigue(MemoireSecondaire *memoire, const char* nom_fichier, int id_enregistrement) ;
void defragmenter_Fichier(MemoireSecondaire *memoire, const char* nom_fichier);
void supprimer_FichierContigue(MemoireSecondaire *memoire, const char *nom_fichier) ;
void compactage_Memoire_SecondaireContigue(MemoireSecondaire* memoire);
void compactage_Contigue(MemoireSecondaire *memoire);
void vider_Memoire_Secondaire(MemoireSecondaire* memoire);
void afficher_Memoire_Secondaire(MemoireSecondaire* memoire , int mode);
void trier_FichierParIDContigu(MemoireSecondaire *memoire, Buffer *buffer, const char *nom_fichier);
///////////////////////////////////////////////////////////////  fonctions intermediaires communes
void preciser_fichier(int cas);
void preciser_nouv_fichier();
int calculer_nombre_blocs(int nb_enregistrements, int nbMax_enregistrements); //calculer le nombre de bloc par fichier
int preciser_enregistrement();
Enregistrement saisir_Enregistrement();
int preciser_logic();
void Saisir_Nombre_Enreg(int *nombre);
int calcul_max_enregistrements();
int confirmerAction();
void mettreAJourPremierBlocApresCompactage(MemoireSecondaire* memoire);
void afficherLicence();
int confirmer_Type_Memoire_Secondaire();
void changer_ModeGlobal();
void generer_DonneesAleatoires(char* buffer, int taille);
void remplir_FichierContigu(MemoireSecondaire *memoire, const char *nom_fichier);
int comparer_enregistrements_par_id(const void *a, const void *b);

/////////////////////////////////////////////////////////////// fonctions intermediaires non communes
int chercher_ID_Fichier(const char *nom_fichier, MemoireSecondaire *memoire);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int choisir_Type_Systeme_Fichier();
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void afficherMenu() {
    printf(BLEU "\n=======================================\n");
    printf("  FSMSim: Simulateur Simplifié d’un SGF (v1.0)\n");
    printf("=======================================\n" RESET);

    printf(JAUNE "1. " VERT "Initialiser la mémoire secondaire\n" RESET);
    printf(JAUNE "2. " VERT "Créer un fichier et le charger\n" RESET);
    printf(JAUNE "3. " VERT "Afficher l’état de la mémoire secondaire\n" RESET);
    printf(JAUNE "4. " VERT "Afficher les métadonnées des fichiers\n" RESET);
    printf(JAUNE "5. " VERT "Insérer un nouvel enregistrement\n" RESET);
    printf(JAUNE "6. " VERT "Rechercher un enregistrement par ID\n" RESET);
    printf(JAUNE "7. " VERT "Supprimer un enregistrement\n" RESET);
    printf(JAUNE "8. " VERT "Défragmenter un fichier\n" RESET);
    printf(JAUNE "9. " VERT "Supprimer un fichier\n" RESET);
    printf(JAUNE "10. " VERT "Renommer un fichier\n" RESET);
    printf(JAUNE "11. " VERT "Compactage de la mémoire secondaire\n" RESET);
    printf(JAUNE "12. " VERT "Vider la mémoire secondaire\n" RESET);
    printf(JAUNE "13. " VERT "Changer mode global\n" RESET);
    printf(JAUNE "14. " VERT "Afficher le contenu d'un fichier\n" RESET);
    printf(JAUNE "15. " ROUGE "Quitter\n" RESET);
    printf(BLEU "=======================================\n" RESET);
}
///////////////////////////////////////////////////////////////////////////////////////

void afficherLicence() {
    printf(JAUNE TEXTE_NOIR "===========================================\n");
    printf("         FSMSim *File System Manager Simulator* : Licence MIT\n");
    printf("==============================\n" RESET);
    printf("  Développé par : " VERT "Amani SAHRAOUI\n" RESET);
    printf("  Formation     : " BLEU "2ème Année Ingénieur en Informatique\n" RESET);
    printf("  Université    : " BLEU "USTHB - Groupe 2, Section C\n" RESET);
    printf("  Encadré par   : " VERT "Dr. LAHRECHE Abdelmadjid\n" RESET);
    printf(JAUNE TEXTE_NOIR "============================================\n\n" RESET);
}
///////////////////////////////////////////////////////////////////  Gestion mémoire secondaire
void initialiserMemoireSecondaire(MemoireSecondaire *memoire, int mode) {
    char buffer;
    if (mode==Contigue)
    printf("Spécifiez la taille de la mémoire secondaire contiguë en blocs : ");
    else
    printf("Spécifiez la taille de la mémoire secondaire  chainée en blocs : "); 
    scanf("%d", &nb_blocs);

    do {
        printf("Fixez la taille du bloc de votre disque (minimum %d octets) : ", TAILLE_BLOC_MIN);
        
        // Vérifier si la saisie est valide
        if (scanf("%d", &taille_Bloc) != 1) {
            printf("\a" JAUNE "Erreur : Veuillez entrer un nombre entier valide." RESET "\n");
            
            // Vider le tampon pour éviter une boucle infinie
            while ((buffer = getchar()) != '\n' && buffer != EOF);
            
            taille_Bloc = -1; // Réinitialiser la taille pour rester dans la boucle
        } else if (taille_Bloc < TAILLE_BLOC_MIN) {
            printf(JAUNE "Erreur : La taille du bloc doit être d'au moins %d octets." RESET "\n", TAILLE_BLOC_MIN);
        }

    } while (taille_Bloc < TAILLE_BLOC_MIN);

    memoire->nb_bloc_disque = nb_blocs;
    memoire->nb_fichiers = 0;

    // Allouer l'espace pour les blocs
    memoire->disque = (Bloc *)malloc(nb_blocs * sizeof(Bloc));
    if (memoire->disque == NULL) {
        printf("Erreur d'allocation pour les blocs du disque.\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser les blocs avec memset
    memset(memoire->disque, 0, nb_blocs * sizeof(Bloc));

    // Allouer l'espace pour les métadonnées
    memoire->fichiers = (Metadonnee *)malloc(MAX_FICHIERS * sizeof(Metadonnee));
    if (memoire->fichiers == NULL) {
        printf("Erreur d'allocation pour les métadonnées.\n");
        free(memoire->disque);
        exit(EXIT_FAILURE);
    }

    // Initialiser les métadonnées avec memset
    memset(memoire->fichiers, 0, MAX_FICHIERS * sizeof(Metadonnee));

    // Calculer le nombre maximum d'enregistrements par bloc
    nbMax_enregistrement = calcul_max_enregistrements();

    // Initialiser les blocs
    for (int i = 0; i < nb_blocs; i++) {
        memoire->disque[i].is_used = false;
        memoire->disque[i].id_fichier = -1;
        memoire->disque[i].nb_enregistrements = 0;

        // Définir le champ next_bloc
        if (i == nb_blocs - 1)
            memoire->disque[i].next_bloc = -1;  // Dernier bloc
        //else if (memoire->fichiers[i].mode_global == Chained )
        else    memoire->disque[i].next_bloc = i + 1;  // Pour le mode contigu, ce champ n'est pas inportant mais gardé pour debogage

        // Allouer l'espace pour les enregistrements
        memoire->disque[i].enregistrements = (Enregistrement *)malloc(nbMax_enregistrement * sizeof(Enregistrement));
        if (memoire->disque[i].enregistrements == NULL) {
            printf("Erreur d'allocation pour les enregistrements du bloc %d.\n", i);
            // Libérer la mémoire précédemment allouée avant d'arrêter
            for (int j = 0; j < i; j++) {
                free(memoire->disque[j].enregistrements);
            }
            free(memoire->disque);
            free(memoire->fichiers);
            exit(EXIT_FAILURE);
        }

        // Initialiser les enregistrements avec memset
        memset(memoire->disque[i].enregistrements, 0, nbMax_enregistrement * sizeof(Enregistrement));

    }

    printf("Mémoire secondaire initialisée avec %d blocs de taille %d octets.\n", nb_blocs, taille_Bloc);
}

//////////////////////////////////////////////////////////////////   Afficher Memoire Secondaire  (supper bloc)
void afficher_Memoire_Secondaire(MemoireSecondaire* memoire, int mode) {
    printf("\nÉtat de la mémoire secondaire :\n");

    if (mode == Contigue) {
        // En-tête sans le champ next_bloc
        printf("+-------+-----------+--------+-----------------+\n");
        printf("| Bloc  | is_used   | id_f   | Enregistrements |\n");
        printf("+-------+-----------+--------+-----------------+\n");

        for (int i = 0; i < memoire->nb_bloc_disque; ++i) {
            Bloc* bloc = &memoire->disque[i];

            if (bloc->is_used) {
                // Affichage en vert pour les blocs utilisés
                printf(VERT "| %5d | %9d | %6d | %14d |\n" RESET,
                       i,
                       bloc->is_used,
                       bloc->id_fichier,
                       bloc->nb_enregistrements);
            } else {
                // Affichage en rouge pour les blocs libres
                printf(ROUGE "| %5d | %9d | %6d | %14d |\n" RESET,
                       i,
                       bloc->is_used,
                       bloc->id_fichier,
                       bloc->nb_enregistrements);
            }
        }

        printf("+-------+-----------+--------+-----------------+\n");
    } else {
        // En-tête avec le champ next_bloc
        printf("+-------+-----------+--------+-----------------+---------+\n");
        printf("| Bloc  | is_used   | id_f   | Enregistrements | next_blk|\n");
        printf("+-------+-----------+--------+-----------------+---------+\n");

        for (int i = 0; i < memoire->nb_bloc_disque; ++i) {
            Bloc* bloc = &memoire->disque[i];

            if (bloc->is_used) {
                // Affichage en vert pour les blocs utilisés
                printf(VERT "| %5d | %9d | %6d | %14d | %7d |\n" RESET,
                       i,
                       bloc->is_used,
                       bloc->id_fichier,
                       bloc->nb_enregistrements,
                       bloc->next_bloc);
            } else {
                // Affichage en rouge pour les blocs libres
                printf(ROUGE "| %5d | %9d | %6d | %14d | %7d |\n" RESET,
                       i,
                       bloc->is_used,
                       bloc->id_fichier,
                       bloc->nb_enregistrements,
                       bloc->next_bloc);
            }
        }

        printf("+-------+-----------+--------+-----------------+---------+\n");
    }
}

/////////////////////////////////////////////////////// Fonction pour choisir le type de système de fichiers

int choisir_Type_Systeme_Fichier() {
    int choix;

    do {
        printf(JAUNE "\n==============================\n");
        printf("  Choisissez le type de système de fichiers\n");
        printf("==============================\n" RESET);
        printf("1. " VERT "Contigu\n" RESET);
        printf("2. " VERT "Chaîné\n" RESET);
        printf(JAUNE "------------------------------\n" RESET);
        printf("Votre choix : ");

        // Vérifie si l'entrée est valide
        if (scanf("%d", &choix) != 1) {
            printf(ROUGE "Entrée invalide. Veuillez entrer un nombre.\n" RESET);
            while (getchar() != '\n'); // Vider le tampon d'entrée
            choix = 0; // Réinitialiser pour rester dans la boucle
        } else if (choix != 1 && choix != 2) {
            printf(ROUGE "Choix invalide. Veuillez sélectionner 1 ou 2.\n" RESET);
        }

    } while (choix != 1 && choix != 2);

    printf(VERT "\nType de système de fichiers défini sur : %s\n" RESET,
           (choix == 1) ? "Contigu" : "Chaîné");
    return choix;
}

/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////  Gestion des fichiers
void creer_FichierContigue(MemoireSecondaire *memoire, const char *nom, int taille_en_blocs) {
    if (memoire->nb_fichiers >= MAX_FICHIERS) {
        printf("Erreur : Nombre maximal de fichiers atteint.\n");
        return;
    }

    // Rechercher des blocs contigus disponibles
    int start_bloc = -1;
    int count = 0;
    for (int i = 0; i < memoire->nb_bloc_disque; i++) {
        if (!memoire->disque[i].is_used) {
            if (start_bloc == -1) start_bloc = i;
            count++;
            if (count == taille_en_blocs) break;
        } else {
            start_bloc = -1;
            count = 0;
        }
    }

    if (count < taille_en_blocs) {
        printf("Erreur : Pas assez de blocs contigus disponibles.\n");
        return;
    }
Metadonnee *nouveauFichier = &memoire->fichiers[memoire->nb_fichiers];
    // Allouer les blocs
    for (int i = start_bloc; i < start_bloc + taille_en_blocs; i++) {
        memoire->disque[i].is_used = true;
        memoire->disque[i].id_fichier = memoire->nb_fichiers;
        //nouveauFichier->blocs[i]=i;
    }

    // Initialiser la métadonnée
    
    nouveauFichier->id = memoire->nb_fichiers;
    strncpy(nouveauFichier->nom, nom, sizeof(nouveauFichier->nom) - 1);
    nouveauFichier->nom[sizeof(nouveauFichier->nom) - 1] = '\0';
    
    nouveauFichier->premier_bloc = start_bloc;
    nouveauFichier->nb_blocs = taille_en_blocs;
    nouveauFichier->mode_global = Contigue;
     // Choisir le interne (trié ou non)
    int tri;
    printf("Voulez-vous que le fichier soit trié par identifiant ? (1: Oui, 0: Non) : ");
    scanf("%d", &tri);
    nouveauFichier->mode_interne=tri;
    memoire->nb_fichiers++;
    printf("Fichier '%s' créé avec succès.\n", nom);
}

void supprimer_FichierContigue(MemoireSecondaire *memoire, const char *nom_fichier) {
    for (int i = 0; i < memoire->nb_fichiers; i++) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];
                    // Vérifier si le fichier est valide
            if (fichier->premier_bloc < 0 || fichier->nb_blocs <= 0) {
                printf("Erreur : Le fichier '%s' est invalide.\n", nom_fichier);
                return;
            }
            // Libérer les blocs
            for (int j = fichier->premier_bloc; j < fichier->premier_bloc + fichier->nb_blocs; j++) {
                memoire->disque[j].is_used = false;
                memoire->disque[j].id_fichier = -1;
            }

            // Supprimer la métadonnée
            for (int k = i; k < memoire->nb_fichiers - 1; k++) {
                memoire->fichiers[k] = memoire->fichiers[k + 1];
            }
            memoire->nb_fichiers--;
            printf("Fichier '%s' supprimé avec succès.\n", nom_fichier);
            return;
        }
    }
    printf("Erreur : Fichier '%s' introuvable.\n", nom_fichier);
}

void afficher_FichiersContigue(MemoireSecondaire *memoire) {
    printf("Liste des fichiers (mode contigu) :\n");
    for (int i = 0; i < memoire->nb_fichiers; i++) {
        Metadonnee *fichier = &memoire->fichiers[i];
        printf("ID: %d, Nom: %s, Premier bloc: %d, Taille: %d blocs\n",
               fichier->id, fichier->nom, fichier->premier_bloc, fichier->nb_blocs);
    }
}

/////////////////////////////////////////////////////////////////////////

void afficher_Metadonnees(MemoireSecondaire *memoire, int mode) {
    // En-tête coloré en bleu
    printf(CYAN "%-10s %-20s %-15s %-15s %-15s\n" RESET, 
           "ID", "Nom", "Taille (blocs)", "Taille (o)", "Premier bloc");

    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        Metadonnee *fichier = &memoire->fichiers[i];

        // Affichage des métadonnées en vert pour les blocs utilisés
        printf(VERT "%-10d" RESET " %-20s %-15d %-15d %-15d\n", 
               fichier->id, 
               fichier->nom, 
               fichier->nb_blocs, 
               fichier->nb_enreg * (int)sizeof(Enregistrement), 
               fichier->premier_bloc);
    }
}


void supprimer_enregistrementContigue(MemoireSecondaire *memoire, const char* nom_fichier, int id_enregistrement) {
    int id_fichier = -1;
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            id_fichier = i;
            break;
        }
    }
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];
    int bloc_id = fichier->premier_bloc;
    for (int i = 0; i < fichier->nb_blocs; ++i) {
        Bloc *bloc = &memoire->disque[bloc_id];

        for (int j = 0; j < bloc->nb_enregistrements; ++j) {
            if (bloc->enregistrements[j].id == id_enregistrement) {
                // Supprimer l'enregistrement
                for (int k = j; k < bloc->nb_enregistrements - 1; ++k) {
                    bloc->enregistrements[k] = bloc->enregistrements[k + 1];
                }
                bloc->nb_enregistrements--;
                fichier->nb_enreg--;
                printf("Enregistrement %d supprimé du bloc %d.\n", id_enregistrement, bloc_id);
                return;
            }
        }
        bloc_id++;
    }
    printf("Enregistrement non trouvé.\n");
}
/////////////////////////////////////  defragmenter les blocs d'un fichier : liberer l'espace non utilisé intenre au fichier
void defragmenter_Fichier(MemoireSecondaire *memoire, const char* nom_fichier) { 
    // Recherche de l'index du fichier
    int id_fichier = -1;
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            id_fichier = i;
            break;
        }
    }
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];

    // Vérifie si le fichier a des blocs alloués
    if (fichier->premier_bloc == -1) {
        printf("Erreur : Fichier \"%s\" est vide ou n'a pas de blocs alloués.\n", fichier->nom);
        return;
    }

    int bloc_id = fichier->premier_bloc;  // Index actuel du premier bloc
    int nouvelle_position = -1;          // Index du nouveau premier bloc (après défragmentation)
    int position_actuelle = fichier->premier_bloc; // Position courante dans la mémoire

    for (int i = 0; i < fichier->nb_blocs; ++i) {
        Bloc *bloc = &memoire->disque[bloc_id];

        // Si le bloc contient des données
        if (bloc->nb_enregistrements > 0) {
            if (nouvelle_position == -1) {
                nouvelle_position = position_actuelle;  // Premier bloc compacté
            }
            // Si le bloc n'est pas à la bonne position
            if (bloc_id != position_actuelle) {
                memoire->disque[position_actuelle] = *bloc;

                // Libérer l'ancien bloc
                bloc->is_used = false;
                bloc->id_fichier = -1;
                bloc->nb_enregistrements = 0;
            }
            memoire->disque[position_actuelle].is_used = true;
            memoire->disque[position_actuelle].id_fichier = fichier->id;
            position_actuelle++; // Avance à la position suivante pour le compactage
        }
        bloc_id++; // Passe au bloc suivant
    }

    // Mise à jour des métadonnées du fichier
    fichier->premier_bloc = nouvelle_position;  // Nouveau premier bloc
    fichier->nb_blocs = position_actuelle - nouvelle_position;  // Recalcul du nombre de blocs utilisés

    printf("Défragmentation et compactage du fichier \"%s\" terminés.\n", fichier->nom);
}

///////////////////////////////
void supprimer_Fichier(MemoireSecondaire *memoire, const char* nom_fichier) {
    int id_fichier = -1;
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            id_fichier = i;
            break;
        }
    }
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];
    for (int i = 0; i < fichier->nb_blocs; ++i) {
        int bloc_id = fichier->premier_bloc;
        Bloc *bloc = &memoire->disque[bloc_id];
        bloc->is_used = false;
        bloc->id_fichier = -1;
        bloc->nb_enregistrements = 0;
        bloc->next_bloc = -1;
    }

    for (int i = id_fichier; i < memoire->nb_fichiers - 1; ++i) {
        memoire->fichiers[i] = memoire->fichiers[i + 1];
    }
    memoire->nb_fichiers--;
    printf("Fichier \"%s\" supprimé.\n", nom_fichier);
}
void renommer_Fichier(MemoireSecondaire *memoire, const char* nom_fichier, const char* nouveau_nom) {
    int id_fichier = -1;
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            id_fichier = i;
            break;
        }
    }
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];
    strncpy(fichier->nom, nouveau_nom, sizeof(fichier->nom) - 1);
    fichier->nom[sizeof(fichier->nom) - 1] = '\0';
    printf("Le fichier \"%s\" a été renommé en \"%s\".\n", nom_fichier, fichier->nom);
}
/////////////////////////////////////////////////////////////// mise à jour de metafile des fichier après compactage des blocs physiques
void mettreAJourPremierBlocApresCompactage(MemoireSecondaire *memoire) {
    int position_actuelle = 0;

    // Parcourir tous les fichiers pour mettre à jour leur premier bloc
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        Metadonnee *fichier = &memoire->fichiers[i];

        // Si le fichier contient des blocs
        if (fichier->nb_blocs > 0) {
            fichier->premier_bloc = position_actuelle; // Le premier bloc du fichier est à la position actuelle
            position_actuelle += fichier->nb_blocs; // Avancer de la taille du fichier en blocs
        }
    }

    // Facultatif : Si nécessaire, vous pouvez encore marquer les blocs restants comme libres
    for (int i = position_actuelle+1; i < memoire->nb_bloc_disque; ++i) {
        memoire->disque[i].is_used = false;
    }
}

/////////////////////////////////////////////////////////////// fonction comfirmation
int confirmerAction() {
    char reponse[4]; // Pour stocker "oui", "non", etc.
    
    printf("Voulez-vous vraiment compacter le disque en entier ? (oui/non) : ");
    scanf("%3s", reponse); // Limite la saisie pour éviter les débordements

    // Boucle pour confirmer l'intention de l'utilisateur
    while (strcmp(reponse, "oui") != 0 && strcmp(reponse, "non") != 0) {
        printf("Réponse invalide. Veuillez entrer 'oui' ou 'non' : ");
        scanf("%3s", reponse);
    }

    return strcmp(reponse, "oui") == 0;
}
////////////////////////////////////////////////////////////  compactage
void compactage_Contigue(MemoireSecondaire *memoire) {
    int dernier_bloc_utilise = -1;
    if (confirmerAction()) {
        for (int i = 0; i < memoire->nb_bloc_disque; ++i) {
            if (memoire->disque[i].is_used && memoire->disque[i].nb_enregistrements > 0) {
                if (dernier_bloc_utilise + 1 != i) {
                    memoire->disque[dernier_bloc_utilise + 1] = memoire->disque[i];
                    memoire->disque[i].is_used = false;
                    memoire->disque[i].id_fichier = -1;
                    memoire->disque[i].nb_enregistrements = 0;
                }
                dernier_bloc_utilise++;
            }
        }
        printf("Compactage terminé.\n");
    } else {
        printf("Opération annulée. Le disque ne sera pas compacté.\n");
    }
}

////////////////////////
int chercher_ID_Fichier(const char *nom_fichier, MemoireSecondaire *memoire) {
    for (int i = 0; i < memoire->nb_fichiers; ++i) { // Utilisation de nb_fichiers depuis la structure
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) { // Accès direct à la structure
            return memoire->fichiers[i].id; // Retourner l'ID du fichier trouvé
        }
    }
    return -1; // Retourner -1 si le fichier n'est pas trouvé
}

////////////////////////////////////////////////////////////////// Gestion des enregistrements
int inserer_EnregistrementContigue(MemoireSecondaire *memoire, const char *nom, Enregistrement *enregistrement) { 
    for (int i = 0; i < memoire->nb_fichiers; i++) {
        if (strcmp(memoire->fichiers[i].nom, nom) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];

            // Parcourir les blocs contigus du fichier
            for (int j = fichier->premier_bloc; j < fichier->premier_bloc + fichier->nb_blocs; j++) {
                Bloc *bloc = &memoire->disque[j];

                // Vérifier si le bloc peut contenir un nouvel enregistrement
                if (bloc->nb_enregistrements < nbMax_enregistrement) {
                    bloc->enregistrements[bloc->nb_enregistrements++] = *enregistrement;

                    // Mettre à jour le nombre total d'enregistrements dans les métadonnées
                    fichier->nb_enreg++;

                    printf("Enregistrement ajouté au fichier '%s' (Bloc %d, Enregistrement %d).\n", 
                           nom, j, bloc->nb_enregistrements - 1);
                    return 1;  // Retourner 1 si l'insertion est réussie
                }
            }

            // Si aucun espace n'est disponible dans les blocs du fichier
            printf("Erreur : Pas d'espace disponible dans le fichier '%s'.\n", nom);
            return -1;  // Retourner -1 si l'insertion échoue
        }
    }

    // Si le fichier n'est pas trouvé
    printf("Erreur : Fichier '%s' introuvable.\n", nom);
    return -1;  // Retourner -1 si le fichier n'existe pas
}

/////////////////////////////////////////////////////////////////////// Fonction pour rechercher un enregistrement dans un fichier
void rechercher_EnregistrementContigue(const char* nom_fichier, int id_enregistrement, MemoireSecondaire* memoire) {
    // Rechercher l'ID du fichier dans la mémoire secondaire
    int id_fichier = chercher_ID_Fichier(nom_fichier, memoire);
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        getchar();  // Attente d'une touche avant de continuer
        return;
    } else {
        printf("Fichier \"%s\" trouvé.\n", nom_fichier);
    }

    // Vérifier que l'ID du fichier est valide
    if (id_fichier < 0 || id_fichier >= memoire->nb_fichiers) {
        printf("Erreur : ID du fichier invalide.\n");
        return;
    }

    Metadonnee* fichier = &(memoire->fichiers[id_fichier]);

    // Parcourir tous les blocs alloués au fichier
    int bloc_id = fichier->premier_bloc;
    for (int i = 0; i < fichier->nb_blocs; ++i) {
  

        // Vérifier que le bloc est utilisé
        if (memoire->disque[bloc_id].is_used) {
            Bloc* bloc = &(memoire->disque[bloc_id]);

            // Parcourir les enregistrements dans le bloc
            for (int j = 0; j < bloc->nb_enregistrements; ++j) {
                if (bloc->enregistrements[j].id == id_enregistrement) {
                    // Enregistrement trouvé
                    printf("Enregistrement trouvé dans le bloc %d :\n", bloc_id);
                    printf("ID: %d, Taille: %d, Données: %s\n",
                           bloc->enregistrements[j].id,
                           bloc->enregistrements[j].taille,
                           bloc->enregistrements[j].data);
                    return;
                }
            }
        }
        bloc_id++;
    }

    // Enregistrement non trouvé
    printf("Enregistrement non trouvé.\n");
}

////////////////////////////////////////////////////////////////////
void Saisir_Nombre_Enreg(int *nombre) {
    int resultat;
    char buffer;
do {
        //printf("Veuillez entrer un nombre entier : ");
        resultat = scanf("%d", nombre);

        // Si l'entrée n'est pas un nombre entier valide
        if (resultat != 1) {
            printf("\a"); // Ajout du bip sonore
            printf(JAUNE "Entrée invalide. Veuillez entrer un nombre entier.\n" RESET);

            // Vider le buffer pour éviter une boucle infinie
            while ((buffer = getchar()) != '\n' && buffer != EOF);
        }
    } while (resultat != 1); // Répéter jusqu'à obtenir une entrée valide
}
/////////////////////////////////////////////////////////////////////: Gestion des enregistrement
Enregistrement saisir_Enregistrement() {
    Enregistrement enregistrement;
    
    // Demander l'ID de l'enregistrement
    printf("Entrez l'ID de l'enregistrement : ");
    scanf("%d", &enregistrement.id);

    // Demander les données de l'enregistrement
    printf("Entrez les données de l'enregistrement : ");
    getchar();  // Consommer le '\n' restant dans le buffer
    fgets(enregistrement.data, MAX_DATA_SIZE, stdin);
    enregistrement.data[strcspn(enregistrement.data, "\n")] = 0;  // Retirer le '\n' à la fin de la chaîne

    // Calculer la taille des données
    enregistrement.taille = strlen(enregistrement.data);
    
    return enregistrement;
}
///////////////////////////////////    compactage de la  Memoire Secondiare //////////////////////////////
void compactage_Memoire_SecondaireContigue(MemoireSecondaire* memoire) {
    int pos_libre = 0; // Position pour placer le prochain bloc valide

    // Parcourir tous les blocs pour les déplacer
    for (int i = 0; i < memoire->nb_bloc_disque; i++) {
        if (memoire->disque[i].id_fichier != -1) { // Si le bloc est occupé
            // Si le bloc est occupé et pas déjà à la position libre
            if (i != pos_libre) {
                // Copier les données du bloc à la position libre
                memoire->disque[pos_libre] = memoire->disque[i];
                memoire->disque[i].id_fichier = -1; // Marquer l'ancien emplacement comme libre
                memset(memoire->disque[i].enregistrements, 0, sizeof(memoire->disque[i].enregistrements));
            }
            pos_libre++; // Avancer la position libre
        }
    }

    // Mettre à jour les métadonnées pour les fichiers
    for (int i = 0; memoire->fichiers[i].id != -1; i++) { // Suppose un marqueur de fin dans fichiers
        int index_bloc = memoire->fichiers[i].premier_bloc;
        memoire->fichiers[i].premier_bloc = pos_libre; // Réattribuer le premier bloc à la nouvelle position

        // Réattribuer les blocs à ce fichier
        for (int j = 0; j < memoire->fichiers[i].nb_blocs; j++) {
            memoire->disque[pos_libre + j] = memoire->disque[index_bloc + j];
            memoire->disque[index_bloc + j].id_fichier = -1; // Réinitialiser les blocs déplacés
            memset(memoire->disque[index_bloc + j].enregistrements, 0, sizeof(memoire->disque[index_bloc + j].enregistrements));
        }

        // Mettre à jour la position libre après avoir déplacé tous les blocs du fichier
        pos_libre += memoire->fichiers[i].nb_blocs;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                // Fonctions intermédiaires //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void vider_Memoire_Secondaire(MemoireSecondaire* memoire) {
    // Réinitialiser chaque bloc de la mémoire secondaire
    for (int i = 0; i < memoire->nb_bloc_disque; ++i) {
        memoire->disque[i].id_fichier = -1;
        memoire->disque[i].is_used = 0;
        memoire->disque[i].nb_enregistrements = 0;
        for (int j = 0; j < MAX_ENREGISTREMENTS; ++j) {
            memoire->disque[i].enregistrements[j].id = 0;
            memoire->disque[i].enregistrements[j].taille = 0;
        }
    }

    // Réinitialiser les métadonnées des fichiers
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        memoire->fichiers[i].id = 0;
        memoire->fichiers[i].nom[0] = '\0';
        memoire->fichiers[i].nb_blocs = 0;
        memoire->fichiers[i].nb_enreg = 0;
        memoire->fichiers[i].premier_bloc= -1;
    }

    // Réinitialiser le compteur de fichiers
    memoire->nb_fichiers = 0;

    printf("La mémoire secondaire a été vidée avec succès.\n");
}

//////////////////////////////  Affichage du contenu d'un fichier l'or de l'ajout d'un nouveau bloc ou de sa suppression
void afficher_contenu_du_fichier(MemoireSecondaire* memoire, const char *nom_fichier) {
    // Rechercher le fichier par son nom
    int id_fichier = -1;
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            id_fichier = i;
            break;
        }
    }

    if (id_fichier == -1) {
        printf(ROUGE "Erreur : Fichier \"%s\" introuvable.\n" RESET, nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];
    printf(VERT "Affichage du contenu du fichier \"%s\" (ID : %d):\n" RESET, fichier->nom, fichier->id);

    printf("%-10s %-10s\n", "Bloc", "Contenu");
    printf("-------------------------\n");

    // Parcourir les blocs du fichier
    int bloc_id = fichier->premier_bloc;
    for (int i = 0; i < fichier->nb_blocs; ++i) {
        if (bloc_id < 0 || bloc_id >= MAX_BLOCS) {
            printf(ROUGE "Erreur : Bloc ID invalide (%d).\n" RESET, bloc_id);
            break;
        }

        Bloc *bloc = &memoire->disque[bloc_id];
        printf("%-10d ", bloc_id);

        if (bloc->nb_enregistrements == 0) {
            printf(ROUGE "(Réservé mais vide)\n" RESET);
        } else {
            printf(VERT);
            for (int j = 0; j < bloc->nb_enregistrements; ++j) {
                Enregistrement *enreg = &bloc->enregistrements[j];
                printf("Enreg[%d]: %s ", enreg->id, enreg->data);
            }
            printf(RESET "\n");
        }

        bloc_id++;
    }

    // Afficher les espaces disponibles
    //printf("\n" VERT "Espaces disponibles (blocs non assignés aux fichiers) :" RESET "\n");
    //printf("%-10s %-10s\n", "Bloc", "Statut");
    //printf("-------------------------\n");

    //for (int i = 0; i < MAX_BLOCS; ++i) {
      //  if (!memoire->disque[i].is_used) {
        //    printf("%-10d " ROUGE "(Inutilisé)\n" RESET, i);
        //}
    //}
}

//  l'utilisateur doit spécifier quel fichier doit intéroger
void preciser_fichier(int cas) {
    // Afficher le message selon le cas
    switch (cas) {
        case 2:
            printf("Entrez le nom du fichier à créer : ");
            break;
        case 5:
            printf("Entrez le nom du fichier où insérer l'enregistrement : ");
            break;
        case 6:
            printf("Entrez le nom du fichier où chercher l'enregistrement : ");
            break;
        case 7:
            printf("Entrez le nom du fichier où supprimer l'enregistrement : ");
            break;
        case 8:
            printf("Entrez le nom du fichier à défragmenter : ");
            break;
        case 9:
            printf("Entrez le nom du fichier à supprimer : ");
            break;
        case 10:
            printf("Entrez le nom du fichier à renommer : ");
            break;
        case 14:
            printf("Entrez le nom du fichier pour afficher son contenu : ");
            break;
        default:
            printf("Option non valide.\n");
            return;
    }
  // Lire le nom du fichier
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if (fgets(nom_fichier, sizeof(nom_fichier), stdin) != NULL) {
        // Supprimer '\n' s'il est présent
        size_t len = strlen(nom_fichier);
        if (len > 0 && nom_fichier[len - 1] == '\n') {
            nom_fichier[len - 1] = '\0';
        }

        // Vérification de la chaîne
        if (strlen(nom_fichier) == 0) {
            printf("Erreur : Le nom du fichier ne peut pas être vide.\n");
        } else {
            printf("Nom du fichier : %s\n", nom_fichier);
        }
    } else {
        printf("Erreur lors de la lecture du nom du fichier.\n");
    }

}
////////////////////////////////////////////////////////////////
void preciser_nouv_fichier() {
    
    // Initialisation de variables
    int index = 0;
    int ch;

    // Lire caractère par caractère
    while ((ch = getchar()) != '\n' && ch != EOF && index < sizeof(nouv_nom) - 1) {
        nouv_nom[index++] = ch;
    }
    nouv_nom[index] = '\0'; // Terminer la chaîne

    // Vérification si la chaîne est vide
    if (index == 0) {
        printf("Erreur : Le nom du fichier ne peut pas être vide.\n");
        return;
    }

    // Vérification de caractères non valides
    if (strpbrk(nouv_nom, "\\/:*?\"<>|") != NULL) {
        printf("Erreur : Le nom du fichier contient des caractères non valides.\n");
    } else {
        printf("Nom du fichier : %s\n", nouv_nom);
    }
}

// Fonction pour calculer le nombre de blocs nécessaires
int calculer_nombre_blocs(int nb_enregistrements, int nbMax_enregistrements) {
    if (nbMax_enregistrements == 0) {
        printf("Erreur : nbMax_enregistrements ne peut pas être zéro.\n");
        return 0;
    }
    return (nb_enregistrements + nbMax_enregistrements - 1) / nbMax_enregistrements; // Division arrondie vers le haut
}

// Fonction pour demander à l'utilisateur de préciser un numéro d'enregistrement
int preciser_enregistrement(int cas) {
    int numero_enregistrement;

    // Vérification et affichage des messages en fonction du choix dans le menu
    if (cas == 6) {
        printf("Veuillez entrer le numéro de l'enregistrement à chercher : ");
    } else if (cas == 7) {
        printf("Veuillez entrer le numéro de l'enregistrement à supprimer : ");
    } else {
        printf("Cas non pris en charge.\n");
        return -1; // Code d'erreur pour un cas invalide
    }

    // Lecture et validation de l'entrée
    while (scanf("%d", &numero_enregistrement) != 1 || numero_enregistrement < 0) {
        printf("Entrée invalide. Veuillez entrer un numéro d'enregistrement valide (un entier positif) : ");
        while (getchar() != '\n'); // Effacer le buffer d'entrée
    }

    return numero_enregistrement;
}

//////////////
int preciser_logic() {
    int choix;

    // Demander à l'utilisateur de spécifier le type de suppression
    printf("Voulez-vous une suppression de manière logique (1) ou physique (0) ? : ");
    
    // Lire la saisie de l'utilisateur
    while (1) {
        if (scanf("%d", &choix) != 1) {
            // Si l'entrée n'est pas un nombre, on demande à l'utilisateur de ressaisir
            while(getchar() != '\n'); // Vider le tampon
            printf("Entrée invalide. Veuillez saisir 1 pour une suppression logique ou 0 pour une suppression physique : ");
        } else if (choix == 0 || choix == 1) {
            // Si l'entrée est valide (0 ou 1), sortir de la boucle
            break;
        } else {
            // Si l'entrée est autre que 0 ou 1, demander à nouveau
            printf("Choix invalide. Veuillez saisir 1 pour une suppression logique ou 0 pour une suppression physique : ");
        }
    }

    return choix;
}
//////////////////////////// Calcule du maximum d'enregistrement à ajouter à un bloc dont sa taille est definie par l'utilisateur
int calcul_max_enregistrements() { 
    // Calcul de l'espace utilisé par les champs non liés aux enregistrements
    size_t taille_non_enregistrement = sizeof(int) * 3 + sizeof(bool) + sizeof(int);  // 3 ints et 1 bool
    size_t espace_disponible = taille_Bloc - taille_non_enregistrement;
    
    // Calcul du nombre d'enregistrements pouvant tenir dans l'espace disponible
    int max_enregistrements = espace_disponible / taille_enregistrement;
    int fragment = espace_disponible-max_enregistrements*taille_enregistrement;
    printf("fragmentation interne au bloc de %d octets\n",fragment);
    return max_enregistrements;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int confirmer_Type_Memoire_Secondaire() {
    int choix;

    do {
        printf("\nVoulez-vous créer une mémoire secondaire de type :\n");
        printf("1. Contiguë\n");
        printf("2. Chaînée\n");
        printf("Votre choix (1 ou 2) : ");

        if (scanf("%d", &choix) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n'); // Vider le tampon d'entrée
            choix = 0; // Réinitialiser pour rester dans la boucle
        } else if (choix != 1 && choix != 2) {
            printf("Choix invalide. Veuillez sélectionner 1 ou 2.\n");
        }

    } while (choix != 1 && choix != 2);

    printf("Vous avez choisi une mémoire secondaire de type %s.\n",
           (choix == 1) ? "contiguë" : "chaînée");

    return choix;
}
/////////////////////////////////////////////////////////////////////////
void changer_ModeGlobal() {
    int choix;

    printf("Choisissez le mode de stockage global :\n");
    printf("1. Mode Contigu\n");
    printf("2. Mode Chaîné\n");
    printf("Entrez votre choix (1 ou 2) : ");
    scanf("%d", &choix);

    if (choix == Contigue) {
        mode_global = Contigue; // Mode Contigu
        printf("Le mode global a été changé au mode Contigu.\n");
    } else if (choix == Chained) {
        mode_global = Chained; // Mode Chaîné
        printf("Le mode global a été changé au mode Chaîné.\n");
    } else {
        printf("Choix invalide. Le mode global reste inchangé.\n");
    }
}
//////////////////////////////////////////////////////////////////////:::::*

// Fonction utilitaire pour générer une chaîne aléatoire
void generer_DonneesAleatoires(char* buffer, int taille) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < taille - 1; ++i) {
        buffer[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    buffer[taille - 1] = '\0';
}
////////////
void remplir_FichierContigu(MemoireSecondaire *memoire, const char *nom_fichier) {
    printf("Voulez-vous remplir automatiquement les enregistrements du fichier \"%s\" ? (O/N) : ", nom_fichier);
    char choix;
    scanf(" %c", &choix);

    choix = tolower(choix); // Convertir en minuscule pour traiter 'o' et 'O' comme "oui"

    if (choix != 'o') {
        printf("Remplissage automatique annulé pour le fichier \"%s\".\n", nom_fichier);
        return;
    }
    int id_fichier = chercher_ID_Fichier(nom_fichier, memoire);
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];

    // Initialiser le générateur aléatoire
    srand(time(NULL));

    // Parcourir les blocs du fichier
    int bloc_id = fichier->premier_bloc;
    for (int i = 0; i < fichier->nb_blocs; i++) {
        Bloc *bloc = &memoire->disque[bloc_id];
        for (int j = 0; j < nbMax_enregistrement && fichier->nb_enreg < nb_enregistrement; j++) {
            // Générer un enregistrement aléatoire
            bloc->enregistrements[j].id = fichier->nb_enreg+1;//rand() % 1000; // ID entre 0 et 999
            bloc->enregistrements[j].taille = rand() % 10 + 1; // Taille entre 1 et 10
            snprintf(bloc->enregistrements[j].data, sizeof(bloc->enregistrements[j].data), "Data%d", rand() % 100);
            bloc->nb_enregistrements++;
            fichier->nb_enreg++;
        }

        bloc_id++; // Passer au bloc suivant
    }
 
    printf("Fichier \"%s\" rempli automatiquement en mode Contigu.\n", nom_fichier);
}
///////////////////////////////////////////////////
void trier_FichierParIDContigu(MemoireSecondaire *memoire, Buffer *buffer, const char *nom_fichier) {
    // Étape 1 : Vérifier si le fichier existe
    int id_fichier = chercher_ID_Fichier(nom_fichier, memoire);
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];

    // Étape 2 : Charger tous les blocs du fichier dans le buffer
    charger_blocs_bufferContigue(buffer, memoire, nom_fichier);

    // Étape 3 : Compter le nombre total d'enregistrements
    int total_enregistrements = fichier->nb_enreg;
    Enregistrement *tableau_enregistrements = malloc(total_enregistrements * sizeof(Enregistrement));
    if (!tableau_enregistrements) {
        printf("Erreur : Échec de l'allocation mémoire.\n");
        return;
    }

    // Étape 4 : Extraire tous les enregistrements des blocs dans le buffer
    int index = 0;
    for (int i = 0; i < buffer->taille_actuelle; ++i) {
        Bloc *bloc = &buffer->data[i];
        for (int j = 0; j < bloc->nb_enregistrements; ++j) {
            tableau_enregistrements[index++] = bloc->enregistrements[j];
        }
    }

    // Étape 5 : Trier les enregistrements par leur champ `id` avec la fonction de comparaison
    qsort(tableau_enregistrements, total_enregistrements, sizeof(Enregistrement), comparer_enregistrements_par_id);

    // Étape 6 : Réécrire les enregistrements triés dans les blocs du buffer
    index = 0;
    for (int i = 0; i < buffer->taille_actuelle; ++i) {
        Bloc *bloc = &buffer->data[i];
        bloc->nb_enregistrements = 0; // Réinitialiser le compteur
        for (int j = 0; j < nbMax_enregistrement && index < total_enregistrements; ++j) {
            bloc->enregistrements[j] = tableau_enregistrements[index++];
            bloc->nb_enregistrements++;
        }
    }

    // Étape 7 : Écrire les blocs mis à jour dans la mémoire secondaire
    ecrire_blocs_memoireContigue(buffer, memoire, nom_fichier);

    // Libérer la mémoire allouée
    free(tableau_enregistrements);

    printf("Fichier \"%s\" trié par identifiants des enregistrements (mode contigu).\n", nom_fichier);
}
int comparer_enregistrements_par_id(const void *a, const void *b) {
    const Enregistrement *enreg_a = (const Enregistrement *)a;
    const Enregistrement *enreg_b = (const Enregistrement *)b;
    return enreg_a->id - enreg_b->id; // Tri ascendant par ID
}



#endif // FUNCTIONS_H