#include <iostream>
#include <climits>

using namespace std;

#define N 100

int p[N], key[N], tb[N][N];  // 定义存储父节点、关键值和图的邻接矩阵的数组

int prim(int v, int n)  // Prim算法实现
{
    int minValue = 0;  // 最小生成树的总权值
    int i, j;
    int min;
    for (i = 1; i <= n; i++)  // 初始化
    {
        p[i] = v;  // 将所有节点的父节点初始化为v
        key[i] = tb[v][i];  // 将所有节点的关键值初始化为与v相连的边的权值
    }
    key[v] = 0;  // 将起始节点的关键值设为0，表示已加入最小生成树

    for (i = 2; i <= n; i++)  // 逐步构建最小生成树
    {
        min = INT_MAX;  // 初始化最小值为最大整数
        for (j = 1; j <= n; j++)
        {
            if (key[j] > 0 && key[j] < min)  // 找到关键值最小的节点
            {
                v = j;  // 更新当前节点为关键值最小的节点
                min = key[j];  // 更新最小值
            }
        }
        cout << "最小耗费是:" << p[v] << "和" << v << " " << endl;  // 输出加入最小生成树的边
        minValue += tb[v][p[v]];  // 更新最小生成树的总权值
        key[v] = 0;  // 将当前节点加入最小生成树
        for (j = 1; j <= n; j++)
        {
            if (tb[v][j] < key[j])  // 更新与当前节点相邻的节点的关键值
            {
                p[j] = v;  // 更新父节点
                key[j] = tb[v][j];  // 更新关键值
            }
        }
    }
    return minValue;  // 返回最小生成树的总权值
}

int main()
{
    int n, m;
    int i, j;
    int u, v, w;
    cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n"; //输入所求的顶点数目和边数
    while (cin >> n >> m)
    {
        if (m != 0 && n != 0)
        {
            for (i = 1; i <= n; i++)
            {
                for (j = 1; j <= n; j++)
                {
                    tb[i][j] = INT_MAX;  // 初始化邻接矩阵
                }
            }
            cout << "请输入两条边的节点序号以及它们的权值(以空格分隔各个数):\n";
            while (m--)
            {
                cin >> u >> v >> w; //输入边数以及它们的权值
                tb[u][v] = tb[v][u] = w;  // 更新邻接矩阵
            }
            cout << "最小生成树权值为" << prim(1, n) << endl;  // 输出最小生成树的总权值
            cout << "请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n"; //输入所求的顶点数目和边数
        }
        else if (n == 0 && m == 0)
            return 0;  // 结束程序
    }
    return 0;
}
