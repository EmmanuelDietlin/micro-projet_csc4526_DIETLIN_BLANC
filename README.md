# Projet CSC4526 DIETLIN Emmanuel - BLANC Ludovic


Ce projet � �t� r�alis� par Emmanuel DIETLIN et Ludovic BLANC, �tudiants de 2�me ann�e � T�l�com Sudparis.

Il a �t� r�alis� en 15 jours, du 25/05/2022 au 9/06/2022, dans le cadre du module CSC4525 - Programmation C++.

Ce projet s'inspire de l'oeuvre de Jules Verne, "[Les r�volt�s de la Bounty]("https://fr.wikipedia.org/wiki/Les_R%C3%A9volt%C3%A9s_de_la_Bounty_(nouvelle)")".

#--------

## Outils

Le jeu est programm� en C++ via l'IDE **Visual Studio Community 2022**. 
Les fonds d'�cran sont des cartes g�n�r�es via l'outil [Tiled](https://www.mapeditor.org/), et impl�ment�e en utilisant
la biblioth�que [timxlite](https://github.com/fallahn/tmxlite).
Le jeu utilise �galement la biblioth�que [vdk-signals](https://github.com/vdksoft/signals/blob/master/docs/signals.md).

#--------

## Principe de jeu

![ecran principal]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/main_menu_window.png")

L'objectif du jeu est de parcourir une distance de 6700km en 47 jours ou moins. Pour ce faire,
le joueur peut d�cider � chaque tour de jeu (un tour = un jour) quelles actions effectuer.
Il dispose pour cela d'un certains nombre de jetons d'action qu'il peut r�partir comme il le souhaite.
Une fois les jetons r�partis, le joueur peut passer au jour suivant.

![ecran de r�partition des jetons]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window.png")

Au d�but de chaque journ�e, un compte-rendu des actions effectu�es, des ressources r�colt�es et de la 
distance parcourue est affich�. Il y a �galement une chance que des �v�nements se d�clenchent � la fin d'un tour
de jeu, ajoutant donc une partie d'al�atoire au jeu. Ces �v�nements peuvent �tre positifs ou n�gatifs.

![r�capitulatif de la journ�e pr�c�dente]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

Le joueur gagne la partie s'il parvient � parcourir 6700km en au plus 47 jours.
Il perd si le bateau ou le joueur n'a plus de vie, ou bien s'il n'est pas parvenu � parcourir 
la distance requise dans le temps imparti.

![ecran de victoire]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

![�cran de d�faite]("https://github.com/EmmanuelDietlin/micro-projet_csc4526_DIETLIN_BLANC/tree/main/resources/screenshots/game_window_2.png")

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