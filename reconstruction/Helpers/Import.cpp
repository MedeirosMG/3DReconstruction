#include "stdafx.h"
#include "Import.h"

namespace Helpers {

	Import::Import()
	{

	}

	Import::~Import()
	{
	}

	vector<TimeExecution> Import::Csv(string pathDirectory)
	{
		vector<TimeExecution> result;
		string line = "";
		bool titleLine = false;
		ifstream file;
		file.open(pathDirectory + "\\time_execution.csv");

		if (file.is_open()) {
			while (getline(file, line))
			{
				vector<string> listSplitted = StringHelper::Split(line, ';');
				if (!titleLine) {
					for each (string name in listSplitted)
					{
						result.push_back(*new TimeExecution(name));
					}

					titleLine = true;
				}
				else {
					for (int i = 0; i < listSplitted.size(); i++)
					{
						result[i].Add(stol(listSplitted[i]));
					}
				}
			}
	
			file.close();
		}

		return result;
	}
}