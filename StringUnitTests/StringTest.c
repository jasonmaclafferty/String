#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "StringTest.h"
#include "String.h"

/* string data type tests */

void start_testing(void)
{
    test_string_equal();
    test_string_copy_cptr_sptr();
    test_string_copy_sptr();
    test_string_concat();
    test_string_tolower();
    test_string_toupper();
    test_string_equal_cstring();
    test_string_is_int();
    test_string_remove_nonalpha();
    test_string_toint();
    test_string_isnonalpha();
    test_string_isalphanum();
    test_string_get_slice();
    test_string_copy_range();
    test_string_fgets();
    test_string_find_cstr();
    test_string_in();
    test_string_set_range();
    test_string_replace();
}

void test_string_equal(void)
{
    string_t* test_str1     =   string_init();
    string_t* test_str2     =   string_init();
    string_t* test_str3     =   string_init();
    string_t* test_str4     =   string_init();
    string_t* test_str5     =   NULL;
    string_t* test_str6     =   NULL;
    string_t* test_str7     =   string_init();
    string_t* test_str8     =   string_init();
    string_t* test_str9     =   string_init();

    string_copy_cptr_sptr(test_str1, "A person is...");
    string_copy_cptr_sptr(test_str2, "Who are you?");
    string_copy_cptr_sptr(test_str3, "Who are you?");
    string_copy_cptr_sptr(test_str4, "Something random here please.");
    string_copy_cptr_sptr(test_str7, "Something random here please. I need all I can get.");

    assert(string_equal(test_str2, test_str3));
    assert(string_equal(test_str5, test_str6));      /* Two NULL string objects should be equal */
    assert(string_equal(test_str5, test_str1) == 0); /* NULL && !NULL = False */
    assert(string_equal(test_str1, test_str2) == 0);
    assert(string_equal(test_str4, test_str7) == 0); /* two strings of different lengths should not be equal */
    assert(string_equal(test_str8, test_str9));      /* Two 0-length strings should be equal. */

    string_destroy(test_str1);
    string_destroy(test_str2);
    string_destroy(test_str3);
    string_destroy(test_str4);
    string_destroy(test_str7);
    string_destroy(test_str8);
    string_destroy(test_str9);
}

void test_string_copy_sptr(void)
{
    string_t* test_str1         =   string_cust_init(30);
    string_t* test_str2         =   string_cust_init(30);
    string_t* test_str3         =   string_cust_init(30);
    string_t* test_str4         =   string_cust_init(30);
    string_t* test_str5         =   string_cust_init(30);
    string_t* test_str6         =   string_cust_init(30);
    string_t* test_str7         =   NULL;
    string_t* test_str8         =   NULL;
    string_t* test_str9         =   string_cust_init(5);
    string_t* test_str9_temp    =   string_init();
    string_t* test_str10        =   NULL;

    string_copy_cptr_sptr(test_str1, "abcdefghijklmnop");
    string_copy_cptr_sptr(test_str2, "qrstuvwxyz");
    string_copy_cptr_sptr(test_str3, "aJPerXfun.exe");
    string_copy_cptr_sptr(test_str9_temp, "This string is way too long for test_str9. I am completely positive.");

    string_copy_sptr(test_str4, test_str1);
    assert(string_equal(test_str4, test_str1)); /* The first 3 tests test function behavior with proper input. */

    string_copy_sptr(test_str5, test_str2);
    assert(string_equal(test_str5, test_str2));

    string_copy_sptr(test_str6, test_str3);
    assert(string_equal(test_str6, test_str3));

    string_copy_sptr(test_str7, test_str8);
    assert(test_str7 == NULL && test_str8 == NULL); /* copying a NULL to a NULL should do nothing. */

    string_copy_sptr(test_str8, test_str1); /* copying a valid string to a NULL string object should not do */
    assert(test_str8 == NULL);              /* anything either. */

    string_copy_sptr(test_str9, test_str9_temp); /* test the ability of string_copy_sptr to reallocate memory for */
    assert(string_equal(test_str9, test_str9_temp)); /* the destination. */

    string_copy_sptr(test_str1, test_str8); /* try copying a NULL string object to a non-NULL one. */
    assert(string_equal_cstring(test_str1, "abcdefghijklmnop"));

    string_copy_sptr(test_str9, test_str10); /* copying a 0-length string object should do nothing. */
    assert(string_equal(test_str9, test_str9_temp));

    string_destroy(test_str1);
    string_destroy(test_str2);
    string_destroy(test_str3);
    string_destroy(test_str4);
    string_destroy(test_str5);
    string_destroy(test_str6);
    string_destroy(test_str9);
    string_destroy(test_str9_temp);
}

