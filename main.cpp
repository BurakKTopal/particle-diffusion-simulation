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
#include "src/WindowInit.cpp"
#include "inc/RenderMachines/BaseRenderMachine.h"
#include "inc/RenderMachines/TwoDimensionalRenderMachine.h"

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
    // Initialization
    srand(time(0));

    // Set up the simulation space metadata
    SpaceMetadata *space_data = new SpaceMetadata();
    space_data->setMetaData(GRID_WIDTH, GRID_HEIGHT, 2);

    // Initialize particle store and engine
    BaseParticleStore *particle_store = new RandomPositionedParticleStore(space_data);
    particle_store->initialize(0.1);
    Engine *engine = new Engine(particle_store, space_data);

    // Set up the window and particles
    GLFWwindow *window = initializeWindow();
    Particle **particles = particle_store->getParticles();

    BaseRenderMachine *render_machine = new TwoDimensionalRenderMachine();

    render_machine->render(window, particles);

    // Countdown before starting the simulation
    countDown(5000);

    // Main simulation loop
    int milliseconds = 5;
    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->update();
        cout << "Engine updated" << endl;
        render_machine->render(window, particles);
        glfwPollEvents();
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }

    cout << "Simulation ended" << endl;

    // Cleanup and close the window
    while (!glfwWindowShouldClose(window))
    {
    }

    delete particle_store;
    delete engine;
    glfwTerminate();

    return 0;
}
