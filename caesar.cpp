#include <iostream>
#include <string>
using namespace std;

void printToConsole (string str) {
	cout << str << endl;
}


string encryptLine(string unenLine, int key) {
	string enLine;	
	int firstChar = 97;
	int lastChar = 122;	
	
	for (unsigned int i = 0; i < unenLine.length(); i++) {
		int unenchar = (int)unenLine.at(i);
		
		// New character is in Range of first and lastCharacter
		if (firstChar <= unenchar + key && unenchar + key <= lastChar) {
			enLine.append(1, (char)(unenchar+key));
		}
		 
		// New character is larger than lastCharacter
		else if (unenchar + key > lastChar) {			
			enLine.append(1, (char)((unenchar+key) % lastChar + firstChar - 1));
		}
		
		// New character is smaller than firstCharacter
		else {
			enLine.append(1, (char)(lastChar + ((unenchar+key) - firstChar + 1)));
		}		
	}
	return enLine;
};

int main()
{	
	while (true) {
		
		// Get key
		int k;
		printToConsole("Enter your key:");
		cin >> k;
		
		// Get string
		string unencrypted;
		printToConsole("Enter your unencrypted word (only lowercase):");
		cin >> unencrypted;
		
		// Encrypt String
		string encrypted = encryptLine(unencrypted, k);		
		
		//Print encrypted string
		printToConsole("Your encrypted line is: " + encrypted);
	}	
	return 0;
}
