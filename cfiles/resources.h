/*resources.c is a very simple file that provides a few
resource functions so that one can add, remove and track
the amount of resources a team has. The code that utilises these
functiosn is currently entirely in buildings.c*/

//returns the number of resources the given team has
int getResources(int team);

//adds the specified number of resources
void addResources(int team, int resources);

//returns 0 if the player has enough resources to be removed,
//1 otherwise. If a player needs to go to a negative amount, useeaddResources
//with a negative amount instead
int removeResources(int team, int resources);
