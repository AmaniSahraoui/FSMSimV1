#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#ifndef FUNCTIONS_CHAINE_H
#define FUNCTIONS_CHAINE_H
//////////////////////////////////////////////////////////////////////////////////////////////////////// Prototypes


void creer_FichierChaine(MemoireSecondaire *memoire, const char *nom, int taille_en_blocs);
int inserer_EnregistrementChaine(MemoireSecondaire *memoire, const char *nom, Enregistrement *enregistrement); 
void rechercher_EnregistrementChaine(const char *nom_fichier, int id_enregistrement, MemoireSecondaire *memoire);
void supprimer_FichierChaine(MemoireSecondaire *memoire, const char *nom_fichier);
void mettreAJourPremierBlocApresCompactage(MemoireSecondaire *memoire);
void compactage_Chaine(MemoireSecondaire *memoire);
void supprimer_enregistrementChaine(MemoireSecondaire *memoire, const char* nom_fichier, int id_enregistrement);
void trier_FichierParIDChaine(MemoireSecondaire *memoire, Buffer *buffer, const char *nom_fichier);
//////////////////////////////////////////////////////////////////////////////////////////////////////
int chercher_ID_Fichier(const char *nom_fichier, MemoireSecondaire *memoire);
int confirmerAction();
void remplir_FichierChaine(MemoireSecondaire *memoire, const char *nom_fichier);
//////////////////////////////////////////////////////////////////////////////////////////////////////
void creer_FichierChaine(MemoireSecondaire *memoire, const char *nom, int taille_en_blocs) {
    if (memoire->nb_fichiers >= MAX_FICHIERS) {
        printf("Erreur : Nombre maximal de fichiers atteint.\n");
        return;
    }

    int allocated_blocs = 0;
    int prev_bloc = -1;
    int start_bloc = -1;

    for (int i = 0; i < memoire->nb_bloc_disque && allocated_blocs < taille_en_blocs; i++) {
        if (!memoire->disque[i].is_used) {
            if (start_bloc == -1) start_bloc = i; // Définir le premier bloc

            // Allouer le bloc
            memoire->disque[i].is_used = true;
            memoire->disque[i].id_fichier = memoire->nb_fichiers;
            memoire->disque[i].next_bloc = -1; // Par défaut, fin de la chaîne

            // Relier au bloc précédent
            if (prev_bloc != -1) {
                memoire->disque[prev_bloc].next_bloc = i;
            }

            prev_bloc = i;
            allocated_blocs++;
        }
    }

    if (allocated_blocs < taille_en_blocs) {
        printf("Erreur : Pas assez de blocs libres disponibles pour le mode chaîné.\n");
        // Libérer les blocs déjà alloués
        for (int i = start_bloc; i <= prev_bloc; i++) {
            memoire->disque[i].is_used = false;
            memoire->disque[i].id_fichier = -1;
            memoire->disque[i].next_bloc = -1;
        }
        return;
    }

    // Initialiser les métadonnées
    Metadonnee *nouveauFichier = &memoire->fichiers[memoire->nb_fichiers];
    nouveauFichier->id = memoire->nb_fichiers;
    strncpy(nouveauFichier->nom, nom, sizeof(nouveauFichier->nom) - 1);
    nouveauFichier->nom[sizeof(nouveauFichier->nom) - 1] = '\0';
    nouveauFichier->premier_bloc = start_bloc;
    nouveauFichier->nb_blocs = taille_en_blocs;
    nouveauFichier->mode_global = Chained;

    memoire->nb_fichiers++;
    printf("Fichier '%s' créé avec succès en mode chaîné.\n", nom);
}