void test_string_copy_cptr_sptr(void) /* whitebox testing is absolutely necessary for this function */
{                                     /* to be certain one of the most important functions is working. */
    string_t* test_str1;              /* copying from a char array to a string object is a critical necessity */
    string_t* test_str2;
    string_t* test_str3;
    string_t* test_str4;
    string_t* test_str5     =   NULL;
    char* test5             =   NULL;
    string_t* test_str6;

    test_str1 = string_init();
    string_copy_cptr_sptr(test_str1, "Jason is working now!");
    assert(strcmp(test_str1->char_array, "Jason is working now!") == 0);
    string_destroy(test_str1);

    test_str2 = string_init();
    string_copy_cptr_sptr(test_str2, "Do I like this? I am sure I do.");
    assert(strcmp(test_str2->char_array, "Who are you?") != 0);
    string_destroy(test_str2);

    test_str3 = string_cust_init(30);
    string_copy_cptr_sptr(test_str3, "C is a programming language. A very powerful one. I like it. Do you?");
    /* CRASH at line 144 */
    assert(strcmp(test_str3->char_array, "C is a programming language. A very powerful one. I like it. Do you?") == 0);
    string_destroy(test_str3);

    test_str4 = string_init();
    string_copy_cptr_sptr(test_str4, "");
    assert(strcmp(test_str4->char_array, "") == 0);
    string_destroy(test_str4);

    string_copy_cptr_sptr(test_str5, test5);
    assert(test_str5 == NULL && test5 == NULL);

    test_str6 = string_cust_init(1);
    string_copy_cptr_sptr(test_str6, "abcdefghijjiklmnopqrstuvwxyz");
    assert(string_equal_cstring(test_str6, "abcdefghijjiklmnopqrstuvwxyz"));
    string_destroy(test_str6);
}

void test_string_concat(void)
{
    string_t* test_str1         =   string_cust_init(1);
    string_t* test_str1_copy    =   string_init();
    string_t* test_str2         =   string_init();
    string_t* test_str3         =   string_init();
    string_t* test_str4         =   NULL;
    string_t* test_str5         =   NULL;
    string_t* test4_expected    =   string_init();

    string_copy_cptr_sptr(test_str2, "Test information. Please keep it a secret!!!");

    string_copy_cptr_sptr(test_str3, "More confidential info for you to keep to yourself.");

    string_concat(test_str1, test_str2);            /* Test 1 : Try a concatenation onto an almost empty string object */
    assert(string_equal(test_str1, test_str2));

    string_concat(test_str4, test_str5);            /* Test 2 : Try concatenating Two NULL string objects */
    assert(test_str4 == NULL);

    string_copy_sptr(test_str1_copy, test_str1);   /* Test 3 : Try a NULL and a non-NULL */

    string_concat(test_str1, test_str5);
    assert(string_equal(test_str1, test_str1_copy));

    string_copy_cptr_sptr(test4_expected,
    "Test information. Please keep it a secret!!!More confidential info for you to keep to yourself."); /* Test 4 */

    string_concat(test_str2, test_str3);           /* Try a regular concatenation */
    assert(string_equal(test_str2, test4_expected));

    string_destroy(test_str1);
    string_destroy(test_str1_copy);
    string_destroy(test_str2);
    string_destroy(test_str3);
    string_destroy(test4_expected);
}

