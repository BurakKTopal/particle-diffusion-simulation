#ifndef TWO_DIMENSIONAL_RENDER_MACHINE_H
#define TWO_DIMENSIONAL_RENDER_MACHINE_H

#include "BaseRenderMachine.h"


class TwoDimensionalRenderMachine : public BaseRenderMachine
{
public:
    TwoDimensionalRenderMachine(SpaceMetadata *space_data, int grid_spacing);
    ~TwoDimensionalRenderMachine();

private:
    int grid_spacing;
    int grid_width;
    int grid_height;
    void fillBox(int row, int col, float r, float g, float b) override;

    void drawSpace() override;
    void drawBoxes(Particle **particles) override;
};

#endif