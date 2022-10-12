#ifndef __K_ROUND_FACTORY_H__
#define __K_ROUND_FACTORY_H__

#include "kshapefactory.h"
#include "kround.h"

class KRoundFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceRound(std::string name, double radius) override;
};

#endif 