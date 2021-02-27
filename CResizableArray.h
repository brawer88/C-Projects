// --------------------------------------------------------------------------------
// Name: CResizableArray
// Abstract: This is a class to create and manage a dynamic array, made as a template
//		     and with an overloaded [] operator
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Pre-compiler Directives
// --------------------------------------------------------------------------------
#pragma once		// Include this file only once even if referenced multiple times

// --------------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------------
#include <stdlib.h>
#include <iostream>

using namespace std;

template <class Value>
class CResizableArray
{
	// --------------------------------------------------------------------------------
	// Properties
	// --------------------------------------------------------------------------------
public:			// Never make public properties.  
				// Make protected or private with public get/set methods

protected:

private:
	long m_lngArraySize;
	Value* m_pavalValues;

	// --------------------------------------------------------------------------------
	// Methods
	// --------------------------------------------------------------------------------
public:
	// default construcotr
	CResizableArray( );
	// parameterized constructors
	CResizableArray( long lngNewSize );
	CResizableArray( long lngNewSize, Value valDefaultValue );

	// copy constructor 
	CResizableArray( const CResizableArray <Value> &clsSource );

	// assignment operator overload
	void operator = ( const CResizableArray <Value> &clsSource );

	// destructor
	~CResizableArray( );


	void SetSize( long lngNewSize ); // Zero value are allowed but not negative values.
	void SetSize( long lngNewSize, Value valDefaultValue );
	Value GetSize( ) const;

	void SetValueAt( Value valValue, long lngIndex );
	Value GetValueAt( long lngIndex ) const;

	// overload [] operator
	Value& operator [] ( long lngIndex );
	const Value& operator [] ( long lngIndex ) const;

	// overload the += operator
	void operator+= ( const CResizableArray<Value> &clsOriginalToAppend );
	// overload the + operator
	CResizableArray<Value> operator + ( const CResizableArray<Value> &clsRight ) const;

	void AddValueToFront( Value valValueToAdd );
	void AddValueToEnd( Value valValueToAdd );
	void InsertValueAt( Value valValueToAdd, long lngIndex );

	void RemoveAt( long lngIndex );

	void PrintArray( ) const;
	void PrintArray( const char* pstrCaption ) const;



protected:
	void Initialize( long lngInitialSize, Value valDefaultValue );	// Set array size and array pointer to 0
	void MakeArrayCopy( Value** pavalCopy, long lngArraySize ) const;
	void CleanUp( );
	void DeepCopy( CResizableArray <Value> &clsSource );

private:

};



// --------------------------------------------------------------------------------
// Name: Constructor
// Abstract: Default constructor
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value>::CResizableArray( )
{
	Initialize( 0, 0 );
}



// --------------------------------------------------------------------------------
// Name: Constructor
// Abstract: Parameterized constructor
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value>::CResizableArray( long lngNewSize )
{
	Initialize( lngNewSize, 0 );
}



// --------------------------------------------------------------------------------
// Name: Constructor
// Abstract: Parameterized constructor
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value>::CResizableArray( long lngNewSize, Value valDefaultValue )
{
	Initialize( lngNewSize, valDefaultValue );
}



// --------------------------------------------------------------------------------
// Name: Copy Constructor
// Abstract: Creates a deep copy to be passed around
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value>::CResizableArray( const CResizableArray <Value> &clsSource )
{
	// do a deep copy with explicit cast
	Initialize( 0, 0 );

	*this = clsSource;
}



// --------------------------------------------------------------------------------
// Name: Assignment operator overload
// Abstract: overloads the assignment operator to follow the rule of 3
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::operator=( const CResizableArray<Value> &clsSource )
{

	// check for self assignment
	if (this != &clsSource)
	{
		// clean up
		CleanUp( );

		// do a deep copy with explicit cast
		DeepCopy( ( CResizableArray<Value>& ) clsSource );
	}
}



// --------------------------------------------------------------------------------
// Name: Destructor
// Abstract: Calls the cleanup method
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value>::~CResizableArray( )
{
	CleanUp( );
}



// --------------------------------------------------------------------------------
// Name: Initialize
// Abstract: Initiliazes array, setting size and array pointer to 0
// --------------------------------------------------------------------------------
template <class Value>
inline void CResizableArray<Value>::Initialize( long lngInitialSize, Value valDefaultValue )
{
	m_lngArraySize = 0;
	m_pavalValues = 0;

	// call set method
	SetSize( lngInitialSize, valDefaultValue );
}