void test_string_tolower(void)
{
    string_t* test1_str     =   NULL;
    string_t* test2_str     =   string_init();
    string_t* test3_str     =   string_init();
    string_t* test4_str     =   string_init();

    string_tolower(test1_str);
    assert(test1_str == NULL);

    string_copy_cptr_sptr(test2_str, "This is test1.");
    string_tolower(test2_str);
    assert(string_equal_cstring(test2_str, "this is test1."));
    string_destroy(test2_str);

    string_copy_cptr_sptr(test3_str, "AbCddd.#@#.HLroBerTs?><}\n");
    string_tolower(test3_str);
    assert(string_equal_cstring(test3_str, "abcddd.#@#.hlroberts?><}\n"));
    string_destroy(test3_str);

    string_tolower(test4_str);
    assert(string_equal_cstring(test4_str, ""));
    string_destroy(test4_str);
}

void test_string_toupper(void)
{
    string_t* test1_str     =   NULL;
    string_t* test2_str     =   string_init();
    string_t* test3_str     =   string_init();
    string_t* test4_str     =   string_init();

    string_toupper(test1_str);
    assert(test1_str == NULL);

    string_copy_cptr_sptr(test2_str, "This is test1.");
    string_toupper(test2_str);
    assert(string_equal_cstring(test2_str, "THIS IS TEST1."));
    string_destroy(test2_str);

    string_copy_cptr_sptr(test3_str, "AbCddd.#@#.HLroBerTs?><}\n");
    string_toupper(test3_str);
    assert(string_equal_cstring(test3_str, "ABCDDD.#@#.HLROBERTS?><}\n"));
    string_destroy(test3_str);

    string_toupper(test4_str);
    assert(string_equal_cstring(test4_str, ""));
    string_destroy(test4_str);
}

void test_string_remove_nonalpha(void)
{
    string_t* test1_str     =   NULL;
    string_t* test2_str     =   string_init();
    string_t* test3_str     =   string_init();
    string_t* test4_str     =   string_init();
    string_t* test5_str     =   string_init();
    string_t* test6_str     =   string_init();

    string_remove_nonalpha(test1_str);
    assert(test1_str == NULL);

    string_copy_cptr_sptr(test2_str, "!@#>:;\"");
    string_remove_nonalpha(test2_str);
    assert(string_equal_cstring(test2_str, ""));
    string_destroy(test2_str);

    string_copy_cptr_sptr(test3_str, "computers");
    string_remove_nonalpha(test3_str);
    assert(string_equal_cstring(test3_str, "computers"));
    string_destroy(test3_str);

    string_copy_cptr_sptr(test4_str, "Compu,ters.");
    string_remove_nonalpha(test4_str);
    assert(string_equal_cstring(test4_str, "Computers"));
    string_destroy(test4_str);

    string_copy_cptr_sptr(test5_str, "   ");
    string_remove_nonalpha(test5_str);
    assert(string_equal_cstring(test5_str, ""));

    string_copy_cptr_sptr(test5_str, "\t");
    string_remove_nonalpha(test5_str);
    assert(string_equal_cstring(test5_str, ""));
    string_destroy(test5_str);

    string_remove_nonalpha(test6_str);
    assert(string_equal_cstring(test6_str, ""));
    string_destroy(test6_str);
}

void test_string_isalpha(void)
{
    string_t* test_str1     =   string_init();
    string_t* test_str2     =   string_init();
    string_t* test_str3     =   string_init();
    string_t* test_str4     =   NULL;

    assert(!string_isalpha(test_str4)); /* A null string object is not alphabetical */

    assert(!string_isalpha(test_str1)); /* a zero length string object is not either */

    string_copy_cptr_sptr(test_str1, "A person");
    assert(string_isalpha(test_str1));
    string_destroy(test_str1);

    string_copy_cptr_sptr(test_str2, "Who are you?");
    assert(!string_isalpha(test_str2));
    string_destroy(test_str2);

    string_copy_cptr_sptr(test_str3, "@!+jason");
    assert(!string_isalpha(test_str3));
    string_destroy(test_str3);
}

