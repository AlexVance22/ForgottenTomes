#pragma once


class Profiler
{
private:
	std::chrono::steady_clock::time_point m_begin;
	std::vector<long long> m_results;
	bool m_tracking = true;

public:
	Profiler();
	~Profiler();

	void step();

	void pause();
	void resume();
};