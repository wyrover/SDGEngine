#pragma once

namespace SDGEngine
{
	/** Template class for creating single-instance global classes.
	*/
	template<typename T>
	class Singleton
	{
	public:
		Singleton() {}
		virtual ~Singleton() {}

		static T* GetSingleton(){
			if (NULL == m_pInstance)
				m_pInstance.reset(new T);

			return m_pInstance.get();
		}

	private:
		static std::shared_ptr<T> m_pInstance;
	};
	template<typename T> std::shared_ptr<T> Singleton<T>::m_pInstance = NULL;
}