void test_string_isalphanum(void)
{
    string_t* test1_str     =   NULL;
    string_t* test2_str     =   string_init();
    string_t* test_str3     =   string_init();

    assert(!string_isalphanum(test1_str)); /* a NULL string_t* is not defined to be alphanumerical. */

    string_copy_cptr_sptr(test2_str, "A1bz39");
    assert(string_isalphanum(test2_str));
    string_destroy(test2_str);

    assert(!string_isalphanum(test_str3)); /* a 0-length string is not alphanumerical. */

    string_copy_cptr_sptr(test_str3, "#@#ac5");
    assert(!string_isalphanum(test_str3));
    string_destroy(test_str3);
}

void test_string_isnonalpha(void)
{
    string_t* test1_str     =   string_init();
    string_t* test2_str     =   string_init();
    string_t* test3_str     =   string_init();
    string_t* test4_str     =   NULL;
    string_t* test5_str     =   string_init();

    string_copy_cptr_sptr(test1_str, "Hello World");
    assert(!string_isnonalpha(test1_str));
    string_destroy(test1_str);

    string_copy_cptr_sptr(test2_str, "Hello World!!!");
    assert(!string_isnonalpha(test2_str));
    string_destroy(test2_str);

    string_copy_cptr_sptr(test3_str, "195@#\t");
    assert(string_isnonalpha(test3_str));
    string_destroy(test3_str);

    assert(string_isnonalpha(test4_str)); /* A NULL string is nonalphabetical. */

    assert(string_isnonalpha(test5_str)); /* A 0-length string is nonalphabetical too. */
    string_destroy(test5_str);
}

void test_string_toint(void)
{
    string_t* test1_str     =   string_init();
    string_t* test2_str     =   NULL;
    string_t* test3_str     =   string_cust_init(5);
    string_t* test4_str     =   string_cust_init(10);
    string_t* test5_str     =   string_cust_init(10);
    string_t* test6_str     =   string_init();

    string_copy_cptr_sptr(test1_str, "10");
    assert(string_toint(test1_str) == 10);

    assert(string_toint(test2_str) == -1); /* a null pointer is not considered a meaningful integer. */

    string_copy_cptr_sptr(test3_str, "#1@59");
    assert(string_toint(test3_str) == -3); /* not a valid integer */

    string_copy_cptr_sptr(test4_str, "1.1");
    assert(string_toint(test4_str) == -3); /* floating point values are not integers. */

    string_copy_cptr_sptr(test5_str, "1259103");
    assert(string_toint(test5_str) == 1259103);

    assert(string_toint(test6_str) == -2); /* A 0-length string cannot be converted to an integer. */

    string_destroy(test1_str);
    string_destroy(test3_str);
    string_destroy(test4_str);
    string_destroy(test5_str);
    string_destroy(test6_str);
}

