





							/* ** ** **
				Randomly Decoding : Playing with Arrays and ASCII characters 
					Task i. Assume the output from cipher ( ask the user for a string to encode ) 
					Task ii. Decode an output provided by another file 
							** ** ** */ 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define BEGINNING_ARRAY 0   			// Starting point of arrays 
#define INIT_NUM 0            			// Digit to initialise arrays with 
#define INIT_NUM_DECIPHER 0   			// Digit to initialise the decipher arrays with 
#define MAX_LENGTH_USER_INPUT 50        // Max length of string
#define NEGATIVE 0            			// Mimicks boolean
#define POSITIVE 1             			// Mimicks boolean
#define SIZE_BYTE 8          			// Size of byte 
#define SIZE_BYTE_ARRAY 7    			// Number used when traversing arrays 
#define SIZE_NIBBLE 4        			// Size of nibble 

							/** ** ** *
			Global variables
							* ** ** **/
							
// The rows we will figure out to be in our decoded array
int decodedRows = 0; 
float percentageAlphanumerical_Max = 0; 

							/** ** ** * 
			Define the functions
							** ** ** */
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int init );
void print_arrayHorizontally_Entire( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void counting_theBits( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber, unsigned int boolean_int );
void flipAnd_addOne( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber );
int encode_onFlippingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingNibbles( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
void decipher_strippingCode( unsigned int encodedSequences[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void decipher_SwappingNibbles( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );
void decipher_SwappingBits( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );
void decipher_FlippingBits( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );

			/** ** ** *
	Function :
		Count the Bits 
	Parametres : 
		unsigned int : Array. Size : MAX_LENGTH_USER_INPUT ( define ) * SIZE_BYTE ( define ) 
		int : counterRows : Keeps track of the row counted 
		unsigned int valueNumber : Keeps track of the integer being calculated 
		unsigned int boolean_int : Mimicks boolean behaviour 
	Return : 
		Void 
	Functionality : 
		Loops through a row in the Array. Checking if the value is 1. 
		If so, it raises 2 to the power of index j; in the Array[ i ][ j ] 
		And adds the returning result to valueNumber. 
		Once done, the integer in valueNumber should be the number associated with that sequence of bits 
	Local Variables : 
		None
			* ** ** **/
void counting_theBits( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber, unsigned int boolean_int )
{
// for loop checks the bits for 1s, making the math
    for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
    {
        if( intArray[ counterRows ][ j ]== 1 ){ valueNumber+= pow( 2,j ); }
    }
}
			/** ** ** *
	Function :
		Flip the Bits, add a One 
	Parametres : 
		unsigned int : intArray. Size : MAX_LENGTH_USER_INPUT * SIZE_BYTE
		int counterRows
		unsigned int valueNumber
	Return : 
		Void 
	Functionality : 
		Two-step function. 
		Takes the array given. Traverses a row (whichever matches the current letter).
		Uses row counter as it's anchor. 
		Create another array, gives the opposite values to it (between 0 and 1), i.e.: "flipping the bits".
		Finally, mimicks a bitwise +1 operation on the new array
		valueNumber is given only so it may be passed to the function : count theBITS 
	Local Variables : 
		unsigned int whileLoop_condition : 
			The condition for the while loop. We change it in order to get out of it. 
		unsigned int whileLoop_counter : 
			The counter used inside the while loop. 
		unsigned int inputString_flip4negative : 
			An array the holds the flipped numbers of a sequence, in case the negative int of a sequence needs to be found 
		int j :	
			( for loop ) traverses intArray with counterRows and j 
			* ** ** **/
void flipAnd_addOne( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber )
{
    unsigned int inputString_flip4negative[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];   
	unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0; 

// Initialise array with INIT_NUM
    initialiseAn_intArray( inputString_flip4negative, INIT_NUM );

// For loop flips all the bits of the sequence above and saves them in another 2D array
    for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
    {
        if( intArray[ counterRows ][ j ]== 1 )
        {
            inputString_flip4negative[ counterRows ][ j ]= 0;
        }
        else
        {
            inputString_flip4negative[ counterRows ][ j ]= 1;
        }
    }

// While loop : Adds 1 to the sequence. The condition : Checks if a bit is 0
// If so, there won't be need to add more. The summation will stop. 
    while( whileLoop_condition!=0 )
    {
        whileLoop_condition= inputString_flip4negative[ counterRows ][ whileLoop_counter ];
        if( whileLoop_condition== 0 )
        {
            inputString_flip4negative[ counterRows ][ whileLoop_counter ]= 1;
        }
        else
        {
            inputString_flip4negative[ counterRows ][ whileLoop_counter ]= 0;
        }
        whileLoop_counter++;
    }

    counting_theBits( inputString_flip4negative, counterRows, valueNumber, POSITIVE );

}
			/** ** ** *
	Function :
		Print Array Horizontally, Entirely 
	Parametres : 
		unsigned int : intArray
		unsigned int : length_userInput
	Return : 
		void 
	Functionality : 
		Uses Nested For Loop to print the values of the array passed through in the parametre in horizonal format. As a 2D array. 
		The print statement is formatted with a width of 2 
	Local Variables : 
		int i : 
			( for loop ) traverses the array's rows 
		int j : 
			( nested for loop ) traverses the array's columns
			* ** ** **/
void print_arrayHorizontally_Entire( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] )
{
    unsigned char nibbleCounter = 0;
    printf("As the specifications asked for : \n");
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++ )
    {
        for( int j= ( 2 ); j> 0; j-- )
        {
            printf("%*d%*d%*d%*d",
                2, intArray[ i ][ ( SIZE_NIBBLE* j )- 1 ], 2, intArray[ i ][ ( SIZE_NIBBLE* j )- 2 ],
                2, intArray[ i ][ ( SIZE_NIBBLE* j )- 3 ], 2, intArray[ i ][ ( SIZE_NIBBLE* j )- 4 ]
            );
        }
    }
}
			/** ** ** *
 	Function :
		Initialise Int Array 
	Parametres : 
		unsigned int intArray
		unsigned int init
	Return : 
		int ( an 2D array of ) 
	Functionality : 
		Fills an Array with the values provided by INIT_NUM ( define ) 
 	Local Variables : 
		int i : 
			Traverses the array's rows, going up until MAX_LENGTH_USER_INPUT ( define ) 
		int j : 
			Traverses the array's columns, going up until SIZE_BYTE ( define ) 
			* ** ** **/
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int init )
{
// For loop initialises 2D array with init ( parametre ) 
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++)
    {
        for( int j= 0; j< SIZE_BYTE; j++)
        {
            intArray[ i ][ j ]= init;
        }
    }
    return ( intArray );
}
			/** ** ** *
	Function :
		Flip the bits 
	Parametres : 
		unsigned int userInput_original
		unsigned int userInput_encoded
		int counterRows
		unsigned int temp
	Return :
		int 
	Functionality :
		Taking both 2D arrays and two integers, 
		it 'encodes' userInput_encoded by flipping all the bits of the sequence.
		Then checks if we have a positive or a negative in the leftmost digit 
		Either calling flipAnd_addOne or counting_theBits
 	Local Variables : 
		unsigned int valueNumber : 
			valueNumber = 0, is passed to whatever function is called 
		unsigned int whileLoop_condition : 
			N/A
		unsigned int whileLoop_counter : 
			N/A
			* ** ** **/
