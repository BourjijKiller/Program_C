#include <stdio.h>
#include <stdlib.h>

#include "Exo1.c"

typedef struct file
{
	LISTE deb;
	LISTE fin;
} *MA_FILE;

typedef enum {FAUX, VRAI} booleen;

typedef enum {OK, ERROR} status;

MA_FILE make_file()
{
	MA_FILE mafile = (MA_FILE) malloc(sizeof(MA_FILE));
	if(mafile)
	{
		mafile->deb = NULL;
		mafile->fin = NULL;
	}

	return mafile;
}

booleen vide(MA_FILE f)
{
	booleen estvide;
	if(f->deb == NULL)
		estvide = VRAI;
	else
		estvide = FAUX;

	return estvide;
}

status tete_file(MA_FILE f, int *element)
{
	status isError;

	if(vide(f) == VRAI)
		isError = ERROR;
	else
	{
		*element = (f->deb)->info;
		isError = OK;
	}

	return isError;
}

status enfile(MA_FILE f, int n)
{
	status isOk = OK;
	insert_fin(&(f->deb), n);
	return isOk;
}

status defile(MA_FILE f)
{
	status isStatus;
	if(vide(f) == VRAI)
		isStatus = ERROR;

	else
	{
		supprimer_premier(&(f->deb));
		isStatus = OK;
	}

	return isStatus;
}

int main()
{
	MA_FILE F = make_file();
	printf("Création de la file \n ");
	enfile(F, 5);
	enfile(F, 7);
	enfile(F, 9);
	enfile(F, 11);
	print(F->deb);

	printf("Supprime le premier élément \n");
	defile(F);
	print(F->deb);
	
	return EXIT_SUCCESS;
}