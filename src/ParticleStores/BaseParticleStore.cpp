#include "../../inc/ParticleStores/BaseParticleStore.h"

BaseParticleStore::BaseParticleStore(SpaceMetadata *space_data) : space_data(space_data)
{
    cout << "Particle store initialized with space having width " << space_data->getWidth() << " and height " << space_data->getHeight() << endl;
    n_of_boxes = space_data->getNumberOfBoxes();
}

bool BaseParticleStore::checkIfDuplicatePosition(int position)
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        if (particles[index]->getPosition() == position)
        {

            return true;
        }
        index++;
    }
    return false;
}

void BaseParticleStore::initParticles(int &num_of_initial_particles)
{
    this->particles = (Particle **)malloc(sizeof(Particle *) * (num_of_initial_particles + 1));
    if (particles == nullptr)
    {
        cout << "malloc failed!" << endl;
        exit(1);
    }
    for (size_t i = 0; i < num_of_initial_particles + 1; i++)
    {
        particles[i] = nullptr;
    }
}

void BaseParticleStore::displayErrorAndExit(string error_message)
{
    cout << error_message << endl;
    cin.get();
    exit(1);
}

void BaseParticleStore::checkDensity(float &density)
{
    if (density <= 0 || density > 1)
    {
        displayErrorAndExit("invalid density range (0, 1]");
    }
    if (int(density * n_of_boxes) == 0)
    {
        displayErrorAndExit("too small density, please choose at least " + to_string(1 / (float)n_of_boxes));
    }
}

void BaseParticleStore::initialize(float density)
{
    checkDensity(density);

    int num_of_initial_particles = int(density * n_of_boxes);

    initParticles(num_of_initial_particles);

    generateParticles(num_of_initial_particles);
}

Particle *BaseParticleStore::getParticleByPosition(int &position)
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        if (particles[index]->getPosition() == position)
        {
            return particles[index];
        }
        index++;
    }
    return NULL;
}

Particle **BaseParticleStore::getParticles()
{
    return particles;
}

bool BaseParticleStore::reachedTerminalState()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        if (particles[index]->getState() == MOVING)
        {
            return false;
        }
        index++;
    }
    return true;
}

BaseParticleStore::~BaseParticleStore()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        free(particles[index]);
        index++;
    }
    free(particles);
}
