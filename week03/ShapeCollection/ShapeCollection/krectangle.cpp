#include "krectangle.h"

KRectangle::KRectangle():
	KShape("Rectangle")
{
}
KRectangle::KRectangle(std::string name) :
	KShape("Rectangle")
{
	m_name.append(name);
}
KRectangle::KRectangle(std::string name, double length, double width):
	KShape("Rectangle")
{
	m_name.append(name);
	if (length > 0 && width > 0)
	{
		m_length = length;
		m_width = width;
	}
	else
	{
		m_length = m_width = 0;
	}
}
std::string KRectangle::getType()
{
	return m_name;
}
double KRectangle::getArea(void)
{
	return m_length * m_width;
}
double KRectangle::getPerimeter(void)
{
	return 2 * (m_length + m_width);
}