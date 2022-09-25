#include <iostream>
//单向链表定义
struct LinkNode
{
    int val;
    LinkNode *next;
    LinkNode () : val(0), next(nullptr) {}
    LinkNode (int x) : val(x), next(nullptr) {}
    LinkNode (int x, LinkNode *next) : val(x), next(next) {}
};
int LinkLength(LinkNode* head);
class KLinkSolution
{
public:
    LinkNode* reverseKGroup(LinkNode* head, int k)
    {
        //初始化需要使用的节点指针，begin:左半对换的节点，end:右半对换的节点的直接前驱
        //lastPair:上一对节点接到下一对节点的那个节点
        //lastGroup:上一组节点接到下一组节点的那个节点
        //newHead:每对节点对换后到了前面的节点
        LinkNode* begin, * end, * lastPair, *newHead, *lastGroup;
        begin = end = lastPair = newHead = lastGroup = head;
        //k=2，2个节点一组，逐组对换
        if (k == 2) 
        {
            int flag = 0;
            while (begin->next != nullptr) 
            {
                LinkNode* t = begin->next->next;
                begin->next->next = begin;
                newHead = begin->next;
                begin->next = t;
                if (flag != 0) //连接上一组和下一组
                {
                    lastGroup->next = newHead;
                }
                else //返回新的head
                {
                    head = newHead;
                    flag = 1;
                }
                lastGroup = begin;
                begin = t;
            }
        }
        //k>2，组内左半元素和右半元素对换
        else if(k > 2) 
        {
            //计算一共有多少组，作为最外层循环的次数
            int n_Group = LinkLength(head) / k;
            for (int i = 0; i < n_Group; i++) 
            {
                begin = end = head;
                for (int j = 0; j < i * k - 1; j++)
                {
                    begin = begin->next;
                }
                if (i > 0) {
                    lastGroup = begin;
                    begin = begin->next;
                }
                end = begin;
                int len = k;
                //这重循环的次数是每组中需要交换的pairs的数目
                for (int j = 0; j < k / 2; j++)
                {
                    if (len == 2)
                    {
                        LinkNode* temp = begin->next->next;
                        begin->next->next = begin;
                        newHead = begin->next;
                        begin->next = temp;
                        lastPair->next = newHead;
                    }
                    else
                    {
                        for (int l = 2; l < k - j; l++)
                        {
                            end = end->next;
                        }
                        LinkNode* temp = begin->next;
                        begin->next = end->next->next;
                        end->next->next = temp;
                        newHead = end->next;
                        end->next = begin;
                        if (j > 0) //连接上一对和下一对
                            lastPair->next = newHead;
                        else if (i == 0) //返回新的head
                            head = newHead;
                        else //连接上个组
                            lastGroup->next = newHead;
                        begin = newHead->next;
                        end = newHead;
                        lastPair = newHead;
                        len -= 2;
                    }
                }
            }
        }
        return head;
    }
};
int LinkLength(LinkNode* head) {
    int length = 1;
    LinkNode* p = head;
    while(p->next != nullptr)
    {
        length++;
        p = p->next;
    }
    return length;
}
void ShowLinkList(LinkNode* head) {
    LinkNode* t = head;
    while (t != nullptr) {
        std::cout << t->val << ' ';
        t = t->next;
    }
    std::cout << std::endl;
}
int main(void) {
    KLinkSolution s;
    int n, k;
    LinkNode* head, * rear;
    LinkNode a(1);
    head = rear = &a;
    //测试时假设初始的链表是正整数序列，便于观察
    std::cout << "请输入顺序链表长度：";
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        LinkNode* p = nullptr;
        p = new LinkNode;
        p->val = i + 1;
        p->next = nullptr;
        rear->next = p;
        rear = rear->next;
    }
    std::cout << "请输入每组的长度k：";
    std::cin >> k;
    ShowLinkList(s.reverseKGroup(head, k));
    return 0;
}