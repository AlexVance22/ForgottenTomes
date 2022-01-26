#pragma once


struct FileNotFound : public std::runtime_error
{
	bool silent;

	FileNotFound(const char* what, bool _silent = false)
		: std::runtime_error(what), silent(_silent)
	{}
};


struct InvalidCategory : public std::out_of_range
{
public:
	InvalidCategory(const char* what)
		: std::out_of_range(what)
	{}
};


struct InvalidElement : public std::out_of_range
{
	InvalidElement(const char* what)
		: std::out_of_range(what)
	{}
};


struct InvalidArticle : public std::out_of_range
{
	InvalidArticle(const char* what)
		: std::out_of_range(what)
	{}
};


struct InvalidArgument : public std::invalid_argument
{
	InvalidArgument(const char* what)
		: std::invalid_argument(what)
	{}
};