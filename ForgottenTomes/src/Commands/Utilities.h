#pragma once

struct Argument;


void viewElement(size_t cIndex, int eIndex);

void viewArticle(size_t cIndex, int eIndex, int aIndex);


void cmdList(const std::vector<Argument>& command);

bool cmdSelect(const std::vector<Argument>& command);

bool cmdView(const std::vector<Argument>& command);