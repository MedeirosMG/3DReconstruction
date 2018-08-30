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

	bool xComparator(const Point3f & e1, const Point3f & e2) {
		return (e1.x > e2.x);
	}

	bool yComparator(const Point3f & e1, const Point3f & e2) {
		return (e1.y > e2.y);
	}

	bool zComparator(const Point3f & e1, const Point3f & e2) {
		return (e1.z > e2.z);
	}

	bool Comparator(const Point3f & e1, const Point3f & e2) {
		return (e1.x == e2.x ? e2.y < e2.y : e1.x < e2.x);
	}

	vector<Point3f> CalibrationService::CalculateStereoCameraCalibrationUsingNeighbours(vector<Point3f>listPointsFrame1, vector<Point3f> listPointsFrame2)
	{
		vector<PointPair> listResultRelativesPoints;
		int index = 0;
		for each (Point3f item in listPointsFrame1)
		{
			vector<Point3f> listNeighboursPoints = GetNeighbourPoints(listPointsFrame2, index);
			Point3f neighbour = BestNeighbour(item, listNeighboursPoints);

			listResultRelativesPoints.push_back(*(new PointPair(item, neighbour)));

			index++;
		}

		return CalculateListRealPoints(listResultRelativesPoints);
	}

	vector<Point3f> CalibrationService::CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints)
	{
		return CalculateListRealPoints(listMatchPoints);
	}

	vector<Point3f> CalibrationService::CalculateListRealPoints(vector<PointPair> listPoints)
	{
		//PivelToCoordinate(listPoints);
		//ChangeScale(listPoints);
		//PrintResult(listPoints);

		vector<Point3f> listRealPoints;

		for each (PointPair item in listPoints)
		{
			listRealPoints.push_back(*(CalculateRealPoint(item.FirstPoint, item.SecondPoint)));
		}

		//ChangeScale(listRealPoints);

		return listRealPoints;
	}

	float CalibrationService::CalculateEuclideanDistance(Point3f firstPoint, Point3f secondPoint)
	{
		return sqrt(pow((firstPoint.x - secondPoint.x), 2) + pow((firstPoint.y - secondPoint.y), 2));
	}

	Point3f* CalibrationService::CalculateRealPoint(Point3f firstPoint, Point3f secondPoint) {
		float WorldZ = 0, WorldY = 0, WorldX = 0;
		WorldZ = this->WorldPointZ(firstPoint, secondPoint);
		WorldY = this->WorldPointY(firstPoint.y, WorldZ);
		WorldX = this->WorldPointX(firstPoint.x, WorldZ);

		Point3f* WorldPoint = new Point3f(WorldX, WorldY, WorldZ);

		return WorldPoint;
	}

	void CalibrationService::PrintResult(vector<Point3f> listPoints)
	{
		cout << "============================= Result =============================" << endl;
		int count = 1;
		for each (Point3f item in listPoints)
		{
			if (count < 10)
				cout << "P[0" << count << "] = { " << item.x << " ; " << item.y << " ; " << item.z << " } " << endl;
			else
				cout << "P[" << count << "] = { " << item.x << " ; " << item.y << " ; " << item.z << " } " << endl;
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
				cout << "[0" << count << "] FirstPoint : { " << item.FirstPoint.x << " ; " << item.FirstPoint.y << " } - SecondPoint : { " << item.SecondPoint.x << " ; " << item.SecondPoint.y << " }" << endl;
			else
				cout << "[" << count << "] FirstPoint : { " << item.FirstPoint.x << " ; " << item.FirstPoint.y << " } - SecondPoint : { " << item.SecondPoint.x << " ; " << item.SecondPoint.y << " }" << endl;
			count++;
		}
		cout << "===========================================================================================" << endl;
	}

	void CalibrationService::PrintResult(Point3f point)
	{
		cout << "============================= Result =============================" << endl;
		cout << "Point = { " << point.x << " ; " << point.y << " ; " << point.z << " } " << endl;
		cout << "==================================================================" << endl;
	}

	bool CalibrationService::ExportToJson(vector<Point3f> listPoints, string pathDirectory)
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

	bool CalibrationService::ExportToObj(vector<Point3f> listPoints, string pathDirectory)
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

	void CalibrationService::OrderPointsByAsc(vector<Point3f>& listPoints)
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
			listPoints[i].FirstPoint.x = listPoints[i].FirstPoint.x / 48;
			listPoints[i].FirstPoint.y = listPoints[i].FirstPoint.y / 24;
			listPoints[i].SecondPoint.x = listPoints[i].SecondPoint.x / 48;
			listPoints[i].SecondPoint.y = listPoints[i].SecondPoint.y / 24;
		}
	}

	void CalibrationService::ChangeScale(vector<Point3f>& listPoints)
	{
		for (int i = 0; i < listPoints.size(); i++)
		{
			listPoints[i].x = listPoints[i].x - 4.0;
			listPoints[i].y = listPoints[i].y + 4.0;
			listPoints[i].z = listPoints[i].z + 4.0;
		}
	}

	void CalibrationService::ChangeScale(vector<PointPair>& listPoints)
	{
		float scaleX = -4;
		float scaleY = -4;

		for (int i = 0; i < listPoints.size(); i++)
		{
			listPoints[i].FirstPoint.x = listPoints[i].FirstPoint.x + scaleX;
			listPoints[i].FirstPoint.y = listPoints[i].SecondPoint.y + scaleY;
			listPoints[i].SecondPoint.x = listPoints[i].FirstPoint.x + scaleX;
			listPoints[i].SecondPoint.y = listPoints[i].SecondPoint.y + scaleY;
		}
	}

	vector<Point3f> CalibrationService::FilterByShape(vector<Point3f> listPoints, vector<Point3f> listShapePoints)
	{
		try
		{
			vector<Point3f> result;
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

			for each(Point3f item in listPoints) {
				bool teste = false;
				int count2 = 0;
				for each (Point3f itemShape in listShapePoints)
				{
					if (item.x < 0) {
						if (item.y < 0) {
							if (item.x >= itemShape.x && item.y >= itemShape.y) { //Checkagem do ponto no 3� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
						else {
							if (item.x >= itemShape.x && item.y <= itemShape.y) {//Checkagem do ponto no 2� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
					}
					else {
						if (item.y < 0) {
							if (item.x <= itemShape.x && item.y >= itemShape.y) { //Checkagem do ponto no 4� quadrante
								teste = true;
								result.push_back(item);
								break;
							}
						}
						else {
							if (item.x <= itemShape.x && item.y <= itemShape.y) { //Checkagem do ponto no 4� quadrante
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

			for each (Point3f item in listShapePoints)
			{
				result.push_back(item);
			}

			cout << "-------------------------------- OUT OF SHAPE -----------------------------" << endl;
			cont = 0;
			for each (int item in errorMatches)
			{
				cout << "Out [" << cont << "]: { " << listPoints[item].x << " ; " << listPoints[item].y << " ; " << listPoints[item].z << " }" << endl;
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

	float CalibrationService::WorldPointZ(Point3f firstPoint, Point3f secondPoint) {
		return _lambda - ((_lambda * _b) / (secondPoint.x - firstPoint.x));
	}

	Point3f CalibrationService::BestNeighbour(Point3f checkPoint, vector<Point3f> listNeighbourPoint)
	{
		vector<float> EuclideanDistance;

		for each (Point3f item in listNeighbourPoint)
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

	vector<Point3f> CalibrationService::GetNeighbourPoints(vector<Point3f>listPointsFrame, int positionPointFrame)
	{
		vector<Point3f> result;
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