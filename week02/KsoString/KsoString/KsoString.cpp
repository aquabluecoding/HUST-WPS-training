#include "KsoString.hpp"

int main()
{
	const wchar_t STR1[] = L"华中科技大学";
	const char STR2[] = "HUSTSOCST";

	cout << "构造函数测试、遍历测试、重载'='测试:" << endl;
	KsoString<wchar_t> test01(STR1);
	KsoString<char> test02 = STR2;
	KsoString<char> test03(test02);
	KsoString<wchar_t> test04(7, 'A');
	//KsoString<int> test05("123456");  //不可向模板类中装入其他数据类型
	
	test01.traverse();
	test02.traverse();
	test03.traverse();
	test04.traverse();

	cout << "析构函数测试, 判空测试:" << endl;
	test02.~KsoString();
	if (test02.empty())
		cout << "test02为空" << endl;

	cout << "插入测试：" << endl;
	test04.insert(4, 'B');
	test04.traverse();

	cout << "删除测试：" << endl;
	test04.erase(5);
	test04.traverse();
	
	cout << "首尾增删测试："<<endl;
	wcout << test01.pop_front() << endl;
	wcout << test01.pop_back() << endl;
	test01.traverse();

	test01.push_front(L'华');
	test01.push_back(L'学');
	test01.traverse();
	
	cout << "输出长度测试：" << endl;
	cout << "test01的长度为：" << test01.size() << endl;

	cout << "重载[]测试：" << endl;
	for (int i = 0; i < test03.size(); i++) 
	{
		cout << test03[i] << ' ';
	}
	cout << endl;

	cout << "迭代器测试：" << endl;
	KsoString<char>::iterator it;
	for (it = test03.getHead(); it != test03.getTail(); it++)
	{
		cout << *it << ' ';
	}
	cout << *it << endl;
	return 0;
}