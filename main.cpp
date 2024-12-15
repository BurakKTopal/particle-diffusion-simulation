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

// Use standard library components globally
using namespace std;

const int GRID_WIDTH = 40;
const int GRID_HEIGHT = 40;
const float GRID_SPACING = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f, zoom = 1.0f;

namespace TwoDimensionalRenderMachine
{
    void fillGridBox(int row, int col, float r, float g, float b)
    {
        // Fill a grid box with the specified color
        float xStart = -GRID_WIDTH / 2.0f * GRID_SPACING + col * GRID_SPACING + 0.1f;
        float yStart = -GRID_HEIGHT / 2.0f * GRID_SPACING + row * GRID_SPACING + 0.1f;
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(xStart, yStart);
        glVertex2f(xStart + GRID_SPACING - 0.2f, yStart);
        glVertex2f(xStart + GRID_SPACING - 0.2f, yStart + GRID_SPACING - 0.2f);
        glVertex2f(xStart, yStart + GRID_SPACING - 0.2f);
        glEnd();
    }

    void drawGrid()
    {
        glLineWidth(2.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINES);

        // Draw horizontal lines
        for (int i = 0; i <= GRID_HEIGHT; ++i)
        {
            float y = -GRID_HEIGHT / 2.0f * GRID_SPACING + i * GRID_SPACING;
            glVertex2f(-GRID_WIDTH / 2.0f * GRID_SPACING, y);
            glVertex2f(GRID_WIDTH / 2.0f * GRID_SPACING, y);
        }

        // Draw vertical lines
        for (int i = 0; i <= GRID_WIDTH; ++i)
        {
            float x = -GRID_WIDTH / 2.0f * GRID_SPACING + i * GRID_SPACING;
            glVertex2f(x, -GRID_HEIGHT / 2.0f * GRID_SPACING);
            glVertex2f(x, GRID_HEIGHT / 2.0f * GRID_SPACING);
        }

        glEnd();
    }

    void drawBoxes(Particle **&particles)
    {
        size_t index = 0;
        while (particles[index] != nullptr)
        {
            int pos = particles[index]->getPosition();
            int row = pos / GRID_WIDTH;
            int col = pos % GRID_WIDTH;

            // Set box color based on particle state
            float r = (particles[index]->getState() == MOVING) ? 0.0f : 1.0f;
            float g = (particles[index]->getState() == MOVING) ? 1.0f : 0.0f;
            fillGridBox((GRID_HEIGHT - 1) - row, (GRID_WIDTH - 1) - col, r, g, 0.0f);
            index++;
        }
    }
}

void render(GLFWwindow *window, Particle **&particles)
{
    // Clear the screen and set up the camera
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);

    // Draw the grid and the boxes
    TwoDimensionalRenderMachine::drawGrid();
    TwoDimensionalRenderMachine::drawBoxes(particles);

    // Swap buffers to render
    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float grid_length = max(GRID_HEIGHT, GRID_WIDTH);
    glOrtho(-grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
            -grid_length / 2.0f * GRID_SPACING, grid_length / 2.0f * GRID_SPACING,
            -1.0f, 1.0f);
}

GLFWwindow *initializeWindow()
{
    // Initialize GLFW and create a window
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW" << endl;
        exit(-1);
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "Diffusion-limited-aggregation-simulation", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    // Initialize OpenGL loader (GLAD)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cerr << "Failed to initialize GLAD" << endl;
        exit(-1);
    }

    // Set up the framebuffer size callback
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set the background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return window;
}

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
    render(window, particles);

    // Countdown before starting the simulation
    countDown(5000);

    // Main simulation loop
    int milliseconds = 5;
    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->update();
        cout << "Engine updated" << endl;
        render(window, particles);
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
