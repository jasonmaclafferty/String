/* Created By: Jason MacLafferty
* Date of Creation: May 2013
* Description: Implement a dynamic, full-blown string data type for C.
* Filename: String.c */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "String.h"

/**********************************************************************************
*                                                                                 *
*                                                                                 *
*                          string implementation                                  *
*                                                                                 *
*                                                                                 *
***********************************************************************************/



/** \brief The string data type initializer.
 *
 * \param None
 * \return string_t* A pointer to the newly allocated string object in memory.
 *
 * Initializes a new string object on the heap with an initially-sized internal char array of 200 chars.
 * The initializer function returns a pointer to the new object allocated.
 */
string_t* string_init(void)
{
    string_t* str               =   NULL;
    char* under_lying_array     =   (char*)calloc(200, sizeof(char));

    if (under_lying_array != NULL)
    {
        str = (string_t*)calloc(1, sizeof(string_t));

        if (str != NULL)
        {
            str->char_array             =   under_lying_array;
            str->capacity               =   200;
            str->length                 =   0;
        }
        else
        {
            free(under_lying_array);
        }
    }

    return str;
}

/** \brief Custom initializer for the string data type.
 *
 * \param initial_size int Initial length of the string.
 * \return string_t* A pointer to the new string object.
 *
 * Initializes a new string object to specified initial capacity and returns a pointer to it.
 */
string_t* string_cust_init(int initial_size)
{
    string_t* str               =   NULL;
    char* under_lying_array     =   NULL;

    if (initial_size > 0)
    {
        under_lying_array = (char*)calloc(initial_size, sizeof(char));

        if (under_lying_array != NULL)
        {
            str = (string_t*)calloc(1, sizeof(string_t));

            if (str != NULL)
            {
                str->char_array     =   under_lying_array;
                str->capacity       =   initial_size;
                str->length         =   0;
            }
            else
            {
                free(under_lying_array);
            }
        }
    }

    return str;
}

/** \brief Free the memory allocated for a string.
 *
 * \param str string_t* A pointer to the string to cleanup.
 * \return void Nothing
 *
 * Deallocates the memory allocated for the string object pointed to by 'str'.
 */
void string_destroy(string_t* str)
{
    if (str != NULL)
    {
        free(str->char_array);
        free(str);
    }
}

/** \brief Compares two string objects to see if they contain identical strings.
 *
 * \param str1 const string_t* The first string object for comparison.
 * \param str2 const string_t* The second string object for comparison.
 * \return int A Boolean value indicating equality or a lack of it.
 *
 * Compares two string objects to see if they contain identical strings
 * and returns a Boolean value indicating the result.
 */
int string_equal(const string_t* str1, const string_t* str2)
{
    const char* str1_cptr;
    const char* str2_cptr;
    int return_val = 0;

    if (str1 != NULL && str2 != NULL)
    {
        if (str1->length == str2->length)
        {
            return_val = 1;

            for (str1_cptr = str1->char_array, str2_cptr = str2->char_array;
                 *str1_cptr != '\0' && *str2_cptr != '\0'; str1_cptr++, str2_cptr++)
            {
                if (*str1_cptr != *str2_cptr)
                    return_val = 0; /* strings are not equal */
            }
        }
        else
        {
            return_val = 0; /* strings of different lengths are never equal */
        }
    }
    else if (str1 == NULL && str2 == NULL)
    {
        return_val = 1; /* NULL = NULL */
    }
    else
    {
        return_val = 0; /* not equal */
    }

    return return_val;
}

/** \brief Copies the contents of one string object to another.
 *
 * \param dest string_t* The string object to copy to.
 * \param source const string_t* The string object to copy from.
 * \return void Nothing.
 *
 */
