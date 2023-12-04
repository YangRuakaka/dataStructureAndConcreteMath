/****************************************************************
 * Project Name:  表达式
 * File Name:     表达式.cpp
 * File Function: Problem solution
 * Update Date:   2023/11/1
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//为了实现表达式求值，本项目要求首先读入表达式（包括括号）并创建对应二叉树，
//其次对二叉树进行前序遍历，中序遍历，后续遍历，输出对应的逆波兰式，中序表达式和波兰表达式。

/****************************************************************
* Problem Solution
****************************************************************/

#include <iostream>

//TreeNode
class TreeNode {
public:
    int data;
    char op;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int data ,char val) : data(data), op(val),left(nullptr), right(nullptr) {}
};

//MYSTACK
class MyStack {
private:
    TreeNode** data;//An array in which all the elements are a pointer pointing to the treenode
    int capacity;
    int top;//Top index

public:
    MyStack(int cap); //Initialize the the stack(mallocate a space)
    ~MyStack();//Destory the memory
    void push(TreeNode* node);//Push a tree node in the stack
    TreeNode* pop();//Pop out a tree node
    TreeNode* peek();//Get the top of the stack
    bool isEmpty();//Check whether the stack is empty
};

/***************************************************************************
Function Name:MyStack
Function:To initialize the the stack(mallocate a space)
Input Parameters:the capacity
Return Value:void
Documentation：
****************************************************************************/
MyStack::MyStack(int cap) : capacity(cap), top(-1)
{
    data = new(std::nothrow) TreeNode * [capacity];
    if (data == NULL) {
        std::cout << "栈内存申请失败！" << std::endl;
        return;
    }
}

/***************************************************************************
Function Name:~MyStack
Function:To destory the memory
Input Parameters:void
Return Value:void
Documentation：
****************************************************************************/
MyStack::~MyStack()
{
    delete[] data;
}

/***************************************************************************
Function Name:push
Function:To push a tree node in the stack
Input Parameters:a pointer to the treenode
Return Value:void
Documentation：
****************************************************************************/
void MyStack::push(TreeNode* node)
{
    if (data == NULL) {
        std::cout << "当前栈不存在" << std::endl;
        return;
    }
    if (top < capacity - 1)
        data[++top] = node;
}

/***************************************************************************
Function Name:pop
Function:To pop out a tree node
Input Parameters:void
Return Value:void
Documentation：
****************************************************************************/
TreeNode* MyStack::pop()
{
    if (data == NULL) {
        std::cout << "当前栈不存在" << std::endl;
        return NULL;
    }
    if (top >= 0)
        return data[top--];
    return nullptr; // Error: Stack is empty
}

/***************************************************************************
Function Name:peek
Function:To get the top element
Input Parameters:void
Return Value:void
Documentation：
****************************************************************************/
TreeNode* MyStack::peek()
{
    if (data == NULL) {
        std::cout << "当前栈不存在" << std::endl;
        return NULL;
    }
    if (top >= 0)
        return data[top];
    return nullptr; // Error: Stack is empty
}

/***************************************************************************
Function Name:isEmpty
Function:To check whether the stack is empty
Input Parameters:void
Return Value:void
Documentation：
****************************************************************************/
bool MyStack::isEmpty()
{
    if (data == NULL) {
        std::cout << "当前栈不存在" << std::endl;
        return false;
    }
    return top == -1;
}

/***************************************************************************
Function Name:isOperator
Function:To check whether the char is an operator
Input Parameters:a char
Return Value:void
Documentation：
****************************************************************************/
bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

/***************************************************************************
Function Name:getPrecedence
Function:To calculate the precedence of the operator
Input Parameters:an operator
Return Value:Precedence
Documentation：
****************************************************************************/
int getPrecedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

