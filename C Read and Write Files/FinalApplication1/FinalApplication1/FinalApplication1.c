// ------------------------------------------------------------------------------------------
// Name: Brandon Wernke
// Class: C Programming 1 - 151-400
// Abstract: Final - Application 1
// ------------------------------------------------------------------------------------------


// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

// --------------------------------------------------------------------------------
// Constants
// --------------------------------------------------------------------------------
#define true 1
#define false 0

const char astrSTATES[2][10] = {
									"Ohio",
									"Kentucky"
								};

const char astrOHIO_COUNTIES[2][10] = {
									"Hamilton",
									"Butler"
								};

const char astrKENTUCKY_COUNTIES[2][10] = {
										"Boone",
										"Kenton"
									};

const char astrRACES[5][17] = {
									"Caucasian",
									"African American",
									"Hispanic",
									"Asian",
									"Other"
								};

const char strFILE_PATH[25] = "c:\\temp\\BureauData.txt";

const int intLENGTH_OF_RACE_ARRAY = 5;
const char chrLOWER_A = 'a';
const char chrLOWER_Z = 'z';
const int intCASE_CHANGE_INCREMENT = 32;

// --------------------------------------------------------------------------------
// User Defined Types (UDTs)
// --------------------------------------------------------------------------------
typedef int boolean;

typedef struct 
{
	char strDateofSurvey[ 11 ];
	int intState;
	int intCounty;
	int intRace;
	int intNumberinHousehold;
	double dblYearlyIncome;
} udtSurveyDataType;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
void InitializeSurveyData( udtSurveyDataType* pudtSurveyData );
char ShowMenu( );
	boolean ValidateMenuChoice( char* pcharUserChoice );
void GetInput( udtSurveyDataType* udtSurveyData );
	void GetDateOfSurvey( char* strDate );
		boolean ValidateDate( char* strDate );
	int GetStateID( );
		boolean ValidateIndex( int intIntegerToValidate, int intUpperLimit );
	int GetCountyID( int intStateID );
	int GetRaceID( );
	int GetNumberInHousehold( );
		boolean ValidateHousehold( int intNumberInHousehold );
	double GetYearlyIncome( );
		boolean ValidateIncome( double dblIncome );
void SaveSurveyData( udtSurveyDataType udtSurveyData  );
// string prototypes
void StringCopy( char strDestination[ ], char strSource[ ] );
int StringLength ( char strSource[ ] );
void StringAppend ( char strDestination[ ], char strSource[ ] );

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts.
// --------------------------------------------------------------------------------
void main( )
{
	// declare variables
	udtSurveyDataType audtSurveyData;
	char chrUserMenuChoice = '\0';

	// program loop
	do
	{
		// show menu, return choice
		chrUserMenuChoice = ShowMenu();

		// initialize our structure array, for looping through to save it
		InitializeSurveyData( &audtSurveyData );

		// if A, carry on collecting data
		if ( chrUserMenuChoice == 'A' )
		{
			GetInput( &audtSurveyData );
			SaveSurveyData( audtSurveyData );
		}

		fseek( stdin, 0, SEEK_END ); // clear input stream
	}while ( chrUserMenuChoice != 'Q' );

	//SaveData( audtSurveyDataList );

	printf( "\n" );
	printf( "Program ended.\n");
	system( "pause" );

}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyData
// Abstract: Initializes survey data structure elements to "" or 0
// --------------------------------------------------------------------------------
void InitializeSurveyData( udtSurveyDataType * pudtSurveyData )
{
	StringCopy( pudtSurveyData->strDateofSurvey, "" );
	pudtSurveyData->intState = 0;
	pudtSurveyData->intCounty = 0;
	pudtSurveyData->intRace = 0;
	pudtSurveyData->intNumberinHousehold = 0;
	pudtSurveyData->dblYearlyIncome = 0;
}



