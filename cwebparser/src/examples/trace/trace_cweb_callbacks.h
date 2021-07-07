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

// utility function
  bool printLineInfo(const string& event, const Context& context) const {
    const auto& [bfilename, bline, bcol] = context.loc.begin;
    const auto& [efilename, eline, ecol] = context.loc.end;
    print("{:<6} {:<5} {:<6} {:<5} {}\n", bline, bcol, eline, ecol, event);
    return true;
  }

  function<bool(const string&, const Context&)> text = [this](const string&, const Context& context) {
    return printLineInfo("text", context);
  };

  function<bool(const Context&)> documentBegin = [this](const Context& context) {
    return printLineInfo("documentBegin", context);
  };

  function<bool(const Context&)> documentEnd = [this](const Context& context) {
    return printLineInfo("documentEnd", context);
  };

  function<bool(const string& file, const Context&)> fileBegin = [this](const string&, const Context& context) {
    return printLineInfo("fileBegin", context);
  };

  function<bool(const string& file, const Context&)> fileEnd = [this](const string&, const Context& context) {
    return printLineInfo("fileEnd", context);
  };

  function<bool(void)> limboBegin = [this]() {
    return true;
  };

  function<bool(const Context&)> limboEnd = [this](const Context&) {
    return true;
  };

  function<bool(void)> texBegin = [this]() {
    return true;
  };

  function<bool(void)> texEnd = [this]() {
    return true;
  };

  function<bool(const string&, const Context&)> starredTexSectionBegin = [this](const string&, const Context& context) {
    return printLineInfo("starredTexSectionBegin", context);
  };

  function<bool(const string&, const Context&)> starredTexSectionEnd = [this](const string&, const Context&) {
    return true;
  };

  function<bool(const Context&)> unstarredTexSectionBegin = [this](const Context& context) {
    return printLineInfo("unstarredTexSectionBegin", context);
  };

  function<bool(const Context&)> unstarredTexSectionEnd = [this](const Context&) {
    return true;
  };

  function<bool(void)> middleBegin = [this]() {
    return true;
  };

  function<bool(void)> middleEnd = [this]() {
    return true;
  };

  function<bool(void)> cBegin = [this]() {
    return true;
  };

  function<bool(void)> cEnd = [this]() {
    return true;
  };

  function<bool(const Context&)> innerCBegin = [this](const Context& context) {
    return printLineInfo("innerCBegin", context);
  };

  function<bool(const Context&)> innerCEnd = [this](const Context& context) {
    return printLineInfo("innerCEnd", context);
  };

  function<bool(const CommentType, const Context&)> commentBegin = [this](const CommentType, const Context& context) {
    return printLineInfo("commentBegin", context);
  };

  function<bool(const CommentType, const Context&)> commentEnd = [this](const CommentType, const Context& context) {
    return printLineInfo("commentEnd", context);
  };

  function<bool(const string&, const bool, const string&, const Context&)> includeBegin = [this](const string&, const bool, const string&, const Context& context) {
    return printLineInfo("includeBegin", context);
  };

  function<bool(const Context&)> includeEnd = [this](const Context& context) {
    return printLineInfo("includeEnd", context);
  };

  function<bool(const string&, const bool, const bool, const Context&)> namedSectionBegin = [this](const string&, const bool, const bool, const Context& context) {
    return printLineInfo("namedSectionBegin", context);
  };

  function<bool(const Context&)> namedSectionEnd = [this](const Context& context) {
    return printLineInfo("namedSectionEnd", context);
  };

  function<bool(const string&, const bool, const bool, const Context&)> sectionName = [this](const string&, const bool, const bool, const Context& context) {
    return printLineInfo("sectionName", context);
  };

  function<bool(const Context&)> macroBegin = [this](const Context& context) {
    return printLineInfo("macroBegin", context);
  };

  function<bool(const string&, const vector<string>&, const Context&)> macroNameParams = [this](const string&, const vector<string>&, const Context& context) {
    return printLineInfo("macroNameParams", context);
  };

  function<bool(void)> macroEnd = [this]() {
    return true;
  };

  function<bool(const StringType, const Context&)> stringBegin = [this](const StringType, const Context& context) {
    return printLineInfo("stringBegin", context);
  };

  function<bool(const StringType, const Context&)> stringEnd = [this](const StringType, const Context& context) {
    return printLineInfo("stringEnd", context);
  };

  function<bool(const string&, const string&, const bool, const Context&)> formatDefinitionBegin = [this](const string&, const string&, const bool, const Context& context) {
    return printLineInfo("formatDefinitionBegin", context);
  };

  function<bool(const Context&)> programSectionBegin = [this](const Context& context) {
    return printLineInfo("programSectionBegin", context);
  };

  function<bool(const Context&)> programSectionEnd = [this](const Context&) {
    return true;
  };

  function<bool(void)> fileSectionBegin = [this]() {
    return true;
  };

  function<bool(void)> fileSectionEnd = [this]() {
    return true;
  };

  function<bool(const Context&)> emitMacrosHere = [this](const Context& context) {
    return printLineInfo("emitMacrosHere", context);
  };

  function<bool(const string&, const Context&)> controlText = [this](const string&, const Context& context) {
    return printLineInfo("controlText", context);
  };

  function<bool(const FormatControlCode, const Context&)> formatControl = [this](const FormatControlCode, const Context& context) {
    return printLineInfo("formatControl", context);
  };

  function<bool(const Context&)> formatExpressionBegin = [this](const Context& context) {
    return printLineInfo("formatExpressionBegin", context);
  };

  function<bool(const Context&)> formatExpressionEnd = [this](const Context& context) {
    return printLineInfo("formatExpressionEnd", context);
  };

  function<bool(void)> ctangleControl = [this]() {
    return true;
  };

};

}

#endif

