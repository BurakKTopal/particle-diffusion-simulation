#include <GLFW/glfw3.h>
#include <glad/glad.h> // Include glad for OpenGL function loading
#include <iostream>
#include "inc/ParticleStores/BaseParticleStore.h"
#include "inc/ParticleStores/EdgePositionedParticleStore.h"
#include "inc/ParticleStores/RandomPositionedParticleStore.h"
#include "inc/Particle.h"
#include "inc/Engine.h"
#include <thread>
#include <chrono>

// Grid size
int grid_width = 40;
int grid_height = 40;
float gridSpacing = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f;
float zoom = 1.0f;

namespace TwoDimensionalRenderMachine
{
    void fillGridBox(int row, int col, float r, float g, float b)
    {
        float xStart = -grid_width / 2.0f * gridSpacing + col * gridSpacing + 0.1f;
        float yStart = -grid_height / 2.0f * gridSpacing + row * gridSpacing + 0.1f;
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(xStart, yStart);
        glVertex2f(xStart + gridSpacing - 0.2f, yStart);
        glVertex2f(xStart + gridSpacing - 0.2f, yStart + gridSpacing - 0.2f);
        glVertex2f(xStart, yStart + gridSpacing - 0.2f);
        glEnd();
    }

    void drawGrid()
    {
        glLineWidth(2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);

        // Draw horizontal lines based on grid height
        for (int i = 0; i <= grid_height; ++i)
        {
            float y = -grid_height / 2.0f * gridSpacing + i * gridSpacing;
            glVertex2f(-grid_width / 2.0f * gridSpacing, y);
            glVertex2f(grid_width / 2.0f * gridSpacing, y);
        }

        // Draw vertical lines based on grid width
        for (int i = 0; i <= grid_width; ++i)
        {
            float x = -grid_width / 2.0f * gridSpacing + i * gridSpacing;
            glVertex2f(x, -grid_height / 2.0f * gridSpacing);
            glVertex2f(x, grid_height / 2.0f * gridSpacing);
        }

        glEnd();
    }

    void drawBoxes(Particle **&particles)
    {
        size_t index = 0;
        while (particles[index] != NULL)
        {
            int pos = particles[index]->getPosition();
            int row = pos / grid_width;
            int col = pos % grid_width;

            if (particles[index]->getState() == MOVING)
            {
                fillGridBox((grid_height - 1) - row, (grid_width - 1) - col, 0.0f, 1.0f, 0.0f);
            }
            else
            {
                fillGridBox((grid_height - 1) - row, (grid_width - 1) - col, 1.0f, 0.0f, 0.0f);
            }

            index++;
        }
    }
}

void render(GLFWwindow *window, Particle **&particles)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);
    TwoDimensionalRenderMachine::drawGrid();
    // Drawing the boxes
    TwoDimensionalRenderMachine::drawBoxes(particles);
    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float grid_length = std::max(grid_height, grid_width);
    glOrtho(-grid_length / 2.0f * gridSpacing, grid_length / 2.0f * gridSpacing,
            -grid_length / 2.0f * gridSpacing, grid_length / 2.0f * gridSpacing,
            -1.0f, 1.0f);
}

GLFWwindow *initializeWindow()
{
    std::cout << "Entered initialize window" << std::endl;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        exit(-1);
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "GLFW Grid with Arrow Key Movement", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return window;
}

void countDown(int time_before_start)
{
    for (int i = 0; i < time_before_start / 1000; i++)
    {
        std::cout << time_before_start / 1000 - i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char **argv)
{
    SpaceMetadata *space_data = (SpaceMetadata *)malloc(sizeof(SpaceMetadata));
    space_data->setMetaData(grid_width, grid_height, 2);

    // Initialization
    srand(time(0));

    BaseParticleStore *particle_store = new RandomPositionedParticleStore(space_data);
    particle_store->initialize(0.1);

    std::cout << "Start engine..." << std::endl;
    Engine *engine = new Engine(particle_store, space_data);
    int milliseconds = 150;

    GLFWwindow *window = initializeWindow();
    Particle **particles = particle_store->getParticles();
    render(window, particles);

    std::cout << "Iteration will start in " << std::endl;
    countDown(5000);

    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->update();
        std::cout << "Engine updated" << std::endl;
        render(window, particles);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    std::cout << "Simulation ended" << std::endl;
    while (!glfwWindowShouldClose(window))
    {
    }
    delete particle_store;
    delete engine;
    glfwTerminate();
    return 0;
}
