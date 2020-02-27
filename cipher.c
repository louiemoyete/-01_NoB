





/*                                       CIPHER 4  random                                 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


																		/******************************************************************************************
																							change the commentary first, then the names, then some values
																		******************************************************************************************/
#define MAX_LENGTH 101       // Max length of string
#define BYTE_SIZE 8          // Size of byte 
#define BYTE_SIZE_ARRAY 7
#define NIBBLE_SIZE 4        // Size of nibble 
#define START_oftheARRAY 0   // Starting point of arrays 
#define $_TRUE 1             // Mimicks boolean
#define $_FALSE 0            // Mimicks boolean 
#define INIT_NUM -1          // Digit to initialise arrays with 

																	
			/** ** ** *
		Define the functions
			* ** ** **/
void convertIntArray_toCharacterArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int length_ofWord );
void count_theBITS( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue, unsigned int boolean_type_int );
void flip_theBITS_add_aONE( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue );
void printArray_Vertically( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter);
void printArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter );
void printEntireArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int length_ofWord );
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] );
int toASCII_onTwosComplement( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
int toASCII_onBitReverse( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
int toASCII_nibbleSwap( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
void printEntireArray_Horizontally_FULL( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] );

			/** ** ** *
	Function :
		Convert Int Array to Character Array 
	Parametres : 
		unsigned int : An array of integers. Length : MAX_LENGTH ( define ) x BYTE_SIZE ( define ) 
		unsigned int : length_ofWord
	Return : 
		Void 
	Functionality : 
		Convert an the 2D Array of Ints into 2D Array of Chars. 
		Each row will match a character of the word represented in bits. 
	Local Variables : 
		arbitraryArray_ofCharacters_variousStrings : 
			Holds the byte sequence before being concatenated into arbitraryArray_ofCharacters_temporaryPlaceholder
		arbitraryArray_ofCharacters_temporaryPlaceholder : 
			Holds one byte sequence at a time, printing them out separately
		arbitraryArray_ofCharacters_singleString : 
			Holds the entire String in an Array 			
		i : 
			( for loop ) Traverses length of words 
		j : 
			( nested for loop ) Traverses specific row of arbitraryArray_ofIntegers
			* ** ** **/
void convertIntArray_toCharacterArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int length_ofWord )
{

    unsigned char arbitraryArray_ofCharacters_temporaryPlaceholder[ MAX_LENGTH* BYTE_SIZE ]= "";
    unsigned char arbitraryArray_ofCharacters_variousStrings[ MAX_LENGTH* BYTE_SIZE ]= "";
    unsigned char arbitraryArray_ofCharacters_singleString[ MAX_LENGTH* BYTE_SIZE ]= "";

// Goes over the length of the word. For each character given, add a '0b' to the Array ..._singleString
    for( int i= 0; i< length_ofWord; i++ )
    {
        arbitraryArray_ofCharacters_singleString[( i* 10 )]= '0';
        arbitraryArray_ofCharacters_singleString[(( i* 10 )+ 1 )]= 'b';
			/** ** ** *
	Notice the difference when we add a '0b\0' to the first three places, 
	The \0 will delete everything at the right of it. 
	Then, strcat will replace it with whatever, and add a new one on its own 
			* ** ** **/
        //arbitraryArray_ofCharacters_variousStrings[ 0 ]= '0';
        //arbitraryArray_ofCharacters_variousStrings[ 1 ]= 'b';
		//arbitraryArray_ofCharacters_variousStrings[ 2 ]= '\0';

// Goes through each index in a row, feeding the bytes in integers, as characters, to ..._temporaryPlaceholder
        for( int j= 0; j< BYTE_SIZE_ARRAY; j++ )
        {
            sprintf(& arbitraryArray_ofCharacters_temporaryPlaceholder[( j )], "%d", arbitraryArray_ofIntegers[ i ][ j ]);
        }
// Finally, it concatenates the new strings of bits into both arrays 
        strcat( arbitraryArray_ofCharacters_variousStrings, arbitraryArray_ofCharacters_temporaryPlaceholder );
        strcat( arbitraryArray_ofCharacters_singleString, arbitraryArray_ofCharacters_temporaryPlaceholder );
    }
    printf( "As a single character string starting with 0b :\n" );
    printf( "%s", arbitraryArray_ofCharacters_singleString );
}

/***************************************************************************************************
	Function :
		Count the Bits 
	Parametres : 
		unsigned int : Array. Size : MAX_LENGTH ( define ) * BYTE_SIZE ( define ) 
		int : row_counter : Keeps track of the row counted 
		unsigned int numValue : Keeps track of the integer being calculated 
		unsigned int boolean_type_int : Mimicks boolean behaviour 
	Return : 
		Void 
	Functionality : 
		Loops through a row in the Array. Checking if the value is 1. 
		If so, it raises 2 to the power of index j; in the Array[ i ][ j ] 
		And adds the returning result to numValue. 
		Once done, the integer in numValue should be the number associated with that sequence of bits 
	Local Variables : 
		None
***************************************************************************************************/
void count_theBITS( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue, unsigned int boolean_type_int )
{
    /*
    for loop checks the bits for 1s, making the math
    */
    for( int j= ( BYTE_SIZE-1 ); j>= 0; j-- )
    {
        if( arbitraryArray_ofIntegers[ row_counter ][ j ]== 1 ){ numValue+= pow( 2,j ); }
    }
}
/************************************************************************************************************************
	Function :
		Flip the Bits, add a One 
	Parametres : 
		unsigned int : arbitraryArray_ofIntegers. Size : MAX_LENGTH * BYTE_SIZE
		int row_counter
		unsigned int numValue
	Return : 
		Void 
	Functionality : 
		Two-step function. 
		Takes the array given. Traverses a row (whichever matches the current letter).
		Uses row counter as it's anchor. 
		Create another array, gives the opposite values to it (between 0 and 1), i.e.: "flipping the bits".
		Finally, mimicks a bitwise +1 operation on the new array
		numValue is given only so it may be passed to the function : count theBITS 
	Local Variables : 
		unsigned int whileLoop_condition : 
			The condition for the while loop. We change it in order to get out of it. 
		unsigned int whileLoop_counter : 
			The counter used inside the while loop. 
		unsigned int inputString_flip4negative : 
			An array the holds the flipped numbers of a sequence, in case the negative int of a sequence needs to be found 
		int j :	
			( for loop ) traverses arbitraryArray_ofIntegers with row_counter and j 
*************************************************************************************************************************/
void flip_theBITS_add_aONE( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue )
{
    unsigned int whileLoop_condition= 1; 
    unsigned int whileLoop_counter= 0; 
    unsigned int inputString_flip4negative[ MAX_LENGTH ][ BYTE_SIZE ];   

// Initialise array with INIT_NUM
    initialiseIntArray( inputString_flip4negative );    


// For loop : Flips all Nums of the sequence. Saves them in another 2D array. 
    for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
    {
        if( arbitraryArray_ofIntegers[ row_counter ][ j ]== 1 )
        {
            inputString_flip4negative[ row_counter ][ j ]= 0;
        }
        else
        {
            inputString_flip4negative[ row_counter ][ j ]= 1;
        }
    }

// While loop : Adds 1 to the sequence. The condition : Checks if a bit is 0
// If so, there won't be need to add more. The summation will stop. 
    while( whileLoop_condition!=0 )
    {
        whileLoop_condition= inputString_flip4negative[ row_counter ][ whileLoop_counter ];
        if( whileLoop_condition== 0 )
        {
            inputString_flip4negative[ row_counter ][ whileLoop_counter ]= 1;
        }
        else
        {
            inputString_flip4negative[ row_counter ][ whileLoop_counter ]= 0;
        }
        whileLoop_counter++;
    }
    count_theBITS( inputString_flip4negative, row_counter, numValue, $_TRUE );

}

/******************************************************************************************
																							Left here
																		******************************************************************************************/
																		/************************************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 

printArray Vertically will take the array, go through it, and print its values in a vertical format
MUST SPECIFY THAT ONLY THE ROW PASSED THROUGH IN THE PARAMETRE IS PRINTED
Note that this function is no longer used. Made for testin gpurposes only
************************************************************************************************************************************/
void printArray_Vertically( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter)
{
    for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
    {
        printf("row %d col %d value %d\n", row_counter, j, arbitraryArray_ofIntegers[ row_counter ][ j ] );
    }
}

/************************************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 
	Local Variables : 
		None
printArray Vertically will take the array, go through it, and print its values in a horizontal format
MUST SPECIFY THAT ONLY THE ROW PASSED THROUGH IN THE PARAMETRE IS PRINTED
Note that this function is no longer used. Made for testin gpurposes only
************************************************************************************************************************************/
void printArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter )
{
    for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
    {
        printf("%d", arbitraryArray_ofIntegers[ row_counter ][ j ] );
    }
}

