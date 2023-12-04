/****************************************************************
 * Project Name:  迷宫
 * File Name:     迷宫.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/19
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//迷宫只有两个门，一个门叫入口，另一个门叫出口。
//一个骑士骑马从入口进入迷宫，迷宫设置很多障碍，
//骑士需要在迷宫中寻找通路以到达出口。

  /****************************************************************
   * Problem Solution
   ****************************************************************/

#include<iostream>
#include <conio.h>
#include <random>

#define start_x 1
#define start_y 1
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

//Define four directions
enum Direction { UP, DOWN, LEFT, RIGHT };

/***************************************************************************
 Function Name:shuffleArray
 Function:Shuffle the array
 Input Parameters:array and size
 Return Value:void
 Documentation：
****************************************************************************/
void shuffleArray(int arr[], int size)
{

    //Using the random device
    std::random_device rd;
    std::mt19937 gen(rd());


    //from the last element
    for (int i = size - 1; i > 0; --i) {
        //Generate a random number ranging 0-i
        std::uniform_int_distribution<> dis(0, i);
        int j = dis(gen);

        //Exchange the positon randomly
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

/***************************************************************************
 Function Name:isInside
 Function:Check if the coordinate is inside
 Input Parameters:const int x, const int y, const int rows, const int columns
 Return Value:True for yes,false for no
 Documentation：
****************************************************************************/
bool isInside(const int x, const int y, const int rows, const int columns) 
{
    return (x >= 0 && x < rows && y >= 0 && y < columns);
}


/***************************************************************************
 Function Name:Maze_display
 Function:To display the maze
 Input Parameters:const int rows, const int columns, char** maze
 Return Value:void
 Documentation：
****************************************************************************/
void Maze_display(const int rows, const int columns, char** maze)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

/***************************************************************************
 Function Name:Maze_generate
 Function:To generate a random maze from an original maze
 Input Parameters:int x, int y, const int rows, const int columns,char **maze
 Return Value:void
 Documentation：
****************************************************************************/
void Maze_generate(int x, int y, const int rows, const int columns,char **maze)
{
    //If we reached the terminal spot ,stop generating a new path.Because we only want one path that can lead to the end of maze
    if (x == rows - 2 && y == columns - 2)
        return;
   
    int directions[4] = {UP, DOWN, LEFT, RIGHT};  //Create a vector to hold four directions
    shuffleArray(directions, 4); //Disorder four elements in the array

    //Handle different directions for each iteration.
    for (auto dir : directions) {
        int newX = x;
        int newY = y;
        switch (dir) {
            case UP:
                newX = x - 2;
                break;
            case DOWN:
                newX = x + 2;
                break;
            case LEFT:
                newY = y - 2;
                break;
            case RIGHT:
                newY = y + 2;
                break;
        }

        //Only if a spot is undiscovered before,can it be connected to the current spot
        if (isInside(newX, newY, rows, columns) && maze[newX][newY] == 'Y') {
            maze[(x + newX) / 2][(y + newY) / 2] = ' ';//Clear the new spot
            maze[newX][newY] = ' ';//Connect the spot with the current spot
            Maze_generate(newX, newY, rows, columns, maze);//Entering into the new spot so we can connect more spot
        }
    }

}

/***************************************************************************
 Function Name:Maze_generate
 Function:To generate a random maze
 Input Parameters:const int rows, const int columns
 Return Value:char **
 Documentation：
****************************************************************************/
char** Maze_init(const int rows, const int columns)
{
   //Allocate space for the maze
    char** maze = new(std::nothrow) char* [rows];
    if (maze == NULL) {
        cerr << "内存申请失败" << endl;
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        maze[i] = new(std::nothrow) char[columns];
        if (maze[i] == NULL) {
            cerr << "内存申请失败" << endl;
            return NULL;
        }
    }


    //Generate the original maze like this
    //###############
    //#Y#Y#Y#Y#Y#Y#Y#
    //###############
    //#Y#Y#Y#Y#Y#Y#Y#
    //###############
    //#Y#Y#Y#Y#Y#Y#Y#
    //###############
    //#Y#Y#Y#Y#Y#Y#Y#
    //###############
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (!(i % 2))
                maze[i][j] = '#';
            else
                if (j % 2)
                    maze[i][j] = 'Y';
                else
                    maze[i][j] = '#';
        }
    }
 

    maze[start_x][start_y] = '+';//Marks the start
    Maze_generate(start_x, start_y, rows, columns, maze);//Generate
    maze[rows - 2][columns - 2] = 'X';//Marks the end

    return maze;
    
}

