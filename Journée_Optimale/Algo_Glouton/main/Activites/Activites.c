#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Déclaration d'une énumération booléenne
 */
typedef enum {VRAI, FAUX} BOOL;

/**
 * Ajout des alias pour éviter de mettre le mot-clé struct à chaque fois
 */
typedef struct Activite activite;
typedef struct ListeActivite* activites;
typedef struct Array array;

/**
 * Structure d'une activité
 */
struct Activite
{
    unsigned int identifiant;
    unsigned int heureDebut;
    unsigned int heureFin;
} Activite;

/**
 * Une liste d'activité est composée de plusieurs activité(s)
 */
struct ListeActivite
{
    activite activite;
    activites activiteSuivante;
} ListeActivite;

/**
 * Structure d'un tableau dynamique
 */
struct Array
{
    activite *array;
    size_t used;
    size_t size;
} Array;

/**
 * Permet d'insérer une activité dans la liste passée en paramètre, au début
 * @param l liste
 * @param activite activité
 */
void inserer_ActiviteDeb(activites *l, activite activite)
{
    activites liste = (activites) malloc(sizeof(activites));
    if(liste) {
        liste->activiteSuivante = *l;
        liste->activite = activite;
        *l = liste;
    }
}

/**
 * Permet d'insérer une activité dans la liste passée en paramètre, à la fin
 * @param l liste
 * @param activite activité
 */
void inserer_ActiviteFin(activites *l, activite activite)
{
    if(*l == NULL) {
        inserer_ActiviteDeb(l, activite);
    }
    else {
        inserer_ActiviteFin(&((*l)->activiteSuivante), activite);
    }
}

/**
 * Créer et initialise une activité avec les paramètres spécifiées
 * @param identifiant identifiant de l'activité
 * @param heureDebut heure de début de l'activité
 * @param heureFin heure de fin de l'activité
 * @return Activité
 */
activite initialiseActivite(unsigned int identifiant, unsigned int heureDebut, unsigned int heureFin)
{
    activite newActivite = {0};
    if(identifiant >= 0 && heureDebut >= 0 && heureFin >= 0)
    {
        if(heureDebut < heureFin)
        {
            newActivite.identifiant = identifiant;
            newActivite.heureDebut = heureDebut;
            newActivite.heureFin = heureFin;
        }
    }
    return newActivite;
}

// Variable globale
int i = 0;
/**
 * Affiche le contenu de la liste d'activité
 * @param liste liste d'activité(s)
 */
void printListeActivite(activites liste)
{
    if(liste != NULL) {
        i++;
        printf(" ------------ Activité numéro %d ------------ \n", i);
        printf("Activité ID --> %d \n", liste->activite.identifiant);
        printf("Heure de début --> %d \n", liste->activite.heureDebut);
        printf("Heure de fin --> %d \n", liste->activite.heureFin);
    }

    if(liste->activiteSuivante != NULL) {
        printf("\n\n");
        printListeActivite(liste->activiteSuivante);
    }
}

/**
 * Affiche le contenu d'une activité
 * @param activite activité
 */
void printActivite(activite activite)
{
    if(activite.identifiant == -1) {
        printf("\n L'activité n'existe pas dans la liste... \n");
    }
    else {
        printf("\n\n ----------------- Activité d'ID %d ----------------- \n", activite.identifiant);
        printf("Heure de début --> %d \n", activite.heureDebut);
        printf("Heure de fin --> %d \n", activite.heureFin);
    }
}

/**
 * Affiche un tableau d'activité
 * @param tab tableau
 * @param size taille du tableau
 */
void printTab(array tab)
{
    ssize_t tailleCrochet = snprintf(NULL, 0, "%s", "[ \n");
    ssize_t tailleContenu = snprintf(NULL, 0, "%s", "\t {Activité ID : %d, Heure de début : %d, Heure de fin : %d} \n");

    char* buffer = (char*) malloc(tailleCrochet + 1*sizeof(char));
    ssize_t sizeRealloc = 0;
    if(buffer != NULL) {
        snprintf(buffer, sizeof(buffer), "%s", "[ \n");
        for (int i = 0; i < tab.used; i++)
        {
            char bufferTampon[tailleContenu+20];
            snprintf(bufferTampon, sizeof(bufferTampon), "\t {Activité ID : %d, Heure de début : %d, Heure de fin : %d} \n", tab.array[i].identifiant, tab.array[i].heureDebut, tab.array[i].heureFin);
            sizeRealloc+= sizeof(bufferTampon);
            buffer = realloc(buffer, sizeRealloc* sizeof(char));
            strcat(buffer, bufferTampon);
            free(bufferTampon);
        }

        buffer = realloc(buffer, sizeRealloc + tailleCrochet*sizeof(char));
        strcat(buffer, "]");
        printf("%s \n", buffer);

        free(buffer);
    }
}

