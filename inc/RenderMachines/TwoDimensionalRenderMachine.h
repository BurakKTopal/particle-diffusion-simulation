#ifndef TWO_DIMENSIONAL_RENDER_MACHINE_H
#define TWO_DIMENSIONAL_RENDER_MACHINE_H

#include "BaseRenderMachine.h"
#include "config.h"
// Concrete implementation of a 2D Render Machine
class TwoDimensionalRenderMachine : public BaseRenderMachine
{
public:
    void fillBox(int row, int col, float r, float g, float b) override;
    void drawSpace() override;
    void drawBoxes(Particle **&particles) override;
};

#endif // TWO_DIMENSIONAL_RENDER_MACHINE_H
