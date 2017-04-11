#include "validation.h"

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

int main()
{
	int meth; //Integer marker to set presentation order for signal methods
		// 0 = Syncopated
		// 1 = Melodic
	
	std::string subject;
	
	//Console Introduction

	//Use this snip whenever accessing the tactors//
	if(InitTactorDLL() == -1)
	{
		std::cout << "ERROR DURING INIT\n";
		return -1;
	}
	
	std::cout << "Welcome to the Tactor Signal Validation Study" << std::endl << std::endl;
	std::cout << "What is the subject identifier?: ";
	std::getline(std::cin, subject);
	char m;
	int l=0;
	//while(l == 0){
	//	std::cout << "\nAre you using tactor set A.) 16 or B.) 17?: ";
	//	std::cin >> m;
	//	m = toupper(m);
	//	switch(m){
	//	case 'A':
	//		ConnectDirect("\\.\COM40", Serial); // Weird escape deals with squirrely Windows COM ports.
	//		l = 1;
	//		break;
	//	case 'B':
	//		ConnectDirect("COM9", Serial);
	//		l = 1;
	//		break;
	//	default:
	//		std::cout << std::endl << std::endl << "Please select either A or B." << std::endl;
	//		l = 0;
	//	}
	//	
	//}
	ConnectDirect("COM9", Serial); //Connect to EAI 17
	std::cout << "Tactors connected!" << std::endl;
	Sleep(1000);

	l = 0;
	while(l==0){
		ClearScreen();
		std::cout << std::endl << "Start with Treatment 1 (Syncopated) or Treatment 2 (Melodic)?: ";
		std::cin >> meth;
		meth = meth - 1;
		switch(meth){ //Error processing for input
		case 0:
		case 1:
			l = 1;
			break;
		default:
			l = 0;
			break;
		}
		
	}

	std::ofstream outfile;
	subject = subject + ".csv";
	outfile.open(subject);
	ClearScreen(); //clear the screen
	
	treatment(meth,outfile);

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Completed Treatment." << std::endl << std::endl;
	Sleep(1000);
	std::cout << "Hit any key when prepared to continue:";
	std::cin.get();
	std::cout << "Beginning Musical Test treatment" << std::endl << std::endl;
	Sleep(1000);
	ClearScreen();
	treatment(2,outfile); //Give musical treatment

	ClearScreen();
	std::cout << "Completed Treatment." << std::endl << std::endl;
	Sleep(1000);
	std::cout << "Hit any key when prepared to continue:";
	std::cin.get();

	if(meth==1){ 
		meth = 0;
	}
	else{
		if(meth==0) meth = 1;
	}
	ClearScreen();
	treatment(meth,outfile);
	ClearScreen();
	std::cout <<"Study completed!" << std::endl << std::endl;
	std::cout << "Thank you for your participation. Please be sure to sign the compensation form" << std::endl << std::endl;
	Sleep(1000);
	std::cout << "Hit any key to finish.";
	std::cin.get();
	outfile.close();
	return 0;

	return 0;
}

int calcx(int indx, int n){
	//Calculates the X value of a linear index projected onto an upper triangular matrix
	int x_calc = floor((2*n+1 - std::sqrt((double)(2*n+1)*(2*n+1)- 8*indx)) /2);

	return x_calc;
}

int calcy(int indx, int n,int x){
	//Calculates the Y value of a linear index projected onto an upper triangular matrix
	int y_calc = indx - n * x + x *(x-1)/2 + x;

	return y_calc;
}

