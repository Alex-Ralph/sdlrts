#include "projectiles.h"
#include<stdio.h>

//initialises projectiles linked list
void initProjectiles() {
    firstProjectile = (projectile *)malloc(sizeof(projectile));
    firstProjectile->projectileBefore = NULL;
    firstProjectile->projectileAfter = NULL;
}

//provides pointer of the last projectile in the linked list
projectile *findLastProj() {
    projectile *proj = firstProjectile;
    while(proj->projectileAfter != NULL) {
        proj = proj->projectileAfter;
    }
    return proj;
}

//takes source unit as input, produces the relevant projectile
projectile *addProjectile(unit *source) {
    projectile *newProj = (projectile *)malloc(sizeof(projectile));
    newProj->range = source->range;
    newProj->remainingrange = newProj->range;
    newProj->x = source->x;
    newProj->y = source->y;
    newProj->realx = source->x;
    newProj->realy = source->y;
    newProj->damage = source->atk;
    newProj->speed = 600; //placeholder value, perhaps should be decided by units
    newProj->firedFromx = source->x;
    newProj->firedFromy = source->y;
    newProj->targetUnit = source->attacking;

    //get destination
    int targx, targy;
    findCenter(newProj->targetUnit, &targx, &targy);
    newProj->destx = targx;
    newProj->desty = targy;

    //find how far on the x and y the projectile should travel each cycle
    int distx = newProj->destx - newProj->x;
    int disty = newProj->desty - newProj->y;
    float xratio = (float)abs(distx) / (float)(abs(distx) + abs(disty));
    newProj->xspeed = xratio * newProj->speed * ((distx>0)-(distx<0));
    newProj->yspeed =
    (newProj->speed - fabs(newProj->xspeed)) * ((disty>0)-(disty<0));
    //add to projectile linked list
    projectile *lastProj = findLastProj();
    newProj->projectileBefore = lastProj;
    newProj->projectileAfter = NULL;
    lastProj->projectileAfter = newProj;

    //angle of projection of the projectile
    float baseangle = atan(fabs((float)disty)/fabs((float)distx)) * (180 / M_PI);
    float angle = 0;
    if(distx >= 0 && disty >= 0) { //lower right quadrant
        angle = baseangle;
    }
    else if(distx <=0 && disty >= 0) { //lower left quadrant
        angle = 180 - baseangle;
    }
    else if(distx <= 0 && disty <= 0) {//upper left quadrant
        angle = 180 + baseangle;
    }
    else { //upper left quadrant
        angle = 360 - baseangle;
    }
    newProj->angle = angle;
}

//removes a projectile from the list and existence in general
void removeProjectile(projectile *proj) {
    projectile *projBefore = proj->projectileBefore;
    projectile *projAfter = proj->projectileAfter;
    if(projAfter != NULL) {
        projBefore->projectileAfter = projAfter;
        projAfter->projectileBefore = projBefore;
    }
    else {
        projBefore->projectileAfter = NULL;
    }
    free(proj);
}

//removes all projectiles, used when shutting down the program
void removeAllProjectiles() {
    projectile *proj = firstProjectile;
    while(proj != NULL) {
        projectile *nextProj = proj->projectileAfter;
        free(proj);
        proj = nextProj;
    }
}

//checks if a projectile has hit its target
//returns 1 if the projectile has hit, 0 otherwise
int checkHit(projectile *proj) {
    int maxx, maxy;
    maxx = proj->targetUnit->x + proj->targetUnit->size;
    maxy = proj->targetUnit->y + proj->targetUnit->size;
    if(
    proj->x > proj->targetUnit->x &&
    proj->y > proj->targetUnit->y &&
    proj->x < maxx &&
    proj->y < maxy) {
        return 1;
    }
    return 0;
}

//a cycle to be run every game loop, to update all projectiles
void cycleProjectiles() {
    projectile *proj = firstProjectile;
    while(proj->projectileAfter != NULL) {
        proj = proj->projectileAfter;

        int distancex = abs(proj->destx - proj->x);
        int distancey = abs(proj->desty - proj->y);
        int distance = sqrt(distancex*distancex + distancey*distancey);
        if(checkHit(proj)) {
            proj->targetUnit->health -= proj->damage;
            removeProjectile(proj);
            continue;
        }
        else if(proj->destx == proj->x && proj->desty == proj->y) {
            removeProjectile(proj);
            continue;
        }
        else if(distance < proj->speed/100) {
            proj->x = proj->destx;
            proj->y = proj->desty;
        }
        else {
            proj->realx += proj->xspeed / 100;
            proj->realy += proj->yspeed / 100;
            proj->x = proj->realx;
            proj->y = proj->realy;
        }
    }
}
