#ifndef CWEBPARSER_GUARD_FLEXLEXER_H
#define CWEBPARSER_GUARD_FLEXLEXER_H
// cwebparser_guard_flexlexer.h

// make sure redefinition happens just once using FlexLexer.h macro that guards yyFlexLexer class definition
#ifndef yyFlexLexerOnce
#  undef yyFlexLexer
#  define yyFlexLexer CWebFlexLexer
#  include "FlexLexer.h"
#endif

#endif

