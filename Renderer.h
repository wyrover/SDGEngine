#pragma once

namespace sidescroll
{
	class Renderer : public Component
	{
	public:
		Renderer() {}
		virtual ~Renderer() {}

		bool IsVisible() { return m_isVisible; }
		void setVisible(bool flag) { m_isVisible = flag; }

	private:
		bool m_isVisible = true;
	};
}
