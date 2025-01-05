#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "inc/ParticleStores/BaseParticleStore.h"
#include "inc/ParticleStores/EdgePositionedParticleStore.h"
#include "inc/ParticleStores/RandomPositionedParticleStore.h"
#include "inc/Particle.h"
#include "inc/Engine.h"
#include <thread>
#include <chrono>
#include "inc/config.h"
#include "inc/ParticleStores/ParticleStoreFactory.h"

#include "src/Windows/GridWindow.cpp"
#include "src/RenderMachines/BaseRenderMachine.cpp"
#include "src/RenderMachines/TwoDimensionalRenderMachine.cpp"

// Use standard library components globally
using namespace std;

void countDown(int time_before_start)
{
    // Simple countdown before simulation starts
    cout << "Iteration will start in " << endl;
    for (int i = 0; i < time_before_start / 1000; i++)
    {
        cout << time_before_start / 1000 - i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}

int main(int argc, char **argv)
{
    // Initialization of randomness for particle positions
    srand(time(0));

    // Set up the simulation space metadata
    SpaceMetadata *space_data = new SpaceMetadata();
    space_data->setMetaData(GRID_WIDTH, GRID_HEIGHT, 2);

    // Initialize particle store and engine
    BaseParticleStore *particle_store = ParticleStoreFactory::initialize(PARTICLE_STORE_TYPE, space_data);
    particle_store->initialize(DENSITY, CENTER_DENSITY);

    // Setup engine
    Engine *engine = new Engine(particle_store, space_data);

    BaseWindow *window_instance = new GridWindow();

    // Set up the window and particles
    GLFWwindow *window = window_instance->initialize(800, 800, "2D Particle aggregation Simulation");
    Particle **particles = particle_store->getParticles();

    // Setup rendermachine and visualization
    BaseRenderMachine *render_machine = new TwoDimensionalRenderMachine();

    render_machine->render(window, particles);

    // Countdown before starting the simulation
    countDown(COUNTDOWN_FOR_SIMULATION_MS);

    // Main simulation loop
    size_t n_iteration = 1;
    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->update();
        cout << "Engine updated at iteration " << n_iteration << endl;
        render_machine->render(window, particles);
        glfwPollEvents();
        this_thread::sleep_for(chrono::milliseconds(SIMULATION_TIME_MS));
        n_iteration++;
    }

    cout << "Simulation ended" << endl;

    // Cleanup and close the window
    while (!glfwWindowShouldClose(window))
    {
    }

    // Cleanup
    delete particle_store;
    delete engine;
    delete render_machine;
    delete space_data;
    delete window_instance;
    glfwTerminate();

    return 0;
}
