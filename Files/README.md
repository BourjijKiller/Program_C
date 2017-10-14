# FILES
-----------------

## DESCRIPTION
Programme en C pour manier les files

-----------------
## OPÉRATIONS POSSIBLES
* `MA_FILE make_file()`
	* La fonction retourne une file allouée dynamiquement, avec les champs deb et fin initialisés à NULL.
* `booleen vide(MA_FILE f)`
	* La fonction retourne VRAI si la file ne contient aucun élément et FAUX si non. 
* `status tete_file(MA_FILE f, int*element)`
	* Si la file est vide la fonction retourne la valeur ERROR, sinon la fonction retourne l’élément (entier) en tête dans la variable élément passée par référence et la valeur OK.
* `status enfile(MA_FILE f, int n)`
	* La fonction ajoute un élément à la fin de la file, elle retourne OK.
* `status defile(MA_FILE f)`
	* Si la file est vide la fonction retourne la valeur ERROR, sinon elle supprime l’élément au début de la file et retourne OK.

-----------------
## Utilisation
Compilateur `gcc`

-----------------
## Dépendance
Ce programme utilise les listes