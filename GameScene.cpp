#include "Precompiled.h"

void GameScene::Init()
{
	m_space = new Space;
	m_space->Init();
}

void GameScene::Destroy()
{
	m_space->Destroy();
	SDELETE(m_space);
}

void GameScene::Update(float delta)
{
	m_space->Update(delta);
}

void GameScene::Render()
{
	m_space->Render();
}
