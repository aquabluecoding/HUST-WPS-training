#ifndef __K_SHAPE_FACTORY_H__
#define __K_SHAPE_FACTORY_H__

#include "kshape.h"

class KShapeFactory
{
public:
	virtual KShape* produceShape() = 0;
	virtual KShape* produceRound(std::string name, double radius) { return nullptr; }
	virtual KShape* produceSquare(std::string name, double length) { return nullptr; }
	virtual KShape* produceRectangle(std::string name, double length, double width) { return nullptr; }
	virtual KShape* produceTriangle(std::string name, double a, double b, double c) { return nullptr; }
	virtual KShape* produceTrapezium(std::string name, double base1, double base2, double height, double bias) { return nullptr; }
	virtual KShape* produceCompound(std::string name, std::vector<KShape*> parts) { return nullptr; }
};

#endif
