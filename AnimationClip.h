#pragma once

namespace sidescroll
{
	class AnimationClip
	{
	public:
		AnimationClip(const std::string &name, int start, int end, float speed) 
			: name(name), start(start), end(end), speed(speed), frame(start), isPlaying(false) {}
		virtual ~AnimationClip() {}

		bool isPlaying;
		std::string name;
		int frame;
		float speed;
		int start;
		int end;
	};
}
