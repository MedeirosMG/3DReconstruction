#include "stdafx.h"
#include "ExportVtk.h"

namespace Helpers {
	ExportVtk::ExportVtk()
	{
	}

	ExportVtk::~ExportVtk()
	{
	}

	bool ExportVtk::ExportObj(vtkActor * a, string pathDirectory, string filename)
	{
		try
		{
			int b = 1;
			FILE * fpObj = NULL;
			FILE * fpMat = NULL;
			string pathObj = pathDirectory + "\\" + filename + "_obj.obj";
			string pathMtl = pathDirectory + "\\" + filename + "_mat.mtl";

			
			fpObj = fopen(pathObj.c_str(), "w");
			fpMat = fopen(pathMtl.c_str(), "w");

			WriteAnActor(a, fpObj, fpMat, b);
			fclose(fpObj);
			fclose(fpMat);

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}
}