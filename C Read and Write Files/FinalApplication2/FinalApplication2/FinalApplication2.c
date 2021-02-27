// ------------------------------------------------------------------------------------------
// Name: Brandon Wernke
// Class: C Programming 1 - 151-400
// Abstract: Final - Application 2
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
const int intARRAY_SIZE = 100;
const int intSTRUCTURE_LENGTH = 6;
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

const adblBASIS_OF_POVERTY[5] = {
	12000,
	18000,
	25000,
	30000,
	40000
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
	char strState[ 10 ];
	char strCounty[ 10 ];
	char strRace[ 17 ];
	int intNumberinHousehold;
	double dblYearlyIncome;
} udtSurveyDataType;

typedef struct 
{
	int intOhioCount;
	int intHamiltonCount;
	int intBooneCount;
	int intButlerCount;
	int intKentonCount;
	int intKentuckyCount;
	int intCaucasianCount;
	int intAfricanAmericanCount;
	int intHispanicCount;
	int intAsianCount;
	int intOtherCount;
} udtSurveyCountsType;

typedef struct 
{
	double dblAllAverage;
	double dblOhioAverage;
	double dblHamiltonAverage;
	double dblBooneAverage;
	double dblKentonAverage;
	double dblKentuckyAverage;
	double dblButlerAverage;
	double dblCaucasianAverage;
	double dblAfricanAmericanAverage;
	double dblHispanicAverage;
	double dblAsianAverage;
	double dblOtherAverage;
} udtIncomeAveragesType;

typedef struct 
{
	double dblAllPercent;
	double dblOhioPercent;
	double dblHamiltonPercent;
	double dblBoonePercent;
	double dblKentonPercent;
	double dblKentuckyPercent;
	double dblButlerPercent;
	double dblCaucasianPercent;
	double dblAfricanAmericanPercent;
	double dblHispanicPercent;
	double dblAsianPercent;
	double dblOtherPercent;
} udtPercentBelowPovertyType;


// --------------------------------------------------------------------------------
// Prototypes
// --------------------------------------------------------------------------------
void InitializeSurveyDataList( udtSurveyDataType audtAddressList[ ] );
void InitializeSurveyData( udtSurveyDataType* pudtSurveyData );
void InitializeSurveyCounts( udtSurveyCountsType* pudtSurveyCounts );
void InitializeSurveyAverages( udtIncomeAveragesType* pudtSurveyAverages );
void InitializeSurveyPercents( udtPercentBelowPovertyType* pudtPercentBelowPoverty );

void PopulateSurveyDataList( udtSurveyDataType audtAddressList[ ], int* pintRecordCount );
	int OpenInputFile( char strFileName[ ], FILE** ppfilInput );
	int ReadNextLineFromFile( char strBuffer[ ], FILE* pfilInput );
	void AddSurveyToArray( char strAddress[ ], udtSurveyDataType* pudtAddress );
	void GetNextField( char strNextField[ ], char strAddress[ ], char chrDelimiter );

void PerformInitialCounts( udtSurveyDataType udtSurveyDataList[ ], int intRecordCount, udtSurveyCountsType * pudtSurveyCounts );
	void CalculateTotalSurveyedByCounty( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount
		,udtSurveyCountsType* pudtSurveyCounts );
	void CalculateTotalSurveyedByRace( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount
		,udtSurveyCountsType* pudtSurveyCounts );
void CalculateAverageIncomes( int intRecordCount, udtSurveyDataType audtSurveyDataList[ ], udtIncomeAveragesType* pudtIncomoeAverages, udtSurveyCountsType udtSurveyCounts );
	double GetTotalIncome( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount );
	void GetCountyTotals( udtSurveyDataType audtSurveyDataList[ ], double* pdblOhioTotal, double* pdblHamiltonTotal, double* pdblButlerTotal, double* pdblKentuckyTotal, double* pdblBooneTotal, double* pdblKentonTotal, int intRecordCount );
	void GetRaceTotals( udtSurveyDataType audtSurveyDataList[ ], double* pdblCaucasianTotal, double* pdblAfricanAmericanTotal, double* pdblHispanicTotal, double* pdblAsianTotal, double* pdblOtherTotal, int intRecordCount ); 
void CalculatePercentsBelowPoverty( int intRecordCount, udtSurveyDataType audtSurveyDataList[ ], udtPercentBelowPovertyType* pudtPercentBelowPoverty, udtSurveyCountsType udtSurveyCounts );
	void GetCountyTotalBelow( udtSurveyDataType audtSurveyDataList[ ], int* pintTotalBelow, int* pintOhioBelow, int* pintHamiltonBelow, int* pintButlerBelow, int* pintKentuckyBelow, int* pintBooneBelow, int* pintKentonBelow, int intRecordCount );
		boolean IsBelowPoverty( double dblYearlyIncome, int intNumberinHousehold );
	void GetRaceTotalBelow( udtSurveyDataType audtSurveyDataList[ ], int* pintCaucasianBelow, int* pintAfricanAmericanBelow, int* pintHispanicBelow, int* pintAsianBelow, int* pintOtherBelow, int intRecordCount );

char ShowMenu( );
	boolean ValidateMenuChoice( char* pcharUserChoice );

void ShowTotalSurveyed( int intRecordCount );
void DisplayTotalSurveyedByCounty( udtSurveyCountsType udtSurveyCounts );
void DisplayTotalSurveyedByRace( udtSurveyCountsType udtSurveyCounts );

void DisplayAverageIncome( udtIncomeAveragesType udtIncomeAverages );
void DisplayAverageIncomeByCounty( udtIncomeAveragesType udtIncomeAverages );
void DisplayAverageIncomeByRace( udtIncomeAveragesType udtIncomeAverages );

