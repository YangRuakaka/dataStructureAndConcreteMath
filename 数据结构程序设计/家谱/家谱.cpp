/****************************************************************
 * Project Name:  家谱
 * File Name:     家谱.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/29
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

  //本项目的实质是完成兑家谱成员信息的建立，查找，插入，修改，删除等功能，
  //可以首先定义家族成员数据结构，然后将每个功能作为一个成员函数来完成对数据的操作，
  //最后完成主函数以验证各个函数功能并得到运行结果。

  /****************************************************************
  * Problem Solution
  ****************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>

#define max_input_name 20

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

struct FamilyMember {

    char name[20];
    int age;
    FamilyMember* firstChild;
    FamilyMember* nextSibling;

    FamilyMember() : name(" "), age(0), firstChild(nullptr), nextSibling(nullptr) {}
};

/***************************************************************************
 Function Name:MenuDisplay
 Function:To display the menu
 Input Parameters:void
 Return Value:void
 Documentation：
****************************************************************************/
void MenuDisplay()
{
    std::cout << "            家谱管理系统            " << std::endl;
    std::cout << "====================================" << std::endl;
    std::cout << "  *         A---建立家谱         *  " << std::endl;
    std::cout << "  *         B---添加成员         *  " << std::endl;
    std::cout << "  *         C---解散局部家庭     *  " << std::endl;
    std::cout << "  *         D---修改成员         *  " << std::endl;
    std::cout << "  *         Q---退出程序         *  " << std::endl;
    std::cout << "====================================" << std::endl;
}

