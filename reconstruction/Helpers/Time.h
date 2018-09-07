#ifndef HELPERS_TIME
#define HELPERS_TIME
#include <iostream>
#include <fstream>
#include <chrono>
#include <functional>
#include "../Entities/TimeExecution.h"
#include "../Helpers/Export.h"
#include "../Helpers/Import.h"

using namespace std;
using namespace Entities;
using namespace chrono;

namespace Helpers {
	// Circular including
	class Export;
	class Import;

	class Time
	{
		private:
			vector<TimeExecution> _listMethodExecuted;
			void Add(long time, string methodName);

		public:
			Time();
			~Time();

			vector<TimeExecution> Get();
			void Run(std::function<void()> callback, string methodName);
			void PrintResult();
			void PrintResult(string methodName);
			void Export(string path);
			void Import(string path);
	};
}

#endif