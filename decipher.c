





/*                                       DECIPHER                                 */
/****************************************************************************************************
                ASSUME THE OUTPUT FROM CIPHER :
                A BINARY SEQUENCE FOLLOWED BY -1s
                ALL THE WAY UP TO AND INCLUDING 100
****************************************************************************************************/
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
#define INIT_NUM_DECIPHER 0   // Number with which we initialise the decipher array

/*
Global variables
*/
int decodedRows = 0; // The rows we will figure out to be in our decoded array
float percentageAlphanumerical_Max = 0; // The rows we will figure out to be in our decoded array

/* Define the functions */
void count_theBITS( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue, unsigned int boolean_type_int );
void flip_theBITS_add_aONE( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int numValue );
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int init );
int toASCII_onTwosComplement( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
int toASCII_onBitReverse( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
int toASCII_nibbleSwap( unsigned int inputString_original[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int inputString_enconded[ MAX_LENGTH ][ BYTE_SIZE ], int row_counter, unsigned int temp );
void printEntireArray_Horizontally_FULL( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ] );
void decipherCode( unsigned int enconded[ MAX_LENGTH ][ BYTE_SIZE ] );
void decipherNibbleSwap( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] );
void decipherBitReverse( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] );
void decipherBitFlip( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] );


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
    for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
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

    initialiseIntArray( inputString_flip4negative, INIT_NUM );    // initialise with zeroes

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
int initialiseIntArray( unsigned int arbitraryArray_ofIntegers[ MAX_LENGTH ][ BYTE_SIZE ], unsigned int init )
{
    /*
    For loop initialises 2D array with zeroes
    */
    for( int i= 0; i< MAX_LENGTH; i++)
    {
        for( int j= 0; j< BYTE_SIZE; j++)
        {
            arbitraryArray_ofIntegers[ i ][ j ]= init;
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

    initialiseIntArray( inputString_flip4negative, INIT_NUM );

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

/************************************************************************************************************************************
decipher code pretends we know nothing about the othe rprograms, save the 3 types of ciphering that could have been done, and the encoded message.
Since we know each character is ade up of a byte, we can also skip checking for that.
How many characters are there in the sentence... First we must find out the total amount of elements in the array
Then we must fin dout the total amount of rows
************************************************************************************************************************************/
void decipherCode( unsigned int enconded[ MAX_LENGTH ][ BYTE_SIZE ] )
{
    /*
    We know the ciphering stops when the -1 starts, so we can copy the elements
    into another array, dividing each row in bytes, and stopping when we reach a -1
    We know the size of the array given is MAX_LENGTH (101); we use that to obtain a reach rom 0 to 100.
    We know each byte is 8 bits, we use that to obtain the colums
    All that said,
    first, we must find out how many bits are in the array.
    we know the bits stop when the -1 starts
    let's count them in a very inefficient way like we used to do at the beginning of 2402
    */
    unsigned int counterBits = 0;
    for( int i= 0; i< MAX_LENGTH; i++  )
    {
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( enconded[ i ][ j  ]!= ( -1 ))
            {
                counterBits++;
            }
        }
    }
    /*
    As mentioned, we know each character is held in a pair of bytes ; i.e.: 8 bits.
    Thus, in order to get the amount of characters in oursequence, we divide counterBits by 8
    This value will be the number of rows in our new 2D array.
    The columns, same as before, will be the total amount of bits in a pair of bytes.
    This way, we can have a character per row
    */
    decodedRows=( counterBits/ 8 );
    /*
    This array will hold the 'cleaned' bit sequence
    */
    unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ];
    /*
    Now that we have the exact amount of rows as characters in the sentence,
    we initialise the array with zeroes, instead of -1
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= 0; j<BYTE_SIZE; j++ )
        {
            inputString_decoded[ i ][ j ]= 0;
        }
    }
    /*
    and copy paste the for loop above; this time though, we will copy the elements
    in the encoded array unto the decoded array.
    In theory, we should end up with an exactly full array. No more no less.
    To do this, we will place an if statement to check if we're copying bits or negative ones
    */
    for( int i= 0; i< MAX_LENGTH; i++  )
    {
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( enconded[ i ][ j  ]!= ( -1 ))
            {
                inputString_decoded[ i ][ j ] = enconded[ i ][ j ];
            }
        }
    }
    /*
    Now that we have a clean array. we need to reverse the process for each cipher we did
    */
    decipherBitFlip( inputString_decoded );
    decipherBitReverse( inputString_decoded );
    decipherNibbleSwap( inputString_decoded );
    printf("Deciphered message with a %.2f", percentageAlphanumerical_Max);
    printf("%% accuracy\n");
}

