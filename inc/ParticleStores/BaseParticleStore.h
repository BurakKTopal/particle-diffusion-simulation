#ifndef BASE_PARTICLE_STORE
#define BASE_PARTICLE_STORE

#include <iostream>
#include "../Particle.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "../SpaceInformation.h"
#include <string>

using namespace std;

class BaseParticleStore
{
protected:
    int n_of_boxes;
    SpaceMetadata *space_data;
    Particle **particles;

protected:
    void initParticles(int &num_of_initial_particles);
    virtual void generateParticles(int &num_of_initial_particles) = 0;
    void displayErrorAndExit(string error_message);

public:
    virtual void checkDensity(float &density);
    bool checkIfDuplicatePosition(int position);
    BaseParticleStore(SpaceMetadata *space_data);
    virtual void initialize(float density);
    virtual void initialize(float edge_density, float center_density)
    {
        displayErrorAndExit("The initialize method with center density is only supported for CenterEdgePositionedParticleStore (aka DLA) \n"
                            "Consider using the initialize method with density only.");
    }; // DLA
    Particle **getParticles();
    bool reachedTerminalState();
    Particle *getParticleByPosition(int &position);

    virtual ~BaseParticleStore();
};

#endif // GRID_H
