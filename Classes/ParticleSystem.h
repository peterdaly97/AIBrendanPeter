#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

class ParticleSystem
{
public:

	ParticleSystem(int count, sf::Vector2f pos);	// Constructor
	
	// Update and draw functions
	void update();	
	void draw(sf::RenderWindow& window) ;

	std::vector<Particle *> m_particles;	// The vector particles the system handles
	
private:

	void resetParticle(int index);	// Function to reset particle when particle is dead

	sf::Vector2f m_position;	// Position of particle system
};
#endif // !PARTICLESYSTEM_H