// ------------------------------------------------------------------------------------------
// Name: ShowMenu
// Abstract: Shows user menu, validates input and returns valid input
// ------------------------------------------------------------------------------------------
char ShowMenu( )
{
	// declare variables
	char chrUserChoice = '\0';
	char* pcharUserChoice = &chrUserChoice;

	// display menu
	printf( "---------------------------\n" );
	printf( "|Select from these choices:\n" );
	printf( "---------------------------\n" );
	printf( "A) Enter Survey Data.\n" );
	printf( "Q) Exit.\n" );
	printf( "\n" );

	// scan choice
	scanf("%c", &chrUserChoice );

	// validate, recurse back if invalid
	if( ValidateMenuChoice( pcharUserChoice ) == false ) 
	{
		printf( "Invalid input\n" );
		printf( "\n" );
		fseek( stdin, 0, SEEK_END ); // clear input stream
		ShowMenu();
	}

	return chrUserChoice;
}



// ------------------------------------------------------------------------------------------
// Name: ValidateMenuChoice
// Abstract: Validates input, converts userchoice to uppercase by pointer
// ------------------------------------------------------------------------------------------
boolean ValidateMenuChoice( char* pcharUserChoice )
{
	// declare variables
	boolean blnValidChoice = false;

	// convert to uppercase
	// is it a lowercase letter?
	if ( *pcharUserChoice >= chrLOWER_A && *pcharUserChoice <= chrLOWER_Z )
	{
		// convert to upper
		*pcharUserChoice = *pcharUserChoice - intCASE_CHANGE_INCREMENT;
	}

	// check if valid choice
	if ( *pcharUserChoice == 'A' || *pcharUserChoice == 'Q' )
	{
		blnValidChoice = true;
	}

	return blnValidChoice;
}



// ------------------------------------------------------------------------------------------
// Name: GetInput
// Abstract: Gets needed input for 
// ------------------------------------------------------------------------------------------
void GetInput( udtSurveyDataType* udtSurveyData  )
{
	// declare variables
	char strDate[ 11 ] = "";
	// get date of survey
	GetDateOfSurvey( strDate );
	StringCopy( udtSurveyData->strDateofSurvey, strDate );
	// get state
	udtSurveyData->intState = GetStateID();
	// get county
	udtSurveyData->intCounty = GetCountyID( udtSurveyData->intState );
	// get race
	udtSurveyData->intRace = GetRaceID();
	// get number of household
	udtSurveyData->intNumberinHousehold = GetNumberInHousehold();
	// get yearly income
	udtSurveyData->dblYearlyIncome = GetYearlyIncome();
}



// ------------------------------------------------------------------------------------------
// Name: GetInput
// Abstract: Gets needed input for 
// ------------------------------------------------------------------------------------------
void GetDateOfSurvey( char* strDate )
{

	// prompt for input
	do
	{
		printf( "Enter Date of Survey (MM-DD-YYYY): \n");
		scanf( "%s", strDate );
	} while( ValidateDate( strDate ) == false );

}



// ------------------------------------------------------------------------------------------
// Name: ValidateDate
// Abstract: Validates date is present and of the right length and format, does not verify it is 
//			 a true date, just the right format
// ------------------------------------------------------------------------------------------
boolean ValidateDate( char* strDate )
{
	// declare variables
	boolean blnValidDate = false;

	if ( StringLength( strDate ) == 10 ) // length of proper date format
	{
		if ( strDate[2] == '-' )
		{
			if ( strDate[5] == '-' )
			{
				blnValidDate = true;
			}
		}
	}

	if ( blnValidDate == false )
	{
		printf( "Invalid input\n" );
		printf( "\n" );
		fseek( stdin, 0, SEEK_END ); // clear input stream
	}

	return blnValidDate;
}



// ------------------------------------------------------------------------------------------
// Name: GetStateID
// Abstract: Gets state id
// ------------------------------------------------------------------------------------------
int GetStateID( )
{
	// declare variables
	int intStateID = 0;
	const int intUPPER_LIMIT = 2; 
	// prompt for input
	do
	{
		printf( "Choose the state: \n");
		printf( "\t1) %s\n", astrSTATES[ 0 ]);
		printf( "\t2) %s\n", astrSTATES[ 1 ]);
		scanf( "%d", &intStateID );
		// decrement choice to align with indices
		intStateID -= 1;
	} while( ValidateIndex( intStateID, intUPPER_LIMIT ) == false );

	return intStateID;
}



