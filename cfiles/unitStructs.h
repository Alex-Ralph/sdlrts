/*contains all the necessary structures these are:
A unit struct for controllable, attackable units
A buildings struct for buildings that build units
A projectiles struct to produce projectiles fired by ranged units
*/

//Defines a type for a unit
typedef struct unit {
    int ID; //for identifying the unit
    short typeID; //what type of unit this is (IE archer, warrior, scout)
    short health; //the current health of the unit
    short maxhealth; //the maximum health of the unit
    short atk; //attack damage dealt by the unit
    short atkspd; //attack speed in milliseconds of the unit
    int x; //x location of top left corner
    int y; //y location of top left corner
    int moveToX; //target location to move to, or -1 if inactive
    int moveToY; //target location to move to, or -1 if inactive
    int timeToAtk; //time until the unit can unleash its next attack
    short movSpd; //movement speed of the unit
    short range; //range of the unit (0 if melee)
    short size; //size of the unit in pixels
    short team; //which team the unit is on

    //used only for movement pathing, for the purpose of making it smoother
    float realX;
    float realY;

    struct unit *attacking; // the unit this unit is trying to attack
    struct building *attackingBuilding; //the building this unit is trying to attack

    //for use in the linked list
    struct unit *unitBefore;
    struct unit *unitAfter;


} unit;
//units that will require global access
unit *firstUnit;
unit *activeUnit;

//for ranged removeAllUnits
typedef struct projectile {
    short range; //how far the projectile will travel
    short remainingrange; //how far the projectile has left to travel
    unit* targetUnit; //the unit the projectile is trying to hit
    struct building* targetBuilding; //the building the projectile is trying to hit
    short damage; //the amount of damage the projectile will do
    short speed; //the speed at which the projectile travels
    int x; //x location of the tip of the projectile
    int y; //y location of the tip of the projectile
    float xspeed; //speed of the projectile along x
    float yspeed; //speed of the projectile along y
    float realx; //actual precise location of x
    float realy; //actual precise location of y
    int firedFromx; //source from which the projectile was fired
    int firedFromy; //source from which the projectile was fired
    int destx; //destination on the x axis
    int desty; //destination on the y axis
    float angle; //angle at which the projectile was fired (degrees)

    //for use in the linked list
    struct projectile *projectileBefore;
    struct projectile *projectileAfter;
} projectile;

//public projectile, does not exist in the game, only for linked list usage
projectile *firstProjectile;

//building struct
typedef struct building {
    int x; //x location of top left
    int y; //y location
    short ID; //ID of building
    short typeID; //ID of type of building
    short size; //size of building in pixels
    short health; //remaining health of building
    short maxhealth; //max health of building
    short team; //team to which the building belongs
    short unitBuildingType; //type of unit the building is building
    int totalBuildTime; //max build time for whatever teh building is building
    int buildTimeRemaining; //remaining build time

    //for use in linked list
    struct building *buildingBefore;
    struct building *buildingAfter;
} building;


//global buildings
building *firstBuilding;
building *activeBuilding;
