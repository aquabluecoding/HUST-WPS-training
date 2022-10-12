#ifndef __K_TRANGLE_FACTORY_H__
#define __K_TRANGLE_FACTORY_H__

#include "kshapefactory.h"
#include "ktriangle.h"

class KTriangleFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceTriangle(std::string name, double a, double b, double c) override;
};

#endif 