void string_copy_sptr(string_t* dest, const string_t* source) /* add dynamic memory allocation feature here */
{
    char* dest_cptr;
    const char* source_cptr;
    char* temp = NULL;

    if (dest != NULL && source != NULL)
    {
        if (source->length > 0)
        {
            if (dest->capacity < source->length + 1)
            {
                temp = (char*)realloc(dest->char_array, source->length + 51);

                if (temp != NULL)
                {
                    dest->char_array        =       temp;
                    dest->capacity          =       source->length + 51;
                }
            }

            if (dest->capacity >= source->length + 1)
            {
                dest->length = 0;
                for (source_cptr = source->char_array, dest_cptr = dest->char_array; *source_cptr != '\0';
                    source_cptr++, dest_cptr++)
                {
                    *dest_cptr = *source_cptr;
                    dest->length++;
                }
                *dest_cptr = *source_cptr; /* copy the '\0' */
            }
        }
    }
}

/** \brief Copies the contents of a standard C string, a char array, to a string object.
 *
 * \param dest string_t* A pointer to the string object to copy to.
 * \param source const char* A pointer the base of a char array to copy from.
 * \return void Nothing.
 *
 */
void string_copy_cptr_sptr(string_t* dest, const char* source)
{
    int source_pos;
    char* temp = NULL;

    if (dest != NULL && source != NULL)
    {
        if (strlen(source) > 0)
        {
            if (dest->capacity < (int)(strlen(source)) + 1)
            {
                /* allocate space for the new string plus a little more */
                temp = (char*)realloc(dest->char_array, strlen(source) + 51);

                if (temp != NULL)
                {
                    dest->char_array        =       temp;
                    dest->capacity          =       strlen(source) + 51;
                }
            }

            if (dest->capacity >= (int)(strlen(source)) + 1)
            {
                dest->length = 0;
                for (source_pos = 0; source_pos < (int)(strlen(source)); source_pos++)
                {
                    dest->char_array[source_pos] = source[source_pos];
                    dest->length++;
                }

                dest->char_array[source_pos + 1] = '\0'; /* mark the end of the string with a null character */
            }
        }
    }
}

/** \brief Concatenates the contents of one string object onto another.
 *
 * \param str1 string_t* A pointer to the first string object.
 * \param str2 const string_t* A pointer to the second string object.
 * \return void Nothing.
 *
 * Concatenates the contents of str2 onto the end of str1's contents.
 */
void string_concat(string_t* str1, const string_t* str2)
{
    int str1_pos, str2_pos;
    char* temp = NULL;

    if (str1 != NULL && str2 != NULL)
    {
        if (str2->length > 0)
        {
            if (str1->capacity < str1->length + str2->length + 2) /* + 2 for the '\0' characters */
            {
                temp = realloc(str1->char_array, str1->length + str2->length + 52);

                if (temp != NULL)
                {
                    str1->char_array        =       temp;
                    str1->capacity          =       str1->length + str2->length + 52;
                }
            }

            if (str1->capacity >= str1->length + str2->length + 2)
            {
                for (str1_pos = str1->length, str2_pos = 0; str2_pos < str2->length; str1_pos++, str2_pos++)
                {
                    str1->char_array[str1_pos] = str2->char_array[str2_pos];
                    str1->length++;
                }

                str1->char_array[str1_pos] = str2->char_array[str2_pos]; /* copy null char */
            }
        }
    }
}

/** \brief Converts all alphabetical characters in the string to lowercase.
 *
 * \param str string_t* The string object to convert.
 * \return void Nothing.
 *
 */
void string_tolower(string_t* str)
{
    char* str_cptr;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if (*str_cptr >= 'A' && *str_cptr <= 'Z')
                    *str_cptr += 32;
            }
        }
    }
}

/** \brief Converts all lowercase characters in the string to uppercase.
 *
 * \param str string_t* The string to convert.
 * \return void Nothing.
 *
 */
void string_toupper(string_t* str)
{
    char* str_cptr;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if (*str_cptr >= 'a' && *str_cptr <= 'z')
                    *str_cptr -= 32;
            }
        }
    }
}

/** \brief Removes all the of the non-alphabetical characters in a string.
 *
 * \param str string_t* String to remove the undesired characters from.
 * \return void Nothing.
 *
 */