int inserer_EnregistrementChaine(MemoireSecondaire *memoire, const char *nom, Enregistrement *enregistrement) { 
    for (int i = 0; i < memoire->nb_fichiers; i++) {
        if (strcmp(memoire->fichiers[i].nom, nom) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];

            // Parcourir les blocs chaînés du fichier
            int current_bloc = fichier->premier_bloc;
            while (current_bloc != -1) {
                Bloc *bloc = &memoire->disque[current_bloc];

                // Vérifier si le bloc peut contenir un nouvel enregistrement
                if (bloc->nb_enregistrements < nbMax_enregistrement) {
                    bloc->enregistrements[bloc->nb_enregistrements++] = *enregistrement;

                    // Mettre à jour le nombre total d'enregistrements dans les métadonnées
                    fichier->nb_enreg++;

                    printf("Enregistrement ajouté au fichier '%s' (Bloc %d, Enregistrement %d).\n", 
                           nom, current_bloc, bloc->nb_enregistrements - 1);
                    return 1;  // Retourner 1 si l'insertion est réussie
                }

                // Passer au bloc suivant
                current_bloc = bloc->next_bloc;
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
//////////////////////////////////////////////////////////////
void rechercher_EnregistrementChaine(const char *nom_fichier, int id_enregistrement, MemoireSecondaire *memoire) {
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

    Metadonnee *fichier = &(memoire->fichiers[id_fichier]);

    // Parcourir tous les blocs chaînés du fichier
    int bloc_id = fichier->premier_bloc;
    while (bloc_id != -1) {
        Bloc *bloc = &(memoire->disque[bloc_id]);

        // Vérifier que le bloc est utilisé
        if (bloc->is_used) {
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

        // Passer au bloc suivant
        bloc_id = bloc->next_bloc;
    }

    // Enregistrement non trouvé
    printf("Enregistrement non trouvé.\n");
}
///////////////////////////////////////////////////////////////////////////////////:
void supprimer_FichierChaine(MemoireSecondaire *memoire, const char *nom_fichier) {
    for (int i = 0; i < memoire->nb_fichiers; i++) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];

            // Vérifier si le fichier est valide
            if (fichier->premier_bloc < 0) {
                printf("Erreur : Le fichier '%s' est invalide.\n", nom_fichier);
                return;
            }

            // Libérer les blocs chaînés
            int bloc_id = fichier->premier_bloc;
            while (bloc_id != -1) {
                Bloc *bloc = &memoire->disque[bloc_id];
                int next = bloc->next_bloc; // Sauvegarder le prochain bloc
                bloc->is_used = false;
                bloc->id_fichier = -1;
                bloc->nb_enregistrements = 0;
                bloc->next_bloc = -1; // Réinitialiser le pointeur
                bloc_id = next;      // Passer au bloc suivant
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
/////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
void compactage_Chaine(MemoireSecondaire *memoire) {
    if (!confirmerAction()) {
        printf("Opération annulée. Le disque ne sera pas compacté.\n");
        return;
    }

    int dernier_bloc_utilise = -1;

    for (int i = 0; i < memoire->nb_bloc_disque; ++i) {
        if (memoire->disque[i].is_used && memoire->disque[i].nb_enregistrements > 0) {
            // Si le bloc actuel n'est pas dans une position contiguë
            if (dernier_bloc_utilise != -1 && dernier_bloc_utilise != i - 1) {
                // Déplacer le bloc vers la position contiguë suivante
                memoire->disque[dernier_bloc_utilise + 1] = memoire->disque[i];
                memoire->disque[i].is_used = false;
                memoire->disque[i].id_fichier = -1;
                memoire->disque[i].nb_enregistrements = 0;
                memoire->disque[i].next_bloc = -1;

                // Mettre à jour les métadonnées des fichiers
                for (int j = 0; j < memoire->nb_fichiers; ++j) {
                    Metadonnee *fichier = &memoire->fichiers[j];
                    int bloc_id = fichier->premier_bloc;

                    // Parcourir les blocs chaînés pour ce fichier
                    while (bloc_id != -1) {
                        if (bloc_id == i) {
                            // Si le bloc déplacé était dans la chaîne, mettre à jour le pointeur
                            bloc_id = dernier_bloc_utilise + 1;
                            break;
                        }
                        bloc_id = memoire->disque[bloc_id].next_bloc;
                    }
                }
            }
            dernier_bloc_utilise++;
        }
    }

    printf("Compactage terminé.\n");
}
//////////////////////////////////////////////////////////////////////////////
void supprimer_enregistrementChaine(MemoireSecondaire *memoire, const char *nom_fichier, int id_enregistrement) {
    // Rechercher le fichier
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

    // Parcourir les blocs chaînés
    while (bloc_id != -1) {
        Bloc *bloc = &memoire->disque[bloc_id];

        // Parcourir les enregistrements dans le bloc
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

        // Passer au bloc suivant dans la chaîne
        bloc_id = bloc->next_bloc;
    }

    // Si l'enregistrement n'a pas été trouvé
    printf("Enregistrement non trouvé.\n");
}
/////////////////////////////////////////////////////////////////////////////////:::*
void remplir_FichierChaine(MemoireSecondaire *memoire, const char *nom_fichier) {
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

    // Parcourir les blocs chaînés
    int bloc_id = fichier->premier_bloc;
    while (bloc_id != -1) {
        Bloc *bloc = &memoire->disque[bloc_id];
        for (int j = 0; j < nbMax_enregistrement && fichier->nb_enreg < nb_enregistrement; j++) {
            // Générer un enregistrement aléatoire
            bloc->enregistrements[j].id = fichier->nb_enreg+1;   //rand() % 1000; // ID entre 0 et 999
            bloc->enregistrements[j].taille = rand() % 10 + 1; // Taille entre 1 et 10
            snprintf(bloc->enregistrements[j].data, sizeof(bloc->enregistrements[j].data), "Data%d", rand() % 100);
            bloc->nb_enregistrements++;
            fichier->nb_enreg++;
        }

        bloc_id = bloc->next_bloc; // Passer au bloc suivant
    }

    printf("Fichier \"%s\" rempli automatiquement en mode Chaîné.\n", nom_fichier);
}
void trier_FichierParIDChaine(MemoireSecondaire *memoire, Buffer *buffer, const char *nom_fichier) {
    // Étape 1 : Vérifier si le fichier existe
    int id_fichier = chercher_ID_Fichier(nom_fichier, memoire);
    if (id_fichier == -1) {
        printf("Erreur : Fichier \"%s\" introuvable.\n", nom_fichier);
        return;
    }

    Metadonnee *fichier = &memoire->fichiers[id_fichier];

    // Étape 2 : Charger tous les blocs du fichier dans le buffer
    charger_blocs_bufferChaine(buffer, memoire, nom_fichier);

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
    ecrire_blocs_memoireChaine(buffer, memoire, nom_fichier);

    // Libérer la mémoire allouée
    free(tableau_enregistrements);

    printf("Fichier \"%s\" trié par identifiants des enregistrements (mode contigu).\n", nom_fichier);
}
///////////////////////////////:

#endif // FUNCTIONS_CHAINE_H