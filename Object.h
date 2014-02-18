#pragma once

namespace sidescroll
{
	class Renderer;
	struct Object
	{
		virtual ~Object() {}
		virtual void Init() = 0;
		virtual void Destroy() = 0;
		virtual void Update(float delta) = 0;
		virtual void Render() = 0;

		//void *operator new(size_t size)
		//{
		//	return MemPooler<Object>::GetUserPool().Alloc();
		//}

		//void operator delete(void *p)
		//{
		//	MemPooler<Object>::GetUserPool().Free((Object *)p);
		//}
	};
}