int encode_onFlippingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int valueNumber= 0;
    unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

// for loop flips  all the bits of the sequence above
    for( int j= ( SIZE_BYTE-1 ); j>= 0; j-- )
    {
        if((( temp& ( 1<< j ))>> j )> 0 )
        {
            userInput_encoded[ counterRows ][ j ]= 0;
        }
        else
        {
            userInput_encoded[ counterRows ][ j ]= 1;
        }
    }

// If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    if( userInput_encoded[ counterRows ][ 7 ]== 1 )
    {
        flipAnd_addOne( userInput_encoded, counterRows, valueNumber );
    }
    else
    {
        counting_theBits( userInput_encoded, counterRows, valueNumber, NEGATIVE );
    }
    return userInput_encoded;
}
			/** ** ** *
	Function : 
		Swap the bits 
	Parametres : 
		unsigned int : userInput_original 
		unsigned int : userInput_encoded
		unsigned int : temp
		int : counterRows
	Return : 
		int : An 'Encoded' Array filled with 1s and 0s 
	Functionality : 
		Takes as parametre two 2D Arrays and 2 integers. 
		With the userInput_original, it fills the spaces of userInput_encoded
			by reading and copying the bits in reverse order. 
		Then, it checks whether or not the leftmost digit is 1 or 0,  
			representing negative or positive sign respectively, 
			choosing, thus, which function to jump to afterwards. 
	Local Variables : 
		unsigned int valueNumber : 
			Value holding the sum of all the 1s in the bit sequence
		unsigned int traverseRight : 
			Value used to traverse the n=8 arrays from the right
		unsigned int traverseLeft : 
			Value used to traverse the n=8 arrays from the left
		unsigned int traverseMiddle : 
			Value used to traverse the n=8 arrays starting from the middle
			* ** ** **/
