#ifndef ECHO_CWEB_CALLBACKS_H
#define ECHO_CWEB_CALLBACKS_H

// echo_cweb_callbacks.h

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

#include "parserapi/v4/cwebparser.v4.h"

namespace echo_cweb {
using namespace std;
using namespace cweb::v4;

struct EchoCallbacks {
  //function<bool(const Error& error)> error;

  function<bool(const string&, const Context&)> text = [](const string& text, const Context&) {
    cout << text;
    return true;
  };

  function<bool(const string&, const Context&)> starredTexSectionBegin = [](const string&, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const string&, const Context&)> starredTexSectionEnd = [](const string&, const Context&) {
    return true;
  };

  function<bool(const Context&)> unstarredTexSectionBegin = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> unstarredTexSectionEnd = [](const Context&) {
    return true;
  };

  function<bool(const Context&)> innerCBegin = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> innerCEnd = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const CommentType, const Context&)> commentBegin = [](const CommentType, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const CommentType, const Context&)> commentEnd = [](const CommentType, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const string&, const bool, const string&, const Context&)> includeBegin = [](const string&, const bool, const string&, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> includeEnd = [](const Context&) {
    return true;
  };

  function<bool(const string&, const bool, const bool, const Context&)> namedSectionBegin = [](const string&, const bool, const bool, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> namedSectionEnd = [](const Context&) {
    return true;
  };

  function<bool(const string&, const bool, const bool, const Context&)> sectionName = [](const string&, const bool, const bool, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> macroBegin = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const string&, const vector<string>&, const Context&)> macroNameParams = [](const string&, const vector<string>&, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(void)> macroEnd = []() {
    return true;
  };

  function<bool(const StringType, const Context&)> stringBegin = [](const StringType, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const StringType, const Context&)> stringEnd = [](const StringType, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const string&, const string&, const bool, const Context&)> formatDefinitionBegin = [](const string&, const string&, const bool, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> programSectionBegin = [](const Context& context) {
    cout << context.text;
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
    cout << context.text;
    return true;
  };

  function<bool(const string&, const Context&)> controlText = [](const string&, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const FormatControlCode, const Context&)> formatControl = [](const FormatControlCode, const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> formatExpressionBegin = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(const Context&)> formatExpressionEnd = [](const Context& context) {
    cout << context.text;
    return true;
  };

  function<bool(void)> ctangleControl = []() {
    return true;
  };

};

}

#endif

