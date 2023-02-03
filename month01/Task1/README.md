# KTinySTL

实现了STL的基础支撑部件：

+ 空间分配器（基于内存池）
+ type traits类型过滤机制
+ iterator traits机制

实现了以下容器：

+ KVector
+ KList
+ KDeque
+ KStack
+ KQueue

实现了以下算法：

+ fill/fill_n
+ find/finf_if/find_if_not
+ min/max
+ sort
+ distance

实现了对各个容器和算法的测试（有待完善）

不足：红黑树的实现比较复杂，所以没有实现set/map，留待以后研究



