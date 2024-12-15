#include "../../inc/RenderMachines/TwoDimensionalRenderMachine.h"
#include <glad/glad.h> // Include glad for OpenGL function loading
#include <GLFW/glfw3.h>

TwoDimensionalRenderMachine::TwoDimensionalRenderMachine(SpaceMetadata *space_data, int grid_spacing)
    : BaseRenderMachine(space_data),
      grid_height{space_data->getHeight()},
      grid_spacing{grid_spacing},
      grid_width{space_data->getWidth()}

{
    cout << "entered initialize window" << endl;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }
}

void TwoDimensionalRenderMachine::fillBox(int row, int col, float r, float g, float b)
{
    float xStart = -grid_width / 2.0f * grid_spacing + col * grid_spacing + 0.1f;
    float yStart = -grid_height / 2.0f * grid_spacing + row * grid_spacing + 0.1f;

    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(xStart, yStart);
    glVertex2f(xStart + grid_spacing - 0.2f, yStart);
    glVertex2f(xStart + grid_spacing - 0.2f, yStart + grid_spacing - 0.2f);
    glVertex2f(xStart, yStart + grid_spacing - 0.2f);
    glEnd();
}

void TwoDimensionalRenderMachine::drawSpace()
{
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);

    // Draw horizontal lines based on grid height
    for (int i = 0; i <= grid_height; ++i)
    {
        float y = -grid_height / 2.0f * grid_spacing + i * grid_spacing;
        glVertex2f(-grid_width / 2.0f * grid_spacing, y);
        glVertex2f(grid_width / 2.0f * grid_spacing, y);
    }

    // Draw vertical lines based on grid width
    for (int i = 0; i <= grid_width; ++i)
    {
        float x = -grid_width / 2.0f * grid_spacing + i * grid_spacing;
        glVertex2f(x, -grid_height / 2.0f * grid_spacing);
        glVertex2f(x, grid_height / 2.0f * grid_spacing);
    }

    glEnd();
}

void TwoDimensionalRenderMachine::drawBoxes(Particle **particles)
{
    size_t index = 0;
    while (particles[index] != NULL)
    {
        int pos = particles[index]->getPosition();
        int row = pos / grid_width;
        int col = pos % grid_width;

        if (particles[index]->getState() == MOVING)
        {
            fillBox((grid_height - 1) - row, (grid_width - 1) - col, 0.0f, 1.0f, 0.0f);
        }
        else
        {
            fillBox((grid_height - 1) - row, (grid_width - 1) - col, 1.0f, 0.0f, 0.0f);
        }

        index++;
    }
}