void DisplayBelowPoverty( udtPercentBelowPovertyType udtPercentBelowPoverty );
void DisplayBelowPovertyByCounty( udtPercentBelowPovertyType udtPercentBelowPoverty );
void DisplayBelowPovertyByRace( udtPercentBelowPovertyType udtPercentBelowPoverty );

// string functions
void StringCopy( char strDestination[ ], char strSource[ ] );
int StringLength ( char strSource[ ] );
void StringAppend ( char strDestination[ ], char strSource[ ] );
int FindLetterIndex( char strSource[ ],  char chrLetterToFind );
void Trim( char strSource[ ] );
boolean IsWhiteSpace( char chrLetterToCheck );
int CountWords( char strSource[ ] );
void SubString ( char strDestination[ ], char strSource[ ], int intStartIndex, int intLength );
boolean StringCompare( char strFirstString[ ], char strSecondString[ ] );

// --------------------------------------------------------------------------------
// Name: main
// Abstract: This is where the program starts.
// --------------------------------------------------------------------------------
void main( )
{
	// declare variables
	int intRecordCount = 0;
	char chrUserMenuChoice = 0;
	udtSurveyCountsType udtSurveyCounts;
	int* pintRecordCount = &intRecordCount;
	udtSurveyDataType audtSurveyDataList [ 100 ];
	udtIncomeAveragesType udtIncomeAverages;
	udtPercentBelowPovertyType udtPercentBelowPoverty;

	// initialize address list
	InitializeSurveyDataList( audtSurveyDataList );

	// populate address list
	PopulateSurveyDataList( audtSurveyDataList, pintRecordCount );

	// init counts struct
	InitializeSurveyCounts( &udtSurveyCounts );

	// perform initial counts
	PerformInitialCounts( audtSurveyDataList, intRecordCount, &udtSurveyCounts );

	// init survey averages struct
	InitializeSurveyAverages( &udtIncomeAverages );

	// get the average incomes by county
	CalculateAverageIncomes( intRecordCount, audtSurveyDataList, &udtIncomeAverages, udtSurveyCounts );

	// init percents structure
	InitializeSurveyPercents( &udtPercentBelowPoverty );

	// calculate percents below poverty
	CalculatePercentsBelowPoverty( intRecordCount, audtSurveyDataList, &udtPercentBelowPoverty, udtSurveyCounts );

	// program loop
	do
	{
		// show menu, return choice
		chrUserMenuChoice = ShowMenu();

		switch ( chrUserMenuChoice )
		{
			case 'A': // show total surveryed
				ShowTotalSurveyed( intRecordCount );
				break;
			case 'B': // show total surveryed by state/county
				DisplayTotalSurveyedByCounty( udtSurveyCounts );
				break;
			case 'C': // show total surveryed by race
				DisplayTotalSurveyedByRace( udtSurveyCounts );
				break;
			case 'D': // show average household income
				DisplayAverageIncome( udtIncomeAverages );
				break;
			case 'E': // show average household income by state/county
				DisplayAverageIncomeByCounty( udtIncomeAverages );
				break;
			case 'F': // show average household income by race
				DisplayAverageIncomeByRace( udtIncomeAverages );
				break;
			case 'G': // percentage below poverty
				DisplayBelowPoverty( udtPercentBelowPoverty );
				break;
			case 'H': // percentage below poverty by state/county
				DisplayBelowPovertyByCounty( udtPercentBelowPoverty );
				break;
			case 'I': // percentage below poverty by race
				DisplayBelowPovertyByRace( udtPercentBelowPoverty );
				break;
		}

		fseek( stdin, 0, SEEK_END ); // clear input stream
	}while ( chrUserMenuChoice != 'Q' );

	printf( "\n" );
	printf( "Program ended.\n");
	system( "pause" );
}



// --------------------------------------------------------------------------------
// Name: InitializeAddressList
// Abstract: Initializes address list
// --------------------------------------------------------------------------------
void InitializeSurveyDataList( udtSurveyDataType pudtSurveyDataList[ ] )
{
	// declare variables
	int intIndex = 0;
	// inititalize each element of array
	for( intIndex = 0; intIndex < intARRAY_SIZE; intIndex += 1 )
	{
		InitializeSurveyData( &pudtSurveyDataList[ intIndex ] );
	}
}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyData
// Abstract: Initializes survey data structure elements to "" or 0
// --------------------------------------------------------------------------------
void InitializeSurveyData( udtSurveyDataType * pudtSurveyData )
{
	StringCopy( pudtSurveyData->strDateofSurvey, "" );
	StringCopy( pudtSurveyData->strState, "" );
	StringCopy( pudtSurveyData->strCounty, "" );
	StringCopy( pudtSurveyData->strRace, "" );
	pudtSurveyData->intNumberinHousehold = 0;
	pudtSurveyData->dblYearlyIncome = 0;
}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyCounts
// Abstract: Initializes survey counts structure elements to 0
// --------------------------------------------------------------------------------
void InitializeSurveyCounts( udtSurveyCountsType * pudtSurveyCounts )
{
	pudtSurveyCounts->intOhioCount = 0;
	pudtSurveyCounts->intHamiltonCount = 0;
	pudtSurveyCounts->intButlerCount = 0;
	pudtSurveyCounts->intKentuckyCount = 0;
	pudtSurveyCounts->intBooneCount = 0;
	pudtSurveyCounts->intKentonCount = 0;
	pudtSurveyCounts->intCaucasianCount = 0;
	pudtSurveyCounts->intAfricanAmericanCount = 0;
	pudtSurveyCounts->intHispanicCount = 0;
	pudtSurveyCounts->intAsianCount = 0;
	pudtSurveyCounts->intOtherCount = 0;
}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyAverages
// Abstract: Initializes survey averages structure elements to 0
// --------------------------------------------------------------------------------
void InitializeSurveyAverages( udtIncomeAveragesType * pudtSurveyAverages )
{
	pudtSurveyAverages->dblAllAverage = 0.0;
	pudtSurveyAverages->dblOhioAverage = 0.0;
	pudtSurveyAverages->dblHamiltonAverage = 0.0;
	pudtSurveyAverages->dblButlerAverage = 0.0;
	pudtSurveyAverages->dblKentuckyAverage = 0.0;
	pudtSurveyAverages->dblBooneAverage = 0.0;
	pudtSurveyAverages->dblKentonAverage = 0.0;
	pudtSurveyAverages->dblCaucasianAverage = 0.0;
	pudtSurveyAverages->dblAfricanAmericanAverage = 0.0;
	pudtSurveyAverages->dblHispanicAverage = 0.0;
	pudtSurveyAverages->dblAsianAverage = 0.0;
	pudtSurveyAverages->dblOtherAverage = 0.0;
}



