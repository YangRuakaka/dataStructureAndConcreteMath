#include <iostream>
#include <vector>

using namespace std;

// 定义Warshall算法函数
void warshall(vector<vector<bool>>& matrix, int n)
{
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = matrix[i][j] || (matrix[i][k] && matrix[k][j]);
            }
        }
    }
}

// 输入关系矩阵
void inputMatrix(vector<vector<bool>>& matrix, int n)
{
    cout << "请输入" << n << "x" << n << "的关系矩阵（用0和1表示）：" << endl;
    for (int i = 0; i < n; i++) {
        vector<bool> row;
        for (int j = 0; j < n; j++) {
            bool value;
            cin >> value;
            row.push_back(value);
        }
        matrix.push_back(row);
    }
}

int main()
{
    int n;
    cout << "请输入矩阵的大小：";
    cin >> n;

    // 定义关系矩阵
    vector<vector<bool>> matrix;

    // 输入关系矩阵
    inputMatrix(matrix, n);

    // 调用Warshall算法函数
    warshall(matrix, n);

    // 打印传递闭包矩阵
    cout << "传递闭包矩阵：" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