// ------------------------------------------------------------------------------------------
// Name: ValidateInteger
// Abstract: Validates integer value is >= 0 < upper limit
// ------------------------------------------------------------------------------------------
boolean ValidateIndex( int intIntegerToValidate, int intUpperLimit ) 
{
	// declare variables
	boolean blnValidIndex = false;

	if ( intIntegerToValidate >= 0 )
	{
		if ( intIntegerToValidate < intUpperLimit )
		{
			blnValidIndex = true;
		}
	}

	if ( blnValidIndex == false )
	{
		printf( "Invalid input\n" );
		printf( "\n" );
		fseek( stdin, 0, SEEK_END ); // clear input stream
	}

	return blnValidIndex;
}



// ------------------------------------------------------------------------------------------
// Name: GetCountyID
// Abstract: Gets county ID based on State ID
// ------------------------------------------------------------------------------------------
int GetCountyID( int intStateID )
{
	// declare variables
	int intCountyID = 0;
	const int intUPPER_LIMIT = 2; 
	// prompt for input
	do
	{
		printf( "Choose the county: \n"); // ohio counties
		if( intStateID == 0 )
		{
			printf( "\t1) %s\n", astrOHIO_COUNTIES[ 0 ]);
			printf( "\t2) %s\n", astrOHIO_COUNTIES[ 1 ]);
		}
		else if( intStateID == 1 )
		{
			printf( "\t1) %s\n", astrKENTUCKY_COUNTIES[ 0 ]);
			printf( "\t2) %s\n", astrKENTUCKY_COUNTIES[ 1 ]);
		}
		scanf( "%d", &intCountyID );
		// decrement choice to align with indices
		intCountyID -= 1;
	} while( ValidateIndex( intCountyID, intUPPER_LIMIT ) == false );

	return intCountyID;
}



// ------------------------------------------------------------------------------------------
// Name: GetRaceID
// Abstract: Gets race ID
// ------------------------------------------------------------------------------------------
int GetRaceID( )
{
	// declare variables
	int intRaceID = 0;
	int intIndex = 0;
	// prompt for input
	do
	{
		printf( "Choose the race of Head of Household: \n");
		for( intIndex = 0; intIndex < intLENGTH_OF_RACE_ARRAY; intIndex += 1 )
		{
			printf( "\t%d) %s\n", intIndex + 1, astrRACES[intIndex]);
		}
		scanf( "%d", &intRaceID );
		// decrement choice to align with indices
		intRaceID -= 1;
	} while( ValidateIndex( intRaceID, intLENGTH_OF_RACE_ARRAY ) == false );

	return intRaceID;
}



// ------------------------------------------------------------------------------------------
// Name: GetNumberInHousehold
// Abstract: Gets number in household
// ------------------------------------------------------------------------------------------
int GetNumberInHousehold( )
{
	// declare variables
	int intNumberInHousehold = 0;
	// prompt for input
	do
	{
		printf( "Enter number in household: \n");
		scanf( "%d", &intNumberInHousehold );
	} while( ValidateHousehold( intNumberInHousehold ) == false );

	return intNumberInHousehold;
}



// ------------------------------------------------------------------------------------------
// Name: ValidateHousehold
// Abstract: validates that the number in household is above zero
// ------------------------------------------------------------------------------------------
boolean ValidateHousehold( int intNumberInHousehold )
{
	// declare variables
	boolean blnValidHousehold = false;

	if( intNumberInHousehold > 0 )
	{
		blnValidHousehold = true;
	}

	if ( blnValidHousehold == false )
	{
		printf( "Invalid input\n" );
		printf( "\n" );
		fseek( stdin, 0, SEEK_END ); // clear input stream
	}

	return blnValidHousehold;
}



