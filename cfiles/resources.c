int teamOneResources = 0;
int teamTwoResources = 0;

//returns the amount of resources the given team has
int getResources(int team) {
    switch(team) {
        case 0:
            return teamOneResources;
        case 1:
            return teamTwoResources;
        default:
            return 0;
    }
}

//adds the specified amount of resources to the given team
void addResources(int team, int resources) {
    switch(team) {
        case 0:
            teamOneResources += resources;
            break;
        case 1:
            teamTwoResources += resources;
            break;
    }
}

//returns 0 if the player has enough resources to be removed,
//1 otherwise. If a player needs to go to a negative amount, use addResources
//with a negative amount instead
int removeResources(int team, int resources) {
    switch(team) {
        case 0:
            if(teamOneResources > resources) {
                teamOneResources -= resources;
                return 0;
            }
            return 1;
            break;
        case 1:
            if(teamTwoResources > resources) {
                teamTwoResources -= resources;
                return 0;
            }
            return 1;
            break;
    }
}
