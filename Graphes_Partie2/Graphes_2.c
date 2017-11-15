/* ---------------------------------------------------------------------------
  |                                                                           |
  |                            Graphes pondérés                               |
  |                                                                           |
   ---------------------------------------------------------------------------

Auteur : ENTEZAM Samuel
Date : 26/10/2017
*/

#include <stdio.h>
#include <stdlib.h>

#define INFINITE 10000000

typedef struct noeud
{
	int element;
	int poids;
	struct noeud* suivant;
} *listepond;

typedef enum {ORIENTED, NON_ORIENTED} graph_type;
typedef enum {OK, ERROR} status;
typedef enum {VRAI, FAUX} boolean;

typedef struct graphPL *graphpond;
struct graphPL
{
	int size;
	graph_type type;
	listepond* adjacent;
};

void insert_tete(listepond* PL, int element, int poids)
{
	listepond L = (listepond) malloc(sizeof(listepond));
	if(L) {
		L->suivant = *PL;
		L->element = element;
		L->poids = poids;
		*PL = L;
	}
}

void print_liste(listepond L)
{
	if(L != NULL) {
		printf("[%d avec poids = %d] ", L->element, L->poids);

		if(L->suivant != NULL)
		{
			printf(" --> ");
			print_liste(L->suivant);
		}
	}
}

void efface(listepond *PL)
{
	if(*PL != NULL) {
		efface(&((*PL)->suivant));
		free(*PL);
		*PL = NULL;
	}
}


graphpond makegraph(int size, graph_type type)
{
	int i;
	graphpond G = (graphpond) malloc(sizeof(graphpond));
	if(!G)
		return NULL;
	else {
		G->size = size;
		G->type = type;
		G->adjacent = (listepond*) malloc(size*sizeof(listepond));
	}

	if(!G->adjacent) {
		free(G);
		return NULL;
	}

	for(i = 0; i < size; i++)
		G->adjacent[i] =  NULL;

	return G;
}

status add_arc(graphpond G, int source, int dest, int poids)
{
	if(source < G->size && dest < G->size && source >= 0 && dest >= 0) {
		switch(G->type) {
			case ORIENTED:
				insert_tete(&(G->adjacent[source]), dest, poids);
				break;
			case NON_ORIENTED:
				insert_tete(&(G->adjacent[source]), dest, poids);
				insert_tete(&(G->adjacent[dest]), source, poids);
		}

		return OK;
	}

	else
		return ERROR;
}

void print_graph(graphpond G)
{
	if(G) {
		for(int i = 0; i < G->size; i++) {
			if(!G->adjacent[i])
				printf(" %d : / \n", i);
			else {
				if(G->adjacent[i] == 1) {
					printf(" %d : ", i);
					print_liste(G->adjacent[i]);
				}

				else {
					printf(" %d : ", i);
					print_liste(G->adjacent[i]);
				}
			}

			printf("\n");
		}
	}
}

void destroy_graph(graphpond *PG)
{
	for (int i = 0; i < (*PG)->size; i++)
	{
		efface(&(*PG)->adjacent[i]);
	}

	free((*PG)->adjacent);
	free(*PG);
	*PG = NULL;
}

/* ---------------------------------------------------------------------------
  |                                                                           |
  |                        Algorithme de Dijkstra                             |
  |                                                                           |
   ---------------------------------------------------------------------------

Auteur : ENTEZAM Samuel
Date : 27/10/2017
*/

typedef struct prioqueue
{
	int* priorities; /* tableau des propriétés */
	int nbel; /* nombre d'éléments présents dans la file */
	int size; /* taille de la file */
} *prioqueue;

prioqueue make_prioqueue(int size)
{
	prioqueue q = (prioqueue) malloc(sizeof(prioqueue));
	q->priorities = (int*) malloc(size*sizeof(int));
	q->size = size;
	q->nbel = 0;
	for(int i = 0; i < q->size; i++) {
		q->priorities[i] = -1;
	}

	return q;
}

status enqueue(prioqueue q, int element, int priority)
{
	if(q->nbel == q->size)
		return ERROR;
	if(element < q->size && (element != -1 || element != NULL)) {
		q->priorities[element] = priority;
		q->nbel++;
	}

	return OK;
}

void update(prioqueue q, int element, int newpriority)
{
	if(newpriority < q->priorities[element])
		q->priorities[element] = newpriority;
}

boolean empty(prioqueue q)
{
	for(int i = 0; i < q->size; i++)
	{
		if(q->priorities[i] != -1)
			return FAUX;
	}

	return VRAI;
}

status extract_min(prioqueue q, int* elementMin)
{
	int k = 0;

	if(empty(q) == VRAI)
		return ERROR;

	while(q->priorities[k] == -1)
		k++;

	*elementMin = k;
	for(int i = 0; i < q->size; i++) {
		if(q->priorities[i] != -1 && q->priorities[i] < q->priorities[*elementMin])
			*elementMin = i;
	}

	update(q, *elementMin, -1);
	q->nbel--;

	return OK;
}

