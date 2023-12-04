/****************************************************************
 * Project Name:  ������
 * File Name:     ������.cpp
 * File Function: Problem solution
 * Update Date:   2023/11/3
 ****************************************************************/

/****************************************************************
 * Problem Description
 ****************************************************************/

//��������ؼ��ֲ�����������������ʵ�ֶ����������Ĳ���Ͳ��ҹ��ܡ�
//��������������ָ��ԭ�����е����ݸ��ݴ�С����һ�ö�������
//�������е����н����������һ���Ĵ�С��ϵ�����е��������еĽ����ȸ����С��
//���е��������Ľ����ȸ����󡣶���������������ָ���ն����������н��Ĺ�ϵ���в��ң�
//���ҹؼ�������ͬ�������бȽϣ�����������ҳɹ�������ȸ��ڵ�С�������������в��ң�
//����ȸ����������������н��в��ҡ����ֲ��ҷ������Կ�����С���ҷ�Χ��
//�����ٲ��ҹؼ��ıȽϴ������Ӷ���߲��ҵ�Ч�ʡ�

/****************************************************************
 * Problem Solution
 ****************************************************************/

#include <iostream>
#include <conio.h>

 /***************************************************************************
  Function Name:pause
  Function:To wait for the space to continue
  Input Parameters:void
  Return Value:void
  Documentation��
 ****************************************************************************/
void pause()
{
	while (_getch() != '\r')
		;
	std::cout << std::endl;
}
 


/***************************************************************************
  Function Name:MenuDisplay
  Function:To display the menu
  Input Parameters:void
  Return Value:void
  Documentation��
 ****************************************************************************/
void menuDisplay()
{
	std::cout << "            ����������              " << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "  *         A---����������       *  " << std::endl;
	std::cout << "  *         B---��ӽڵ�         *  " << std::endl;
	std::cout << "  *         C---��ѯ�ڵ�         *  " << std::endl;
	std::cout << "  *         Q---�˳�����         *  " << std::endl;
	std::cout << "====================================" << std::endl;
}

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

//Data structure of binary tree
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

/***************************************************************************
  Function Name:treeDisplay
  Function:To display the tree in order
  Input Parameters:TreeNode
  Return Value:void
  Documentation��
 ****************************************************************************/
void treeDisplay(TreeNode* root)
{
	if (root == nullptr)
		return;
	else {
		treeDisplay(root->left);
		std::cout << root->data << "  ";
		treeDisplay(root->right);
	}

}

/***************************************************************************
Function Name:insert
Function:To insert a treenode
Input Parameters:The root of a tree and the key value
Return Value:void
Documentation��
****************************************************************************/
void insert(TreeNode*& root, int key) 
{
    //If finding the bottom of the tree,create a new treenode for the data
    if (root == nullptr) {
        root = new(std::nothrow) TreeNode(key);
        if (root == NULL) {
            std::cout << "Ҷ�ӽ���ڴ�����ʧ��" << std::endl;
            return;
        }
    }
    else if (key < root->data)//If the key value is smaller than its root
        insert(root->left, key);//Insert it in the left subtree of the root
    else if (key > root->data)//If the key value is greater than its root
        insert(root->right, key);//Insert it in the right subtree of the root
    else
        std::cout << "���нڵ�" << key << "�����У������ظ����룡" << std::endl;

}

/***************************************************************************
Function Name:search
Function:To search for a treenode 
Input Parameters:The root of a tree
Return Value:void
Documentation��
****************************************************************************/
bool search(TreeNode* root, int key)
{
    if (root == nullptr)//Reaching the bottom
        return false; //Fail to find
    else if (key == root->data)//If the key equals to the root value
        return true; //Found!
    else if (key < root->data)//If the key is smaller than the root
        return search(root->left, key);//Search it in the left subtree    
    else //If the key is greater than the root
        return search(root->right, key);//Search it in the right subtree
}

int main()
{

    TreeNode* root = nullptr;//Create the root

	//The loop can let the user execute the process repeatedly
	while (true) {
		//Clear our screen
		system("cls");

		//Display our list
		menuDisplay();

		char controller;//Create a variable to hold the choice we input
		while (true) {
			controller = _getch();//_getch can avoid displaying undesired input on the screen

				if ((controller == 'Q' || controller == 'q') || (controller >= 'a' && controller <= 'c')|| (controller >= 'A' && controller <= 'C')) {
				std::cout << controller << std::endl;//Display the choice on the screen
				switch (controller)
				{
					case 'Q':
					case 'q':
						std::cout << "���������" << std::endl;
						return 0;
					case 'A':
					case 'a':
						std::cout << "���д�������������" << std::endl;
						int n;
						std::cout << "������������ڵ����" << std::endl;
						n = input<int>(1, INT_MAX);

						for (int i = 0; i < n; ++i) {
							int key;
							std::cout << "�������" << i + 1 << "���ڵ������" << std::endl;
							key = input<int>(INT_MIN, INT_MAX);
							insert(root, key);//Add the node to the tree
						}
						std::cout << "��ǰ��Ϊ��" << std::endl;
						treeDisplay(root);
						std::cout << std::endl;
						std::cout << "������ɣ����س�����..." << std::endl;
						pause();
						break;
					case 'B':
					case 'b':
						std::cout << "������ӽڵ����" << std::endl;
						int key;
						std::cout << "��������������ڵ������" << std::endl;
						key = input<int>(INT_MIN, INT_MAX);
						insert(root, key);//Add the node to the tree
						std::cout << "��ǰ��Ϊ��" << std::endl;
						treeDisplay(root);
						std::cout << std::endl;
						std::cout << "������ɣ����س�����..." << std::endl;
						pause();
						break;
					case 'c':
					case 'C':
						std::cout << "ѡ����Ҳ���" << std::endl;
						int target;
						std::cout << "������������ҵĽڵ�����" << std::endl;
						target = input<int>(INT_MIN, INT_MAX);

						if (search(root, target))
							std::cout << "�ڵ�" << target << "�ѱ��ҵ���" << std::endl;
						else
							std::cout << "�ڵ�" << target << "δ���ҵ�" << std::endl;
						std::cout << "������ɣ����س�����..." << std::endl;
						pause();
						break;
					default:
						continue;
				}
				break;
			}//end of if
		}//end of while


	}//end of while

    return 0;
}
