#include "../../inc/RenderMachines/BaseRenderMachine.h"
#include <glad/glad.h>

// Non-virtual render function implementation
void BaseRenderMachine::render(GLFWwindow *window, Particle **&particles)
{
    // Clear the screen and set up the camera
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);

    // Draw the grid and the boxes
    // drawSpace();
    drawBoxes(particles);

    // Swap buffers to render
    glfwSwapBuffers(window);
}
