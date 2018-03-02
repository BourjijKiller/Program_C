# ARBRES BINAIRES & TAS

-----------------------------

## DESCRIPTION
Ce programme introduit le fonctionnement des arbres binaires, et plus particulièrement de la génération d'un tas sous forme de tableau en fonction de l'arbre binaire représenté.
Un arbre binaire est un arbre dont chaque noeuds a au plus deux fils.
Par définition, un _**TAS**_ **est représenté par une file de priorité. C'est une file d'attente dont les éléments de sortie dépendent de la priorité et non pas de l'ordre d'entrée des éléments.**
Dans un tableau représenté par un TAS, on sait si, pour chaque élément, c'est un fils gauche ou un fils droit (La racine de l'arbre étant toujours l'indice 0 du tableau).
* Pour un fils gauche --> **2xi+1 (i étant l'indice de l'élément courant du tableau)**
* Pour un fils droit --> **2xi+2 (i étant l'indice de l'élément courant du tableau)**

-----------------------------
## EXEMPLE
Voici un arbre binaire respectant le principe du TAS (les éléments dont la priorité est la plus élevée sont les plus en haut de l'arbre).

![Arbre Binaire](https://upload.wikimedia.org/wikipedia/commons/thumb/c/c3/MaxHeapRemove0.svg/230px-MaxHeapRemove0.svg.png)

La représentation du TAS sous forme de tableau est la suivante (selon l'arbre ci-dessus) : 

	| Élément | Indice tableau |
	|:---:|:---:|
	| **53** | **0** |
	| **41** | **1** |
	| **30** | **2** |
	| **36** | **3** |
	| **28** | **4** |
	| **21** | **5** |
	| **6** | **6** |
	| **31** | **7** |
	| **16** | **8** |
	| **20** | **9** |

1. **Ajout d'un élément**
	* L'ajout d'un élément consiste tout d'abord à tester si l'élément sera un fils gauche ou un fils droit. Pour cela, on ajoute l'élément dans la première case vide du tableau, et on regarde si l'indice de cet élément est pair ou impair. Si l'indice est pair, alors l'élément sera un fils droit, et al contrario, l'élément sera un fils gauche.
	Ensuite, il faut comparer la valeur de priorité de l'élément avec la valeur de priorité de son père. Si celle-ci est inférieur, alors on ne fait rien. Cependant, si la valeur de priorité de l'élément est supérieur à la valeur de priorité du père de l'élément, on permute la place des deux éléments. Et on répète cette opération tant que la valeur de priorité de l'élément est supérieur à la valeur de priorité du père de l'élément.

2. **Suppression d'un élément**
	* La suppression d'un élément consiste donc à supprimer l'élément dont la valeur de priorité est la plus élevé, donc la racine de l'arbre, soit l'indice 0 de notre tableau représentant le TAS. Cependant, après cette suppression, il faut donc regénérer correctement le TAS. La méthode est la suivante :
		* Placement du dernier élément du tableau à l'indice 0 (on remonte le dernier élément à la racine)
		* On compare la valeur de priorité de cet élément à la valeur de priorité la plus élevé entre les deux fils de l'élément. Si la valeur de priorité du fils sélectionné est plus élevé que la valeur de priorité de l'élément, alors on permute les deux éléments. On repète l'opération tant que _**valeur de priorité de l'élément < MAX(fils).Valeur de priorité**_

-----------------------------

## OPÉRATIONS POSSIBLES POUR L'UTILISATEUR

![Choix de l'utilisateur](https://image.noelshack.com/fichiers/2017/47/7/1511725259-24167427-1915246248792168-1473021681-o.png)

-----------------------------

## UTILISATION
1. Compilateur `gcc`
2. `IDE` supportant le langage C