/**
 * Affiche une activité contenu dans une liste, en fonction d'un ID précisé en paramètre
 * @param liste liste d'activités
 * @param id id de l'activité
 * @return activité
 */
activite getActiviteByIDInList(activites liste, unsigned int id)
{
    activite activite = {-1};
    if(liste != NULL) {
        if(liste->activite.identifiant == id) {
            activite = liste->activite;
            printActivite(activite);
        }
        else {
            return getActiviteByIDInList(liste->activiteSuivante, id);
        }
    }
    return activite;
}

/**
 * Récupère l'activité dans le tableau en fonction de l'id passé en paramètre
 * @param array tableau d'activités
 * @param id id de l'activité
 * @return activité
 */
activite getActiviteByIDInTab(array array, unsigned int id)
{
    activite activite = {-1};
    if(array.used > 0) {
        for (int i = 0; i < array.used && activite.identifiant == -1; i++) {
            if(array.array[i].identifiant == id) {
                activite = array.array[i];
            }
        }
    }

    return activite;
}

/**
 * Initialise un tableau dynamique en fonction d'une taille initiale
 * @param a tableau
 * @param initialSize taille initiale du tableau
 */
void initArrayActivite(array *a, size_t initialSize)
{
    // Allocation d'espace initial
    a->array = (activite*)malloc(initialSize*sizeof(activite));
    a->used = 0;
    a->size = initialSize;

    for (int i = 0; i < initialSize; i++)
    {
        // Initialiser les valeurs du tableau à 0
        memset(&a->array[i], -1, sizeof(activite));
    }
}

/**
 * Insert un élément dans le tableau
 * @param a tableau
 * @param element élément à insérer
 */
void insertArray(array *a, activite element)
{
    if(a->used == a->size) {
        a->size += 1;
        a->array = (activite*) realloc(a->array, a->size * sizeof(activite));
    }
    a->array[a->used].identifiant = element.identifiant;
    a->array[a->used].heureDebut = element.heureDebut;
    a->array[a->used].heureFin = element.heureFin;

    a->used++;
}

/**
 * Supprime un élément du tableau directement dans ce dernier, sans copie (passage par référence *)
 * @param a tableau
 * @param element élément à supprimer
 */
void deleteArray(array *a, activite element)
{
    for (int i = 0; i < a->used; i++) {
        if(a->array[i].identifiant == element.identifiant) {
            for(int j = i; j < a->used; j++) {
                if(j+1 != a->used) {
                    a->array[j] = a->array[j+1];
                }
                else {
                    a->used -= 1;
                    a->size -= 1;
                    a->array = (activite*) realloc(a->array, a->used * sizeof(activite));
                }
            }
            break;
        }
    }
}

/**
 * Effectue un tri par insertion sur les activités pour les trier par ordre croissant selon les horaires de début
 * @param tab tableau à trier
 * Le tableau étant passé par pointeur, iol n'est pas nécessaire de le retourner
 */
void triInsertion(array *tab)
{
    int i, j;
    if(tab->used > 0) {
        for (i = 0; i < tab->used; i++) {
            activite currentActivite = tab->array[i];
            for (j = i; j > 0 && tab->array[j-1].heureDebut > currentActivite.heureDebut; j-- ) {
                tab->array[j] = tab->array[j-1];
            }
            tab->array[j] = currentActivite;
        }
    }
}

/**
 * Permet de créer une nouvelle liste d'activités optimale en appliquant l'algorithme de glouton
 * @param tab tableau contenant les activités
 * @param listeActivitesOptimale liste qui sera renvoyée avec les activités triées par intervalle de temps
 * @param dureeMinimale durée minimale d'une activité
 * @param tabTemp tableau temporaire
 * @param premierPassage
 * @return liste d'activités optimale triée
 */