void string_remove_nonalpha(string_t* str)
{
    int str_inner_pos, str_outer_pos;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_outer_pos = 0; str_outer_pos < str->length; str_outer_pos++)
            {
                if (!((str->char_array)[str_outer_pos] >= 'a' && (str->char_array)[str_outer_pos] <= 'z')
                    && !((str->char_array)[str_outer_pos] >= 'A' && (str->char_array)[str_outer_pos] <= 'Z'))
                {
                    for (str_inner_pos = str_outer_pos; str_inner_pos < str->length; str_inner_pos++)
                        (str->char_array)[str_inner_pos] = (str->char_array)[str_inner_pos + 1];
                    str->length--;
                    str_outer_pos--; /* yucky, but otherwise the outer loop will skip one char. */
                }
            }
        }
    }

}

int string_isalpha(const string_t* str)
{
    const char* str_cptr;
    int return_val = 1;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if (!(*str_cptr >= 'a' && *str_cptr <= 'z') && !(*str_cptr >= 'A' && *str_cptr <= 'Z'))
                {
                    return_val = 0; /* str is not purely alphabetical. */
                    break;
                }
            }
        }
    }

    return return_val;
}

/** \brief Tests whether the string object contains strictly alphanumeric characters.
 *
 * \param str const string_t* A pointer to the string object.
 * \return int A Boolean value indicating the success or fail of the evaluation.
 *
 */
int string_isalphanum(const string_t* str)
{
    const char* str_cptr;
    int return_val = 1;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if (!(*str_cptr >= 'a' && *str_cptr <= 'z') && !(*str_cptr >= 'A' && *str_cptr <= 'Z')
                    && !(*str_cptr >= '0' && *str_cptr <= '9'))
                {
                        return_val = 0; /* str is not alphanumeric. */
                        break;
                }
            }
        }
        else
        {
            return_val = 0; /* A 0-length string is not alphanumeric. */
        }
    }
    else
    {
        return_val = 0; /* A NULL string is not strictly alphanumeric. */
    }

    return return_val;
}

/** \brief Returns a Boolean value indicating whether or not the string is strictly non-alphabetical.
 *
 * \param str const string_t* A pointer to the string object.
 * \return int A Boolean value.
 *
 * Note: NULL string_t pointers and 0-length string objects are defined to be non alphabetical.
 */
int string_isnonalpha(const string_t* str)
{
    const char* str_cptr;
    int return_val = 1;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if ((*str_cptr >= 'a' && *str_cptr <= 'z') || (*str_cptr >= 'A' && *str_cptr <= 'Z'))
                {
                    return_val = 0; /* str is NOT non-alphabetical--it's alphabetical */
                    break;
                }
            }
        }
    }

    return return_val; /* return true; str is non-alphabetical */
}

/** \brief Returns the integer corresponding to the specified string form of the integer.
 *
 * \param str string_t* A pointer to the string object to convert.
 * \return int The signed integer equivalent to the string object.
 *
 */
int string_toint(const string_t* str)
{
    int highest_power;
    int return_val;
    const char* str_cptr;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            str_cptr = str->char_array;

            if (string_is_int(str))
            {
                return_val = 0;
                highest_power = strlen(str->char_array) - 1;

                while (*str_cptr != '\0')
                {
                    return_val += (*str_cptr - '0') * (int)pow(10, highest_power);
                    str_cptr++;
                    highest_power--;
                }
            }
            else
            {
                return_val = -3; /* "str" is not a valid integer. */
            }
        }
        else
        {
            return_val = -2; /* "str" is of zero-length and so therefore not an integer */
        }
    }
    else
    {
        return_val = -1; /* "str" is NULL and cannot be converted. */
    }

    return return_val;
}

/** \brief Compares the contents of a string object and a standard C string (char*).
 *
 * \param str1 string_t* A pointer to the string object.
 * \param str2 const char* The C string.
 * \return int A boolean value indicating the presence or lack of equality.
 *
 */
int string_equal_cstring(const string_t* str1, const char* str2)
{
    const char* str1_cptr;
    const char* str2_cptr;
    int return_val = 1;

    if (str1 != NULL && str2 != NULL)
    {
        if (str1->length == (int)(strlen(str2)))
        {
            for (str1_cptr = str1->char_array, str2_cptr = str2; *str1_cptr != '\0'; str1_cptr++, str2_cptr++)
            {
                if (*str1_cptr != *str2_cptr)
                {
                    return_val = 0; /* not equal */
                    break;
                }
            }
        }
        else
        {
            return_val = 0; /* strings of different lengths are never equal */
        }
    }
    else
    {
        return_val = 0; /* at least one of the function arguments is NULL */
    }

    return return_val;
}

