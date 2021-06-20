#pragma once

#include "CMDenums.h"
#include "Files/File.h"


bool findItem(ItemLocation& loc, const std::vector<int>& command, size_t startIndex);

void appendCategory(std::string& base, size_t fIndex);

void printFile(const std::string& fileName);

bool listElements(ARG code);