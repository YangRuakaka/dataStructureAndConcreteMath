#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include<conio.h>

using std::cin;
using std::cout;
using std::endl;

enum { AND, OR, Implication, Equality }; // ����ö�����ͣ���ʾ�߼������

int main()
{
    int a[4]; // �洢�߼�������
    bool i, j; // �洢������߼�ֵ

    while (true) { // ����ѭ����ֱ���û�ѡ���˳�

        // �����ӭ����
        cout << "***************************************\n";
        cout << "**                                   **\n";
        cout << "**        ��ӭ�����߼��������       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // �����߼�ֵ i
        cout << "������P��ֵ��0��1��,�Իس�����:" << endl;
        while (true) {
            cin >> i;
            if (cin.fail() || (i != false && i != true)) { // ��������Ƿ�Ϸ�
                std::cerr << "P��ֵ��������,����������!" << endl;
                std::cin.clear();
                std::cin.ignore(1234, '\n');
            }
            else
                break;
        }

        // �����߼�ֵ j
        cout << "������Q��ֵ��0��1��,�Իس�����:" << endl;
        while (true) {
            cin >> j;
            if (cin.fail() || (j != false && j != true)) { // ��������Ƿ�Ϸ�
                std::cerr << "Q��ֵ��������,����������!" << endl;
                std::cin.clear();
                std::cin.ignore(1234, '\n');
            }
            else
                break;
        }

        // �����߼�����
        a[AND] = (i && j);  // ������
        a[OR] = (i || j);  // ������
        a[Implication] = ((!i) || j);  // �̺����㣬����ת��Ϊ������ʽ
        a[Equality] = (((!i) || j) && ((!j) || i));  // ��ֵ���㣬����ת��Ϊ������ʽ

        // ����߼�������
        printf("\n\n  ��ȡ:\n       P/\\Q = %d\n", a[AND]);  // ������
        printf("  ��ȡ:\n       P\\/Q = %d\n", a[OR]);
        printf("  ����:\n       P->Q = %d\n", a[Implication]);
        printf("  ˫����:\n       P<->Q = %d\n", a[Equality]);

        // ѯ���Ƿ��������
        cout << "\n�Ƿ��������?��y/n��";
        char s;
        while (true) {
            s = _getch();
            if (s == 'y' || s == 'n') {
                cout << s << endl;
                Sleep(100);
                break;
            }
            else
                continue;
        }
        if (s == 'y')
        {
            system("cls");  // ����
            continue;  // ���ض���
        }
        else
        {
            printf("��ӭ�´��ٴ�ʹ��!\n");  // �˳�
            exit(0);
        }
    }

    return 0;
}
