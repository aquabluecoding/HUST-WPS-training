#include "ktrapeziumfactory.h"

KShape* KTrapeziumFactory::produceShape()
{
	return new KTrapezium();
}
KShape* KTrapeziumFactory::produceTrapezium(std::string name, double base1, double base2, double height, double bias)
{
	return new KTrapezium(name, base1, base2, height, bias);
}