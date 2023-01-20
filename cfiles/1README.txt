README:

SDL2, SDL2_image and SDL2_ttf are all required to compile this game successfully. 

Images are stored in a seperate directory to these c files, make sure it's in the same relative position as it would be normally if you wish to be moving files about

The makefile provides the recipe for the main game (./game) as well as the two prototypes mentioned in the report. 

Controls:
The player is allowed to control both teams, for the purpose of demonstration
Red is team 1, blue is team 2.
Resources (required to build units) are displayed in the top left corner
Arrow keys scroll the camera across the map
Left click on a unit or building to select it

Controls for buildings:
(when selected)
Q - Build a warrior
W - Build a scout
E - Build an archer
R - Build the test unit (no resource cost, high damage, high health, low attack speed)

Controls for units: 
(when selected)
Right click on terrain - move to location
Right click on enemy unit/building - attack

The objective would usually be to destroy all the enemy team's buildings, but as this is a proof of concept more than a game, there's no win condition. 


