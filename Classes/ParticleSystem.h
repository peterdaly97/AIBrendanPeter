#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "Particle.h"

class ParticleSystem
{
public:

	ParticleSystem(int count, sf::Vector2f pos);
	
	void update();

	void draw(sf::RenderWindow& window) ;
	
private:

	void resetParticle(int index);

	std::vector<Particle *> m_particles;
	sf::Vector2f m_position;
};
#endif // !PARTICLESYSTEM_H
