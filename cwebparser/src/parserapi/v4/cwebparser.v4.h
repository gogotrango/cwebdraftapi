#ifndef CWEBPARSER_H
#define CWEBPARSER_H

// cwebparser.v4.h

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

// API for parsing CWEB documents

#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <optional>
#include <functional>
#include <fmt/format.h>

#include "bisonparser/v4/cwebbisonparser.v4.bison.h"
#include "flexlexer/v4/cweblexer.v4.h"

#include "parserapi/v4/cwebparser_callbacks.v4.h"


namespace cweb::v4 {
using namespace std;
using namespace fmt;

struct CWebParserConfig {
  bool escapeMacroNewlines = true;
};

struct CWebParser {

  CWebParser() = default;

  CWebParser(const CWebParserConfig& config): cwebConfig(config) {
    lexer.config.escapeMacroNewlines = config.escapeMacroNewlines;
  }

  template<typename UserCallbacksT>
  int parse(istream& in, UserCallbacksT& ucb) {
    addCallbacks(ucb);
    lexer.switch_streams(&in);
    return bison();
  }

  int parse(istream& in) {
    lexer.switch_streams(&in);
    return bison();
  }

  int parse() {
    return bison();
  }

  void debug(bool debug) {
    lexer.set_debug(debug);
    bison.set_debug_level(debug);
  }