/*
This here function will take the 'cleaned' array titled inputString_decoded, along with the counted rows
create a new array in which we copy all the values so as not to overwite the original
and then we will reverse the process did on the cipher Nibble Swap
finally, we will print out the percentage of alphanumeric characters vs the total amount of characters in the sentece,
which we happen to know is == to decodedRows
*/
void decipherNibbleSwap( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] )
{
    /*
    What did Nibble Swap do ?
        Nibble Swap took the binary sequence and swaped the nibbles
        by dividing the byte in two groups of four bits each
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_NibbleSwap[ decodedRows ][ BYTE_SIZE ];
    /*
    we initialise the array with the values of inputString_decoded
    breaking apart the nibbles and switching them
    Having thus two for loop, dividing both halfs
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= ( BYTE_SIZE_ARRAY ); j>= NIBBLE_SIZE; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_NibbleSwap[ i ][ ( j- NIBBLE_SIZE) ]= 1;
            }
            else
            {
                inputString_decoded_NibbleSwap[ i ][ (j- NIBBLE_SIZE) ]= 0;
            }
        }
    }
    for( int i= 0; i< decodedRows; i++ )
    {
            /* the minus one marks where we left off in the last loop */
        for( int j= ( NIBBLE_SIZE-1 ); j>= 0; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_NibbleSwap[ i ][( NIBBLE_SIZE+ j )]= 1;
            }
            else
            {
                inputString_decoded_NibbleSwap[ i ][( NIBBLE_SIZE+ j )]= 0;
            }
        }
    }
    /*
    Now that we have the bit sequence, we need to get its ASCII values
    First, we will convert the binary into an integer by making some math
    Since we need to check the value for its character, we will start a for loop
    to traverse the rows
    lets make a variable to hold the integer
    we will want to turn it into an ascii character later on, so let us start a character holder as well
    while we're at it, we need a variable that will count the amount of characters in our set that are alphanumerical
    this variable we will later divide over the total amount of characters so as to get the percentage
    and since we need to print out the result as well, in the form of a string,
    we will also get a character array going
    */
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;
    /*
    our string, we will give it a space equal to the amount of characters (which we know to be decodedRows ), + 1 for the null terminator
    */
    char decodedString[( decodedRows+1 )];
    /*
    the foor loop will do operations with the power of two
    */
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
        /*
        we will initialise the values inside the for loop, so they reset
        for every row we go through
        */
        integerHolder = 0;
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_NibbleSwap[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
        /*
        now that we're in posession of the value of the bit sequence, we will check if it is an alphanumerical value by
        comparing it with their numeric values in the ASCII table
        */
        if( integerHolder== 32)                                     // if it is a space
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))       // if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))       // if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))       // if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
        /*
        Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
        */
        characterHolder_ASCII = ( char )integerHolder;
        /*
        Finally, we want to add this new character into our string
        */
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII);
    }
        /*
        After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        */
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
        /* lastly, we print the formated result */
        printf( "Match = %.2f%% Deciphered String = %s\n", percentageAlphanumerical, decodedString );
        if( percentageAlphanumerical > percentageAlphanumerical_Max ){ percentageAlphanumerical_Max= percentageAlphanumerical; }
}

