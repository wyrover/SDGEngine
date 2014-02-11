#pragma once

class Renderer;
struct Object
{
	virtual ~Object() {}
	virtual void Init() = 0;
	virtual void Destroy() = 0;
	virtual void Update(float delta) = 0;
	virtual void Render() = 0;
};
