#ifndef SLICE_SESSION_MANAGER
#define SLICE_SESSION_MANAGER

#include "Common.h"

namespace SliceEngine
{
	class SessionManager : IModule
	{
		TimePoint m_SessionStartTime;
		TimePoint m_SessionCurrentTime;

		void UpdateTime();


	public:
		SessionManager(TimePoint& start_time);

		void Init() override;
		void Update() override;
		void Exit() override;

		double GetDurationInMilliseconds();

		~SessionManager();
	};
}

#endif