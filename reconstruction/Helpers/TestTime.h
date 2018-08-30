#pragma once
class TestTime
{
	public:
		TestTime();
		~TestTime();

		static void Run(void(*ptr)());
};

