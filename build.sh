g++ $(find src/Grids -name "*.cpp") src/Particle.cpp src/Engine.cpp main.cpp -o build/main
g++ -g $(find src/Grids -name "*.cpp") src/Particle.cpp src/Engine.cpp main.cpp -o debug/main
