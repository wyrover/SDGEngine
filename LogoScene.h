#pragma once

class LogoScene : public GameScene
{
public:
	LogoScene();
	virtual ~LogoScene();

	virtual void Init() final;
	virtual void Destroy() final;

	virtual void Update(float delta) final;
	virtual void Render() final;

private:

};
