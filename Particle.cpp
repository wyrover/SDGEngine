#include "Precompiled.h"
#include "Particle.h"

namespace SDGEngine
{
	Particle::Particle(int x, int y, int life) 
		:m_x(x), m_y(y), m_life(life), xx(x), yy(y)
	{
		m_texture = Singleton<Assets>::GetSingleton()->RequestTexture("particle.tga");
	}

	Particle::Particle(int x, int y, int life, int amount)
		:m_x(x), m_y(y), m_life(life)
	{
		m_texture = Singleton<Assets>::GetSingleton()->RequestTexture("particle.tga");
		Particle(x, y, life);
		for (int i = 0; i < amount - 1; i++) {
			m_particles.push_back(new Particle(x, y, life));
		}
		m_particles.push_back(this);
	}

	Particle::~Particle() {
		for (auto i : m_particles) {
			SDELETE(i);
		}
	}

	void Particle::Render() {
		for (auto i : m_particles) {
			Graphics::RenderLineRect(i->xx, i->yy, 1.f, 1.f);
		}
	}

	void Particle::Update(float delta) {
		xx += delta;
		yy += delta;
	}
}