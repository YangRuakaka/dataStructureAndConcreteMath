/****************************************************************
 * Project Name:  二叉树
 * File Name:     二叉树.cpp
 * File Function: Problem solution
 * Update Date:   2023/11/3
 ****************************************************************/

/****************************************************************
 * Problem Description
 ****************************************************************/

//依次输入关键字并建立二叉排序树，实现二叉排序数的插入和查找功能。
//二叉排序树就是指将原来已有的数据根据大小构成一棵二叉树，
//二叉树中的所有结点数据满足一定的大小关系，所有的左子树中的结点均比根结点小，
//所有的右子树的结点均比根结点大。二叉排序树查找是指按照二叉排序树中结点的关系进行查找，
//查找关键自首先同根结点进行比较，如果相等则查找成功；如果比根节点小，则在左子树中查找；
//如果比根结点大，则在右子树中进行查找。这种查找方法可以快速缩小查找范围，
//大大减少查找关键的比较次数，从而提高查找的效率。

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
  Documentation：
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
  Documentation：
 ****************************************************************************/
void menuDisplay()
{
	std::cout << "            二叉树排序              " << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "  *         A---建立二叉树       *  " << std::endl;
	std::cout << "  *         B---添加节点         *  " << std::endl;
	std::cout << "  *         C---查询节点         *  " << std::endl;
	std::cout << "  *         Q---退出程序         *  " << std::endl;
	std::cout << "====================================" << std::endl;
}

 /***************************************************************************
  Function Name:input
  Function:To input the data
  Input Parameters:limits
  Return Value:input value
  Documentation：
 ****************************************************************************/
template<typename T>
T input(T l_limit, T U_limit)
{
    T num;
    while (true) {
        std::cin >> num;
        if (std::cin.fail() || num < l_limit || num > U_limit) {
            std::cerr << "输入有误，请重新输入" << std::endl;
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
  Documentation：
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
Documentation：
****************************************************************************/
void insert(TreeNode*& root, int key) 
{
    //If finding the bottom of the tree,create a new treenode for the data
    if (root == nullptr) {
        root = new(std::nothrow) TreeNode(key);
        if (root == NULL) {
            std::cout << "叶子结点内存申请失败" << std::endl;
            return;
        }
    }
    else if (key < root->data)//If the key value is smaller than its root
        insert(root->left, key);//Insert it in the left subtree of the root
    else if (key > root->data)//If the key value is greater than its root
        insert(root->right, key);//Insert it in the right subtree of the root
    else
        std::cout << "已有节点" << key << "在树中，将不重复插入！" << std::endl;

}

/***************************************************************************
Function Name:search
Function:To search for a treenode 
Input Parameters:The root of a tree
Return Value:void
Documentation：
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
						std::cout << "程序结束！" << std::endl;
						return 0;
					case 'A':
					case 'a':
						std::cout << "进行创建二叉树操作" << std::endl;
						int n;
						std::cout << "请输入二叉树节点个数" << std::endl;
						n = input<int>(1, INT_MAX);

						for (int i = 0; i < n; ++i) {
							int key;
							std::cout << "请输入第" << i + 1 << "个节点的数据" << std::endl;
							key = input<int>(INT_MIN, INT_MAX);
							insert(root, key);//Add the node to the tree
						}
						std::cout << "当前树为：" << std::endl;
						treeDisplay(root);
						std::cout << std::endl;
						std::cout << "操作完成，按回车继续..." << std::endl;
						pause();
						break;
					case 'B':
					case 'b':
						std::cout << "进行添加节点操作" << std::endl;
						int key;
						std::cout << "请输入第你想加入节点的数据" << std::endl;
						key = input<int>(INT_MIN, INT_MAX);
						insert(root, key);//Add the node to the tree
						std::cout << "当前树为：" << std::endl;
						treeDisplay(root);
						std::cout << std::endl;
						std::cout << "操作完成，按回车继续..." << std::endl;
						pause();
						break;
					case 'c':
					case 'C':
						std::cout << "选择查找操作" << std::endl;
						int target;
						std::cout << "请输入你想查找的节点数据" << std::endl;
						target = input<int>(INT_MIN, INT_MAX);

						if (search(root, target))
							std::cout << "节点" << target << "已被找到！" << std::endl;
						else
							std::cout << "节点" << target << "未被找到" << std::endl;
						std::cout << "操作完成，按回车继续..." << std::endl;
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
