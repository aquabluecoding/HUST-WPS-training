#ifndef __K_SQUARE_FACTORY_H__
#define __K_SQUARE_FACTORY_H__

#include "kshapefactory.h"
#include "ksquare.h"

class KSquareFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceSquare(std::string name, double length) override;
};

#endif 