





							/** ** ** * 
			Randomly Encoding : Playing with Arrays and ASCII characters 
							** ** ** */ 
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


#define BEGINNING_ARRAY 0   			// Starting point of arrays 
#define INIT_NUM 0          			// Digit to initialise arrays with 
#define MAX_LENGTH_USER_INPUT 50       	// Max length of string
#define NEGATIVE 0       	     		// Mimicks boolean 
#define POSITIVE 1       		        // Mimicks boolean
#define SIZE_BYTE 8          			// Size of byte 
#define SIZE_BYTE_ARRAY 7	 			// Number used when traversing arrays 
#define SIZE_NIBBLE 4        			// Size of nibble 

																	
			/** ** ** *
		Define the functions
			* ** ** **/
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void print_arrayVertically_byLine( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows);
void print_arrayHorizontally_byLine( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows );
void print_arrayHorizontally_Entire( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int length_userInput );
void print_arrayHorizontally_Entire_100CharLength( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void convertInt_toChar( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int length_userInput );
void counting_theBits( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber, unsigned int boolean_int );
void flipAnd_addOne( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber );
int encode_onFlippingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingNibbles( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );

			/** ** ** *
	Function :
		Convert Int Array to Character Array 
	Parametres : 
		unsigned int : An array of integers. Length : MAX_LENGTH_USER_INPUT ( define ) x SIZE_BYTE ( define ) 
		unsigned int : length_userInput
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
			( nested for loop ) Traverses specific row of intArray
			* ** ** **/
void convertInt_toChar( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int length_userInput )
{

    unsigned char arbitraryArray_ofCharacters_temporaryPlaceholder[ MAX_LENGTH_USER_INPUT* SIZE_BYTE ]= "";
    unsigned char arbitraryArray_ofCharacters_variousStrings[ MAX_LENGTH_USER_INPUT* SIZE_BYTE ]= "";
    unsigned char arbitraryArray_ofCharacters_singleString[ MAX_LENGTH_USER_INPUT* SIZE_BYTE ]= "";

// Goes over the length of the word. For each character given, add a '0b' to the Array ..._singleString
    for( int i= 0; i< length_userInput; i++ )
    {
        arbitraryArray_ofCharacters_singleString[( i* 10 )]= '0';
        arbitraryArray_ofCharacters_singleString[(( i* 10 )+ 1 )]= 'b';
			/** ** ** *
	Note : 
		the difference when we add a '0b\0' to the first three places, 
		The \0 will delete everything at the right of it. 
		Then, strcat will replace it with whatever, and add a new one on its own 
			* ** ** **/
        //arbitraryArray_ofCharacters_variousStrings[ 0 ]= '0';
        //arbitraryArray_ofCharacters_variousStrings[ 1 ]= 'b';
		//arbitraryArray_ofCharacters_variousStrings[ 2 ]= '\0';

// Goes through each index in a row, feeding the bytes in integers, as characters, to ..._temporaryPlaceholder
        for( int j= 0; j< SIZE_BYTE_ARRAY; j++ )
        {
            sprintf(& arbitraryArray_ofCharacters_temporaryPlaceholder[( j )], "%d", intArray[ i ][ j ]);
        }
// Finally, it concatenates the new strings of bits into both arrays 
        strcat( arbitraryArray_ofCharacters_variousStrings, arbitraryArray_ofCharacters_temporaryPlaceholder );
        strcat( arbitraryArray_ofCharacters_singleString, arbitraryArray_ofCharacters_temporaryPlaceholder );
    }
    printf( "As a single character string starting with 0b :\n" );
    printf( "%s", arbitraryArray_ofCharacters_singleString );
}

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

// for loop checks the bits for 1s; holding j, if the bit is 1 then valueNumber += 2^j 
    for( int j= ( SIZE_BYTE-1 ); j>= 0; j-- )
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
    initialiseAn_intArray( inputString_flip4negative );    

// For loop : Flips all Nums of the sequence. Saves them in another 2D array. 
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
		Print Array Vertically by Line
	Parametres : 
		unsigned int : intArray
		int : counterRows
	Return : 
		void 
	Functionality : 
		Prints the values of the array passed through the parametre in vertical format.
		Only the row passed through the parametre is printed. 
			*!* Function no longer used, made for testing purposes only. *!*
	Local Variables : 
		int j :
			( for loop ) traverses the array's columns
			* ** ** **/
void print_arrayVertically_byLine( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows)
{
    for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
    {
        printf("row %d col %d value %d\n", counterRows, j, intArray[ counterRows ][ j ] );
    }
}

			/** ** ** *
	Function :
		Print Array Horizontally by Line
	Parametres : 
		unsigned int : intArray
		int : counterRows
	Return : 
		void 
	Functionality : 
		Prints the values of the array passed through the parametre in horizontal format.
		Only the row passed through the parametre is printed 
			*!* Function no longer used, made for testing purposes only. *!*
	Local Variables : 
		int j : 	
			( for loop ) traverses the array's columns
			* ** ** **/
void print_arrayHorizontally_byLine( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows )
{
    for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
    {
        printf("%d", intArray[ counterRows ][ j ] );
    }
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
void print_arrayHorizontally_Entire( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int length_userInput )
{
    printf("As a 2D integer array, formatted with a width of 2 : \n");
    for( int i= 0; i< length_userInput; i++ )
    {
        for( int j= ( 2 ); j> 0; j-- )
        {
            printf("%*d%*d%*d%*d\n",
                2, intArray[ i ][ ( SIZE_NIBBLE* j )- 1 ], 2, intArray[ i ][ ( SIZE_NIBBLE* j )- 2 ],
                2, intArray[ i ][ ( SIZE_NIBBLE* j )- 3 ], 2, intArray[ i ][ ( SIZE_NIBBLE* j )- 4 ]
            );
        }
    }
}
			/** ** ** *
	Function :
		Print Entire Array Horizontally, Entirely, 100 characters of length 
	Parametres : 
		unsigned int : 
			intArray
	Return : 
		void 
	Functionality : 
		Prints the entire array passed through parametres : 
		in horizontal format, 
		with a length of 100 characters, 
		filling the non-0 & non-1 characters with -1,
		with a width of 2 
	Local Variables : 
		int i : 
			( for loop ) traverses array's rows 
		int j : 
			( nest for loop ) traverses array's columns
			* ** ** **/
void print_arrayHorizontally_Entire_100CharLength( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] )
{
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
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] )
{

// For loop initialises 2D array with zeroes
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++)
    {
        for( int j= 0; j< SIZE_BYTE; j++)
        {
            intArray[ i ][ j ]= INIT_NUM;
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

    initialiseAn_intArray( inputString_flip4negative );

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
	Local Variables in Main : 
		unsigned char inputString_m : 
			Holds the sentence given
		unsigned int userInput_original : 
			Holds the bit sequence of the sentence
		unsigned int userInput_encoded : 
			Holds the flipped bits of the sequence
		unsigned int length_userInput :
			Holds the length of the words given by the user
		unsigned int temp :
			Used to hold the Integer version of the letters in inputString_m
		unsigned int tempCounter : 
			Used to count so as to write the Integer version of the Binary Encoding
		unsigned char cipher : 
			Will hold the know ciphered bit sequence in the form of a string
		unsigned int randomCounter : 
			Keeps track of the random number that will choose the cipher
			* ** ** **/
int main()
{
    unsigned char inputString_m[ MAX_LENGTH_USER_INPUT ]= "";
    unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];
    unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];
    unsigned int length_userInput= 0;
    unsigned int temp= 0;
    unsigned int tempCounter= 0;
    unsigned char cipher[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ]= {{""}};
    unsigned int randomCounter= 0;

// Set the Random Seed to the Time of day
    srand( time( NULL ));
// Save the string given by user
    scanf( "%s", &( inputString_m[ 0 ]));           
// Mark the length of said string	
    length_userInput = strlen( inputString_m );        

// Call initialiseAn_intArray to set the values of our arrays to zero
    initialiseAn_intArray( userInput_original );
    initialiseAn_intArray( userInput_encoded );

// For loop starts the program, Picking off the first letter in the sentence
    for( int i= 0; i< length_userInput; i++ )
    {

// In temp we retain the Integer version of said letter
        temp= ( int )inputString_m[ i ];

// For loop then starts the range from 0 to 7, the size of a character in bits
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
        {

// If statement checks if the bit is 0 or 1, printing the corresponding match
            if((( temp& ( 1<< j ))>> j )> 0 )
            {
                userInput_original[ i ][ j ]= 1;
            }
            else
            {
                userInput_original[ i ][ j ]= 0;
            }
        }
		
// Choose a random number between 0 and 2
        randomCounter = ( int )( rand()/( double )RAND_MAX* 3 );
// Ternary statement grabs the randomCounter and chooses a cipher depending on the int given
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
    print_arrayHorizontally_Entire( userInput_encoded, length_userInput );
    printf( "\n\n" );
    convertInt_toChar( userInput_encoded, length_userInput );
    printf( "\n\n" );
    print_arrayHorizontally_Entire_100CharLength( userInput_encoded );
    printf( "\n\n" );
    return 0;
}
