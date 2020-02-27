





/*                                    CIPHER 2 toASCII_onBitReverse                                    */
#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 101 // We assume the string to be 100 characters long + the null terminator.
#define BYTE_SIZE 8 // Size of a byte in bits, size of a character in bits
#define BYTE_SIZE_ARRAY 7 // From 0 to 7
#define NIBBLE_SIZE 4 // Size of a nibble in bits, size of half a character in bits
#define START_oftheARRAY 0 // Define the starting point of an array
#define $_TRUE 1         // Boolean type integer mimicks true/false statement
#define $_FALSE 0        // Boolean type integer mimicks true/false statement

/* Declare functions */
void toASCII_onBitReverse( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] );
void printArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter );
void printArray_Vertically( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter);
void flip_theBITS_add_aONE( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue );
void count_theBITS( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue, unsigned int boolean_type_int );

/***************************************************************************************************
count theBITS takes and array of integers, which it traveses using a for loop.
The variable row counter in its parametres serves as the row, and the for loop index variable j will do as the columns.
As it goes, each makes a power notation of 2^j for each entry that == 1
it adds it to the parametre passed, numValue
and finally, it prints it out as a negative or a positive. Depending n the valye of boolean type int. Also in the parametre.
***************************************************************************************************/
void count_theBITS( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue, unsigned int boolean_type_int )
{
    /*
    for loop checks the bits for 1s, making the math
    */
    for( int j=( BYTE_SIZE-1 ); j>=0; j-- )
    {
        if( arbitraryArray_ofIntegers[ row_counter ][ j ]==1 ){ numValue += pow( 2,j ); }
    }
    /*
    If statement uses boolean-type-integer to check if we want a negative or a positive
    */
    if( boolean_type_int==1 )
    {
        printf( " = -%d", numValue );
    }
    else
    {
        printf( " = %d", numValue );
    }
}
/************************************************************************************************************************
flip theBITS add aONE is a two step function
first, it takes the array given. it will traverse a single row in it (the one matching the letter currently on) using row counter as it's anchor
it will create another array, which will be given the opposite values to the one given; " flipping the bits "
finally, it will perform a bit wise +1 operation on the new array.
the vlaue numValue is given only so that it may then be passed to the function : count theBITS
*************************************************************************************************************************/
void flip_theBITS_add_aONE( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue )
{
    unsigned int whileLoop_condition = 1; // The condition, if a bit is 0 then adding a one will not give us another one, thus stopping the summation
    unsigned int whileLoop_counter = 0; // To count the columns in the while loop
    unsigned int inputString_flip4negative[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence

    initialiseIntArray( inputString_flip4negative );    // initialise with zeroes

    /*
    for loop flips all the bits of the sequence above and saves them in another 2D array
    */
    for( int j=( BYTE_SIZE_ARRAY ); j>=0; j-- )
    {
        if( arbitraryArray_ofIntegers[ row_counter ][ j ]==1 )
        {
            inputString_flip4negative[ row_counter ][ j ]=0;
        }
        else
        {
            inputString_flip4negative[ row_counter ][ j ]=1;
        }
    }


    /*
    while loop will add the bit sequence of encoded by 1
    */
    while( whileLoop_condition!=0 )
    {
        whileLoop_condition=inputString_flip4negative[ row_counter ][ whileLoop_counter ];
        if( whileLoop_condition==0 )
        {
            inputString_flip4negative[ row_counter ][ whileLoop_counter ]=1;
        }
        else
        {
            inputString_flip4negative[ row_counter ][ whileLoop_counter ]=0;
        }
        whileLoop_counter++;
    }

    count_theBITS( inputString_flip4negative, row_counter, numValue, $_TRUE );

}
/************************************************************************************************************************************
printArray Vertically will take the array, go through it, and print its values in a vertical format
MUST SPECIFY THAT ONLY THE ROW PASSED THROUGH IN THE PARAMETRE IS PRINTED
Note that this function is no longer used. Made for testin gpurposes only
************************************************************************************************************************************/
void printArray_Vertically( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter)
{
    for( int j=( BYTE_SIZE_ARRAY ); j>=0; j-- )
    {
        printf("row %d col %d value %d\n", row_counter, j, arbitraryArray_ofIntegers[ row_counter ][ j ] );
    }
}
/************************************************************************************************************************************
printArray Vertically will take the array, go through it, and print its values in a horizontal format
************************************************************************************************************************************/
void printArray_Horizontally( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter )
{
    for( int j=( BYTE_SIZE_ARRAY ); j>=0; j-- )
    {
        printf("%d", arbitraryArray_ofIntegers[ row_counter ][ j ] );
    }
}
/************************************************************************************************************************************
 initialiseIntArray will take an array and set all its values to zero
************************************************************************************************************************************/
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] )
{
    /*
    For loop initialises 2D array with zeroes
    */
    for( int i=0; i<MAX_LENGTH; i++)
    {
        for( int j=0; j<BYTE_SIZE; j++)
        {
            arbitraryArray_ofIntegers[ i ][ j ]=0;
        }
    }
    return ( arbitraryArray_ofIntegers );
}
/************************************************************************************************************
function takes as parametre the two 2d arrays and two integers.
Given the original array, it fills the spaces in the array 'encoded' by reading and copying the bits in reverse order
then it checks whether or not the lfetmost digit is 1 or 0, representing negative or positive sign.
chossing, thus, which function to jump to afterwards based on that realisation
************************************************************************************************************/
void toASCII_onBitReverse( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp )
{
    unsigned int numValue = 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight = START_oftheARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft = BYTE_SIZE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle = NIBBLE_SIZE;    // The value used to traverse the n=8 arrays starting from the middle

    /*
    while loop create the new array by comparing the orginal's values
    */
    while( traverseRight!=BYTE_SIZE )
    {
        if( inputString_original[ row_counter ][ traverseRight ]==1 )
        {
            inputString_enconded[ row_counter ][ traverseLeft ]=1;
            printf( "%d", inputString_enconded[ row_counter ][ traverseLeft ] );
        }
        else
        {
            inputString_enconded[ row_counter ][ traverseLeft ]=0;
            printf( "%d", inputString_enconded[ row_counter ][ traverseLeft ] );
        }
        traverseRight++;
        traverseLeft--;
    }

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
    if( inputString_enconded[ row_counter ][ 7 ]==1 )
    {
        flip_theBITS_add_aONE( inputString_enconded, row_counter, numValue );
    }
    else
    {
        count_theBITS( inputString_enconded, row_counter, numValue, $_FALSE );
    }
}
int main()
{
    unsigned char inputString_m[ MAX_LENGTH ]="";           // Holds the sentence given
    unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the bit sequence of the sentence
    unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence
    unsigned int length_ofWord=0;       // holds the length of the words given by the user
    unsigned int temp=0;            // Used to hold the Integer version of the letters in inputString_m
    unsigned int tempCounter=0;     // Used to count so as to write the Integer version of the Binary Econding

    printf( "Enter the message to encode...\n" );
    scanf( "%s", &( inputString_m[ 0 ]));
    printf( "\n" );
    length_ofWord = strlen( inputString_m );

    // Call initialiseIntArray to set the values of our arrays to zero
    initialiseIntArray( inputString_original );
    initialiseIntArray( inputString_enconded );

    /*
        For loop starts the program, Picking off the first letter in the sentence
    */
    for( int i=0; i<length_ofWord; i++)
    {

    /*
        In temp we retain the Integer version of said letter
    */
        temp = (int)inputString_m[ i ];

    /*
    For loop starts the range from 0 to 7, the size of a character in bits
    */
        for( int j=( BYTE_SIZE_ARRAY ); j>=0; j-- )
        {

    /*
    If statement checks if the bit is 0 or 1, printing the corresponding match, saving it in the original array
    */
            if((( temp&( 1<<j )) >>j ) >0 )
            {
                inputString_original[ i ][ j ]=1;
            }
            else
            {
                inputString_original[ i ][ j ]=0;
            }
        }
        printArray_Horizontally( inputString_original, i );

    /*
    print statement prints the ASCII value of the letter being worked with
    */
        printf( " = %d\n", inputString_m[ i ]);

        /*
        if statement checks the edge case where all 8 bits are 0, flipping them would cause and overflow when adding by 1
        */
        if( temp==0 )
        {
            printf( " 0 = 0" );
        }

        /*
        else, we call the function that will do the summation and print the result
        */
        else
        {
            toASCII_onBitReverse( inputString_original, inputString_enconded, i, temp );

        }
        printf( "\n\n" );
    }
    return 0;
}
