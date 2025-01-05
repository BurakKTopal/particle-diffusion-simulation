#include "../../inc/RenderMachines/BaseRenderMachine.h"
#include <glad/glad.h>

void BaseRenderMachine::render(GLFWwindow *window, Particle **&particles)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);

    // Draw the grid and the boxes
    drawBoxes(particles);

    glfwSwapBuffers(window);
}
