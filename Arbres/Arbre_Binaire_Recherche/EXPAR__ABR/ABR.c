/** ------------------------------------------------------------------------
   |                                                                        |
   |                         Arbre Binaire de Recherche                     |
   |                                                                        |
    ------------------------------------------------------------------------
Création d'un arbre binaire de recherche en fonction d'une expression arithmétique
Auteur : ENTEZAM Samuel
Date : 04/11/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef struct Arbre *Arbre;

struct Arbre
{
	char contenu;
	struct Arbre* filsGauche;
	struct Arbre* filsDroit;
};

/* Création d'un arbre */
Arbre nouvelArbre(char contenu, Arbre filsGauche, Arbre filsDroit)
{
	Arbre arbre = (Arbre) malloc(sizeof(Arbre));
	arbre->contenu = contenu;
	arbre->filsGauche = filsGauche;
	arbre->filsDroit = filsDroit;

	return arbre;
}

/* Affichage de l'arbre */
void print_Arbre(Arbre arbre, int tab)
{
	if(arbre != NULL) {
		for(int i = 0; i < tab; i++)
			printf("\t");
		printf("Racine --> [%c] \n", arbre->contenu);
		if(arbre->filsGauche != NULL)
			print_Arbre(arbre->filsGauche, tab-2);
		if(arbre->filsDroit != NULL)
			print_Arbre(arbre->filsDroit, tab+2);
	}
}

/* Permet d'afficher l'arbre en fonction de la priorité à gauche */
void GaucheNoeudDroite(Arbre arbre)
{
	if(arbre != NULL) {
		GaucheNoeudDroite(arbre->filsGauche);
		printf("%c \n", arbre->contenu);
		GaucheNoeudDroite(arbre->filsDroit);
	}
}

/* Permet d'afficher l'arbre en fonction de la priorité à droite */
void DroiteNoeudGauche(Arbre arbre)
{
	if(arbre != NULL) {
		DroiteNoeudGauche(arbre->filsDroit);
		printf("%c \n", arbre->contenu);
		DroiteNoeudGauche(arbre->filsGauche);
	}
}

/* Programme de test */
int main()
{
	int err;
	regex_t controle;
	const char *str_request;
	const char *str_regex = "([[:digit:]]+[\\+\\-\\*\\/])+";
	char *saisie = (char*) malloc(sizeof(char));
	printf("Saisir votre expression arithmétique : \n");
	fgets(saisie, 80, stdin);
	printf("Vous avez saisie l'expression suivante --> %s \n", saisie);
	str_request = saisie;
	err = regcomp(&controle, str_regex, REG_NOSUB | REG_EXTENDED);
	if(err == 0) {
		int match;
		match = regexec(&controle, str_request, 0, NULL, 0);
		regfree(&controle);

		if(match == REG_NOMATCH) {
			printf("%s n\'est pas une expression valide ! \n", str_request);
			exit(EXIT_FAILURE);
		}
	}

	if(saisie == NULL) {
		printf("Merci de saisir une expression ! \n");
		exit(EXIT_FAILURE);
	}

	else {
		printf("\n ------------------------ AFFICHAGE DE l'ABR ------------------------ \n");
		Arbre arbre;
		int compteurPlus = 0;
		int nbOperateur = 0;
		for(int i = 0; i < strlen(saisie); i++) {
			if(saisie[i] == '+' || saisie[i] == '-' || saisie[i] == '*' || saisie[i] == '/')
				nbOperateur++;
			switch(saisie[i]) {
				case '+':
					if(compteurPlus == 0)
						arbre = nouvelArbre('+', nouvelArbre(saisie[i-1], NULL, NULL), nouvelArbre(saisie[i+1], NULL, NULL));
					else
						arbre = nouvelArbre('+', arbre, nouvelArbre(saisie[i+1], NULL, NULL));
					compteurPlus++;
					break;
				case '-':
					if(compteurPlus == 0)
						arbre = nouvelArbre('-', nouvelArbre(saisie[i-1], NULL, NULL), nouvelArbre(saisie[i+1], NULL, NULL));
					else
						arbre = nouvelArbre('-', arbre, nouvelArbre(saisie[i+1], NULL, NULL));
					compteurPlus++;
					break;
				case '*':
					if(compteurPlus == 0)
						arbre = nouvelArbre('*', nouvelArbre(saisie[i-1], NULL, NULL), nouvelArbre(saisie[i+1], NULL, NULL));
					else
						arbre = nouvelArbre('*', arbre, nouvelArbre(saisie[i+1], NULL, NULL));
					compteurPlus++;
					break;
				case '/':
					if(compteurPlus == 0)
						arbre = nouvelArbre('/', nouvelArbre(saisie[i-1], NULL, NULL), nouvelArbre(saisie[i+1], NULL, NULL));
					else
						arbre = nouvelArbre('/', arbre, nouvelArbre(saisie[i+1], NULL, NULL));
					compteurPlus++;
					break;
			}
		}

		print_Arbre(arbre, nbOperateur*2);
	}
	return 0;
}