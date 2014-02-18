#include "Precompiled.h"

namespace sidescroll
{
	Controller::Controller()
	{

	}

	Controller::~Controller()
	{

	}

	void Controller::Init()
	{

	}

	void Controller::Destroy()
	{

	}

	void Controller::Update(float delta)
	{

	}

	void Controller::Render()
	{

	}

	EMessageResult Controller::HandleMessage(const Message &msg)
	{
		switch (msg.m_type)
		{
		case MT_OBJECT_CREATED:

			return MR_TRUE;
		case MT_UPDATE:

			return MR_TRUE;
		}

		return MR_IGNORED;
	}
}
