#pragma once

struct Argument;
struct ItemLocation;


void viewCategory(const ItemLocation& loc);

void viewElement(const ItemLocation& loc);

void viewArticle(const ItemLocation& loc);


void cmdList(const std::vector<Argument>& command);

void cmdSelect(const std::vector<Argument>& command);

void cmdView(const std::vector<Argument>& command);