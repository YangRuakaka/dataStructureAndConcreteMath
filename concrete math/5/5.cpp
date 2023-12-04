#include <iostream>
#include <cstdlib>
#define N 13

struct tree
{
    int num;
    struct tree* Lnode;
    struct tree* Rnode;
}*fp[N]; //������
char s[2 * N]; //��ǰ׺��

void init_node(int f[], int n) //����Ҷ�ӽ��
{
    int i;
    struct tree* pt;
    for (i = 0; i < n; i++)
    {
        pt = new struct tree; //����Ҷ�ӽ��
        pt->num = f[i];
        pt->Lnode = NULL;
        pt->Rnode = NULL;
        fp[i] = pt;
    }
}

void sort(struct tree* array[], int n) //����N-n������뵽���ź����������
{
    int i;
    struct tree* temp;
    for (i = N - n; i < N - 1; i++)
    {
        if (array[i]->num > array[i + 1]->num) // �Ƚ������ڵ��Ȩֵ��С
        {
            temp = array[i + 1]; // �����ڵ�λ��
            array[i + 1] = array[i];
            array[i] = temp;
        }
    }
}

struct tree* construct_tree(int f[], int n) //������
{
    int i;
    struct tree* pt;
    for (i = 1; i < N; i++)
    {
        pt = new struct tree; //���ɷ�Ҷ�ӽ��
        pt->num = fp[i - 1]->num + fp[i]->num; // ��Ҷ�ӽڵ��ȨֵΪ�����ӽڵ��Ȩֵ֮��
        pt->Lnode = fp[i - 1];
        pt->Rnode = fp[i];
        fp[i] = pt; //wl+w2
        sort(fp, N - i); // �����ź�������н��в�������
    }
    return fp[N - 1]; // ���ظ��ڵ�
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
        { //P ָ��Ҷ��
            std::cout << p->num << ": ";
            for (j = 0; j <= k; j++)
                std::cout << s[j]; //���ǰ׺��
            std::cout << std::endl;
        }
        preorder(p->Lnode, k + 1, '1'); // ����������
        preorder(p->Rnode, k + 1, 'r'); // ����������
    }
}

int main()
{
    int n;
    std::cout << "������ڵ����(������������):";
    std::cin >> n;
    int f[80];
    std::cout << "������ڵ�(�Կո�ָ�):";
    for (int i = 0; i < n; i++)
    {
        std::cin >> f[i]; // ��������ڵ��Ȩֵ
    }
    struct tree* head;
    init_node(f, N); //��ʼ�����
    head = construct_tree(f, N); //����������
    s[0] = 0;
    preorder(head, 0, '1'); //������
    return 0;
}