activites choixActivite(array *tab, array *tabTemp, activites listeActivitesOptimale, int dureeMinimale, BOOL premierPassage)
{
    // Il faut prendre dans le tableau l'activité avec une durée minimal pour le premier passage dans la fonction
    // On se basera par la suite sur cette durée minimale
    int id = -1;

    if(premierPassage == VRAI) {
        for(int i = 0; i < tab->used; i++) {
            if(dureeMinimale == -1 || dureeMinimale > tab->array[i].heureFin - tab->array[i].heureDebut) {
                dureeMinimale = tab->array[i].heureFin - tab->array[i].heureDebut;
                id = tab->array[i].identifiant;
            }
        }
        // On récupère l'activité concerné par l'ID déterminé au dessus
        activite activiteMin = getActiviteByIDInTab(*tab, id);
        // Suppression de l'activité dans le tableau (passage par pointeur)
        deleteArray(tab, activiteMin);
        // Ajout de l'activité dans un tableau temporaire de taille initiale 0
        insertArray(tabTemp, activiteMin);
    }
    else {
        while(id == -1) {
            for(int i = 0; i < tab->used; i++) {
                if(dureeMinimale == tab->array[i].heureFin - tab->array[i].heureDebut) {
                    dureeMinimale = tab->array[i].heureFin - tab->array[i].heureDebut;
                    id = tab->array[i].identifiant;
                    dureeMinimale--;
                    break;
                }
            }
            dureeMinimale++;
        }
    }
    // Recursivité de la fonction tant que les heures début et heures fin des activités sont en dehors des plages des activités du tableau temporaire
    // On test si le tableau d'activité est vide
    if(tab->used > 0) {
        if(premierPassage == VRAI) {
            premierPassage = FAUX;
            for(int i = 0; i < tab->used; i++) {
                BOOL failed = FAUX;
                int heureDebutTemp = tab->array[i].heureDebut;
                int heureFinTemp = tab->array[i].heureFin;
                int idTemp = tab->array[i].identifiant;
                for(int j = 0; j < tabTemp->used && failed == FAUX; j++) {
                    // 1 incompatibilité suffit pour passer à l'activité suivante
                    if(heureDebutTemp >= tabTemp->array[j].heureFin || (heureDebutTemp < tabTemp->array[j].heureDebut && heureFinTemp <= tabTemp->array[j].heureDebut)) {
                        activite activiteOk = getActiviteByIDInTab(*tab, idTemp);
                        deleteArray(tab, activiteOk);
                        insertArray(tabTemp, activiteOk);
                        return choixActivite(tab, tabTemp, listeActivitesOptimale, dureeMinimale, premierPassage);
                    }
                    else {
                        failed = VRAI;
                        deleteArray(tab, tab->array[i]);
                    }
                }
            }
        }

        else {
            BOOL failed = FAUX;
            activite activite = getActiviteByIDInTab(*tab, id);
            int heureDebutTemp = activite.heureDebut;
            int heureFinTemp = activite.heureFin;

            for(int j = 0; j < tabTemp->used && failed == FAUX; j++) {
                if(heureDebutTemp >= tabTemp->array[j].heureFin || (heureDebutTemp < tabTemp->array[j].heureDebut && heureFinTemp <= tabTemp->array[j].heureDebut)) {

                }
                else {
                    failed = VRAI;
                }
            }

            deleteArray(tab, activite);
            if(failed == FAUX) {
                insertArray(tabTemp, activite);
            }

            if(tab->used > 0) {
                return choixActivite(tab, tabTemp, listeActivitesOptimale, dureeMinimale, premierPassage);
            }
        }
    }

    printf(" -------------- Affichage du tableau optimale d'activités non-trié -------------- \n");
    printTab(*tabTemp);

    // On trie ensuite les activités retenues dans l'ordre croissant en fonction des horaires de début
    triInsertion(tabTemp);
    printf(" -------------- Affichage du tableau optimale d'activités trié -------------- \n");
    printTab(*tabTemp);

    // Parcours du tableau d'activités trié et insertion de chaque élément dans la liste
    // Parcours décroissant de tabTemp pour ajouter les éléments dans l'ordre dans la liste
    for(int i = tabTemp->used -1 ; i >= 0; i--) {
        inserer_ActiviteDeb(&listeActivitesOptimale, tabTemp->array[i]);
    }

    return listeActivitesOptimale;
}

