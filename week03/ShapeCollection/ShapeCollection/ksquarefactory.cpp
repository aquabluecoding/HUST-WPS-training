#include "ksquarefactory.h"

KShape* KSquareFactory::produceShape()
{
	return new KSquare();
}
KShape* KSquareFactory::produceSquare(std::string name, double len)
{
	return new KSquare(name, len);
}