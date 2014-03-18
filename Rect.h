#pragma once

namespace SDGEngine
{
	class Rect
	{
	public:
		Rect();
		~Rect();

		Rect(const float _left, const float _top, const float _right, const float _bottom);
		Rect(const Rect &rhs);
		Rect &operator =(const Rect &rhs);
		Rect &operator +=(float x);
		Rect &operator -=(float x);
		Rect &operator *=(float x);
		Rect &operator /=(float x);
		bool operator ==(const Rect &rhs);
		bool operator !=(const Rect &rhs);

		void SetRect(const float _left, const float _top, const float _right, const float _bottom);

	public:
		float left, right;
		float top, bottom;
	};
}
