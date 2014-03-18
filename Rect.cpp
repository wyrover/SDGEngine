#include "Precompiled.h"

namespace SDGEngine
{
	Rect::Rect()
		:left(0.f), right(0.f), top(0.f), bottom(0.f)
	{
	}

	Rect::~Rect()
	{
	}

	Rect::Rect(const float _left, const float _top, const float _right, const float _bottom)
	{
		left = _left;
		right = _right;
		top = _top; 
		bottom = _bottom;
	}

	Rect::Rect(const Rect &rhs)
	{
		left = rhs.left;
		right = rhs.right;
		top = rhs.top;
		bottom = rhs.bottom;
	}

	Rect & Rect::operator=(const Rect &rhs)
	{
		left = rhs.left;
		right = rhs.right;
		top = rhs.top;
		bottom = rhs.bottom;

		return *this;
	}

	void Rect::SetRect(const float _left, const float _top, const float _right, const float _bottom)
	{
		left = _left;
		right = _right;
		top = _top;
		bottom = _bottom;
	}

	Rect & Rect::operator+=(float x)
	{
		left += x;
		right += x;
		top += x;
		bottom += x;

		return *this;
	}

	Rect & Rect::operator-=(float x)
	{
		left -= x;
		right -= x;
		top -= x;
		bottom -= x;

		return *this;
	}

	Rect & Rect::operator*=(float x)
	{
		left *= x;
		right *= x;
		top *= x;
		bottom *= x;

		return *this;
	}

	Rect & Rect::operator/=(float x)
	{
		left /= x;
		right /= x;
		top /= x;
		bottom /= x;

		return *this;
	}

	bool Rect::operator==(const Rect &rhs)
	{
		if (left == rhs.left && 
			right == rhs.right &&
			top == rhs.top &&
			bottom == rhs.bottom) {
			return true;
		}

		return false;
	}

	bool Rect::operator!=(const Rect &rhs)
	{
		if (left == rhs.left &&
			right == rhs.right &&
			top == rhs.top &&
			bottom == rhs.bottom) {
			return false;
		}

		return true;
	}
}
