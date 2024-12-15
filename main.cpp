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
int n = 100;
float gridSpacing = 1.0f;
float cameraX = 0.0f, cameraY = 0.0f;
float zoom = 1.0f;

void fillGridBox(int row, int col, float r, float g, float b)
{
    float xStart = -n / 2.0f * gridSpacing + col * gridSpacing + 0.1f;
    float yStart = -n / 2.0f * gridSpacing + row * gridSpacing + 0.1f;
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
    for (int i = 0; i <= n; ++i)
    {
        float y = -n / 2.0f * gridSpacing + i * gridSpacing;
        glVertex2f(-n / 2.0f * gridSpacing, y);
        glVertex2f(n / 2.0f * gridSpacing, y);
    }
    for (int i = 0; i <= n; ++i)
    {
        float x = -n / 2.0f * gridSpacing + i * gridSpacing;
        glVertex2f(x, -n / 2.0f * gridSpacing);
        glVertex2f(x, n / 2.0f * gridSpacing);
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

    // if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
    //     zoom *= 1.1f;
    // if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
    //     zoom /= 1.1f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void drawBoxes(BaseParticleStore *&particle_store)
{
    Particle **particles = particle_store->getParticles();
    size_t index = 0;
    while (particles[index] != NULL)
    {
        int pos = particles[index]->getPosition();
        int row = particles[index]->getPosition() / n;
        int col = particles[index]->getPosition() % n;
        if (particles[index]->getState() == MOVING)
        {
            fillGridBox((n - 1) - row, (n - 1) - col, 0.0f, 1.0f, 0.0f);
        }
        else
        {
            fillGridBox((n - 1) - row, (n - 1) - col, 1.0f, 0.0f, 0.0f);
        }
        index++;
    }
}
void render(GLFWwindow *window, BaseParticleStore *&particle_store)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glScalef(zoom, zoom, 1.0f);
    glTranslatef(cameraX, cameraY, 0.0f);
    drawGrid();
    // Drawing the boxes
    drawBoxes(particle_store);
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
        glOrtho(-n / 2.0f * gridSpacing * aspect, n / 2.0f * gridSpacing * aspect,
                -n / 2.0f * gridSpacing, n / 2.0f * gridSpacing,
                -1.0f, 1.0f);
    }
    else
    {
        glOrtho(-n / 2.0f * gridSpacing, n / 2.0f * gridSpacing,
                -n / 2.0f * gridSpacing / aspect, n / 2.0f * gridSpacing / aspect,
                -1.0f, 1.0f);
    }
}

void runIteration(GLFWwindow *window, BaseParticleStore *&particle_store, Engine *&engine)
{
    int iteration = 1;
    while (!particle_store->reachedTerminalState())
    {
        cout << "ITERATION " << iteration << endl;
        engine->updateGrid();
        // grid->display();
        iteration++;
    }
}

int main(int argc, char **argv)
{
    SpaceMetadata *space_data = (SpaceMetadata *)malloc(sizeof(SpaceMetadata));
    space_data->setMetaData(n, n, 20);

    // Initialization
    srand(time(0));

    BaseParticleStore *particle_store = new RandomPositionedParticleStore(space_data);
    particle_store->initialize(0.03);

    cout << "Start engine..." << endl;
    Engine *engine = new Engine(particle_store, space_data);
    int milliseconds = 150;

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(800, 800, "GLFW Grid with Arrow Key Movement", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    render(window, particle_store);
    cout << "iteration will start in " << endl;
    int time_before_start = 20000;
    for (int i = 0; i < time_before_start / 1000; i++)
    {
        cout << time_before_start / 1000 - i << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    while (!glfwWindowShouldClose(window) && !particle_store->reachedTerminalState())
    {
        engine->updateGrid();
        cout << "engine updated" << endl;
        processInput(window);
        render(window, particle_store);
        glfwPollEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
    cout << "Simulation ended";
    while (!glfwWindowShouldClose(window))
    {
    }
    delete particle_store;
    delete engine;
    glfwTerminate();
    return 0;
}