// --------------------------------------------------------------------------------
// Name: SetSize
// Abstract: Sets the size of the array, preserving any existing values
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::SetSize( long lngNewSize )
{
	// set default value to 0
	SetSize( lngNewSize, 0 );
}



// --------------------------------------------------------------------------------
// Name: SetSize
// Abstract: Sets the size of the array, preserving any existing values
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::SetSize( long lngNewSize, Value valDefaultValue )
{
	// declare variables
	Value* pvalTempValues = 0;
	long lngIndex = 0;

	if (lngNewSize < 0) lngNewSize = 0;
	if (lngNewSize > 100000) lngNewSize = 100000;


	// make array copy
	MakeArrayCopy( &pvalTempValues, lngNewSize );
	// copy old array into temp array
	for (lngIndex = 0; lngIndex < lngNewSize; lngIndex += 1)
	{
		if (lngIndex < m_lngArraySize)
		{
			pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex ];
		}
		else
		{
			pvalTempValues[ lngIndex ] = valDefaultValue; // sets to default value if nothing to copy
		}
	}
	// delete original array 
	delete[] m_pavalValues;
	m_pavalValues = 0;
	// have class array point to this temp array value
	m_pavalValues = pvalTempValues;
	// set new size
	m_lngArraySize = lngNewSize;
}



// --------------------------------------------------------------------------------
// Name: GetSize
// Abstract: Get the array size
// --------------------------------------------------------------------------------
template<class Value>
inline Value CResizableArray<Value>::GetSize( ) const
{
	return m_lngArraySize;
}



// --------------------------------------------------------------------------------
// Name: SetValueAt
// Abstract: Set the value at specified index
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::SetValueAt( Value valValue, long lngIndex )
{
	// is the array size above 0?
	if (m_lngArraySize > 0)
	{
		// boundary check
		if (lngIndex < 0)
		{
			lngIndex = 0;
		}
		else if (lngIndex > m_lngArraySize)
		{
			lngIndex = m_lngArraySize - 1;
		}

		// set value
		m_pavalValues[ lngIndex ] = valValue;
	}
	else
	{
		cout << "Array size has not been set." << endl;
		throw out_of_range( "Invalid position!" );
		exit( 1 );
	}

}



// --------------------------------------------------------------------------------
// Name: GetValueAt
// Abstract: Get the value at specified index
// --------------------------------------------------------------------------------
template<class Value>
inline Value CResizableArray<Value>::GetValueAt( long lngIndex ) const
{
	// declare variable
	Value valReturnValue = 0;

	// is the array size above 0?
	if (m_lngArraySize > 0)
	{
		// boundary check
		if (lngIndex < 0)
		{
			lngIndex = 0;
		}
		else if (lngIndex > m_lngArraySize)
		{
			lngIndex = m_lngArraySize - 1;
		}

		valReturnValue = m_pavalValues[ lngIndex ];
	}
	else
	{
		cout << "Array size has not been set." << endl;
		throw out_of_range( "Invalid position!" );
		exit( 1 );
	}
	return valReturnValue;
}



// --------------------------------------------------------------------------------
// Name: operator[] 
// Abstract: Overloads the [] operator to allow accessing and assigning the index
//			 through the opertor
// --------------------------------------------------------------------------------
template<class Value>
inline Value& CResizableArray<Value>::operator[]( long lngIndex )
{

	if (lngIndex >= m_lngArraySize || lngIndex < 0)
	{
		// do not allow to resize through the [] operator
		cout << "Index out of bounds" << endl;
		throw out_of_range( "Invalid position!" );
		exit( 1 );
	}

	return m_pavalValues[ lngIndex ];

}



// --------------------------------------------------------------------------------
// Name: operator[] 
// Abstract: Overloads the [] operator to allow accessing and assigning the index
//			 through the opertor
// --------------------------------------------------------------------------------
template<class Value>
inline const Value & CResizableArray<Value>::operator[]( long lngIndex ) const
{
	if (lngIndex >= m_lngArraySize || lngIndex < 0)
	{
		// do not allow to resize through the [] operator
		cout << "Index out of bounds" << endl;
		throw out_of_range( "Invalid position!" );
		exit( 1 );
	}

	return m_pavalValues[ lngIndex ];
}



