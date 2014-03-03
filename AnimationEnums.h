#pragma once

namespace sidescroll
{
	enum EWrapMode
	{
		Once, // 한번 재생
		Loop, // 반복 플레이
		Default, // 디폴트 설정값
		PingPong, // 한번 정방 재생되고 다시 역방으로 재생 루프
		ClampForever // 한번만 플레이되고 마지막 모션에 고정된다.
	};
}