void test_string_equal_cstring(void)
{
    string_t* test_str1     =   NULL;
    char* test_cstr1        =   NULL;
    char test_cstr2[]       =   "Jason, who are you?";
    char test_cstr3[]       =   "I am a person too!";
    char test_cstr4[]       =   "Who are you?";
    string_t* test_str2     =   string_init();
    string_t* test_str3     =   string_init();
    string_t* test_str4     =   string_init();
    string_t* test_str5     =   string_init();

    assert(string_equal_cstring(test_str1, test_cstr1) == 0);    /* compare a NULL string_t* and a NULL char* */
    assert(string_equal_cstring(test_str1, test_cstr3) == 0);    /* compare a NULL string_t* and a non-NULL char* */

    string_copy_cptr_sptr(test_str2, "Jason, who are you?");
    string_copy_cptr_sptr(test_str3, "Think about such things.");
    string_copy_cptr_sptr(test_str4, "Who are you?");

    assert(string_equal_cstring(test_str2, test_cstr1) == 0);    /* compare a non-NULL string_t* and a NULL char* */
    assert(string_equal_cstring(test_str2, test_cstr2));         /* test_cstr2 && test_str2 should equal True */
    assert(string_equal_cstring(test_str4, test_cstr4));         /*                " */
    assert(string_equal_cstring(test_str3, test_cstr3) == 0);    /* test_str3 != test_cptr3 */
    assert(!string_equal_cstring(test_str5, "C programming."));  /* Try 0-length string object and non-0-length c string. */
    assert(!string_equal_cstring(test_str5, test_cstr1));        /* Try 0-length string object and NULL c string. */

    string_destroy(test_str2);
    string_destroy(test_str3);
    string_destroy(test_str4);
    string_destroy(test_str5);
}

void test_string_is_int(void)
{
    string_t* test1_str     =   string_init();
    string_t* test2_str     =   string_init();
    string_t* test3_str     =   string_init();
    string_t* test4_str     =   NULL;
    string_t* test5_str     =   string_cust_init(5);

    string_copy_cptr_sptr(test1_str, "10");
    assert(string_is_int(test1_str));
    string_destroy(test1_str);

    string_copy_cptr_sptr(test2_str, "-29");
    assert(string_is_int(test2_str));
    string_destroy(test2_str);

    string_copy_cptr_sptr(test3_str, "0.1");
    assert(!string_is_int(test3_str));
    string_destroy(test3_str);

    assert(!string_is_int(test4_str)); /* A NULL string_t* does not represent a valid integer. */

    assert(!string_is_int(test5_str)); /* A zero-length string does not represent a valid integer.*/
    string_destroy(test5_str);
}

void test_string_get_slice(void)
{
    string_t* test_str      =   string_init();
    string_t* test_str2     =   string_init();
    string_t* test1_result  =   NULL;
    string_t* test2_result  =   NULL;
    string_t* test3_result  =   NULL;
    string_t* test6_result  =   NULL;

    string_copy_cptr_sptr(test_str, "This will be a moderately lengthened string for testing.");

    test1_result = string_get_slice(test_str, 5, 10);
    assert(string_equal_cstring(test1_result, "will "));
    string_destroy(test1_result);

    test2_result = string_get_slice(test_str, -1, -1);
    assert(string_equal_cstring(test2_result, "This will be a moderately lengthened string for testing."));
    string_destroy(test2_result);

    test3_result = string_get_slice(test_str, 23, 56);
    assert(string_equal_cstring(test3_result, "ly lengthened string for testing."));
    string_destroy(test3_result);

    assert(string_get_slice(test_str2, 0, 10) == NULL); /* slicing a 0-length string should return NULL. */
    string_destroy(test_str2);

    test6_result = string_get_slice(test_str, 10, -1);
    assert(string_equal_cstring(test6_result, "be a moderately lengthened string for testing."));
    string_destroy(test6_result);

    string_destroy(test_str);
    test_str = NULL;
    assert(string_get_slice(test_str, 1, 5) == NULL); /* attempting to slice a NULL string should return NULL. */
}

