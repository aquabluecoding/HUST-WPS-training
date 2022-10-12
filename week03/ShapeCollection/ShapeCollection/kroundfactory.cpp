#include "kroundfactory.h"

KShape* KRoundFactory::produceShape()
{
	return new KRound();
}
KShape* KRoundFactory::produceRound(std::string name, double radius)
{
	return new KRound(name, radius);
}