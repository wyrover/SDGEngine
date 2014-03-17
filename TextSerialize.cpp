#include "Precompiled.h"

namespace SDGEngine
{
	// Takes a pointer and returns a pointer offset in bytes
#define PTR_ADD( PTR, OFFSET ) \
	((void *)(((char *)(PTR)) + (OFFSET)))

	static unsigned level = 0;

	void Padding(std::ostream& os)
	{
		for (unsigned i = 0; i < level; ++i)
			os << "  ";
	}

	void TextSerialize(std::ostream& os, RefVariable var)
	{
		const MetaData *meta = var.Meta();
		void *data = var.Data();

		assert(meta->HasMembers()); // This type does not have a SerializePrim associated with it for some reason.

		os << meta->Name() << std::endl;

		const Member *mem = meta->Members();
		Padding(os);
		os << "{" << std::endl;

		while (mem)
		{
			++level;
			void *offsetData = PTR_ADD(var.Data(), mem->Offset());
			mem->Meta()->Serialize(os, RefVariable(mem->Meta(), offsetData));
			mem = mem->Next();
			--level;
		}

		Padding(os);
		os << "}" << std::endl;
	}
}