void test_string_copy_range(void)
{
    string_t* test_output           =       string_init();
    string_t* test_old_output       =       string_init();
    string_t* test_input            =       string_init();

    string_copy_cptr_sptr(test_input, "Today I will program in C. Will you?");

    /* Test 0 */
    string_copy_range(test_output, test_input, 1, 4);
    assert(string_equal_cstring(test_output, "oday"));

    /* Test 1 */
    string_copy_range(test_output, test_input, 6, 12);
    assert(string_equal_cstring(test_output, "I will progr")); /* FAILING!!! */

    /* Test 2 */
    string_copy_sptr(test_old_output, test_output);
    string_copy_range(test_output, test_input, -1, 9); /* negative indexes are not allowed. */
    assert(string_equal(test_output, test_old_output));

    /* Test 3 */
    string_copy_range(test_output, test_input, 0, -20); /* a negative count is not allowed. */
    assert(string_equal(test_output, test_old_output));

    /* Test 4 */
    /* using a character count that exceeds the number of characters from the specified start index
    to the end of the string defaults to the rest of the characters in the string being copied. */
    string_copy_range(test_output, test_input, 5, 200);
    assert(string_equal_cstring(test_output, " I will program in C. Will you?"));

    /* Test 5 */
    /* Try an out-of-range start index. */
    string_copy_sptr(test_old_output, test_output);
    string_copy_range(test_output, test_input, 1000, 5);
    assert(string_equal(test_output, test_old_output));

    /* Test 6 */
    string_copy_range(test_output, NULL, 5, 1); /* try a source string object of NULL */
    assert(string_equal(test_output, test_old_output));

    /* Test 7 */
    /* See what happens when a count of 0 characters is given. */
    string_copy_range(test_output, test_input, 15, 0);
    assert(string_equal(test_output, test_old_output));

    string_destroy(test_input);
    string_destroy(test_output);
    string_destroy(test_old_output);
}

void test_string_fgets(void)
{
    string_t* test_str1         =       string_init();
    FILE* test_input_file       =       NULL;
    string_copy_cptr_sptr(test_str1, "This is a test string literal.");

    string_fgets(test_str1, -1, stdin);
    assert(string_equal_cstring(test_str1, "This is a test string literal."));

    string_fgets(test_str1, 5, NULL);
    assert(string_equal_cstring(test_str1, "This is a test string literal."));

    string_fgets(NULL, 10, stdin);
    assert(string_equal_cstring(test_str1, "This is a test string literal."));

    string_fgets(test_str1, 0, stdin);
    assert(string_equal_cstring(test_str1, "This is a test string literal."));

    string_destroy(test_str1);
    test_str1 = string_cust_init(10);
    test_input_file = fopen("computing_bucket_list.txt", "r");
    if (test_input_file != NULL)
    {
        string_fgets(test_str1, 15, test_input_file);
        assert(string_equal_cstring(test_str1, "My Computing Bu"));
        fclose(test_input_file);
    }
}

void test_string_in(void)
{
    string_t* test_str      =       string_init();
    string_t* test_str2     =       string_init();
    string_copy_cptr_sptr(test_str, "This is a test string literal.");

    assert(!string_in(test_str, "clock"));
    assert(!string_in(NULL, "jason"));
    assert(!string_in(test_str, NULL));
    assert(string_in(test_str, "This"));
    assert(string_in(test_str, "literal"));
    assert(!string_in(NULL, NULL));
    assert(!string_in(test_str2, NULL));
    assert(!string_in(test_str2, "test"));

    string_destroy(test_str);
    string_destroy(test_str2);
}

void test_string_find_cstr(void)
{
    string_t* test_str      =       string_init();
    string_t* test_str2     =       string_init();
    string_copy_cptr_sptr(test_str, "This is a test string literal.");

    assert(string_find_cstr(test_str, "This", 0) == 0);
    assert(string_find_cstr(test_str, "ing", 5) == 18);
    assert(string_find_cstr(test_str, "J", 0) == -1);
    assert(string_find_cstr(test_str, NULL, 10) == -1);
    assert(string_find_cstr(NULL, "test", 10) == -1);
    assert(string_find_cstr(NULL, NULL, 0) == -1);
    assert(string_find_cstr(test_str2, "abc", 0) == -1);

    string_destroy(test_str);
    string_destroy(test_str2);
}