/**
 * Vide le tableau et libère la mémoire
 * @param a tableau
 */
void freeArray(array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = 0;
    a->size = 0;
}

/**
 * Méthode de test
 * @return EXIT_SUCCESS
 */
int main()
{
    // Déclaration d'une liste d'activités
    activites liste;
    liste = NULL;

    // Déclaration d'activités sous forme {id, heureDebut, heureFin} en respectant les conditions préalables
    activite a1 = initialiseActivite(1, 13, 16);
    activite a2 = initialiseActivite(2, 9, 67);
    activite a3 = initialiseActivite(3, 16, 17);
    activite a4 = initialiseActivite(4, 1, 2);
    activite a5 = initialiseActivite(5, 10, 15);
    activite a6 = initialiseActivite(6, 13, 22);

    /** Insertion des activités dans la liste
     * Chaque élément ajouté doit être placé en premier dans la liste
     */
    inserer_ActiviteDeb(&liste, a1);
    inserer_ActiviteDeb(&liste, a2);
    inserer_ActiviteDeb(&liste, a3);
    inserer_ActiviteDeb(&liste, a4);
    inserer_ActiviteDeb(&liste, a5);
    inserer_ActiviteDeb(&liste, a6);

    // Affichage de la liste --> OK
    printf(" ---------------------------- Liste d'activités ---------------------------- \n");
    printListeActivite(liste);
    printf("\n\n");

    // Ne fonctionne pas, il n'existe pas d'ID 900 dans la liste
    // Renvoi une activité avec des valeurs de 0
    printf(" ---------------- Recherche de l'activité d'ID 900 ---------------- ");
    activite activiteKO = getActiviteByIDInList(liste, 900);
    printActivite(activiteKO);
    printf("\n");
    // Fonctionne
    printf(" ---------------- Recherche de l'activité d'ID 4 ---------------- ");
    activite activiteOK = getActiviteByIDInList(liste, 4);
    printActivite(activiteOK);
    printf("\n");

    // Déclaration d'un tableau de structure dynamique à taille 2 au début
    // Déclaration tableau dynamique
    array tabActivite;
    activite a7 = initialiseActivite(7, 8, 12);
    activite a8 = initialiseActivite(8, 8, 10);
    activite a9 = initialiseActivite(9, 9, 11);
    activite a10 = initialiseActivite(10, 10, 11);
    activite a11 = initialiseActivite(11, 10, 12);
    activite a12 = initialiseActivite(12, 12, 13);
    activite a13 = initialiseActivite(13, 13, 17);
    activite a14 = initialiseActivite(14, 13, 14);
    activite a15 = initialiseActivite(15, 16, 17);
    activite a16 = initialiseActivite(16, 17, 19);
    activite a17 = initialiseActivite(17, 13, 15);
    activite a18 = initialiseActivite(18, 7, 8);
    initArrayActivite(&tabActivite, 0);
    // Remplissage du tableau dynamique avec des activités dans le désordre
    insertArray(&tabActivite, a7);
    insertArray(&tabActivite, a8);
    insertArray(&tabActivite, a9);
    insertArray(&tabActivite, a10);
    insertArray(&tabActivite, a11);
    insertArray(&tabActivite, a12);
    insertArray(&tabActivite, a13);
    insertArray(&tabActivite, a14);
    insertArray(&tabActivite, a15);
    insertArray(&tabActivite, a16);
    insertArray(&tabActivite, a17);
    insertArray(&tabActivite, a18);
    // Affichage du tableau
    printf(" -------------- Affichage du tableau dynamique d'activités -------------- \n");
    printTab(tabActivite);
    // Algorithme de solution optimale des activités
    printf(" -------------- Solution optimale du tableau d'activités par l'algorithme de glouton  -------------- \n");
    activites listeActivite = NULL;
    int dureeMinimale = -1;
    array tabTemp;
    BOOL premierPassage = VRAI;
    initArrayActivite(&tabTemp, 0);
    listeActivite = choixActivite(&tabActivite, &tabTemp, listeActivite, dureeMinimale, premierPassage);
    printf(" -------------- Affichage de la liste d'activités optimale, basée sur le tableau initial d'activités -------------- \n");
    printListeActivite(listeActivite);
    // Libération de la mémoire des tableaux
    freeArray(&tabActivite);
    freeArray(&tabTemp);

    return EXIT_SUCCESS;
}