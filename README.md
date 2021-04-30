# PROJET FMSI

### Introduction

L'algorithme rho de Pollard a été introduit par John M. Pollard en 1978 
pour résoudre le problème du logarithme discret. Il est analogue à l'algorithme 
rho de Pollard que le même auteur avait introduit pour résoudre le problème 
factorisation entière. 

L'algorithme permet de résoudre le problème du logarithme discret.
En effet, le calcul des logarithmes discrets s'avère difficile,
tandis que le problème inverse, l'exponentiation discrète,
ne l'est pas (grâce à l'algorithme d'exponentiation rapide).  
Cette asymétrie est exploitée en cryptologie, pour la cryptographie à clé publique.


### Principe Mathémathique pour l'algorithme rho de Pollard
Pour calculer le logarithme d’un élément h, l’algorithme rho repose sur la recherche de collisions <sup>[1](#collision)</sup>  dans les termes d’une séquence obtenue en appliquant une fonction pseudo-aléatoire f de G dans G sur des éléments de la forme 

```math
 x_{i} = g^{a_{i}}h^{b_{i}}
```

Comme G est fini et que f est déterministe, la séquence obtenue contient un cycle. On s’attend à ce que la taille du cycle soit en O(√n). La recherche de collision  est effectuée selon l’algorithme de Floyd pour la détection de cycle. Quand une collision est trouvée, nous avons une égalité de la forme 
```math
g^{a_{1}}h^{b_{1}} = g^{a_{2}}h^{b_{2}}
```
, pour des entiers connus a1,b1, a2 et b2. Cette égalité nous donne l’équation suivante :
```math
(b2−b1)k ≡ (a1−a2)    (mod n)
```
Si cette équation admet une solution (c’est-à-dire si pgcd(b2−b1,n) = 1), alors k correspond au logarithme discret de h. Sinon, nous recommençons le calcul avec de nouvelles valeurs initiales pour les variables a0 et b0.

![Rho de Pollard](https://i.imgur.com/QRMIU8d.png "rho de pollard")

L’algorithme rho de Pollard est probabiliste avec une complexité temps de O(√n)et une complexité mémoire de O(log n). C’est à ce jour l’algorithme générique le plus efficace en terme de temps et d’espace. Il existe un algorithme déterministe cousin de l’algorithme rho, souvent appelé l’algorithme lambda de Pollard, qui n’a pas une meilleure complexité, mais qui se parallélise mieux et qui est utile lorsque le logarithme recherché se trouve dans un intervalle limité. 

### Algorithme
Soit G un groupe cyclique d'ordre n,
Soient α, β ∈ G,
Soit une partition G = S0 ∪ S1 ∪ S2
Soit une fonction f : G → G définie par 
![fonction f](https://wikimedia.org/api/rest_v1/media/math/render/svg/5881bb42a6a01a1bdae916610e184b05ef8cd5d1)

et soient enfin les deux fonctions g : G × Z → Z et h : G × Z → Z définies par 
![fonction g et h](https://wikimedia.org/api/rest_v1/media/math/render/svg/6e3dbfe68064258082da3c282b5e071c1fa86ff2)

On a donc le pseudo code suivant:\
![Algo](https://i.imgur.com/MRASMUJ.png "efdef")

### Sources
[Lien](https://fr.wikipedia.org/wiki/Algorithme_rho_de_Pollard_(logarithme_discret))
[These](http://docnum.univ-lorraine.fr/public/DDOC_T_2015_0065_JELJELI.pdf)


### Note
<a name="collision">1</a> : La résistance aux collisions est une propriété des fonctions de hachage cryptographiques : une fonction de hachage cryptographique H est résistante aux collisions s’il est difficile de trouver deux entrées qui donnent la même valeur de hachage ; c’est-à-dire deux entrées A et B de telles que : H ( A ) = H ( B ) et A ≠ B. 

# Authors
    OLIVAUX Aymeric
    LE BRAS Tom
    GHALI Cyril
    DESCOUTS Maxime
