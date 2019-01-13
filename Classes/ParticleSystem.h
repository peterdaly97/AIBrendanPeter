#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

class ParticleSystem
{
public:

	ParticleSystem(int count, sf::Vector2f pos);
	
	void update();

	void draw(sf::RenderWindow& window) ;

	std::vector<Particle *> m_particles;
	
private:

	void resetParticle(int index);

	
	sf::Vector2f m_position;
};
#endif // !PARTICLESYSTEM_H
