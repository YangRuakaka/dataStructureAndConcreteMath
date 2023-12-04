#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include<conio.h>

using std::cin;
using std::cout;
using std::endl;

enum { AND, OR, Implication, Equality }; // 定义枚举类型，表示逻辑运算符

int main()
{
    int a[4]; // 存储逻辑运算结果
    bool i, j; // 存储输入的逻辑值

    while (true) { // 无限循环，直到用户选择退出

        // 输出欢迎标语
        cout << "***************************************\n";
        cout << "**                                   **\n";
        cout << "**        欢迎进入逻辑运算程序       **\n";
        cout << "**                                   **\n";
        cout << "***************************************\n\n";

        // 输入逻辑值 i
        cout << "请输入P的值（0或1）,以回车结束:" << endl;
        while (true) {
            cin >> i;
            if (cin.fail() || (i != false && i != true)) { // 检查输入是否合法
                std::cerr << "P的值输入有误,请重新输入!" << endl;
                std::cin.clear();
                std::cin.ignore(1234, '\n');
            }
            else
                break;
        }

        // 输入逻辑值 j
        cout << "请输入Q的值（0或1）,以回车结束:" << endl;
        while (true) {
            cin >> j;
            if (cin.fail() || (j != false && j != true)) { // 检查输入是否合法
                std::cerr << "Q的值输入有误,请重新输入!" << endl;
                std::cin.clear();
                std::cin.ignore(1234, '\n');
            }
            else
                break;
        }

        // 进行逻辑运算
        a[AND] = (i && j);  // 与运算
        a[OR] = (i || j);  // 或运算
        a[Implication] = ((!i) || j);  // 蕴含运算，将其转化为与或非形式
        a[Equality] = (((!i) || j) && ((!j) || i));  // 等值运算，将其转化为与或非形式

        // 输出逻辑运算结果
        printf("\n\n  合取:\n       P/\\Q = %d\n", a[AND]);  // 输出结果
        printf("  析取:\n       P\\/Q = %d\n", a[OR]);
        printf("  条件:\n       P->Q = %d\n", a[Implication]);
        printf("  双条件:\n       P<->Q = %d\n", a[Equality]);

        // 询问是否继续运算
        cout << "\n是否继续运算?（y/n）";
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
            system("cls");  // 清屏
            continue;  // 返回顶层
        }
        else
        {
            printf("欢迎下次再次使用!\n");  // 退出
            exit(0);
        }
    }

    return 0;
}
