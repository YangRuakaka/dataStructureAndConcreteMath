#include <iostream>
#include <cstdlib>

using namespace std;

void output(int s[][100]); // 输出矩阵的函数
void zifan(int s2[][100]); // 自反闭包算法
void duichen(int s2[][100]); // 对称闭包算法
void chuandi(int s2[][100]); // 传递闭包算法
void select(); // 选择操作的函数
void exitProgram(); // 退出程序的函数
int s[100][100], z; // 全局变量：关系矩阵和选择操作的变量
int d, n, i, j; // 行数、列数、循环变量

int main()
{
    select(); // 调用选择操作的函数
    return 0;
}

void select()
{
    cout << "请输入矩阵的行数:";
    cin >> n; // 输入矩阵的行数
    cout << "请输入矩阵的列数:";
    cin >> d; // 输入矩阵的列数
    cout << "请输入关系矩阵:\n";
    for (i = 0; i < n; i++)
    {
        cout << "\n";
        cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
        for (j = 0; j < d; j++)
            cin >> s[i][j]; // 输入关系矩阵
    }
    cout << "输入对应序号选择算法\n1:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n";
    cin >> z; // 输入选择操作的序号
    switch (z)
    {
        case 1:
            zifan(s); // 调用自反闭包算法
            break;
        case 2:
            chuandi(s); // 调用传递闭包算法
            break;
        case 3:
            duichen(s); // 调用对称闭包算法
            break;
        case 4:
            exitProgram(); // 退出程序
            break;
        default:
            cout << "无效的选择！" << endl; // 输入错误时输出提示
            select(); // 重新选择操作
    }
}

void output(int s[][100])
{
    cout << "所求关系矩阵为:\n"; // 输出提示
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d; j++)
            cout << s[i][j]; // 输出关系矩阵
        cout << endl;
    }
}

void zifan(int s2[][100])
{
    for (i = 0; i < n; i++)
        s2[i][i] = 1; // 自反闭包：对角线上的元素设为1
    output(s2); // 输出处理后的关系矩阵
    select(); // 重新选择操作
}

void duichen(int s2[][100])
{
    int s1[100][100];
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            s1[j][i] = s2[i][j]; // 获取关系矩阵的转置矩阵
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
        {
            s2[i][j] = s2[i][j] + s1[i][j]; // 对称闭包：矩阵元素与其转置元素相加
            if (s2[i][j] > 1)
                s2[i][j] = 1; // 超过1的元素设为1
        }
    output(s2); // 输出处理后的关系矩阵
    select(); // 重新选择操作
}

void chuandi(int s2[][100])
{
    for (int k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < d; j++)
                if (s2[i][j] == 1 && s2[j][k] == 1)
                    s2[i][k] = 1; // 传递闭包：若存在元素 s[i][j] 和 s[j][k] 均为1，则将 s[i][k] 设为1
    output(s2); // 输出处理后的关系矩阵
    select(); // 重新选择操作
}

void exitProgram()
{
    cout << "欢迎下次再次使用!" << endl; // 输出欢迎提示
    exit(0); // 退出程序
}
