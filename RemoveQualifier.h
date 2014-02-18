#pragma once

namespace sidescroll
{
	template <typename T>
	struct RemQual
	{
		typedef T type;
	};

	template <typename T>
	struct RemQual<const T>
	{
		typedef typename RemQual<T>::type type;
	};

	template <typename T>
	struct RemQual<T&>
	{
		typedef typename RemQual<T>::type type;
	};

	template <typename T>
	struct RemQual<const T&>
	{
		typedef typename RemQual<T>::type type;
	};

	template <typename T>
	struct RemQual<T&&>
	{
		typedef typename RemQual<T>::type type;
	};

	template <typename T>
	struct RemQual<const T *>
	{
		typedef typename RemQual<T *>::type type;
	};
}
