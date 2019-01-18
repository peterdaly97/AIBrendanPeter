SPLIT: 

50/50

PLAYER/GAME WORLD:

Press H to cheat and give more health for testing.

Camera focused on player.
Player rotates with left and right arrow.
Up arrow increases velocity in desired location and creates thruster flames.
Down arrow slows.
Space shoots.
Q use bomb power up when collected.
Health displayed at top left.

Game world made up of 50x50 grid of nodes.
Nodes can be obstacles or empty.

WORKERS:

Spawned randomly at empty nodes.
Wander randomly.
Can be collected by player.
Collected by sweepers.
Can swap to pathfinding if magnet collected.

NESTS:

3 spawned at spots chosen from a collection.
Nests spawn sweepers and predators.
Nests shoot missiles at player if they are withing distance.

SWEEPER BOTS:

Wander randomly in search of workers.
Use cone of vision to see if workers are within distance.
Will seek the workers and collect them.
Will transfer the collected workers to player when destroyed.
Will flee from the player if they are within scary distance.

PREDATORS:

Use flow field pathfinding.
Flow field updated when player changes grid tile and after a set delay.
When they are within a set distance of the player they will begin to fire.
They will also try to surround the player.
Will work out how many predators are close to the player and split a circle into spots.
Will position themselves in their spots.
Will reform when one is destroyed or too far away.
15 predators will be spawned by the nests.

COLLISION DETECTION:

Everything uses the grid layout to determine where the walls are.
Everything converts their position to a grid spot.
Will not be able to move through any obstacles in the grid.
Bullets collide with all enemies and player depending on who fired them.
Bullets also collide with walls.

POWER UPS:

Health power up increases the players health by a set amount.
Bomb power up allows the player to shoot in all directions(PRESS Q AFTER PICK UP).
Magnet power up causes the workers to pathfind to the player for a set amount of time.

Radar:

Radar drawn on bottom right of screen.
Blue dots drawn for power ups.
Red dots for predators.
Purple dots for nests.
Pink dots for sweepers.
Yellow dots for workers.
Green dot for player.

DOXYGEN:

Included with project in Doxygen folder.
All code commented. :)

CODE QUALITY:

I'd say pretty good. :)

ENJOYABILITY:

Leave this up to you I guess. :)

EXTRA:

Particle effects for killing enemies, nests and missiles exploding.
Animated fire thrust for player.