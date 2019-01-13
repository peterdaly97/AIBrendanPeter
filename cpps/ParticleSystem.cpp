#include "../Classes/ParticleSystem.h"

ParticleSystem::ParticleSystem(int count, sf::Vector2f pos) {
	m_position = pos;
	for (int i = 0; i < count; i++) {
		m_particles.push_back(new Particle(pos, i));
	}
}


void ParticleSystem::update() {
	for (int i = 0; i < m_particles.size(); i++) {
		m_particles.at(i)->update();
		if (m_particles.at(i)->m_lifetime < 0) {
			//resetParticle(p->m_index);
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void ParticleSystem::draw(sf::RenderWindow & window) {
	for (Particle * p : m_particles) {
		p->draw(window);
	}
}

void ParticleSystem::resetParticle(int index) {
	m_particles.at(index) = new Particle(m_position, index);
}