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

ifstream code;       //чтение из файла
ofstream Lex_Table; //запись в файл

enum LA_states { //дл€ удобства
    Begin, 
    Error, 
    Const, 
    Variable,  // переменна€
    Assignment, // Ќазначение
	Condition,  //—осто€ние
	Condition1,
	Condition2,
	C1_1,
	C1_2,
	C2_1,
	C2_2,
	Move1,
	Move2
} LA_state = Begin;

void F_Var(char v[100]); 
void F_Char(char a); 
void F_Const_Char(char c[100], char a);
void F_Const(char c[100]); 
void F_Condition(char c[100], char a);
void F_Move(char c[100], char a);
void F_Assignment(char a); 
void F_Error(char* Er); 

void F_Var(char v[100]) {
	if(v[0] != ' ')
    Lex_Table << v << "  ѕеременна€\n";
}

void F_Assignment(char a) {
	Lex_Table << ":=  «накѕрисваивани€\n";
}

void F_Char(char a) {
    switch (a) {
        case ';':
            Lex_Table << a << "  –азделитель¬ыражений\n";
            break;
        case '+':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '-':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '*':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '/':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '(':
            Lex_Table << a << "  ќткрывающа€—кобка\n";
            break;
        case ')':
            Lex_Table << a << "  «акрывающа€—кобка\n";
            break;
        case '<':
        	Lex_Table << a << " «накћеньше\n";
        	break;
        case '>':
        	Lex_Table << a << " «накЅольше\n";
        	break;
        case '=':
            Lex_Table << a << "  «нак–авно\n";
            break;
    }
}

void F_Const(char c[100]) {
    Lex_Table << c << " „исло\n";
}

void F_Const_Char(char c[100], char a) {
    switch (a) {
        case ';':
            Lex_Table << a << "  –азделитель¬ыражений\n";
            break;
        case '+':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '-':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '*':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '/':
            Lex_Table << a << "  «накќперации\n";
            break;
        case '(':
            Lex_Table << a << "  ќткрывающа€—кобка\n";
            break;
        case ')':
            Lex_Table << a << "  «акрывающа€—кобка\n";
            break;
        case '=':
            Lex_Table << ":=  «накѕрисваивани€\n";
            break;
    }
}

void F_Condition(char c[100], char a) {
	switch (a) {
		case 'n':
			Lex_Table << c << " ƒействие1\n";
			break;
		case 'e':
			Lex_Table << c << " ƒействие2\n";
			break;
		default:
			Lex_Table << c << " ”словие\n";
			break;
	}
}

void F_Move(char c[100], char a) {
	switch(a) {
		case '<':
			Lex_Table << c << " —двиг¬лево\n";
			break;
		case '>':
			Lex_Table << c << " —двиг¬право\n";
			break;
	}
}

void F_Error(char* Er) {
    Lex_Table << '|' << Er << '|' << "  ќшибочна€Ћексема\n";
}

void StringPlusChar(char* str, char c) { 
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    str[i] = c;
    str[i + 1] = '\0';
}

