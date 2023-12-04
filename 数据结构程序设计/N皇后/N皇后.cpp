/****************************************************************
 * Project Name:  N�ʺ�
 * File Name:     N�ʺ�.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/22
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//�˻ʺ�������һ�����϶����������⣬�ǻ����㷨�ľ������⡣
//��������ʮ��������������ѧ�Ҹ�˹��1850������ģ�
//��8 * 8�Ĺ������������ϣ�����8���ʺ�Ҫ��û��һ���ʺ��ܹ����Ե����κ�����һ���ʺ�
//�����������ʺ��ܴ���ͬһ�У�ͬһ�л���ͬһ���Խ����ϣ�����ж����ְڷ���

 /****************************************************************
  * Problem Solution
  ****************************************************************/


#include <iostream>
#include <conio.h>

const int l_limit = 1;
const int U_limit = 20;

using std::cerr;
using std::cout;
using std::endl;
using std::cin;

/***************************************************************************
 Function Name:printSolution
 Function:To print the solution
 Input Parameters:the board and its size
 Return Value:void
 Documentation��
****************************************************************************/
void printSolution(char** board, int N)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/***************************************************************************
 Function Name:isSafe
 Function:To judge whether the queen can be placed in this position
 Input Parameters:board position(row and column) size
 Return Value:true for safe,false for not safe
 Documentation��
****************************************************************************/
bool isSafe( char** board, int row, int col, int N)
{
    //If at the same column,not safe
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 'X') {
            return false;
        }
    }

    //If the same diagonal,not safe(check left)
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'X') {
            return false;
        }
    }

    //If the same diagonal,not safe(check right)
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 'X') {
            return false;
        }
    }

    //Is safe
    return true;
}

/***************************************************************************
 Function Name:solveNQueensUtil
 Function:To place the queen safely until we reached the bottom
 Input Parameters:board row size amount of result
 Return Value:
 Documentation��
****************************************************************************/
void solveNQueensUtil(char** board, int row, int N,int &total) 
{
    //If we reached the bottom,we it means we have placed all the queens
    if (row == N) {
        printSolution(board, N);//Print it out
        total++;
        return ;//Termination condition
    }
   

    //Try every position in every row
    for (int i = 0; i < N; i++) {
        if (isSafe(board, row, i, N)) {
            board[row][i] = 'X';//If queen can be placed in this position
            solveNQueensUtil(board, row + 1, N, total);//Place the queen and go to the next row
            board[row][i] = '0';//After we place all the queen reset the position
        }
    }
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
        cin >> num;
        if (std::cin.fail() || num < l_limit || num > U_limit) {
            std::cerr << "������������������" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return num;
    }
}

/***************************************************************************
 Function Name:solveNQueens
 Function:To sovle the problem
 Input Parameters:The amount of queens
 Return Value:void
 Documentation��
****************************************************************************/
void solveNQueens(int N) 
{

    int total = 0;
    char** Board = new char* [N];
    if (Board == NULL) {
        cerr << "�ڴ�����ʧ��" << endl;
        return ;
    }

    for (int i = 0; i < N; i++) {
        Board[i] = new char[N];
        if (Board[i] == NULL) {
            cerr << "�ڴ�����ʧ��" << endl;
            return ;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            Board[i][j] = '0';
        }
    }

   solveNQueensUtil(Board, 0, N, total);

    if (total)
        cout << "һ����" << total << "�ֽⷨ" << endl;
    else
        cout << "�����ڽⷨ" << endl;

    //Release memory
    for (int i = 0; i < N; ++i) {
        delete[] Board[i];
    }
    delete[] Board;
}

int main() 
{
    int N;

    while (true) {

        //Clear our screen
        system("cls");

        std::cout << "������ʺ������1-20�� ";
        N = input<int>(l_limit, U_limit);

        solveNQueens(N);

        //Display the prompt
        std::cout << "��0�˳�������������" << std::endl;
        char controller;//Create a variable to hold the choice we input
        controller = _getch();//_getch can avoid displaying undesired input on the screen
        if (controller == '0') {
            std::cout << "���������" << std::endl;
            return 0;
        }

    }//end of while

    return 0;
}