// --------------------------------------------------------------------------------
// Name: operator+=
// Abstract: Overloads the += operator to allow appending to an array another array
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::operator+=( const CResizableArray<Value>& clsOriginalToAppend )
{
	long lngNewSize = 0;
	Value* pavalNewValues = 0;
	long lngSourceIndex = 0;
	long lngDestinationIndex = 0;

	// get new size of array
 	lngNewSize = clsOriginalToAppend.GetSize( ) + GetSize( );
	// set new size of array
	pavalNewValues = new Value[ lngNewSize ];
	// copy first half
	for ( lngSourceIndex = 0; lngSourceIndex < GetSize( ); lngSourceIndex += 1 )
	{
		pavalNewValues[ lngDestinationIndex ] = (*this)[ lngSourceIndex ];
		lngDestinationIndex += 1;
	}
	// copy second half
	for ( lngSourceIndex = 0; lngSourceIndex < clsOriginalToAppend.GetSize( ); lngSourceIndex += 1 )
	{
		pavalNewValues[ lngDestinationIndex ] = clsOriginalToAppend[ lngSourceIndex ];
		lngDestinationIndex += 1;
	}

	// delete old memory
	CleanUp( );

	// assign new array
	m_pavalValues = pavalNewValues;
	m_lngArraySize = lngNewSize;
}



// --------------------------------------------------------------------------------
// Name: operator+ 
// Abstract: Overloads the + operator to allow addition of arrays
// --------------------------------------------------------------------------------
template<class Value>
inline CResizableArray<Value> CResizableArray<Value>::operator+( const CResizableArray<Value>& clsRight ) const
{
	// make copy
	CResizableArray<Value> clsArrayAddition;

	clsArrayAddition = *this;

	// add second operand to first
	clsArrayAddition += clsRight;

	return clsArrayAddition;
}



// --------------------------------------------------------------------------------
// Name: AddValueToFront
// Abstract: Adds a value to the front of the array
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::AddValueToFront( Value valValueToAdd )
{
	// declare variables
	Value* pvalTempValues = 0;
	long lngIndex = 0;

	// increase our array size
	m_lngArraySize += 1;

	// make array copy
	MakeArrayCopy( &pvalTempValues, m_lngArraySize );

	// add value to front
	*( pvalTempValues ) = valValueToAdd;

	// copy old array into temp array
	for (lngIndex = 1; lngIndex < m_lngArraySize; lngIndex += 1)
	{
		pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex - 1 ];
	}

	// delete original array
	delete[] m_pavalValues;
	m_pavalValues = 0;

	// have class array point to this temp array value
	m_pavalValues = pvalTempValues;
}



// --------------------------------------------------------------------------------
// Name: AddValueToEnd
// Abstract: Adds a value to the end of the array
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::AddValueToEnd( Value valValueToAdd )
{
	// declare variables
	Value* pvalTempValues = 0;
	long lngIndex = 0;

	// increase our array size
	m_lngArraySize += 1;

	// make array copy
	MakeArrayCopy( &pvalTempValues, m_lngArraySize );

	// copy old array into temp array
	for (lngIndex = 0; lngIndex < m_lngArraySize - 1; lngIndex += 1)
	{
		pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex ];
	}

	// add value to front
	pvalTempValues[ lngIndex ] = valValueToAdd;

	// delete original array
	delete[] m_pavalValues;
	m_pavalValues = 0;

	// have class array point to this temp array value
	m_pavalValues = pvalTempValues;
}



// --------------------------------------------------------------------------------
// Name: InsertValueAt
// Abstract: Inserts a value the specified index of the array
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::InsertValueAt( Value valValueToAdd, long lngInsertAtIndex )
{
	if (m_lngArraySize > 0)
	{
		// delcare variables
		long lngIndex = 0;
		Value* pvalTempValues = 0;
		// change value in pointer
		m_lngArraySize += 1;
		// boundary check
		if (lngInsertAtIndex >= m_lngArraySize) lngInsertAtIndex = m_lngArraySize - 1;
		if (lngInsertAtIndex < 0) lngInsertAtIndex = 0;

		MakeArrayCopy( &pvalTempValues, m_lngArraySize ); // make new array with new array size

		for (lngIndex = 0; lngIndex < lngInsertAtIndex; lngIndex += 1) // copy old array values to new array up to insert index
		{
			pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex ];
		}
		// add value to insert
		pvalTempValues[ lngIndex ] = valValueToAdd;
		// continue copying
		for (lngIndex = lngIndex + 1; lngIndex < m_lngArraySize; lngIndex += 1)
		{
			pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex - 1 ];
		}
		// delete original array
		delete[] m_pavalValues;
		m_pavalValues = 0;

		m_pavalValues = pvalTempValues; // have class array point to this temp array value
	}
	else
	{
		cerr << "Array size has not been set." << endl;
	}
}



