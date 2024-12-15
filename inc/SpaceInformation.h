#ifndef SPACE_INFORMATION
#define SPACE_INFORMATION

typedef struct
{
private:
    int dimension;
    int width;
    int height;

public:
    int getDimension()
    {
        return dimension;
    }
    int getWidth()
    {
        return width;
    }
    int getHeight()
    {
        return height;
    }
    int getNumberOfBoxes()
    {
        return height * width;
    }

    void setMetaData(int width, int height, int dimension)
    {
        this->dimension = dimension;
        this->height = height;
        this->width = width;
    }
} SpaceMetadata;

#endif // RANDOM_POSITIONED_PARTICLE_STORE
