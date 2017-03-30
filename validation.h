//Header for Validation study

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> //for random_shuffle
#include <ctime> // For randomizer seed
//#include <cstdlib>
#include <math.h> //for floor()
#include <string> //for std::string
#include <windows.h>
#include "tactor_cHeader.h"
#include <iostream>

enum notes{ //Set the Frequencies for Tactor Tuning, dHz
	//http://www.phy.mtu.edu/~suits/notefreqs.html
	LE = 1648,
	LEb= 1556,
	LD = 1468,
	LC = 1308,
	LB = 1235,
	LA = 1100,
	F  = 1746,
	Fs = 1850,
	Gb = Fs,
	G  = 1960,
	Gs = 2077,
	Ab = Gs,
	A  = 2200,
	As = 2331,
	Bb = As,
	B  = 2469,
	C  = 2616,
	Cs = 2772,
	Db = Cs,
	D  = 2937,
	Ds = 3111,
	Eb = Ds,
	E  = 3296
};


int calcx(int indx, int n);       //Returns x value of an upper triangular index projection
int calcy(int indx, int n,int x); //Returns y value of an upper triangular index projection
int present(int mthd, int sig);  //Presents the signal for given method
int compare(int x, int y, int mthd); //Compares signal x & y
void treatment(int meth, std::ofstream &file); //Carries out treatments 0, 1, & 2
void output(int stor_mat[9][9], std::ofstream &outfile); //Stores results in .csv passed as a stream
void play(int note, int length); //Plays a note (e.g. Cb), in the correct length 
	//(1 == whole, 2 == half, 4== quarter, 45 == dotted quarter, etc.) 