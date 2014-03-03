#pragma once

namespace sidescroll
{
	class AudioAsset : public Asset
	{
	public:
		AudioAsset();
		virtual ~AudioAsset();

		bool Load(const std::string &filename);
		virtual void Reload() override;
		virtual void Unload() override;
	};
}