  template<typename UserCallbacksT>
  void addCallbacks(UserCallbacksT ucb) {

    if constexpr (requires {ucb.documentBegin;})
      bisonConfig.cbs.documentBegin.push_back(ucb.documentBegin);
    if constexpr (requires {ucb.documentEnd;})
      bisonConfig.cbs.documentEnd.push_back(ucb.documentEnd);

    if constexpr (requires {ucb.fileBegin;})
      bisonConfig.cbs.fileBegin.push_back(ucb.fileBegin);
    if constexpr (requires {ucb.fileEnd;})
      bisonConfig.cbs.fileEnd.push_back(ucb.fileEnd);

    if constexpr (requires {ucb.limboBegin;})
      bisonConfig.cbs.limboBegin.push_back(ucb.limboBegin);
    if constexpr (requires {ucb.limboEnd;})
      bisonConfig.cbs.limboEnd.push_back(ucb.limboEnd);

    if constexpr (requires {ucb.texBegin;})
      bisonConfig.cbs.texBegin.push_back(ucb.texBegin);
    if constexpr (requires {ucb.texEnd;})
      bisonConfig.cbs.texEnd.push_back(ucb.texEnd);

    if constexpr (requires {ucb.starredTexSectionBegin;})
      bisonConfig.cbs.starredTexSectionBegin.push_back(ucb.starredTexSectionBegin);

    if constexpr (requires {ucb.starredTexSectionEnd;})
      bisonConfig.cbs.starredTexSectionEnd.push_back(ucb.starredTexSectionEnd);

    if constexpr (requires {ucb.unstarredTexSectionBegin;})
      bisonConfig.cbs.unstarredTexSectionBegin.push_back(ucb.unstarredTexSectionBegin);

    if constexpr (requires {ucb.unstarredTexSectionEnd;})
      bisonConfig.cbs.unstarredTexSectionEnd.push_back(ucb.unstarredTexSectionEnd);

    if constexpr (requires {ucb.middleBegin;})
      bisonConfig.cbs.middleBegin.push_back(ucb.middleBegin);
    if constexpr (requires {ucb.middleEnd;})
      bisonConfig.cbs.middleEnd.push_back(ucb.middleEnd);

    if constexpr (requires {ucb.cBegin;})
      bisonConfig.cbs.cBegin.push_back(ucb.cBegin);
    if constexpr (requires {ucb.cEnd;})
      bisonConfig.cbs.cEnd.push_back(ucb.cEnd);

    if constexpr (requires {ucb.innerCBegin;})
      bisonConfig.cbs.innerCBegin.push_back(ucb.innerCBegin);
    if constexpr (requires {ucb.innerCEnd;})
      bisonConfig.cbs.innerCEnd.push_back(ucb.innerCEnd);

    if constexpr (requires {ucb.commentBegin;})
      bisonConfig.cbs.commentBegin.push_back(ucb.commentBegin);
    if constexpr (requires {ucb.commentEnd;})
      bisonConfig.cbs.commentEnd.push_back(ucb.commentEnd);

    if constexpr (requires {ucb.includeBegin;})
      bisonConfig.cbs.includeBegin.push_back(ucb.includeBegin);

    if constexpr (requires {ucb.includeEnd;})
      bisonConfig.cbs.includeEnd.push_back(ucb.includeEnd);

    if constexpr (requires {ucb.namedSectionBegin;})
      bisonConfig.cbs.namedSectionBegin.push_back(ucb.namedSectionBegin);

    if constexpr (requires {ucb.namedSectionEnd;})
      bisonConfig.cbs.namedSectionEnd.push_back(ucb.namedSectionEnd);

    if constexpr (requires {ucb.sectionName;})
      bisonConfig.cbs.sectionName.push_back(ucb.sectionName);

    if constexpr (requires {ucb.macroBegin;})
      bisonConfig.cbs.macroBegin.push_back(ucb.macroBegin);

    if constexpr (requires {ucb.macroNameParams;})
      bisonConfig.cbs.macroNameParams.push_back(ucb.macroNameParams);

    if constexpr (requires {ucb.macroEnd;})
      bisonConfig.cbs.macroEnd.push_back(ucb.macroEnd);

    if constexpr (requires {ucb.stringBegin;})
      bisonConfig.cbs.stringBegin.push_back(ucb.stringBegin);
    if constexpr (requires {ucb.stringEnd;})
      bisonConfig.cbs.stringEnd.push_back(ucb.stringEnd);

    if constexpr (requires {ucb.formatDefinitionBegin;})
      bisonConfig.cbs.formatDefinitionBegin.push_back(ucb.formatDefinitionBegin);

    if constexpr (requires {ucb.formatDefinitionEnd;})
      bisonConfig.cbs.formatDefinitionEnd.push_back(ucb.formatDefinitionEnd);

    if constexpr (requires {ucb.programSectionBegin;})
      bisonConfig.cbs.programSectionBegin.push_back(ucb.programSectionBegin);
    if constexpr (requires {ucb.programSectionEnd;})
      bisonConfig.cbs.programSectionEnd.push_back(ucb.programSectionEnd);

    if constexpr (requires {ucb.fileSectionBegin;})
      bisonConfig.cbs.fileSectionBegin.push_back(ucb.fileSectionBegin);
    if constexpr (requires {ucb.fileSectionEnd;})
      bisonConfig.cbs.fileSectionEnd.push_back(ucb.fileSectionEnd);

    if constexpr (requires {ucb.emitMacrosHere;})
      bisonConfig.cbs.emitMacrosHere.push_back(ucb.emitMacrosHere);

    if constexpr (requires {ucb.controlText;})
      bisonConfig.cbs.controlText.push_back(ucb.controlText);

    if constexpr (requires {ucb.formatControl;})
      bisonConfig.cbs.formatControl.push_back(ucb.formatControl);

    if constexpr (requires {ucb.formatExpressionBegin;})
      bisonConfig.cbs.formatExpressionBegin.push_back(ucb.formatExpressionBegin);

    if constexpr (requires {ucb.formatExpressionEnd;})
      bisonConfig.cbs.formatExpressionEnd.push_back(ucb.formatExpressionEnd);

    if constexpr (requires {ucb.ctangleControl;})
      bisonConfig.cbs.ctangleControl.push_back(ucb.ctangleControl);

    if constexpr (requires {ucb.text;})
      bisonConfig.cbs.text.push_back(ucb.text);

  }

  CWebParserConfig cwebConfig;
  string infilename = "stdin";
  CWebLexer lexer;
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser bison{[&lexer=lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig};


};


}

#endif

