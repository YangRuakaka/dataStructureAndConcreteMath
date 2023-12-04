/****************************************************************
 * Project Name:  ����ϵͳ
 * File Name:     ����ϵͳ.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/8
 ****************************************************************/

/****************************************************************
 * Problem Description
 ****************************************************************/

//���Ա�������������У���������������µ���ս������������������˺ܴ�Ĺ�������
//����Ŀ�ǶԿ��Ա�������ļ�ģ�⣬�ÿ���̨ѡ���ѡ��ʽ������й��ܣ�
//���뿼����Ϣ�����������Ϣ����ѯ������Ϣ����ӿ�����Ϣ���޸Ŀ�����Ϣ��ɾ��������Ϣ��

/****************************************************************
 * Problem Solution
 ****************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>

const int max_input_name = 8;

//Create a structure type to store the information and we want it to be a node in our linked list.
struct student
{
	int num;//The number of the student
	int age;//The age of the student
    char name[max_input_name+1];//The name of the student
	char catagory[11];//The catagory the student applies for
	char gender[3];//The gender of the student
	student* next;//Pointer points to the next node
};

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
 Function Name:clear
 Function:To clear a node 
 Input Parameters:a pointer which points at the node we want to clear
 Return Value:void
 Documentation��
****************************************************************************/
void clear(student* current)
{
	current->num = 0;
	current->age = 0;
	std::strcpy(current->name, "");
	std::strcpy(current->catagory, "");
	std::strcpy(current->gender, "");
	current->next = NULL;
}

/***************************************************************************
 Function Name:Input
 Function:To input data for a node
 Input Parameters:a pointer which points at the node we want to input data for
 Return Value:void
 Documentation��
****************************************************************************/
void Input(student* current)
{
	
	/* Loop to read and process each number from the input */
	while (true) {

		/* Read a number from the input stream */
		std::cin >> current->num >> current->name >> current->gender >> current->age >> current->catagory;
		if (std::cin.fail()) { // Check if the read operation failed (invalid data type)
			std::cerr << "������������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else if (current->num <= 0 || current->num >= INT_MAX) {
			std::cerr << "����ѧ����������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else if (strlen(current->name) > max_input_name) {
			std::cerr << "�������ֳ���������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else if (!(strcmp(current->gender, "��") == 0 || strcmp(current->gender, "Ů") == 0)) {
			std::cerr << "�����Ա���������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else if (current->age <= 0 || current->num >= INT_MAX) {
			std::cerr << "����������������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else if (!(strcmp(current->catagory, "�������ʦ") == 0 || strcmp(current->catagory, "������ʦ") == 0 || strcmp(current->catagory, "�������ʦ") == 0)) {
			std::cerr << "���뱨�������������������" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			clear(current);//Clear the data we just input
		}
		else {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			break;
		}
			
	}


}

class student_List
{
private:
	student* head;//The head pointer
public:

	/***************************************************************************
	 Function Name:student_List
	 Function:To create a new space for the head node
	 Input Parameters:void
	 Return Value:void
	 Documentation��
	****************************************************************************/
	student_List()
	{
		head = new(std::nothrow) student;//Create a head node;
		if (head == NULL) {
			std::cout << "�����ڴ�����ʧ��!" << std::endl;
			return ;
		}
		
	}

