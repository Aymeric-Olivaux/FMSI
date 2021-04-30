# PROJET FMSI


Nous avons décidé de nous travailler l'algorithme rho de Pollard, introduit par John M. Pollard en 1978 pour résoudre le problème du logarithme discret. Il est analogue à l'algorithme rho de Pollard que le même auteur avait introduit pour résoudre le problème factorisation entière.
Pour autant, cette algorithme introduit des notions de cryptographie que nous détaillons ici meme(logarithme discret, problème de Diffie et Hellman, etc). Nous reviendrons sur son implementation et sur son problème juste apres cette introduction.

### Introduction 
#### Problème d'échange de clés

La clé est un outil central en cryptographie pour pouvoir mettre en place un protocole qui protège la communication entre deux parties. Dans le cadre de la cryptographie symétrique, les deux parties, que l’on appelle habituellement Alice et Bob, sont amenées à établir une clé secrète commune. On appelle ce problème le problème de l’échange de clé.

Diffie et Hellman ont proposé en 1976 une solution qui répond au problème de la création d’une clé commune. De nos jours, le protocole d’échange de clés Diffie-Hellman est intégrédans différents navigateurs web et fait partie de plusieurs protocoles de sécurisation des échanges sur Internet tels que TLS (Transport Layer Security).

Le schéma de la figure ci dessous détaille le protocole qui permet à Alice et Bob de créer communément une clé. Une des deux parties, ici Alice, commence par choisir un groupe cyclique G de cardinal n, noté multiplicativement et engendré par g. Nous utilisons la notation G =〈g〉pour préciser que G est engendré par g. Alice choisit un entier kA ∈ [0, n−1], calcule g^(kA) et l’envoie à Bob. Idem, Bob choisit un entier kB ∈ [0,n−1], calcule g^(kB) et l’envoie à Alice. À la fin de l’échange, les deux parties peuvent alors construire la même clé 
```math
K = (g^{kA})^{kB}= (g^{kB})^{kA}.
```
![Alice et Bob : échange de clé de Diffie et Helman](https://i.imgur.com/APJBL6P.png)

Un attaquant, qui écoute sur le canal, voit passer G, g, n, gkA et gkB. Il espère pouvoir deviner K à partir de ces observations. On appelle ce problème le problème Diffie-Hellman. Pour être en mesure de calculer K, l’attaquant pourrait espérer pouvoir calculer kA ou kB à partir de gkA et gkB, respectivement. Ce calcul correspond à une résolution du problème du logarithme discret.

##### Problème du logarithme discret
Le problème de l'échange de clés fait appel à deux opérations: 
- L'exponentiation discrète.<sup>[1](#expo)</sup>
- Le logarithme discret<sup>[2](#loga)</sup>. Il est la reciproque de l'exponentiation. 
Le problème du logarithme discret consiste à calculer k = log_g(h) à partir de h et g

L’asymétrie entre l’exponentiation et le logarithme discret est utilisée en cryptographie à clé publique pour construire des fonctions à trappe, c’est-à-dire, des fonctions qui peuvent être aisément calculées lorsque la trappe est connue et dures à inverser sans connaissance de la trappe.Dans l’exemple de l’échange de clés Diffie-Hellman, que nous avons précédemment évoqué, la sécurité du protocole repose sur la difficulté pour une troisième partie de pouvoir calculer des logarithmes discrets à partir des données échangées

### Principe Mathémathique pour l'algorithme rho de Pollard
Pour calculer le logarithme d’un élément h, l’algorithme rho repose sur la recherche de collisions <sup>[3](#collision)</sup>  dans les termes d’une séquence obtenue en appliquant une fonction pseudo-aléatoire f de G dans G sur des éléments de la forme 

```math
 x_{i} = g^{a_{i}}h^{b_{i}}
```

Comme G est fini et que f est déterministe <sup>[4](#deterministe)</sup>, la séquence obtenue contient un cycle. On s’attend à ce que la taille du cycle soit en O(√n). La recherche de collision  est effectuée selon l’algorithme de Floyd pour la détection de cycle. Quand une collision est trouvée, nous avons une égalité de la forme 
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
<a name="expo">1</a> Étant donnés le groupe G, un entier k dans [0, n−1] et un élément g∈G, élever g à la puissance k consiste à calculer g^k
<a name="loga">2</a> Étant donnés un groupe G cyclique engendré parget un élément h dans le groupe, le logarithme discret de h, en base g,qu’on note log_g(h), est l’unique entier k dans [0,n−1] tel que h = g^k
<a name="collision">3</a> : La résistance aux collisions est une propriété des fonctions de hachage cryptographiques : une fonction de hachage cryptographique H est résistante aux collisions s’il est difficile de trouver deux entrées qui donnent la même valeur de hachage ; c’est-à-dire deux entrées A et B de telles que : H ( A ) = H ( B ) et A ≠ B. 

<a name="deterministe">4</a> Une fonction déterministe est une fonction qui pour le même argument renverra toujours le même résultat

# Authors
    OLIVAUX Aymeric
    LE BRAS Tom
    GHALI Cyril
    DESCOUTS Maxime
