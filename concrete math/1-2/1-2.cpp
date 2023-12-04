#include <iostream>
#include <cstring>
#include <cmath>
#define N 50

void panduan(int b[N], int f); // ���庯��ԭ�ͣ����ڵݹ�������ֵ��
int tkh(char sz[N], char ccu[N], int icu[N], int h0); // ���庯��ԭ�ͣ����ڴ��������ڵı��ʽ
int fkh(char sz[N], char ccu[N], int icu[N], int h0); // ���庯��ԭ�ͣ����ڴ��������ŵı��ʽ

int main()
{
    int i1, i2, d = 1, icu[N], kh = 0, jg, j = 0, h0;
    int bj = 0, hq[N], h = 0, x = 0, xq[N];
    char sz[N], ccu[N], sz0[N];
    hq[0] = -1;
    xq[0] = -1;
    std::cout << "***************************************\n";
    std::cout << "**                                   **\n";
    std::cout << "**         ��ӭ�����߼��������      **\n";
    std::cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
    std::cout << "**                                   **\n";
    std::cout << "**              ��!��ʾ��            **\n";
    std::cout << "**              ��&��ʾ��            **\n";
    std::cout << "**              ��|��ʾ��            **\n";
    std::cout << "**             ��^��ʾ�̺�           **\n";
    std::cout << "**             ��~��ʾ��ֵ           **\n";
    std::cout << "**                                   **\n";
    std::cout << "***************************************\n\n";
    std::cout << "������һ���Ϸ������⹫ʽ:\n";
    std::cin.getline(sz, N); // ��ȡ�û���������⹫ʽ
    strcpy_s(sz0, sz);
    for (unsigned i1 = 0; i1 < strlen(sz); i1++) // ͳ�����⹫ʽ�еı�������
    {
        if (sz[i1] == ')' || sz[i1] == '(')
            kh++;
        if (sz[i1] >= 'a' && sz[i1] <= 'z' || sz[i1] >= 'A' && sz[i1] <= 'Z') // ͳ�����⹫ʽ�еı���
        {
            for (i2 = 0; i2 < j; i2++)
                if (ccu[i2] == sz[i1])
                    d = 0;
            if (d == 1)
            {
                ccu[j] = sz[i1];
                j++;
            }
            d = 1;
        }
    }
    std::cout << "\n��ʽ���еı�������Ϊ:" << j << "\n"; // �����������
    h0 = j; // ��������������Ϊh0
    std::cout << "\n�����ֵ������:\n \n"; // �����ֵ��ı�ͷ
    for (i1 = 0; i1 < h0; i1++)
        std::cout << " " << ccu[i1] << " "; // ���������
    std::cout << "    ";
    std::cout << sz << "\n\n"; // ������⹫ʽ
    for (i1 = 0; i1 < j; i1++)
        icu[i1] = 0; // ��ʼ����ֵ��
    for (i2 = 0; i2 < j; i2++)
        std::cout << " " << icu[i2] << " "; // �����ֵ���ʼ״̬
    jg = tkh(sz, ccu, icu, h0); // �������⹫ʽ����ֵ
    if (jg == 0)
        hq[h++] = bj; // ����ֵΪ0����������hq����
    else
        xq[x++] = bj; // ����ֵΪ1����������xq����
    std::cout << "    " << jg << "\n"; // ���������
    strcpy_s(sz, sz0); // �ָ�ԭʼ���⹫ʽ
    for (i1 = 0; i1 < (int)pow(2.0, j) - 1; i1++) // ����ֵ���ÿһ�н��м���
    {
        ++bj; // ������1
        panduan(icu, j - 1); // ������һ����ֵ
        jg = tkh(sz, ccu, icu, h0); // �������⹫ʽ����ֵ
        if (jg == 0)
            hq[h++] = bj; // ����ֵΪ0����������hq����
        else
            xq[x++] = bj; // ����ֵΪ1����������xq����
        strcpy_s(sz, sz0); // �ָ�ԭʼ���⹫ʽ
        for (i2 = 0; i2 < j; i2++)
            std::cout << " " << icu[i2] << " "; // �����ǰ�е���ֵ
        std::cout << "    " << jg << "\n"; // ���������
    }
    if (hq[0] == -1)
        std::cout << "\n�����⹫ʽ����������ȡ��ʽ.\n"; // ������
    else
    {
        std::cout << "\n�����⹫ʽ������ȡ��ʽ:\n\t"; // ������
        for (i1 = 0; i1 < h; i1++)
        {
            if (i1 > 0)
                std::cout << "\\/";
            std::cout << "M(" << hq[i1] << ")";
        }
    }
    if (xq[0] == -1)
        std::cout << "\n�����⹫ʽ����������ȡ��ʽ.\n"; // ������
    else
    {
        std::cout << "\n\n�����⹫ʽ������ȡ��ʽ:\n\t"; // ������
        for (i1 = 0; i1 < x; i1++)
        {
            if (i1 > 0)
                std::cout << "/\\";
            std::cout << "m(" << xq[i1] << ")";
        }
    }
    std::cout << "\n"; // ������
    std::cout << "\n��ӭ�´��ٴ�ʹ��!\n"; // ������
    return 0;
}

void panduan(int b[N], int f) // �ݹ�������ֵ��
{
    int i;
    i = f;
    if (b[f] == 0)
        b[f] = 1;
    else
    {
        b[f] = 0;
        panduan(b, --i);
    }
}

