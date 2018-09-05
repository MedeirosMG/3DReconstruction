#ifndef ENTITIES_TIME_BUFFER
#define ENTITIES_TIME_BUFFER

#include <iostream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;

namespace Entities {
	class TimeBuffer
	{
		private:
			string _name;
			vector<high_resolution_clock::time_point> _bufferTimeExecution;

		public:
			TimeBuffer(string name);
			~TimeBuffer();
			void Add(high_resolution_clock::time_point time);
			high_resolution_clock::time_point GetLast();
			string GetName();
	};
}

#endif