# GRAPHES
-----------------

## DESCRIPTION
Programme en C pour manier les graphes pondérés --> Ajout d'un nouveau champ additionnel pour stocker le poid d'un arc
_**Implémentation d'un nouveau type de liste et de graphes, en rajoutant le poid dans le type liste**_

-----------------

## RÉ-IMPLÉMENTATION DES FONCTIONS

### LISTES
* `void insert_tete(listepond* PL , int el, int poids)`
	* La fonction insert un élément `el` avec son poids associé `poids` dans la liste `PL`
* `void print(listepond L )`
	* La fonction affiche la liste `L` à l'écran
* `void efface(listepond *PL)`
	* La fonction supprime la liste et libère la mémoire avec la fonction `free()`


### GRAPHES
* `status add_arc(graphpond G, int source, int dest, int poids)`
	* La fonction ajoute au graphe pondéré `G` un arc de `source` à `dest` (ajoute l'arc inverse si le graphe est non-orienté)
* `void print_graph(graphpond G)`
	* Pour chaque sommet `s`, la fonction imprime `s` et sa liste d'adjacence
* `graphpond makegraph(int size, graph_type type)`
	* Crée un graphe pondéré avec `size` sommets et de type `graph_type`
* `void destroy_graph(graphpond * PG)`
	* La fonction détruit `PG` (en de-allouant la mémoire avec la fonction `free`)

-----------------

## NOUVEAUX TYPES / NOUVELLES FONCTIONS

### TYPES
Implémentation de la structure **file de priorité**
Pour cette application, on peut faire les hypothèses suivantes:
1. La file contient des éléments identifiés par un entier non-négatif
2. Les éléments sont connus a-priori : ils sont numérotés depuis 0 jusqu'au un entier maximum
3. Chaque élément présent dans la file a une valeur de priorité, qui est un entier non-négatif

Une file de priorité peut donc être implémentée simplement comme un tableau. Les indices sont les éléments et la valeur stockée dans chaque location **i** est la priorité de l'élément **i**. Une valeur négatif (par exemple -1) d'un élément **i** indique que l'élément **i** ne fait pas (ou ne fait plus) partie de la file.

### FONCTIONS
* `prioqueue make_prioqueue(int size)`
	* La fonction créé une file de priorité qui peut contenir jusqu'à `size` élément(s)
* `status enqueue(prioqueue q, int element, int priority)`
	* La fonction insert un nouveau élément `element` avec une priorité `priority`
* `void update(prioqueue q, int element, int newpriority)`
	* La fonction met à jour la priorité de `element` à `newpriority` si celle-ci est _strictement inférieure_ à la priorité actuelle
* `boolean empty(prioqueue q)`
	* La fonction test si la file de priorité `q` est vide (si toute les priorités des éléments sont égales à **-1**)
* `status extract_min(prioqueue q, int* elementmin)`
	* Si la file de priorité `q` n'est pas vide, la fonction « enlève » et retourne dans `elementmin` un élément de priorité minimale

-----------------

## PARCOURS DE GRAPHES

### ALGORITHME DE **_DIJKSTRA_**
* `void dijkstra(graphpond G, int source, int poids[], int parent[])`
	* La fonction implémente [l'algorithme de Dijkstra](https://fr.wikipedia.org/wiki/Algorithme_de_Dijkstra) permettant de donner le plus court chemin d'un graphe pondéré. Elle calcule _le poids d'un plus court chemin_ depuis un sommet **source** à chaque sommet et le **parent** de chaque sommet dans ce chemin. Ces informations sont stockées dans des paramètres passés à la fonction.

### ALGORITHME DE **_BELLMAN-FORD_**
* `boolean bellman_ford(graphpond G, int source, int poids[], int parent[])`
	* La fonction implémente [l'algorithme de Bellman-Ford](https://fr.wikipedia.org/wiki/Algorithme_de_Bellman-Ford) qui est un algorithme similaire de recherche du plus court chemin, mais qui peut s'appliquer sur un graphe contenant des arcs de poids négatifs, contrairement à **Dijkstra**.
	La fonction retourne `TRUE` si le graphe contient un circuit de poids négatif accessible depuis `source` et `FALSE` sinon. Si le graphe ne contient pas de circuits de poids négatif accessibles depuis `source`, la fonction calcule le poids _d'un plus court chemin_ depuis `source` à chaque sommet et le `parent` de chaque sommet dans ce chemin. Ces informations sont stockées dans des paramètres passés à la fonction.

-----------------
## UTILISATION
1. Compilateur `gcc`
2. `IDE` supportant le langage C