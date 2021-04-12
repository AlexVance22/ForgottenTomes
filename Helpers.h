#pragma once

#include "CMDenums.h"


struct ItemLocation
{
	int folderIndex = -1;
	int elementIndex = -1;
	int componentIndex = -2;
};


bool findItem(ItemLocation& loc, const std::vector<int>& command, size_t startIndex);


bool listElements(ARG code);