// --------------------------------------------------------------------------------
// Name: InitializeSurveyPercentss
// Abstract: Initializes survey percents structure elements to 0
// --------------------------------------------------------------------------------
void InitializeSurveyPercents( udtPercentBelowPovertyType * pudtPercentBelowPoverty )
{
	pudtPercentBelowPoverty->dblAllPercent = 0.0;
	pudtPercentBelowPoverty->dblOhioPercent = 0.0;
	pudtPercentBelowPoverty->dblHamiltonPercent = 0.0;
	pudtPercentBelowPoverty->dblButlerPercent = 0.0;
	pudtPercentBelowPoverty->dblKentuckyPercent = 0.0;
	pudtPercentBelowPoverty->dblBoonePercent = 0.0;
	pudtPercentBelowPoverty->dblKentonPercent = 0.0;
	pudtPercentBelowPoverty->dblCaucasianPercent = 0.0;
	pudtPercentBelowPoverty->dblAfricanAmericanPercent = 0.0;
	pudtPercentBelowPoverty->dblHispanicPercent = 0.0;
	pudtPercentBelowPoverty->dblAsianPercent = 0.0;
	pudtPercentBelowPoverty->dblOtherPercent = 0.0;
}



// --------------------------------------------------------------------------------
// Name: PopulateAddressList
// Abstract: Populates address list with data from file
// --------------------------------------------------------------------------------
void PopulateSurveyDataList ( udtSurveyDataType audtSurveyDataList[ ], int* pintRecordCount )
{
	// Declare a file pointer
	FILE* pfilInput = 0;
	int intResultFlag = 0;
	char strBuffer[ 100 ]= ""; // 50 is not enough for the first line

	// Try to open the file for reading (notice you have to double up the backslashes)
	intResultFlag = OpenInputFile( strFILE_PATH, &pfilInput );

	// Was the file opened?
	if( intResultFlag == true )
	{
		// Yes, read in records until end of file( EOF )
		while( feof( pfilInput ) == false )
		{			
			// get line by reading one char at a time
			ReadNextLineFromFile( strBuffer, pfilInput );

			// add address to array
			AddSurveyToArray( strBuffer, &audtSurveyDataList[ *pintRecordCount ] );

			// increment our index
			*pintRecordCount += 1;

			// reset the buffer
			StringCopy( strBuffer, "" );
		}
		// Clean up
		fclose( pfilInput );
	}
}



// --------------------------------------------------------------------------------
// Name: OpenInputFile
// Abstract: Open the file for reading.  Return true if successful.
// --------------------------------------------------------------------------------
int OpenInputFile( char strFileName[ ], FILE** ppfilInput )
{

	int intResultFlag = 0;

	// Open the file for reading
	*ppfilInput = fopen( strFileName, "rb" );

	// Success?
	if( *ppfilInput != 0 )
	{
		// Yes
		intResultFlag = 1;
	}
	else
	{
		// No
		printf( "Error opening %s for reading!!!\n", strFileName );
	}
	return intResultFlag;
}



// --------------------------------------------------------------------------------
// Name: ReadNextLineFromFile
// Abstract: reads next line from file, char by char
// --------------------------------------------------------------------------------
int ReadNextLineFromFile( char strBuffer[ ], FILE* pfilInput )
{
	char strLetter[ 2 ]; // did this to pass it to the append subroutine without errors or changing that sub

	while( (strLetter[ 0 ] = fgetc( pfilInput ) ) != '\r' ) // \r is end of line
	{
		// if eof break, else exception occurs
		if( strLetter[ 0 ] == EOF )
		{
			break;
		}
		// terminate charcter string
		strLetter[ 1 ] = 0;
		StringAppend( strBuffer, strLetter );
	}
}



// --------------------------------------------------------------------------------
// Name: AddAddressToArray
// Abstract: Prints the address list
// --------------------------------------------------------------------------------
void AddSurveyToArray( char strSurveyData[ ], udtSurveyDataType* audtSurveyData )
{
	char strNextField[ 50 ] = "";

	// Append a comma so parsing last field is just like all the others
	StringAppend ( strSurveyData, "," );

	// Date of Survey
	GetNextField( strNextField, strSurveyData, ',' );	
	StringCopy( audtSurveyData->strDateofSurvey, strNextField );

	// County
	GetNextField( strNextField, strSurveyData, ',' );	
	StringCopy( audtSurveyData->strCounty, strNextField );

	// State
	GetNextField( strNextField, strSurveyData, ',' );	
	StringCopy( audtSurveyData->strState, strNextField );

	// Race
	GetNextField( strNextField, strSurveyData, ',' );	
	StringCopy( audtSurveyData->strRace, strNextField );

	// Number in House
	GetNextField( strNextField, strSurveyData, ',' );	
	audtSurveyData->intNumberinHousehold = atoi( strNextField );

	// Income
	GetNextField( strNextField, strSurveyData, ',' );	
	audtSurveyData->dblYearlyIncome = atol( strNextField );
}



