





/****************************************************************************************************
                ASSUME THE OUTPUT FROM CIPHER :
                A BINARY SEQUENCE FOLLOWED BY -1s
                ALL THE WAY UP TO AND INCLUDING 100
****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_LENGTH_USER_INPUT 50        // Max length of string
#define POSITIVE 1             			// Mimicks boolean
#define NEGATIVE 0            			// Mimicks boolean
#define BEGINNING_ARRAY 0   			// Starting point of arrays 
#define INIT_NUM 0            			// Digit to initialise arrays with 
#define INIT_NUM_DECIPHER 0   			// Digit to initialise the decipher arrays with 
#define SIZE_BYTE 8          			// Size of byte 
#define SIZE_BYTE_ARRAY 7    			// Number used when traversing arrays 
#define SIZE_NIBBLE 4        			// Size of nibble 

/*
Global variables
*/
int decodedRows = 0; // The rows we will figure out to be in our decoded array
float percentageAlphanumerical_Max = 0; // The rows we will figure out to be in our decoded array

/* Define the functions */
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int init );
void print_arrayHorizontally_Entire( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void counting_theBits( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber, unsigned int boolean_int );
void flipAnd_addOne( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber );

int encode_onFlippingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
int encode_onSwappingNibbles( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp );
void decipher_Code( unsigned int encodedSequences[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] );
void decipher_NibbleSwap( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );
void decipher_BitSwap( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );
void decipher_BitFlip( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] );



/***************************************************************************************************
							HERE : 
/***************************************************************************************************

/***************************************************************************************************
count theBITS takes and array of integers, which it traveses using a for loop.
The variable row counter in its parametres serves as the row, and the for loop index variable j will do as the columns.
As it goes, each makes a power notation of 2^j for each entry that == 1
it adds it to the parametre passed, valueNumber
and finally, it prints it out as a negative or a positive. Depending n the valye of boolean type int. Also in the parametre.
***************************************************************************************************/
void counting_theBits( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber, unsigned int boolean_int )
{
    /*
    for loop checks the bits for 1s, making the math
    */
    for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
    {
        if( intArray[ counterRows ][ j ]== 1 ){ valueNumber+= pow( 2,j ); }
    }
}

