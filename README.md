# Projet CSC4526 DIETLIN Emmanuel - BLANC Ludovic


Ce projet à été réalisé par Emmanuel DIETLIN et Ludovic BLANC, étudiants de 2ème année à Télécom Sudparis.

Il a été réalisé en 15 jours, du 25/05/2022 au 9/06/2022, dans le cadre du module CSC4525 - Programmation C++.

Ce projet s'inspire de l'oeuvre de Jules Verne, "[Les révoltés de la Bounty]("https://fr.wikipedia.org/wiki/Les_R%C3%A9volt%C3%A9s_de_la_Bounty_(nouvelle)")".

#--------

## Outils

Le jeu est programmé en C++ via l'IDE **Visual Studio Community 2022**. 
Les fonds d'écran sont des cartes générées via l'outil [Tiled](https://www.mapeditor.org/), et implémentée en utilisant
la bibliothèque [timxlite](https://github.com/fallahn/tmxlite).
Le jeu utilise également la bibliothèque [vdk-signals](https://github.com/vdksoft/signals/blob/master/docs/signals.md).

#--------

## Principe de jeu

![ecran principal]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/main_menu_window.png")

L'objectif du jeu est de parcourir une distance de 6700km en 47 jours ou moins. Pour ce faire,
le joueur peut décider à chaque tour de jeu (un tour = un jour) quelles actions effectuer.
Il dispose pour cela d'un certains nombre de jetons d'action qu'il peut répartir comme il le souhaite.
Une fois les jetons répartis, le joueur peut passer au jour suivant.

![ecran de répartition des jetons]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window.png")

Au début de chaque journée, un compte-rendu des actions effectuées, des ressources récoltées et de la 
distance parcourue est affiché. Il y a également une chance que des évènements se déclenchent à la fin d'un tour
de jeu, ajoutant donc une partie d'aléatoire au jeu. Ces évènements peuvent être positifs ou négatifs.

![récapitulatif de la journée précédente]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

Le joueur gagne la partie s'il parvient à parcourir 6700km en au plus 47 jours.
Il perd si le bateau ou le joueur n'a plus de vie, ou bien s'il n'est pas parvenu à parcourir 
la distance requise dans le temps imparti.

![ecran de victoire]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

![écran de défaite]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

#--------

## Ressources

Toutes les ressources se trouvent dans le fichier *resources*

Daniel Eddeland - [Rowboat](https://opengameart.org/node/11117)
KnoblePersona - [Ocean background](https://opengameart.org/content/ocean-background)
Craftpix.net - [Character](https://craftpix.net/file-licenses/)
leeor_net - [Flare](https://opengameart.org/content/flare-effect)
sraye - [Beach](https://sraye.itch.io/distant-places-background-pack)
Sevarihk - [Raft sail](https://opengameart.org/content/animated-pixel-art-raft-sprite)
Craftpix.net - [Fish rod](https://opengameart.org/content/fishing-game-assets-pixel-art)
KokoroReflections - [Sail boat](https://opengameart.org/content/old-fashioned-pirate-ship)
Alucard - [Islands](https://opengameart.org/content/island-background-2d)
Nathanael Mortensen - [Island background](https://www.artstation.com/artwork/9el8DR)
Vecteezy.com - [Underwater background](https://www.vecteezy.com/vector-art/5205042-underwater-world-vector-illustration-with-yellow-fish-reefs-and-sunken-ship)
Clipart.com - [Island Background 2](http://clipart-library.com/clipart/8iEbRgorT.htm)
Free sound effect - [Wave sound](https://mixkit.co/free-sound-effects/sea/)
C418 - [Minecraft music](https://www.youtube.com/watch?v=XuZDeT8zI5c&ab_channel=C418-Topic)