//
// Kernel Object
//
#include "Directory.hpp"
#include "../kdebug.hpp"

using namespace Chino;

void Directory::AddItem(std::string_view name, Object & obj)
{
	items_.emplace(name, &obj);
}

ObjectAccessor<Object> Directory::Open(std::string_view name, ObjectAccess access)
{
	ObjectAccessContext context{ access };
	auto it = items_.find(std::string(name));
	kassert(it != items_.end());
	auto obj = it->second;
	obj->Open(context);
	return { std::move(context), std::move(obj) };
}
