#include "kmatrix.cpp"
using namespace std;

int main()
{
    KMatrix<int> a(3, 3);
    a.setData(1, 1, 1);
    a.setData(1, 2, 1);
    a.setData(2, 3, 1);
    a.setData(3, 3, 1);
    cout << "a矩阵(int型)：" << endl;
    a.print();
    cout << endl;

    cout << "a矩阵(2, 2)处的值：" << endl << a.getData(2, 2) << endl;
    cout << "a矩阵(1, 2)处的值：" << endl << a.getData(1, 2) << endl;
    cout << endl;

    cout << "a矩阵的行列数分别为：" << a.getRows() << ", " << a.getCols() << endl << endl;

    KMatrix<int> b(a);
    cout << "b矩阵(int型)：" << endl;
    b.print();
    cout << endl;
    
    cout << "b + a ：" << endl;
    KMatrix<int> add = b + a;
    add.print();
    cout << endl;

    cout << "b - a ：" << endl;
    KMatrix<int> sub = b - a;
    sub.print();
    cout << endl;

    cout << "a的转置：" << endl;
    KMatrix<int> trans = a.transpose();
    trans.print();
    cout << endl;

    cout << "a * b ：" << endl;
    KMatrix<int> mul1 = a * b;
    mul1.print();
    cout << endl;

    KMatrix<double> c(4, 4);
    c.setData(1, 1, 0.1);
    c.setData(2, 2, 0.2);
    c.setData(3, 3, 0.3);
    c.setData(4, 4, 0.4);
    cout << "c矩阵：" << endl;
    c.print();

    c.eraseRow(2);
    cout << "去掉第二行的c矩阵：" << endl;
    c.print();
    cout << endl;
    
    c.eraseCol(2);
    cout << "去掉第二列的c矩阵：" << endl;
    c.print();
    cout << endl;
    
    cout << "遍历输出c矩阵所储存的三元组数据：" << endl;
    for (auto it = c.begin(); it != c.end(); it++) 
    {
        cout << "(" << get<0>(*it) << ", " << get<1>(*it) << ", " << get<2>(*it) << ")" << endl;
    }
    cout << endl;
}
