#ifndef _AlarmEnum
#define _AlarmEnum

class AlarmEnum
{
public:
	AlarmEnum() {};
	~AlarmEnum() {};
	AlarmEnum(const AlarmEnum&) = delete;
	AlarmEnum& operator=(const AlarmEnum&) = delete;

	enum AlarmID
	{
		Alarm_0,
		Alarm_1,
		Alarm_2
	};

};

#endif // !_AlarmEnum
