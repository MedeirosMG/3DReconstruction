#include "stdafx.h"
#include "Export.h"

namespace Helpers {

	Export::Export()
	{

	}
	
	Export::~Export()
	{
	}
	
	bool Export::Json(vector<Point3f> listPoints, string pathDirectory)
	{
		try
		{
			int raiz = sqrt(listPoints.size());
			int column = raiz + 1, line = listPoints.size();
			int range = raiz;
			if (raiz > 10)
				range = raiz * 0.8;
			if (raiz > 100)
				range = raiz * 0.4;
			if (raiz > 1000)
				range = raiz * 0.005;
			if (raiz > 10000)
				range = raiz * 0.0005;

			int bestLine = raiz, bestColumn = raiz;
			while (range > 0) {
				if (column * line < listPoints.size()) {
					bestLine = line;
					bestColumn = column;
				}
				column--;
				line++;
				range--;
			}

			ofstream file;
			file.open(pathDirectory + "\\stereoCameraCalibration.json");
			file << "{\"Column\": " + to_string(bestColumn);
			file << ", ";
			file << "\"Line\": " + to_string(bestLine);
			file << ", ";
			file << "\"Values\": [";
			for each (Point3f item in listPoints)
			{
				file << "{ " << "\"X\": " << item.x << ", \"Y\": " << item.y << ", \"Z\": " << item.z << "},";
			}
			file << "]}";
			file.close();
		}
		catch (const std::exception&)
		{
			return false;
		}

		return true;
	}

	bool Export::Obj(vector<Point3f> listPoints, string pathDirectory)
	{
		try
		{
			int raiz = sqrt(listPoints.size());
			int column = raiz + 1, line = listPoints.size();
			int range = raiz;
			if (raiz > 10)
				range = raiz * 0.8;
			if (raiz > 100)
				range = raiz * 0.4;
			if (raiz > 1000)
				range = raiz * 0.005;
			if (raiz > 10000)
				range = raiz * 0.0005;

			int bestLine = raiz, bestColumn = raiz;
			while (range > 0) {
				if (column * line < listPoints.size()) {
					bestLine = line;
					bestColumn = column;
				}
				column--;
				line++;
				range--;
			}

			ofstream file;
			file.open(pathDirectory + "\\stereoCameraCalibration.obj");
			file << "L " << to_string(bestLine) << endl;
			file << "C " << to_string(bestColumn) << endl;

			for each (Point3f item in listPoints)
			{
				file << "v " << item.x << " " << item.y << " " << item.z << endl;
			}

			file.close();
		}
		catch (const std::exception&)
		{
			return false;
		}

		return true;
	}

	bool Export::Csv(Helpers::Time time, string pathDirectory, string filename)
	{
		try
		{
			vector<TimeExecution> list = time.Get();
			vector<vector<string>> excelValues;
			string exportText = "";
			string splitter = ";";
			int maxQtd = 0;
			ofstream file;

			file.open(pathDirectory + "\\" + filename);
			if (file.is_open()) {
				// setting columns name on csv
				for (int i = 0; i < list.size(); i++)
				{
					exportText += list[i].GetName();
					int sizeMethod = list[i].Get().size();
					if (sizeMethod > maxQtd)
						maxQtd = sizeMethod;

					if ((i + 1) != list.size()) {
						exportText += splitter;
					}
				}
				exportText += "\n";

				// bulding matriz
				for (int i = 0; i < list.size(); i++)
				{
					// each method
					vector<long> listTimes = list[i].Get();
					for (int j = 0; j < listTimes.size(); j++)
					{
						// each time inside each method
						if (excelValues.size() <= j)
							excelValues.push_back(*new vector<string>());

						excelValues[j].push_back(to_string(listTimes[j]));
					}
				}

				// setting values on csv
				for each (vector<string> row in excelValues)
				{
					for each (string col in row)
					{
						exportText += col + splitter;
					}

					exportText += "\n";
				}

				file << exportText;
				
				file.close();
			}
						
			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}

	bool Export::Csv(vector<ReconstructionComparison> reconstructionComparison, string pathDirectory, string filename, string coordinates)
	{
		try
		{
			if (coordinates == "")
				throw exception("Coordinates cannot be null or empty");

			string exportText = "";
			string splitter = ";";
			string data = "";
			ofstream file;

			file.open(pathDirectory + "\\" + filename);
			if (file.is_open()) {
				// setting header
				for (char& c : coordinates) {
					string coord(&c);
					string header = "Reconstruction Coord " + coord + splitter + "Map Coord " + coord + splitter + "Error " + coord + splitter;

					StringHelper::Append(exportText, header);
				}

				StringHelper::Append(exportText, "\n");

				// setting data
				for each (ReconstructionComparison item in reconstructionComparison)
				{
					for (char& c : coordinates) {
						switch (c)
						{
							case 'x':
								data = to_string(item.Reconstruction.x) + splitter + to_string(item.Map.x) + splitter + to_string(item.Error.x) + splitter;
								break;
							case 'y':
								data = to_string(item.Reconstruction.y) + splitter + to_string(item.Map.y) + splitter + to_string(item.Error.y) + splitter;
								break;
							case 'z':
								data = to_string(item.Reconstruction.z) + splitter + to_string(item.Map.z) + splitter + to_string(item.Error.z) + splitter;
								break;
						}

						StringHelper::Append(exportText, data);
					}

					StringHelper::Append(exportText, "\n");
				}
			}

			file << exportText;

			file.close();

			return true;
		}
		catch (const std::exception& ex)
		{
			cout << "Exception Export CSV: " << ex.what() << endl;
			return false;
		}
	}
}