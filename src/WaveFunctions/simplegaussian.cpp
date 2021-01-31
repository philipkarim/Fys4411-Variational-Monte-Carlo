#include "simplegaussian.h"
#include <cmath>
#include <cassert>
#include "wavefunction.h"
#include "../system.h"
#include "../particle.h"

SimpleGaussian::SimpleGaussian(System* system, double alpha) :
        WaveFunction(system) {
    assert(alpha >= 0);
    m_numberOfParameters = 1;
    m_parameters.reserve(1);
    m_parameters.push_back(alpha);
}

double SimpleGaussian::evaluate(std::vector<class Particle*> particles) {
    /* You need to implement a Gaussian wave function here. The positions of
     * the particles are accessible through the particle[i].getPosition()
     * function.
     *
     * For the actual expression, use exp(-alpha * r^2), with alpha being the
     * (only) variational parameter.
     */

     //Calculating a simple gaussian function, looping over each particle
     //in each dimension.
     double r_tot=0.0, psi=1.0;
     std::vector<double> r_pos;

     for(int i=0; i<m_system->getNumberOfParticles(); i++){
       r_pos=particles[i]->getPosition();
       for (int dim=0; dim<m_system->getNumberOfDimensions(); dim++){
         r_tot+=r_pos[dim]*r_pos[dim];

       }
       psi*=exp(-m_parameters[0]*r_tot);
     }
    return psi;
}

double SimpleGaussian::computeDoubleDerivative(std::vector<class Particle*> particles) {
    /* All wave functions need to implement this function, so you need to
     * find the double derivative analytically. Note that by double derivative,
     * we actually mean the sum of the Laplacians with respect to the
     * coordinates of each particle.
     *
     * This quantity is needed to compute the (local) energy (consider the
     * Schrödinger equation to see how the two are related).
     */

     //Non interacting, probably have to add a longer bit of code and an
     //if statement when adding the interacting case

     // For non-interacting particles
     std::vector<double> r_pos;
     double wf=evaluate(particles);
     double derivate2, r_tot;

     for(int i=0; i<m_system->getNumberOfParticles(); i++){
       r_pos=particles[i]->getPosition();
       for (int dim=0; dim<m_system->getNumberOfDimensions(); dim++){
         r_tot+=r_pos[dim]*r_pos[dim];
         derivate2-=2*m_parameters[0]*(2*m_parameters[0]*r_tot)*wf;
       }
       derivate2+=2*m_parameters[0]*m_system->getNumberOfDimensions()*wf;
     }
    return derivate2;
}