/** \brief Prints the string with or without appending a new line character onto the output.
 *
 * \param str string_t* A pointer to the string object to print.
 * \param add_new_line int A boolean value indicating whether or not to append a new line character.
 * \return void Nothing.
 *
 */
void string_print(string_t* str, int add_new_line)
{
    if (str != NULL)
    {
        if (str->length > 0)
        {
            if (add_new_line)
                puts(str->char_array);
            else
                printf("%s", str->char_array);
        }
    }
}

/** \brief Returns a Boolean value indicating whether the string object contains a valid Integer.
 *
 * \param str string_t* A pointer to the string object to check.
 * \return int A boolean value indicating True or False.
 *
 * The finding of any non-digit character--other than a negative in the proper place, is defined to not be an Integer.
 */
int string_is_int(const string_t* str)
{
    const char* str_cptr;
    int return_val = 1;

    if (str != NULL)
    {
        if (str->length > 0)
        {
            for (str_cptr = str->char_array; *str_cptr != '\0'; str_cptr++)
            {
                if (!(*str_cptr >= '0' && *str_cptr <= '9') && *str_cptr != '-')
                {
                    return_val = 0; /* not a valid integer. */
                    break;
                }
            }

            for (str_cptr = str->char_array + 1; *str_cptr != '\0'; str_cptr++)
            {
                if (*str_cptr == '-')
                {
                    return_val = 0; /* not an integer. wrong place for a negative sign. */
                    break;
                }
            }
        }
        else
        {
            return_val = 0; /* A zero-length string is not a valid integer. */
        }
    }
    else
    {
        return_val = 0; /* NULL strings are not valid integers. */
    }

    return return_val;
}

/** \brief Reads in all the characters from the standard input stream and returns them a new string object.
 *
 * \param void No parameters.
 * \return string_t* A pointer to a new string object containing the characters from standard input.
 *
 * This function is intended to be like a safe version of scanf() for the string data type.
 * The internal char array of the string object is reallocated as necessary to hold the data from stdin.
 */
string_t* string_scan_s(void)
{
    string_t* stdin_data = string_init();
    string_scan2_s(stdin_data);

    return stdin_data;
}

/** \brief Reads in all the characters from the standard input stream and returns them as new string object.
 *
 * \param dest string_t* A pointer the string object to store the input in.
 * \return void Nothing.
 *
 * This function is intended to be like a safe version of scanf() for the string data type.
 * The internal char array of the string object is reallocated as necessary to hold the data from stdin.
 */
void string_scan2_s(string_t* dest)
{
    char curr_char;
    char* buffer            =   calloc(200, sizeof(char));
    int sizeof_buffer       =   200;
    int len                 =   0;
    char* temp              =   NULL;

    curr_char = getc(stdin);
    if (buffer != NULL)
    {
        while (curr_char != '\n')
        {
            if (len == sizeof_buffer)
            {
                temp = (char*)realloc(buffer, sizeof_buffer + 50);
                if (temp != NULL)
                {
                    buffer              =       temp;
                    sizeof_buffer       +=      50;
                    strncat(buffer, &curr_char, 1);
                    len++;
                }
                else
                {
                    free(buffer);
                    buffer = NULL;
                    break;
                }
            }
            else
            {
                strncat(buffer, &curr_char, 1);
                len++;
            }

            curr_char = getc(stdin);
        }

        if (buffer != NULL)
        {
            string_copy_cptr_sptr(dest, buffer);
            free(buffer);
        }
    }
}

