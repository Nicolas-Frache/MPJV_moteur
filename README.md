# GROUPE 8 : Construction d’un moteur physique de jeux vidéo - Automne 2023 


## Compilation et Exécution

1. Déplacer le repertoire MPJV_moteur dans le dossier MyApps de openFramework. Par exemple ``C:\Users\USER\Documents\of_v0.12.0_vs_release\apps\myApps``.

2. Ouvrir le fichier MPJV_moteur.sln dans Visual Studio.

3. Appuyer sur la flèche verte pour compiler et lancer le programme.


## Contrôles du Jeu

- Déplacements :
  - Qwerty: WASD.
  - Azerty: ZQSD.
  - Clic droit enfoncé pour tourner la caméra.

## Projets et leurs Propriétés

Vous pouvez lancer trois types de projectiles différents, chacun ayant ses propres propriétés uniques :

1. **Balle** :
   - Projectile rapide avec une portée moyenne.
   - Ne perds pas de l'altitude lorsqu'il rebondit
   - Touche de lancement : `SHIFT + 1`

2. **Boule de Feu** :
   - Projectile avec des particules qui le suivent
   - Touche de lancement : `SHIFT + 2`

3. **Laser** :
   - Projectile laser qui part en ligne droite sans être affecté par la gravité.
   - Touche de lancement : `SHIFT + 3`

4. **Corps Rigide** :
   - Corps rigide avec une forme et une rotation initiale aléatoire.
   - Touche de lancement : `SHIFT + 4`

5. **Jeu de tir** :
	- Dans ce mode le joueur doit viser des cibles mouvante et tirer avec clic gauche pour engendrer des points.

## Le blob

Le blob est un regroupement de particules qui sont liées par plusieurs forces, la particularité du blob c'est qu'il est capable de se diviser en plusieur petit blob et de se regrouper pour former un seul et grand blob

- Déplacements :
   - Flèche directionnel 

- Sauter :
   - espace

- Diviser le blob :
   - Entrée