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
#include "Hash.h"
using namespace std;

void Generator_ID() {
    ofstream File;
	ifstream LexTable;
    LexTable.open("Lexem Table.txt");
    int n = 0,t[200];
    string InputChain[200] = {};
    File.open("ID.txt");
    int i = 0;
	while(!LexTable.eof()) {
    	LexTable >> InputChain[i];
    	i ++;
    	n ++;
	}
	for(int i = 0, j = 0 ; i < n ; i ++, j ++) {
		if(InputChain[i] == "Переменная") {
			t[i] = Hash(InputChain[i-1]);
			for(int k = 0 ; k < j ; k ++) {
				if(t[i] == t[k]) {
					t[i] = ReHash(t[i]);
				}
			}
			File << t[i] << " " << InputChain[i-1] << endl;
		}
	}
	cout << "Генерация таблицы идентификаторов завершена!\n";
}
