/****************************************************************
 * Project Name:  ����
 * File Name:     ����.cpp
 * File Function: Problem solution
 * Update Date:   2023/11/1
 ****************************************************************/

/****************************************************************
 * Problem Description
 ****************************************************************/

//��ÿ��С��֮�䶼��������һ��������·����Ҫ������Ӧ�ľ��ô��ۡ�
//n��С��֮����������n��n - 1�� / 2����·��ѡ�����е�n - 1��ʹ�ܵĺķ����١�

/****************************************************************
 * Problem Solution
 ****************************************************************/
#include <iostream>

const int MAX_N = 100; //Max of Nodes
const int MAX_M = (MAX_N * (MAX_N - 1)) / 2; //Max of edge

struct Edge {
    int u, v, cost;
};//Two nodes and a value

Edge edges[MAX_M]; //Store the edge
int parent[MAX_N]; //Store the information of the root/father of every node

/***************************************************************************
 Function Name:input
 Function:To input the data
 Input Parameters:limits
 Return Value:input value
 Documentation��
****************************************************************************/
template<typename T>
T input(T l_limit, T U_limit)
{
    T num;
    while (true) {
        std::cin >> num;
        if (std::cin.fail() || num < l_limit || num > U_limit) {
            std::cerr << "������������������" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return num;
    }
}

/***************************************************************************
Function Name:init
Function:To initialize the parent array(make every nodes its own father)
Input Parameters:the amount of nodes
Return Value:void
Documentation��
****************************************************************************/
void init(int n) 
{
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }
}

/***************************************************************************
Function Name:find
Function:To find the root of the nodes
Input Parameters:the nodes name(int)
Return Value:the direct father/root of the nodes
Documentation��
****************************************************************************/
int find(int x) 
{
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x]);//Path Compression,quicker when next finding
}

/***************************************************************************
Function Name:unite
Function:To unite two nodes (Make v the father of u)
Input Parameters:the nodes name(int)
Return Value:void
Documentation��
****************************************************************************/
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        parent[x] = y;
}

/***************************************************************************
Function Name:quicksort
Function:To sort the array based on the value
Input Parameters:array two index(low and high)
Return Value:void
Documentation��
****************************************************************************/
void quicksort(Edge* edges, int left, int right) 
{
    //If left index equals to the right index ,return
    if (left >= right)
        return;

    int pivot = edges[left].cost;//Set a pivot
    int l = left, r = right;//Create two index

    while (l < r) {
        while (l < r && edges[r].cost >= pivot)
            --r;//Move the right index to the first element which is greater than pivot
        while (l < r && edges[l].cost <= pivot)
            ++l;//Move the left index to the first element which is smaller than pivot
        if (l < r)
            std::swap(edges[l], edges[r]);//If left index is not equal to the right index swap
    }
    std::swap(edges[left], edges[l]);//Move the privot to the middle

    quicksort(edges, left, l - 1);//Go into the left segment
    quicksort(edges, l + 1, right);//Go into the right segment
}

/***************************************************************************
Function Name:kruskal
Function:To use the kruskal to calculate the minCost
Input Parameters:array two index amount of nodes and amount of edges
Return Value:result
Documentation��
****************************************************************************/
int kruskal(Edge* edges, int n, int m) 
{
    quicksort(edges, 0, m - 1); // Using quicksort 

    init(n);//Initialize the parent array

    int minCost = 0;

    for (int i = 0, j = 0; i < m && j < n - 1; ++i) {
        int u = edges[i].u;//Temporary u
        int v = edges[i].v;//Temporary v
        int cost = edges[i].cost;//Temporary cost

        //If the root of u and v are not same(Connecting them will not lead to a loop)
        if (find(u) != find(v)) {
            unite(u, v);//Connect(Make v the father of u)
            minCost += cost;//Add the cost
            ++j;//Add an existing edge(which will not be greater than n(nodes) minus one
               //Due to the rules of Minimum Spanning Tree
        }
    }

    return minCost;
}

int main() 
{
    int n, m;//N is the amount of nodes,m is the amount of edge
    std::cout << "������ڵ�����" << std::endl;
    n = input<int>(0, MAX_N);
    std::cout << "������ߵ�����" << std::endl;
    m = input<int>(0, MAX_M);

    //Initialize the edge
    for (int i = 0; i < m; ++i) {
        std::cout << "�������" << i + 1 << "���ߵĵ�һ���ڵ�" << std::endl;
        edges[i].u = input<int>(0, MAX_N);
        std::cout << "�������" << i + 1 << "���ߵĵڶ����ڵ�" << std::endl;
        edges[i].v = input<int>(0, MAX_N);
        std::cout << "�������" << i + 1 << "���ߵ����" << std::endl;
        edges[i].cost = input<int>(0, 1000000);
    }

    int result = kruskal(edges, n, m);
    std::cout << "��С��۵�����������ǣ�" << result << std::endl;

    return 0;
}
