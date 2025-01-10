#ifndef BUFFER_H
#define BUFFER_H
/////////////////////////////////////////////////////////////// Prototypes
// Prototypes
void initialiser_buffer(Buffer *buffer, int taille_max);
void charger_blocs_bufferContigue(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier);
void ecrire_blocs_memoireContigue(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier);
/////////////////////////////////////////////////////////////////////////
void initialiser_buffer(Buffer *buffer, int taille_max);
void charger_blocs_bufferChaine(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier);
void ecrire_blocs_memoireChaine(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier);
/////////////////////////////////////////////////////////////////////////
void initialiser_buffer(Buffer *buffer, int taille_max) 
{
    buffer->data = (Bloc *)malloc(taille_max * sizeof(Bloc));
    buffer->taille_max = taille_max;
    buffer->taille_actuelle = 0;
}
void charger_blocs_bufferContigue(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier) {
    buffer->taille_actuelle = 0;  // Réinitialiser la taille actuelle

    // Recherche de la Metadonnee correspondant au nom_fichier
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];
            
            // Copier les blocs associés à ce fichier dans le buffer
            int bloc_id = fichier->premier_bloc;
            while (bloc_id != -1 && buffer->taille_actuelle <= fichier->nb_enreg) {
                buffer->data[buffer->taille_actuelle] = memoire->disque[bloc_id];
                buffer->taille_actuelle++;
                // Passer au bloc suivant
                bloc_id ++;
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////:::: Reverser les bloc vers le fichier
void ecrire_blocs_memoireContigue(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier) {
    // Rechercher le fichier dans la mémoire secondaire
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
    int index_buffer = 0;

    // Écrire les blocs du buffer dans la mémoire secondaire pour ce fichier
    while (bloc_id != -1 && index_buffer < buffer->taille_actuelle) {
        Bloc *bloc = &buffer->data[index_buffer];


            memoire->disque[bloc_id] = *bloc;  // Écrire dans la mémoire secondaire
            index_buffer++;
        // Passer au bloc suivant
        bloc_id ++;
    }

    printf("Blocs écrits dans la mémoire secondaire pour le fichier \"%s\".\n", nom_fichier);
}
//////////////////////////////////////////////////////////////////////////  partie chainé



void charger_blocs_bufferChaine(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier) {
    buffer->taille_actuelle = 0;  // Réinitialiser la taille actuelle
int index_buffer = 0;
    // Recherche de la Metadonnee correspondant au nom_fichier
    for (int i = 0; i < memoire->nb_fichiers; ++i) {
        if (strcmp(memoire->fichiers[i].nom, nom_fichier) == 0) {
            Metadonnee *fichier = &memoire->fichiers[i];
            
            // Copier les blocs associés à ce fichier dans le buffer
            int bloc_id = fichier->premier_bloc;
            while (bloc_id != -1 && buffer->taille_actuelle <= fichier->nb_enreg) {
                Bloc *bloc = &buffer->data[index_buffer];
                buffer->data[buffer->taille_actuelle] = memoire->disque[bloc_id];
                buffer->taille_actuelle++;
                // Passer au bloc suivant
                 bloc_id = bloc->next_bloc; // Passer au bloc suivant
                 index_buffer ++;
            }
            break;
        }
    }
}

///////////////////////////////////////////////////////////:::: Reverser les bloc vers le fichier
void ecrire_blocs_memoireChaine(Buffer *buffer, MemoireSecondaire *memoire, const char *nom_fichier) {
    // Rechercher le fichier dans la mémoire secondaire
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
    int index_buffer = 0;

    // Écrire les blocs du buffer dans la mémoire secondaire pour ce fichier
    while (bloc_id != -1 && index_buffer < buffer->taille_actuelle) {
        Bloc *bloc = &buffer->data[index_buffer];


            memoire->disque[bloc_id] = *bloc;  // Écrire dans la mémoire secondaire
            index_buffer++;
        // Passer au bloc suivant
          bloc_id = bloc->next_bloc; // Passer au bloc suivant
    }

    printf("Blocs écrits dans la mémoire secondaire pour le fichier \"%s\".\n", nom_fichier);
}
#endif