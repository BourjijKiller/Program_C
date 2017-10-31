/* ---------------------------------------------------------------------------
  |                                                                           |
  |                            Les Graphes / PARTIE A                         |
  |                                                                           |
   ---------------------------------------------------------------------------

Auteur : ENTEZAM Samuel
Date : 05/10/2017
*/

#include <stdio.h>
#include <stdlib.h>

#include "Exo1.c"
#include "Exo2.c"

typedef enum {ORIENTED, NON_ORIENTED} graph_type;
typedef enum {GRIS, BLANC, NOIR} graph_color;
typedef struct graphL *graphL;

struct graphL
{
	int size;
	graph_type type;
	LISTE *adjacent;
};

graphL makegraphL(int size, graph_type type)
{
	int i;
	graphL G = (graphL) malloc(sizeof(struct graphL));
	if(!G)
		return NULL;

	else {
		G->size = size;
		G->type = type;
		G->adjacent = (LISTE*) malloc(size*sizeof(LISTE));
	}

	if(!G->adjacent) {
		free(G);
		return NULL;
	}

	for(i = 0; i < size; i++)
		G->adjacent[i] =  NULL;

	if(G->type == ORIENTED)
		printf(" --------------------- Déclaration d'un graphe orienté --------------------- \n");
	else
		printf(" --------------------- Déclaration d'un graphe non-orienté --------------------- \n");
	return G;
}

graphL add_arc(graphL G, int source, int dest)
{
	if(source < G->size && dest < G->size && source >= 0 && dest >= 0) {
		if(G->type == ORIENTED)
			insert_tete(&(G->adjacent[source]), dest);
		else {
			insert_tete(&(G->adjacent[source]), dest);
			insert_tete(&(G->adjacent[dest]), source);
		}
	}

	else {
		if(source > G->size || source < 0)
			printf("Erreur, le sommet source %d n'existe pas dans le graphe ... \n", source);
		if(dest > G->size || dest < 0)
			printf("Erreur, le sommet destination %d n'existe pas dans le graphe ... \n", dest);
	}

}

void print_graph(graphL G)
{
	if(G) {
		for (int i = 0; i < G->size; i++) {
			if(!G->adjacent[i])
				printf("%d : / \n", i);
			else {
				if(G->adjacent[i] == 1) {
					printf("%d : ", i);
					print(G->adjacent[i]);
				}

				else {
					printf("%d : ", i);
					print(G->adjacent[i]);
				}
			}

			printf("\n");
		}
	}
}

void destroy_graph(graphL *G)
{
	for(int i = 0; i < (*G)->size; i++) {
		efface(&(*G)->adjacent[i]);
	}

	free((*G)->adjacent);
	free(*G);
	*G = NULL;
	if((*G) == NULL)
		printf("\n Le graphe est vide ! \n");
}

void BFT(graphL G, int source, int parent[], int distance[], graph_color couleur[])
{
	for(int i = 0; i < G->size; i++) {
		couleur[i] = BLANC;
		parent[i] = -1;
		distance[i] = -1;
	}

	file F = make_file();
	couleur[source] = GRIS;
	enfile(F, source);
	distance[source] = 0;
	LISTE liste;

	int u;
	while(empty(F) == FAUX) {
		tete_file(F, &u);
		liste = G->adjacent[u];

		while(liste != NULL) {
			if(couleur[liste->info] == BLANC) {
				couleur[liste->info] = GRIS;
				parent[liste->info] = u;
				distance[liste->info] = distance[u] + 1;
				enfile(F, liste->info);
			}
			liste = liste->suivant;
		}

		couleur[u] = NOIR;
		defile(F);
	}
}

/* ---------------------------------------------------------------------------
  |                                                                           |
  |                            Les Graphes / PARTIE B                         |
  |                                                                           |
   ---------------------------------------------------------------------------

Auteur : ENTEZAM Samuel
Date : 19/10/2017
*/

typedef enum {FALSE, TRUE} boolean;

void dft_recherche_circ(graphL G, int source, graph_color* color, boolean *CIRCUIT)
{
	if(G->type == ORIENTED) {
		color[source] = GRIS;
		*CIRCUIT = FALSE;
		LISTE L = G->adjacent[source];

		while(L != NULL) {
			switch(color[L->info]) {
				case BLANC :
					dft_recherche_circ(G, L->info, color, CIRCUIT);
					break;
				case GRIS :
					*CIRCUIT = TRUE;
					break;
			}

			L = L->suivant;
		}

		color[source] = NOIR;
	}

	else {
		printf("Erreur, le graphe n'est pas orienté ! \n");
		exit(EXIT_FAILURE);
	}
}

boolean recherche_circuit(graphL G)
{
	boolean CIRCUIT = FALSE;
	graph_color color[G->size];
	for(int i = 0; i < G->size; i++)
		color[i] = BLANC;

	for(int j = 0; j < G->size; j++) {
		if(color[j] == BLANC)
			dft_recherche_circ(G, j, color, &CIRCUIT);
		if(CIRCUIT == TRUE)
			return TRUE;
	}

	return FALSE;
}

