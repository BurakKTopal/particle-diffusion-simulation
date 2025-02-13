#include "ParticleStores/ParticleStoreFactory.h"

#ifndef CONFIG_H
#define CONFIG_H

const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;
const float GRID_SPACING = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f, zoom = 1.0f;
int SIMULATION_TIME_MS = 50;
int COUNTDOWN_FOR_SIMULATION_MS = 20000;
float DENSITY = 0.1;                            // from 0 to 1
ParticleStoreType PARTICLE_STORE_TYPE = RANDOM; // RANDOM | EDGE | CENTER_EDGE (DLA) resp. puts particles initially random or at edge

float CENTER_DENSITY = 0.109; // Only applicable for CENTER_EDGE particle store type

#endif