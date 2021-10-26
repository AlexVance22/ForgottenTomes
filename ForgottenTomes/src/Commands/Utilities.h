#pragma once


void viewElement(size_t cIndex, int eIndex);

void viewArticle(size_t cIndex, int eIndex, int aIndex);


void cmdList(const std::vector<int>& command);

bool cmdSelect(const std::vector<int>& command);

bool cmdView(const std::vector<int>& command);