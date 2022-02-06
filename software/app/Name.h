/*
Copyright © 2022 Bas Kluiters

Permission is hereby granted, free of charge, to any person obtaining a copy of this 
software and associated documentation files (the “Software”), to deal in the Software 
without restriction, including without limitation the rights to use, copy, modify, 
merge, publish, distribute, sublicense, and/or sell copies of the Software, and to 
permit persons to whom the Software is furnished to do so, subject to the following 
conditions:

The above copyright notice and this permission notice shall be included in all copies 
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef _NAME_H
#define _NAME_H

#include <stdio.h>

/**
 * @brief the Name object
 */
class Name {
  public:
/**
 * @brief Construct a Name object
 * @param name Provide a name
 * @code
 *  Name my_name("Qluit");
 * @endcode
 * @warning Make sure you provide a <tt>constant char *</tt> as only the pointer is stored.
 */
    Name(const char *name);
/**
 * @brief Construct a Name object
 * @param base Provide a Name object
 * @code
 *  Name my_name("Qluit");
 *  Name my_new_name(&my_name);
 * @endcode
 * @see Name#Multi how to create Name objects 
 */
    Name(Name *base = NULL);
    unsigned print(unsigned padding = 0, char separator = '.'); /**< print to @c STDOUT */
    void snprint(char *p, size_t len = 0); /**< copy the Name into a string */
    int compare(const char *p); /**< Compare with a string */
    int compareName(Name *p); /**< Compare with another Name object */
/**
 * @brief Construct a Name object from multiple strings
 * @param a,b,c,d,e provide one string and 4 optional ones
 * @code
 *  Name my_name(Name::Multi("A", "B", "C"));
 *  my_name.print();
 *  > A.B.C
 * @endcode
 */
    static Name *Multi(const char *a, const char *b = NULL, const char *c = NULL, const char *d = NULL, const char *e = NULL);
  private:
    void setAsBase(Name *base);
    void fillWithName(char **p, char separator = '.');
    int _compare(const char **p);
    const char *_name;
    Name *_base;
};

#endif