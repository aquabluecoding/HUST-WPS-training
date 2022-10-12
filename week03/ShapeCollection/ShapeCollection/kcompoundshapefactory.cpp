#include "kcompoundshapefactory.h"

KShape* KCompoundShapeFactory::produceShape()
{
	return new KCompoundShape();
}
KShape* KCompoundShapeFactory::produceCompound(std::string name, std::vector<KShape*> parts)
{
	return new KCompoundShape(name, parts);
}