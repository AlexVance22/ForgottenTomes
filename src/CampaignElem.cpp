#include "PCH.h"

#include "CampaignElem.h"

#include "File.h"


template<typename Elem>
std::vector<std::string> getRefs(const Elem& ses) {}

template<>
std::vector<std::string> getRefs<Session>(const Session& ses)
{
	for (const auto& el : ses.elems)
	{
		std::ifstream stream(el);

		File::Get().path;
	}

	return {};
}

template<>
std::vector<std::string> getRefs<Location>(const Location& ses)
{
	return {};
}

template<>
std::vector<std::string> getRefs<Character>(const Character& ses)
{
	return {};
}



std::vector<CampaignElem*> findRefs(nlohmann::json const* refNames)
{
	return {};
}