// --------------------------------------------------------------------------------
// Name: GetNextField
// Abstract: Gets the next field from the remaining address string
// --------------------------------------------------------------------------------
void GetNextField( char strDestination[ ], char strSource[ ], char chrDelimiter )
{
	int intDelimiterIndex = 0;
	int intStringAddressLength = 0;

	// field ends with delimiter
	// get delimiter index
	intDelimiterIndex = FindLetterIndex( strSource, chrDelimiter );

	// copy substring to next field
	SubString( strDestination, strSource, 0, intDelimiterIndex );

	// get strAddress length
	intStringAddressLength = StringLength( strSource ); 

	// add one to remove the comma as well
	intDelimiterIndex += 1;

	// remove field address 
	SubString( strSource, strSource, intDelimiterIndex, intStringAddressLength );

	// trim white space
	Trim( strDestination );
	Trim( strSource );

}



// --------------------------------------------------------------------------------
// Name: PerformInitialCounts
// Abstract: Counts needed counts for future calculations
// --------------------------------------------------------------------------------
void PerformInitialCounts( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount, udtSurveyCountsType * pudtSurveyCounts )
{
	// count byt county/state
	CalculateTotalSurveyedByCounty( audtSurveyDataList, intRecordCount, pudtSurveyCounts );
	// count by race
	CalculateTotalSurveyedByRace( audtSurveyDataList, intRecordCount, pudtSurveyCounts );
}



// --------------------------------------------------------------------------------
// Name: ShowTotalSurveyedByCounty
// Abstract: Prints total surveyed by county
// --------------------------------------------------------------------------------
void CalculateTotalSurveyedByCounty( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount
	,udtSurveyCountsType* pudtSurveyCounts )
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 0 ] ) == true )
		{
			pudtSurveyCounts->intOhioCount += 1;
			if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrOHIO_COUNTIES[ 0 ] ) == true )
			{
				pudtSurveyCounts->intHamiltonCount += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty,  astrOHIO_COUNTIES[ 1 ] ) == true )
			{
				pudtSurveyCounts->intButlerCount += 1;
			}
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 1 ] ) == true )
		{
			pudtSurveyCounts->intKentuckyCount += 1;
			if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 0 ] ) == true )
			{
				pudtSurveyCounts->intBooneCount += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 1 ] ) == true )
			{
				pudtSurveyCounts->intKentonCount += 1;
			}
		}
	}
}



// --------------------------------------------------------------------------------
// Name: ShowTotalSurveyedByCounty
// Abstract: Prints total surveyed by county
// --------------------------------------------------------------------------------
void CalculateTotalSurveyedByRace( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount
	,udtSurveyCountsType* pudtSurveyCounts)
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 0 ] ) == true )
		{
			pudtSurveyCounts->intCaucasianCount += 1;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 1 ] ) == true )
		{
			pudtSurveyCounts->intAfricanAmericanCount += 1;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 2 ] ) == true )
		{
			pudtSurveyCounts->intHispanicCount += 1;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 3 ] ) == true )
		{
			pudtSurveyCounts->intAsianCount += 1;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 4 ] ) == true )
		{
			pudtSurveyCounts->intOtherCount += 1;
		}
	}
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

	fseek( stdin, 0, SEEK_END ); // clear input stream

	// display menu
	printf( "---------------------------\n" );
	printf( "|Select from these choices:\n" );
	printf( "---------------------------\n" );
	printf( "A) Total Households Surveyed.\n" );
	printf( "B) Total Households Surveyed per County.\n" );
	printf( "C) Total Households Surveyed per Race.\n" );
	printf( "D) Average Household Income.\n" );
	printf( "E) Average Household Income by county and state.\n" );
	printf( "F) Average Household Income by race.\n" );
	printf( "G) Percentage below Poverty.\n" );
	printf( "H) Percentage below Poverty by county and state.\n" );
	printf( "I) Percentage below Poverty by race.\n" );
	printf( "Q) Exit.\n" );
	printf( "\n" );

	// scan choice
	scanf("%c", &chrUserChoice );

	// validate, recurse back if invalid
	if( ValidateMenuChoice( pcharUserChoice ) == false ) 
	{
		printf( "Invalid input\n" );
		printf( "\n" );
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
	if ( *pcharUserChoice >= 'A' && *pcharUserChoice <= 'I' )
	{
		blnValidChoice = true;
	}
	if ( *pcharUserChoice == 'Q' )
	{
		blnValidChoice = true;
	}
	

	return blnValidChoice;
}



