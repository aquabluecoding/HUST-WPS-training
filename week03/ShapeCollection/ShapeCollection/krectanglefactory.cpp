#include "krectanglefactory.h"

KShape* KRectangleFactory::produceShape()
{
	return new KRectangle();
}
KShape* KRectangleFactory::produceRectangle(std::string name, double len, double wid)
{
	return new KRectangle(name, len, wid);
}