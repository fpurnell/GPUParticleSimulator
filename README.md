# Particle-Simulator
This program will simulate 2-Dimensional particle interactions with conservation of momentum.
To generate the most realistic results possible, a lot of processing power is used.

Models Used:
The system conserves momentum, therefore it is assumed that every collision is elastic.
This also assumes that the particles do not chemically or subatomically react in any way.




# Global Inputs:

isAbleGPU - whether the user's computer is able to run a GPU version
isGPU - whether to include CUDA for processing
isSingleThreaded - whether to use multi-threaded CPU applcation
numCPUCores - the number of cores to use with CPU processing
(A) numParticles - the number of particles to populate the boundary
isOnePartSize - if there is only one size of particles 
(A) sizeParts - the size of the particles and their percentage of the whole
boundShape - the shape (square, rectangle, circle, concentric circle, etc.)
boundSizeA - The Primary dimension of the boundary
boundSizeB - (opt.) The secondary dimension of the boundary
numberSects - number of sections in which to divide the boundary

# Global Outputs:

(A) sectParticles - the number of particles present in a subsection