/************************************************************************************************************************
flip theBITS add aONE is a two step function
first, it takes the array given. it will traverse a single row in it (the one matching the letter currently on) using row counter as it's anchor
it will create another array, which will be given the opposite values to the one given; " flipping the bits "
finally, it will perform a bit wise +1 operation on the new array.
the vlaue valueNumber is given only so that it may then be passed to the function : count theBITS
*************************************************************************************************************************/
void flipAnd_addOne( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int valueNumber )
{
    unsigned int whileLoop_condition= 1; // The condition, if a bit is 0 then adding a one will not give us another one, thus stopping the summation
    unsigned int whileLoop_counter= 0; // To count the columns in the while loop
    unsigned int inputString_flip4negative[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence

    initialiseAn_intArray( inputString_flip4negative, INIT_NUM );    // initialise with zeroes

    /*
    for loop flips all the bits of the sequence above and saves them in another 2D array
    */
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


    /*
    while loop will add the bit sequence of encoded by 1
    */
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

/************************************************************************************************************************************
print_arrayHorizontally_Entire will take the array, go through it, and print its values in a horizontal format
WILL PRINT ALL 100 CHARACTERS, as it is asked for in the specifications : with a -1 filling the empty spots
************************************************************************************************************************************/
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

/************************************************************************************************************************************
 initialiseAn_intArray will take an array and set all its values to zero
************************************************************************************************************************************/
int initialiseAn_intArray( unsigned int intArray[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int init )
{
    /*
    For loop initialises 2D array with zeroes
    */
    for( int i= 0; i< MAX_LENGTH_USER_INPUT; i++)
    {
        for( int j= 0; j< SIZE_BYTE; j++)
        {
            intArray[ i ][ j ]= init;
        }
    }
    return ( intArray );
}

/************************************************************************************************************
function takes as parametre the two 2d arrays and two integers.
it encodes the original, by filling the encoded array with the opposite values compared to the original.
Then it checks if its posiive or negative, by checkng the leftmost sign,
given that decision, we move on to the next function : flip and add one,
or jump to the last function : count theBITS
************************************************************************************************************/
int encode_onFlippingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int valueNumber= 0;
    unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

    /*
    for loop flips  all the bits of the sequence above
    */
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

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
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

/************************************************************************************************************
function takes as parametre the two 2d arrays and two integers.
Given the original array, it fills the spaces in the array 'encoded' by reading and copying the bits in reverse order
then it checks whether or not the lfetmost digit is 1 or 0, representing negative or positive sign.
chossing, thus, which function to jump to afterwards based on that realisation
************************************************************************************************************/
int encode_onSwappingBits( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int valueNumber= 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight= BEGINNING_ARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft= SIZE_BYTE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle= SIZE_NIBBLE;    // The value used to traverse the n=8 arrays starting from the middle

    /*
    while loop create the new array by comparing the orginal's values
    */
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

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
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

/************************************************************************************************************
Function takes two arrays and two integers. It grabs the encoded array and fillts its values with
the same as the originals; however, it divides the original's in nibbles (groups of 4 bits) and swaps
them about. Then it checks whetehr or not the leftmost digit is 1 or a 0, marking negative/positive.
Afterwards, it calls on the next functions.
************************************************************************************************************/
int encode_onSwappingNibbles( unsigned int userInput_original[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], unsigned int userInput_encoded[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ], int counterRows, unsigned int temp )
{
    unsigned int valueNumber= 0;          // The value which holds the sum of all the 1s in the bit sequence
    unsigned int traverseRight= BEGINNING_ARRAY;         // the value used to traverse the n=8 arrays from the right
    unsigned int traverseLeft= SIZE_BYTE_ARRAY;    // The value used to traverse the n=8 arrays from the left
    unsigned int traverseMiddle= SIZE_NIBBLE;    // The value used to traverse the n=8 arrays starting from the middle
    unsigned int inputString_flip4negative[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ];   // Holds the flipped bits of the sequence in case we need to find the negative integer of a bit sequence
    unsigned int whileLoop_condition= 1;
    unsigned int whileLoop_counter= 0;

    initialiseAn_intArray( inputString_flip4negative, INIT_NUM );

    /*
    for loop create the new array by comparing the orginal's values in the 1st half
    */
    for( int j= ( SIZE_BYTE_ARRAY ); j>= SIZE_NIBBLE; j-- )
    {
        if( userInput_original[ counterRows ][ traverseMiddle ]== 1 )
        {
            userInput_encoded[ counterRows ][ traverseRight ]= 1;
            //printf( "%d", userInput_encoded[ counterRows ][ traverseRight ] );
        }
        else
        {
            userInput_encoded[ counterRows ][ traverseRight ]= 0;
            //printf( "%d", userInput_encoded[ counterRows ][ traverseRight ] );
        }
        traverseRight++;
        traverseMiddle++;
    }
    /*
    for loop create the new array by comparing the orginal's values in the 2nd half
    */
    for( int j= 0; j< SIZE_NIBBLE; j++ )
    {
        if( userInput_original[ counterRows ][ j ]== 1 )
        {
            userInput_encoded[ counterRows ][ j+ SIZE_NIBBLE ]= 1;
            //printf( "%d", userInput_encoded[ counterRows ][ traverseRight ] );
        }
        else
        {
            userInput_encoded[ counterRows ][ j+ SIZE_NIBBLE ]= 0;
            //printf( "%d", userInput_encoded[ counterRows ][ traverseRight ] );
        }
    }

    /*
    If statement checks if we have a positive or a negative in the left most digit of out 8-bit sequence
    */
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

/************************************************************************************************************************************
decipher code pretends we know nothing about the othe rprograms, save the 3 types of ciphering that could have been done, and the encoded message.
Since we know each character is ade up of a byte, we can also skip checking for that.
How many characters are there in the sentence... First we must find out the total amount of elements in the array
Then we must fin dout the total amount of rows
************************************************************************************************************************************/
void decipher_Code( unsigned int encodedSequences[ MAX_LENGTH_USER_INPUT ][ SIZE_BYTE ] )
{
    /*
    We know the ciphering stops when the -1 starts, so we can copy the elements
    into another array, dividing each row in bytes, and stopping when we reach a -1
    We know the size of the array given is MAX_LENGTH_USER_INPUT (101); we use that to obtain a reach rom 0 to 100.
    We know each byte is 8 bits, we use that to obtain the colums
    All that said,
    first, we must find out how many bits are in the array.
    we know the bits stop when the -1 starts
    let's count them in a very inefficient way like we used to do at the beginning of 2402
    */
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
    unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ];
    /*
    Now that we have the exact amount of rows as characters in the sentence,
    we initialise the array with zeroes, instead of -1
    */
    for( int i= 0; i< decodedRows; i++ )
    {
        for( int j= 0; j<SIZE_BYTE; j++ )
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
    /*
    Now that we have a clean array. we need to reverse the process for each cipher we did
    */
    decipher_BitFlip( inputString_decoded );
    decipher_BitSwap( inputString_decoded );
    decipher_NibbleSwap( inputString_decoded );
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
void decipher_NibbleSwap( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
{
    /*
    What did Nibble Swap do ?
        Nibble Swap took the binary sequence and swaped the nibbles
        by dividing the byte in two groups of four bits each
    */
    /*
    This array will be the temporary that we will play with
    */
    unsigned int inputString_decoded_NibbleSwap[ decodedRows ][ SIZE_BYTE ];
    /*
    we initialise the array with the values of inputString_decoded
    breaking apart the nibbles and switching them
    Having thus two for loop, dividing both halfs
    */
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
            /* the minus one marks where we left off in the last loop */
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
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
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
void decipher_BitSwap( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
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
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
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
void decipher_BitFlip( unsigned int inputString_decoded[ decodedRows ][ SIZE_BYTE ] )
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
        for( int j= ( SIZE_BYTE_ARRAY ); j>= 0; j-- )
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
    decipher_Code( userInput_encoded );
    return 0;
}
