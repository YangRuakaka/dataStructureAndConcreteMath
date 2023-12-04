#include <iostream>
#include <cstdlib>
#define N 13

struct tree
{
    int num;
    struct tree* Lnode;
    struct tree* Rnode;
}*fp[N]; //保存结点
char s[2 * N]; //放前缀码

void init_node(int f[], int n) //生成叶子结点
{
    int i;
    struct tree* pt;
    for (i = 0; i < n; i++)
    {
        pt = new struct tree; //生成叶子结点
        pt->num = f[i];
        pt->Lnode = NULL;
        pt->Rnode = NULL;
        fp[i] = pt;
    }
}

void sort(struct tree* array[], int n) //将第N-n个点插入到已排好序的序列中
{
    int i;
    struct tree* temp;
    for (i = N - n; i < N - 1; i++)
    {
        if (array[i]->num > array[i + 1]->num) // 比较两个节点的权值大小
        {
            temp = array[i + 1]; // 交换节点位置
            array[i + 1] = array[i];
            array[i] = temp;
        }
    }
}

struct tree* construct_tree(int f[], int n) //建立树
{
    int i;
    struct tree* pt;
    for (i = 1; i < N; i++)
    {
        pt = new struct tree; //生成非叶子结点
        pt->num = fp[i - 1]->num + fp[i]->num; // 非叶子节点的权值为左右子节点的权值之和
        pt->Lnode = fp[i - 1];
        pt->Rnode = fp[i];
        fp[i] = pt; //wl+w2
        sort(fp, N - i); // 对已排好序的序列进行插入排序
    }
    return fp[N - 1]; // 返回根节点
}

void preorder(struct tree* p, int k, char c)
{
    int j;
    if (p != NULL)
    {
        if (c == '1')
            s[k] = '0';
        else
            s[k] = '1';
        if (p->Lnode == NULL)
        { //P 指向叶子
            std::cout << p->num << ": ";
            for (j = 0; j <= k; j++)
                std::cout << s[j]; //输出前缀码
            std::cout << std::endl;
        }
        preorder(p->Lnode, k + 1, '1'); // 遍历左子树
        preorder(p->Rnode, k + 1, 'r'); // 遍历右子树
    }
}

int main()
{
    int n;
    std::cout << "请输入节点个数(必须是正整数):";
    std::cin >> n;
    int f[80];
    std::cout << "请输入节点(以空格分隔):";
    for (int i = 0; i < n; i++)
    {
        std::cin >> f[i]; // 输入各个节点的权值
    }
    struct tree* head;
    init_node(f, N); //初始化结点
    head = construct_tree(f, N); //生成最优树
    s[0] = 0;
    preorder(head, 0, '1'); //遍历树
    return 0;
}
