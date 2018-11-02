# CONSTRUCTION D'UNE JOURNÉE OPTIMALE COMPOSÉE D'ACTIVITÉS
#### Implémentation de l'algorithme de _Glouton_
-------------------------------------------------------------------

## DESCRIPTION
-------------------------------------------------------------------
Ce programme implémenté en langage C permet, à partir d'un tableau d'activités quelconque, de renvoyer une liste d'activités optimales.

Dans le contexte du programme, une **liste d'activités optimale** représente en réalitée une journée contenant le plus d'activités possibles, tout en vérifiant que chaque activités ne se _piétine_ pas entre elles.

Une activité est structurée comme suit :
```c
   /**
    * Structure d'une activité
    */
   struct Activite
   {
       unsigned int identifiant;
       unsigned int heureDebut;
       unsigned int heureFin;
   } Activite;
```
* _Un identifiant pseudo-unique_ (le programme ne vérifie pas si l'identifiant existe déjà dans le tableau)
* _Une heure de début_ de l'activité **(int)**
*  _Une heure de fin_ de l'activité **(int)**

Afin de vérifier que les activités ne sont pas en conflits les une sur les autres, on va donc effectuer une vérification sur l'heure de début et l'heure de fin.

Ce concept de liste optimale fait référence à l'algorithme _[Glouton](https://fr.wikipedia.org/wiki/Algorithme_glouton)_ qui est un algorithme **d'optimisation** en informatique.

## FONCTIONS IMPLÉMENTÉES
-------------------------------------------------------------------
Le programme implémente de nombreuses méthodes, mais des plus générales et utiles peuvent être utilisées dans d'autres programmes en C :

* Déclaration et opérations sur des **listes chaînées** (voir [ici](https://github.com/BourjijKiller/Program_C/blob/master/Listes/Exo1.c))
* Création d'une méthode permettant de concaténer des chaînes de caractères et de renvoyer l'ensemble
```c
    /**
     * Affiche un tableau d'activité
     * @param tab tableau
     * @param size taille du tableau
     */
    void printTab(array tab)
```
* Déclaration et manipulation de données sur un tableau dynamique
```c
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
 * Insert un élément dans le tableau
 * @param a tableau
 * @param element élément à insérer
 */
void insertArray(array *a, activite element)

/**
 * Supprime un élément du tableau directement dans ce dernier, sans copie (passage par référence *)
 * @param a tableau
 * @param element élément à supprimer
 */
void deleteArray(array *a, activite element)

/**
 * Vide le tableau et libère la mémoire
 * @param a tableau
 */
void freeArray(array *a)
```

*  Implémentation du [tri par insertion]() prenant en paramètre un tableau d'éléments, et retournant un tableau trié (si le tableau passé en paramètre est directement passé par référence, c'est ce dernier qui est modifié et par conséquent, il n'est pas nécessaire de le retourner)
```c
/**
 * Effectue un tri par insertion sur les activités pour les trier par ordre croissant selon les horaires de début
 * @param tab tableau à trier
 * Le tableau étant passé par pointeur, il n'est pas nécessaire de le retourner
 */
void triInsertion(array *tab)
```

Le programme est assez flexible, on peut donc :
1. Déclarer des activités avec la fonction `initialiseActivite`
2. Insérer des activités en début d'une liste chaînée avec la fonction `inserer_ActiviteDeb`
3. Insérer des activités en fin de liste chaînée avec la fonction `inserer_ActiviteFin`
4. Afficher le contenu d'une activité avec la fonction `printActivite`
5. Afficher le contenu d'une liste d'activités avec la fonction `printListeActivite`
6. Afficher le contenu d'un tableau dynamique d'activités avec la fonction `printTab`
7. Rechercher et retourner une activité dans une liste en fonction de son identifiant avec la fonction `getActiviteByIDInList`
8. Appliquer l'algorithme de **Glouton** pour renvoyer une liste d'activités optimale avec la fonction `choixActivite`

## UTILISATION ET TESTS
-------------------------------------------------------------------
1. Compilation et exécution avec un _compilateur C_ (GCC)
2. Utilisation d'un IDE ([JetBrains CLion](https://www.jetbrains.com/clion/))