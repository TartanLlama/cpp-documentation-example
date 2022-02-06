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

#include "Name.h"
#include <string.h>
#ifdef ARDUINO
#include "aux.h"
#endif

Name::Name(const char *name) {
  _name = name;
  _base = NULL;
}

Name::Name(Name *base) {
  _name = NULL;
  _base = NULL;
  if( base ) {
    _name = base->_name;
    _base = base->_base;
    delete base;
  }
}

unsigned Name::print(unsigned padding, char separator) {
  unsigned printed = 0;
  if( _base ) {
    printed += _base->print();
    if( _name ) {
      printf("%c", separator);
      printed++;
    }
  }
  if( _name ) {
    printf("%s", _name);
    printed += strlen(_name);
  }
  if( padding ) {
    for(unsigned i = printed; i < padding; i++ ) {
      printf(" ");
      printed++;
    }
  }
  return printed;
}

void Name::fillWithName(char **p, char separator) {
  if( _base ) {
    _base->fillWithName(p);
    if( _name )
      *(*p)++ = separator;
  }
  if( _name ) {
    sprintf(*p, "%s", _name);
    (*p) += strlen(_name);
  }
}

void Name::snprint(char *p, size_t len) {
  fillWithName(&p);
}

// Name::~Name() {
// Do not delete _base as it is used when Name object is copied. 
//   if( _base )
//     delete _base;
// }

int Name::_compare(const char **p) {
  int retval;
  if( _base ) {
    retval = _base->_compare(p);
    if( retval ) // unequal
      return retval;
    retval = '.' - **p;
    if( retval ) // unequal
      return retval;
    *p = *p + 1; // skipping the dot
  }
  if( _name ) {
    retval = strncmp(*p, _name, strlen(_name));
    *p += strlen(_name);
    return retval;
  }
  return 42; // Exceptional value. Just not zero
}

int Name::compare(const char *p) {
  if( !p )
    return 42; // Exceptional value. Just not zero
  return _compare(&p);
}

int Name::compareName(Name *p) {
  if( !p )
    return 42; // Exceptional value. Just not zero
  int retval;
  if( _base && !p->_base ) {
    retval = _base->compareName(p);
    if( retval )
      return retval;
  }
  if( !_base && p->_base ) {
    retval = compareName(p->_base);
    if( retval )
      return retval;
  }
  if( _base && p->_base ) {
    retval = _base->compareName(p->_base);
    if( retval )
      return retval;
  }
  return strcmp(_name, p->_name);
}

void Name::setAsBase(Name *base) {
  _base = base;
}

Name *Name::Multi(const char *a, const char *b, const char *c, const char *d, const char *e) {
  Name *retval  = NULL;
  const char *ptrs[] = {a,b,c,d,e};
  for(unsigned i = 0; i < sizeof(ptrs)/sizeof(ptrs[0]); i++) {
    const char *p = ptrs[i];
    if( p ) {
      Name *tmp = new Name(p);
      tmp->setAsBase(retval);
      retval = tmp;
    }
  }
  return retval;
}

#ifdef NAME_UNIT_TEST
// ========== Unit Tests ============
// g++ -D NAME_UNIT_TEST -o name.out Name.cpp && ./name.out && rm name.out

#include <assert.h>

class Test {
  public:
    Test(Name name, int x = 42) {
      _name = name;
      _name.print();
      printf("\n");
    }
    int compare(const char *string) {
      return _name.compare((char *)string);
    }
  private:
    Name _name;
};

int main(void) {
  Name a("A");
  assert( 42 == a.compare((char *)NULL));
  assert( !a.compare((char *)"A"));
  Name b(new Name("BB"));
  assert( !b.compare((char *)"BB"));
  Name c(Name::Multi("A", "B", "C", "D"));
  assert( !c.compare((char *)"A.B.C.D") );
  Name d((const char *)NULL);
  assert( 42 == d.compare((char *)NULL));
  assert( 42 == d.compare((char *)""));
  Name e((Name *)NULL);
  assert( 42 == e.compare((char *)NULL));
  assert( 42 == e.compare((char *)""));
  Test t("cavia", 12);
  assert( !t.compare("cavia"));
  Test u(new Name("konijn"));
  assert( !u.compare("konijn"));
  Test v(Name::Multi("A", "B", "C"), 45);
  assert( !v.compare("A.B.C"));
  Test w(Name::Multi("A", "B", "C", "D"));
  assert( !w.compare("A.B.C.D"));
  Name n("eekhoorn");
  Name p("eekhoorn");
  Name q("bever");
  assert( 42 == n.compareName(NULL) );
  assert( 0 == n.compareName(&p) );
  assert( q.compareName(&p) < 0 );
  assert( p.compareName(&q) > 0 );
  Name g(Name::Multi("Aap","B"));
  Name j(Name::Multi("Aap","A"));
  Name k("Aap");
  Name l("Noot");
  assert( g.compareName(&j) > 0 );
  assert( j.compareName(&k) < 0 );
  assert( j.compareName(&g) < 0 );
  assert( k.compareName(&j) > 0 );
  assert( l.compareName(&g) > 0 );
  assert( l.compareName(&j) > 0 );
  assert( l.compareName(&k) > 0 );
  char line[100];
  g.snprint(line);
  assert( !strcmp(line, "Aap.B") );
  p.snprint(line);
  assert( !strcmp(line, "eekhoorn") );
}
#endif
