#ifndef STRUCTURES_H
#define STRUCTURES_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define TAILLE_BLOC_MIN 128  // Taille minimale d'un bloc en octets 
#define MAX_FICHIERS 10  // Nombre maximal de fichiers
#define MAX_ENREGISTREMENTS 50  // Nombre maximal d'enregistrements par fichier 
#define MAX_DATA_SIZE 64        // taille max des donnée dans un enregistrement
#define MAX_BLOCS 100
// #define MAX_ENREGISTREMENTS ?   // à calculer après avoir saisie la taille du bloc

#define Contigue 1
#define Chained  2
#define Trie     1
#define Non_Trie 0
/////////////////////////////////////                           /////////////////////////////////////////////////////////
////////////////////////////////////  // Variables globales // /////////////////////////////////////////////////////////


extern char nom_fichier[50];
extern char nouv_nom[50];
extern int mode_global;
extern int id_enregistrement;
extern bool logic;
extern int nb_fichiers;                                   // Compteur de fichiers
extern int nb_blocs;                                      // Nombre total de blocs (taille disque en bloc)
extern int taille_Bloc;                                       // taille du bloc disque
extern int taille_en_Bloc;                                // Taille fichier en bloc
extern int nbMax_enregistrement;                          // nombre d'enregistrement MAx par bloc à calculer en fonction de la taille de bloc proposé
extern int nb_enregistrement;                             // Nombre maximal d'enregistrements par fichier 
extern size_t taille_enregistrement;
extern int tri;
/////////////////////////////////////////    Les structures    /////////////////////////////////////////////////////////
//size_t taille_enregistrement = sizeof(Enregistrement);
typedef struct {
    int id;                        // Identifiant unique de l'enregistrement
    char data[MAX_DATA_SIZE];      // Données de l'enregistrement
    int taille;                    // Taille des données
} Enregistrement;

typedef struct {
    int id;                  // Identifiant du fichier
    char nom[50];            // Nom du fichier
    //int blocs[10];         // Indices des blocs alloués, non utilisé
    int premier_bloc;        // Index du premier bloc (cas contigue) du fichier, et utilisé comme pointeur du premier bloc (cas chainé)
    int nb_blocs;            // Nombre de blocs utilisés (taille en blocs)
    int nb_enreg;            // Taille totale du fichier en enregistrement calculé en fonction du champ nb_enregistrements dans struct bloc
    int mode_global;         // contigue ou chainé
    int mode_interne;        // trié ou non
} Metadonnee;

typedef struct {
    int id_fichier;                                         // "facultatif utilisé pour le débogage", codé sur 4 octets:  Identifiant du fichier utilisant le bloc (ou -1 si vide)
    bool is_used;                                           // "remplace la table des blocs libre" codé sur un bit:    Indicateur si le bloc est utilisé
    int next_bloc;                                          // "Mode Chainé" codé sur 4 octets:  Index du prochain bloc dans la chaîne (-1 si fin de chaîne)
    Enregistrement *enregistrements;                        // max_enregistrement: Pointeur vers les enregistrements
    int nb_enregistrements;                                 // codé sur 4 octets:  Nombre d'enregistrements dans le bloc
} Bloc;

// Structure pour regrouper les métadonnées globales (mémoire secondaire)
typedef struct MemoireSecondaire {
    int nb_fichiers;  // Nombre de fichiers
    Bloc *disque;
    Metadonnee *fichiers;
    int nb_bloc_disque;
} MemoireSecondaire;

//////////////////////////////////////////////////// Structure Buffer //////////////////////////////////////////////////////
typedef struct {
    Bloc *data;        // Pointeur vers les blocs stockés dans le buffer
    int taille_max;    // Capacité maximale du buffer (nombre de blocs)
    int taille_actuelle; // Nombre actuel de blocs dans le buffer
} Buffer;

/////////////////////////////////////////////////////Divers/////////////////////////////////////////////////////////////////


// Code ANSI pour la couleur
#define RESET   "\033[0m"
#define ROUGE   "\033[31m"  // Rouge pour les blocs libres
#define VERT    "\033[32m"  // Vert pour les blocs utilisés
#define JAUNE   "\033[33m"   // Jaune pour le menu
#define BLEU    "\033[34m"   // Bleu pour le titre
#define CYAN    "\033[1;36m" // Cyan clair pour le titre
#define FOND_JAUNE     "\033[43m"   // Arrière-plan jaune
#define FOND_BLANC     "\033[47m"   // Arrière-plan blanc
#define TEXTE_NOIR     "\033[30m"   // Texte noir

#endif