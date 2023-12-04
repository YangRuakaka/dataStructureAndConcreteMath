/****************************************************************
 * Project Name:  约瑟夫生死游戏
 * File Name:     约瑟夫生死游戏.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/19
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//约瑟夫生者死者游戏的大意是：30个旅客同乘一条船，因为严重超载，加上风高浪大危险万分；
//因此船长告诉乘客，只有将全船一半的旅客投入海中，其余人才能幸免于难。
//无奈，大家只得统一这种方法，并议定30个人围成一圈，由第一个人开始，依次报数，
//数到第9人，便将他投入大海中，然后从他的下一个人数起，数到第9人，再将他投入大海，
//如此循环，直到剩下15个乘客为止。问哪些位置是将被扔下大海的位置。

  /****************************************************************
   * Problem Solution
   ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;

const int N_l_limit = 10;
const int N_U_limit = 50;
const int S_l_limit = 1;
const int M_l_limit = 0;
const int K_l_limit = 0;



/***************************************************************************
 Function Name:input
 Function:To input the data
 Input Parameters:limits
 Return Value:input value
 Documentation：
****************************************************************************/
template<typename T>
T input(T l_limit,T U_limit)
{
	T num;
	while (true) {
		cin >> num;
		if (std::cin.fail() || num < l_limit || num > U_limit) {
			std::cerr << "输入有误，请重新输入" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
			return num;
	}
}

//Create a structure type to store the information and we want it to be a node in our linked list.
struct Player
{
	int num;//The number of the player
	bool alive;//Dead for false,alive for true
	Player* next;//Pointer points to the next player
};


class Player_list {
private:
	Player* head;
	Player* end;//A pointer points at the last player
public:
	/***************************************************************************
	 Function Name:Player_list
	 Function:Establish the list
	 Input Parameters:The amount of the player
	 Return Value:void
	 Documentation：
	****************************************************************************/
	Player_list(int N)
	{
		head = new(std::nothrow) Player;//Create a head node;
		if (head == NULL) {
			cout << "内存申请失败" << endl;
			return;
		}
		head->num = N;//Store the amount
		head->alive = true;
		head->next = new(std::nothrow) Player;//Points at the first element

		Player* Last = head->next;
		head->next->num = 1;//The first element is No.1
		head->next->alive = true;
		for (int i = 1; i < N; i++) {
			Player* current = new Player;//New a new space for the new student
			if (current == NULL) {
				std::cerr << "建立链表时内存申请失败，程序结束" << std::endl;
				return;
			}
			current->num = i + 1;
			current->alive = true;
			Last->next = current;//And now the pointer 'last' is updated because we want to go to the next one and the current one becomes a 'last'
			Last = current;//The previous one's next-pointer is pointing at the current one
		}

		//Set the 'Last' pointer
		Last->next = head->next;
		end = Last;

	}
	/***************************************************************************
	 Function Name:Display_the_death
	 Function:Kill the people and display the position
	 Input Parameters:The amount of the player,start position,death number,amount of survivor
	 Return Value:void
	 Documentation：
	****************************************************************************/
	void Display_the_death(int N, int S, int M, int K)
	{
	
		Player* Deathmark = head;//Create a pointer to kill the people

		//Move the starter to the start position
		for (int i = 1; i < S; i++) {
			Deathmark = Deathmark->next;
		}

		//Use a loop to kill
		for (int i = 0; i < N - K; i++) {
			for (int count = 0; count < M; ) {
				Deathmark = Deathmark->next;
				if (Deathmark->alive)//Only count the people alive
					count++;
			}
			Deathmark->alive = false;//Kill the people
			cout << "第" << i + 1 << "个死者的位置是：" << Deathmark->num << endl;//Display the information
			
		}//Kill N-K people

		//Display the settlement
		cout << endl;
		cout << std::left << std::setw(20) << "最后剩下" << K << "人" << endl;
		cout <<"剩余生者位置为:" << endl;
		//Display all the people that are still alive
		for (Player* current = head->next; current != end;) {
			if (current->alive)
				cout << std::right << std::setw(8) << current->num;
			current = current->next;
		}
		if(end->alive)
			cout << std::right << std::setw(8) << end->num;
		cout << endl;
	
	}

	/***************************************************************************
	 Function Name:reset
	 Function:respawn
	 Input Parameters:void
	 Return Value:void
	 Documentation：
	****************************************************************************/
	void reset()
	{
		for (Player* current = head->next; current != end;) {
			current->alive = true;
			current = current->next;
		}
		end->alive = true;
	}
	/***************************************************************************
	 Function Name:~student_List
	 Function:To delete all the space we created in this class
	 Input Parameters:void
	 Return Value:void
	 Documentation：
	****************************************************************************/
	~Player_list()
	{
		for (Player* current = head; current != end;) {
			Player* temp = current->next;
			delete current;
			current = temp;
		}
		head = NULL;
		end = NULL;
	}
};

int main()
{
	int N, S, M, K;

	//Display the prompt and let the client input
	cout << "请输入游戏人数(10-50)" << endl;
	N = input<int>(N_l_limit, N_U_limit);

	//Create a new list
	Player_list List(N);

	while (true) {

		//Clear our screen
		system("cls");

		std::cout << "请输入开始位置(1-" << N << ")" << endl;
		S = input<int>(S_l_limit, N);
		cout << "请输入死亡数字(0-" << N << ")" << endl;
		M = input<int>(M_l_limit, N);
		std::cout << "请输入剩余生者数(0-" << N << ")" << endl;
		K = input<int>(K_l_limit, N);

		//Clear our screen
		system("cls");

		//Display our condition
		std::cout << "当前游戏人数N:" << N << std::endl;
		std::cout << "当前开始位置S:" << S << std::endl;
		std::cout << "当前死亡数字M:" << M << std::endl;
		std::cout << "当前存活人数K:" << K << std::endl;
		cout << endl;

		List.Display_the_death(N, S, M, K);

		List.reset();

		//Display the prompt
		std::cout << "按0退出，其他键继续" << std::endl;
		char controller;//Create a variable to hold the choice we input
		controller = _getch();//_getch can avoid displaying undesired input on the screen
		if (controller == '0') {
			std::cout << "程序结束！" << std::endl;
			return 0;
		}

	}//end of while

	return 0;
}