// ------------------------------------------------------------------------------------------
// Name: GetYearlyIncome
// Abstract: Gets yearly income
// ------------------------------------------------------------------------------------------
double GetYearlyIncome( )
{
	// declare variables
	double dblYearlyIncome = 0;
	// prompt for input
	do
	{
		printf( "Enter yearly income of household: \n");
		scanf( "%lf", &dblYearlyIncome );
	} while( ValidateIncome( dblYearlyIncome ) == false );

	return dblYearlyIncome;
}



// ------------------------------------------------------------------------------------------
// Name: ValidateIncome
// Abstract: Validates income is present, numeric, and above zero
// ------------------------------------------------------------------------------------------
boolean ValidateIncome( double dblIncome )
{
	// declare variables
	boolean blnValidIncome = false;

	if( dblIncome > 0 )
	{
		blnValidIncome = true;
	}

	if ( blnValidIncome == false )
	{
		printf( "Invalid input\n" );
		printf( "\n" );
		fseek( stdin, 0, SEEK_END ); // clear input stream
	}

	return blnValidIncome;
}



// --------------------------------------------------------------------------------
// Name: SaveSurveyData
// Abstract: Appends line of data to file at file path
// --------------------------------------------------------------------------------
void SaveSurveyData( udtSurveyDataType udtSurveyData )
{
	// declare variables
	FILE *filSaveTo;

	filSaveTo = fopen( strFILE_PATH, "a" );

	// save strDateofSurvey
	fprintf( filSaveTo, "\n%s,", udtSurveyData.strDateofSurvey);
	// save county
	if( udtSurveyData.intState == 0 ) // ohio counties
	{
		fprintf( filSaveTo, " %s,", astrOHIO_COUNTIES[ udtSurveyData.intCounty ] );
	}
	else
	{
		fprintf( filSaveTo, " %s,", astrKENTUCKY_COUNTIES[ udtSurveyData.intCounty ] );
	}
	// save state
	fprintf( filSaveTo, " %s,", astrSTATES[ udtSurveyData.intState ] );
	// save race
	fprintf( filSaveTo, " %s,", astrRACES[ udtSurveyData.intRace ] );
	// save number of household
	fprintf( filSaveTo, " %d,", udtSurveyData.intNumberinHousehold );
	// save income
	fprintf( filSaveTo, " %lf", udtSurveyData.dblYearlyIncome );
	// close file
	fclose( filSaveTo );
}


// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------
// String Functions
// --------------------------------------------------------------------------------
// --------------------------------------------------------------------------------



// --------------------------------------------------------------------------------
// Name: StringCopy
// Abstract: Copies source to destination
// --------------------------------------------------------------------------------
void StringCopy( char strDestination[ ], char strSource[ ] )
{
	// declare variables
	int intIndex = 0;

	while( strSource[ intIndex ] != 0 )
	{
		strDestination[ intIndex ] = strSource[ intIndex ];
		intIndex += 1;
	}

	// terminate
	strDestination[ intIndex ] = 0;
}



// ------------------------------------------------------------------------------------------
// Name: StringLength
// Abstract: Return the string length
// ------------------------------------------------------------------------------------------
int StringLength ( char strSource[ ] )
{
	// declare variables
	int intLength = 0;
	int intIndex = 0;

	// loop over string, until null char is reached
	while( strSource[ intIndex ] != 0 )
	{
		intIndex += 1;
	}

	intLength = intIndex;

	return intLength;
}



// ------------------------------------------------------------------------------------------
// Name: StringAppend
// Abstract: Appends source to desination
// ------------------------------------------------------------------------------------------
void StringAppend ( char strDestination[ ], char strSource[ ] )
{
	// declare variables
	int intIndex = 0;
	int intDestinationEndIndex = 0;

	// get destination end, length is index of termination char
	intDestinationEndIndex = StringLength( strDestination );

	// loop over source and append to destination
	while ( strSource[ intIndex ] != 0 )
	{
		strDestination[ intDestinationEndIndex ] = strSource[ intIndex ];
		intIndex += 1;
		// increment end index
		intDestinationEndIndex += 1;
	}

	// Terminate destination
	strDestination[ intDestinationEndIndex ] = 0;
}