/************************************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 

printEntireArray_Horizontally will take the array, go through it, and print its values in a horizontal format
************************************************************************************************************************************/
void printEntireArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int length_ofWord )
{
    unsigned char nibbleCounter = 0;
    printf("As a 2D integer array, formatted with a width of 2 : \n");
    for( int i= 0; i< length_ofWord; i++ )
    {
        for( int j= ( 2 ); j> 0; j-- )
        {
            printf("%*d%*d%*d%*d",
                2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 1 ], 2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 2 ],
                2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 3 ], 2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 4 ]
            );
        }
    }
}
/************************************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 
	Local Variables : 
		None
printEntireArray_Horizontally_FULL will take the array, go through it, and print its values in a horizontal format
WILL PRINT ALL 100 CHARACTERS, as it is asked for in the specifications : with a -1 filling the empty spots
************************************************************************************************************************************/
void printEntireArray_Horizontally_FULL( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] )
{
    unsigned char nibbleCounter = 0;
    printf("As the specifications asked for : \n");
    for( int i= 0; i< MAX_LENGTH; i++ )
    {
        for( int j= ( 2 ); j> 0; j-- )
        {
            printf("%*d%*d%*d%*d",
                2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 1 ], 2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 2 ],
                2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 3 ], 2, arbitraryArray_ofIntegers[ i ][ ( NIBBLE_SIZE* j )- 4 ]
            );
        }
    }
}