	/***************************************************************************
     Function Name:List_insert
     Function:To insert a new element into our linked list
     Input Parameters:void
     Return Value:Bool whether the operation is successful,if it is return 1
     Documentation��
	****************************************************************************/
	bool List_insert() 
	{
		if (head == NULL) {
			std::cout << "����������,���ȴ���!" << std::endl;
			return 0;
		}
		std::cout << "��������Ҫ���뿼����λ��" << std::endl;
		int num;
		while (true) {
			std::cin >> num;
			if (std::cin.fail() || num <= 0) {
				std::cerr << "������������������" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Let the current points to the element we want,always is the one that is previous to the one we are operating on
		student* current = head;
		for (int i = 0; i < num - 1; i++,current=current->next) {
			if (current->next == NULL) {
				//If the current is NULL ,it means that we have gone too far
					std::cout << "��ǰλ���޷�����Ԫ��" << std::endl;
					std::cout << "���β������������س���������һ�ֲ���...";
					pause();
					return 0;
			}

		}

		student* new_current = new(std::nothrow) student;
		if (new_current == NULL) {
			std::cerr << "�ڴ�����ʧ��" << std::endl;
			std::cout << "���β������������س���������һ�ֲ���...";
			pause();
			return 0;
		}

		//Input the new data
		std::cout << "�������뿼���Ŀ��ţ��������Ա����估�������" << std::endl;
		Input(new_current);

		//Insert
		student * temp;
		if (current->next == NULL) {
			current->next = new_current;
			new_current->next = NULL;
		}
		else {
			temp = current->next;
			current->next = new_current;
			new_current->next = temp;
		}

		return 1;

	}
	/***************************************************************************
 	 Function Name:List_delete
	 Function:To delete a new element from our linked list
	 Input Parameters:void
 	 Return Value:Bool whether the operation is successful,if it is return 1
	 Documentation��
	****************************************************************************/
	bool List_delete()
	{
		if (head == NULL) {
			std::cout << "����������,���ȴ���!" << std::endl;
			return 0;
		}
		std::cout << "��������Ҫɾ�������Ŀ���" << std::endl;
		int num;
		while (true) {
			std::cin >> num;
			if (std::cin.fail() || num <= 0) {
				std::cerr << "������������������" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Let the current points to the element we want,always is the one that is previous to the one we are operating on
		for (student* current = head; current->next!= NULL; current = current->next) {
			//If found,display the information,and exit the function
			if (current->next->num == num) {
				//Display the information we are deleting
				std::cout << "ɾ������ѧ����Ϣ��" << std::endl;
				std::cout << std::left << std::setw(8) << "����" << std::setw(8) << "����" << std::setw(8) << "�Ա�" << std::setw(8) << "����" << std::setw(8) << "�������" << std::endl;
				std::cout << std::left << std::setw(8) << current->next->num;
				std::cout << std::left << std::setw(8) << current->next->name;
				std::cout << std::left << std::setw(8) << current->next->gender;
				std::cout << std::left << std::setw(8) << current->next->age;
				std::cout << std::left << std::setw(8) << current->next->catagory;
				std::cout << std::endl;
				//delete
				student* temp = current->next->next;
				delete current->next;
				current->next = temp;
				return 1;
				
			}
		}

		//If not found,display the prompt
		std::cout << "δ���ҵ���ѧ����Ϣ��" << std::endl;
		std::cout << "���β������������س���������һ�ֲ���...";
		pause();
		return 0;


	}
	/***************************************************************************
	 Function Name:List_edit
	 Function:To edit a new element in our linked list
	 Input Parameters:void
	 Return Value:Bool whether the operation is successful,if it is return 1
	 Documentation��
	****************************************************************************/
	bool List_edit()
	{
		if (head == NULL) {
			std::cout << "����������,���ȴ���!" << std::endl;
			return 0;
		}
		std::cout << "��������Ҫ�޸Ŀ�����λ��" << std::endl;
		int num;
		while (true) {
			std::cin >> num;
			if (std::cin.fail() || num <= 0) {
				std::cerr << "������������������" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Let the current points to the element we want,always is the one that is previous to the one we are operating on
		student* current = head;
		for (int i = 0; i < num - 1; i++, current = current->next) {
			if (current->next == NULL) {
				//If the current is NULL ,it means that we have gone too far
				std::cout << "��ǰλ����Ԫ��" << std::endl;
				std::cout << "���β������������س���������һ�ֲ���...";
				pause();
				return 0;
			}

		}

		//Edit
		if (current->next == NULL) {
			//If the current-> is NULL ,it means that we reached the last node and there is no node after it
			std::cout << "��ǰλ����Ԫ��" << std::endl;
			std::cout << "���β������������س���������һ�ֲ���...";
			pause();
			return 0;
		}
		else {
			std::cout << "�������뿼���Ŀ��ţ��������Ա����估�������" << std::endl;
			Input(current->next);
			return 1;
		}


	}
	/***************************************************************************
	 Function Name:List_search
	 Function:To search a element in our linked list
	 Input Parameters:void
	 Return Value:Bool whether the operation is successful,if it is return 1
	 Documentation��
	****************************************************************************/
	bool List_search() 
	{
		if (head == NULL) {
			std::cout << "����������,���ȴ���!" << std::endl;
			return 0;
		}
		std::cout << "��������Ҫ���ҿ����Ŀ���" << std::endl;
		int num;
		while (true) {
			std::cin >> num;
			if (std::cin.fail() || num <= 0) {
				std::cerr << "������������������" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Let the current points to the element we want,always is the one that is previous to the one we are operating on
		for (student* current = head; current!=NULL;current = current->next) {
			//If found,display the information,and exit the function
			if (current->num == num) {
				std::cout << "���ҵ���ѧ����Ϣ��" << std::endl;
				std::cout << std::left << std::setw(8) << "����" << std::setw(8) << "����" << std::setw(8) << "�Ա�" << std::setw(8) << "����" << std::setw(8) << "�������" << std::endl;
				std::cout << std::left << std::setw(8) << current->num;
				std::cout << std::left << std::setw(8) << current->name;
				std::cout << std::left << std::setw(8) << current->gender;
				std::cout << std::left << std::setw(8) << current->age;
				std::cout << std::left << std::setw(8) << current->catagory;
				std::cout << std::endl;
				return 1;
			}
		}

		//If not found,display the prompt
		std::cout << "δ���ҵ���ѧ����Ϣ��" << std::endl;
		std::cout << "���β������������س���������һ�ֲ���...";
		pause();
		return 0;

	}
	/***************************************************************************
	 Function Name:calculateSum
	 Function:To calculate the amount of student in our linked list
	 Input Parameters:void
	 Return Value:Bool whether the operation is successful,if it is return 1
	 Documentation��
	****************************************************************************/
	bool calculateSum()
	{
		if (head == NULL) {
			std::cout << "����������,���ȴ���!" << std::endl;
			return 0;
		}
		if (head->next) {

			int count_male = 0, count_female = 0, total = 0;//Create variables to store the amount
			//Count
			for (student* current = head->next; current != NULL; current = current->next) {
				if (std::strcmp(current->gender, "��") == 0) {
					count_male++;
				}
				else
					count_female++;
			}
			//Sum
			total = count_male + count_female;
			//Display the outcome
			std::cout << "ͳ�ƽ��Ϊ��һ����" << total << "�ˣ�����������" << count_male << "�ˣ�Ů����" << count_female << "��" << std::endl;

			return 1;
		}
		else {
			std::cout<<"�ñ�Ϊ�ձ��޷�ͳ�ƣ�" << std::endl;
			std::cout << "���β������������س���������һ�ֲ���...";
			pause();
			return 0;
		}
		
		
	}
	/***************************************************************************
	 Function Name:List_display
	 Function:To display our linked list
	 Input Parameters:void
	 Return Value:void
	 Documentation��
	****************************************************************************/
	void List_display()
	{
		if (head->next) {

			std::cout << std::left << std::setw(8) << "����" << std::setw(8) << "����" << std::setw(8) << "�Ա�" << std::setw(8) << "����" << std::setw(8) << "�������" << std::endl;
			for (student* current = head->next; current != NULL; current = current->next) {
				std::cout << std::left << std::setw(8) << current->num;
				std::cout << std::left << std::setw(8) << current->name;
				std::cout << std::left << std::setw(8) << current->gender;
				std::cout << std::left << std::setw(8) << current->age;
				std::cout << std::left << std::setw(8) << current->catagory;
				std::cout << std::endl;
			}
			
		}
		else 
			std::cout << "��ǰ����Ϊ�գ�" << std::endl;
		
	}


	/***************************************************************************
	 Function Name:establish
	 Function:To create our linked list
	 Input Parameters:void
	 Return Value:bool
	 Documentation��
	****************************************************************************/
	bool establish()
	{
		if (head == NULL) {
			std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
			return 0;
		}

		std::cout << "�뽨��������Ϣϵͳ" << std::endl;
		std::cout << "�����뿼������" << std::endl;

		int num;
		while (true) {
			std::cin >> num;
			if (std::cin.fail() || num <= 0) {
				std::cerr << "������������������" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		

		head->next = new(std::nothrow) student;//Create the first node
		if (head->next == NULL) {
			std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
			return 0;
		}

		std::cout << "�������뿼���Ŀ��ţ��������Ա����估�������" << std::endl;
		Input(head->next);

		student* last = head->next;//Last is pointing at the previous one 

		for (int i = 0; i < num - 1; i++) {
			student* current = new(std::nothrow) student;//New a new space for the new student
			if (current == NULL) {
				std::cerr << "��������ʱ�ڴ�����ʧ�ܣ��������" << std::endl;
				return 0;
			}
			last->next = current;//The previous one's next-pointer is pointing at the current one
			Input(current);//Input the data
			last = current;//And now the pointer 'last' is updated because we want to go to the next one and the current one becomes a 'last'
		}

		last->next = NULL;//At the end of the 'for' loop,the last student's pointer is not pointing to anything as we want it to point at NULL

		return 1;
	}

	/***************************************************************************
	 Function Name:~student_List
	 Function:To delete all the space we created in this class
	 Input Parameters:void
	 Return Value:void
	 Documentation��
	****************************************************************************/
	~student_List()
	{
		for (student* current = head; current != NULL;) {
			student* temp = current->next;
			delete current;
			current = temp;
		}
	}
};



int main()
{
	//Create a new list
	student_List List;

	//Establish our list��if fail ,exit the program
	if (List.establish())
		;
	else
		return 0;
	
	//The loop can let the user execute the process repeatedly
	while (true) {
		//Clear our screen
		system("cls");

		//Display our list
		std::cout << "��ǰ����ϵͳ����" << std::endl;
		List.List_display();

		//Display the prompt
		std::cout << "ѡ���㵱ǰҪ���еĲ�����0Ϊ�˳���1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�" << std::endl;
		char controller;//Create a variable to hold the choice we input
		while (true) {
			controller = _getch();//_getch can avoid displaying undesired input on the screen
			if (controller >= '0' && controller <= '5') {
				std::cout << controller << std::endl;//Display the choice on the screen
				switch (controller)
				{
					case '0':
						std::cout << "���������" << std::endl;
						return 0;
					case '1':
						std::cout << "ѡ����1�����в������" << std::endl;
						if (List.List_insert()) {
							std::cout << std::endl;
							std::cout << "���β�����ɣ����س���������һ�ֲ���...";
							pause();
						}
						break;
					case '2':
						std::cout << "ѡ����2������ɾ������" << std::endl;
						if (List.List_delete()) {
							std::cout << std::endl;
							std::cout << "���β�����ɣ����س���������һ�ֲ���...";
							pause();
						}
						break;
					case '3':
						std::cout << "ѡ����3�����в��Ҳ���" << std::endl;
						if (List.List_search()) {
							std::cout << std::endl;
							std::cout << "���β�����ɣ����س���������һ�ֲ���...";
							pause();
						}
						break;
					case '4':
						std::cout << "ѡ����4�������޸Ĳ���" << std::endl;
						if (List.List_edit()) {
							std::cout << std::endl;
							std::cout << "���β�����ɣ����س���������һ�ֲ���...";
							pause();
						}
						break;
					case '5':
						std::cout << "ѡ����5������ͳ�Ʋ���" << std::endl;
						if (List.calculateSum()){
						std::cout << std::endl;
							std::cout << "���β�����ɣ����س���������һ�ֲ���...";
							pause();
						}
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