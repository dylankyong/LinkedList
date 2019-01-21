// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>
#include <plib.h>

// User libraries
#include "LinkedList.h"
#define MIDDLE
// **** Set any macros or preprocessor directives here ****

// **** Declare any data types here ****

// **** Define any module-level, global, or external variables here ****

// **** Declare any function prototypes here ****

int main()
{
    BOARD_Init();
    printf("\r\nWelcome to the LinkedList testing suite\r\n");
    //
    // Your testing code goes after here
    //
    static char *alpha = "alpha";
    static char *bravo = "bravo";
    static char *charlie = "charlie";
    static char *delta = "delta";
    static char *echo = "echo";
    static char *foxtrot = "foxtrot";
    static char *golf = "golf";
    static char *hotel = "hotel";
    static char *homes = "homes";
    static char *horse = "horse";
    static char *hersh = "hersh";

    ListItem *testList;
    int status;

    //initialization test
    testList = LinkedListNew(alpha);
    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);

    //end placement test
LinkedListCreateAfter(testList, foxtrot);
LinkedListCreateAfter(testList, golf);
LinkedListCreateAfter(testList, delta);
LinkedListCreateAfter(testList, charlie);
LinkedListCreateAfter(testList, echo);
LinkedListCreateAfter(testList, bravo);

    //testList = LinkedListCreateAfter(testList, hotel);
    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);

    //middle placement test
#ifdef MIDDLE
   
    //second end placement test
    //printf("we at %s\n", testList->data); //location test
    testList = LinkedListCreateAfter(testList, hotel);
    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);

    //swap data test
    //printf("we at %s\n", testList->data); //location test
    status = LinkedListSwapData(testList, testList->previousItem->previousItem);
    printf("Swap status: %u\n", status);
    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);

    //swap data test 2
    printf("we at %s\n", testList->data); //location test
    status = LinkedListSwapData(testList, testList->nextItem->nextItem);
    printf("Swap status: %u\n", status);
    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);

    //sort test
    testList = LinkedListCreateAfter(testList, NULL);
    testList = LinkedListCreateAfter(testList, NULL);
    testList = LinkedListCreateAfter(testList, NULL);
    testList = LinkedListCreateAfter(testList, hersh);
    testList = LinkedListCreateAfter(testList, homes);
    testList = LinkedListCreateAfter(testList, horse);
    testList = LinkedListCreateAfter(testList, NULL);
    testList = LinkedListCreateAfter(testList, NULL);
    testList = LinkedListCreateAfter(testList, hersh);
    testList = LinkedListCreateAfter(testList, NULL);


    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);
    status = LinkedListSort(testList);
    printf("Sort status: %u\n", status);

    status = LinkedListPrint(testList);
    printf("Print status: %u\n", status);
#endif
    // You can never return from main() in an embedded system (one that lacks an operating system).
    // This will result in the processor restarting, which is almost certainly not what you want!
    while (1);
}