/*
This here function will take the 'cleaned' array titled inputString_decoded, along with the counted rows
create a new array in which we copy all the values so as not to overwite the original
and then we will reverse the process did on the cipher bit Reverse
finally, we will print out the percentage of alphanumeric characters vs the total amount of characters in the sentece,
which we happen to know is == to decodedRows
*/
void decipherBitReverse( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] )
{
    /*
    What did Bit Reverse do ?
        Bit reverse took the binary sequence and swaped the bits
        in order, highest with lowest
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_BitReverse[ decodedRows ][ BYTE_SIZE ];
    /*
    we initialise the array with the values of inputString_decoded backwards
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded[ i ][ j ]== 1 )
            {
                inputString_decoded_BitReverse[ i ][ (BYTE_SIZE_ARRAY-j) ]= 1;
            }
            else
            {
                inputString_decoded_BitReverse[ i ][ (BYTE_SIZE_ARRAY-j) ]= 0;
            }
        }
    }
    /*
    Now that we have the bit sequence, we need to get its ASCII values
    First, we will convert the binary into an integer by making some math
    Since we need to check the value for its character, we will start a for loop
    to traverse the rows
    lets make a variable to hold the integer
    we will want to turn it into an ascii character later on, so let us start a character holder as well
    while we're at it, we need a variable that will count the amount of characters in our set that are alphanumerical
    this variable we will later divide over the total amount of characters so as to get the percentage
    and since we need to print out the result as well, in the form of a string,
    we will also get a character array going
    */
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;
    /*
    our string, we will give it a space equal to the amount of characters (which we know to be decodedRows ), + 1 for the null terminator
    */
    char decodedString[( decodedRows+1 )];
    /*
    the foor loop will do operations with the power of two
    */
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
        /*
        we will initialise the values inside the for loop, so they reset
        for every row we go through
        */
        integerHolder = 0;
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_BitReverse[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
        /*
        now that we're in posession of the value of the bit sequence, we will check if it is an alphanumerical value by
        comparing it with their numeric values in the ASCII table
        */
        if( integerHolder== 32)                                     // if it is a space
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))       // if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))       // if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))       // if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
        /*
        Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
        */
        characterHolder_ASCII = ( char )integerHolder;
        /*
        Finally, we want to add this new character into our string
        */
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII);
    }
        /*
        After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        */
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
        /* lastly, we print the formated result */
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
void decipherBitFlip( unsigned int inputString_decoded[ decodedRows ][ BYTE_SIZE ] )
{
    /*
    What did Bit Flip do ?
        Bit Flip took the binary sequence and flipped the bits
        so, assuming that these bits are flipped, we must know flip them back
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_BitFlip[ decodedRows ][ BYTE_SIZE ];
    /*
    we initialise the array with the opposite values of inputString_decoded
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= 0; j<BYTE_SIZE; j++ )
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
    /*
    Now that we have the bit sequence, we need to get its ASCII values
    First, we will convert the binary into an integer by making some math
    Since we need to check the value for its character, we will start a for loop
    to traverse the rows
    lets make a variable to hold the integer
    we will want to turn it into an ascii character later on, so let us start a character holder as well
    while we're at it, we need a variable that will count the amount of characters in our set that are alphanumerical
    this variable we will later divide over the total amount of characters so as to get the percentage
    and since we need to print out the result as well, in the form of a string,
    we will also get a character array going
    */
    int integerHolder;
    char characterHolder_ASCII;
    int alphanumericalCounter= 0;
    /*
    our string, we will give it a space equal to the amount of characters (which we know to be decodedRows ), + 1 for the null terminator
    */
    char decodedString[( decodedRows+1 )];
    /*
    the foor loop will do operations with the power of two
    */
    for( int i= ( 0 ); i< decodedRows; i++ )
    {
        /*
        we will initialise the values inside the for loop, so they reset
        for every row we go through
        */
        integerHolder = 0;
        for( int j= ( BYTE_SIZE_ARRAY ); j>= 0; j-- )
        {
            if( inputString_decoded_BitFlip[ i ][ j ]== 1 ){ integerHolder+= pow( 2,j ); }
        }
        /*
        now that we're in posession of the value of the bit sequence, we will check if it is an alphanumerical value by
        comparing it with their numeric values in the ASCII table
        */
        if( integerHolder== 32)                                     // if it is a space
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=48 )&&( integerHolder<=57 ))       // if it is a number
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=65 )&&( integerHolder<=90 ))       // if it is a majuscule letter
            {
                alphanumericalCounter++;
            }
        else if(( integerHolder>=97 )&&( integerHolder<=122 ))       // if it is a miniscule letter
            {
                alphanumericalCounter++;
            }
        /*
        Now that we want to to turn it into an ASCII character
        we start by equaling the character to the integer, typecasting the integer in the progress
        */
        characterHolder_ASCII = ( char )integerHolder;
        /*
        Finally, we want to add this new character into our string
        */
        sprintf(& decodedString[( i )], "%c", characterHolder_ASCII );
    }
        /*
        After exiting the for loop, we get the percentage of alphanumerical characters by dividing the counter with the total
        */
        float percentageAlphanumerical=(( (float)alphanumericalCounter/ (float)decodedRows )*100);
        /* lastly, we print the formated result */
        printf( "Match = %.2f%% Deciphered String = %s\n", percentageAlphanumerical, decodedString );
        if( percentageAlphanumerical > percentageAlphanumerical_Max ){ percentageAlphanumerical_Max= percentageAlphanumerical; }
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
    initialiseIntArray( inputString_original, INIT_NUM );
    initialiseIntArray( inputString_enconded, INIT_NUM );

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
    printEntireArray_Horizontally_FULL( inputString_enconded );
    printf( "\n\n" );
    printf( "Deciphering...\n" );
    printf( "...\n" );
    printf( "Deciphered:\n" );
    decipherCode( inputString_enconded );
    return 0;
}
