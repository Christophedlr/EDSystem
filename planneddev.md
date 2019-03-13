# Évolutions prévues

## 1.1.0

1. Ajout de filtres sur les trajets
2. Ajout du calcul du bénéfice total de tout ce qui est listé dans les trajets (filtrés ou non)
3. Ajout de tri sur les trajets
..* Systèmes
..* Catégorie de produits
..* Date
..* Quantité
..* Bénéfice
4. Ajout du filtre sur la catégorie de produits dans la liste des produits

## 2.0.0

Cette version n'est pas certaine à l'heure actuelle car des tests sont à réalisés.

1. Intégration de PHP avec le logiciel afin de gérer l'accès aux données (lecture/écriture) d'une façon plus pratique à maintenir
2. Recodage total du logiciel prenant en compte l'interaction avec PHP
3. Amélioration du visuel de chaque fenêtres

Concernant l'intégration de PHP, il s'agîrait d'avoir PHP fournis avec le logiciel.
Lors du démarrage, le serveur interne de PHP serait démarré (port réglable alors dans la configuration initiale du logiciel).
Le logiciel se contenterait alors d'appeler une URL, PHP renvoyant alors simplement des données brutes.
Le système n'aurait alors que le travail d'affichage, lire et écrire dans la base serait géré entièrement par PHP.

Le principe, est de permettre de séparer totalement le visuel (le logiciel) du reste (le traitement), tout en ayant
un moyen simple et rapide de le faire (PHP) tout en étant puissant (différents outils fournis via Composer).


Il est nécessaire bien rappeler que ce n'est qu'une estimation des évolutions prévues, des tests sont à réalisés
afin de vérifier la viabilité de l'usage de PHP en serveur interne et donc fournis avec le logiciel.