// --------------------------------------------------------------------------------
// Name: CalculateAverageIncome
// Abstract: Calculates average income
// --------------------------------------------------------------------------------
void CalculateAverageIncomes( int intRecordCount, udtSurveyDataType audtSurveyDataList[ ], udtIncomeAveragesType* pudtIncomeAverages, udtSurveyCountsType udtSurveyCounts )
{
	// declare variables
	double dblTotalIncome = 0.0;
	double dblOhioTotal = 0.0;
	double dblHamiltonTotal = 0.0;
	double dblButlerTotal = 0.0;
	double dblKentuckyTotal = 0.0;
	double dblBooneTotal = 0.0;
	double dblKentonTotal = 0.0;
	double dblCaucasianTotal = 0.0;
	double dblAfricanAmericanTotal = 0.0;
	double dblHispanicTotal = 0.0;
	double dblAsianTotal = 0.0;
	double dblOtherTotal = 0.0;

	// get total
	dblTotalIncome = GetTotalIncome( audtSurveyDataList, intRecordCount );
	pudtIncomeAverages->dblAllAverage = dblTotalIncome / intRecordCount;
	// get county and states totals
	GetCountyTotals( audtSurveyDataList, &dblOhioTotal, &dblHamiltonTotal, &dblButlerTotal, &dblKentuckyTotal, &dblBooneTotal, &dblKentonTotal, intRecordCount );
	// get race totals
	GetRaceTotals( audtSurveyDataList, &dblCaucasianTotal, &dblAfricanAmericanTotal, &dblHispanicTotal, &dblAsianTotal, &dblOtherTotal, intRecordCount );

	// calculate and store averages
	pudtIncomeAverages->dblAllAverage = dblTotalIncome / intRecordCount;
	pudtIncomeAverages->dblOhioAverage = dblOhioTotal / udtSurveyCounts.intOhioCount;
	pudtIncomeAverages->dblHamiltonAverage = dblHamiltonTotal / udtSurveyCounts.intHamiltonCount;
	pudtIncomeAverages->dblButlerAverage = dblButlerTotal / udtSurveyCounts.intButlerCount;
	pudtIncomeAverages->dblKentuckyAverage = dblKentuckyTotal / udtSurveyCounts.intKentuckyCount;
	pudtIncomeAverages->dblBooneAverage = dblBooneTotal / udtSurveyCounts.intBooneCount;
	pudtIncomeAverages->dblKentonAverage = dblKentonTotal / udtSurveyCounts.intKentonCount;
	pudtIncomeAverages->dblCaucasianAverage = dblCaucasianTotal / udtSurveyCounts.intCaucasianCount;
	pudtIncomeAverages->dblAfricanAmericanAverage = dblAfricanAmericanTotal / udtSurveyCounts.intAfricanAmericanCount;
	pudtIncomeAverages->dblHispanicAverage = dblHispanicTotal / udtSurveyCounts.intHispanicCount;
	pudtIncomeAverages->dblAsianAverage = dblAsianTotal / udtSurveyCounts.intAsianCount;
	pudtIncomeAverages->dblOtherAverage = dblOtherTotal / udtSurveyCounts.intOtherCount;
}



// --------------------------------------------------------------------------------
// Name: GetTotalIncome
// Abstract: Adds all income together
// --------------------------------------------------------------------------------
double GetTotalIncome( udtSurveyDataType audtSurveyDataList[ ], int intRecordCount )
{
	// declare variables
	double dblTotalIncome = 0.0;
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		dblTotalIncome += audtSurveyDataList[ intIndex ].dblYearlyIncome;
	}


	return dblTotalIncome;
}



// --------------------------------------------------------------------------------
// Name: GetCountyTotals
// Abstract: Adds income together by county and state
// --------------------------------------------------------------------------------
void GetCountyTotals( udtSurveyDataType audtSurveyDataList[ ], double * pdblOhioTotal, double * pdblHamiltonTotal, 
					double * pdblButlerTotal, double * pdblKentuckyTotal, double * pdblBooneTotal, double * pdblKentonTotal, int intRecordCount )
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 0 ] ) == true )
		{
			*pdblOhioTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrOHIO_COUNTIES[ 0 ] ) == true )
			{
				*pdblHamiltonTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty,  astrOHIO_COUNTIES[ 1 ] ) == true )
			{
				*pdblButlerTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			}
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 1 ] ) == true )
		{
			*pdblKentuckyTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 0 ] ) == true )
			{
				*pdblBooneTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 1 ] ) == true )
			{
				*pdblKentonTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
			}
		}
	}
}



// --------------------------------------------------------------------------------
// Name: GetRaceTotals
// Abstract: Adds income together by race
// --------------------------------------------------------------------------------
void GetRaceTotals( udtSurveyDataType audtSurveyDataList[], double * pdblCaucasianTotal, double * pdblAfricanAmericanTotal, 
					double * pdblHispanicTotal, double * pdblAsianTotal, double * pdblOtherTotal, int intRecordCount )
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 0 ] ) == true )
		{
			*pdblCaucasianTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 1 ] ) == true )
		{
			*pdblAfricanAmericanTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 2 ] ) == true )
		{
			*pdblHispanicTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 3 ] ) == true )
		{
			*pdblAsianTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
		}
		else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 4 ] ) == true )
		{
			*pdblOtherTotal += audtSurveyDataList[ intIndex ].dblYearlyIncome;
		}
	}
}



// --------------------------------------------------------------------------------
// Name: CalculatePercentsBelowPoverty
// Abstract: Calculates the percentages below poverty for all metrics
// --------------------------------------------------------------------------------
void CalculatePercentsBelowPoverty( int intRecordCount, udtSurveyDataType audtSurveyDataList[ ], udtPercentBelowPovertyType * pudtPercentBelowPoverty, udtSurveyCountsType udtSurveyCounts )
{
	// declare variables
	int intTotalBelow = 0;
	int intOhioBelow = 0;
	int intHamiltonBelow = 0;
	int intButlerBelow = 0;
	int intKentuckyBelow = 0;
	int intBooneBelow = 0;
	int intKentonBelow = 0;
	int intCaucasianBelow = 0;
	int intAfricanAmericanBelow = 0;
	int intHispanicBelow = 0;
	int intAsianBelow = 0;
	int intOtherBelow = 0;

	// get county and states totals
	GetCountyTotalBelow( audtSurveyDataList, &intTotalBelow, &intOhioBelow, &intHamiltonBelow, &intButlerBelow, &intKentuckyBelow, &intBooneBelow, &intKentonBelow, intRecordCount );
	// get race totals
	GetRaceTotalBelow( audtSurveyDataList, &intCaucasianBelow, &intAfricanAmericanBelow, &intHispanicBelow, &intAsianBelow, &intOtherBelow, intRecordCount );

	// calculate averages
	pudtPercentBelowPoverty->dblAllPercent = (double) intTotalBelow / intRecordCount;
	pudtPercentBelowPoverty->dblOhioPercent = (double) intOhioBelow / udtSurveyCounts.intOhioCount;
	pudtPercentBelowPoverty->dblHamiltonPercent = (double) intHamiltonBelow / udtSurveyCounts.intHamiltonCount;
	pudtPercentBelowPoverty->dblButlerPercent = (double) intButlerBelow / udtSurveyCounts.intButlerCount;
	pudtPercentBelowPoverty->dblKentuckyPercent = (double) intKentuckyBelow / udtSurveyCounts.intKentuckyCount;
	pudtPercentBelowPoverty->dblBoonePercent = (double) intBooneBelow / udtSurveyCounts.intBooneCount;
	pudtPercentBelowPoverty->dblKentonPercent = (double) intKentonBelow / udtSurveyCounts.intKentonCount;
	pudtPercentBelowPoverty->dblCaucasianPercent = (double) intCaucasianBelow / udtSurveyCounts.intCaucasianCount;
	pudtPercentBelowPoverty->dblAfricanAmericanPercent = (double) intAfricanAmericanBelow / udtSurveyCounts.intAfricanAmericanCount;
	pudtPercentBelowPoverty->dblHispanicPercent = (double) intHispanicBelow / udtSurveyCounts.intHispanicCount;
	pudtPercentBelowPoverty->dblAsianPercent = (double) intAsianBelow / udtSurveyCounts.intAsianCount;
	pudtPercentBelowPoverty->dblOtherPercent = (double) intOtherBelow / udtSurveyCounts.intOtherCount;
}



