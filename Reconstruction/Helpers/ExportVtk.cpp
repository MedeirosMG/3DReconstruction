#include "stdafx.h"
#include "ExportVtk.h"

namespace Helpers {
	ExportVtk::ExportVtk()
	{
	}

	ExportVtk::~ExportVtk()
	{
	}

	bool ExportVtk::ExportObj(vtkActor * a, string path_export)
	{
		try
		{
			int b = 1;
			FILE * fpObj = NULL;
			FILE * fpMat = NULL;
			string pathObj = path_export + ".obj";
			string pathMtl = path_export + ".mtl";

			
			fpObj = fopen(pathObj.c_str(), "w");
			fpMat = fopen(pathMtl.c_str(), "w");

			WriteAnActor(a, fpObj, fpMat, b);
			fclose(fpObj);
			fclose(fpMat);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export OBJ: " << ex.what() << endl;
			return false;
		}
	}
}