void dft_top_sortDAG(graphL G, int source, graph_color* color, LISTE* sorted)
{
	color[source] = GRIS;
	LISTE L = G->adjacent[source];
	trieListe(L);

	while(L != NULL) {
		if(color[L->info] == BLANC)
			dft_top_sortDAG(G, L->info, color, sorted);
		L = L->suivant;
	}

	color[source] = NOIR;
	insert_tete(sorted, source);
}

LISTE topsort(graphL G)
{
	graph_color color[G->size];
	for(int i = 0; i < G->size; i++)
	{
		color[i] = BLANC;
	}

	LISTE L3 = NULL;
	for (int j = 0; j < G->size; j++)
	{
		if(color[j] == BLANC)
			dft_top_sortDAG(G, j, color, &L3);
	}

	print(L3);
	return L3;
}

void trieListe(LISTE L)
{
	LISTE tmp1, tmp2, tmp3;
	int min;

	for(tmp1 = L ; tmp1 != NULL ; tmp1 = tmp1->suivant) {
		tmp3 = tmp1;
		min = tmp1->info;
		for(tmp2 = tmp1->suivant ; tmp2 != NULL ; tmp2 = tmp2->suivant) {
			if(min > tmp2->info) {
				tmp3 = tmp2;
				min = tmp3->info;
			}
		}

		tmp3->info = tmp1->info;
		tmp1->info = min;
	}
}


int main()
{
	graphL G;
	graphL G2;
	graphL G3;
	graphL G4;
	G = makegraphL(5, ORIENTED);
	add_arc(G, 1, 2);
	add_arc(G, 0, 4);
	add_arc(G, 3, 2);
	add_arc(G, 3, 0);
	add_arc(G, 3, 4);
	add_arc(G, 1, 0);
	add_arc(G, 4, 3);
	add_arc(G, 2, 1);
	print_graph(G);
	int *parent = (int*) malloc(G->size*sizeof(int));
	int *distance = (int*) malloc(G->size*sizeof(int));
	graph_color *couleur = (graph_color*) malloc(G->size*sizeof(graph_color));
	BFT(G, 0, parent, distance, couleur);
	printf(" --------------------- BFT --------------------- \n");
	for(int i = 0; i < G->size; ++i)
	{
		if(i == 0)
			printf("\n %d \n", parent[i]);
		else {
			printf("\n | \n");
			printf(" v \n");
			printf("\n %d \n", parent[i]);
		}
	}

	printf(" --------------------- Vérification de circuit --------------------- \n");
	if(recherche_circuit(G) == TRUE) {
		printf("Le graphe contient un circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		printf("\n Pas de tri topologique \n");
	}

	else {
		printf("Le graphe ne contient pas de circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		topsort(G);
	}


	printf("\n --------------------- Destruction du graphe --------------------- \n");
	destroy_graph(&G);

	G2 = makegraphL(4, ORIENTED);
	add_arc(G2, 0, 1);
	add_arc(G2, 1, 2);
	add_arc(G2, 2, 3);
	print_graph(G2);

	printf(" --------------------- Vérification de circuit --------------------- \n");
	if(recherche_circuit(G2) == TRUE) {
		printf("\n Le graphe contient un circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		printf("\n Pas de tri topologique \n");
	}

	else {
		printf("Le graphe ne contient pas de circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		topsort(G2);
	}


	printf("\n --------------------- Destruction du graphe --------------------- \n");
	destroy_graph(&G2);

	G3 = makegraphL(4, NON_ORIENTED);
	add_arc(G3, 0, 2);
	add_arc(G3, 1, 2);
	add_arc(G3, 2, 3);
	add_arc(G3, 0, 3);
	print_graph(G3);

	printf("\n --------------------- Destruction du graphe --------------------- \n");
	destroy_graph(&G3);

	G4 = makegraphL(9, ORIENTED);
	add_arc(G4, 0, 1);
	add_arc(G4, 0, 7);
	add_arc(G4, 1, 2);
	add_arc(G4, 1, 7);
	add_arc(G4, 2, 5);
	add_arc(G4, 3, 4);
	add_arc(G4, 3, 2);
	add_arc(G4, 4, 5);
	add_arc(G4, 8, 7);
	print_graph(G4);

	printf(" --------------------- Vérification de circuit --------------------- \n");
	if(recherche_circuit(G4) == TRUE) {
		printf("\n Le graphe contient un circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		printf("\n Pas de tri topologique \n");
	}

	else {
		printf("Le graphe ne contient pas de circuit \n");
		printf("\n --------------------- Tri topologique DAG --------------------- \n");
		topsort(G4);
	}


	printf("\n --------------------- Destruction du graphe --------------------- \n");
	destroy_graph(&G4);

	return 0;
}