/************************************************************************************************************************************
 	Function :
	Parametres : 
	Return : 
	Functionality : 
 	Local Variables : 
		None
 initialiseIntArray will take an array and set all its values to zero
************************************************************************************************************************************/
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] )
{
    /*
    For loop initialises 2D array with zeroes
    */
    for( int i= 0; i< MAX_LENGTH; i++)
    {
        for( int j= 0; j< BYTE_SIZE; j++)
        {
            arbitraryArray_ofIntegers[ i ][ j ]= INIT_NUM;
        }
    }
    return ( arbitraryArray_ofIntegers );
}

/************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 	Local Variables : 
		None

function takes as parametre the two 2d arrays and two integers.
it encodes the original, by filling the encoded array with the opposite values compared to the original.
Then it checks if its posiive or negative, by checkng the leftmost sign,
given that decision, we move on to the next function : flip and add one,
or jump to the last function : count theBITS
************************************************************************************************************/
int toASCII_onTwosComplement( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp )
{
    unsigned int numValue= 0;
    unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

    /*
    for loop flips  all the bits of the sequence above
    */
    for( int j= ( BYTE_SIZE-1 ); j>= 0; j-- )
    {
        if((( temp& ( 1<< j ))>> j )> 0 )
        {
            inputString_enconded[ row_counter ][ j ]= 0;
        }
        else
        {
            inputString_enconded[ row_counter ][ j ]= 1;
        }
    }

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
    if( inputString_enconded[ row_counter ][ 7 ]== 1 )
    {
        flip_theBITS_add_aONE( inputString_enconded, row_counter, numValue );
    }
    else
    {
        count_theBITS( inputString_enconded, row_counter, numValue, $_FALSE );
    }
    return inputString_enconded;
}

/************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 
	Local Variables : 
		None
function takes as parametre the two 2d arrays and two integers.
Given the original array, it fills the spaces in the array 'encoded' by reading and copying the bits in reverse order
then it checks whether or not the lfetmost digit is 1 or 0, representing negative or positive sign.
chossing, thus, which function to jump to afterwards based on that realisation
************************************************************************************************************/
int toASCII_onBitReverse( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp )
{
    unsigned int numValue= 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight= START_oftheARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft= BYTE_SIZE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle= NIBBLE_SIZE;    // The value used to traverse the n=8 arrays starting from the middle

    /*
    while loop create the new array by comparing the orginal's values
    */
    while( traverseRight!= BYTE_SIZE )
    {
        if( inputString_original[ row_counter ][ traverseRight ]== 1 )
        {
            inputString_enconded[ row_counter ][ traverseLeft ]= 1;
        }
        else
        {
            inputString_enconded[ row_counter ][ traverseLeft ]= 0;
        }
        traverseRight++;
        traverseLeft--;
    }

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
    if( inputString_enconded[ row_counter ][ 7 ]== 1 )
    {
        flip_theBITS_add_aONE( inputString_enconded, row_counter, numValue );
    }
    else
    {
        count_theBITS( inputString_enconded, row_counter, numValue, $_FALSE );
    }
    return inputString_enconded;
}

