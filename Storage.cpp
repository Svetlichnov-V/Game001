#pragma once
#include "Storage.h"

std::ostream& operator << (std::ostream& streamP, const GameObject& object)
{
	streamP << object.position << ' ' << object.name << std::endl;
	return streamP;
}

std::ostream& operator << (std::ostream& streamP, Storage& stor)
{
	Iterator iter(&stor);
	GameObject object = iter.stepIteration();
	while (object.name != "NULL")
	{
		streamP << object << std::endl;
		object = iter.stepIteration();
	}
	return streamP;
}