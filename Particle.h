#pragma once

namespace SDGEngine
{
	class Particle
	{
	public:
		Particle(int x, int y, int life);
		Particle(int x, int y, int life, int amount);
		~Particle();

		void Render();
		void Update(float delta);

	private:
		std::list<Particle *> m_particles;
		int m_life;
		TextureAsset *m_texture;
		int m_x, m_y;
		float xx, yy;
	};
}
