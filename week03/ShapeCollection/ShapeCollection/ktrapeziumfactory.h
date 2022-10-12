#ifndef __K_TRAPEZIUM_FACTORY_H__
#define __K_TRAPEZIUM_FACTORY_H__

#include "kshapefactory.h"
#include "ktrapezium.h"

class KTrapeziumFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceTrapezium(std::string name, double base1, double base2, double height, double bias) override;
};

#endif 