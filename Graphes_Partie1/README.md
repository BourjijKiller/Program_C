# GRAPHES
-----------------

## DESCRIPTION
Programme en C pour manier les graphes

-----------------

## OPÉRATIONS POSSIBLES
* `graphL makegraph(int size, graph_type type)`
	* Crée un graphe avec `size` sommets et de type `graph_type`
* `add_arc(graphL G, int source, int dest)`
	* La fonction ajoute au graphe `G` un arc de `source` à `dest` (ajoute l'arc inverse si le graphe est non-orienté)
* `print_graph(graphL G)`
	* Pour chaque sommet `s`, la fonction imprime `s` et sa liste d'adjacence
* `destroy_graph(graphL *G)`
	* La fonction détruit `G` (en de-allouant la mémoire avec la fonction `free`)

-----------------

## PARCOURS DE GRAPHES

### BFT

* `void BFT(graphL G, int source, int parent[], int distance[], graph_color couleur[])`
	* La fonction effectue un parcours en largeur([Breadth-First Traversal](https://fr.wikipedia.org/wiki/Algorithme_de_parcours_en_largeur)) d’un graphe G à partir d’un sommet source. La fonction détermine pour chaque sommet u **le parent** de u dans l’arbre construit pendant le parcours et sa **distance minimale** depuis source. Les autres paramètres (un ou plusieurs) enregistrent les informations calculées par l'algorithme, c'est à dire **la couleur**, **le parent** et **la distance** d’un sommet depuis le sommet source

### DFT

* `boolean recherche_circuit(graphL G)`
	* Retourne TRUE si `G` contient un circuit, FALSE sinon. Pour vérifier qu'un graphe contient un circuit, il faut effectuer un parcours en profondeur du graphe et vérifier s'il possède au moins 1 arc arrière (arc pointant sur un sommet adjacent GRIS)

		* `void dft_recherche_circ (graphL G, int source, int* color, boolean *CIRCUIT)`
			* Cette fonction auxiliaire récursive effectue un parcours en profondeur ([Depth-First Traversal](https://fr.wikipedia.org/wiki/Algorithme_de_parcours_en_profondeur)) de **G** à partir du sommet **source** en utilisant un tableau **color**, la fonction peut modifier la variable booléenne **CIRCUIT**

* `list topsort(graphL G) `
	* Retourne une liste des sommets de G triés en ordre topologique ([Tri topologique](https://fr.wikipedia.org/wiki/Tri_topologique)) d'un **graphe orienté sans circuits (DAG)**

		* `void dft_top_sortDAG(graphL G, int source, int* color, list* sorted)`
			* Cette fonction auxiliaire récursive effectue un parcours en profondeur de **G** à partir du sommet **source**, utilise un tableau **color** et construit la liste **sorted** des sommets triés

-----------------
## UTILISATION
1. Compilateur `gcc`
2. `IDE` supportant le langage C

-----------------
## DÉPENDANCE
Ce programme utilise les listes et les files