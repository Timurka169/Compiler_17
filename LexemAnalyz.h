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

enum LA_states { //для удобства
    Begin, // Начало
    Error,  // Конец
    Const,  // Константа
    Variable,  // переменная
    Assignment, // Присваивание
    
    // С данного места идут enum-ы по варианту
    
    Do, // Ключевое слово do
    
    W1, // Ключевое слово while
    W2, // Ключевое слово while
    W3, // Ключевое слово while
    W4 // Ключевое слово while

} LA_state = Begin;

void F_Var(char v[100]); 
void F_Char(char a); 
void F_Const(char c[100]);
void F_Loop_do();
void F_Loop_while(); 
void F_Assignment(char a); 
void F_Error(char* Er); 

void F_Var(char v[100]) {
	if(v[0] != ' ')
    Lex_Table << v << "  Переменная\n";
}

void F_Assignment(char a) {
	Lex_Table << ":=  ЗнакПрисваивания\n";
}

void F_Char(char a) {
    switch (a) {
        case ';':
            Lex_Table << a << "  РазделительВыражений\n";
            break;
        case '+':
            Lex_Table << a << "  ЗнакОперации\n";
            break;
        case '-':
            Lex_Table << a << "  ЗнакОперации\n";
            break;
        case '*':
            Lex_Table << a << "  ЗнакОперации\n";
            break;
        case '/':
            Lex_Table << a << "  ЗнакОперации\n";
            break;
        case '(':
            Lex_Table << a << "  ОткрывающаяСкобка\n";
            break;
        case ')':
            Lex_Table << a << "  ЗакрывающаяСкобка\n";
            break;
        case '<':
        	Lex_Table << a << " ЗнакМеньше\n";
        	break;
        case '>':
        	Lex_Table << a << " ЗнакБольше\n";
        	break;
        case '=':
            Lex_Table << a << "  ЗнакРавно\n";
            break;
        case '{':
        	Lex_Table << a << " ОткрывающаяФигурнаяСкобка\n";
        	break;
        case '}':
        	Lex_Table << a << " ЗакрывающаяФигурнаяСкобка\n";
        	break;
    }
}

void F_Const(char c[100]) {
    Lex_Table << c << " Число\n";
}

void F_Loop_do() {
	Lex_Table << "do " << "Действие\n"; 
}

void F_Loop_while() {
	Lex_Table << "while " << "Условие\n";
}

void F_Error(char* Er) {
    Lex_Table << '|' << Er << '|' << "  ОшибочнаяЛексема\n";
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
    Lex_Table.open("Lexem Table.txt");  //выполняет чтение
    int c;
    char Var_buffer[100];  //  массив переменных
    char Const_buffer[100]; // массив констант
    Var_buffer[0] = '\0';
    Const_buffer[0] = '\0';
    char Er_buf[100]; // массив ошибок
    while ((c = code.get()) != EOF) {
        switch (LA_state) {
            case Begin:
                if (c == ':') {
                    LA_state = Assignment;
                    break;
                }
                if (c >= '0' && c <= '7') {
                    StringPlusChar(Const_buffer, (char) c);
                    LA_state = Const;
                    break;
                }
                if(c == 'd') {
                	StringPlusChar(Var_buffer, (char)c);
                	LA_state = Do;
                	break;
                }
                if(c == 'w') {
                	StringPlusChar(Var_buffer, (char)c);
                	LA_state = W1;
                	break;
                }
                if(c == '{' || c == '}') {
                	F_Char((char) c);
                	break;
                }
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '8' || c == '9' || c == '_') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '<') {
                	StringPlusChar(Var_buffer, (char) c);
                    F_Char((char)c);
                    break;
				}
				if(c == '>') {
					StringPlusChar(Var_buffer, (char) c);
                    F_Char((char)c);
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
            case Do:
            	if(c == 'o') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = Do;
            		break;
            	} else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '{' || c == ' ') {
                	F_Loop_do();
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                if (c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
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
				break;
            case W1:
            	if(c == 'h') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = W2;
            		break;
            	} else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
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
            	break;
            case W2:
            	if(c == 'i') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = W3;
            		break;
            	} else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
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
            	break;
            case W3:
            	if(c == 'l') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = W4;
            		break;
            	} else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
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
            	break;
            case W4:
            	if(c == 'e') {
            		StringPlusChar(Var_buffer, (char)c);
            		LA_state = W4;
            		break;
            	} else if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
                    StringPlusChar(Var_buffer, (char) c);
                    LA_state = Variable;
                    break;
                }
                if(c == '(' || c == ' ') {
                	F_Loop_while();
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                if (c == ' ' || c == '\t' || c == '\n') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    LA_state = Begin;
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
            	break;
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
                if (c >= '0' && c <= '7') {
                    StringPlusChar(Const_buffer, c);
                    LA_state = Const;
                    break;
                }
                if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '8' && c <= '9') {
                    StringPlusChar(Const_buffer, (char) c);
                    for(int i = 0; i <= 100; i ++) {
                    	Var_buffer[i] = Const_buffer[i];
                    }
                    Const_buffer[0] = '\0';
                    LA_state = Variable;
                    break;
                }
                if ((c == ' ') || (c == '\t') || (c == '\n')) {
                    F_Const(Const_buffer);
                    Const_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') {
                    F_Const(Const_buffer);
                    F_Char(c);
                    Const_buffer[0] = '\0';
                    LA_state = Begin;
                    break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	LA_state = Begin;
                	F_Char((char) c);
                	break;
                }
                
                if (c == ';' || c == '}') {
                	F_Const(Const_buffer);
                    Const_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                else {
                	Const_buffer[0] = '\0';
                	StringPlusChar(Er_buf, c);
                	LA_state = Error;
                	break;
				}
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
                if (c == '+' ||c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == ';') {
                    F_Var(Var_buffer);
                    Var_buffer[0] = '\0';
                    F_Char(c);
                    LA_state = Begin;
                    break;
                }
                if(c == '>' || c == '<' || c == '=') {
                	F_Var(Var_buffer);
                	Var_buffer[0] = '\0';
                	F_Char((char) c);
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
            	if( c == ' ') {
            		LA_state = Assignment;
            		break;
            	}
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
    Lex_Table << "@ КонецФайла";
    Lex_Table.close();
    cout << "\nЛексический анализ проведён!\n";
}