/** \brief Attempts to imitate the Python slice operator for the string data type.
 *
 * \param source const string_t* A pointer to the string object to slice.
 * \param beg_slice_indx int Beginning slice index.
 * \param end_slice_indx int End slice index.
 * \return string_t* A pointer to the string slice.
 *
 * The function returns a pointer to a new string object containing the slice specified in the following syntax:
 * (1) Slice indexes are consecutively numbered from 0 on up. (2) Slice indexes describe positions between characters
 * in a string like this: "0T1H2I3N4G5" where the integers 0, 1, 2, 3, 4, and 5 represent the slice index positions
 * between the characters in the string "THING".
 * ***Note*** Since C does not support optional function parameters, this function accepts a value of -1 where,
 * the slice index in python would have been blank.
 * The following Python slicing features are implemented as shown below:
 * let x and y both be positive integers where x < y
 * Python: str[x:y]     C: beg_slice_indx = x, end_slice_indx = y
 * Python: str[:]       C: beg_slice_indx = -1, end_slice_indx = -1
 * Python: str[x:]      C: beg_slice_indx = x, end_slice_indx = -1
 * For more information please look up the slice operator in the official Python documentation.
 * See http://docs.python.org for details.
 */
string_t* string_get_slice(const string_t* source, int beg_slice_indx, int end_slice_indx)
{
    string_t* source_slice          =       NULL;
    int bool_copy                   =       0;

    if (source != NULL)
    {
        if (source->length > 0)
        {
            if (beg_slice_indx >= 0 && beg_slice_indx < source->length)
            {
                if (end_slice_indx > 0 && end_slice_indx <= source->length)
                {
                    if (beg_slice_indx < end_slice_indx)
                    {
                        /* perhaps I should allocate enough space for 50 extra chars like everything else? */
                        source_slice = string_cust_init((end_slice_indx - beg_slice_indx) + 1);
                        if (source_slice != NULL)
                        {
                            bool_copy = 1;
                            end_slice_indx--;
                        }
                    }
                }
                else if (end_slice_indx == -1)
                {
                    source_slice = string_cust_init((source->length - beg_slice_indx) + 1);
                    if (source_slice != NULL)
                    {
                        bool_copy           =       1;
                        end_slice_indx      =       source->length -1;
                    }
                }
            }
            else if (beg_slice_indx == -1 && end_slice_indx == -1) /* imitate a python [:] slice operation. */
            {                                                      /* as in a copy of the string. */
                source_slice = string_cust_init(source->length + 1);
                if (source_slice != NULL)
                {
                    bool_copy           =       1;
                    beg_slice_indx      =       0;                  /* char positions in this case. */
                    end_slice_indx      =       source->length - 1; /* not actual python slice indices */
                }
            }

            if (bool_copy)
                string_copy_range(source_slice, source, beg_slice_indx,
                                  (end_slice_indx - beg_slice_indx) + 1);
        }
    }

    return source_slice;
}

/** \brief Copies a specified range from one string object to another.
 *
 * \param dest string_t* A pointer to the string object to copy to.
 * \param source const string_t* A pointer to the source string object.
 * \param src_strt_idx int The index of the first character to copy from the source string object.
 * \param num_to_copy int The number of characters to copy from the source string object.
 * \return void No return value.
 *
 * ***Note*** Characters are copied from the source string object until either the number of characters
 * copied equals the value of num_to_copy or until the end of the source string is reached--whichever
 * comes first.
 */
void string_copy_range(string_t* dest, const string_t* source, int src_strt_idx, int num_to_copy)
{
    char* temp = NULL;
    int dest_pos, source_pos;

    if (dest != NULL && source != NULL)
    {
        if (source->length > 0)
        {
            if (src_strt_idx >= 0 && src_strt_idx < source->length - 1)
            {
                if (num_to_copy > 0)
                {
                    if (num_to_copy > (source->length - src_strt_idx))
                        num_to_copy = source->length - src_strt_idx;

                    if (num_to_copy <= dest->capacity)
                    {
                        dest->length = 0;
                        for (dest_pos = 0, source_pos = src_strt_idx;
                             dest_pos < num_to_copy; dest_pos++, source_pos++)
                        {
                            dest->char_array[dest_pos] = source->char_array[source_pos];
                            dest->length++;
                        }
                        dest->char_array[dest_pos] = '\0';
                    }
                    else
                    {
                        temp = (char*)realloc(dest->char_array, num_to_copy + 51);
                        if (temp != NULL)
                        {
                            dest->char_array        =       temp;
                            dest->capacity          =       num_to_copy + 51;
                            dest->length            =       0;
                            for (dest_pos = 0, source_pos = src_strt_idx;
                                 dest_pos < num_to_copy; dest_pos++, source_pos++)
                            {
                                dest->char_array[dest_pos] = source->char_array[source_pos];
                                dest->length++;
                            }
                            dest->char_array[dest_pos] = '\0';
                        }
                    }
                }
            }
        }
    }
}

