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
        Lexem_Analyz(argv[1]); //сканер который читает литеры и стрит из них слова ("лексемы"-структурная еденица языка) исходного языка
    // в основном выполняет исключения из текста исходной программы коментарьев и незначительных пробелов а также выделение лексем
        //индификатор, знак операции, числовых констант итд определяет
        // результат таблица лексем и таблица индифекаторов стр 42 
        Generator_ID(); //записывет в файл таблицы лексем и таблица индифекаторов стр 42 
        Syntax_Analyz();//
        Generator_Triad(argv[2]);
    }
    else
    {
        cout << "Нет аргументов" << endl;
    }
    return 0;
}
