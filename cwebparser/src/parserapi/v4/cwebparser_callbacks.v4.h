#ifndef CWEBPARSER_CALLBACKS_H
#define CWEBPARSER_CALLBACKS_H
// cwebparser_callbacks.h

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

#include <string>
#include <vector>
#include <functional>

#include "parserapi/v4/cwebparser_context.v4.h"

namespace cweb::v4 {
using namespace std;

enum class StringType {
  quotedC = 0,
  rawCplusplus
};

enum class CommentType {
  c = 0,
  cplusplus
};

enum class FormatControlCode {
  thinSpace = 0,
  linebreak,
  optionalLinebreak,
  forceLinebreak,
  cancelLinebreak,
  invisibleSemicolon
};

struct Callbacks {
  //vector<function<bool(const Error& error)>> error;
  vector<function<bool(const string&, const Context&)>> text;

  vector<function<bool(const Context&)>> documentBegin;
  vector<function<bool(const Context&)>> documentEnd;

  vector<function<bool(const string& file, const Context&)>> fileBegin;
  vector<function<bool(const string& file, const Context&)>> fileEnd;

  vector<function<bool(void)>> limboBegin;
  vector<function<bool(const Context&)>> limboEnd;

  vector<function<bool(void)>> texBegin;
  vector<function<bool(void)>> texEnd;

  vector<function<bool(const string&, const Context&)>> starredTexSectionBegin;
  vector<function<bool(const string&, const Context&)>> starredTexSectionEnd;

  vector<function<bool(const Context&)>> unstarredTexSectionBegin;
  vector<function<bool(const Context&)>> unstarredTexSectionEnd;

  vector<function<bool(void)>> middleBegin;
  vector<function<bool(void)>> middleEnd;

  vector<function<bool(void)>> cBegin;
  vector<function<bool(void)>> cEnd;

  vector<function<bool(const Context&)>> innerCBegin;
  vector<function<bool(const Context&)>> innerCEnd;

  vector<function<bool(const CommentType, const Context&)>> commentBegin;
  vector<function<bool(const CommentType, const Context&)>> commentEnd;

  vector<function<bool(const string&, const bool, const string&, const Context&)>> includeBegin;
  vector<function<bool(const Context&)>> includeEnd;

  vector<function<bool(const string&, const bool, const bool, const Context&)>> namedSectionBegin;
  vector<function<bool(void)>> namedSectionEnd;

  vector<function<bool(const string&, const bool, const bool, const Context&)>> sectionName;

  vector<function<bool(const Context&)>> macroBegin;
  vector<function<bool(const string&, const vector<string>&, const Context&)>> macroNameParams;
  vector<function<bool(void)>> macroEnd;

  vector<function<bool(const StringType, const Context&)>> stringBegin;
  vector<function<bool(const StringType, const Context&)>> stringEnd;

  vector<function<bool(const string&, const string&, const bool, const Context&)>> formatDefinitionBegin;
  vector<function<bool(const Context&)>> formatDefinitionEnd;

  vector<function<bool(const Context&)>> programSectionBegin;
  vector<function<bool(const Context&)>> programSectionEnd;

  vector<function<bool(void)>> fileSectionBegin;
  vector<function<bool(void)>> fileSectionEnd;

  vector<function<bool(const Context&)>> emitMacrosHere;

  vector<function<bool(const string&, const Context&)>> controlText;

  vector<function<bool(const FormatControlCode, const Context&)>> formatControl;

  vector<function<bool(const Context&)>> formatExpressionBegin;
  vector<function<bool(const Context&)>> formatExpressionEnd;

  vector<function<bool(void)>> ctangleControl;
};

}

#endif
