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
		//setDeserialize(function);
		//Deserialize(File("file.txt", "rb"));
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
