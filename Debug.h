#pragma once

namespace sidescroll
{
	class Debug : public MySingleton<Debug>
	{
	public:
		Debug();
		~Debug();

		template <typename T>
		void Log(T type)
		{
			std::cout << type << std::endl;
		}

		template <>
		void Log<D3DXVECTOR2>(D3DXVECTOR2 type)
		{
			std::cout << "x: " << type.x << " y: " << type.y << std::endl;
		}

		template <>
		void Log<D3DXCOLOR>(D3DXCOLOR type)
		{
			std::cout << "r: " << type.r << " g: " << type.g << " b: " << type.b << " a: " << type.a << std::endl;
		}
	};
}
