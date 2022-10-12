#include "ktrianglefactory.h"

KShape* KTriangleFactory::produceShape()
{
	return new KTriangle();
}
KShape* KTriangleFactory::produceTriangle(std::string name, double a, double b, double c)
{
	return new KTriangle(name, a, b, c);
}