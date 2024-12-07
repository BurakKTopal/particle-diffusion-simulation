#include <iostream>
#include "../../inc/Grids/BaseGrid.h"
#include "../../inc/Particle.h"

using namespace std;

BaseGrid::BaseGrid(int width, int height) : width(width), height(height)
{

    cout << "Grid initialized with width " << width << " and height " << height << endl;
    grid_len = width * height;
}

bool BaseGrid::checkIfDuplicatePosition(int position)
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

int BaseGrid::generateRandomPositions(size_t case_id)
{
    int pos;
    int random_number = (rand() + 1); // +1 to not give more chance for 0
    switch (case_id)
    {
    case 0:
        pos = random_number % width;
        break;
    case 1:
        pos = (width - 1) + (random_number % height) * width;
        break;
    case 2:
        pos = (random_number % width) + (height - 1) * (width);
        break;
    case 3:
        pos = (random_number % height) * (width);
        break;
    default:
        pos = random_number % grid_len;
        break;
    }
    return pos;
}

void BaseGrid::initParticles(int &num_of_initial_particles)
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

void BaseGrid::initialize(float density)
{
    if (density <= 0 || density > 1)
    {
        cout << "invalid density range (0, 1]" << endl;
        exit(1);
    }

    int num_of_initial_particles = int(density * grid_len);
    if (num_of_initial_particles == 0)
    {
        cout << "too small density, please choose at least " << (1 / (float)grid_len) << endl;
        exit(1);
    }

    if (num_of_initial_particles > 2 * (width + height) - 4)
    {
        cout << "Too much boundary particles. Maximally " << ((float)(2 * (width + height) - 4) / (height * width)) << endl;
        exit(1);
    }
    initParticles(num_of_initial_particles);

    generateParticles(num_of_initial_particles);
}

Particle *BaseGrid::getParticleByPosition(int &position)
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

void BaseGrid::print()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        cout << "there is a particle at " << particles[index]->getPosition() << endl;
        index++;
    }
}

void BaseGrid::display()
{
    vector<vector<int>> grid(height, vector<int>(width, 0));
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        Particle *particle = particles[index];
        int row = particle->getPosition() / width;
        int col = particle->getPosition() % width;
        (particle->getState() == MOVING) ? grid[row][col] = 1 : grid[row][col] = 2;
        index++;
    }
    for (const auto &row : grid)
    {
        for (const auto &cell : row)
        {
            cout << cell << " ";
        }
        cout << endl;
    }
}

Particle **BaseGrid::getParticles()
{
    return particles;
}
int BaseGrid::getWidth()
{
    return width;
}

int BaseGrid::getHeight()
{
    return height;
}

bool BaseGrid::reachedTerminalState()
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

BaseGrid::~BaseGrid()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        free(particles[index]);
        index++;
    }
    free(particles);
}
