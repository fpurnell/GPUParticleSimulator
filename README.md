# GPUParticleSimulator
Using nVidia's CUDA language, this program will simulate rudimentary particle diffusion.





Global Inputs:

(A) numParticles - the number of particles to populate the boundary
isOnePartSize - if there is only one size of particles 
(A) sizeParts - the size of the particles and their percentage of the whole
boundShape - the shape (square, rectangle, circle, concentric circle, etc.)
boundSizeA - The Primary dimension of the boundary
boundSizeB - (opt.) The secondary dimension of the boundary
numberSects - number of sections in which to divide the boundary

Global Outputs:

(A) sectParticles - the number of particles present in a subsection
