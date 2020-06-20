#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <string.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include "LexemAnalyz.h"
#include "GeneratorID.h"
#include "SyntaxAnalyz.h"
#include "GeneratorCoda.h"
#include "Manual.h"
using namespace std;

int main(int argc, char const *argv[]) {
	setlocale(LC_ALL, "rus");
	string man = "man";
	if(argv[1] == man) {
    		OutputManual();
    		return 0;
	}
	if (argc > 1)
    {
        Lexem_Analyz(argv[1]); //������ ������� ������ ������ � ����� �� ��� ����� ("�������"-����������� ������� �����) ��������� �����
    // � �������� ��������� ���������� �� ������ �������� ��������� ����������� � �������������� �������� � ����� ��������� ������
        //�����������, ���� ��������, �������� �������� ��� ����������
        // ��������� ������� ������ � ������� ������������� ��� 42 
        Generator_ID(); //��������� � ���� ������� ������ � ������� ������������� ��� 42 
        Syntax_Analyz();//
        Generator_Triad(argv[2]);
    }
    else
    {
        cout << "��� ����������" << endl;
    }
    return 0;
}
