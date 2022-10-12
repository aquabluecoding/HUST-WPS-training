#include "kcompoundshape.h"

KCompoundShape::KCompoundShape() :
	KShape("CompoundShape")
{
}
KCompoundShape::KCompoundShape(std::string name):
	KShape("CompoundShape")
{
	m_name.append(name);
}
KCompoundShape::KCompoundShape(std::string name, std::vector<KShape*> parts) :
	KShape("CompoundShape")
{
	m_name.append(name);
	for (std::vector<KShape*>::iterator it = parts.begin(); it != parts.end(); it++)
	{
		m_perimeter += (*it)->getPerimeter();
		m_area += (*it)->getArea();
		m_log.push_back((*it)->getType());
	}
}

std::string KCompoundShape::getType()
{
	return m_name;
}

double KCompoundShape::getArea(void)
{
	return m_area;
}

double KCompoundShape::getPerimeter(void)
{
	return m_perimeter;
}
void KCompoundShape::showComponent(void)
{
	std::cout << *(m_log.begin());
	for (std::vector<std::string>::iterator it = m_log.begin()+1; it != m_log.end(); it++)
	{
		std::cout << " + " << *it;
	}
}
int KCompoundShape::showComponentNumber(void)
{
	return m_log.size();
}