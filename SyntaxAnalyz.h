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
using namespace std;

char RuleMatrix[18][18] = {
//   +    -    /    *    (    )    a    c   :=    ;    #   do  while  <    > 	=	 {   }
    '>', '>', '>', '>', ' ', ' ', '<', '<', ' ', '>', ' ', '=', '=', ' ', ' ', ' ', '=', '>', // + 
    '>', '>', '>', '>', ' ', ' ', '<', '<', ' ', '>', ' ', '=', '=', ' ', ' ', ' ', '=', '>', // - 
    '>', '>', '>', '>', ' ', ' ', '<', '<', ' ', '>', ' ', '=', '=', ' ', ' ', ' ', '=', '>', // / 
    '>', '>', '>', '>', ' ', ' ', '<', '<', ' ', '>', ' ', '=', '=', ' ', ' ', ' ', '=', '>', // * 
    '<', '<', '<', '<', '=', '=', '<', '<', ' ', ' ', ' ', ' ', '=', '=', '=', '=', '=', '=', // ( 
    '>', '>', '>', '>', '=', '=', '>', '>', ' ', '<', '>', ' ', '=', '=', '=', '=', '=', '=', // ) 
    '>', '>', '>', '>', '=', '=', ' ', ' ', '=', '>', ' ', '=', '=', '>', '>', '>', '=', '=', // a  
    '>', '>', '>', '>', ' ', '>', ' ', ' ', ' ', '>', ' ', ' ', ' ', '>', '>', '>', ' ', '>', // c 
    '<', '<', '<', '<', ' ', ' ', '<', '<', ' ', '>', ' ', '=', '=', ' ', ' ', ' ', '=', '>', // :=
    ' ', ' ', ' ', ' ', ' ', ' ', '>', '>', ' ', '=', '>', '>', '=', ' ', ' ', ' ', '=', '=', // ; 
    '<', '<', '<', '<', ' ', ' ', '<', '<', ' ', '<', ' ', '<', ' ', ' ', ' ', ' ', ' ', ' ', // $ 
    ' ', ' ', ' ', ' ', ' ', ' ', '=', '=', ' ', ' ', ' ', ' ', '=', ' ', ' ', ' ', '=', '=', // do
    ' ', ' ', ' ', ' ', '<', '<', '>', '>', '=', ' ', '>', ' ', ' ', '=', '=', '=', '=', '=', // while 
    ' ', ' ', ' ', ' ', '=', '=', '<', '<', '=', ' ', ' ', '=', '=', ' ', ' ', ' ', ' ', ' ', // < 
    ' ', ' ', ' ', ' ', '=', '=', '<', '<', '=', ' ', ' ', '=', '=', ' ', ' ', ' ', ' ', ' ', // > 
    ' ', ' ', ' ', ' ', '=', '=', '<', '<', '=', ' ', ' ', '=', '=', ' ', ' ', ' ', ' ', ' ', // =
	'=', '=', '=', '=', '=', '=', '<', '<', ' ', '<', ' ', '=', '=', '=', '=', '=', '=', '=', // {
	'=', '=', '=', '=', '=', '=', ' ', ' ', '=', ' ', ' ', '=', '=', '=', '=', '=', '=', '='  // }
}; 

int Get_Relations(string left, string right) {
//	cout << "left: " << left << " right: " << right << endl;
    int l = -1, r = -1;
    if (left == "+") l = 0;
    else if (left == "-") l = 1;
    else if (left == "/") l = 2;
    else if (left == "*") l = 3;
    else if (left == "(") l = 4;
    else if (left == ")") l = 5;
    else if (left == "a") l = 6;
    else if (left == "c") l = 7;
    else if (left == ":=") l = 8;
    else if (left == ";") l = 9;
    else if (left == "$") l = 10;
    else if (left == "do") l = 11;
    else if (left == "while") l = 12;
    else if (left == "<") l = 13;
    else if (left == ">") l = 14;
    else if (left == "=") l = 15;
    else if (left == "{") l = 16;
    else if (left == "}") l = 17;

    if (right == "+") r = 0;
    else if (right == "-") r = 1; 
    else if (right == "*") r = 2;
    else if (right == "/") r = 3;
    else if (right == "(") r = 4;
    else if (right == ")") r = 5;
    else if (right == "a") r = 6;
    else if (right == "c") r = 7;
    else if (right == ":=") r = 8;
    else if (right == ";") r = 9;
    else if (right == "#") r = 10;
    else if (right == "do") r = 11;
    else if (right == "while") r = 12;
    else if (right == "<") r = 13;
    else if (right == ">") r = 14;
    else if (right == "=") r = 15;
    else if (right == "{") r = 16;
    else if (right == "}") r = 17;
    
    if (l == -1 || r == -1) {
        cout << "Left is " << left << " right is " << right << "\nERROR with l=" << l << " and r=" << r << endl;
        return '~';
    }
    return (int) RuleMatrix[l][r];
}

string Find_LT(const string Magazine[200], const int Up) {
    int res = Up;
    while (Magazine[res] == "E") {
        res--;
    }
    return Magazine[res];
}

int Get_Rule(string Y) {
    if (Y == "E;" || Y == "E;E;" || Y == "E;E;E;") return 1;
    else if (Y == "do{E}whileE" || Y == "Edo{E}whileE" || Y == "do{E;}whileE" || Y == "Edo{E;}whileE" || Y == "do{E;E;}whileE" || Y == "Edo{E;E;}whileE") return 2;
    else if (Y == "a:=E" || Y == "Ea:=E") return 3;
    else if (Y == "E+E" || Y == "EE+E") return 4;
    else if (Y == "E-E" || Y == "EE-E") return 5;
    else if (Y == "E/E" || Y == "EE/E") return 6;
    else if (Y == "E*E" || Y == "EE*E") return 7;
    else if (Y == "(E<E)") return 9;
    else if (Y == "(E>E)") return 10;
    else if (Y == "(E=E)") return 11;
    else if (Y == "a" || Y == "Ea") return 12;
    else if (Y == "c" || Y == "Ec") return 13;
    else return -1;
}

