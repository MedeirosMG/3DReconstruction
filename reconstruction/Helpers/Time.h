#ifndef HELPERS_TIME
#define HELPERS_TIME
#include <iostream>
#include <fstream>
#include <chrono>

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

			void Run(void(*callback)());
			void Run(bool(*callback)());
			void Run(void(*callback)(), string methodName);
			void Run(bool(*callback)(), string methodName);
			void PrintResult();
			void PrintResult(string methodName);
	};
}

#endif