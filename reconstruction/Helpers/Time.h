#ifndef HELPERS_TIME
#define HELPERS_TIME
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include "../Entities/TimeExecution.h"

using namespace std;
using namespace Entities;
using namespace chrono;

namespace Helpers {

	class Time
	{
		private:
			vector<TimeExecution> _listMethodExecuted;
			void Add(long time, string methodName);

		public:
			Time();
			~Time();

			void PrintResult();
			void PrintResult(string methodName);
			void Run(std::function<void()> callback, string methodName);
	};
}

#endif