int tkh(char sz[N], char ccu[N], int icu[N], int h0)
{
    int i, j, h, s, kh = 0, wz[N], a;
    char xs1[N], ckh[N];
    s = strlen(sz);
    for (i = 0; i < s; i++)
        if (sz[i] == '(' || sz[i] == ')')
        {
            wz[kh] = i;
            ckh[kh] = sz[i];
            kh++;
        }
    if (kh == 0)
        return fkh(sz, ccu, icu, h0);
    else
    {
        for (i = 0; i < kh; i++)
            if (ckh[i] == ')')
                break;
        for (j = wz[i - 1] + 1, h = 0; j < wz[i]; j++, h++)
            xs1[h] = sz[j];
        xs1[h] = '\0';
        a = fkh(xs1, ccu, icu, h0);
        if (a == 1)
            sz[wz[i - 1]] = 1;
        else
            sz[wz[i - 1]] = -2;
        for (j = wz[i - 1] + 1; j < s + wz[i - 1] - wz[i]; j++)
            sz[j] = sz[j + wz[i] - wz[i - 1]];
        sz[j] = '\0';
        return tkh(sz, ccu, icu, h0);
    }
}

int fkh(char sz[N], char ccu[N], int icu[N], int h0)
{
    int i, h = 0, j = 0, j1 = 0, j2 = 0, j3 = 0, j4 = 0, j5 = 0, i1, i2, p1 = -1, p2 = -1, s;
    char dt[N];
    s = strlen(sz);
    if (s == 1)
        if (sz[0] == -2)
            return 0;
        else
            return 1;
    else
    {
        for (i = 0; i < s - j; i++)
            if (sz[i] == '!')
            {
                for (i1 = 0; i1 < h0; i1++)
                    if (sz[i + 1] == ccu[i1])
                        p1 = icu[i1];
                if (sz[i + 1] == -2)
                    p1 = 0;
                if (p1 == -1)
                    p1 = sz[i + 1];
                dt[j + 2] = !p1;
                sz[i] = j + 2;
                j++;
                p1 = 0;
                for (i1 = i + 1; i1 < s - j; i1++)
                    sz[i1] = sz[i1 + 1];
            }
        p1 = -1;
        j1 = j;
        for (i = 0; i < s - j1 - 2 * j2; i++)
            if (sz[i] == '&')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (sz[i - 1] == ccu[i1])
                        p1 = icu[i1];
                    if (sz[i + 1] == ccu[i1])
                        p2 = icu[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (sz[i - 1] == i2)
                        p1 = dt[i2];
                    if (sz[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (sz[i - 1] == -2)
                    p1 = 0;
                if (sz[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = (int)(sz[i - 1]);
                if (p2 == -1)
                    p2 = (int)(sz[i + 1]);
                dt[j + 2] = p1 && p2;
                sz[i - 1] = j + 2;
                j++;
                j2++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2; i1++)
                    sz[i1] = sz[i1 + 2];
                i = i - 1;
            }
        for (i = 0; i < s - j1 - 2 * j2 - 2 * j3; i++)
            if (sz[i] == '|')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (sz[i - 1] == ccu[i1])
                        p1 = icu[i1];
                    if (sz[i + 1] == ccu[i1])
                        p2 = icu[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (sz[i - 1] == i2)
                        p1 = dt[i2];
                    if (sz[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (sz[i - 1] == -2)
                    p1 = 0;
                if (sz[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = (int)(sz[i - 1]);
                if (p2 == -1)
                    p2 = (int)(sz[i + 1]);
                dt[j + 2] = p1 || p2;
                sz[i - 1] = j + 2;
                j++;
                j3++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3; i1++)
                    sz[i1] = sz[i1 + 2];
                i--;
            }
        for (i = 0; i < s - j1 - 2 * j2 - 2 * j3 - 2 * j4; i++)
            if (sz[i] == '^')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (sz[i - 1] == ccu[i1])
                        p1 = icu[i1];
                    if (sz[i + 1] == ccu[i1])
                        p2 = icu[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (sz[i - 1] == i2)
                        p1 = dt[i2];
                    if (sz[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (sz[i - 1] == -2)
                    p1 = 0;
                if (sz[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = (int)(sz[i - 1]);
                if (p2 == -1)
                    p2 = (int)(sz[i + 1]);
                dt[j + 2] = !p1 || p2;
                sz[i - 1] = j + 2;
                j++;
                j4++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3 - 2 * j4; i1++)
                    sz[i1] = sz[i1 + 2];
                i--;
            }
        for (i = 0; i < s - j1 - 2 * j2 - 2 * j3 - 2 * j4 - 2 * j5; i++)
            if (sz[i] == '~')
            {
                for (i1 = 0; i1 < h0; i1++)
                {
                    if (sz[i - 1] == ccu[i1])
                        p1 = icu[i1];
                    if (sz[i + 1] == ccu[i1])
                        p2 = icu[i1];
                }
                for (i2 = 2; i2 < j + 2; i2++)
                {
                    if (sz[i - 1] == i2)
                        p1 = dt[i2];
                    if (sz[i + 1] == i2)
                        p2 = dt[i2];
                }
                if (sz[i - 1] == -2)
                    p1 = 0;
                if (sz[i + 1] == -2)
                    p2 = 0;
                if (p1 == -1)
                    p1 = (int)(sz[i - 1]);
                if (p2 == -1)
                    p2 = (int)(sz[i + 1]);
                dt[j + 2] = (!p1 || p2) && (!p2 || p1);
                sz[i - 1] = j + 2;
                j++;
                j5++;
                p1 = -1;
                p2 = -1;
                for (i1 = i; i1 < s - j1 - 2 * j2 - 2 * j3 - 2 * j4 - 2 * j5; i1++)
                    sz[i1] = sz[i1 + 2];
                i--;
            }
        return dt[j + 1];
    }
}

