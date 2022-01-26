#pragma once

#include "files/File.h"


struct Argument;


ItemLocation parseLocStr(const std::vector<Argument>& command, size_t idx);

const fs::path categoryPath(size_t cIndex) noexcept;

void printFile(const fs::path& filepath);