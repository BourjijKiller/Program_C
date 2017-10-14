#include <stdio.h>
#include <stdlib.h>

typedef struct maillon* LISTE;
typedef struct maillon
{
	int info;
	LISTE suivant;
} maillon;

void insert_tete(LISTE* pl, int n)
{
	LISTE L = (LISTE) malloc(sizeof(maillon));
	if(L)
	{
		L->suivant = *pl;
		L->info = n;
		*pl = L;
	}
}

void print(LISTE L)
{
	if(L != NULL)
	{
		printf("%d \n", L->info);
		if(L->suivant != NULL)
		{
			print(L->suivant);
		}
	}
}

LISTE recherche(LISTE L, int n)
{
	if(L == NULL)
		return NULL;
	else
	{
		if(L->info == n)
			return L;

		else
			return recherche(L->suivant, n);
	}

	exit(EXIT_SUCCESS);
}

void insert_fin(LISTE* pl, int n)
{
	if(*pl == NULL)
	{
		insert_tete(pl, n);
	}

	else
	{
		insert_fin(&((*pl)->suivant),n);
	}
}

void supprimer_premier(LISTE *pl)
{
	LISTE tmpListe = *pl;
	*pl = (*pl)->suivant;
	free(tmpListe);
}

void supprime(LISTE *pl, int n)
{
	if(pl == NULL)
		exit(EXIT_FAILURE);
	else
	{
		if((*pl)->info == n)
		{
			supprimer_premier(pl);
		}

		else
		{
			supprime(&((*pl)->suivant),n);
		}
	}
}

void efface(LISTE *pl)
{
	if(*pl != NULL)
	{
		supprimer_premier(pl);
		efface(pl);
	}
	
	else
	{
		printf("\n Liste vide \n");
		exit(EXIT_FAILURE);
	}
}


int main()
{
	LISTE L;
	L = NULL;

	insert_tete(&L, 1);
	insert_tete(&L, 2);
	insert_tete(&L, 3);
	insert_tete(&L, 4);
	insert_tete(&L, 5);
	insert_tete(&L, 6);
	insert_tete(&L, 7);
	insert_tete(&L, 8);
	insert_tete(&L, 9);
	printf(" -------------- Affichage de la liste -------------- \n");
	print(L);
	printf(" -------------- Affichage de la sous-liste avec n = 5 --------------\n");
	print(recherche(L, 5));
	printf(" -------------- Insertion de l'élément 10 en fin de liste -------------- \n");
	insert_fin(&L, 10);
	print(L);
	printf(" -------------- Supprimer le premier élément de la liste -------------- \n");
	supprimer_premier(&L);
	print(L);
	printf(" -------------- Liste sans le 5 --------------\n");
	supprime(&L, 5);
	print(L);
	printf(" -------------- Suppression de la liste -------------- \n");
	efface(&L);

	return EXIT_SUCCESS;
}