/** \brief Provides a wrapper for the standard fgets with additional dynamic memory management features.
 *
 * \param str string_t* A pointer to the string object in which to place the data from the stream.
 * \param len int The number of characters to get from the stream.
 * \param strm FILE* A pointer to the stream to read from.
 * \return void No return value.
 *
 */
void string_fgets(string_t* dest_str, int len, FILE* strm)
{
    char* temp = NULL;

    if (dest_str != NULL && strm != NULL)
    {
        if (len > 0)
        {
            if (len + 2 <= dest_str->capacity) /* + 2 to account for the \0 && \n characters appended by fgets() */
            {
                fgets(dest_str->char_array, len, strm);
                dest_str->length = len;
            }
            else
            {
                temp = (char*)realloc(dest_str->char_array, len + 52);
                if (temp != NULL)
                {
                    dest_str->capacity          =       len + 52;
                    dest_str->char_array        =       temp;

                    fgets(dest_str->char_array, len, strm);
                    dest_str->length = len;
                }
            }
        }
    }
}

/** \brief Imitates the Python "in" operator.
 *
 * \param str_to_search string_t* A pointer to the string object in which to search for the existence of str_to_find.
 * \param str_to_find char* A pointer to the char array (C string) for which to look for in str_to_search.
 * \return int Boolean, 1 for True, 0 for False
 *
 * Returns True if str_to_find was found in str_to_search or False if it was not found.
 */
int string_in(string_t* str_to_search, char* str_to_find)
{
    int ret_val = 0;

    if (str_to_search != NULL && str_to_find != NULL)
    {
        if (str_to_search->length > 0 && strlen(str_to_find) > 0)
        {
            if (string_find_cstr(str_to_search, str_to_find, 0) >= 0)
                ret_val = 1;
        }
    }

    return ret_val;
}

/** \brief Determines whether str_to_find exists in str_to_search.
 *
 * \param str_to_search string_t* A pointer to the string object to search.
 * \param str_to_find string_t* A pointer to the string object to look for.
 * \return int A Boolean value, 1 for True and 0 for False, to indicate whether or not
 * str_to_find was found in str_to_search.
 *
 * This is a simple function wrapper for string_in
 */
int string_in2(string_t* str_to_search, string_t* str_to_find)
{
    return string_in(str_to_search, str_to_find->char_array);
}

/** \brief Searches for the specified C string within the string object and returns its index if found.
 *
 * \param str_to_search string_t* A pointer to the string object to search.
 * \param str_to_find char* A pointer to the C string (char array) to find.
 * \param search_strt_pos int The character position to start searching at.
 * \return int The index of the first character of the string found in the string object. -1 if not found.
 *
 */
int string_find_cstr(string_t* str_to_search, char* str_to_find, int search_strt_pos)
{
    int ret_val = -1, str_to_find_pos, str_to_search_pos;

    if (str_to_search != NULL && str_to_find != NULL)
    {
        if (search_strt_pos >= 0 && search_strt_pos < str_to_search->length)
        {
            if (strlen(str_to_find) > 0 && str_to_search->length > 0)
            {
                str_to_find_pos         =       0;
                str_to_search_pos       =       search_strt_pos;

                while (str_to_search_pos < str_to_search->length)
                {
                    if (str_to_search->char_array[str_to_search_pos] == str_to_find[str_to_find_pos])
                    {
                        ret_val = str_to_search_pos;
                        str_to_find_pos++;
                        str_to_search_pos++;

                        while (str_to_find_pos < (int)strlen(str_to_find) && str_to_search_pos < str_to_search->length)
                        {
                            if (str_to_search->char_array[str_to_search_pos] != str_to_find[str_to_find_pos])
                            {
                                ret_val             =       -1;
                                str_to_find_pos     =       0;
                                break;
                            }

                            str_to_find_pos++;
                            str_to_search_pos++;
                        }

                        if (str_to_find_pos > 0)
                            break;
                    }

                    str_to_search_pos++;
                }
            }
        }
    }

    return ret_val;
}

