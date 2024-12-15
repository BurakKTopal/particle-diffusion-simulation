#ifndef BASE_RENDER_MACHINE_H
#define BASE_RENDER_MACHINE_H
#include "../Particle.h"
#include "../SpaceInformation.h"
using namespace std;

class BaseRenderMachine
{
protected:
    virtual void fillBox(int row, int col, float r, float g, float b) = 0;

public:
    BaseRenderMachine(SpaceMetadata *space_data) {};
    virtual void drawSpace() = 0;
    virtual void drawBoxes(Particle **particles) = 0;
};

#endif // ENGINE_H