int present(int mthd, int sig){
	//Presents Signal # from the correct method (Syncopated or Melodic)
	//  -> This should likely be adapted as a header
	
	//Returns 1 if signal exists, returns 0 if not.
	if(InitTactorDLL() == -1)
	{
		std::cout << "ERROR DURING INIT\n";
	}
	SetGain(0,0,4,0,false); //Set gain to max!

	switch (mthd){
		// mthd == 0 
		////////////////////////
		// Syncopated Signals //
		////////////////////////
	case 0:
		switch (sig){
		case 0:
			play(B,1);
			return 1;
			break;
		case 1: // 4 Quarter Notes
			play(B,4);
			play(B,4);
			play(B,4);
			play(B,4);
			return 1;
			break;
		case 2: // Sync 2
			play(B,16);
			play(B,16);
			play(B,8);
			//Rest 8 + 16
			Sleep(R8);
			Sleep(R16);
			play(B,4);
			play(B,8);
			play(B,85);
			return 1;
			break;
		case 3: // Sync 3
			//Eigth
			play(B,8);
			// Sixteenth
			play(B,16);
			// Eighth
			play(B,8);
			// Sixteenth
			play(B,16);
			// Eighth
			play(B,8);
			// Eighth
			play(B,8);
			//Sixteenth
			play(B,16);
			// Rest
			Sleep(R16);
			// Sixteenth
			play(B,16);
			// Eighth
			play(B,8);
			return 1;
			break;
		case 4:
			play(B,4);
			play(B,8);
			play(B,8);
			//rest 8;
			Sleep(300);
			play(B,8);
			play(B,4);
			return 1;
			break;
		case 5:
			play(B,4);
			//Triplet. May need editing
			play(B,8);
			play(B,8);
			play(B,8);
			play(B,4);
			play(B,4);

			return 1;
			break;
		case 6:
			play(B,2);
			play(B,8);
			play(B,4);
			play(B,8);
			return 1;
			break;
		case 7:
			play(B,16);
			//rest 16;
			Sleep(R16);
			play(B,4);
			//rest 8;
			Sleep(R8);
			play(B,16);
			//rest 16;
			Sleep(R16);
			play(B,45);
			return 1;
			break;
		case 8:
			play(B,4);
			play(B,8);
			play(B,4);
			play(B,8);
			play(B,4);
			return 1;
			break;
		case 9:
			play(B,32);
			play(B,16);
			play(B,8);
			play(B,4);
			play(B,16);
			play(B,8);
			play(B,45);
			return 1;
			break;
		case 10: //Shouldn't be used, but included here for usage if problems occur with other signals.
			play(B,16);
			play(B,16);
			play(B,8);
			//Rest 8 + 16
			Sleep(R8);
			Sleep(R16);
			play(B,4);
			play(B,8);
			play(B,85);
			return 1;
		default:
			return 0;
			std::cout << "\nNo such signal" << std::endl << std::endl;
		}
		break;
		// mthd == 1
		/////////////////////
		// Melodic Signals //
		/////////////////////
	case 1:
		switch (sig){
		case 0: // Whole Note
			play(B,1);
			return 1;
			break;
		case 1: //4 Alternating Quarter Notes
			play(F,4);
			play(C,4);
			play(F,4);
			play(C,4);
			return 1;
			break;
		case 2: 
			play(A,4);
			play(C,4);
			play(F,4);
			play(C,16);
			play(C,45);
			return 1;
			break;
		case 3: // Shave & a Hair Cut
			play(A,4);
			play(G,8);
			play(G,8);
			play(Ab,4);
			play(G,4);
			//Quarter Rest
			Sleep(R4);
			play(B,4);
			play(C,4);
			return 1;
			break;
		case 4: // Mary had a Little Lamb, 1st measure
			play(B,4);
			play(A,4);
			play(G,4);
			play(A,4);
			play(B,4);
			play(B,4);
			play(B,2);
			
			return 1;
			break;
		case 5: // C Arpeggio
			play(LC,8);
			play(LE,8);
			play(G, 8);
			play(C, 8);
			play(G, 8);
			play(LE,8);
			play(LC,4);
			return 1;
			break;
		case 6:
			play(B,8);
			play(C,4);
			//Rest 8;
			Sleep(R8);
			play(G,16);
			play(A,16);
			play(F,4);
			play(F,8);
			return 1;
			break;
		case 7:
			play(A,8);
			play(C,8);
			play(F,8);
			play(A,8);
			play(F,8);
			play(F,16);
			play(F,4);
			return 1;
			break;
		case 8:
			play(A,4);
			play(B,8);
			//rest 8
			Sleep(R8);
			play(G,8);
			play(D,16);
			play(B,16);
			play(A,8);
			return 1;
			break;
		case 9:
			play(F,45);
			play(C,8);
			Sleep(R8);
			play(C,8);
			play(F,4);
			return 1;
			break;
		default:
			return 0;
		}
		break;
		// mthd == 2

		///////////////////
		// Song Snippets //
		///////////////////
	case 2:
		switch (sig){
		case 0: //1. Mary had a Little Lamb
			play(B,4);
			play(A,4);
			play(G,4);
			play(A,4);
			play(B,4);
			play(B,4);
			play(B,2);
			play(A,4);
			play(A,4);
			play(A,2);
			play(B,4);
			play(D,4);
			play(D,2);
			return 1;
			break;
		case 1: //2. Here We Go Round the Mulberry Bush  
			play(F,8);
			play(F,16);
			play(F,16);
			play(F,8);
			play(A,8);
			play(C,16);
			play(C,16);
			play(A,8);
			play(F,8);
			play(F,8);
			
			play(G,16);
			play(G,16);
			play(LE,8);
			play(LC,8);
			play(LC,8);
			play(C,16);
			play(C,16);
			play(A,8);
			play(F,4);
			return 1;
			break;
		case 2: //3. Ring Around the Rosy
					
			//1st Measure
			play(G,4);
			play(G,8);
			play(LE,4);
			play(A,8);

			play(G,45);
			play(LE,4);
			play(F,8);

			play(G,4);
			play(G,8);
			play(LE,4);
			play(A,8);

			play(G,45);
			play(LE,45);
			
			play(G,45);
			play(LE,45);

			play(G,45);
			play(LE,4);
			play(LE,8);
			
			play(G,45);
			play(G,45);
			
			play(LC,45);
			return 1;
			break;
		case 3: //4. Twinkle Twinkle Little Star
				
			play(LC,4);
			play(LC,4);
			play(G,4);
			play(G,4);
			play(A,4);
			play(A,4);
			play(G,2);
			play(F,4);
			play(F,4);
			play(LE,4);
			play(LE,4);
			play(LD,4);
			play(LD,4);
			play(LC,2);
			return 1;
			break;
		case 4: //5. Frere Jacques
			play(F,4);
			play(G,4);
			play(A,4);
			play(F,4);
			play(F,4);
			play(G,4);
			play(A,4);
			play(F,4);
			play(A,4);
			play(B,4);
			play(C,2);
			play(A,4);
			play(B,4);
			play(C,2);
			return 1;
			break;
		case 5: //6. Bingo
			play(G,8);
			play(C,8);
			play(C,8);
			play(G,8);
			play(G,8);
			play(A,8);
			play(A,8);
			play(G,8);
			play(G,8);
			play(C,8);
			play(C,8);
			play(D,8);
			play(D,8);
			play(E,4);
			play(C,4);
			return 1;
			break;
		case 6: //7. Old MacDonald
			play(C,4);
			play(C,4);
			play(C,4);
			play(G,4);
			play(A,4);
			play(A,4);
			play(G,2);
			play(E,4);
			play(E,4);
			play(D,4);
			play(D,4);
			play(C,2);
			return 1;
			break;
		case 7: //8. The Wheels on the Bus
			play(LC,4);
			play(F,4);
			play(F,8);
			play(F,8);
			play(F,4);
			play(A,4);
			play(C,4);
			play(A,4);
			play(F,2);
			play(G,4);
			play(G,4);
			play(G,2);
			play(LE,4);
			play(LD,4);
			play(LC,4);
			
			return 1;
			break;
		case 8: //9. Incy Wincy Spider
			play(LD,8);
			play(G,4);
			play(G,8);
			play(G,4);
			play(A,8);
			play(B,45);
			play(B,4);
			play(B,8);
			play(A,8);
			play(G,8);
			play(A,4);
			play(B,8);
			play(G,25);
			
			return 1;
			break;
		case 9: //10. Imperial March
			play(G,4);
			play(G,4);
			play(LEb,85);
			play(Bb,16);
			
			play(G,4);
			play(LEb,85);
			play(Bb,16);
			play(G,2);
			
			play(D,4);
			play(D,4);
			play(D,4);
			play(Eb,85);
			play(Bb,16);
			
			play(Gb,4);
			play(LEb,85);
			play(Bb,16);
			play(G,4);
			
			return 1;
			break;
		default:
			return 0;
		}
		break;
	}
}	