// --------------------------------------------------------------------------------
// Name: GetCountyTotalBelow
// Abstract: gets the number below poverty for counties and states, and the total number below 
// --------------------------------------------------------------------------------
void GetCountyTotalBelow( udtSurveyDataType audtSurveyDataList[ ], int * pintTotalBelow, int * pintOhioBelow, 
						int * pintHamiltonBelow, int * pintButlerBelow, int * pintKentuckyBelow, int * pintBooneBelow, int * pintKentonBelow, int intRecordCount )
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( IsBelowPoverty( audtSurveyDataList[ intIndex ].dblYearlyIncome, audtSurveyDataList[ intIndex ].intNumberinHousehold ) == true )
		{
			*pintTotalBelow	 += 1;
			if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 0 ] ) == true )
			{
				*pintOhioBelow += 1;
				if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrOHIO_COUNTIES[ 0 ] ) == true )
				{
					*pintHamiltonBelow += 1;
				}
				else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty,  astrOHIO_COUNTIES[ 1 ] ) == true )
				{
					*pintButlerBelow += 1;
				}
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strState, astrSTATES[ 1 ] ) == true )
			{
				*pintKentuckyBelow += 1;
				if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 0 ] ) == true )
				{
					*pintBooneBelow += 1;
				}
				else if( StringCompare( audtSurveyDataList[ intIndex ].strCounty, astrKENTUCKY_COUNTIES[ 1 ] ) == true )
				{
					*pintKentonBelow += 1;
				}
			}
		}
	}
}



// --------------------------------------------------------------------------------
// Name: IsBelowPoverty
// Abstract: Determines if an income level is below poverty
// --------------------------------------------------------------------------------
boolean IsBelowPoverty( double dblYearlyIncome, int intNumberinHousehold )
{
	// declare variables
	boolean blnBelowPoverty = false;
	int intIndexOfPovertyLine = intNumberinHousehold - 1;

	// boundary check
	if( intIndexOfPovertyLine < 0 )
	{
		intIndexOfPovertyLine = 0;
	}
	if( intIndexOfPovertyLine > 4 )
	{
		intIndexOfPovertyLine = 4;
	}

	// test if below the pvoerty line
	if( dblYearlyIncome < adblBASIS_OF_POVERTY[ intIndexOfPovertyLine ] )
	{
		// super poor
		blnBelowPoverty = true;
	}

	return blnBelowPoverty;
}



// --------------------------------------------------------------------------------
// Name: GetRaceTotalBelow
// Abstract: Gets the number below poverty by race
// --------------------------------------------------------------------------------
void GetRaceTotalBelow( udtSurveyDataType audtSurveyDataList[ ], int * pintCaucasianBelow, int * pintAfricanAmericanBelow, int * pintHispanicBelow, int * pintAsianBelow, int * pintOtherBelow, int intRecordCount )
{
	// declare variables
	int intIndex = 0;

	// loop through array and count
	for( intIndex = 0; intIndex < intRecordCount; intIndex += 1 )
	{
		if( IsBelowPoverty( audtSurveyDataList[ intIndex ].dblYearlyIncome, audtSurveyDataList[ intIndex ].intNumberinHousehold ) == true )
		{
			if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 0 ] ) == true )
			{
				*pintCaucasianBelow += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 1 ] ) == true )
			{
				*pintAfricanAmericanBelow += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 2 ] ) == true )
			{
				*pintHispanicBelow += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 3 ] ) == true )
			{
				*pintAsianBelow += 1;
			}
			else if( StringCompare( audtSurveyDataList[ intIndex ].strRace, astrRACES[ 4 ] ) == true )
			{
				*pintOtherBelow += 1;
			}
		}
	}
}



