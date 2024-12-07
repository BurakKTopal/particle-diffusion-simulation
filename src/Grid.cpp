#include <iostream>
#include <map>
#include <vector>
#include "../inc/Grid.h"
#include "../inc/Particle.h"

using namespace std;

Grid::Grid(int width, int height) : width(width), height(height)
{

    cout << "Grid initialized with width " << width << " and height " << height << endl;
    grid_len = width * height;
}

bool Grid::checkIfDuplicatePosition(int position)
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

int Grid::generateRandomPosOnEdge(size_t case_id)
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
        break;
    }
    return pos;
}

void Grid::initParticles(int &num_of_initial_particles)
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

void Grid::initialize(float density)
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

    size_t direction_id = 0;
    for (size_t i = 0; i < num_of_initial_particles; i++)
    {
        int particle_pos = generateRandomPosOnEdge(direction_id % 4);
        int num_call_in_edge = 1;
        while (checkIfDuplicatePosition(particle_pos))
        {
            if (num_call_in_edge > max(height, width))
            {
                num_call_in_edge = 1;
                direction_id += 1;
                cout << "direction id changed" << "on index" << i << endl;
                break;
            }
            particle_pos = generateRandomPosOnEdge(direction_id % 4);
            cout << "duplicate " << particle_pos << " !!!" << endl;
            num_call_in_edge++;
        }
        particles[i] = new Particle(particle_pos);
        direction_id++;
    }
}

Particle *Grid::getParticleByPosition(int &position)
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

void Grid::print()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        cout << "there is a particle at " << particles[index]->getPosition() << endl;
        index++;
    }
}

void Grid::display()
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

Particle **Grid::getParticles()
{
    return particles;
}
int Grid::getWidth()
{
    return width;
}

int Grid::getHeight()
{
    return height;
}

bool Grid::reachedTerminalState()
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

Grid::~Grid()
{
    size_t index = 0;
    while (particles[index] != nullptr)
    {
        free(particles[index]);
        index++;
    }
    free(particles);
}
