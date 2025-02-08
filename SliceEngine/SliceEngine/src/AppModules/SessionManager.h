#ifndef SLICE_SESSION_MANAGER
#define SLICE_SESSION_MANAGER

namespace SliceEngine
{
	class SessionManager
	{
		TimePoint m_SessionStartTime;
		TimePoint m_SessionCurrentTime;

	public:
		SessionManager(TimePoint& start_time);

		void UpdateTime();

		double GetDurationInMilliseconds();
	};
}

#endif