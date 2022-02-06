#include "Name.h"

#include <assert.h>
#include <string.h>

/**
 * @brief Test object to see how you can embed a Name in an object
 */
class Test { 
  public:
    Test(Name name, int x = 42) { /**< Constructor */
      _name = name;
      _name.print();
      printf("\n");
    }
    int compare(const char *string) { /**< compare to string */
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
