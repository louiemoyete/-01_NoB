cipher2.c                                                                                           0000664 0001750 0001750 00000027456 13620105750 012533  0                                                                                                    ustar   student                         student                                                                                                                                                                                                                





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
                                                                                                                                                                                                                  cipher3.c                                                                                           0000664 0001750 0001750 00000031465 13620105767 012537  0                                                                                                    ustar   student                         student                                                                                                                                                                                                                





/*                                        CIPHER 3 toASCII_nibbleSwap                                   */
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
void toASCII_nibbleSwap( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
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
void printArray_Vertically( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter )
{
    for( int j=( BYTE_SIZE_ARRAY ); j>=0; j-- )
    {
        printf("encode : row %d col %d value %d\n", row_counter, j, arbitraryArray_ofIntegers[ row_counter ][ j ] );
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
Function takes two arrays and two integers. It grabs the encoded array and fillts its values with
the same as the originals; however, it divides the original's in nibbles (groups of 4 bits) and swaps
them about. Then it checks whetehr or not the leftmost digit is 1 or a 0, marking negative/positive.
Afterwards, it calls on the next functions.
************************************************************************************************************/
void toASCII_nibbleSwap( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp )
{
    unsigned int numValue = 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight = START_oftheARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft = BYTE_SIZE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle = NIBBLE_SIZE;    // The value used to traverse the n=8 arrays starting from the middle
    unsigned int inputString_flip4negative[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence
    unsigned int whileLoop_condition = 1;
    unsigned int whileLoop_counter = 0;

    initialiseIntArray( inputString_flip4negative );

    /*
    for loop create the new array by comparing the orginal's values in the 1st half
    */
    for( int j=( BYTE_SIZE_ARRAY ); j>=NIBBLE_SIZE; j-- )
    {
        if( inputString_original[ row_counter ][ traverseMiddle ]==1 )
        {
            inputString_enconded[ row_counter ][ traverseRight ]=1;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        else
        {
            inputString_enconded[ row_counter ][ traverseRight ]=0;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        traverseRight++;
        traverseMiddle++;
    }
    /*
    for loop create the new array by comparing the orginal's values in the 2nd half
    */
    for( int j=0; j<NIBBLE_SIZE; j++ )
    {
        if( inputString_original[ row_counter ][ j ]==1 )
        {
            inputString_enconded[ row_counter ][ j+NIBBLE_SIZE ]=1;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
        else
        {
            inputString_enconded[ row_counter ][ j+NIBBLE_SIZE ]=0;
            //printf( "%d", inputString_enconded[ row_counter ][ traverseRight ] );
        }
    }

    printArray_Horizontally( inputString_enconded, row_counter );

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
    unsigned int length_ofWord=0;               // holds the length of the words given by the user
    unsigned int temp=0;            // Used to hold the Integer version of the letters in inputString_m
    unsigned int tempCounter=0;     // Used to count so as to write the Integer version of the Binary Econding


    printf( "Enter the message to encode...\n" );
    scanf( "%s", &( inputString_m[ START_oftheARRAY ]));
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
            toASCII_nibbleSwap( inputString_original, inputString_enconded, i, temp );

        }
        printf( "\n\n" );
    }
    return 0;
}
                                                                                                                                                                                                           cipher.c                                                                                            0000664 0001750 0001750 00000056217 13620107354 012450  0                                                                                                    ustar   student                         student                                                                                                                                                                                                                





/*                                       CIPHER 4  random                                 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_LENGTH 101       // We assume the string to be 100 characters long + the null terminator.
#define BYTE_SIZE 8          // Size of a byte in bits, size of a character in bits
#define BYTE_SIZE_ARRAY 7    // From 0 to 7
#define NIBBLE_SIZE 4        // Size of a nibble in bits, size of half a character in bits
#define START_oftheARRAY 0   // Define the starting point of an array
#define $_TRUE 1             // Boolean type integer mimicks true/false statement
#define $_FALSE 0            // Boolean type integer mimicks true/false statement
#define INIT_NUM -1            // Number to initialise Int Arrays with

/* Define the functions */
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

/*
convert Int Array into Character Array will take an integer 2D array, who rows are the corresponding letters of the word and its columns the bits
representing each individual letter. Then it will create two different arrays,
array various strings will only hold one string at a time, printing out each corresponding sequence of bits before being erased
array single string will hold all the sequences of bits in a single string, each sequence of bytes separated by a 0b
array various strings has been commented out, but left here on purpose since I'm not sure why neither one of these two work
To explain, both of them hold the proper sequence of bits; however, when printing them out as a %d or a %c, I do not get the right result
*/
void convertIntArray_toCharacterArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int length_ofWord )
{
    /* temporary Placeholder will hold the byte sequence before being concatenated into another array, onne with 0b in it */
    unsigned char arbitraryArray_ofCharacters_temporaryPlaceholder[ MAX_LENGTH* BYTE_SIZE ]= "";

    /* various Strings will hold one byte sequence at a time, printing them out separately */
    unsigned char arbitraryArray_ofCharacters_variousStrings[ MAX_LENGTH* BYTE_SIZE ]= "";

    /* single String will hold the entire string in an array */
    unsigned char arbitraryArray_ofCharacters_singleString[ MAX_LENGTH* BYTE_SIZE ]= "";

    /* for loop will go over the length of the word given,
        for each character given, it will add a '0' and a 'b' to the single String array
        in palace after each byte sequence. the sprintf command will feed the bytes in integers, as characters,
        to temporary Placeholder; and finally, it will concatenate the new string of bits into both arrays.
        */
    for( int i= 0; i< length_ofWord; i++ )
    {
        arbitraryArray_ofCharacters_singleString[( i* 10 )]= '0';
        arbitraryArray_ofCharacters_singleString[(( i* 10 )+ 1 )]= 'b';
        /*
        The difference here, is that every time we go over the for loop we add a null terminator
        in place : index= 2 of various Strings. Deleting the string that was originally placed afterwards.
        strcat then sticks the new string there, deleted the  null terminator, and adds a new one.
        */
        //arbitraryArray_ofCharacters_variousStrings[ 0 ]= '0';
        //arbitraryArray_ofCharacters_variousStrings[ 1 ]= 'b';
        arbitraryArray_ofCharacters_variousStrings[ 2 ]= '\0';

        for( int j= 0; j< BYTE_SIZE_ARRAY; j++ )
        {
            sprintf(& arbitraryArray_ofCharacters_temporaryPlaceholder[( j )], "%d", arbitraryArray_ofIntegers[ i ][ j ]);
        }
        strcat( arbitraryArray_ofCharacters_variousStrings, arbitraryArray_ofCharacters_temporaryPlaceholder );
        strcat( arbitraryArray_ofCharacters_singleString, arbitraryArray_ofCharacters_temporaryPlaceholder );
    }
    printf( "As a single character string starting with 0b :\n" );
    printf( "%s", arbitraryArray_ofCharacters_singleString );
}

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
    for( int j= ( BYTE_SIZE-1 ); j>= 0; j-- )
    {
        if( arbitraryArray_ofIntegers[ row_counter ][ j ]== 1 ){ numValue+= pow( 2,j ); }
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
    unsigned int whileLoop_condition= 1; // The condition, if a bit is 0 then adding a one will not give us another one, thus stopping the summation
    unsigned int whileLoop_counter= 0; // To count the columns in the while loop
    unsigned int inputString_flip4negative[ MAX_LENGTH ][ BYTE_SIZE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence

    initialiseIntArray( inputString_flip4negative );    // initialise with zeroes

    /*
    for loop flips all the bits of the sequence above and saves them in another 2D array
    */
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


    /*
    while loop will add the bit sequence of encoded by 1
    */
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

/************************************************************************************************************************************
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
                                                                                                                                                                                                                                                                                                                                                                                 ReadMe                                                                                              0000664 0001750 0001750 00000003311 13620110376 012073  0                                                                                                    ustar   student                         student                                                                                                                                                                                                                First of, Good Morning.

Student Name, Luis Moyano.
Student ID, 101064606.

Include, math library : -lm when compiling

List of files :
cipher1.c
cipher2.c
cipher3.c
cipher.c
decipher.c

The first three files go perfectly.
You will notice something weird about the fourth,
I had not realised that the we were tasked to work on a character array holding a bit sequence.
I had been working with an integer array all this time, and up until in the specification of question 5 I read something about chars and bits
I took it upon myself to change the output a bit.
I honesty don't quite understand the instructions very well and have little idea of what I'm supposed to do or how to do it.
So I did it how it made sense, and in question 4 you will notice 3 different outputs :
the first one is the same as the outputs in all the other cipher files, where the array holding the encoded binary sequence as integers is printed out
the second output comes from a function that loops through this array and uses sprintf to convert them all into one single string.
      Regarding on this string, notice that every sequence of bytes starts with a 0b.
      I tried it all, even though the sequence of 1s and 0s is proper, and even though it starts with a 0b,
      I still cannot get it to output its corresponding ASCII code with %c;
      not its corresponding ASCII number with %d.
      But I left it in the result cause I got confused in the end regarding the format the professor wanted the result to be in.
Finally, the third result prints what I originally had for this function and what I think is what Mr. Lanthier wanted.
I.E.: the sequence of bits corresponding to the random encoding + a bunch of -1 all the way up AND including 100.
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       