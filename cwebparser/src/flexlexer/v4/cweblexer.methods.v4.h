#ifndef CWEBLEXER_METHODS_V4_H
#define CWEBLEXER_METHODS_V4_H
// cweblexer.methods.v4.h

/*
MIT License

Copyright (c) 2021 Zartaj Majeed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
file to #include in flex .l epilog because it needs symbols in .cpp file generated by flex
can be named .h or .cpp
*/

#include "bisonparser/v4/cwebbisonparser.v4.bison.h"

namespace cweb::v4 {
using namespace std;
using namespace fmt;

using Mode = BisonParserState::Mode;

// YY_BUF_SIZE is in flex generated .cpp file
void CWebLexer::includeFileStart(istream& file) {
  auto buf = yy_create_buffer(&file, YY_BUF_SIZE);
  yypush_buffer_state(buf);
  //print("CWebLexer.{}.{}: reading from include file\n", __func__, __LINE__);
}

void CWebLexer::setLexerState(const BisonParserState& parserState) {

// ignore parser state while inside macro, macro states are local to lexer and unknown to parser
#if 0
  if(false
     || YY_START == CONTROL
     || YY_START == C_COMMENT
     || YY_START == CPLUSPLUS_COMMENT
     || (YY_START >= NAMED_SECTION_BODY && YY_START < NAMED_SECTION_LAST)
     || (YY_START >= MACRO_BEGIN && YY_START < MACRO_LAST)
  ) {
    if(debug() != 0) {
      print("CWebLexer.{}.{}: parser mode {}: lexer state change ignored while in state {}\n", __func__, __LINE__, parserState.mode, YY_START);
    }
    return;
  }
#endif

// for debugging only
  auto oldState = YY_START;

  switch(parserState.mode) {
    case Mode::limbo:
      BEGIN(LIMBO);
      break;
    case Mode::tex:
      BEGIN(TEX);
      break;
    case Mode::middle:
      BEGIN(MIDDLE);
      break;
    case Mode::c:
      BEGIN(C);
      break;
    case Mode::inner_c:
      BEGIN(INNER_C);
      break;
    case Mode::restricted_tex:
      BEGIN(RESTRICTED_TEX);
      break;
    case Mode::c_comment:
      BEGIN(C_COMMENT);
      break;
    case Mode::cplusplus_comment:
      BEGIN(CPLUSPLUS_COMMENT);
      break;
    case Mode::c_string:
      BEGIN(C_STRING_CHARS);
      break;
    case Mode::cplusplus_rawstring:
      BEGIN(CPLUSPLUS_RAWSTRING_CHARS);
      break;
// macro mode means lexer can be in one of its MACRO states
    case Mode::macro:
    default:
      break;
  };

  if(debug() != 0) {
    auto newState = YY_START;
    print("CWebLexer.{}.{}: parser mode {}: lexer state {}change new {} old {}\n", __func__, __LINE__, parserState.mode, newState == oldState? "no ": "", newState, oldState);
  }

}

}

#endif
