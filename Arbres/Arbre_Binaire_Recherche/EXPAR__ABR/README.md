# ARBRES BINAIRES DE RECHERCHE

-----------------------------

## DESCRIPTION
Ce programme permet de transformer une expression arithmétique en un **arbre binaire de recherche**.
Lors du lancement du programme, il vous sera demandé de saisir une expression arithmétique (Exemple : 1+2+3). Si la saisie utilisateur n'est pas une expression arithmétique valide, le programme génèrera un message d'erreur et l'arrêt immédiat de celui-ci.

Pour plus d'information sur le concept de transformation d'une expression arithmétique en ABR, cliquez [ici](https://www.developpez.net/forums/d1168100/general-developpement/algorithme-mathematiques/general-algorithmique/transformer-expression-arithmetique-bien-parenthesee-arbre-binaire/)

-----------------------------

## OPÉRATIONS POSSIBLES
* `Arbre nouvelArbre(char contenu, Arbre filsGauche, Arbre filsDroit)`
	* Cette fonction permet de créer un nouvelle arbre contenant une information _**contenu**_ ainsi qu'un sous arbre _**filsGauche**_ et _**filsDroit**_
* `void print_Arbre(Arbre arbre, int tab)`
	* Cette fonction permet d'afficher l'arbre binaire de recherche _**arbre**_ avec une ou plusieurs tabulations _**tab**_ pour le style d'affichage
* `void GaucheNoeudDroite(Arbre arbre)`
	* Cette fonction affiche l'arbre binaire de recherche _**arbre**_ dans l'ordre FilsGauche puis FilsDroit, en descendant successivement dans l'arbre
* `void DroiteNoeudGauche(Arbre arbre)`
	* Cette fonction affiche l'arbre binaire de recherche _**arbre**_ dans l'ordre FilsDroit puis FilsF+Gauche, en descendant successivement dans l'arbre

-----------------------------

## VERSIONS
* **[V 1.0] 04/11/2017**
	1. Fonctionnel pour de simples expressions arithmétiques (sans parenthèses)
* **[V FINAL] 12/11/2017**
	1. Corrections des bugs du regex, permettant de contrôler la saisie utilisateur
	2. Ne tient pas compte des priorités des signes (+-x/)

-----------------------------

## UTILISATION
1. Compilateur `gcc`
2. `IDE` supportant le langage C