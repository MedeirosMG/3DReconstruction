#ifndef ENTITIES_TIME_EXECUTION
#define ENTITIES_TIME_EXECUTION

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace Entities {
	class TimeExecution
	{
		private:
			string _name;
			vector<long> _bufferTimeExecution;

		public:
			TimeExecution(string name);
			~TimeExecution();
			void Add(long timeMilliseconds);
			string GetName();
			void PrintTimeExecution();
	};
}

#endif