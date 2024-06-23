#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ==================== LemonadeChange
    Given an integer array bills where bills[i] is the bill the ith customer pays, 
    return true if you can provide every customer with the correct change, or false otherwise.
==================== */
bool LemonadeChange( int * bills, int billsSize );

/* ==================== Main
    Function called when you run the program. Calls other functions.
==================== */
int main( void ) {
    int bills[5] = { 5, 5, 5, 10, 20 };
    int billsSize = 5;

    if ( LemonadeChange( bills, billsSize ) ) {
        printf( "True\n" );
    } else {
        printf( "False\n" );
    }
    return 0;
}

bool LemonadeChange( int * bills, int billsSize ) {
    int i = 0;
    int notas10 = 0;
    int notas5 = 0;

    while ( i < billsSize ) {
        switch ( bills[i] ) {
            case 5:
                notas5++;
                break;
            case 10:
                if ( notas5 > 0 ) {
                    notas5--;
                    notas10++;
                } else {
                    return false;
                }
                break;
            case 20:
                if ( notas5 > 0 && notas10 > 0 ) {
                    notas5--;
                    notas10--;
                } else if ( notas5 >= 3 ) {
                    notas5 = notas5 - 3;
                } else {
                    return false;
                }
                break;
            default:
                return false;
        }
        i++;
    }
    return true;
}
