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
int width = 25;
int height = 25;
float grid_spacing = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f;
float zoom = 1.0f;

void fillGridBox(int row, int col, float r, float g, float b)
{
    float xStart = -width / 2.0f * grid_spacing + col * grid_spacing + 0.1f;
    float yStart = -height / 2.0f * grid_spacing + row * grid_spacing + 0.1f;
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(xStart, yStart);
    glVertex2f(xStart + grid_spacing - 0.2f, yStart);
    glVertex2f(xStart + grid_spacing - 0.2f, yStart + grid_spacing - 0.2f);
    glVertex2f(xStart, yStart + grid_spacing - 0.2f);
    glEnd();
}

void drawGrid()
{
    glLineWidth(2.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);

    // Draw horizontal lines
    for (int i = 0; i <= height; ++i)
    {
        float y = -height / 2.0f * grid_spacing + i * grid_spacing;
        glVertex2f(-width / 2.0f * grid_spacing, y);
        glVertex2f(width / 2.0f * grid_spacing, y);
    }

    // Draw vertical lines
    for (int i = 0; i <= width; ++i)
    {
        float x = -height / 2.0f * grid_spacing + i * grid_spacing;
        glVertex2f(x, -width / 2.0f * grid_spacing);
        glVertex2f(x, height / 2.0f * grid_spacing);
    }

    glEnd();
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraY -= 0.01f / zoom;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraY += 0.01f / zoom;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraX += 0.01f / zoom;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraX -= 0.01f / zoom;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawBoxes(Particle **particles)
{
    size_t index = 0;
    while (particles[index] != NULL)
    {
        int pos = particles[index]->getPosition();
        int row = particles[index]->getPosition() / width;
        int col = particles[index]->getPosition() % width;
        if (particles[index]->getState() == MOVING)
        {
            fillGridBox((height - 1) - row, (width - 1) - col, 0.0f, 1.0f, 0.0f);
        }
        else
        {
            fillGridBox((height - 1) - row, (width - 1) - col, 1.0f, 0.0f, 0.0f);
        }
        index++;
    }
}

void render(GLFWwindow *window, Particle **particles)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);
    drawGrid();
    // Drawing the boxes
    // drawBoxes(particles);
    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)width / height;
    if (aspect >= 1.0f)
    {
        glOrtho(-width / 2.0f * grid_spacing * aspect, width / 2.0f * grid_spacing * aspect,
                -height / 2.0f * grid_spacing, height / 2.0f * grid_spacing,
                -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-width / 2.0f * grid_spacing, width / 2.0f * grid_spacing,
                -height / 2.0f * grid_spacing / aspect, height / 2.0f * grid_spacing / aspect,
                -1.0f, 1.0f);
    }
}

GLFWwindow *initializeWindow()
{
    cout << "entered initialize window" << endl;
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        // exit(-1);
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "GLFW Grid with Arrow Key Movement", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        // exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        // exit(-1);
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    return window;

    cout << "EXITED initialize window" << endl;
}

void countDown(int time_before_start)
{
    for (int i = 0; i < time_before_start / 1000; i++)
    {
        cout << time_before_start / 1000 - i << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(int argc, char **argv)
{
    SpaceMetadata *space_data = (SpaceMetadata *)malloc(sizeof(SpaceMetadata));
    space_data->setMetaData(width, width, 2);

    // Initialization
    srand(time(0));

    BaseParticleStore *particle_store = new RandomPositionedParticleStore(space_data);
    particle_store->initialize(0.03);

    cout << "Start engine..." << endl;
    Engine *engine = new Engine(particle_store, space_data);

    GLFWwindow *window = initializeWindow();
    render(window, particle_store->getParticles());

    cout << "iteration will start in " << endl;
    countDown(5000);

    int milliseconds = 150;
    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->update();
        cout << "engine updated" << endl;
        processInput(window);
        render(window, particle_store->getParticles());
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    cout << "Simulation ended";
    while (!glfwWindowShouldClose(window))
    {
    }
    delete particle_store;
    delete engine;
    delete space_data;
    glfwTerminate();
    return 0;
}