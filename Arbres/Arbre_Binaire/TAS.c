/** ------------------------------------------------------------------------
   |                                                                        |
   |                      Arbre Binaire / TAS par tableau                   |
   |                                                                        |
    ------------------------------------------------------------------------
Création d'un arbre binaire à partir d'un TAS (fil de priorité)
Auteur : ENTEZAM Samuel (& Valentin BARRET (ce chien) qui m'a help <3 <3)
Date : 25/11/2017
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Arbre *Arbre;

/* Déclaration de la structure dynamique de l'arbre binaire */
struct Arbre
{
	int priorite;
	struct Arbre* filsGauche;
	struct Arbre* filsDroit;
};

/* Création d'un nouvel arbre */
Arbre creer_arbre(int priorite)
{
	Arbre arbre = (Arbre) malloc(sizeof(Arbre));
	arbre->priorite = priorite;
	arbre->filsGauche = NULL;
	arbre->filsDroit = NULL;

	return arbre;
}

/* Affichage du tableau des priorités */
void afficher_tas(int tab[], int tailleTab)
{
	if(tab[0] != NULL) {
		printf("\n Priorité des éléments \n");
		for(int i = 0; i < tailleTab; i++)
			printf("\t %d \n", tab[i]);
	}

	else {
		printf("\n Tableau vide \n");
	}
}

/* Opération d'initialisation du tas */
void creation_tas(int tab[], int tailleTab)
{
	for(int i = 0; i < tailleTab; i++)
		tab[i] = 0;
}

/* Nettoyage du terminal entre chaque opérations */
void clear()
{
	sleep(2);
	system("clear");
}

/* Ajout d'un élément dans le tas
Il faut ajouter l'élément à la bonne place dans le tableau en fonction des éléments déjà existants */
void ajout(int element, int tab[])
{
	int i = 0;
	int tmp;
	if(tab[0] == NULL)
		tab[0] = element;
	else {
		while(tab[i] != NULL)
			i++;
		tab[i] = element;
	}

	if(i != 0) {
		// C'est un fils droit
		if(i % 2 == 0) {
			i = (i-2)/2;
			tab[2*i+2] = element;
			while(tab[2*i+2] > tab[i]) {
				tmp = tab[2*i+2];
				tab[2*i+2] = tab[i];
				tab[i] = tmp;
				i = (i-2)/2;
			}
		}

		// C'est un fils gauche
		else if(i % 2 != 0) {
			i = (i-1)/2;
			tab[2*i+1] = element;
			while(tab[2*i+1] > tab[i]) {
				tmp = tab[2*i+1];
				tab[2*i+1] = tab[i];
				tab[i] = tmp;
				i = (i-1)/2;
			}
		}
	}
}

/* Suppression du premier élément du tableau, puis placement du dernier élément du tableau au premier
Permutation à la bonne place de nouveau en fonction des éléments déjà existants */
void supprimer(int tab[], int tailleTab)
{
	tab[0] = tab[tailleTab-1];
	tab[tailleTab-1] = NULL;
	tailleTab--;
	int i = 0;

	while(tab[i] < recup_max(tab[2*i+1], tab[2*i+2])) {
		int tmp;
		printf("%d \n", recup_max(tab[2*i+1], tab[2*i+2]));
		tmp = recup_max(tab[2*i+1], tab[2*i+2]);
		if(recup_max(tab[2*i+1], tab[2*i+2]) == tab[2*i+1]) {
			tab[2*i+1] = tab[i];
			tab[i] = tmp;
			i = 2*i+1;
		}

		else {
			tab[2*i+2] = tab[i];
			tab[i] = tmp;
			i = 2*i+2;
		}
	}

}

/* Retourne le maximum entre deux nombres */
int recup_max(int nombre1, int nombre2)
{
	int max = nombre1;
	if(nombre1 < nombre2)
		max = nombre2;

	return max;
}

int main()
{
	int tailleTab;
	printf("\n Choisir la taille du tas : ");
	scanf("%d", &tailleTab);
	printf("\n ----------------------- Création du TAS de taille %d ----------------------- \n", tailleTab);
	int tab[tailleTab];
	creation_tas(tab, tailleTab);
	int choix;

	do {
		printf("\n ------------------ [ACTIONS SUR LE TAS] ------------------ \n");
		printf("1 --> [AJOUT] d'un élément \n");
		printf("2 --> [SUPPRESSION] d'un élément \n");
		printf("3 --> [AFFICHAGE] du tableau \n");
		printf("4 --> [EXIT] \n");
		printf("\n");

		printf("Choix --> ");
		scanf("%d", &choix);

		if(choix == 1) {
			int element;
			printf("\n Élément à insérer dans le tas : ");
			scanf("%d", &element);
			ajout(element, tab);
		}

		else if(choix == 2) {
			supprimer(tab, tailleTab);
		}

		else if(choix == 3)
			afficher_tas(tab, tailleTab);

		else if(choix == 4)
			printf("Sortie \n");

		else {
			printf("Erreur de saisie ... \n");
			clear();
		}
	} while(choix != 4);

	return 0;
}