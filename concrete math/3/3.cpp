#include <iostream>
#include <cstdlib>

using namespace std;

void output(int s[][100]); // �������ĺ���
void zifan(int s2[][100]); // �Է��հ��㷨
void duichen(int s2[][100]); // �ԳƱհ��㷨
void chuandi(int s2[][100]); // ���ݱհ��㷨
void select(); // ѡ������ĺ���
void exitProgram(); // �˳�����ĺ���
int s[100][100], z; // ȫ�ֱ�������ϵ�����ѡ������ı���
int d, n, i, j; // ������������ѭ������

int main()
{
    select(); // ����ѡ������ĺ���
    return 0;
}

void select()
{
    cout << "��������������:";
    cin >> n; // ������������
    cout << "��������������:";
    cin >> d; // ������������
    cout << "�������ϵ����:\n";
    for (i = 0; i < n; i++)
    {
        cout << "\n";
        cout << "���������ĵ�" << i << "��Ԫ��(Ԫ���Կո�ָ�):";
        for (j = 0; j < d; j++)
            cin >> s[i][j]; // �����ϵ����
    }
    cout << "�����Ӧ���ѡ���㷨\n1:�Է��հ�\n2:���ݱհ�\n3:�ԳƱհ�\n4:�˳�\n";
    cin >> z; // ����ѡ����������
    switch (z)
    {
        case 1:
            zifan(s); // �����Է��հ��㷨
            break;
        case 2:
            chuandi(s); // ���ô��ݱհ��㷨
            break;
        case 3:
            duichen(s); // ���öԳƱհ��㷨
            break;
        case 4:
            exitProgram(); // �˳�����
            break;
        default:
            cout << "��Ч��ѡ��" << endl; // �������ʱ�����ʾ
            select(); // ����ѡ�����
    }
}

void output(int s[][100])
{
    cout << "�����ϵ����Ϊ:\n"; // �����ʾ
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < d; j++)
            cout << s[i][j]; // �����ϵ����
        cout << endl;
    }
}

void zifan(int s2[][100])
{
    for (i = 0; i < n; i++)
        s2[i][i] = 1; // �Է��հ����Խ����ϵ�Ԫ����Ϊ1
    output(s2); // ��������Ĺ�ϵ����
    select(); // ����ѡ�����
}

void duichen(int s2[][100])
{
    int s1[100][100];
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
            s1[j][i] = s2[i][j]; // ��ȡ��ϵ�����ת�þ���
    for (i = 0; i < n; i++)
        for (j = 0; j < d; j++)
        {
            s2[i][j] = s2[i][j] + s1[i][j]; // �ԳƱհ�������Ԫ������ת��Ԫ�����
            if (s2[i][j] > 1)
                s2[i][j] = 1; // ����1��Ԫ����Ϊ1
        }
    output(s2); // ��������Ĺ�ϵ����
    select(); // ����ѡ�����
}

void chuandi(int s2[][100])
{
    for (int k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < d; j++)
                if (s2[i][j] == 1 && s2[j][k] == 1)
                    s2[i][k] = 1; // ���ݱհ���������Ԫ�� s[i][j] �� s[j][k] ��Ϊ1���� s[i][k] ��Ϊ1
    output(s2); // ��������Ĺ�ϵ����
    select(); // ����ѡ�����
}

void exitProgram()
{
    cout << "��ӭ�´��ٴ�ʹ��!" << endl; // �����ӭ��ʾ
    exit(0); // �˳�����
}