/** \brief Returns the index of the first occurrence of str_to_find in str_to_search, starting at search_strt_pos.
 *
 * \param str_to_search string_t* A pointer to the string object to search.
 * \param str_to_find string_t* A pointer to the string object whose contents to find in str_to_search.
 * \param search_strt_pos int The index to start the search in str_to_search.
 * \return int The index of the found occurrence or -1 if not found.
 *
 * Provides a function wrapper for string_find_cstr.
 */
int string_find(string_t* str_to_search, string_t* str_to_find, int search_strt_pos)
{
    return string_find_cstr(str_to_search, str_to_find->char_array, search_strt_pos);
}

/** \brief Overwrites a specified range in the string object with a new value.
 *
 * \param dest string_t* A pointer to the string object to change.
 * \param replacement_str char* The C string to overwrite the specified range with.
 * \param start_pos int Character position to start overwriting.
 * \param end_pos int Character position to finish the overwriting.
 * \return void Nothing.
 *
 * If strlen(replacement_str) > (end_pos - start_pos) + 1 then only (end_pos - start_pos) + 1 characters
 * are replaced in the destination. If strlen(replacement_str) <= (end_pos - start_pos) + 1 then only
 * strlen(replacement_str) number of characters are overwritten.
 */
void string_set_range(string_t* dest, char* replacement_str, int start_pos, int end_pos)
{/* add one-character replace test for this function */
    int dest_pos, replacement_str_pos, count_to_write;

    if (dest != NULL && replacement_str != NULL)
    {
        if (start_pos >= 0 && start_pos < dest->length && end_pos >= 0 && end_pos < dest->length)
        {
            if (start_pos < end_pos)
            {
                if ((int)strlen(replacement_str) > (end_pos - start_pos) + 1)
                    count_to_write = (end_pos - start_pos) + 1;
                else
                    count_to_write = (int)strlen(replacement_str);

                for (dest_pos = start_pos, replacement_str_pos = 0; replacement_str_pos < count_to_write;
                    dest_pos++, replacement_str_pos++)
                        dest->char_array[dest_pos] = replacement_str[replacement_str_pos];
            }
            else if (start_pos == end_pos)
            {
                dest->char_array[start_pos] = replacement_str[0];
            }
        }
    }
}

/** \brief Overwrites a specified range in the string object with a new value.
 *
 * \param dest string_t* A pointer to the string object to change.
 * \param replacement_str string_t* The string object whose contents to overwrite the specified range with.
 * \param start_pos int Character position to start overwriting.
 * \param end_pos int Character position to finish the overwriting.
 * \return void Nothing.
 *
 * If replacement_str->length > (end_pos - start_pos) + 1 then only (end_pos - start_pos) + 1 characters
 * are replaced in the destination. If replacement_str->length <= (end_pos - start_pos) + 1 then only
 * replacement_str->length number of characters are overwritten.
 *
 * Provides a function wrapper for string_set_range.
 */
void string_set_range2(string_t* dest, string_t* replacement_str, int start_pos, int end_pos)
{
    string_set_range(dest, replacement_str->char_array, start_pos, end_pos);
}

/** \brief Replaces the first occurrence of str_to_replace with replacement_text in the string object pointed to by dest.
 *
 * \param dest string_t* A pointer to the string object in which to do the replacements.
 * \param str_to_replace char* The C string to replace in the string object pointed to by dest.
 * \param replacement_text char* The C string to use as a replacement for the first found occurrence of str_to_replace.
 * \return int A Boolean value, 0 for False and 1 for True, indicating whether or not a replacement was made.
 *
 * Subsequent, identical calls to the function with the same parameters will replace the next occurrence of
 * str_to_replace--if found.
 */
