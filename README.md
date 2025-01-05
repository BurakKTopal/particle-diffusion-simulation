# Particle Diffusion Simulation
C++ simulation of particle diffusion in OpenGL, with different initialization strategies (center-edge (->Diffusion Limited Aggregation), random, edge).

# Run it yourself!
In case you would like to run the executable yourself, go to the `/build` and run the executable. Be sure that the dll file is in the same folder to ensure the dynamic library linking.

# Setting up own simulation
To setup up your own simulation, with the unique params go to `inc/config.h`. Change the values here, and build (Shortcut: ctrl + shift + B for vscode). For the VSCoders, I have left the .vscode folder in there so that you can look at the build params. This should make it a lot easier.

For the project structure to get a successful build is neatly shown in 2 minutes at https://www.youtube.com/watch?v=Y4F0tI7WlDs

The project structure with these library files would look similar to:
```
diffusion-limited-aggregation/
├── debug/                   
├── lib/                     
├── inc/                     
│   ├── glad/                
│   ├── GLFW/                
│   ├── KHR/                 
│   ├── ...                  
├── src/                     
│   ├── ExternalUtils/       
│   ├── ...                  
├── .vscode/                 
│   ├── tasks.json           
│   ├── ...                 
├── ...                      
```

I've left my own tasks.json in there as this is specific to this project.

# Type of simulations

We support the following types of particle stores:

1. **Random Positioned Particle Store (`RANDOM`)**: Initializes particles at random positions within the simulation space.

2. **Edge Positioned Particle Store (`EDGE`)**: Initializes particles along the edges of the simulation space.

3. **Center Edge Positioned Particle Store (`CENTER_EDGE`)**: Initializes particles starting from the center and edges in a clockwise, snake-like pattern, systematically constructing the formation from the center outward. This approach ensures an orderly yet dynamic placement of particles suitable for diffusion-limited aggregation (DLA) simulations. This store utilizes an additional parameter `DENSITY_CENTER` to control the density of particles at the center.

# Animation

<p>
  <img src="https://github.com/BurakKTopal/diffusion-limited-aggregation/blob/main/media/particleSimulationNoGrid_150ms.gif" width="50%" />
  <br />
  <em>Simulation for random positioned particles</em>
</p>
