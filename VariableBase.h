#pragma once

namespace SDGEngine
{
	class VariableBase
	{
	public:
		template<typename T>
		T& GetValue();
		template<typename T>
		const T& GetValue() const;
		const MetaData *Meta() const;
		void *Data() const;
		void SetData(void *d);

		void Serialize(std::ostream& os) const;

	protected:
		VariableBase(void);
		VariableBase(const MetaData *m, void *d);
		const MetaData *meta;
		void *data;
	};

	// 이거 안하면 포인터를 제대로 받지 못함
	template <typename T>
	struct CastHelper
	{
		static T& Cast(void *& data)
		{
			return *(T *&)(data);
		}
	};

	template <typename T>
	struct CastHelper<T *>
	{
		static T *& Cast(void *& data)
		{
			return (T *&)data;
		}
	};

	template<typename T>
	const T& VariableBase::GetValue() const
	{
		return CastHelper<T>::Cast(data);
	}

	template<typename T>
	T& VariableBase::GetValue()
	{
		assert(META_TYPE(T) == meta);
		return CastHelper<T>::Cast(data);
	}
}
