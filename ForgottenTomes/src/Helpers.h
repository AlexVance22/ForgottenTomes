#pragma once

#include "Files/File.h"


struct Argument;


bool parseLocStr(ItemLocation& loc, const std::vector<Argument>& command, size_t idx);

std::string categoryPath(size_t cIndex);

void printFile(const std::string& filepath);