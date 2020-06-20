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

int Hash(string c) {
	int h = 0;
	for(int i = 0 ; i < c.length(); i ++) {
		h += int(c[i]) + rand() % 400;
	} 
	return h % 400;
} 

int ReHash(int mas) {
	mas += rand() % 400 ;
	return mas;
}
