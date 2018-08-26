#include "stdafx.h"
#include "CalibrationService.h"

namespace Services {

	CalibrationService::CalibrationService(float b, float lambda, OpenCV* openCv, int k) : _b(b), _lambda(lambda), _k(k) {
		_openCv = openCv;
	}

	CalibrationService::CalibrationService(OpenCV* openCv)
	{
		_openCv = openCv;
	}

	CalibrationService::~CalibrationService()
	{
	}

	bool xComparator(const CustomPoint & e1, const CustomPoint & e2) {
		return (e1.X > e2.X);
	}

	bool yComparator(const CustomPoint & e1, const CustomPoint & e2) {
		return (e1.Y > e2.Y);
	}

	bool zComparator(const CustomPoint & e1, const CustomPoint & e2) {
		return (e1.Z > e2.Z);
	}

	bool Comparator(const CustomPoint & e1, const CustomPoint & e2) {
		return (e1.X == e2.X ? e2.Y < e2.Y : e1.X < e2.X);
	}

	vector<CustomPoint> CalibrationService::CalculateStereoCameraCalibrationUsingNeighbours(vector<CustomPoint>listPointsFrame1, vector<CustomPoint> listPointsFrame2)
	{
		vector<PointPair> listResultRelativesPoints;
		int index = 0;
		for each (CustomPoint item in listPointsFrame1)
		{
			vector<CustomPoint> listNeighboursPoints = GetNeighbourPoints(listPointsFrame2, index);
			CustomPoint neighbour = BestNeighbour(item, listNeighboursPoints);

			listResultRelativesPoints.push_back(*(new PointPair(item, neighbour)));

			index++;
		}

		return CalculateListRealPoints(listResultRelativesPoints);
	}

