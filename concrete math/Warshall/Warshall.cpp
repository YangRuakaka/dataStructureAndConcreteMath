#include <iostream>
#include <vector>

using namespace std;

// ����Warshall�㷨����
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

// �����ϵ����
void inputMatrix(vector<vector<bool>>& matrix, int n)
{
    cout << "������" << n << "x" << n << "�Ĺ�ϵ������0��1��ʾ����" << endl;
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
    cout << "���������Ĵ�С��";
    cin >> n;

    // �����ϵ����
    vector<vector<bool>> matrix;

    // �����ϵ����
    inputMatrix(matrix, n);

    // ����Warshall�㷨����
    warshall(matrix, n);

    // ��ӡ���ݱհ�����
    cout << "���ݱհ�����" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
