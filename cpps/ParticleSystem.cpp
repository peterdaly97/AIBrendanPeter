#include "../Classes/ParticleSystem.h"

/// <summary>
/// Constructor
/// </summary>
/// <param name="count"></param>
/// <param name="pos"></param>
ParticleSystem::ParticleSystem(int count, sf::Vector2f pos) {
	m_position = pos;	// Set particl systems position
	for (int i = 0; i < count; i++) {
	// Loop that will reiterate for each desired particle
		// Add a new particle to the particle system
		m_particles.push_back(new Particle(pos, i));
	}
}

/// <summary>
/// Function for updating all the particles in the particle system
/// </summary>
void ParticleSystem::update() {
	for (int i = 0; i < m_particles.size(); i++) {
	// Loops through every particle
		m_particles.at(i)->update();	// Updates particle
		if (m_particles.at(i)->m_lifetime < 0) {
		// checks if particle is dead
			m_particles.erase(m_particles.begin() + i);	// Deletes particle
		}
	}
}

/// <summary>
/// Function for drawing all the particles
/// </summary>
/// <param name="window"></param>
void ParticleSystem::draw(sf::RenderWindow & window) {
	for (Particle * p : m_particles) {
	// Loops through every particle 
		p->draw(window);	// Draws the particle
	}
}

/// <summary>
/// Function for resetting a dead particle
/// </summary>
/// <param name="index"></param>
void ParticleSystem::resetParticle(int index) {
	// Sets dead particle to a new particle
	m_particles.at(index) = new Particle(m_position, index);
}