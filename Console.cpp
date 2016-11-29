// Validation Console.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <math.h>

int myrandom (int i) { return std::rand()%i;} //Random seed for shuff()

std::vector<int> shuff(int n){
	//Function generates a randomly ordered index vector of length n
	//Method adapted from: http://www.cplusplus.com/reference/algorithm/random_shuffle/
	// Indices = (0, n], or (0,n-1) inclusive

	//Generate randomizer seed
	std::srand ( unsigned ( std::time(0) ) );
	
	//Declare data vectors
	std::vector<int> shuff_vec;
	

	for(int m = 0; m < n; ++m) shuff_vec.push_back(m); // {0, 1, 2, ..., 45}

	std::random_shuffle( shuff_vec.begin(), shuff_vec.end(), myrandom);
	
	return shuff_vec;
}

// Yes, calcx and calcy are lazy. I know I should probably be using a tuple.
// This is a good example of coding for laboratory usage and not sound development
// tl;dr: Do as I say. Not as I do.

//Method from http://stackoverflow.com/questions/19143657/linear-indexing-in-symmetric-matrices
int calcx(int indx, int n){
	//Calculates the X value of a linear index projected onto an upper triangular matrix
	int x_calc = floor( ( 2*n+1 - sqrt( (2*n+1)*(2*n+1)- 8*indx) ) /2);

	return x_calc;
}

int calcy(int indx, int n,int x){
	//Calculates the Y value of a linear index projected onto an upper triangular matrix
	int y_calc = indx - n * x + x *(x-1)/2;

	return y_calc;
}

void present(int sig, int mthd){
	//Presents Signal # from the correct method (Syncopated or Melodic)
	//  -> This should likely be adapted as a header
}

int compare(int x, int y,int mthd){
	//Function returns -1 if x > y, 0 if x == y, 1 if x < y.
	// Returns -2 if in error.

	char c; //User character response
	int m;  //Function return value
	int n=1; //While loop control
	//While loop to keep presenting signals until an option is checked	
	while(n==1){
		//present signal x
		std::cout << "Signal 1" << std::endl;
		present(x,mthd);
		//present signal 2
		std::cout << "Signal 2" << std::endl;
		present(y,mthd);
		//Present option menu
		std::cout << "\nPlease select a response:" << std::endl;
		std::cout << "\tA.) Signal 1 > Signal 2" << std::endl;
		std::cout << "\tB.) Signal 1 = Signal 2" << std::endl;
		std::cout << "\tC.) Signal 1 < Signal 3" << std::endl;

		std::cout << "\nSelect any other option to repeat" << std::endl;
		//Get user response:
		std::cin >> c;
		
		switch(toupper(c)){
			case 'A':
				m = -1;
				n = 0;
				break;
			case 'B':
				m = 0;
				n = 0;
				break;
			case 'C':
				m = 1;
				n = 0;
				break;
			default:
				std::cout << "\nRepeating" << std::endl << std::endl;
				break;
		}
	}
	
	return m;
}

int main()
{
	
	std::vector<int> indx_vec; //Randomized vector of index values
	std::vector<int> sync_vec; //data vector for syncopated comparisons
	std::vector<int> mel_vec;  //data vector for melodic comparisons
	int meth = 1; //Integer marker to set presentation order for signal methods
		// 1 = Syncopated
		// 2 = Melodic
	int x, y; //Define integers for coordinates
	int n = 45; //number of comparisons

	//Get a shuffled index vector
	indx_vec = shuff(n); //n == (m)(m-1)/2: the number of unique handshakes
	// In this case 45 = 10(9)/2, or 10 categories for comparison


	// Go through each element in indx_vec
	for(unsigned int a=0; a < sizeof(indx_vec); a++){
		x = calcx(indx_vec[a],n);   //Project randomized index onto x coordinate
		y = calcy(indx_vec[a],n,x); //Project randomized index onto y coordinate
		
		if( meth == 1) sync_vec[x,y] = compare(x,y,meth); //If meth == 1, store in the sync vector
		else mel_vec[x,y] = compare(x,y,meth);

	}
	

	return 0;
}