	vector<CustomPoint> CalibrationService::CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints)
	{
		return CalculateListRealPoints(listMatchPoints);
	}

	vector<CustomPoint> CalibrationService::CalculateListRealPoints(vector<PointPair> listPoints)
	{
		//PivelToCoordinate(listPoints);
		//ChangeScale(listPoints);
		//PrintResult(listPoints);

		vector<CustomPoint> listRealPoints;

		for each (PointPair item in listPoints)
		{
			listRealPoints.push_back(*(CalculateRealPoint(item.FirstPoint, item.SecondPoint)));
		}

		//ChangeScale(listRealPoints);

		return listRealPoints;
	}

	float CalibrationService::CalculateEuclideanDistance(CustomPoint firstPoint, CustomPoint secondPoint)
	{
		return sqrt(pow((firstPoint.X - secondPoint.X), 2) + pow((firstPoint.Y - secondPoint.Y), 2));
	}

	CustomPoint* CalibrationService::CalculateRealPoint(CustomPoint firstPoint, CustomPoint secondPoint) {
		float WorldZ = 0, WorldY = 0, WorldX = 0;
		WorldZ = this->WorldPointZ(firstPoint, secondPoint);
		WorldY = this->WorldPointY(firstPoint.Y, WorldZ);
		WorldX = this->WorldPointX(firstPoint.X, WorldZ);

		CustomPoint* WorldPoint = new CustomPoint(WorldX, WorldY, WorldZ);

		return WorldPoint;
	}

	void CalibrationService::PrintResult(vector<CustomPoint> listPoints)
	{
		cout << "============================= Result =============================" << endl;
		int count = 1;
		for each (CustomPoint item in listPoints)
		{
			if (count < 10)
				cout << "P[0" << count << "] = { " << item.X << " ; " << item.Y << " ; " << item.Z << " } " << endl;
			else
				cout << "P[" << count << "] = { " << item.X << " ; " << item.Y << " ; " << item.Z << " } " << endl;
			count++;
		}
		cout << "==================================================================" << endl;
	}

	void CalibrationService::PrintResult(vector<PointPair> listPoints)
	{
		cout << "================================== Print PointPair ========================================" << endl;
		int count = 1;
		for each (PointPair item in listPoints)
		{
			if (count < 10)
				cout << "[0" << count << "] FirstPoint : { " << item.FirstPoint.X << " ; " << item.FirstPoint.Y << " } - SecondPoint : { " << item.SecondPoint.X << " ; " << item.SecondPoint.Y << " }" << endl;
			else
				cout << "[" << count << "] FirstPoint : { " << item.FirstPoint.X << " ; " << item.FirstPoint.Y << " } - SecondPoint : { " << item.SecondPoint.X << " ; " << item.SecondPoint.Y << " }" << endl;
			count++;
		}
		cout << "===========================================================================================" << endl;
	}

	void CalibrationService::PrintResult(CustomPoint point)
	{
		cout << "============================= Result =============================" << endl;
		cout << "Point = { " << point.X << " ; " << point.Y << " ; " << point.Z << " } " << endl;
		cout << "==================================================================" << endl;
	}

	bool CalibrationService::ExportToJson(vector<CustomPoint> listPoints, string pathDirectory)
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
			string test = "{\"Column\": " + to_string(column);
			file << "{\"Column\": " + to_string(bestColumn);
			file << ", ";
			file << "\"Line\": " + to_string(bestLine);
			file << ", ";
			file << "\"Values\": [";
			for each (CustomPoint item in listPoints)
			{
				file << "{ " << "\"X\": " << item.X << ", \"Y\": " << item.Y << ", \"Z\": " << item.Z << "},";
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

	bool CalibrationService::ExportToObj(vector<CustomPoint> listPoints, string pathDirectory)
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

			for each (CustomPoint item in listPoints)
			{
				file << "v " << item.X << " " << item.Y << " " << item.Z << endl;
			}

			file.close();
		}
		catch (const std::exception&)
		{
			return false;
		}

		return true;
	}

	void CalibrationService::OrderPointsByAsc(vector<CustomPoint>& listPoints)
	{
		std::stable_sort(listPoints.begin(), listPoints.end(), zComparator);
		std::stable_sort(listPoints.begin(), listPoints.end(), yComparator);
		std::stable_sort(listPoints.begin(), listPoints.end(), xComparator);
		/*std::stable_sort(listPoints.begin(), listPoints.end(), Comparator);*/
	}

	void CalibrationService::PivelToCoordinate(vector<PointPair>& listPoints)
	{
		float aux = 300.0;
		float aux2 = 6.0;
		for (int i = 0; i < listPoints.size(); i++)
		{
			listPoints[i].FirstPoint.X = listPoints[i].FirstPoint.X / 48;
			listPoints[i].FirstPoint.Y = listPoints[i].FirstPoint.Y / 24;
			listPoints[i].SecondPoint.X = listPoints[i].SecondPoint.X / 48;
			listPoints[i].SecondPoint.Y = listPoints[i].SecondPoint.Y / 24;
		}
	}

	void CalibrationService::ChangeScale(vector<CustomPoint>& listPoints)
	{
		for (int i = 0; i < listPoints.size(); i++)
		{
			listPoints[i].X = listPoints[i].X - 4.0;
			listPoints[i].Y = listPoints[i].Y + 4.0;
			listPoints[i].Z = listPoints[i].Z + 4.0;
		}
	}

	void CalibrationService::ChangeScale(vector<PointPair>& listPoints)
	{
		float scaleX = -4;
		float scaleY = -4;

		for (int i = 0; i < listPoints.size(); i++)
		{
			listPoints[i].FirstPoint.X = listPoints[i].FirstPoint.X + scaleX;
			listPoints[i].FirstPoint.Y = listPoints[i].SecondPoint.Y + scaleY;
			listPoints[i].SecondPoint.X = listPoints[i].FirstPoint.X + scaleX;
			listPoints[i].SecondPoint.Y = listPoints[i].SecondPoint.Y + scaleY;
		}
	}

	vector<CustomPoint> CalibrationService::FilterByShape(vector<CustomPoint> listPoints, vector<CustomPoint> listShapePoints)
	{
		try
		{
			vector<CustomPoint> result;
			vector<int> errorMatches;

			int cont = 0;

			/*--------------------------------------------
			Separei a checkagem em quadrantes, para assim podermos testar cada ponto do Sift em cada ponto do Contorno.
			Se o ponto do Sift cair no 1� quadrante, vamos aplicar as regras de verifica��o para o 1� quadrante e
			assim igual aos demais quadrantes.
			Regras (chamarei {Xc; Yc} para pontos do contorno, e {Xs ;Ys} para pontos do Sift) :
			- 1� Quadrante: Xs e Ys s�o positivos, logo checamos se Xs <= Xc && Ys <= Yc
			- 2� Quadrante: Xs � negativo e Ys � positivo, logo checamos se Xs >= Xc && Ys <= Yc
			- 3� Quadrante: Xs e Ys s�o negativos, logo checamos se Xs >= Xc && Ys >= Yc
			- 4� Quadrante: Xs � positivo e Ys � negativo, logo checamos se Xs <= Xc && Ys >= Yc
			----------------------------------------------*/

			for each(CustomPoint item in listPoints) {
				bool teste = false;
				int count2 = 0;
				for each (CustomPoint itemShape in listShapePoints)
				{
					if (item.X < 0) {
						if (item.Y < 0) {
							if (item.X >= itemShape.X && item.Y >= itemShape.Y) { //Checkagem do ponto no 3� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
						else {
							if (item.X >= itemShape.X && item.Y <= itemShape.Y) {//Checkagem do ponto no 2� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
					}
					else {
						if (item.Y < 0) {
							if (item.X <= itemShape.X && item.Y >= itemShape.Y) { //Checkagem do ponto no 4� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
						else {
							if (item.X <= itemShape.X && item.Y <= itemShape.Y) { //Checkagem do ponto no 4� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
					}
					count2++;
				}

				if (teste == false) {
					errorMatches.push_back(cont);

				}

				cont++;
			}

			for each (CustomPoint item in listShapePoints)
			{
				result.push_back(item);
			}

			cout << "-------------------------------- OUT OF SHAPE -----------------------------" << endl;
			cont = 0;
			for each (int item in errorMatches)
			{
				cout << "Out [" << cont << "]: { " << listPoints[item].X << " ; " << listPoints[item].Y << " ; " << listPoints[item].Z << " }" << endl;
				cont++;
			}
			cout << "------------------------------------------------------------------------------" << endl;

			return result;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}

	float CalibrationService::WorldPointX(float firstPointX, float Z) {
		return (firstPointX / _lambda) * (_lambda - Z);
	}

	float CalibrationService::WorldPointY(float firstPointY, float Z) {
		return (firstPointY / _lambda) * (_lambda - Z);
	}

	float CalibrationService::WorldPointZ(CustomPoint firstPoint, CustomPoint secondPoint) {
		return _lambda - ((_lambda * _b) / (secondPoint.X - firstPoint.X));
	}

	CustomPoint CalibrationService::BestNeighbour(CustomPoint checkPoint, vector<CustomPoint> listNeighbourPoint)
	{
		vector<float> EuclideanDistance;

		for each (CustomPoint item in listNeighbourPoint)
		{
			EuclideanDistance.push_back(CalculateEuclideanDistance(checkPoint, item));
		}

		float minValue = EuclideanDistance[0];
		int minPosition = 0;
		for (int i = 0; i < _k; i++)
		{
			if (EuclideanDistance[i] < minValue)
				minPosition = i;
		}

		return listNeighbourPoint[minPosition];
	}

	vector<CustomPoint> CalibrationService::GetNeighbourPoints(vector<CustomPoint>listPointsFrame, int positionPointFrame)
	{
		vector<CustomPoint> result;
		int count = 0;
		int firstPosition = positionPointFrame - (positionPointFrame / 2);

		if (firstPosition < 0)
			firstPosition = 0;

		while (count < _k) {
			result.push_back(listPointsFrame[firstPosition]);
			count++;
		}

		return result;
	}
	
}