#include "../src/pch.h"
#include "SessionManager.h"

namespace SliceEngine
{
	SessionManager::SessionManager(TimePoint& start_time) :
		m_SessionStartTime(start_time),
		m_SessionCurrentTime(start_time)
	{

	}

	void SessionManager::Init()
	{

	}

	void SessionManager::Update()
	{
		UpdateTime();
	}

	void SessionManager::Exit()
	{

	}

	SessionManager::~SessionManager()
	{
		
	}

	void SessionManager::UpdateTime()
	{
		m_SessionCurrentTime = TimePoint::clock::now();
	}

	double SessionManager::GetDurationInMilliseconds()
	{
		return std::chrono::duration<double>(m_SessionCurrentTime - m_SessionStartTime).count();
	}
}

