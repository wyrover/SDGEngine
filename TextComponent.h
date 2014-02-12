#pragma once

class TextComponent : public Component
{
public:
	TextComponent();
	virtual ~TextComponent();

	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Update(float delta) override;
	virtual void Render() override;
	virtual EMessageResult HandleMessage(const Message &) override;

	void setText(std::string str) { text = str; }

private:
	std::string text;
};
