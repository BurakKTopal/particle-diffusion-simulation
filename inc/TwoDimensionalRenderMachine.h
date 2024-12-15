#ifndef TWODIMENSIONALRENDERMACHINE_H
#define TWODIMENSIONALRENDERMACHINE_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "../inc/ParticleStores/BaseParticleStore.h"
#include "SimulationParams.h"

namespace TwoDimensionalRenderMachine
{

    // Function to fill a specific grid box with color
    void fillGridBox(int row, int col, float r, float g, float b);

    // Function to draw the grid lines
    void drawGrid();

    // Function to process user input for camera movement and zoom
    void processInput(GLFWwindow *window);

    // Function to draw the boxes based on particle positions
    void drawBoxes(Particle **particles);

    // Function to render the scene (grid and particles)
    void render(GLFWwindow *window, Particle **particles);
}

#endif // TWODIMENSIONALRENDERMACHINE_H
