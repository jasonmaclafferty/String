************************************
*         String README            *
************************************

************************************
*         General Info             *
************************************
This document README file attempts to provide some basic, helpful information regarding the use of the rich, dynamic string data type implementation for C offered here in the "String" Github repo.

************************************
*      String Project Objective    *
************************************
The objective for this project was to implement a rich, dynamicly-sized, high-level string data type for C. With robust, automatic memory management features built into the library and the string operational functionalities provided with the data type API it is intended to provide a full-blown data type for string data similar to higher level languages such as Python and C#. It was born out of the project author's painful experiences using character arrays to represent strings in C programs during his first year studying Computer Science in college.

************************************
* Using the String data type for C *
************************************
To use the data type properly, one should follow the following steps:

1.  Declare a pointer of type "string_t*"
2.  Assign the new pointer variable to the result of a function call to either "string_init()" or "string_cust_init()"
*******Note that both functions return the address of a newly allocated and initialized string object in memory. "string_init()" takes no parameters and "string_cust_init()" takes a single parameter indicating the desired initial capacity for the internal character array of the string object represented as a struct. Please additionally note that the string data type initializers return a string_t* pointer instead of just initializing an already allocated object from the programmer. This is understood to be non-conventional behavior from standard written C, but was implemented like so in an attempt to abstract as much of the memory management under the hood so that the programmer would not have to worry about it.*******
3.  Call any of the functions defined by the API on the string_t* pointer, or a collection of them, completely forgetting about space and memory size constraints for the internal char array as the library automatically resizes it as necessary to hold the requested data.
4.  Pass any string_t* pointers used to the cleanup function "string_destroy()" to free memory resources used by the allocated string objects when you are done with them.

*******Note: the internal fields of the string_t struct are managed automatically by the library and should not be modified directly by the programmer. Read only access to them by the programmer is considered acceptable, but it should rarely be necessary to read any field outside of the "length" field. Modify any of them directly at your own risk--as doing so holds serious risks for memory leaks and undefined behavior with the library. Doing so will require the the programmer to manage all the string_t fields himself--which is the very reason the library was created in the first place--so the programmer would not have to worry about them.*******
