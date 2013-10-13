/* Created By: Jason MacLafferty
* Date of Creation: May 2013
* Description: Implement a dynamic, full-blown string data type for C
* Filename: String.h */

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED
#include <stdio.h>

typedef struct string_t
{
    char* char_array;
    int length; /* number of chars in the array--excluding the terminating null character */
    int capacity; /* number of bytes currently allocated for the associated char array */
} string_t;

string_t* string_init(void); /* allocates memory for and returns a pointer to a string object of default size */

string_t* string_cust_init(int initial_size);

void string_destroy(string_t* str);

void string_print(string_t* str, int add_new_line);

#define string_puts(str) (string_print(str, 1))

int string_equal(const string_t* str1, const string_t* str2);

void string_copy_sptr(string_t* dest, const string_t* source);

void string_copy_cptr_sptr(string_t* dest, const char* source);

void string_concat(string_t* str1, const string_t* str2);

void string_tolower(string_t* str);

void string_toupper(string_t* str);

void string_remove_nonalpha(string_t* str);

int string_isalpha(const string_t* str);

int string_isalphanum(const string_t* str);

int string_isnonalpha(const string_t* str);

int string_toint(const string_t* str);

int string_equal_cstring(const string_t* str1, const char* str2);

int string_is_int(const string_t* str);

void string_fgets(string_t* dest_str, int len, FILE* strm);

#define string_fputs(str, strm) (fputs(str->char_array, strm))

string_t* string_scan_s(void);

void string_scan2_s(string_t* dest);

string_t* string_get_slice(const string_t* source, int beg_slice_indx, int end_slice_indx);

void string_copy_range(string_t* dest, const string_t* source, int src_strt_idx, int num_to_copy);

int string_in(string_t* str_to_search, char* str_to_find);

int string_in2(string_t* str_to_search, string_t* str_to_find);

int string_find_cstr(string_t* str_to_search, char* str_to_find, int search_strt_pos);

int string_find(string_t* str_to_search, string_t* str_to_find, int search_strt_pos);

void string_set_range(string_t* dest, char* replacement_str, int start_pos, int end_pos);

void string_set_range2(string_t* dest, string_t* replacement_str, int start_pos, int end_pos);

int string_replace(string_t* dest, char* str_to_replace, char* replacement_text);

int string_replace2(string_t* dest, string_t* str_to_replace, string_t* replacement_text);

#endif /* STRING_H_INCLUDED */
