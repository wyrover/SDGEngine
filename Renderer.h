#pragma once

class Renderer : public Component
{
public:
	Renderer();
	virtual ~Renderer();

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float delta) override;
	virtual void Render() override;

private:
};