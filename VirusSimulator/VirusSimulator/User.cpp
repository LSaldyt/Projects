#include "stdafx.h"
#include "User.hpp"
//You can put includes in stdafx or Declarations.hpp


User::User()
{

	name = generateRandomName();

	
}


//Generates a random name. Callable by anything. Easy to generate system brand names and stuff
string User::generateRandomName() {

	string generatedName;

	//training and personality inputted
	//This is to generate a random name. The idea is awesome sounding names which are utterly alien.

	//This generates random numbers though actual entropy

	std::random_device rd;
	srand(rd());

	//Lengths up to 13 and no shorter than 4
	int stringNameLength = rand() % 9 + 4;

	//This is error avoidance. Who knows if it really matters but I want to avoid it checking junk.
	bool isFirstChar = true;
	bool isSecondChar = true;
	int distanceFromVowel = 0;

	//Initing to stop the once in 255 error which would occur otherwise.
	char lastCharUsed = 7;


	//TODO: Make the names more realistic without using actual lists of prefixes and suffixes.
	while (stringNameLength > 0) {

		if (isFirstChar) {
			//Any char works here
			//Should work with only caps
			char ranCharOne = rand() % 26 + 65;
			distanceFromVowel++;

			if (ranCharOne == 65 || ranCharOne == 69 || ranCharOne == 73 ||
				ranCharOne == 79 || ranCharOne == 85) {
				distanceFromVowel = 0;
			}
			//Append it to the string
			generatedName.append(1u, ranCharOne);
			lastCharUsed = ranCharOne;

			//cout << "This is your name " << name;

			//Never run again
			isFirstChar = false;
		}
		else {
			//generate either a vouel or not a vouel, but determine what here
			//Casts the int as a float, again as error avoidance.
			float vowelLikely = pow((float)distanceFromVowel, 2.0);

			//Rolls a 1d12 and compares it to the square of the number of letters since a vouel.
			vowelLikely = vowelLikely - rand() % 12;

			if (distanceFromVowel > 2) {
				vowelLikely = 1;
			}



			//This forces a vouel second
			if (isSecondChar && distanceFromVowel == 1) {
				int ranVouel = rand() % 5;

				//TODO: make some vouels show up more often
				if (ranVouel == 0) {
					char randomVowelChar = 'a';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVouel == 1) {
					char randomVowelChar = 'e';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVouel == 2) {
					char randomVowelChar = 'i';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVouel == 3) {
					char randomVowelChar = 'o';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVouel == 4) {
					char randomVowelChar = 'u';
					generatedName.append(1u, randomVowelChar);


				}

				//If last char is vouel we can set it to whatever, I like the bell.
				lastCharUsed = 7;

				//never run again
				distanceFromVowel = 0;

			}
			else if (vowelLikely > 0) {
				int ranVowel = rand() % 5;

				distanceFromVowel = 0;

				if (ranVowel == 0) {
					char randomVowelChar = 'a';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVowel == 1) {
					char randomVowelChar = 'e';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVowel == 2) {
					char randomVowelChar = 'i';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVowel == 3) {
					char randomVowelChar = 'o';
					generatedName.append(1u, randomVowelChar);
				}
				else if (ranVowel == 4) {
					char randomVowelChar = 'u';
					generatedName.append(1u, randomVowelChar);
				}

			}
			else {
				char ranChar = 'a';
				while (ranChar == 'a' || ranChar == 'e' || ranChar == 'i' || ranChar == lastCharUsed ||
					ranChar == 'o' || ranChar == 'u' || ranChar == 'q' || ranChar == 'x' || ranChar == 'z') {

					//forces standard letter without 21 checks.
					ranChar = rand() % 26 + 97;
					distanceFromVowel++;

				}

				generatedName.append(1u, ranChar);

				lastCharUsed = ranChar;


				isSecondChar = false;



			}




		}










		//ends it

		stringNameLength--;
	}

	return generatedName;
}


void User::login(string username, string password)
{




}

void User::logout()
{

}

string User::getName()
{
	return name;
}