void treatment(int meth, std::ofstream &outfile){
	//Initialize variables
	std::vector<int> indx_vec; //Randomized vector of index values
	int n = 45; //number of comparisons
	indx_vec = shuff(n); //n == (m)(m-1)/2: the number of unique handshakes
		// In this case 45 = 10(9)/2, or 10 categories for comparison
	int x, y;	//Define integers for coordinates
	int stor_mat[9][9];

	//Run Treatment
	switch (meth){
	case 0: //Syncopation
		outfile << "Syncopated" << std::endl;
		for (unsigned int a = 0; a < 45; a++){
			x = calcx(indx_vec[a], 9);   //Project randomized index onto x coordinate
			y = calcy(indx_vec[a], 9, x); //Project randomized index onto y coordinate

			stor_mat[x][y] = compare(x,(y+1), 0); //Store x and y in the correct method section; (y+1) to correct for off-by-one in the matrix
			// y + 1 prevents self-comparison and uses 9 at the end of the signal.
			//Comparison should be x={0,1,2,3,4,5,6,7,8} and y = {1,2,3,4,5,6,7,8,9}

		}
		break;
	case 1: //Melodic
		outfile << "Melodic" << std::endl;

		//Go through each unique presentation combination, based on indx_vec
		for (unsigned int a = 0; a < 45; a++){
			x = calcx(indx_vec[a], 9);   //Project randomized index onto x coordinate
			y = calcy(indx_vec[a], 9, x); //Project randomized index onto y coordinate

			stor_mat[x][y] = compare(x,(y+1), 1); //Store x and y in the correct method section; (y+1) to correct for off-by-one in the matrix
			// y + 1 prevents self-comparison and uses 9 at the end of the signal.
			//Comparison should be x={0,1,2,3,4,5,6,7,8} and y = {1,2,3,4,5,6,7,8,9}

		}
		output(stor_mat, outfile);

		break;
	case 2: //Musical Identification
		
		int song_mat[10]; // Array for responses
		int answers[10] = { 0, 3, 0, 1, 0, 3, 2, 3, 2, 2};

		std::string opt[10][4]={ // Array for choice options
			{"Mary Had a Little Lamb",			 "Frere Jacques",						"Bingo",							  "The Incy-Wincy Spider"},				//0: Mary Had a Little Lamb (0)
			{"Sing a Song of Sixpence",			 "The Wheels on the Bus",				"On Top of Spaghetti",				  "Here We Go Round the Mulberry Bush"},//1: Here We Go Round the Mulberry Bush (3)
			{"Ring Around the Rosy",			 "Hot Cross Buns",						"Chopsticks",						  "Baa Baa Black Sheep" },				//2: Ring Around the Rosy (0)
			{"Yankee Doodle",					 "Twinkle Twinkle Little Star",			"Ode to Joy",						  "I'm A Little Teapot" },				//3: Twinkle Twinkle Little Star (1) 
			{"Frere Jacques",					 "Hickory Dickory Dock",				"Hot Cross Buns",					  "The Incy-Wincy Spider"},				//4: Frere Jacques (0)
			{"Head, Shoulders, Knees, and Toes", "Hot Cross Buns",						"Frere Jacques",					  "Bingo" },							//5: Bingo (3)
			{"I'm A Little Teapot",				 "Baa Baa Black Sheep",					"Old MacDonald",					  "Head, Shoulders, Knees, and Toes" }, //6: Old MacDonald (2)
			{"Bingo",							 "Frere Jacques" ,						"Hot Cross Buns",					  "The Wheels on the Bus"},				//7: The Wheels on the Bus (3)
			{"Baa Baa Black Sheep",				 "Here We go Round the Mulberry Bush",  "The Incy-Wincy Spider",			  "Sing a Song of Sixpence"},			//8: The Incy-Wincy Spider (2)
			{"Ode to Joy",						 "Beethoven's 5th Symphony",			"The Imperial March (Vader's Theme)", "Air on a G String"}					//9: The Imperial March (Vader's Theme) (2)
		};
		
		char n; //User character response
		

		for (int i = 0; i < 10; i++){
			int m = -2;  //Function return value, resets after a good response
			while (m == -2){
				//present signal i
				ClearScreen();
				std::cout << "Song " << i + 1;
				present(2, i);

				//Present option menu
				std::cout << "\nPlease select a response:" << std::endl;
				std::cout << "\tA.) " << opt[i][0] << std::endl;
				std::cout << "\tB.) " << opt[i][1] << std::endl;
				std::cout << "\tC.) " << opt[i][2] << std::endl;
				std::cout << "\tD.) " << opt[i][3] << std::endl;

				std::cout << "\nSelect any other option to repeat" << std::endl;
				//Get user response:
				std::cin >> n;
				n = toupper(n);

				switch (n){
				case 'A':
					m = 0;
					break;
				case 'B':
					m = 1;
					break;
				case 'C':
					m = 2;
					break;
				case 'D':
					m = 3;
					break;
				default:
					ClearScreen();
					std::cout << "\nRepeating" << std::endl << std::endl;
					break;
				}
				song_mat[i] = m;

				//output results to outfile
				//output(song_mat)

			} 
		}// End of loop through all 10 songs
		outfile << "Song Identification" << std::endl << std::endl;
		for (int i = 0; i < 10; i++){
			if (song_mat[i] == answers[i]) {
				outfile << 1 << std::endl;
			}
			else outfile << 0 << std::endl;
		}
		break; //End Case 2
	}
}

