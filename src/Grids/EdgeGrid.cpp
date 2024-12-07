#include "../../inc/Grids/EdgeGrid.h"

EdgeGrid::EdgeGrid(int width, int height) : BaseGrid(width, height)
{
}
void EdgeGrid::generateParticles(int &num_of_initial_particles)
{
    size_t direction_id = 0;
    for (size_t i = 0; i < num_of_initial_particles; i++)
    {
        int particle_pos = generateRandomPositions(direction_id % 4);
        int num_call_in_edge = 1;
        while (checkIfDuplicatePosition(particle_pos))
        {
            if (num_call_in_edge > max(height, width))
            {
                num_call_in_edge = 1;
                direction_id += 1;
                std::cout << "direction id changed" << " on index " << i << std::endl;
                break;
            }
            particle_pos = generateRandomPositions(direction_id % 4);
            std::cout << "duplicate " << particle_pos << " !!!" << std::endl;
            num_call_in_edge++;
        }
        particles[i] = new Particle(particle_pos);
        direction_id++;
    }
}
EdgeGrid::~EdgeGrid()
{
}
