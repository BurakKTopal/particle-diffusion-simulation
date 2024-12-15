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

// int BaseParticleStore::generateRandomPositions(size_t case_id)
// {
//     int pos;
//     int random_number = (rand() + 1); // +1 to not give more chance for 0
//     switch (case_id)
//     {
//     case 0:
//         pos = random_number % width;
//         break;
//     case 1:
//         pos = (width - 1) + (random_number % height) * width;
//         break;
//     case 2:
//         pos = (random_number % width) + (height - 1) * (width);
//         break;
//     case 3:
//         pos = (random_number % height) * (width);
//         break;
//     default:
//         pos = random_number % grid_len;
//         break;
//     }
//     return pos;
// }

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

void BaseParticleStore::initialize(float density)
{

    if (density <= 0 || density > 1)
    {
        cout << "invalid density range (0, 1]" << endl;
        exit(1);
    }
    int num_of_initial_particles = int(density * n_of_boxes);
    if (num_of_initial_particles == 0)
    {
        cout << "too small density, please choose at least " << (1 / (float)n_of_boxes) << endl;
        exit(1);
    }
    additionalDensityCheck(density);

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
// int BaseParticleStore::getWidth()
// {
//     return width;
// }

// int BaseParticleStore::getHeight()
// {
//     return height;
// }

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
