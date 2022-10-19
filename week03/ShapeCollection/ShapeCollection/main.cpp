#include "kcompoundshapefactory.h"
#include "krectanglefactory.h"
#include "kroundfactory.h"
#include "ksquarefactory.h"
#include "ktrianglefactory.h"
#include "ktrapeziumfactory.h"

int main()
{
	KShapeFactory* refactory = new KRectangleFactory;
	KShapeFactory* rofactory = new KRoundFactory;
	KShapeFactory* sqfactory = new KSquareFactory;
	KShapeFactory* trafactory = new KTrapeziumFactory;
	KShapeFactory* trifactory = new KTriangleFactory;
	KShapeFactory * cfactory = new KCompoundShapeFactory;

	//测试矩形
	KShape* rectangle = refactory->produceRectangle("01", 2.0, 3.0);
	std::cout << "名称：" << rectangle->getType() << "\t周长：" << rectangle->getPerimeter() << "\t面积：" << rectangle->getArea() << std::endl;

	//测试圆
	KShape* round = rofactory->produceRound("01", 1.0);
	std::cout << "名称：" << round->getType() << "\t周长：" << round->getPerimeter() << "\t面积：" << round->getArea() << std::endl;

	//测试正方形
	KShape* square = sqfactory->produceSquare("01", 3.0);
	std::cout << "名称：" << square->getType() << "\t周长：" << square->getPerimeter() << "\t面积：" << square->getArea() << std::endl;

	//测试梯形
	KShape* trapezium = trafactory->produceTrapezium("01", 3.0, 4.0, 3.0, 0.5);
	std::cout << "名称：" << trapezium->getType() << "\t周长：" << trapezium->getPerimeter() << "\t面积：" << trapezium->getArea() << std::endl;

	//测试三角形
	KShape* triangle = trifactory->produceTriangle("01", 3.0, 4.0, 5.0);
	std::cout << "名称：" << triangle->getType() << "\t周长：" << triangle->getPerimeter() << "\t面积：" << triangle->getArea() << std::endl;

	//测试合成图形
	std::vector<KShape*> shapes;
	shapes.push_back(rectangle);
	shapes.push_back(square);
	shapes.push_back(round);
	KShape* compoundShape = cfactory->produceCompound("01", shapes);
	std::cout << "名称：" << compoundShape->getType() << "\t周长：" << compoundShape->getPerimeter() << "\t面积：" << compoundShape->getArea() << "\t子图形数量：" << ((KCompoundShape*)compoundShape)->showComponentNumber() << "\t子图形：";
	((KCompoundShape*)compoundShape)->showComponent();

	delete rectangle;
	delete round;
	delete square;
	delete trapezium;
	delete triangle;
	delete compoundShape;

	delete refactory;
	delete refactory;
	delete rofactory;
	delete sqfactory;
	delete trafactory;
	delete trifactory;
	delete cfactory;

	return 0;
}