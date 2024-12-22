
#include "../../inc/ParticleStores/CenterEdgePositionedParticleStore.h"

CenterEdgePositionedParticleStore::CenterEdgePositionedParticleStore(SpaceMetadata *space_data)
    : EdgePositionedParticleStore(space_data)
{
}

void CenterEdgePositionedParticleStore::generateCenterParticles(int num_edge_particles, int num_center_particles)
{
    int width = space_data->getWidth();
    int height = space_data->getHeight();
    int center_col = width / 2 - 1;
    int center_row = height / 2;
    int center_pos = center_col + center_row * width;
    int displacement[] = {-width, 1, width, -1}; // 0: up, 1: right, 2: down, 3: left

    cout << "Generating center particles at position " << center_pos << endl;
    cout << "Number of edge particles: " << num_edge_particles << endl;
    cout << "Number of center particles: " << num_center_particles << endl;

    particles[num_edge_particles] = new Particle(center_pos, STATIONARY); // Only center particle is stationary

    int index = 1;
    int curr_pos = center_pos;
    int direction_id = 0;
    int steps = 0;

    while (index < num_center_particles)
    {
        if (direction_id % 2 == 0)
        {
            steps++;
        }

        for (int i = 0; i < steps && index < num_center_particles; i++)
        {
            curr_pos += displacement[direction_id % 4];
            particles[num_edge_particles + index] = new Particle(curr_pos, STATIONARY);
            index++;
        }

        direction_id++;
    }
}

void CenterEdgePositionedParticleStore::generateParticles(int num_edge_particles, int num_center_particles)
{
    EdgePositionedParticleStore::generateParticles(num_edge_particles);
    generateCenterParticles(num_edge_particles, num_center_particles);
}

void CenterEdgePositionedParticleStore::checkCenterDensity(float center_density)
{
    int width = space_data->getWidth();
    int height = space_data->getHeight();
    int num_center_particles = static_cast<int>(center_density * width * height);
    int max_center_particles = (width - 2) * (height - 2); // There should be at least distance of 1 from the edge

    if (num_center_particles > max_center_particles)
    {
        displayErrorAndExit("Too many center particles. Maximum allowed: " + to_string(max_center_particles));
    }
    if (num_center_particles < 0)
    {
        displayErrorAndExit("Number of center particles must be strictly bigger than 0.");
    }
    if (num_center_particles == 0)
    {
        displayErrorAndExit("The number of center particle density should be at least " + to_string(1.0f / max_center_particles));
    }
    if (max_center_particles < 0)
    {
        displayErrorAndExit("Space is too small to have center particles. Consider increasing the space size.");
    }
}

void CenterEdgePositionedParticleStore::initialize(float edge_density, float center_density)
{
    checkCenterDensity(center_density);
    checkDensity(edge_density);

    int num_edge_particles = static_cast<int>(edge_density * n_of_boxes);
    int num_center_particles = static_cast<int>(center_density * space_data->getWidth() * space_data->getHeight());
    int total_particles = num_edge_particles + num_center_particles;

    BaseParticleStore::initParticles(total_particles);
    generateParticles(num_edge_particles, num_center_particles);
}

void CenterEdgePositionedParticleStore::initialize(float density)
{
    float center_density = 1.0f / (space_data->getWidth() * space_data->getHeight());
    initialize(density, center_density);
}

CenterEdgePositionedParticleStore::~CenterEdgePositionedParticleStore()
{
}