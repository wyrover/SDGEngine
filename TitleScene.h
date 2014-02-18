#pragma once

class TitleScene : public GameScene
{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Start() override;
	virtual void Finish() override;

	virtual void OnUpdate(float delta) override;
	virtual void OnRender() override;
};
