# SCHOKOBAN - USER MANUAL

## Table of contents
<!-- @import "[TOC]" {cmd="toc" depthFrom=2 depthTo=3 orderedList=false} -->

<!-- code_chunk_output -->

- [About Sokoban](#about-sokoban)
  - [Objective and rules](#objective-and-rules)
  - [Scoring](#scoring)
- [Game behavior](#game-behavior)
  - [Appearance](#appearance)
  - [Starting the game](#starting-the-game)
  - [Loading a saved game](#loading-a-saved-game)
  - [The end of the game](#the-end-of-the-game)
  - [Controls](#controls)

<!-- /code_chunk_output -->


## About Sokoban
Sokoban (倉庫番, Sōko-ban) is a single-player puzzle game where the player pushes
boxes around in a warehouse.

### Objective and rules
The objective is to push all boxes onto storage location(s), also
called goals. The player can push a box in any direction as long as it is not
obstructed by another box or a wall. The player may undo their moves an
unlimited number of times. (using undo repeatedly "rolls back time")

The location of the boxes and the storage locations are set by the map's author
and are always in the same location on a map. The game consists of multiple
levels with varying difficulty determined by the number of boxes and the
complexity of the solution to the puzzle.

### Scoring
The player's score is the number of moves they made to complete the map:
- Any successful directional move, including box pushes, count as one
- Undos also count as moves
- Map resets also reset the move counter

A lower score (fewer amount of moves) is better. 

## Game behavior

### Appearance
The game is playable through a console/terminal window with colorful Unicode
characters representing each of the six possible states on any given playing
field:

- `█` (`U+2588` "Full Block") for the walls
- `⨯` (`U+2A2F` "Cross Product") colored *red* for the goals
- `◼` (`U+25FC` "Black Medium Square") for the boxes
  - colored *yellow* for boxes not on goals
  - colored *green* for boxes on goals
- `☻` (`U+263B` "Black Smiling Face") for the player character/figure
  - colored *red* if standing on a goal

![UI Example](spec_ui.png)

### Starting the game
When opening the game, the player can choose what mode they want to play in:
- **Arcade mode:** The levels are played in a set order, one after another.
- **Free play:** Choose one specific level from arcade mode to play.
- **Custom maps:** Input a path to any XSB map file.

### Loading a saved game
If a saved state can be found for the selected level in free play or cutom mode, 
you can choose to load or delete the saved state.

### The end of the game
If the player's score surpasses or matches any of those in the current
leaderboard, the player can choose whether or not they want to appear on the
leaderboard. If they want to appear, they are asked to input a nickname;
the new list is saved and displayed.

The leaderboard may only contain a maximum of 10 entries and is 'first come,
first served' when there is a tie.

### Controls
- **Directional input:** `WASD` or arrow keys
  - Game controls
  - Menu navigation
- **Accept:** `Enter` or `Space`
  - Confirm choices in the menu
- **Menu exit:** `Escape` or `Backspace`
  - Exiting from the game (show leaderboard and exit menu): `Escape`
- **Map reset:** `R`
- **Move undo:** `U`
