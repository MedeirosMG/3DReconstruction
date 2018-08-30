#include "..\stdafx.h"
#include "TestTime.h"


TestTime::TestTime()
{
}


TestTime::~TestTime()
{
}

void TestTime::Run(void(*ptr)())
{
	(*ptr) ();
}