void dijkstra(graphpond G, int source, int poids[], int parent[], int recupMin[])
{
	/* Le tableau recupMin[] déclaré dans les paramètres de la fonction permet de récupérer le minimum à chaque appel
	 * de la fonction extract_min(), afin d'afficher le chemin le plus court dans le main().
	 * La variable cpt, elle, correspond aux index du tableau recupMin[], et s'incrémente à chaque fois qu'un élément y est mis, 
	 * pour pouvoir remplir le tableau.
	*/

	int cpt = 0;

	for(int i = 0; i < G->size; i++) {
		poids[i] = INFINITE;
		parent[i] = -1;
	}

	prioqueue Q = make_prioqueue(G->size);
	for(int i = 0; i < G->size; i++)
		enqueue(Q, i, poids[i]);
	update(Q, source, 0);

	int u;
	listepond liste;

	while(empty(Q) == FAUX) {
		extract_min(Q, &u);
		recupMin[cpt] = u;
		cpt++;
		poids[u] = 0;
		liste = G->adjacent[u];

		while(liste != NULL) {
			if(poids[liste->element] > poids[u] + liste->poids) {
				poids[liste->element] = poids[u] + liste->poids;
				parent[liste->element] = u;
				update(Q, liste->element, poids[liste->element]);
			}

			liste = liste->suivant;
		}
	}
}

void print_dijkstra(graphpond G, int recupMin[], int parent[])
{
	printf(" --------------------- Dijkstra --------------------- \n");
	for(int i = 0; i < G->size; i++)
	{
		if(parent[i] == -1)
			printf("\n Sommet %d avec comme parent %d (sommet source, donc pas de parent) \n", recupMin[i], parent[i]);
		else {
			printf("\n\t | \n");
			printf("\t v \n");
			printf("\n Sommet %d avec comme parent %d \n", recupMin[i], parent[i]);
		}
	}
}

void print_bellman(graphpond G, int parent[], int poids[])
{
	printf(" ------------------------ Chemin le plus court ------------------------ \n");
	for(int i = 0; i < G->size; i++) {
		if(parent[i] == -1) {
			printf("\n Sommet %d : \n", i);
			printf("\t [PARENT] --> %d \n", parent[i]);
			printf("\t [POIDS] --> %d \n", poids[i]);
		}

		else {
			printf("\n\t | \n");
			printf("\t v \n");
			printf("\n Sommet %d : \n", i);
			printf("\t [PARENT] --> %d \n", parent[i]);
			if(poids[i] == poids[i-1])
				printf("\t [POIDS] --> %d (poids non-actualisé car ce n'était pas le poids le plus petit !) \n", poids[i]);
			else
				printf("\t [POIDS] --> %d \n", poids[i]);
		}
	}
}

boolean bellman_ford(graphpond G, int source, int poids[], int parent[])
{
	int cpt = 0;

	for(int i = 0; i < G->size; i++) {
		poids[i] = INFINITE;
		parent[i] = -1;
	}

	poids[source] = 0;
	listepond liste;

	for(int i = 0; i < G->size; i++) {
		liste = G->adjacent[i];

		while(liste != NULL) {
			if(poids[liste->element] > poids[i] + liste->poids) {
				poids[liste->element] = poids[i] + liste->poids;
				parent[liste->element] = i;
				if(poids[liste->element] < 0) {
					return VRAI;
					break;
				}
			}

			liste = liste->suivant;
		}
	}

	return FAUX;
}

int main()
{
	graphpond G = NULL;
	G = makegraph(5, ORIENTED);
	if(G->type == ORIENTED)
		printf("\n ----------------------------- Déclaration d'un graphe orienté ----------------------------- \n");
	else
		printf("\n ----------------------------- Déclaration d'un graphe non-orienté ----------------------------- \n");
	add_arc(G, 0, 1, 10);
	add_arc(G, 0, 2, 5);
	add_arc(G, 1, 2, 2);
	add_arc(G, 1, 3, 1);
	add_arc(G, 2, 1, 3);
	add_arc(G, 2, 4, 2);
	add_arc(G, 2, 3, 9);
	add_arc(G, 3, 4, 4);
	add_arc(G, 4, 3, 6);
	add_arc(G, 4, 0, 7);

	print_graph(G);

	int *poids = (int*) malloc(G->size*sizeof(int));
	int *parent = (int*) malloc(G->size*sizeof(int));
	int *recupMin = (int*) malloc(G->size*sizeof(int));
	dijkstra(G, 0, poids, parent, recupMin);

	print_dijkstra(G, recupMin, parent);

	destroy_graph(&G);
	if((G) == NULL)
		printf("\n Le graphe est vide ! \n");

	graphpond G2 = NULL;
	G2 = makegraph(4, ORIENTED);
	if(G2->type == ORIENTED)
		printf("\n ----------------------------- Déclaration d'un graphe orienté ----------------------------- \n");
	else
		printf("\n ----------------------------- Déclaration d'un graphe non-orienté ----------------------------- \n");

	add_arc(G2, 0, 1, 6);
	add_arc(G2, 0, 2, 7);
	add_arc(G2, 1, 2, 8);
	add_arc(G2, 2, 3, 9);
	add_arc(G2, 3, 1, -20);

	print_graph(G2);
	printf(" --------------------- Bellman-Ford --------------------- \n");
	if(bellman_ford(G2, 0, poids, parent) == VRAI) {
		printf("Le graphe contient un circuit de poids négatif accessible depuis source de : \n");
		for(int i = 0; i < G2->size; i++) {
			if(poids[i] < 0)
				printf("%d \n", poids[i]);
		}
	}
	else {
		printf("Le graphe ne contient pas de circuit(s) de poids négatif(s) accessible(s) depuis source \n");
		print_bellman(G2, parent, poids);
	}

	return 0;
}