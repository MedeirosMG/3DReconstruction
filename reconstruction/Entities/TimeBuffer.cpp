#include "stdafx.h"
#include "TimeBuffer.h"

namespace Entities {

	TimeBuffer::TimeBuffer(string name) {
		_name = name;
	}

	TimeBuffer::~TimeBuffer()
	{
	}

	void TimeBuffer::Add(high_resolution_clock::time_point time)
	{
		_bufferTimeExecution.push_back(time);
	}

	string TimeBuffer::GetName()
	{
		return _name;
	}

	high_resolution_clock::time_point TimeBuffer::GetLast() {
		return _bufferTimeExecution[_bufferTimeExecution.size()];
	}
}