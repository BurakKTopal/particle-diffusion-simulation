#include <iostream> // Necessary for input/output operations

using namespace std;
class Grid
{
private:
    int width;
    int height;

public:
    Grid(int width, int height) : width(width), height(height)
    {
        cout << "Grid initialized with width " << width << " and height " << height << endl;
    }
};

int main()
{
    Grid *grid1 = new Grid(1, 5);
    Grid grid(2, 4);
    delete grid1;
}