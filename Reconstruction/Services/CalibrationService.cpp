#include "stdafx.h"
#include "CalibrationService.h"

namespace Services {

	CalibrationService::CalibrationService(float b, float lambda, OpenCV* openCv, int k, Size imgSize) : _b(b), _lambda(lambda), _k(k) {
		_openCv = openCv;
		_imgSize = imgSize;
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

	vector<Point3f> CalibrationService::CalculateStereoCameraCalibration(vector<PointPair> listMatchPoints, Mat contour)
	{
		PointUtilities *converter = new PointUtilities();
		vector<Point3f> listRealPoints;

		//listMatchPoints = converter->PixelToCoordenate(listMatchPoints, _imgSize);

		for each (PointPair item in listMatchPoints)
		{
			Point3f point = *CalculateRealPoint(item.FirstPoint, item.SecondPoint);
			if (converter->CheckInsidePoint(Point2f(point.x, point.y), contour)) {
				// Filter Z
				if(point.z >= 0 && point.z <= 150)
					listRealPoints.push_back(point);
					//listRealPoints.push_back(converter->CoordenateToPixel(*(CalculateRealPoint(item.FirstPoint, item.SecondPoint)), _imgSize));
			}
		}

		return listRealPoints;
	}

	Point3f* CalibrationService::CalculateRealPoint(Point3f firstPoint, Point3f secondPoint) {
		float WorldZ = 0, WorldY = 0, WorldX = 0;
		WorldZ = this->WorldPointZ(firstPoint, secondPoint);
		WorldY = this->WorldPointY(firstPoint.y, WorldZ);
		WorldX = this->WorldPointX(firstPoint.x, WorldZ);

		Point3f* WorldPoint = new Point3f(firstPoint.x, firstPoint.y, WorldZ);

		return WorldPoint;
	}

	void CalibrationService::OrderPointsByAsc(vector<Point3f>& listPoints)
	{
		std::stable_sort(listPoints.begin(), listPoints.end(), zComparator);
		std::stable_sort(listPoints.begin(), listPoints.end(), yComparator);
		std::stable_sort(listPoints.begin(), listPoints.end(), xComparator);
		/*std::stable_sort(listPoints.begin(), listPoints.end(), Comparator);*/
	}

	float CalibrationService::WorldPointX(float firstPointX, float Z) {
		return (firstPointX / _lambda) * (_lambda - Z);
	}

	float CalibrationService::WorldPointY(float firstPointY, float Z) {
		return (firstPointY / _lambda) * (_lambda - Z);
	}

	float CalibrationService::WorldPointZ(Point3f firstPoint, Point3f secondPoint) {
		return (_lambda - ((_lambda * _b) / (secondPoint.x - firstPoint.x)));
	}	
}