int compare(int x, int y, int mthd){
	//Function returns 0 F(x) > F(y), 1 if F(x) == F(y), 2 if F(x) < F(y).

	char n; //User character response
	int m = -2;  //Function return value
	//While loop to keep presenting signals until an option is checked	
	while (m == -2){
		ClearScreen();
		//present signal x
		std::cout << "Signal A" << std::endl;
		present(mthd,x);
		Sleep(500);
		//present signal 2
		std::cout << "Signal B" << std::endl;
		present(mthd,y);
		Sleep(500);
		//Present option menu
		std::cout << "\nPlease select a response:" << std::endl;
		std::cout << "\tA.) Signal A greater than Signal B" << std::endl;
		std::cout << "\tB.) Signal A equal to Signal B" << std::endl;
		std::cout << "\tC.) Signal A less than Signal B" << std::endl;

		std::cout << "\nSelect any other option to repeat" << std::endl;
		//Get user response:
		std::cin >> n;
		n = toupper(n);
		switch (n){
		case 'A':
			m = 0;
			break;
		case 'B':
			m = 1;
			break;
		case 'C':
			m = 2;
			break;
		default:
			ClearScreen();
			std::cout << "\nRepeating" << std::endl << std::endl;
			break;
		}
	}

	return m;
}


void output(int stor_mat[9][9], std::ofstream &outfile){
	//Takes: 9x9 matrix & the file stream for the .csv
	//Outputs: Upper triangular matrix formatted data
	
	//Tested: prints out [0..44] indices in upper triangular
		//Test matrix: 
		/*
		int test_mat[9][9] = {  //Set index
		{0, 1,  2,  3,  4,  5,  6,  7,  8},
		{0, 9, 10, 11, 12, 13, 14, 15, 16},
		{0, 0, 17, 18, 19, 20, 21, 22, 23},
		{0, 0,  0, 24, 25, 26, 27, 28, 29},
		{0, 0,  0,  0, 30, 31, 32, 33, 34},
		{0, 0,  0,  0,  0, 35, 36, 37, 38},
		{0, 0,  0,  0,  0,  0, 39, 40, 41},
		{0, 0,  0,  0,  0,  0,  0, 42, 43},
		{0, 0,  0,  0,  0,  0,  0,  0, 44}
		};
		*/

	//Print out the results
	for (int i = 0; i < 9; i++){ //iterate across x 
		for (int j = 0; j < 9; j++){ // iterate across y
			if (j >= i) outfile << stor_mat[i][j]; //Not sure if j >= or just >
			if (j < 8) outfile << ",";
		}
		outfile << std::endl;
	}
}

