#ifndef TRACE_CWEB_CALLBACKS_H
#define TRACE_CWEB_CALLBACKS_H

// trace_cweb_callbacks.h

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
#include <iostream>

#include <fmt/format.h>

#include "parserapi/v4/cwebparser.v4.h"

namespace trace_cweb {
using namespace std;
using namespace fmt;
using namespace cweb::v4;

struct TraceCallbacks {
  //function<bool(const Error& error)> error;

  function<bool(const string&, const Context&)> text = [](const string&, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} text\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> documentBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} documentBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> documentEnd = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} documentEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string& file, const Context&)> fileBegin = [](const string&, const Context&) {
    return true;
  };

  function<bool(const string& file, const Context&)> fileEnd = [](const string&, const Context&) {
    return true;
  };

  function<bool(void)> limboBegin = []() {
    return true;
  };

  function<bool(const Context&)> limboEnd = [](const Context&) {
    return true;
  };

  function<bool(void)> texBegin = []() {
    return true;
  };

  function<bool(void)> texEnd = []() {
    return true;
  };

  function<bool(const string&, const Context&)> starredTexSectionBegin = [](const string&, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} starredTexSectionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const Context&)> starredTexSectionEnd = [](const string&, const Context&) {
    return true;
  };

  function<bool(const Context&)> unstarredTexSectionBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} unstarredTexSectionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> unstarredTexSectionEnd = [](const Context&) {
    return true;
  };

  function<bool(void)> middleBegin = []() {
    return true;
  };

  function<bool(void)> middleEnd = []() {
    return true;
  };

  function<bool(void)> cBegin = []() {
    return true;
  };

  function<bool(void)> cEnd = []() {
    return true;
  };

  function<bool(const Context&)> innerCBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} innerCBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> innerCEnd = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} innerCEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const CommentType, const Context&)> commentBegin = [](const CommentType, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} commentBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const CommentType, const Context&)> commentEnd = [](const CommentType, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} commentEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const bool, const string&, const Context&)> includeBegin = [](const string&, const bool, const string&, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} includeBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> includeEnd = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} includeEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const bool, const bool, const Context&)> namedSectionBegin = [](const string&, const bool, const bool, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} namedSectionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(void)> namedSectionEnd = []() {
    return true;
  };

  function<bool(const string&, const bool, const bool, const Context&)> sectionName = [](const string&, const bool, const bool, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} sectionName\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> macroBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} macroBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const vector<string>&, const Context&)> macroNameParams = [](const string&, const vector<string>&, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} macroNameParams\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(void)> macroEnd = []() {
    return true;
  };

  function<bool(const StringType, const Context&)> stringBegin = [](const StringType, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} stringBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const StringType, const Context&)> stringEnd = [](const StringType, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} stringEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const string&, const bool, const Context&)> formatDefinitionBegin = [](const string&, const string&, const bool, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} formatDefinitionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> programSectionBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} programSectionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> programSectionEnd = [](const Context&) {
    return true;
  };

  function<bool(void)> fileSectionBegin = []() {
    return true;
  };

  function<bool(void)> fileSectionEnd = []() {
    return true;
  };

  function<bool(const Context&)> emitMacrosHere = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} emitMacrosHere\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const string&, const Context&)> controlText = [](const string&, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} controlText\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const FormatControlCode, const Context&)> formatControl = [](const FormatControlCode, const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} formatControl\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> formatExpressionBegin = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} formatExpressionBegin\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(const Context&)> formatExpressionEnd = [](const Context& context) {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} formatExpressionEnd\n", bline, bcol, eline, ecol);
    return true;
  };

  function<bool(void)> ctangleControl = []() {
    return true;
  };

};

}

#endif