/***************************************************************************
 Function Name:inputname
 Function:To input the name
 Input Parameters:void
 Return Value:The address of the string
 Documentation：
****************************************************************************/
void inputname(char* name)
{
    char inputname[max_input_name];
    /* Loop to read and process each number from the input */
    while (true) {
        /* Read a number from the input stream */
        std::cin >> inputname;
        if (std::cin.fail()) { // Check if the read operation failed (invalid data type)
            std::cerr << "输入有误，请重新输入" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            strcpy_s(inputname, "");
        }
        else if (strlen(inputname) > max_input_name) {
            std::cerr << "输入名字超长，请重新输入" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            strcpy_s(inputname, "");
        }
        else {
            strcpy(name, inputname);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
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
class FamilyTree {
private:
    FamilyMember* root;

public:

    /***************************************************************************
     Function Name:FamilyTree
     Function:To initialize the root of the tree
     Input Parameters:Root's name and age
     Return Value:void
     Documentation：
    ****************************************************************************/
    FamilyTree(char* name, int age)
    {
        root = new(std::nothrow) FamilyMember;
        if (root == NULL) {
            std::cout << "家谱内存申请失败" << std::endl;
            return;
        }
        strcpy_s(root->name, name);
        root->age = age;
    }
    /***************************************************************************
     Function Name:addChild
     Function:Add a child to a member
     Input Parameters:char* parentName, char* childName, int childAge
     Return Value:void
     Documentation：
    ****************************************************************************/
    void addChild(char* parentName, char* childName, int childAge)
    {
        FamilyMember* parent = findMember(root, parentName);
        if (parent == nullptr) {
            std::cout << "未找到双亲" << std::endl;
            return;
        }
        if (parent->firstChild == nullptr) {
            parent->firstChild = new(std::nothrow) FamilyMember;
            if (parent->firstChild == NULL) {
                std::cout << "家谱内存申请失败" << std::endl;
                return;
            }
            parent->firstChild->age = childAge;
            strcpy_s(parent->firstChild->name, childName);
        }
        else {
            FamilyMember* sibling = parent->firstChild;
            while (sibling->nextSibling != nullptr) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = new(std::nothrow) FamilyMember;
            if (sibling->nextSibling == NULL) {
                std::cout << "家谱内存申请失败" << std::endl;
                return;
            }
            sibling->nextSibling->age = childAge;
            strcpy_s(sibling->nextSibling->name, childName);
            sibling->nextSibling->nextSibling = nullptr;
        }
        std::cout << "将" << childName << "加入到" << parentName << "的家庭" << std::endl;
    }


    /***************************************************************************
     Function Name:findMember
     Function: Find a member by name
     Input Parameters:FamilyMember* current, char* name
     Return Value:void
     Documentation：
    ****************************************************************************/
    FamilyMember* findMember(FamilyMember* current, char* name)
    {
        if (current == nullptr) {
            return nullptr;
        }
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        FamilyMember* foundInChildren = findMember(current->firstChild, name);
        if (foundInChildren != nullptr) {
            return foundInChildren;
        }
        return findMember(current->nextSibling, name);
    }

    /***************************************************************************
     Function Name:findParent
     Function: Find a member by name
     Input Parameters:FamilyMember* start, char* childName
     Return Value:FamilyMember ptr
     Documentation：
    ****************************************************************************/
    FamilyMember* findParent(FamilyMember* start, char* childName)
    {
        if (start == nullptr) {
            return nullptr;
        }

        FamilyMember* child = start->firstChild;
        while (child != nullptr) {
            if (strcmp(child->name, childName) == 0) {
                return start;
            }
            FamilyMember* parent = findParent(child, childName);
            if (parent != nullptr) {
                return parent;
            }
            child = child->nextSibling;
        }

        return nullptr;
    }


    /***************************************************************************
     Function Name:printFamilyTree
     Function: Print the tree
     Input Parameters:FamilyMember* current, int level
     Return Value:void
     Documentation：
    ****************************************************************************/
    void printFamilyTree(FamilyMember* current, int level)
    {
        if (current == nullptr) {
            return;
        }
        for (int i = 0; i < level; i++) {
            std::cout << "--";
        }
        std::cout << "|_" << current->name << " (" << current->age << ")" << std::endl;
        printFamilyTree(current->firstChild, level + 1);
        printFamilyTree(current->nextSibling, level);
    }

    /***************************************************************************
     Function Name:getRoot
     Function: get the root ptr
     Input Parameters:void
     Return Value:ptr of the root
     Documentation：
    ****************************************************************************/
    FamilyMember* getRoot()
    {
        return root;
    }

    /***************************************************************************
     Function Name:modifyMember
     Function:To modify the information of a member
     Input Parameters:char* name,char* newName, int newAge
     Return Value:void
     Documentation：
    ****************************************************************************/
    void modifyMember(char* name, char* newName, int newAge)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            strcpy_s(member->name, newName);
            member->age = newAge;
            std::cout << "修改了" << name << "的信息" << std::endl;
        }
        else {
            std::cout << "未找到该成员" << std::endl;
        }
    }

    /***************************************************************************
     Function Name:deleteSubtree
     Function:To delete a member and its subtree
     Input Parameters:FamilyMember* member
     Return Value:void
     Documentation：
    ****************************************************************************/
    void deleteSubtree(FamilyMember* member)
    {
        if (member == nullptr) {
            return;
        }
        FamilyMember* child;
        child = member->firstChild;
        while (child != NULL) {
            FamilyMember* temp;
            temp = child->nextSibling;
            deleteSubtree(child);
            child = temp;
        }

        delete member;
    }

    /***************************************************************************
     Function Name:disbandFamily
     Function:To disband a family
     Input Parameters:char* name
     Return Value:void
     Documentation：
    ****************************************************************************/
    void disbandFamily(char* name)
    {
        FamilyMember* member = findMember(root, name);
        if (member != nullptr) {
            if (member == root) {
                std::cout << "不能解散整个家庭" << std::endl;
                return;
            }
            FamilyMember* parent = findParent(root, member->name);
            if (parent->firstChild == member)
                parent->firstChild = parent->firstChild->nextSibling;
            else {
                FamilyMember* child = parent->firstChild;
                while (child->nextSibling != member) {
                    child = child->nextSibling;
                }
                child->nextSibling = child->nextSibling->nextSibling;
            }
            deleteSubtree(member);
            std::cout << "已解散" << name << "的家庭" << std::endl;
        }
        else {
            std::cout << "未找到该成员" << std::endl;
        }
    }
};

int main() 
{

    //Display our list
    MenuDisplay();

    while (true) {
        char controller = _getch();//_getch can avoid displaying undesired input on the screen
        if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
            std::cout << controller << std::endl;//Display the choice on the screen
            switch (controller)
            {
                case 'q':
                case 'Q':
                    std::cout << "程序结束！" << std::endl;
                    return 0;
                case 'a':
                case 'A':
                    break;
                default:
                    std::cout << "请先建立家谱！" << std::endl;
                    continue;
            }
            break;
        }//end of if
    }//end of while

    int Ancestorsage;
    char AncestorsName[max_input_name];
    std::cout << "请输入祖先姓名" << std::endl;
    inputname(AncestorsName);
    std::cout << "请输入祖先年龄" << std::endl;
    Ancestorsage = input<int>(0, 100000000);
    FamilyTree family(AncestorsName, Ancestorsage);
    family.printFamilyTree(family.getRoot(), 0);
    std::cout << std::endl;
    std::cout << "本次操作完成，按回车键进行新一轮操作...";
    pause();

    while (true) {

        //Clear our screen
        system("cls");

        //Display our prompt
        MenuDisplay();


        char controller;//Create a variable to hold the choice we input
        while (true) {
            controller = _getch();//_getch can avoid displaying undesired input on the screen
            if ((controller >= 'A' && controller <= 'D') || controller == 'Q' || controller == 'q' || (controller >= 'a' && controller <= 'd')) {
                std::cout << controller << std::endl;//Display the choice on the screen
                switch (controller)
                {
                    case 'q':
                    case 'Q':
                        std::cout << "程序结束！" << std::endl;
                        return 0;

                    case 'a':
                    case 'A':
                        std::cout << "不可重复建立家谱！" << std::endl;
                        std::cout << std::endl;
                        std::cout << "本次操作完成，按回车键进行新一轮操作...";
                        pause();
                        break;

                    case 'b':
                    case 'B':
                        std::cout << "选择了 B---添加成员，进行添加成员操作" << std::endl;
                        {
                            int age;
                            char Pname[max_input_name];
                            char Nname[max_input_name];
                            std::cout << "请输入双亲姓名" << std::endl;
                            inputname(Pname);
                            std::cout << "请输入新添加成员姓名" << std::endl;
                            inputname(Nname);
                            std::cout << "请输入新添加成员年龄" << std::endl;
                            age = input<int>(0, 100000000);
                            family.addChild(Pname, Nname, age);
                        }
                        family.printFamilyTree(family.getRoot(), 0);
                        std::cout << std::endl;
                        std::cout << "本次操作完成，按回车键进行新一轮操作...";
                        pause();
                        break;
                    case 'c':
                    case 'C':
                        std::cout << "选择了 C---解散局部家庭，进行解散局部家庭操作" << std::endl;
                        {
                            char name[max_input_name];
                            std::cout << "请输入解散局部家庭成员姓名" << std::endl;
                            inputname(name);
                            family.disbandFamily(name);
                            family.printFamilyTree(family.getRoot(), 0);
                        }
                        std::cout << std::endl;
                        std::cout << "本次操作完成，按回车键进行新一轮操作...";
                        pause();
                        break;
                    case 'D':
                    case 'd':
                        std::cout << "选择了 D---修改成员，进行修改成员操作" << std::endl;
                        {
                            int age;
                            char name[max_input_name];
                            char Nname[max_input_name];
                            std::cout << "请输入修改成员原姓名" << std::endl;
                            inputname(name);
                            std::cout << "请输入修改成员现姓名" << std::endl;
                            inputname(Nname);
                            std::cout << "请输入修改成员现年龄" << std::endl;
                            age = input<int>(0, 100000000);
                            family.modifyMember(name, Nname, age);
                            family.printFamilyTree(family.getRoot(), 0);
                        }
                        std::cout << std::endl;
                        std::cout << "本次操作完成，按回车键进行新一轮操作...";
                        pause();
                        break;
                    default:
                        continue;
                }
                break;
            }//end of if
        }//end of while

    }

    return 0;
}


