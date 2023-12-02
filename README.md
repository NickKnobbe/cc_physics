# cc_physics

## Objectives
Carnage Physics aims to create a physics engine for Godot
that can be used as an efficient 2D engine in 3D projects.
The main objective is performance. 

Godot 4.x GDExtension with C++ is used. I debated using Rust, but I chose
C++ since the engine itself is written in C++.

## Benchmarking and Notes

Until another test is mentioned, it can be assumed that the previously-mentioned benchmarking test is used.

#### 11-30-2023
The main benchmark is now 2500 vessels using a hard-coded 2D input vector,
all of them following that same vector.
When using a std vector to hold all internal nodes: 183 fps
When using a std unordered map mapping vessel id to internal node and iterating with key/value: 173 fps
When using a custom cycle list to hold all internal nodes: 165 fps

#### 12-02-2023
The unordered map iteration was settled on to help with removal later. The engine now runs a physics process
with custom timers and interpolates the coordinates of frames that occur in-between
physics iterations. This allows for an excellent smooth frame rate. 
The custom processes are set up to read input and velocity to gain a better baseline for what comes next.
With all this in mind, the 2500 static movement test yields a consistent average of 167 fps. 
Vessels will be culled later on when they are away from the player. Knowing this, I am happy with these results.