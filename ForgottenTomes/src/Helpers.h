#pragma once

#include "CMDenums.h"
#include "Files/File.h"


bool parseLocStr(ItemLocation& loc, const std::vector<int>& command, size_t idx);

std::string categoryPath(size_t cIndex);

void printFile(const std::string& filepath);

bool listElements(ARG code);