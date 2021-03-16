// --------------------------------------------------------------------------------
// Name: Brandon Wernke
// Class: Main
// Abstract: Stack of Structures
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// Includes – built-in libraries of functions
// --------------------------------------------------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;


// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// User Defined Types (UDT)
// --------------------------------------------------------------------------------
typedef struct udtNode
{
	int intValue;
	udtNode *pudtNextNode;
} udtNodeType;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
char* GetFileNameFromUser( );
udtNodeType* ReadInValuesFromFile( char* strFilename );
bool OpenFile( char* pstrFileName, ifstream &ifsDataFile );
void PrintLinkedList( udtNodeType *pudtHeadNode );
void DeleteLinkedList( udtNodeType **pudtHeadNode );

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts
// --------------------------------------------------------------------------------
void main( )
{
	// declare variables
	char* strFilename = 0;
	int intUserValue = 0;
	udtNodeType* pudtHeadNode = 0;


	// get filename
	strFilename = GetFileNameFromUser( );

	// read in values from the file
	pudtHeadNode = ReadInValuesFromFile( strFilename );

	// free pointer
	delete [] strFilename;
	strFilename = 0;

	// print linked list
	PrintLinkedList( pudtHeadNode );

	// delete all nodes
	DeleteLinkedList( &pudtHeadNode );

	// test deletion
	cout << "Value of linked list pointer after deletion is: " << pudtHeadNode << endl;


	system( "pause" );
}



// --------------------------------------------------------------------------------
// Name: GetFileNameFomeUser
// Abstract: gets the file name of the file form the user
// --------------------------------------------------------------------------------
char* GetFileNameFromUser( )
{
	// declare char pointer
	char* strFileNameInput = new char[1000];
	int intStringLength = 0;
	char* strFileNameRightSized = 0;
	// prompt user
	cout << "Please enter the file name to process: " << endl;

	// retrieve name
	cin >> strFileNameInput;

	// dynamically allocate space for this string
	intStringLength = strlen( strFileNameInput );
	strFileNameRightSized = new char[ intStringLength + 1];

	// copy to new space
	strcpy( strFileNameRightSized, strFileNameInput );

	// delete input string
	delete [] strFileNameInput;
	strFileNameInput = 0;

	// return filename
	return strFileNameRightSized;
}



// --------------------------------------------------------------------------------
// Name: ReadInValuesFromFile
// Abstract: gets the values from a file and stores them in a linked list
// --------------------------------------------------------------------------------
udtNodeType * ReadInValuesFromFile( char* strFilename )
{
	udtNodeType* pudtHeadNode = 0;
	udtNodeType* pudtNextNode = 0;
	bool blnResult = false;
	ifstream ifsDataFile;
	int intValue = 0;
	// OPEN FILE
	blnResult = OpenFile( strFilename, ifsDataFile );

	// Success?
	if( blnResult == true )
	{
		// use extraction operation as the test for end of file to prevent double read of last value
		while( ifsDataFile.eof() == false )
		{	
			// is the extraction successful?
			if ( ifsDataFile >> intValue ) 
			{
				// allocate
				pudtHeadNode = new udtNodeType;

				// populate
				pudtHeadNode->intValue = intValue;

				// link
				pudtHeadNode->pudtNextNode = pudtNextNode;

				// ready for next
				pudtNextNode = pudtHeadNode;
			}
		}

		// All done
		ifsDataFile.close();
	}

	return pudtHeadNode;
}



// --------------------------------------------------------------------------------
// Name: OpenFile
// Abstract: opens the file in the given location
// --------------------------------------------------------------------------------
bool OpenFile( char * pstrFileName, ifstream & ifsDataFile )
{
	bool blnResult = false;

	// Open the file
	ifsDataFile.open( pstrFileName, istream::in );

	// Was the file open successfully?
	if(ifsDataFile.is_open() == true)
	{
		// Yes
		blnResult = true;
	}
	else
	{
		// No, display error message
		cout << "Error opening file: " << pstrFileName << endl;
	}

	return blnResult;
}



// --------------------------------------------------------------------------------
// Name: PrintLinkedList
// Abstract: prints the nodes in the list
// --------------------------------------------------------------------------------
void PrintLinkedList( udtNodeType * pudtHeadNode )
{
	udtNodeType* pudtCurrentNode = 0;
	udtNodeType* pudtNextNode = 0;

	int intIndex = 0;

	// start at the top
	pudtCurrentNode = pudtHeadNode;

	while ( pudtCurrentNode != 0 )
	{
		// count
		intIndex += 1;

		// display current value
		cout << "Value at node #" << intIndex << " is " << pudtCurrentNode->intValue << endl;

		// get next node
		pudtNextNode = pudtCurrentNode->pudtNextNode;

		// move to next node
		pudtCurrentNode = pudtNextNode;
	}
}



// --------------------------------------------------------------------------------
// Name: DeleteLinkedList
// Abstract: Deletes all nodes in the linked list
// --------------------------------------------------------------------------------
void DeleteLinkedList( udtNodeType  **pudtHeadNode )
{
	udtNodeType* pudtNextNode = 0;

	// loop until the end of the list ( pointer will be 0 )
	while ( *pudtHeadNode != 0 )
	{
		// get next node first
		pudtNextNode = (*pudtHeadNode)->pudtNextNode;

		// delete the node
		delete[] *pudtHeadNode;
		*pudtHeadNode = 0;

		// move to next node
		*pudtHeadNode = pudtNextNode;	
	}
}
