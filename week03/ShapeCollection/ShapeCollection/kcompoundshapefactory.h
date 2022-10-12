#ifndef __K_COMPOUND_SHAPE_FACTORY_H__
#define __K_COMPOUND_SHAPE_FACTORY_H__

#include "kshapefactory.h"
#include "kcompoundshape.h"

class KCompoundShapeFactory :public KShapeFactory
{
public:
	virtual KShape* produceShape() override;
	virtual KShape* produceCompound(std::string name, std::vector<KShape*> parts) override;
};

#endif 