void Lexem_Analyz(char const* filename) {
    code.open(filename);                 //открывает документ
    Lex_Table.open("Lexem Table.txt");  //выполн€ет чтение
    int c;
    char Var_buffer[100];  //  массив переменных
    char Const_buffer[100]; // массив констант
    Var_buffer[0] = '\0';
    Const_buffer[0] = '\0';
    char Er_buf[100]; // массив ошибок?
    while ((c = code.get()) != EOF) {
        switch (LA_state) {
            case Begin:
                if (c == ':') {
                    LA_state = Assignment;
                    break;
                }
                if (c == '0' || c == '1') {
                    StringPlusChar(Const_buffer, (char) c);
                    LA_state = Const;
                    break;
                }
                if(c == 'i') {
                	StringPlusChar(Var_buffer, (char)c);
                	LA_state = Condition;
                	break;
				}
				if(c == 't') {
					StringPlusChar(Var_buffer, (char)c);
                	LA_state = Condition1;
                	break;
				}
				if(c == 'e') {
					StringPlusChar(Var_buffer, (char)c);
                	LA_state = Condition2;
                	break;
				}
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '<') {
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    LA_state = Begin;
                    break;
                }
                StringPlusChar(Er_buf, c);
                LA_state = Error;
                break;
            case Move1:
            	if(c == '<') {
            		StringPlusChar(Var_buffer, (char) c);
            		F_Move(Var_buffer, (char)c);
            		Var_buffer[0] = '\0';
            		LA_state = Begin;
            		break;
				}
				else {
					Var_buffer[0] = '\0';
					F_Char('>');
					StringPlusChar(Var_buffer, (char) c);
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					LA_state = Begin;
					break;
				}
			case Move2:
            	if(c == '>') {
            		StringPlusChar(Var_buffer, (char) c);
            		F_Move(Var_buffer, (char)c);
            		Var_buffer[0] = '\0';
            		LA_state = Begin;
            		break;
				}
				else {
					Var_buffer[0] = '\0';
					F_Char('>');
					StringPlusChar(Var_buffer, (char) c);
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					LA_state = Begin;
					break;
				}	
            case Condition:
            	if(c == 'f') {
            		StringPlusChar(Var_buffer, (char)c);
            		F_Condition(Var_buffer, c);
            		Var_buffer[0] = '\0';
            		LA_state = Begin;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}
			case Condition1:
            	if(c == 'h') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = C1_1;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}
			case C1_1:
            	if(c == 'e') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = C1_2;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}
			case C1_2:
            	if(c == 'n') {
            		StringPlusChar(Var_buffer, (char)c);
            		F_Condition(Var_buffer, c);
            		Var_buffer[0] = '\0';
            		LA_state = Begin;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}		
			case Condition2:
            	if(c == 'l') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = C2_1;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}
			case C2_1:
            	if(c == 's') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = C2_2;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}
			case C2_2:
            	if(c == 'e') {
            		StringPlusChar(Var_buffer, (char)c);
            		F_Condition(Var_buffer, c);
            		Var_buffer[0] = '\0';
            		LA_state = Begin;
            		break;
				}
				else {
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';' || c == '=') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
				}	
            case Error:
                if (c == ' ' || c == '\n' || c == '\t') {
                    LA_state = Begin;
                    F_Error(Er_buf);
                    Er_buf[0] = '\0';
                    break;
                }
                if ((c == ';') || (c == '(') || (c == ')')) {
                    F_Char(c);
                    LA_state = Begin;
                    F_Error(Er_buf);
                    Er_buf[0] = '\0';
                    break;
                }
                StringPlusChar(Er_buf, c);
                LA_state = Error;
                break;
            case Const:
                if (c == '0' || c == '1') {
                    StringPlusChar(Const_buffer, c);
                    LA_state = Const;
                    break;
                }
                if ((c == ' ') || (c == '\t') || (c == '\n')) {
                    F_Const(Const_buffer);
                    Const_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                    F_Const(Const_buffer);
                    F_Char(c);
                    Const_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if (c == ';' || c == '(' || c == ')') {
                    Const_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                else {
                	LA_state = Error;
                	break;
				}
                Const_buffer[0] = '\0';
                StringPlusChar(Er_buf, c);
                LA_state = Error;
                break;
            case Variable:
                if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '<') {
                	F_Var(Var_buffer);
					Var_buffer[0] = '\0';
                	StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move1;
                    break;
				}
				if(c == '>') {
					F_Var(Var_buffer);
					Var_buffer[0] = '\0';
					StringPlusChar(Var_buffer, (char) c);
                    LA_state = Move2;
                    break;
				}
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if (c == ':') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Assignment;
                    break;
                }
                strcpy(Er_buf, Var_buffer);
                StringPlusChar(Er_buf, c);
                Var_buffer[0] = '\0';
                LA_state = Error;
                break;
            case Assignment:
                if (c == '=') {
                    F_Assignment(c);
                    LA_state = Begin;
                    break;
                }
                StringPlusChar(Er_buf, '=');
                StringPlusChar(Er_buf, c);
                LA_state = Error;
        }
    }
    code.close();
    Lex_Table.close();
    cout << "\nЋексический анализ проведЄн!\n";
}
