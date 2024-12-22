#include "ParticleStores/ParticleStoreFactory.h"

#ifndef CONFIG_H
#define CONFIG_H

const int GRID_WIDTH = 150;
const int GRID_HEIGHT = 150;
const float GRID_SPACING = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f, zoom = 1.0f;
int SIMULATION_TIME_MS = 10;
int COUNTDOWN_FOR_SIMULATION_MS = 5000;
float DENSITY = 0.8;                          // from 0 to 1
ParticleStoreType PARTICLE_STORE_TYPE = EDGE; // RANDOM | EDGE resp. puts particles initially random or at edge

#endif