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

void Generator_Coda(string const* InputChain, char const* filename, int n) {
	ofstream Out;
    Out.open(filename);
    bool check = 0;
	for(int i = 0; i < n; i ++) {
		if(InputChain[i] == "+") {
			Out << "mov ax, " << InputChain[i-2] << endl << "mov dx, " << InputChain[i+2] << endl << "add ax, dx" << endl;
		}
		if(InputChain[i] == "-") {
			Out << "mov ax, " << InputChain[i-2] << endl << "mov dx, " << InputChain[i+2] << endl << "sub ax, dx" << endl;
		}
		if(InputChain[i] == "*") {
			Out << "mov ax, " << InputChain[i-2] << endl << "mov dx, " << InputChain[i+2] << endl << "mul ax, dx" << endl;
		}
		if(InputChain[i] == "/") {
			Out << "mov ax, " << InputChain[i-2] << endl << "mov dx, " << InputChain[i+2] << endl << "div ax, dx" << endl;
		}
		if(InputChain[i] == ":=") {
			Out << "mov " << InputChain[i-2] << ", " << InputChain[i-1] << endl;
			i += 2;
		}
		if(InputChain[i] == "<" || InputChain[i] == ">" || InputChain[i] == "=") {
			Out << "mov eax, " << InputChain[i-2] << endl << "cmp eax, " << InputChain[i+2] << endl << "jmp L" << endl;
		}
		if(InputChain[i] == "if") {
			check = 1;
			Out << "jae L" << endl << "jne ElsePart" << endl << "jmp ebx" << endl << "jmp EndOfIf" << endl;
		}
		if(InputChain[i] == "then") {
			Out << "jae ebx" << endl;
		}
		if(InputChain[i] == "else") {
			Out << "ElsePart:" << endl;
		}
	}
	if(check == 1) {
		Out << "EndOfIf" << endl;
	}
	Out.close();
	cout << "√отово!\n" << endl;
}

void Generator_Triad(char const* filename) {
	ifstream LexTable;
    LexTable.open("Lexem Table.txt");
    string buf, buf1;
    bool check = 0, check1 = 0, check2 = 0;
    int n = 1,t = 0,max_count=0;
    string InputChain[200] = {};
    string OutputChain[200] = {};
	while(!LexTable.eof()) {
    	LexTable >> InputChain[n];
    	n ++;
	}
	for(int i = 0, k = 49; i < n; i ++) {
		if(check == 1 && t > 0) {
			OutputChain[i] = buf;
			OutputChain[i+1] = buf1;
			check = 0;
			k = 49;
			max_count = 0;	
		}
			if(InputChain[i] == "”словие") {
			OutputChain[i] = "if";
			OutputChain[i+1] = InputChain[i+1];
			OutputChain[i+3] = InputChain[i+3];
			OutputChain[i+5] = InputChain[i+5];		
		}
		if(InputChain[i] == "ƒействие1") {
			OutputChain[i] = "then";
		}
		if(InputChain[i] == "ƒействие2") {
			OutputChain[i] = "else";
		}
		max_count = i;
		if(InputChain[i] == "«накќперации" && InputChain[i+4] == "«накќперации") {
				int count = 1;
				while(InputChain[i+count*4] == "«накќперации") {
					count ++;
				}
				max_count = i+count*4-1;
				count --;
				while(count > -1) {
					if(k>49) { OutputChain[i+count*4] = InputChain[i+count*4-1]; OutputChain[i+count*4-3] = InputChain[i+count*4-3]; }
					else { OutputChain[i+count*4-1] = InputChain[i+count*4-1]; OutputChain[i+count*4-3] = InputChain[i+count*4-3]; OutputChain[i+count*4+1] = InputChain[i+count*4+1]; }	
					count --;
				}
		} 
		i = max_count;
		if(InputChain[i] == "«накѕрисваивани€") {
			buf = InputChain[i-1];
			buf1 = InputChain[i-3];
			check = 1;
		} 
		if(InputChain[i] == "«накќперации") {
			if(k > 49) { OutputChain[i-1] = InputChain[i-1]; OutputChain[i+1] = InputChain[i+1]; }
			else { OutputChain[i-1] = InputChain[i-1]; OutputChain[i-3] = InputChain[i-3]; OutputChain[i+1] = InputChain[i+1]; }
			t = k;
			k ++;
		}
		if(InputChain[i] == "«накѕрисваивани€" && InputChain[i+4] == "–азделитель¬ыражений") {
			OutputChain[i-1] = InputChain[i-1]; OutputChain[i-3] =  InputChain[i-3]; OutputChain[i-2] = InputChain[i+1];
		}	
	}
	LexTable.close();
	Generator_Coda(OutputChain, filename, n);
}
