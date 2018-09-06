#include "stdafx.h"
#include "Time.h"

namespace Helpers {

	Time::Time()
	{
	}

	Time::~Time()
	{
	}

	void Time::Add(long time, string methodName) {
		bool existMethod = false;
		for each (TimeExecution method in _listMethodExecuted)
		{
			if (method.GetName() == methodName) {
				existMethod = true;
				method.Add(time);
				break;
			}
		}

		if (!existMethod) {
			TimeExecution* obj = new TimeExecution(methodName);
			obj->Add(time);
			_listMethodExecuted.push_back(*obj);
		}
	}
	
	void Time::Run(std::function<void()> callback, string methodName) {
		high_resolution_clock::time_point start = high_resolution_clock::now();
		callback();
		high_resolution_clock::time_point end = high_resolution_clock::now();

		long duration = duration_cast<microseconds>(end - start).count();

		Add(duration, methodName);
	}

	void Time::PrintResult()
	{
		cout << "============== Start Print Time Execution ==============" << endl;

		for each (TimeExecution method in _listMethodExecuted)
		{
			method.PrintTimeExecution();
		}

		cout << "============= Finish Print Time Execution ==============" << endl;
	}

	void Time::PrintResult(string methodName)
	{
		for each (TimeExecution method in _listMethodExecuted)
		{
			if (method.GetName() == methodName) {
				method.PrintTimeExecution();
			}
		}
	}	
}