void Syntax_Analyz() {
	ifstream LexTable;
	ofstream File;
	LexTable.open("Lexem Table.txt");
    string buf1, buf2;
    string InputChain[200] = {};
    File.open("Syntax.txt");
    int i = 0;
    while (buf2 != "КонецФайла") {
        LexTable >> buf1;
        LexTable >> buf2;
        if (buf2 == "Переменная") {
            InputChain[i] = "a";
        }
        if (buf2 == "ЗнакПрисваивания") {
            InputChain[i] = ":=";
        }
        if (buf2 == "ЗнакОперации") {
            InputChain[i] = buf1;
        }
        if (buf2 == "Число") {
            InputChain[i] = "c";
        }
        if (buf2 == "ОткрывающаяСкобка") {
            InputChain[i] = "(";
        }
        if (buf2 == "ЗакрывающаяСкобка") {
            InputChain[i] = ")";
        }
        if (buf2 == "РазделительВыражений") {
            InputChain[i] = buf1;
        }
        if (buf2 == "ОшибочнаяЛексема"){
		}
		if (buf2 == "КонецФайла"){
			i--;
		}
		if (buf2 == "Действие"){
			InputChain[i] = "do";
		}
		if (buf2 == "ЗнакБольше"){
			InputChain[i] = ">";
		}
		if (buf2 == "ЗнакМеньше"){
			InputChain[i] = "<";
		}
		if (buf2 == "ЗнакРавно"){
			InputChain[i] = "=";
		}
		if (buf2 == "Условие"){
			InputChain[i] = "while";
		}
		if (buf2 == "ОткрывающаяФигурнаяСкобка"){
			InputChain[i] = "{";
		}
		if (buf2 == "ЗакрывающаяФигурнаяСкобка"){
			InputChain[i] = "}";
		}
        i++;
    }
    InputChain[i] = "#"; 

    int j = 0;
    while (j <= i) {
        File << InputChain[j];
        j++;
    }
    File << "\n\n";

    bool error_check = false, succes_check = false;
    int ReadingHead = 0, RuleLine[100], RuleCount = 0, Up = 0, counter = 0, relations = 0;
    string Magazine[200], LastTerminal, gamma;

    Magazine[0] = '$';

    while (error_check == false && succes_check == false) {
        File << ++ counter;
        File << ") \"";
        for (int i = 0; i < Up + 1; i++) {
		File << Magazine[i];; 
		} 
        File << "\" ";
        LastTerminal = Find_LT(Magazine, Up);
        if (LastTerminal == "$" && InputChain[ReadingHead] == "#") succes_check = true;
        else {
            relations = Get_Relations(LastTerminal, InputChain[ReadingHead]);
            switch (relations) {
                case '<':
                case '=':
                    File << "Сдвиг\n";
                    Up ++;
                    Magazine[Up] = InputChain[ReadingHead];
                    ReadingHead ++;
                    break;
                case '>': 
                {
                    File << "Свертка";
                    int Num_LT = Up;
//                    cout << "LastTerminal: " << LastTerminal << endl;
//                    cout << "Num_LT: " << Num_LT << endl;
                    while (Magazine[Num_LT] != LastTerminal) {
//                    	cout << "Magazine[" << Num_LT << "] = " << Magazine[Num_LT] << endl;
                    	Num_LT--; 
                    } 

                    string Pre_LT; 
                    int rel_PreLT_LT, base_count = 0, base = Num_LT;

                    bool repeat = true;
                    while (repeat == true) {
                        base--;
                        Pre_LT = Find_LT(Magazine, base); 
                        while (Magazine[base] != Pre_LT) base--; 

                        rel_PreLT_LT = Get_Relations(Pre_LT, LastTerminal);
                        if (rel_PreLT_LT == '=') {
                            base_count++;
                        } else {
                            repeat = false;
                            base++;
                        }
                    }
                    if (base_count == 0) {
                        base = Num_LT;
                        while (Magazine[base - 1] == "E") base--;
                    } else while (Magazine[base - 1] == "E") base--;

                    while (Up > base) { 
                        gamma.insert(0, Magazine[Up]); 
                        Magazine[Up] = "";
                        Up--;
                    }
                    gamma.insert(0, Magazine[Up]);

                    RuleLine[RuleCount] = Get_Rule(gamma);
                    File << " \"" << gamma << "\" по правилу " << RuleLine[RuleCount] << endl;
                    if (RuleLine[RuleCount] != -1) { 
                        RuleCount++;
                        Magazine[Up] = "E";
                    } else error_check = true;
                    gamma = "";
                    break;
                }
                case ' ':
                    cout << "Найден пробел в правилах \n";
                    error_check = true;
                    break;
                default:
                    cout << "\n Ошибка в правилах \n" << endl;
                    error_check = true;
                    break;
            }

        }
        if (succes_check == true) {
            File << "Разбор успешно закончен \n Цепочка правил: ";
            for(int i=0; i < RuleCount; i++) {
            	File << RuleLine[i] << " ";
			} 
            File << endl;
        }
    }
    cout << "Синтаксический анализ проведён!\n";
    Lex_Table.close();
    File.close();
}