/***************************************************************************
Function Name:createExpressionTree
Function:To create the expression tree
Input Parameters:an expression an index
Return Value:void
Documentation：
****************************************************************************/
TreeNode* createExpressionTree(const char* expression, int& pos) 
{
    MyStack nodes(100); // Max capacity of 100, adjust as needed
    MyStack operators(100); // Stack to hold operators

    //Read until end
    while (expression[pos] != '\0') {

        char token = expression[pos];//The char we are checking

        if (isdigit(token)) {
            int operand = 0;//Calculate its value

            while (isdigit(expression[pos])) {
                operand = operand * 10 + (expression[pos] - '0');
                ++pos;
            }//Caculate the number 
            TreeNode* operandNode = new TreeNode(operand, '\0');//Create a treenode to store it
            nodes.push(operandNode);//Push it into the nodes
        }
        else if (isOperator(token)) {
            //If the operatorsstack is not empty and the operators we are checking is prior
            while (!operators.isEmpty() &&  getPrecedence(operators.peek()->op) >= getPrecedence(token)) {
                TreeNode* operatorNode = operators.pop();//Get the operators top element
                TreeNode* rightNode = nodes.pop();//Get the top two elements in nodesstack
                TreeNode* leftNode = nodes.pop();
                operatorNode->left = leftNode;//Connect these two elements(operatorsNode is the root)
                operatorNode->right = rightNode;
                nodes.push(operatorNode);//Push the operatorsNode into the node stack
            }
            //If not ,just put the operate into the stack directly without any processing
            TreeNode* operatorNode = new TreeNode(0, token);
            operators.push(operatorNode);
            ++pos;//Index++
        }
        else if (token == '(') {
            ++pos;
            TreeNode* subexpression = createExpressionTree(expression, pos); //Create a subexpression and make it a node
            ++pos; // Skip ')'
            nodes.push(subexpression);
        }
        else if (token == ')') 
            break;//If thers is a ')',then process
        else 
            ++pos;//Read a blank or something unimportant
    }
    //Process until the operatorsstack is empty
    while (!operators.isEmpty()) {
        TreeNode* operatorNode = operators.pop();//Get the operators top element
        TreeNode* rightNode = nodes.pop();//Get the top two elements in nodesstack
        TreeNode* leftNode = nodes.pop();
        operatorNode->left = leftNode;//Connect these two elements(operatorsNode is the root)
        operatorNode->right = rightNode;
        nodes.push(operatorNode);//Push the operatorsNode into the node stack
    }

    return nodes.pop();//There will be only a root treenode in this stack
}

/***************************************************************************
Function Name:printorder
Function:To print the tree in a order
Input Parameters:the root of the tree
Return Value:void
Documentation：
****************************************************************************/
void printorder(TreeNode* root) {
    if (root) {
        if (root->op != '\0')
            std::cout << root->op << ' ';
        else
            std::cout << root->data << ' ';
        printorder(root->left);
        printorder(root->right);
    }
}

/***************************************************************************
Function Name:printInorder
Function:To print the tree in a inorder
Input Parameters:the root of the tree
Return Value:void
Documentation：
****************************************************************************/
void printInorder(TreeNode* root) {
    if (root) {
        printInorder(root->left);
        if (root->op != '\0')
            std::cout << root->op << ' ';
        else
            std::cout << root->data << ' ';
        printInorder(root->right);
    }
}

/***************************************************************************
Function Name:printPostorder
Function:To print the tree in a post order
Input Parameters:the root of the tree
Return Value:void
Documentation：
****************************************************************************/
void printPostorder(TreeNode* root) {
    if (root) {
        printPostorder(root->left);
        printPostorder(root->right);
        if (root->op != '\0')
            std::cout << root->op << ' ';
        else
            std::cout << root->data << ' ';
    }
}

/***************************************************************************
Function Name:evaluateExpression
Function:To calculate the result
Input Parameters:the root of the tree
Return Value:void
Documentation：
****************************************************************************/
int evaluateExpression(TreeNode* root) {
    if (!root) //If there is no root ,return 
        return 0;
    
    if (root->op == '\0') //If read a number,return it
        return root->data;
    

    int leftValue = evaluateExpression(root->left);
    int rightValue = evaluateExpression(root->right);

    //If read an operator
    switch (root->op) {
        //Caculate
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            if (rightValue != 0) {
                return leftValue / rightValue;
            }
            else {
                std::cerr << "零不能作为除数！" << std::endl;
                exit(1);
            }
    }

    return 0; //In case of unexpected operator
}

int main() {

    char infixExpression[100];
    std::cout << "请输入表达式" << std::endl;
    std::cin.getline(infixExpression,100);

    int pos = 0;
    TreeNode* expressionTree = createExpressionTree(infixExpression, pos);

    std::cout << "原表达式: " << infixExpression << std::endl;
    std::cout << "中序表达式: ";
    printInorder(expressionTree);
    std::cout << std::endl;

    std::cout << "逆波兰式: ";
    printPostorder(expressionTree);
    std::cout << std::endl;

    std::cout << "波兰表达式: ";
    printorder(expressionTree);
    std::cout << std::endl;

    int result = evaluateExpression(expressionTree);
    std::cout << "结果: " << result << std::endl;

   
    return 0;
}