// --------------------------------------------------------------------------------
// Name: RemoveAt
// Abstract: Removes an element of the array at specified index
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::RemoveAt( long lngIndexToRemove )
{
	if (m_lngArraySize > 0)
	{
		// delcare variables
		long lngIndex = 0;
		Value* pvalTempValues = 0;
		// change value in pointer
		m_lngArraySize -= 1;

		// boundary check
		if (lngIndexToRemove >= m_lngArraySize) lngIndexToRemove = m_lngArraySize;
		if (lngIndexToRemove < 0) lngIndexToRemove = 0;
		// make new array with new array size
		MakeArrayCopy( &pvalTempValues, m_lngArraySize );

		// copy old array values to new array up to remove index
		for (lngIndex = 0; lngIndex < lngIndexToRemove; lngIndex += 1)
		{
			pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex ];
		}
		// continue copying, skipping remove index value 
		for (lngIndex = lngIndex; lngIndex < m_lngArraySize; lngIndex += 1)
		{
			pvalTempValues[ lngIndex ] = m_pavalValues[ lngIndex + 1 ];
		}
		// delete original array
		delete[] m_pavalValues;
		m_pavalValues = 0;
		// have class array point to this temp array value
		m_pavalValues = pvalTempValues;
	}
	else
	{
		cerr << "Array size has not been set." << endl;
	}
}



// --------------------------------------------------------------------------------
// Name: PrintArray
// Abstract: Prints the array
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::PrintArray( ) const
{
	long lngIndex = 0;

	for (lngIndex = 0; lngIndex < m_lngArraySize; lngIndex += 1)
	{
		cout << "Element " << lngIndex << ": " << m_pavalValues[ lngIndex ] << endl;
	}
}



// --------------------------------------------------------------------------------
// Name: PrintArray
// Abstract: Prints the array with a caption
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::PrintArray( const char * pstrCaption ) const
{
	// display caption
	cout << pstrCaption << endl;
	cout << "---------------------------------" << endl;
	// now print array
	PrintArray( );
}



// --------------------------------------------------------------------------------
// Name: MakeArrayCopy
// Abstract: Makes a new array to be used for copying an old one
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::MakeArrayCopy( Value** pavalCopy, long lngArraySize ) const
{
	// declare variables
	Value* pvalTempValues = 0;
	long lngIndex = 0;

	// allocate memory for temp array
	pvalTempValues = new Value[ lngArraySize ];


	for (lngIndex = 0; lngIndex < lngArraySize; lngIndex += 1)
	{
		pvalTempValues[ lngIndex ] = 0;
	}


	*pavalCopy = pvalTempValues;
}



// --------------------------------------------------------------------------------
// Name: CleanUp
// Abstract: Deletes allocated array space in system memory and sets pointer to 0
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::CleanUp( )
{
	if (m_pavalValues != 0)
	{
		delete[] m_pavalValues;
	}

	// set values to 0
	m_pavalValues = 0;
	m_lngArraySize = 0;
}



// --------------------------------------------------------------------------------
// Name: DeepCopy
// Abstract: Performs a deep copy of the class pointer members
// --------------------------------------------------------------------------------
template<class Value>
inline void CResizableArray<Value>::DeepCopy( CResizableArray<Value>& clsSource )
{
	// declare variable
	long lngIndex = 0;

	m_pavalValues = 0; // deleting the pointer throws an error, even when non-zero. 

					   // because m_length is not a pointer, we can shallow copy it
	m_lngArraySize = clsSource.GetSize( );

	// m_pavalValues is a pointer, so we need to deep copy it if it is non-null
	if (clsSource.m_pavalValues)
	{
		// allocate memory for our copy
		m_pavalValues = new Value[ m_lngArraySize ];

		// do the copy
		for (lngIndex = 0; lngIndex < m_lngArraySize; lngIndex += 1)
		{
			this->m_pavalValues[ lngIndex ] = clsSource[ lngIndex ];
		}
	}
	else
	{
		m_pavalValues = nullptr;
	}
}