int encode_onSwappingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int valueNumber= 0;
    unsigned int traverseRight= BEGINNING_ARRAY;
    unsigned int traverseLeft= SIZE_BYTE_ARRAY;
    unsigned int traverseMiddle= SIZE_NIBBLE;

// while loop create the new array by comparing the orginal's values
    while( traverseRight!= SIZE_BYTE )
    {
        if( userInput_original[ counterRows ][ traverseRight ]== 1 )
        {
            userInput_encoded[ counterRows ][ traverseLeft ]= 1;
        }
        else
        {
            userInput_encoded[ counterRows ][ traverseLeft ]= 0;
        }
        traverseRight++;
        traverseLeft--;
    }

// If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    if( userInput_encoded[ counterRows ][ 7 ]== 1 )
    {
        flipAnd_addOne( userInput_encoded, counterRows, valueNumber );
    }
    else
    {
        counting_theBits( userInput_encoded, counterRows, valueNumber, NEGATIVE );
    }
    return userInput_encoded;
}
			/** ** ** *
	Function :
		Swap the Nibbles 
	Parametres : 
		unsigned int : userInput_original
		unsigned int : userInput_encoded
		unsigned int : temp
		int : counterRows
	Return : 
		int : An 'Encoded' Array filled with 1s and 0s 
	Functionality : 
		Taking two Arrays and two Integers, 
		Fills the values of userInput_encoded with the same as userInput_original.
		It divides userInput_original's into groups of four, and swaps them. 
		Then, it checks if the leftmost digit it 1 or 0, 
			representing positive or negative, respectively. 
	Local Variables : 
		unsigned int valueNumber : 
			The value which holds the sum of all the 1s in the bit sequence
		unsigned int traverseRight : 
			The value used to traverse the n=8 arrays from the right
		unsigned int traverseLeft : 
			The value used to traverse the n=8 arrays from the left
		unsigned int traverseMiddle : 
			The value used to traverse the n=8 arrays starting from the middle
		unsigned int inputString_flip4negative : 
			Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence
		unsigned int whileLoop_condition : 
			Condition for the while loop 
		unsigned int whileLoop_counter : 
			Counter for the while loop 
			* ** ** **/