void test_string_set_range(void)
{
    string_t* test_str      =       string_init();
    string_t* test_str2     =       string_init();
    string_copy_cptr_sptr(test_str, "This is a string for testing.");

    string_set_range(test_str, "phrase", 9, 14);
    assert(string_equal_cstring(test_str, "This is aphraseg for testing."));

    string_set_range(test_str, NULL, 1, 5);
    assert(string_equal_cstring(test_str, "This is aphraseg for testing."));

    string_set_range(NULL, "jason", 5, 20); /* This should not crash. */
    string_set_range(NULL, NULL, 0, 5); /* " */

    string_set_range(test_str2, "a thing", 0, 6);
    assert(string_equal_cstring(test_str2, ""));

    string_set_range(test_str, "A", -1, 5); /* Indexes cannot be negative. */
    assert(string_equal_cstring(test_str, "This is aphraseg for testing."));

    string_set_range(test_str, "an expression", 5, 0); /* The start index cannot be greater than the end index. */
    assert(string_equal_cstring(test_str, "This is aphraseg for testing."));

    string_set_range(test_str, "something here", 0, 0);
    assert(string_equal_cstring(test_str, "shis is aphraseg for testing."));

    /* If strlen(replacement string) > (end index - start index) + 1 then only (end index - start index)
    + 1 characters are replaced in the destination string. */
    string_set_range(test_str, "to use for", 17, 19);
    assert(string_equal_cstring(test_str, "shis is aphraseg to  testing."));

    /* If strlen(replacement string) <= (end index - start index) + 1, then only len(replacement string) number of
    characters will be replaced in the destination string. */
    string_set_range(test_str, "ab", 0, 15);
    assert(string_equal_cstring(test_str, "abis is aphraseg to  testing."));

    /* a single character in the string object can be set by setting start_pos = end_pos */
    string_set_range(test_str, "A", 0, 0);
    assert(string_equal_cstring(test_str, "Abis is aphraseg to  testing."));

    string_set_range(test_str, "X", 19, 19);
    assert(string_equal_cstring(test_str, "Abis is aphraseg toX testing."));

    string_destroy(test_str);
    string_destroy(test_str2);
}

void test_string_replace(void)
{
    string_t* test_str      =       string_init();
    string_t* test_str2     =       string_init();
    string_t* test_str3     =       string_init();
    string_copy_cptr_sptr(test_str, "This is a string expression for unit testing.");
    string_copy_cptr_sptr(test_str3, "a b a b a b a b a b a b a b ab");

    string_replace(NULL, "This", "A"); /* This should not crash. */

    string_replace(test_str, NULL, "B");
    assert(string_equal_cstring(test_str, "This is a string expression for unit testing."));

    string_replace(test_str, "string", NULL);
    assert(string_equal_cstring(test_str, "This is a string expression for unit testing."));

    string_replace(NULL, NULL, NULL); /* This should neither do anything nor crash. */

    string_replace(test_str2, "the", "and"); /* try a zero-lengthened string */
    assert(string_equal_cstring(test_str2, ""));

    string_replace(test_str2, "", ""); /* calling string_replace with all empty strings should do absolutely nothing. */
    assert(string_equal_cstring(test_str2, ""));

    string_replace(test_str, "This", "A");
    assert(string_equal_cstring(test_str, "A is a string expression for unit testing."));

    string_replace(test_str, "unit", "function");
    assert(string_equal_cstring(test_str, "A is a string expression for function testing."));

    /* the following is the currently failing test. */
    while (string_replace(test_str3, "a", "b")); /* replace all occurrences of the letter a in test_str3 */
    assert(string_equal_cstring(test_str3, "b b b b b b b b b b b b b b bb"));

    assert(string_replace(test_str3, "ba", "a") == 0);
    assert(string_equal_cstring(test_str3, "b b b b b b b b b b b b b b bb"));

    string_replace(test_str, "expression", "exp");
    assert(string_equal_cstring(test_str, "A is a string exp for function testing."));

    string_replace(test_str, "exp", "expression");
    assert(string_equal_cstring(test_str, "A is a string expression for function testing."));
}

