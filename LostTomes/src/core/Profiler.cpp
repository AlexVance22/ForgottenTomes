#include "PCH.h"
#include "Profiler.h"

using namespace std::chrono;


Profiler::Profiler()
{
	m_begin = high_resolution_clock::now();
	m_results.push_back(0);
}

Profiler::~Profiler()
{
	if (m_tracking)
		m_results[m_results.size() - 1] += duration_cast<microseconds>(high_resolution_clock::now() - m_begin).count();

	for (long long step : m_results)
		std::cout << step << "\tmicroseconds\n";
}


void Profiler::step()
{
	if (m_tracking)
	{
		m_results[m_results.size() - 1] += duration_cast<microseconds>(high_resolution_clock::now() - m_begin).count();
		m_begin = high_resolution_clock::now();
	}

	m_results.push_back(0);
}


void Profiler::pause()
{
	m_results[m_results.size() - 1] += duration_cast<microseconds>(high_resolution_clock::now() - m_begin).count();
	m_tracking = false;
}

void Profiler::resume()
{
	m_begin = high_resolution_clock::now();
	m_tracking = true;
}