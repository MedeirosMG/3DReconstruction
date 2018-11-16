#include "stdafx.h"
#include "Import.h"
#include "Console.h"

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

	CameraProperties Import::CameraParameters(string pathDirectory)
	{
		vector<string> listSplitted_0;
		vector<string> listSplitted_cam0;
		vector<string> listSplitted_baseline;
		vector<string> listSplitted_width;
		vector<string> listSplitted_doffs;
		CameraProperties result;

		ifstream file;
		string line = "";
		int count = 0;
		file.open(pathDirectory);

		if (file.is_open()) {
			while (getline(file, line))
			{
				switch (count)
				{
					default:
						break;
					case 0: // cam0
						listSplitted_0 = StringHelper::Split(line, '[');
						listSplitted_cam0 = StringHelper::Split(listSplitted_0[1], ' ');
						break;
					case 2: // doffs
						listSplitted_doffs = StringHelper::Split(line, '=');
					case 3: // baseline
						listSplitted_baseline = StringHelper::Split(line, '=');
						break;
					case 4: // width
						listSplitted_width = StringHelper::Split(line, '=');
						break;
				}

				count++;
			}

			result.f = std::stof(listSplitted_cam0[0]);
			result.width = std::stof(listSplitted_width[1]);
			result.Lambda = std::stof(listSplitted_cam0[0]) / std::stof(listSplitted_width[1]);
			result.B = std::stof(listSplitted_baseline[1]);
			result.doffs = std::stof(listSplitted_doffs[1]);
			
			file.close();
		}

		Console::Print(result);

		return result;
	}

	vector<CameraProperties> Import::CameraParameters(vector<string> pathDirectory)
	{
		vector<CameraProperties> result;

		for each (string path in pathDirectory)
		{
			result.push_back(CameraParameters(path));
		}

		return result;
	}
}