// --------------------------------------------------------------------------------
// Name: ShowTotalSurveyed
// Abstract: Prints total surveyed
// --------------------------------------------------------------------------------
void ShowTotalSurveyed( int intRecordCount )
{
	// print record count
	printf( "\nTotal surveyed = %d\n", intRecordCount );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayTotalSurveyedByCounty
// Abstract: Displays total surveyed by county
// --------------------------------------------------------------------------------
void DisplayTotalSurveyedByCounty( udtSurveyCountsType udtSurveyCounts )
{
	printf( "Total Surveyed By County\n");
	printf( "------------------------\n");
	printf( "Ohio:      \t%d\n", udtSurveyCounts.intOhioCount );
	printf( "  Hamilton:\t%d\n", udtSurveyCounts.intHamiltonCount );
	printf( "  Butler:\t%d\n", udtSurveyCounts.intButlerCount );
	printf( "Kentucky:  \t%d\n", udtSurveyCounts.intKentuckyCount );
	printf( "  Boone:\t%d\n", udtSurveyCounts.intBooneCount );
	printf( "  Kenton:\t%d\n", udtSurveyCounts.intKentonCount );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayTotalSurveyedByRace
// Abstract: Displays total surveyed by race
// --------------------------------------------------------------------------------
void DisplayTotalSurveyedByRace( udtSurveyCountsType udtSurveyCounts )
{
	printf( "Total Surveyed By Race\n");
	printf( "------------------------\n");
	printf( "Caucasian:%20d\n", udtSurveyCounts.intCaucasianCount );
	printf( "African American:%13d\n", udtSurveyCounts.intAfricanAmericanCount );
	printf( "Hispanic:%21d\n", udtSurveyCounts.intHispanicCount );
	printf( "Asian:%24d\n", udtSurveyCounts.intAsianCount );
	printf( "Other:%24d\n", udtSurveyCounts.intOtherCount );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayTotalSurveyedByRace
// Abstract: Displays total surveyed by race
// --------------------------------------------------------------------------------
void DisplayAverageIncome( udtIncomeAveragesType udtIncomeAverages )
{
	// print record count
	printf( "\nAverage household income = %.2lf $\n", udtIncomeAverages.dblAllAverage );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayAverageIncomeByCounty
// Abstract: Displays average income by county
// --------------------------------------------------------------------------------
void DisplayAverageIncomeByCounty( udtIncomeAveragesType udtIncomeAverages )
{
	printf( "Income Average By County\n");
	printf( "------------------------\n");
	printf( "Ohio:      \t%.2lf $\n", udtIncomeAverages.dblOhioAverage );
	printf( "  Hamilton:\t%.2lf $\n", udtIncomeAverages.dblHamiltonAverage );
	printf( "  Butler:\t%.2lf $\n", udtIncomeAverages.dblButlerAverage );
	printf( "Kentucky:  \t%.2lf $\n", udtIncomeAverages.dblKentuckyAverage );
	printf( "  Boone:\t%.2lf $\n", udtIncomeAverages.dblBooneAverage );
	printf( "  Kenton:\t%.2lf $\n", udtIncomeAverages.dblKentonAverage );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayAverageIncomeByRace
// Abstract: Displays average income by race
// --------------------------------------------------------------------------------
void DisplayAverageIncomeByRace( udtIncomeAveragesType udtIncomeAverages )
{
	printf( "Income Averages By Race\n" );
	printf( "------------------------\n");
	printf( "Caucasian:%20.2lf $\n", udtIncomeAverages.dblCaucasianAverage );
	printf( "African American:%13.2lf $\n", udtIncomeAverages.dblAfricanAmericanAverage );
	printf( "Hispanic:%21.2lf $\n", udtIncomeAverages.dblHispanicAverage );
	printf( "Asian:%24.2lf $\n", udtIncomeAverages.dblAsianAverage );
	printf( "Other:%24.2lf $\n", udtIncomeAverages.dblOtherAverage );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayBelowPoverty
// Abstract: Displays the percent below poverty
// --------------------------------------------------------------------------------
void DisplayBelowPoverty( udtPercentBelowPovertyType udtPercentBelowPoverty )
{
	// print record count
	printf( "\nPercent Below Poverty = %.1lf %%\n", udtPercentBelowPoverty.dblAllPercent * 100 );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayBelowPovertyByCounty
// Abstract: Displays the percent below poverty by county and state
// --------------------------------------------------------------------------------
void DisplayBelowPovertyByCounty( udtPercentBelowPovertyType udtPercentBelowPoverty )
{
	printf( "Percent Below Poverty By County\n");
	printf( "------------------------\n");
	printf( "Ohio:      \t%.1lf %%\n", udtPercentBelowPoverty.dblOhioPercent * 100 );
	printf( "  Hamilton:\t%.1lf %%\n", udtPercentBelowPoverty.dblHamiltonPercent * 100 );
	printf( "  Butler:\t%.1lf %%\n", udtPercentBelowPoverty.dblButlerPercent * 100 );
	printf( "Kentucky:  \t%.1lf %%\n", udtPercentBelowPoverty.dblKentuckyPercent * 100 );
	printf( "  Boone:\t%.1lf %%\n", udtPercentBelowPoverty.dblBoonePercent * 100 );
	printf( "  Kenton:\t%.1lf %%\n", udtPercentBelowPoverty.dblKentonPercent * 100 );
	printf( "\n" );
}



// --------------------------------------------------------------------------------
// Name: DisplayBelowPovertyByRace
// Abstract: Displays the percent below poverty by race
// --------------------------------------------------------------------------------
void DisplayBelowPovertyByRace( udtPercentBelowPovertyType udtPercentBelowPoverty )
{
	printf( "Percent Below Poverty By Race\n");
	printf( "------------------------\n");
	printf( "Caucasian:%20.1lf %%\n", udtPercentBelowPoverty.dblCaucasianPercent * 100 );
	printf( "African American:%13.1lf %%\n", udtPercentBelowPoverty.dblAfricanAmericanPercent * 100 );
	printf( "Hispanic:%21.1lf %%\n", udtPercentBelowPoverty.dblHispanicPercent * 100 );
	printf( "Asian:%24.1lf %%\n", udtPercentBelowPoverty.dblAsianPercent * 100 );
	printf( "Other:%24.1lf %%\n", udtPercentBelowPoverty.dblOtherPercent * 100 );
	printf( "\n" );
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



// --------------------------------------------------------------------------------
// Name: FindLetterIndex
// Abstract: Find first occurence of letter (case-sensitive) from left to right.
// --------------------------------------------------------------------------------
int FindLetterIndex( char strSource[ ],  char chrLetterToFind )
{
	int intLetterToFindIndex = -1;
	int intIndex = 0;

	// Check character
	while( strSource[ intIndex ] != 0 )
	{
		// Is this the character for which we are looking
		if( strSource[ intIndex ] == chrLetterToFind )
		{
			// Yes, save the index
			intLetterToFindIndex = intIndex;

			// Stop searching
			break;
		}
		intIndex += 1;
	}

	return intLetterToFindIndex;
}



// --------------------------------------------------------------------------------
// Name: Trim
// Abstract: Remove leading and trailing whitespace (space, tab or newline)
// --------------------------------------------------------------------------------
void Trim( char strSource[ ] )
{

	int intIndex = 0;
	int intFirstNonWhitespaceIndex = -1;
	int intLastNonWhitespaceIndex = 0;
	int intSourceIndex = 0;
	int intDestinationIndex = 0;

	// Default first non-whitespace character index to end of string in case string is all whitespace
	// Bug fix.  Not in video.
	intFirstNonWhitespaceIndex = StringLength( strSource );

	// Find first non-whitespace character
	while( strSource[ intIndex ] != 0 )
	{
		// Non-whitespace character?
		if( IsWhiteSpace( strSource[ intIndex ] ) == false )
		{
			// Yes, save the index
			intFirstNonWhitespaceIndex = intIndex;

			// Stop searching!
			break;
		}

		// Next character
		intIndex += 1;
	}

	// Find the last non-whitespace character
	while( strSource[ intIndex ] != 0 )
	{
		// Non-whitespace character?
		if( IsWhiteSpace( strSource[ intIndex ] ) == false )
		{
			// Yes, save the index
			intLastNonWhitespaceIndex = intIndex;
		}

		// Next character
		intIndex += 1;
	}

	// Any non-whitepsace characters?
	if( intFirstNonWhitespaceIndex >= 0 )
	{
		// Yes, copy everything in between
		for( intSourceIndex = intFirstNonWhitespaceIndex; intSourceIndex <= intLastNonWhitespaceIndex; intSourceIndex += 1 )
		{
			// Copy next character
			strSource[ intDestinationIndex ] = strSource[ intSourceIndex ];

			intDestinationIndex += 1;
		}
	}

	// Terminate 
	strSource[ intDestinationIndex ] = 0;
}



// --------------------------------------------------------------------------------
// Name: IsWhiteSpace
// Abstract: Return true if letter is a space, tab, newline or carriage return
// --------------------------------------------------------------------------------
boolean IsWhiteSpace( char chrLetterToCheck )
{
	boolean blnIsWhiteSpace = false;

	// Space
	if( chrLetterToCheck == ' ' ) blnIsWhiteSpace = true;

	// Tab
	if( chrLetterToCheck == '\t' ) blnIsWhiteSpace = true;

	// Carriarge return
	if( chrLetterToCheck == '\r' ) blnIsWhiteSpace = true;

	// Line feed
	if( chrLetterToCheck == '\n' ) blnIsWhiteSpace = true;

	return blnIsWhiteSpace;
}



// --------------------------------------------------------------------------------
// Name: CountWords
// Abstract: Count the words in a string
// --------------------------------------------------------------------------------
int CountWords( char strSource[ ] )
{
	int intWordCount = 0;
	int intIndex = 0;
	char chrCurrentLetter = 0;
	char chrPreviousLetter = ' ';

	// Copy each character
	while( strSource[ intIndex ] != 0 )
	{
		chrCurrentLetter = strSource[ intIndex ];

		// Word boundary (space followed by non-space)?
		if( chrPreviousLetter == ' ' && chrCurrentLetter != ' ' )
		{
			// Yes, count it
			intWordCount += 1;
		}

		// Save current character
		chrPreviousLetter = chrCurrentLetter;

		// Next
		intIndex += 1;
	}

	return intWordCount;
}



// ------------------------------------------------------------------------------------------
// Name: SubString
// Abstract: Copies substring of source to desination
// ------------------------------------------------------------------------------------------
void SubString ( char strDestination[ ], char strSource[ ], int intStartIndex, int intLength )
{
	// declare variables
	int intIndex = 0;
	int intSourceLength = 0; // for boundary checking

							 // get source length
	intSourceLength = StringLength( strSource );

	// if start index is less than zero, set to zero
	if( intStartIndex < 0 ) 
	{
		intStartIndex = 0;
	}

	// if intLength is greater than source string minus start index, 
	// set to source string length minus start index (to prevent going out of index range)
	if( intLength > intSourceLength - intStartIndex )
	{
		intLength = intSourceLength - intStartIndex;
	}

	// loop over source substring and insert into destination
	for ( intIndex = 0; intIndex < intLength; intIndex += 1 )
	{
		strDestination[ intIndex ] = strSource[ intStartIndex ];

		// increment start index
		intStartIndex += 1;
	}

	// Terminate
	strDestination[ intIndex ] = 0;
}



// --------------------------------------------------------------------------------
// Name: StringCompare
// Abstract: Compares strings, returns true is equal
// --------------------------------------------------------------------------------
boolean StringCompare( char strFirstString[ ], char strSecondString[ ] )
{
	// declare variables
	int intIndex = 0;
	boolean blnStringsEqual = true;

	int intLastCharacter = StringLength( strFirstString );

	// check string length first
	if( StringLength( strFirstString ) == StringLength( strSecondString ) )
	{
		// compare each character value, if lengths are the same
		for( intIndex = 0; intIndex < intLastCharacter; intIndex += 1)
		{
			if( strFirstString[ intIndex ] != strSecondString[ intIndex ] )
			{
				blnStringsEqual = false;
				// not equal, abort
				break;
			}
		}
	}
	else
	{
		blnStringsEqual = false;
	}

	return blnStringsEqual;
}

