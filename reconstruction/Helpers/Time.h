#ifndef HELPERS_TIME
#define HELPERS_TIME
#include <iostream>
#include <fstream>
#include <chrono>

#include "../Entities/TimeExecution.h"
#include "../Entities/TimeBuffer.h"

using namespace std;
using namespace Entities;
using namespace chrono;

namespace Helpers {

	class Time
	{
		private:
			vector<TimeExecution> _listMethodExecuted;
			vector<TimeBuffer> _bufferMethodExecuted;
			void Add(long time, string methodName);
			void AddBuffer(high_resolution_clock::time_point time, string methodName);

		public:
			Time();
			~Time();

			void Start(string methodName);
			void Stop(string methodName);
			void PrintResult();
			void PrintResult(string methodName);
	};
}

#endif