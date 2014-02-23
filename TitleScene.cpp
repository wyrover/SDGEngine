#include "Precompiled.h"

namespace sidescroll
{
	TitleScene::TitleScene()
	{
	}

	TitleScene::~TitleScene()
	{
	}

	void TitleScene::Start()
	{
		setActive(true);
	}

	void TitleScene::Finish()
	{

	}

	void TitleScene::OnUpdate(float delta)
	{
		std::cout << "TitleScene OnUpdate()" << std::endl;
	}

	void TitleScene::OnRender()
	{

	}
}