int string_replace(string_t* dest, char* str_to_replace, char* replacement_text)
{
    static int search_strt_pos              =       0;
    int bool_replaced                       =       0;
    int size_diff                           =       0; 
    char* temp                              =       NULL;
    static string_t* old_dest               =       NULL;
    static char* old_str_to_replace         =       NULL;
    static char* old_replacement_text       =       NULL;
    int dest_pos, found_at_pos, replacement_end_pos;

    if (old_dest == NULL && old_str_to_replace == NULL && old_replacement_text == NULL)
    {
        old_dest                    =       dest;
        old_replacement_text        =       replacement_text;
        old_str_to_replace          =       str_to_replace;
    }

    if (dest != NULL && str_to_replace != NULL && replacement_text != NULL)
    {
        if (dest->length > 0 && strlen(str_to_replace) > 0 && strlen(replacement_text) > 0)
        {
            if (dest != old_dest || str_to_replace != old_str_to_replace || replacement_text != old_replacement_text)
            {
                search_strt_pos             =       0;
                old_dest                    =       dest;
                old_replacement_text        =       replacement_text;
                old_str_to_replace          =       str_to_replace;
            }

            size_diff           =       (int)(fabs((double)((int)strlen(str_to_replace) - (int)strlen(replacement_text))));
            found_at_pos        =       string_find_cstr(dest, str_to_replace, search_strt_pos);
            search_strt_pos     =       found_at_pos + 1;

            if (found_at_pos > -1)

            {
                if (strlen(replacement_text) > strlen(str_to_replace))
                {
                    if (dest->length + size_diff > dest->capacity)
                    {
                        temp = (char*)realloc(dest->char_array, dest->capacity + size_diff + 50);
                    }

                    if (temp != NULL || dest->length + size_diff <= dest->capacity)
                    {
                        if (temp != NULL)
                            dest->capacity = dest->capacity + size_diff + 50;

                        /* make room to insert the longer phrase */
                        for (dest_pos = dest->length - 1; dest_pos > found_at_pos + (int)strlen(str_to_replace) - 1; dest_pos--)
                            dest->char_array[dest_pos + size_diff] = dest->char_array[dest_pos];

                        dest->length            +=      size_diff;
                        replacement_end_pos     =       found_at_pos + strlen(replacement_text) - 1;
                        string_set_range(dest, replacement_text, found_at_pos, replacement_end_pos);
                        bool_replaced           =       1;
                    }
                }
                else if (strlen(replacement_text) < strlen(str_to_replace))
                {
                    /* remove unneeded characters */
                    for (dest_pos = found_at_pos + strlen(replacement_text); dest_pos < dest->length - 1; dest_pos++)
                        dest->char_array[dest_pos] = dest->char_array[dest_pos + size_diff];

                    dest->length            -=      size_diff;
                    replacement_end_pos     =       found_at_pos + strlen(replacement_text) - 1;
                    string_set_range(dest, replacement_text, found_at_pos, replacement_end_pos);
                    bool_replaced           =       1;
                }
                else
                {
                    replacement_end_pos     =       found_at_pos + strlen(replacement_text) - 1;
                    string_set_range(dest, replacement_text, found_at_pos, replacement_end_pos);
                    bool_replaced           =       1;
                }
            }
        }
    }

    return bool_replaced;
}

/** \brief Replaces the first occurrence of str_to_replace with replacement_text in the string object pointed to by dest.
 *
 * \param dest string_t* A pointer to the string object in which to do the replacements.
 * \param str_to_replace string_t* A pointer to the string object holding the value to replace in the
 * string object pointed to by dest.
 * \param replacement_text char* A pointer to the string object with contents to use as a replacement for the first
 * found occurrence of str_to_replace.
 * \return int A Boolean value, 0 for False and 1 for True, indicating whether or not a replacement was made.
 *
 * Subsequent, identical calls to the function with the same parameters will replace the next occurrence of
 * str_to_replace--if found.
 */
int string_replace2(string_t* dest, string_t* str_to_replace, string_t* replacement_text)
{
    return string_replace(dest, str_to_replace->char_array, replacement_text->char_array);
}