/***************************************************************************
 Function Name:Maze_delete
 Function:To delete the maze
 Input Parameters:const int rows, char **maze
 Return Value:void
 Documentation：
****************************************************************************/
void Maze_delete(const int rows, char **maze)
{   
    //Release memory
    for (int i = 0; i < rows; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

/***************************************************************************
 Function Name:input
 Function:To input the data
 Input Parameters:void
 Return Value:input value
 Documentation：
****************************************************************************/
template<typename T>
T input()
{
    T num;
    while (true) {
        cin >> num;
        if (std::cin.fail() || num < 10 || num >100 || !(num % 2)) {
            std::cerr << "输入有误，请重新输入" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            return num;
    }
}

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
 Function Name:solution
 Function:To solve the maze by checking every path
 Input Parameters:int x, int y,const int rows, const int columns, char** maze,bool flag
 Return Value:whether the spot we are checking is a right way
 Documentation：When we are checking a new spot ,we defaultly regard it as a
 'wrong' way(Because only we reached the real terminal can we go back to the
 spot we passed and tell that is the right spot),so the flag is false and we 
 make the spot 0 defaultly.
****************************************************************************/
bool solution(int x, int y,const int rows, const int columns, char** maze,bool flag)
{
    
    //Reach the terminal and return true
    if (x == rows - 2 && y == columns - 2) {
        return true;
    }

    //Before checking the next spot ,we regard the current spot is the wrong way
    maze[x][y] = '0';

    int directions[4] = { UP, DOWN, LEFT, RIGHT };  //Create a vector to hold four directions

    //Handle different directions for each iteration.
    for (auto dir : directions) {

        int newX = x;
        int newY = y;
        switch (dir) {
            case UP:
                newX--;
                break;
            case DOWN:
                newX++;
                break;
            case LEFT:
                newY--;
                break;
            case RIGHT:
                newY++;
                break;
        }
        if (maze[newX][newY] == ' '|| maze[newX][newY] == 'X') {
            //This flag can be passed to a new solution so we cannot explore a new place after flaging
            flag = solution(newX, newY, rows, columns, maze, flag);
        }
        else
            continue;
        //Why this continue makes a difference before we add'flag = false;'.
        //Because if we passed the flag as True ,its okay when we reached a dead end
        //And the dead end spot will not run the codes below(maze[x][y] = '.';)
        //So after the loop is over ,the dead end spot returns false
        //The former spot that connects to the dead end spot which should be '.' as we mistakenly passed the True flag
        //will change its incorrect flag due to the 'flag = solution(newX, newY, rows, columns, maze, flag);'is run before
        //the if (flag == true) ,so we changed the wrong flag and double mistakes make it right, it is really dangerous >_<
        if (flag == true) {
            //Change the current spot if a adjoined spot is the 
            maze[x][y] = '.';
            //!!Necessary!!If the flag is not changed to false,the TRUE could be passed to next solution,and thats not we want
            flag = false;
        }
    }

   
    if (maze[x][y] == '.')
        return true; //If the current spot is '.',then tell the former spot that it is on the right path
    else
        return false; //Otherwise it is on the wrong path


}
/***************************************************************************
 Function Name:solution_display
 Function:To display the right path
 Input Parameters:int x,int y,const int rows, const int columns, char** maze
 Return Value:void
 Documentation：
****************************************************************************/
void solution_display(int x,int y,const int rows, const int columns, char** maze)
{
    //Display the current spot
    cout << '<' << x << ',' << y << '>';
    if (maze[x][y] == 'X') 
        return;
    else
        cout << "--->";
    
    //Mark the spot as read ,we only read it once
    maze[x][y] = '*';
    int directions[4] = { UP, DOWN, LEFT, RIGHT };  //Create a vector to hold four directions
    shuffleArray(directions,4); //Disorder four elements in the array

    //Handle different directions for each iteration.
    for (auto dir : directions) {

        int newX = x;
        int newY = y;
        switch (dir) {
            case UP:
                newX--;
                break;
            case DOWN:
                newX++;
                break;
            case LEFT:
                newY--;
                break;
            case RIGHT:
                newY++;
                break;
        }
        //Find the next right spot and display it
        if (maze[newX][newY] == '.'|| maze[newX][newY] == 'X') {
            solution_display(newX, newY, rows, columns, maze);
            return;
        }
        else
            continue;
          
    }

}

int main()
{
    int rows, columns;

    //Display the prompt and let the client input
    cout << "请输入矩阵的行数(10到100之间的奇数）" << endl;
    rows = input<int>();
    std::cout << "请输入矩阵的列数(10到100之间的奇数）" << endl;
    columns = input<int>();

    //Initialize the maze and display it on the screen
    char** maze = Maze_init(rows, columns);
    if (maze == NULL)
        return 0;
    cout << "生成迷宫：" << endl;
    Maze_display(rows, columns, maze);

    //Wait for the enter
    cout << "按回车输出结果" << endl;
    pause();

    //Solve the maze
    solution(start_x, start_y, rows, columns, maze, false);

    //Clear the screen and display the new maze
    system("cls");
    cout << "最佳路径：" << endl;
    Maze_display(rows, columns, maze);

    //Display the solution path
    cout << "最佳路径坐标：" << endl;
    solution_display(start_x, start_y, rows, columns, maze);

    //Delete the maze
    Maze_delete(rows, maze);

    return 0;

}