int encode_onSwappingNibbles( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int inputString_flip4negative[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];
    unsigned int traverseLeft= SIZE_BYTE_ARRAY;
    unsigned int traverseMiddle= SIZE_NIBBLE;
	unsigned int traverseRight= BEGINNING_ARRAY;
    unsigned int valueNumber= 0;
	unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

    initialiseAn_intArray( inputString_flip4negative, INIT_NUM );

// for loop create the new array by comparing the orginal's values in the 1st half
    for( int j= ( SIZE_BYTE_ARRAY ); j>= SIZE_NIBBLE; j-- )
    {
        if( userInput_original[ counterRows ][ traverseMiddle ]== 1 )
        {
            userInput_encoded[ counterRows ][ traverseRight ]= 1;
        }
        else
        {
            userInput_encoded[ counterRows ][ traverseRight ]= 0;
        }
        traverseRight++;
        traverseMiddle++;
    }
// for loop create the new array by comparing the orginal's values in the 2nd half
    for( int j= 0; j< SIZE_NIBBLE; j++ )
    {
        if( userInput_original[ counterRows ][ j ]== 1 )
        {
            userInput_encoded[ counterRows ][ j+ SIZE_NIBBLE ]= 1;
        }
        else
        {
            userInput_encoded[ counterRows ][ j+ SIZE_NIBBLE ]= 0;
        }
    }
// If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    if( userInput_encoded[ counterRows ][ 7 ]== 1 )
    {
        flipAnd_addOne( userInput_encoded, counterRows, valueNumber );
    }
    else
    {
        counting_theBits( userInput_encoded, counterRows, valueNumber, NEGATIVE );
    }
    return userInput_encoded;

}
			/** ** ** *
	Function :
		Decipher Code 
	Parametres : 
		unsigned int : encodedSequences
	Return : 
		void
	Functionality : 
		The ciphering stops when the -1 starts, this is known, so the elements can be copied
			into another array, dividing each row in bytes, and stopping when we reach a -1
		The size of the array given is MAX_LENGTH_USER_INPUT (101), this is known, 
			a reach from 0 to 100 is used because of it.
		Each byte is 8 bits, this is known, that is used to obtain the colums.  
		Given all : 
			First, find how many bits are in the array.
				Knowing the bits stop when the -1 starts
				Counting them in a rather inefficient way
			This information is held in counterBits ( local ) 
			Dividing it by 8, gives the rows, which equals the characters 
			This value will be the number of rows in the new 2D array
				Saved in decodedRows ( Global ) 
			Create a new array, initialise it with zeroes and copy the elements from the old array unto the new one 
			With an array filled with only the bit sequence of the characters, 
				the functions to decipher are called 
	Local Variables : 
		unsigned int counterBits : 
			For loop counter 
		unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] :
			New array 
			* ** ** **/
void decipher_strippingCode( unsigned int encodedSequences[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] )
{
    unsigned int counterBits = 0;
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++  )
    {
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( encodedSequences[ i ][ j  ]!= ( -1 ))
            {
                counterBits++;
            }
        }
    }
    decodedRows=( counterBits/ 8 );
    unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ];
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= 0; j<SIZE_BYTE; j++ )
        {
            inputString_decoded[ i ][ j ]= 0;
        }
    }
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++  )
    {
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( encodedSequences[ i ][ j  ]!= ( -1 ))
            {
                inputString_decoded[ i ][ j ] = encodedSequences[ i ][ j ];
            }
        }
    }
    decipher_FlippingBits( inputString_decoded );
    decipher_SwappingBits( inputString_decoded );
    decipher_SwappingNibbles( inputString_decoded );
    printf("Deciphered message with a %.2f", percentageAlphanumerical_Max);
    printf("%% accuracy\n");
}
			/** ** ** *
	Function :
		Decipher Swapping Nibbles  
	Parametres : 
		unsigned int : inputString_decoded
	Return : 
		void
	Functionality : 
		Takes the array provided by decipher_strippingCode, 
		it will create a new copy of the array so as to not overwrite the original. 
		Finally, it will reverse the process did on encode_onSwappingNibbles
			Printing out the percentage of alphanumeric characters vs the total amount of characters in the sentence 
	Local Variables : 
		unsigned int counterBits : 
			For loop counter 
		unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] :
			New array 
			* ** ** **/
void decipher_SwappingNibbles( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
{
    unsigned int inputString_decoded_NibbleSwap[ decodedRows ][ SIZE_BYTE ];

    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= ( SIZE_BYTE_ARRAY ); j>= SIZE_NIBBLE; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_NibbleSwap[ i ][ ( j- SIZE_NIBBLE) ]= 1;
            }
            else
            {
                inputString_decoded_NibbleSwap[ i ][ (j- SIZE_NIBBLE) ]= 0;
            }
        }
    }
    for( int i= 0; i< decodedRows; i++ )
    {
// The minus one marks where we left off in the last loop
        for( int j= ( SIZE_NIBBLE-1 ); j>= 0; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_NibbleSwap[ i ][( SIZE_NIBBLE+ j )]= 1;
            }
            else
            {
                inputString_decoded_NibbleSwap[ i ][( SIZE_NIBBLE+ j )]= 0;
            }
        }
    }
							/** ** ** *
			Having the bit sequence, we need the ASCII values
			First, we convert the binary into an integer by making some math
			Since we need to check the value for its character, we will start a for loop
				to traverse the rows.
			A variable is created to hold the integer
				later on, it'll be turned into an ASCII character, so we create a character holder as well
			A variable will count the amount of characters in the set that are alphanumerical
				this variable will later be divided over the total amount of characters so as to get the percentage
				and since the result will be printed, in the form of a string,
			A character array is also created
							* ** ** **/
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;