void play(int note, int length){ // notes handled by Enum.
	SetSinFreq_Fine1(0, 0, note, false);
	SetSigSrc(0,0,1,1,false);  //Set source to Freq1
	switch(length){
	case 1:  //Whole Note
		TacOnTime(0, 0, Tac1, 900, false);
		Sleep(1000);
		break;
	case 2:  // Half Note
		TacOnTime(0, 0, Tac1, 500, false);
		Sleep(650);
		break;
	case 25: //Dotted Half
		TacOnTime(0, 0, Tac1, 725, false);
		Sleep(800);
	case 4:  //Quarter
		TacOnTime(0, 0, Tac1, 250, false);
		Sleep(400);
		break;
	case 45: // Dotted quarter
		TacOnTime(0, 0, Tac1, 350, false);
		Sleep(500);
		break;
	case 8:	 //Eighth
		TacOnTime(0, 0, Tac1, 100, false);
		Sleep(300);
		break;
	case 85: //Dotted-Eighth
		TacOnTime(0, 0, Tac1, 220, false);
		Sleep(400); //from 400
	case 16: // 16th
		TacOnTime(0, 0, Tac1, 65, false);
		Sleep(150);
		break;
	case 32:
		TacOnTime(0, 0, Tac1, 25, false);
		Sleep(75);
	}
}

void ClearScreen(){
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }