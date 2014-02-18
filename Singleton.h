#pragma once

namespace sidescroll
{
	/** Template class for creating single-instance global classes.
	*/
	template <typename T>
	class Singleton
	{
	protected:
		static T* msSingleton;

	public:
		Singleton(){
			assert(!msSingleton);
			msSingleton = static_cast<T*>(this);
		}
		~Singleton(){
			assert(msSingleton);
			msSingleton = 0;
		}
		static T& getSingleton(){
			assert(msSingleton);
			return (*msSingleton);
		}
		static T* getSingletonPtr(){
			return msSingleton;
		}
	};
}