/************************************************************************************************************
	Function :
	Parametres : 
	Return : 
	Functionality : 
	Local Variables : 
		None
Function takes two arrays and two integers. It grabs the encoded array and fillts its values with
the same as the originals; however, it divides the original's in nibbles (groups of 4 bits) and swaps
them about. Then it checks whetehr or not the leftmost digit is 1 or a 0, marking negative/positive.
Afterwards, it calls on the next functions.
************************************************************************************************************/
int toASCII_nibbleSwap( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp )
{
    unsigned int numValue= 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight= START_oftheARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft= BYTE_SIZE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle= NIBBLE_SIZE;    // The value used to traverse the n=8 arrays starting from the middle
    unsigned int inputString_flip4negative[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence
    unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

    initialiseIntArray( inputString_flip4negative );

    /*
    for loop create the new array by comparing the orginal's values in the 1st half
    */
    for( int j= ( BYTE_SIZE_ARRAY ); j>= NIBBLE_SIZE; j-- )
    {
        if( inputString_original[ row_counter ][ traverseMiddle ]== 1 )
        {
            inputString_enconded[ row_counter ][ traverseRight ]= 1;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        else
        {
            inputString_enconded[ row_counter ][ traverseRight ]= 0;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        traverseRight++;
        traverseMiddle++;
    }
    /*
    for loop create the new array by comparing the orginal's values in the 2nd half
    */
    for( int j= 0; j< NIBBLE_SIZE; j++ )
    {
        if( inputString_original[ row_counter ][ j ]== 1 )
        {
            inputString_enconded[ row_counter ][ j+ NIBBLE_SIZE ]= 1;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        else
        {
            inputString_enconded[ row_counter ][ j+ NIBBLE_SIZE ]= 0;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
    }

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
    if( inputString_enconded[ row_counter ][ 7 ]== 1 )
    {
        flip_theBITS_add_aONE( inputString_enconded, row_counter, numValue );
    }
    else
    {
        count_theBITS( inputString_enconded, row_counter, numValue, $_FALSE );
    }
    return inputString_enconded;

}

int main()
{
    unsigned char inputString_m[ MAX_LENGTH ]= "";           // Holds the sentence given
    unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the bit sequence of the sentence
    unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence
    unsigned int length_ofWord= 0;       // holds the length of the words given by the user
    unsigned int temp= 0;            // Used to hold the Integer version of the letters in inputString_m
    unsigned int tempCounter= 0;     // Used to count so as to write the Integer version of the Binary Econding
    unsigned char cipher[ MAX_LENGTH ][ BYTE_SIZE ]= {{""}}; // Will hold the know ciphered bit sequence in the form of a string
    unsigned int randomCounter= 0; // Keeps track of the random number that will choose the cipher

    /* The following line of code was copied from the course notes */
    /* Set the Random Seed to be that of the Time of day */
    srand( time( NULL ));
    scanf( "%s", &( inputString_m[ 0 ]));           // save the string given by user
    length_ofWord = strlen( inputString_m );        // mark the length of said string

    // Call initialiseIntArray to set the values of our arrays to zero
    initialiseIntArray( inputString_original );
    initialiseIntArray( inputString_enconded );

    /*
        For loop starts the program, Picking off the first letter in the sentence
    */
    for( int i= 0; i< length_ofWord; i++ )
    {

    /*
        In temp we retain the Integer version of said letter
    */
        temp= ( int )inputString_m[ i ];

    /*
    For loop then starts the range from 0 to 7, the size of a character in bits
    */
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {

    /*
    If statement checks if the bit is 0 or 1, printing the corresponding match
    */
            if((( temp& ( 1<< j ))>> j )> 0 )
            {
                inputString_original[ i ][ j ]= 1;
            }
            else
            {
                inputString_original[ i ][ j ]= 0;
            }
        }

    /* The following line of code was copied from the course notes */
    /* Choose a random number between 0 and 2*/
        randomCounter = ( int )( rand()/( double )RAND_MAX* 3 );
    /* If ternary statement grabs the randomCounter and chooses a cipher depending on the int given */
        if(  randomCounter== 0)
        {
            toASCII_onTwosComplement( inputString_original, inputString_enconded, i, temp );

        }
        else if(  randomCounter== 1)
        {
            toASCII_onBitReverse( inputString_original, inputString_enconded, i, temp );

        }
        else
        {
            toASCII_nibbleSwap( inputString_original, inputString_enconded, i, temp );
        }
    }
    printEntireArray_Horizontally( inputString_enconded, length_ofWord );
    printf( "\n\n" );
    convertIntArray_toCharacterArray( inputString_enconded, length_ofWord );
    printf( "\n\n" );
    printEntireArray_Horizontally_FULL( inputString_enconded );
    printf( "\n\n" );
    return 0;
}
