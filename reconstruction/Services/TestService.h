#ifndef SERVICES_TEST
#define SERVICES_TEST
#include <iostream>
#include "ControllerService.h"
#include "..\Helpers\Time.h"
#include "..\Helpers\Console.h"


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
			void Reconstruction(int argc, char **argv);
			void Canny();
			void Firefly();
			void Render(int argc, char **argv);
			void Delaunay();
			void Ransac();
			void ConnectedComponents();
	};

}

#endif