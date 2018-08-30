#ifndef SERVICES_TEST
#define SERVICES_TEST
#include <iostream>
#include "ControllerService.h"
#include "..\Helpers\Time.h"

using namespace std;
using namespace Helpers;

namespace Services {

	class TestService
	{
		private:
			Time* _time;

		public:
			TestService();
			~TestService();
			void TimeExecution();
			void Reconstruction(int argc, char **argv);
	};

}

#endif