#pragma once
#include "Particle.h"

class Blob :
    public Particle
{
    //à voir si on fait une particule avec un certain nombre de liaisons possibles (genre hexagone par ex)
    //ou si on fait une liste de voisins ? ça peut se faire
    //par contre ça serait un peu dégueu en brut de faire tout les voisinages sur le ofApp 
    //genre on a part1 part2 et part3
    //faut appliquer ressortA sur part1 et part2, ressortB sur part2 et part3, ressortC sur part3 et part1 par ex
    //du coup 6 forces à appliquer

};