// The string, will have a space = to the amount of characters ( which we know to be decodedRows ), + 1 for the null terminator
    char decodedString[( decodedRows+1 )];

// The foor loop will do operations with the power of two
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
// we will initialise the values inside the for loop, so they reset for every row we go through
        integerHolder = 0;
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_NibbleSwap[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
// Check if the value of the bit sequence is alphanumerical by comparing it with their numeric values in the ASCII table
        if( integerHolder== 32)
// if it is a space			
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))
// if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))
// if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))
// if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
						/** ** ** *
		Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
						* ** ** **/
        characterHolder_ASCII = ( char )integerHolder;
// Finally, we want to add this new character into our string
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII);
    }
// After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
// Lastly, we print the formated result
        printf( "Match = %.2f%% Deciphered String = %s\n", percentageAlphanumerical, decodedString );
        if( percentageAlphanumerical > percentageAlphanumerical_Max ){ percentageAlphanumerical_Max= percentageAlphanumerical; }
}

/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** *
																						LEFT HERE 
* ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
/*
This here function will take the 'cleaned' array titled inputString_decoded, along with the counted rows
create a new array in which we copy all the values so as not to overwite the original
and then we will reverse the process did on the cipher bit Reverse
finally, we will print out the percentage of alphanumeric characters vs the total amount of characters in the sentece,
which we happen to know is == to decodedRows
*/
void decipher_SwappingBits( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
{
    /*
    What did Bit Reverse do ?
        Bit reverse took the binary sequence and swaped the bits
        in order, highest with lowest
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_BitReverse[ decodedRows ][ SIZE_BYTE ];
    /*
    we initialise the array with the values of inputString_decoded backwards
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_BitReverse[ i ][ (SIZE_BYTE_ARRAY-j) ]= 1;
            }
            else
            {
                inputString_decoded_BitReverse[ i ][ (SIZE_BYTE_ARRAY-j) ]= 0;
            }
        }
    }
							/** ** ** *
			Having the bit sequence, we need the ASCII values
			First, we convert the binary into an integer by making some math
			Since we need to check the value for its character, we will start a for loop
				to traverse the rows.
			A variable is created to hold the integer
				later on, it'll be turned into an ASCII character, so we create a character holder as well
			A variable will count the amount of characters in the set that are alphanumerical
				this variable will later be divided over the total amount of characters so as to get the percentage
				and since the result will be printed, in the form of a string,
			A character array is also created
							* ** ** **/
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;

// The string, will have a space = to the amount of characters ( which we know to be decodedRows ), + 1 for the null terminator
    char decodedString[( decodedRows+1 )];

// The foor loop will do operations with the power of two
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
// we will initialise the values inside the for loop, so they reset for every row we go through
        integerHolder = 0;
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_BitReverse[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
// Check if the value of the bit sequence is alphanumerical by comparing it with their numeric values in the ASCII table
        if( integerHolder== 32)                                     
// if it is a space
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))       
// if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))       
// if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))       
// if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
						/** ** ** *
		Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
						* ** ** **/
        characterHolder_ASCII = ( char )integerHolder;
// Finally, we want to add this new character into our string
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII);
    }
