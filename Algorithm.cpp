// Developer: Shiwei Huang
// Assignment: Lab5
// Keywords: File input output; class; friend method; constructor; operator overloading; ARRAY OF POINTERS;

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;
// Create a data structure to hold the data from the file;
class inventoryItem {
public:
	// a public constructor that takes an int, a float, and a string;
	inventoryItem (int a, float b, string c ) { isbn = a; price = b; title = c; }; 
	string toString ();
	bool operator == ( inventoryItem aRandomItem );
	bool operator == ( int anotherItem );
private:
	//inventoryItem class contains three private data members: an int isbn; float price and string title;
	//set this class to be its own friend, so that the methods in the class can access the private data members of other objects of the same class;
	friend class inventoryItem; 
	int isbn;
	float price;
	string title;

};

// A public to string function that takes no input, and returns a string of the form:
// Return formating: Title: [put title here] ISBN: [put isbn here] Price: $[put price here] 
// returns type: string;
string inventoryItem :: toString () {
	string intToString, floatToString; //to store two converted results;
	ostringstream convertIsbn, convertPrice; //ostringstream used for the string conversion
	int isbnInFunction = isbn;
	float priceInFunction = price;
	convertIsbn << isbnInFunction;
	convertPrice << priceInFunction;

	intToString = convertIsbn.str(); //integer to string conversion;
	floatToString = convertPrice.str(); //float to string conversion;

	return "Title: " + title + " ISBN: " + intToString + " Price: $" + floatToString; //convert everything to the form of string and return;
}


// Operator overloading;
// This is the first operator;
// It takes an inventoryItem as input;
// Returns true if the two inventoryItems have the same isbn;
bool inventoryItem::operator== ( inventoryItem someRandomItem ) {
	if ( isbn == someRandomItem.isbn ) {
		return true;
	} 
	else {
		return false;
	}

}

// Operator overloading;
// This is the second operator;
// The second takes an int as input
// Returns true if the inventoryItem you are in has an isbn equal to the input;
bool inventoryItem::operator== ( int someRandomItem ) {
	if ( someRandomItem == isbn ) {
		return true;
	}
	else {
		return false; 
	}
}

// function readFile takes a string containing a file name as input;
// returns an !!!ARRAY OF POINTERS!!! to inventoryItem; (!!!WHICH IS DIFFERENT THAN "AN ARRAY IN THE FORM OF A POINTER" FROM LAB4!!!) 
// fileName is pass by value. The function should open the file whose name is given as input;
// read it and put the data in the array;
// The function should return an ARRAY OF POINTERS to inventoryItme;
// The function also return the size of the array by reference;
inventoryItem** readFile ( string fileName, int &n ) { //&n: returns the size of array by reference;
	ifstream file(fileName);
	inventoryItem **myArray; //array of pointers;
	if ( file.is_open() ) {
		
		int nextThing;
		file >> nextThing;
		n = nextThing; // which is the first number from my .txt file. This line tells me how many rest number of lines exists in my file;

		//myArray is pointer to pointer to inventory item;
		myArray = new inventoryItem*[n];//allocating array of pointers; allocation array of pointers and pointing to the first cell; 

		string oink1, oink2, woof, quack, roar1, roar2, random1, random2;
		int someNum;
		float someFloat;
		
		for ( int i = 0; i < n; i++ ) {
// ********************************** Fixed file format **********************************
// oink oink [integer] woof [float] quack roar roar [string] meow
// oink oink 215385713 woof 66.07 quack roar roar RDfQn meow
// **********************************End of Fixed file format **********************************
			file >> oink1 >> oink2 >> someNum >> woof >> someFloat >> quack >> roar1 >> roar2 >> random1 >> random2;
			// !!IMPORTANT!! ARRAYS OF POINTERS SYNTAX;
			myArray[i] = new inventoryItem( someNum, someFloat, random1 ); //allocating an object of type inventoryItem;
		}
		/*************** BEGIN QUETION ***************/
		//QUESTION QUESTION: myArray[0] is the pointer; and myArray[0] -> toString () points to the actual blub??
		// cout << "testing under readFile function:" << myArray[0] -> toString() << endl; 
		// cout << "testing to see 2nd line:" << myArray[1] -> toString() << endl;
		/*************** END QUETION ***************/
	}

	else {
		cout << "Sorry. Cannot locate your file." << endl;
	}
	return myArray; //the function return an ARRAY OF POINTES TO inventoryItem;
}

//write a function printFile that takes an array of pointers, an integer containing size of the array; and a string containing a file name as input;
void printFile ( inventoryItem **arrayOfPointers, int sizeOfArray, string fileName ) {
	ofstream myFile;
	myFile.open ("final.txt");
	
	// cout <<"The first line of the output should contain the number of remaining lines in the file: " << sizeOfArray << endl;
	myFile << sizeOfArray << endl; //the first line of the output file should contain the number of remaining lines in the file;

	for ( int i = 0; i < sizeOfArray; i++ ) {
		myFile << arrayOfPointers[i] -> toString() << endl;  //each line should be written using the toString function of each object;
	}
}

//function searchArray takes an array of pointers to inventoryItems, an integer containing the size of the array, and an integer containing an isbn;
//the function should return a pointer to an inventory item whose isbn is equal to the input;
//or a NULL pointer if no such object is found; 
inventoryItem* searchArray ( inventoryItem **arrayPointers, int sizeOfArray, int isbnContainer ) {
	for ( int i = 0; i < sizeOfArray; i++ ) {
		//operator overloading
		//arrayPointers[i] is a pointer;
/*********VERY IMPORTANT NOTE FROM OFFICE HOUR *********/
// *** BEGIN C++ LECTURE ***/
// 	int *b; //pointer;
// 	(*b) = 3; //pointer pointing to integer 3;
// 	count << b << endl; //cout pointer;
// 	count << (*b) << endl; //cout the value that pointer pointed to; 
// *** END C++ LECTURE ***/

// I think arrayPointer[i] is the POINTER;
// * (arrayPointer[i]) is the ACTUAL BLUB  that arrayPointer[i] is pointing to;

//Thus, *(arrayPointers[i]) is the blub  that arrayPoinnter[i] is pointing to; 
		if ( *(arrayPointers[i]) == isbnContainer ) { //BLUB == isbnContainer; // this is also operator overloading;
			cout << "index is " << i << endl; //Testing statement. To see the actual place where the isbn is;
			return arrayPointers[i]; //IMPORTANT return A POINTER TO AN INVENTORYITEM
		}

	}	
	return NULL; // If did not find anything; return NULL; 
}

// The main is used to test all the functions listed above;
// The function should use readFile;
// Allow users to search for a number of ISBNs;
// And use printFile;
int main () {
	
	cout << "What is the file name you want to open (in the type of string): " << endl;

	string myFileName;
	int value;
	cin >> myFileName;
	
	inventoryItem **array = readFile (myFileName, value);
	inventoryItem *pointerToIsbn = searchArray ( array, value, 120153676);
	cout << "this is my location for this isbn: " << pointerToIsbn << endl;

	/************* Begin testing how to print out the pointer to the actual blub *************/
	// The following test statement could work if the actual ISBN is found; 
	// You need to comment out the following statement if it returns null for not causing any SEG FAULT;
	// cout << "the actual content of that object is: " << pointerToIsbn -> toString() << endl; 
	/************* End testing how to print out the pointer to the actual blub *************/

	printFile ( array, value, myFileName); //calling my function printFile;

	return 0;
}



