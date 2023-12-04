/****************************************************************
 * Project Name:  Լɪ��������Ϸ
 * File Name:     Լɪ��������Ϸ.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/19
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//Լɪ������������Ϸ�Ĵ����ǣ�30���ÿ�ͬ��һ��������Ϊ���س��أ����Ϸ���˴�Σ����֣�
//��˴������߳˿ͣ�ֻ�н�ȫ��һ����ÿ�Ͷ�뺣�У������˲����������ѡ�
//���Σ����ֻ��ͳһ���ַ��������鶨30����Χ��һȦ���ɵ�һ���˿�ʼ�����α�����
//������9�ˣ��㽫��Ͷ����У�Ȼ���������һ��������������9�ˣ��ٽ���Ͷ��󺣣�
//���ѭ����ֱ��ʣ��15���˿�Ϊֹ������Щλ���ǽ������´󺣵�λ�á�

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
 Documentation��
****************************************************************************/
template<typename T>
T input(T l_limit,T U_limit)
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
	 Documentation��
	****************************************************************************/
	Player_list(int N)
	{
		head = new(std::nothrow) Player;//Create a head node;
		if (head == NULL) {
			cout << "�ڴ�����ʧ��" << endl;
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
				std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
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
	 Documentation��
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
			cout << "��" << i + 1 << "�����ߵ�λ���ǣ�" << Deathmark->num << endl;//Display the information
			
		}//Kill N-K people

		//Display the settlement
		cout << endl;
		cout << std::left << std::setw(20) << "���ʣ��" << K << "��" << endl;
		cout <<"ʣ������λ��Ϊ:" << endl;
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
	 Documentation��
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
	 Documentation��
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
	cout << "��������Ϸ����(10-50)" << endl;
	N = input<int>(N_l_limit, N_U_limit);

	//Create a new list
	Player_list List(N);

	while (true) {

		//Clear our screen
		system("cls");

		std::cout << "�����뿪ʼλ��(1-" << N << ")" << endl;
		S = input<int>(S_l_limit, N);
		cout << "��������������(0-" << N << ")" << endl;
		M = input<int>(M_l_limit, N);
		std::cout << "������ʣ��������(0-" << N << ")" << endl;
		K = input<int>(K_l_limit, N);

		//Clear our screen
		system("cls");

		//Display our condition
		std::cout << "��ǰ��Ϸ����N:" << N << std::endl;
		std::cout << "��ǰ��ʼλ��S:" << S << std::endl;
		std::cout << "��ǰ��������M:" << M << std::endl;
		std::cout << "��ǰ�������K:" << K << std::endl;
		cout << endl;

		List.Display_the_death(N, S, M, K);

		List.reset();

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