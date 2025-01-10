///////////////////////////////////////////////////////   Projet fait par SAHRAOUI Amani  dans le cadre du module (SFSD) Systèmes de fichiers //////////////////
//// SAHRAOUI Amani éudiante en USTHB:                                                                                                                    //////
//// 2ème Année Ingénieur en Informatique Groupe 2 - Section C                                                                                            //////
//// Ce TP sert comme un simulateur de systèmes de gestion de fichier                                                                                     //////
//// Deux SGF sont simulés en deux couches :                                                                                                              //////
//// 1- Système     : pour la reservation et l'allocation de la mémoire secondaire  en mode contigu et chainé                                             //////
//// 2- utilisateur : pour la création des fichiers (enregistrements et données)                                                                          //////
//// 3- un menu textuel est programmé pour s'interfacer avec l'utilisateur (en mono), l'affichage des métadonnées, etc.                                   //////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <time.h>
#include "functionsContigue.h"
#include "FunctionsChaine.h"  
//#include "Buffer.h"
///////////////////////////////////////////////  Variables Globales  /////////////////////////////////////////////
char nouv_nom[50];
char nom_fichier[50];
int mode_global=0;
int id_enregistrement=0;
bool logic = 1;                 // 1 pour suppression logique, 0 pour suppression physique
int nb_fichiers = 0;            // Compteur de fichiers
int nb_blocs = 0;               // Nombre total de blocs
int taille_Bloc = 0;            // taille du bloc de la mémoire secondaire (disq)
int taille_en_Bloc = 0;         // taille fichier en bloc
int nbMax_enregistrement = 0;   // Nombre max d'enregistrements par bloc
int nb_enregistrement = 0;
bool memoire_initialisee = false;
size_t taille_enregistrement = sizeof(Enregistrement);
//////////////////////////////////////                          //////////////////////////////////////////
///
int main() {
    strcpy(nom_fichier, "fileinit");
    strcpy(nouv_nom, "filenew");
    SetConsoleOutputCP(CP_UTF8);
    int choix;
    MemoireSecondaire memoireContigue;                   // Ces mémoires secondaire sont les deux disque à manipuler dans tous les cas
    MemoireSecondaire memoireChaine;
    memoireContigue.nb_bloc_disque = 0;         // init taille disque à zero
    memoireChaine.nb_bloc_disque = 0;
    Buffer buffer;
    initialiser_buffer(&buffer, 10); // Taille du buffer, par exemple 10 blocs
    afficherLicence();
    do {
        
        afficherMenu();
        printf("Choisissez une option (1-15) sur disc %d:\\>", mode_global);
        if (scanf("%d", &choix) != 1) {
        printf("Entrée invalide.\n");
        choix = 0; // Réinitialiser la variable pour éviter des comportements imprévus
        while (getchar() != '\n'); // Vider le tampon
        }

        switch (choix) {
            case 1:                            /*** initialisation de la mémoire secondaire */
            mode_global=confirmer_Type_Memoire_Secondaire();
                if(mode_global== Contigue){
                /***** Initialisation du disque contigu *****/
                initialiserMemoireSecondaire(&memoireContigue, Contigue);
                afficher_Memoire_Secondaire(&memoireContigue, Contigue);}
                else {
                /***** Initialisation du disque chaîné *****/
                initialiserMemoireSecondaire(&memoireChaine, Chained);
                afficher_Memoire_Secondaire(&memoireChaine, Chained);}
                memoire_initialisee=true;
            break;
            case 2:             /*****          Création de fichiers                       *****/
                if (!memoire_initialisee) {
                    printf(ROUGE "Erreur : La mémoire secondaire n'a pas été initialisée.\n");
                    printf("Veuillez initialiser la mémoire avant de créer des fichiers.\n");
                    break;
                }

                printf(VERT "Quel est le nombre d'enregistrements de votre fichier à créer : ");
                Saisir_Nombre_Enreg(&nb_enregistrement);

                preciser_fichier(2); // Obtenir le nom du fichier
                taille_en_Bloc = calculer_nombre_blocs(nb_enregistrement, nbMax_enregistrement);
                printf("Nombre de blocs nécessaires : %d\n", taille_en_Bloc);

                // Définir l'organisation externe
                if (choisir_Type_Systeme_Fichier() == Contigue) {
                    creer_FichierContigue(&memoireContigue, nom_fichier, taille_en_Bloc);
                    remplir_FichierContigu(&memoireContigue, nom_fichier);
                } else {
                    creer_FichierChaine(&memoireChaine, nom_fichier, taille_en_Bloc);
                    remplir_FichierChaine(&memoireChaine, nom_fichier);
                }

                break;

            case 3:
                if(mode_global== Contigue)
                afficher_Memoire_Secondaire(&memoireContigue, Contigue);
                else
                afficher_Memoire_Secondaire(&memoireChaine, Chained);
                break;
            case 4:                             /** afficher les metadonnées des fichiers */
                if(mode_global== Contigue)
                afficher_Metadonnees(&memoireContigue, Contigue);
                else
                afficher_Metadonnees(&memoireChaine, Chained);              
                break;
            case 5: {                          /** inserer un enregistrement et afficher le contenu d'un fichier */
                preciser_fichier(5);
                Enregistrement enregistrement=saisir_Enregistrement();
                Buffer buffer;                  // préparer Buffer
                initialiser_buffer(&buffer, 100); // Initialisation du buffer avec une capacité de 10 blocs
                if(mode_global== Contigue){
                 if (inserer_EnregistrementContigue(&memoireContigue, nom_fichier, &enregistrement) == 1) {
                    printf("Insertion réussie.\n");
                    trier_FichierParIDContigu(&memoireContigue, &buffer, nom_fichier);
                       free(buffer.data);
                 } else {
                     printf("Échec de l'insertion.\n");
                 }
                    afficher_contenu_du_fichier(&memoireContigue, nom_fichier);
                }
                else{
                 if (inserer_EnregistrementChaine(&memoireChaine, nom_fichier, &enregistrement) == 1) {
                    printf("Insertion réussie.\n");
                    trier_FichierParIDChaine(&memoireChaine, &buffer, nom_fichier);
                        free(buffer.data);
                 } else {
                     printf("Échec de l'insertion.\n");
                 }
                    afficher_contenu_du_fichier(&memoireChaine, nom_fichier);
                }
                break;
            }
            case 6:
                preciser_fichier(6);           /** rechercher un enregistrement */
                id_enregistrement= preciser_enregistrement(6);
                if(mode_global== Contigue)
                rechercher_EnregistrementContigue(nom_fichier, id_enregistrement, &memoireContigue);
                else
                rechercher_EnregistrementChaine(nom_fichier, id_enregistrement, &memoireContigue);
                break;
            case 7:
                preciser_fichier(7);        /** supprimer un enregistrement  */
                id_enregistrement= preciser_enregistrement(7);
                logic = preciser_logic();
                if (logic){
                if(mode_global== Contigue){
                    supprimer_enregistrementContigue(&memoireContigue, nom_fichier, id_enregistrement);  //  suppression logique de l'enrigistrement
                    afficher_contenu_du_fichier(&memoireContigue, nom_fichier);
                }
                else {
                    supprimer_enregistrementChaine(&memoireChaine, nom_fichier, id_enregistrement);
                    afficher_contenu_du_fichier(&memoireContigue, nom_fichier);
                }

                }
                else{
                    if(mode_global== Contigue){
                        defragmenter_Fichier(&memoireContigue,nom_fichier); //  defragmenter les enregistrement après suppression (compacter)
                        afficher_contenu_du_fichier(&memoireContigue, nom_fichier);
                    }
                    else {
                        defragmenter_Fichier(&memoireChaine,nom_fichier); //  defragmenter les enregistrement après suppression (compacter)
                        afficher_contenu_du_fichier(&memoireChaine, nom_fichier);
                    }
                }
                break;
            case 8:                     /**  defragmenter le contenu d'un fichier */
                preciser_fichier(8);
                if(mode_global== Contigue){
                    defragmenter_Fichier(&memoireContigue,nom_fichier);
                    afficher_contenu_du_fichier(&memoireContigue, nom_fichier);}
                else{
                    defragmenter_Fichier(&memoireChaine,nom_fichier); //  defragmenter les enregistrement après suppression (compacter)
                    afficher_contenu_du_fichier(&memoireChaine, nom_fichier);  
                }
                break;
            case 9:                    /** supprimer un fichier */
                preciser_fichier(9);
                if(mode_global== Contigue){
                supprimer_FichierContigue(&memoireContigue, nom_fichier);}
                else{
                supprimer_FichierChaine(&memoireChaine, nom_fichier);
                }
                break;

            case 10: {                /* renomer un fichier */
                preciser_fichier(10);
                printf("Entrez le nouveau nom du fichier : ");
                preciser_nouv_fichier();
                if(mode_global== Contigue)
                renommer_Fichier(&memoireContigue, nom_fichier, nouv_nom);
                else 
                renommer_Fichier(&memoireChaine, nom_fichier, nouv_nom);
                break;  
            }
            case 11:                /*** compacter la memoire secondaire */
                if(mode_global== Contigue){
                compactage_Contigue(&memoireContigue);
                mettreAJourPremierBlocApresCompactage(&memoireContigue);}
                else{
                compactage_Chaine(&memoireChaine);
                mettreAJourPremierBlocApresCompactage(&memoireChaine);}
                break;
            case 12: {                /***** Vider la mémoire secondaire *****/
                if(mode_global== Contigue){
 
                for (int i = 0; i < memoireContigue.nb_bloc_disque; i++) {
                    free(memoireContigue.disque[i].enregistrements);
                }
                free(memoireContigue.disque);
                free(memoireContigue.fichiers);
                printf("Mémoire secondaire libérée.\n");}
                else{
                for (int i = 0; i < memoireContigue.nb_bloc_disque; i++) {
                    free(memoireContigue.disque[i].enregistrements);
                }
                free(memoireContigue.disque);
                free(memoireContigue.fichiers);
                printf("Mémoire secondaire libérée.\n"); 
                }
                break;
            }
            case 13:
            changer_ModeGlobal();

            if (mode_global == Contigue) {
                    printf("Les opérations seront effectuées en mode Contigu.\n");
            } else if (mode_global == Chained) {
                   printf("Les opérations seront effectuées en mode Chaîné.\n");
            }
                break;
            case 14:
            preciser_fichier(14);
            if (mode_global == Contigue)
            afficher_contenu_du_fichier(&memoireContigue, nom_fichier);
            else
            afficher_contenu_du_fichier(&memoireChaine, nom_fichier);
            break; 
            case 15:
                printf("Merci d’avoir utilisé le simulateur !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir entre 1 et 13.\n");
                break;
        }
        printf("\n");
    
    } while (choix != 15);

    return 0;
}