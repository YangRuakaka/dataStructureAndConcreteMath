/****************************************************************
 * Project Name:  Լɪ��������Ϸ
 * File Name:     Լɪ��������Ϸ.cpp
 * File Function: Problem solution
 * Update Date:   2023/10/19
 ****************************************************************/

 /****************************************************************
  * Problem Description
  ****************************************************************/

//����һ���ı��ļ����ļ������û��ü������룬
//����һ�������ո�Ĺؼ��֣�ͳ������ؼ������ı��еĳ��ִ�����

 /****************************************************************
  * Problem Solution
  ****************************************************************/
#include <iostream>
#include <fstream>
#include <cstring>

#define MAX_SIZE 10000

/***************************************************************************
Function Name:computeLPSArray
Function:To compute Longest Proper Prefix which is also Suffix
Input Parameters:pattern string lenth of the string the match value
Return Value:void
Documentation��
****************************************************************************/
void computeLPSArray(const char* pat, int M, int* lps) 
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) 
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/***************************************************************************
Function Name:KMPSearch
Function:Using the KMP to search the string
Input Parameters:pattern string the txt file we input
Return Value:the times of appearance
Documentation��
****************************************************************************/
int KMPSearch(const char* pat, const char* txt) 
{
    int M = strlen(pat);
    int N = strlen(txt);

    int lps[MAX_SIZE];
    computeLPSArray(pat, M, lps);

    int count = 0;
    int i = 0;
    int j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            count++;
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0) 
                j = lps[j - 1];
            else 
                i = i + 1;
        }
    }

    return count;
}

/***************************************************************************
Function Name:countKeywordOccurrences
Function:To open a file and calculate the time of appearance
Input Parameters:file name and the keyword
Return Value:the time of the appearance
Documentation��
****************************************************************************/
int countKeywordOccurrences(const char* filename, const char* keyword)
{
    std::ifstream file(filename);
    char line[MAX_SIZE];
    int count = 0;

    if (file.is_open()) {
        while (file.getline(line, MAX_SIZE)) 
            count += KMPSearch(keyword, line);

        file.close();
    }
    else 
        std::cout << "Unable to open file" << std::endl;
    

    return count;
}

int main() {

    char filename[MAX_SIZE];
    char keyword[MAX_SIZE];
    std::cout << "�������ļ�����";
    std::cin.getline(filename, MAX_SIZE);
    std::cout << "�����벻���ո�Ĺؼ��֣�";
    std::cin.getline(keyword, MAX_SIZE);

    int occurrences = countKeywordOccurrences(filename, keyword);
    std::cout << "�ؼ��� '" << keyword << "' ���ļ��г����� " << occurrences << " �Ρ�" << std::endl;

    return 0;
}
