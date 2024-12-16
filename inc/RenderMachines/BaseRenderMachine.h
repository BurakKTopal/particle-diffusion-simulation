#ifndef BASE_RENDER_MACHINE_H
#define BASE_RENDER_MACHINE_H

#include <GLFW/glfw3.h>
#include "../inc/Particle.h"
#include "../config.h"

// Abstract Base Class for Render Machines
class BaseRenderMachine
{
public:
    virtual ~BaseRenderMachine() = default;

    // Pure virtual methods to be implemented by derived classes
    virtual void fillBox(int row, int col, float r, float g, float b) = 0;
    virtual void drawSpace() = 0;
    virtual void drawBoxes(Particle **&particles) = 0;

    // Non-virtual render function
    void render(GLFWwindow *window, Particle **&particles);
};

#endif // BASE_RENDER_MACHINE_H