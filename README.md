# Installation

Dézippé le fichier, pas besoin d'installation.

# Configuration

Lors du premier lancement du logiciel, ce dernier vous demandera quelques informations : hôte MySQL, Utilisateur et mot de passe MySQL, Base de donnée MySQL et le port MySQL(par défaut 3306).

Une fois ces informations remplies, le système va alors créer les tables et la configuration. Lors des prochains lancement, vous n'aurez pas besoin de remettre ces informations. Si vous souhaitez réinstaller la base de donnée (toutes les données sont alors perdue), vous avez un bouton **Configuraiton initiale** qui permet de retrouver cet écran de configuration.

# Utilisation

## Découpage du fonctionnement

Le logiciel permet d'enregistrer les trajets effectués avec les bénéfices survenus, ainsi vous avez trois parties : les systèmes & stations du jeu, les produits (et catégories de ces derniers) et enfin les trajets.

## Systèmes & stations

Ces deux boutons permettent respectivement d'enregistrer une liste de systèmes et une liste de stations (rattachées aux systèmes préalablement enregistrés).

## Catégories & produits

Ces deux boutons permettent d'enregistrer une liste de catégorie de produits et les produits qui vont avec.

## Trajets

Ce bouton, vous permet d'enregistrer votre trajet entre deux stations, d'y noter la soute vendue (produit et quantité) et les bénéfices obtenus, ainsi que la date.
Si à une même station vous vendez plusieurs marchandises différentes, il est alors nécessaire d'enregistrer plusieurs fois le dit trajet afin de pouvoir choisir un autre produit dans la liste et y noter le bénéfice de ce produit en question.


# Rappel

Le logiciel est complètement externe à Elite Dangerous et requiert une base de donnée MySQL ou MariaDB, ce dernier doit donc être installé sur la machine ou votre machine doit pouvoir accéder à distance à la base de données (attention avec les hébergements, tous ne permettent pas un accès externe à la base de données en dehors du site internet).
