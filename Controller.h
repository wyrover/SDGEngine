/*
Copyright (c) 2013 bodguy http://blog.naver.com/bodguy

Creator(s)    : bodguy
Creation Date : 2014-02-18
File Name     : Controller.h
license		  : LGPL v3.0
Purpose       :
*/

#pragma once

class Controller : public Behaviour
{
public:
	Controller();
	virtual ~Controller();

	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update(float delta) override;
	virtual void Render() override;

	virtual EMessageResult HandleMessage(const Message &msg) override;
};
