#include "stdafx.h"
#include "TimeExecution.h"

namespace Entities {

	TimeExecution::TimeExecution(string name) {
		_name = name;
	}

	TimeExecution::~TimeExecution()
	{
	}

	void TimeExecution::Add(long timeMilliseconds)
	{
		_listTimeExecution.push_back(timeMilliseconds);
	}

	string TimeExecution::GetName()
	{
		return _name;
	}

	void TimeExecution::PrintTimeExecution()
	{
		cout << "============== Time Execution ============ " << endl;
		cout << ">> Method: " << _name << " | Attempts: " << _listTimeExecution.size() << endl;
		
		int cont = 0;
		for each (long time in _listTimeExecution)
		{
			cout << "[" << cont <<"] Time Execution: " << time << " ms" << endl;
		}

		cout << "========================================== " << endl;
	}

}