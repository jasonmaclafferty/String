#include <stdio.h> #include <stdlib.h>
#include "StringTest.h"
#include "String.h"

#define RUN_IO_TESTS 0

int main(void)
{
    #if RUN_IO_TESTS
    string_t* io_test_str1  =   string_init();
    string_t* io_test_str2  =   NULL;
    string_t* io_test_str3  =   NULL;
    string_t* io_test_str4  =   string_init();
    #endif

    printf("Starting to test.\n\n");
    start_testing();

    /* test IO functions */
    #if RUN_IO_TESTS
    printf("Start testing string data type IO functions.\n");

    /* test string_print */
    printf("Start testing function: string_print.\n");
    string_copy_cptr_sptr(io_test_str1, "Hello World!!!.");
    printf("**** Without a new line. ****\n");
    string_print(io_test_str1, 0); /* print without appending a new line. */
    printf("**** With a new line. ****\n");
    string_print(io_test_str1, 1); /* append a new line to the output. */
    /* try convenient string_print macro. */
    printf("Try a convenient string print macro.\n");
    string_puts(io_test_str1);

    string_destroy(io_test_str1);
    printf("Finished testing function string_print.\n");

    printf("Testing function: string_scan_s.\n");

    /* test string_scan_s */
    printf("Enter 100's of chars...\n");
    io_test_str2 = string_scan_s();
    printf("\nIs the following what was entered?\n");
    string_print(io_test_str2, 0);
    string_destroy(io_test_str2);

    printf("\nPlease enter a few more characters.\n");
    io_test_str3 = string_scan_s();
    printf("\nThe following was received from standard input.\n");
    string_print(io_test_str3, 0);
    string_destroy(io_test_str3);

    printf("\nFinished testing string_scan_s().\n");

    /* test string_scan2_s */
    printf("Testing function: string_scan2_s.\n");
    printf("Please enter any amount of input.\n");
    string_scan2_s(io_test_str4);
    /* display received input. */
    printf("The following was received as input: ");
    string_puts(io_test_str4);

    printf("Please enter a few more characters...\n");
    string_scan2_s(io_test_str4);
    printf("The following was received as input: ");
    string_puts(io_test_str4);

    printf("End of testing for string_scan2_s.\n");
    printf("Completed testing string data type IO functions.\n");
    #endif

    printf("\nCompleted all tests.\n");

    return 0;
}
