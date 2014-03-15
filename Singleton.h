#pragma once

namespace sidescroll
{
	/** Template class for creating single-instance global classes.
	*/
	template <typename T> class Singleton
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

	template<typename T>
	class MySingleton
	{
	public:
		MySingleton(){}
		virtual ~MySingleton(){}

		static T* GetSingleton(){
			if (nullptr == m_pInstance)
				m_pInstance.reset(new T);

			return m_pInstance.get();
		}

	private:
		static std::shared_ptr<T> m_pInstance;
	};
	template<typename T> std::shared_ptr<T> MySingleton<T>::m_pInstance = nullptr;
}
