#pragma once

#include "CMDenums.h"
#include "Files/File.h"


bool parseLocStr(ItemLocation& loc, const std::vector<int>& command, size_t idx);

void appendCategory(std::string& base, size_t cIndex);

void printFile(const std::string& fileName);

bool listElements(ARG code);