// After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
// Lastly, we print the formated result
        printf( "Match = %.2f%% Deciphered String = %s\n", percentageAlphanumerical, decodedString );
        if( percentageAlphanumerical > percentageAlphanumerical_Max ){ percentageAlphanumerical_Max= percentageAlphanumerical; }
}
/*
This here function will take the 'cleaned' array titled inputString_decoded, along with the counted rows
create a new array in which we copy all the values so as not to overwite the original
and then we will reverse the process did on the cipher Bit Flip
finally, we will print out the percentage of alphanumeric characters vs the total amount of characters in the sentece,
which we happen to know is == to decodedRows
*/
void decipher_FlippingBits( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
{
    /*
    What did Bit Flip do ?
        Bit Flip took the binary sequence and flipped the bits
        so, assuming that these bits are flipped, we must know flip them back
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_BitFlip[ decodedRows ][ SIZE_BYTE ];
    /*
    we initialise the array with the opposite values of inputString_decoded
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= 0; j<SIZE_BYTE; j++ )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_BitFlip[ i ][ j ]= 0;
            }
            else
            {
                inputString_decoded_BitFlip[ i ][ j ]= 1;
            }
        }
    }
							/** ** ** *
			Having the bit sequence, we need the ASCII values
			First, we convert the binary into an integer by making some math
			Since we need to check the value for its character, we will start a for loop
				to traverse the rows.
			A variable is created to hold the integer
				later on, it'll be turned into an ASCII character, so we create a character holder as well
			A variable will count the amount of characters in the set that are alphanumerical
				this variable will later be divided over the total amount of characters so as to get the percentage
				and since the result will be printed, in the form of a string,
			A character array is also created
							* ** ** **/
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;

// The string, will have a space = to the amount of characters ( which we know to be decodedRows ), + 1 for the null terminator
    char decodedString[( decodedRows+1 )];
// The foor loop will do operations with the power of two
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
// we will initialise the values inside the for loop, so they reset for every row we go through
        integerHolder = 0;
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_BitFlip[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
// Check if the value of the bit sequence is alphanumerical by comparing it with their numeric values in the ASCII table
        if( integerHolder== 32)                                     
// if it is a space
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))       
// if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))       
// if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))       
// if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
						/** ** ** *
		Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
						* ** ** **/
        characterHolder_ASCII = ( char )integerHolder;
// Finally, we want to add this new character into our string
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII );
    }
// After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
// Lastly, we print the formated result
        printf( "Match = %.2f%% Deciphered String = %s\n", percentageAlphanumerical, decodedString );
        if( percentageAlphanumerical > percentageAlphanumerical_Max ){ percentageAlphanumerical_Max= percentageAlphanumerical; }
}
/** ** ** *
* ** ** **/
int main()
{
    unsigned char inputString_m[ MAX_LENGTH_USER_INPUT ]= "";           // Holds the sentence given
    unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];   // Holds the bit sequence of the sentence
    unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];   // Holds the flipped bits of the sequence
    unsigned int length_ofWord= 0;       // holds the length of the words given by the user
    unsigned int temp= 0;            // Used to hold the Integer version of the letters in inputString_m
    unsigned int tempCounter= 0;     // Used to count so as to write the Integer version of the Binary Econding
    unsigned char cipher[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ]= {{""}}; // Will hold the know ciphered bit sequence in the form of a string
    unsigned int randomCounter= 0; // Keeps track of the random number that will choose the cipher

    /* The following line of code was copied from the course notes */
    /* Set the Random Seed to be that of the Time of day */
    srand( time( NULL ));
    scanf( "%s", &( inputString_m[ 0 ]));           // save the string given by user
    length_ofWord = strlen( inputString_m );        // mark the length of said string

    // Call initialiseAn_intArray to set the values of our arrays to zero
    initialiseAn_intArray( userInput_original, INIT_NUM );
    initialiseAn_intArray( userInput_encoded, INIT_NUM );

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
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {

    /*
    If statement checks if the bit is 0 or 1, printing the corresponding match
    */
            if((( temp& ( 1<< j ))>> j )> 0 )
            {
                userInput_original[ i ][ j ]= 1;
            }
            else
            {
                userInput_original[ i ][ j ]= 0;
            }
        }

    /* The following line of code was copied from the course notes */
    /* Choose a random number between 0 and 2*/
        randomCounter = ( int )( rand()/( double )RAND_MAX* 3 );
    /* If ternary statement grabs the randomCounter and chooses a cipher depending on the int given */
        if(  randomCounter== 0)
        {
            encode_onFlippingBits( userInput_original, userInput_encoded, i, temp );

        }
        else if(  randomCounter== 1)
        {
            encode_onSwappingBits( userInput_original, userInput_encoded, i, temp );

        }
        else
        {
            encode_onSwappingNibbles( userInput_original, userInput_encoded, i, temp );
        }
    }
    print_arrayHorizontally_Entire( userInput_encoded );
    printf( "\n\n" );
    printf( "Deciphering...\n" );
    printf( "...\n" );
    printf( "Deciphered:\n" );
    decipher_strippingCode( userInput_encoded );
    return 0;
}
