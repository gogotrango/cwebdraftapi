#ifndef CWEBPARSER_CONTEXT_H
#define CWEBPARSER_CONTEXT_H
// cwebparser_context.h

#include "bisonparser/v4/cwebbisonparser.v4.bison.h"
#include "bisonparser/v4/location.bison.h"

namespace cweb::v4 {
using namespace std;

struct Context {

  location loc;
  string text;

};

}

#endif

