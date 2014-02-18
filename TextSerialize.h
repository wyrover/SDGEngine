#pragma once

namespace sidescroll
{
	void Padding(std::ostream& os);
	void TextSerialize(std::ostream& os, RefVariable var);

	template <typename T>
	void TextSerializePrim(std::ostream& os, RefVariable prim)
	{
		Padding(os);
		os << prim.GetValue<RemQual<T>::type>() << std::endl;
	}
}
