// cwebbisonparser.v4.bison.y

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

This is a bison grammar for cweb - the structured documentation language for the C and C++ programming languages

cweb is described at https://www-cs-faculty.stanford.edu/~knuth/cweb.html

The grammar is based on the cweb manual and documentation generated from cweb source files. There are four documents that describe the language and the behavior of tools for working with cweb content: cwebman.pdf, cweave.pdf, ctangle.pdf and common.pdf

Briefly, the cweb language comprises two-character control codes that start with "@". The codes are case-insensitive. The "|" pipe character is special in certain contexts too. These codes are used within c and tex text. The cweb language specifies what codes are allowed in what contexts. It also specifies how the various parts of a cweb document can be arranged.

*/

// c++ parser classes skeleton file
%skeleton "lalr1.cc"

%require "3.7"

// c++ parser
%language "c++"

// generate parser description report .output file
%verbose

%defines "cwebbisonparser.v4.bison.h"
%output "cwebbisonparser.v4.bison.cpp"

// enable debug trace
%define parse.trace

// detailed option should be used with full lookahead correction
//%define parse.error detailed
//%define parse.lac full

// have to provide report_syntax_error method for custom error handling
%define parse.error custom

// adds location parameter to symbol constructors
%locations

// don't generate locations file for use by applications
//%define api.location.file none
%define api.location.file "location.bison.h"
%define api.location.include {"bisonparser/v4/location.bison.h"}

// want to return character token from flex but don't think it can work with api.token.constructor
// better lookup performance at cost of disallowing literal characters in grammar
%define api.token.raw

%code requires {
// %code requires is topmost user code block in generated .h file before namespace and parser class
// standard c++ #includes and defines

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

#include <stddef.h>

#include <string>
#include <vector>
#include <stack>
#include <optional>
#include <functional>
#include <istream>
#include <fstream>
#include <filesystem>

#include <fmt/format.h>

#include "bisonparser/v4/location.bison.h"

#include "parserapi/v4/cwebparser_callbacks.v4.h"

namespace cweb::v4 {
using namespace std;
using namespace fmt;

// all these types are needed by CWebBisonParser for methods and fields

struct StarredTexSection {
  string title;
  string text;
};

struct IncludeFile {
  string file;
  string trailingText;
  string text;
  bool quoted = false;
};

struct MacroName {
  string name;
  vector<string> params;
  string text;
};

struct FormatDefinition {
  string left;
  string right;
  string text;
  bool suppress = false;
};

struct IndexEntry {
  string entry;
  string text;
};

struct NamedSection {
  string name;
  string text;
  bool isPrefix = false;
  bool isContinuation = false;
};

// yylex parameter for parser to control lexer,
// this is how parser and lexer communicate
struct BisonParserState {

  enum class Mode {
    limbo = 0,
    tex,
    middle,
    c,
    inner_c,
    restricted_tex,
    c_comment,
    cplusplus_comment,
    c_string,
    cplusplus_rawstring,
    macro,
    size
  } mode = Mode::limbo;

  stack<Mode> nestedModes = {};

  ifstream includeFile{nullptr};
  enum class IncludeFileState {
    closed = 0,
    open,
    reading,
    eof
  } includeFileState = IncludeFileState::closed;

  location loc = location{};

};

struct BisonParserConfig {
  Callbacks cbs;
  string infilename = "";
  string cwebdir = "";
};

}

}

// custom namespace generated by bison
%define api.namespace {cweb::v4}

// custom classname generated by bison
%define api.parser.class {CWebBisonParser}

// make yylex a lambda member of CWebBisonParser that will call real yylex
%parse-param {function<CWebBisonParser::symbol_type(BisonParserState&)> yylex}

// parser state for lexer to examine for lexical feedback
// unfortunate this has to be added as reference parse-param due to bison constraints
%parse-param {BisonParserState& publicState}

// config settings for bison parser, for parser-api communication
%parse-param {BisonParserConfig& publicConfig}

// parser controls lexer through ParserState parameters, so lambda above has to take this as a parameter and pass it to real yylex which obviously also has to take the same parameter
%lex-param {BisonParserState& publicState}

// use actual c++ types for tokens
%define api.value.type variant

// use c++ token objects, changes signature of yylex, yylex now returns CWebBisonParser::symbol_type
%define api.token.constructor

// implicit moves for parameters to make_* token constructors
%define api.value.automove

// use rtti to check symbol use, enable internal YY_ASSERT which is just c++ assert
%define parse.assert

%code provides {
// %code provides goes in generated .h file after namespace and parser class
// everything here needs CWebBisonParser defined earlier

namespace cweb::v4 {
using namespace std;

}

}

%code top {
// %code top is topmost user code block in generated .cpp file just below gnu license

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

}

%{
// unnamed %code block goes in generated .cpp file before #include of generated .h file and before namespace and parser class

%}

%code {
// %code block goes in generated .cpp file after #include of generated .h file and before namespace and parser class

#include <sstream>
#include <string_view>

#include "flexlexer/v4/cweblexer.v4.h"

#include "parserapi/v4/cwebparser_context.v4.h"

using namespace std;
using namespace cweb::v4;

using Mode = BisonParserState::Mode;
using IncludeFileState = BisonParserState::IncludeFileState;

namespace {

// convenience routine to print location
inline string loc(const location& l) {
  return format("loc.begin: {} {}, loc.end: {} {}", l.begin.line, l.begin.column, l.end.line, l.end.column);
}

}

void CWebBisonParser::error(const location& loc, const string& msg) {
  stringstream locstr;
  locstr << loc;
  print(stderr, "CWebBisonParser.error: msg \"{}\" location {}\n", msg, locstr.str());
}

// needed for %define parse.error custom
void CWebBisonParser::report_syntax_error (const CWebBisonParser::context& ctx) const {
  auto n = ctx.expected_tokens(NULL, 0); 
  vector<CWebBisonParser::symbol_kind_type> expectedTokens(n);
  ctx.expected_tokens(expectedTokens.data(), n); 
  string expectedTokensList;
  for(auto i = 0; i < n - 1; ++i) {
    expectedTokensList += string(CWebBisonParser::symbol_name(expectedTokens[i])) + ", ";
  }
  expectedTokensList += CWebBisonParser::symbol_name(expectedTokens[n - 1]);
  stringstream loc;
  loc << ctx.location();
  print(stderr, "CWebBisonParser.report_syntax_error: location \"{}\" token \"{}\" lookahead \"{}\" expected tokens \"{}\" \n", loc.str(), CWebBisonParser::symbol_name(ctx.token()), ctx.lookahead().name(), expectedTokensList);
}

using Mode = BisonParserState::Mode;

}

// all tokens have types, at a minimum token must return a string with the unparsed source text
// functions used by the lexer to create and return these tokens are named after the token enums
// the token string names or aliases are used in the grammar below
%token <string> UNSTARRED_TEX_BEGIN             "@space unstarred tex section"
%token <StarredTexSection> STARRED_TEX_BEGIN    "@* starred tex section"

%token <string> MACRO_BEGIN                     "@d macro def"
%token <MacroName> MACRO_NAME_PARAMS            "macro name params"

%token <FormatDefinition> FORMAT_DEF_BEGIN      "@f format def"
%token <FormatDefinition> SUPPRESSED_FORMAT_DEF "@s suppressed format def"

%token <string> UNNAMED_PROGRAM_SECTION_BEGIN   "@c/@p unnamed program section"


%token <NamedSection> NAMED_SECTION_BEGIN       "@< named section definition @>="

%token <NamedSection> SECTION_NAME              "@< section name @>"
%token <string> FILE_OUTPUT_C_SECTION_BEGIN     "@( file output section @>="
%token <string> EMIT_MACROS_HERE                "@h emit macros here"

%token <IndexEntry> INDEX_ENTRY                 "@^ index entry @>"
%token <IndexEntry> INDEX_TYPEWRITER            "@. index typewriter entry @>"
%token <IndexEntry> INDEX_TEX9                  "@: index tex9 entry @>"
%token <IndexEntry> HBOX_TEXT                   "@t hbox @>"
%token <IndexEntry> VERBATIM_TEXT               "@= verbatim @>"
%token <IndexEntry> COMMENT_TEXT                "@q comment @>"
%token <IndexEntry> INDEX_UNDERLINE             "@! index underline entry @>"

%token <char> ASCII_CHAR                        "@' ascii char"
%token <string> NBSP                            "@& nbsp"
%token <string> LATIN_CHAR                      "@l latin char"

%token <string> THIN_SPACE                      "@, thin space"
%token <string> LINEBREAK                       "@/ linebreak"
%token <string> OPTIONAL_LINEBREAK              "@| optional linebreak"
%token <string> FORCE_LINEBREAK                 "@# linebreak extra space"
%token <string> CANCEL_LINEBREAK                "@+ no linebreak"
%token <string> INVISIBLE_SEMICOLON             "@; invisible semicolon"
%token <string> FORMAT_C_EXPRESSION_BEGIN       "@[ open format expression"
%token <string> FORMAT_C_EXPRESSION_END         "@] close format expression"

%token <IncludeFile> INCLUDE_FILE               "@i include file"

%token <string> INNER_C_CONTEXT_DELIM           "|"

%token <string> C_COMMENT_BEGIN                 "/*"
%token <string> C_COMMENT_END                   "*/"

%token <string> CPLUSPLUS_COMMENT_BEGIN         "//"
%token <string> CPLUSPLUS_COMMENT_END           "eol"

// free means free of cweb control codes and other special characters depending on context
%token <string> FREE_TEXT                       "free text"

%token <string> SINGLE_QUOTE                    "'"
%token <string> DOUBLE_QUOTE                    "\""

%token <string> CPLUSPLUS_RAWSTRING_OPEN        "R\""
%token <string> CPLUSPLUS_RAWSTRING_DELIMITER   "c++ raw string delimiter"

// TEST_PARSE tokens are for unit testing
%token <bool> TEST_PARSE_TEX_PART TEST_PARSE_MIDDLE_PART TEST_PARSE_C_PART

%initial-action {
// %initial-action goes in its own brace scoped block in generated .cpp at top of parse() function, anything declared here is local to this block and cannot be used in the rest of parse()

  publicState.loc.initialize(&publicConfig.infilename);

  @$.initialize(&publicConfig.infilename);
}

%start cweb

%%

// no code allowed in rules section, just bison comments that are dropped from .cpp

// cweb document has sections with optional limbo prolog
cweb:
    documentBegin limbo sections documentEnd
    | documentBegin limbo documentEnd

// special rules for unit tests for single part bypassing sections
    | TEST_PARSE_TEX_PART texBegin tex texEnd
    | TEST_PARSE_MIDDLE_PART middleBegin middle mimddleEnd
    | TEST_PARSE_C_PART cBegin c cEnd
    ;

// limbo has pieces of limbo content
limbo:
     %empty
     | limboBegin limbo_contents limboEnd
     ;

// any number of pieces of limbo content
limbo_contents:
              limbo_content
              | limbo_contents limbo_content
              ;

// piece of limbo content can be some control codes and tex text
limbo_content:
             limbo_control
             | free_text_tex
             ;

// control codes allowed in limbo
limbo_control:
             include_file
             | "@q comment @>" controlTexEvent
             | "@s suppressed format def" formatDefBegin formatDefEnd
             | "@l latin char"
             ;

include_file:
            includeFileBegin "@i include file" includeFileEnd
            ;

// main cweb document has any number of sections
sections:
        section
        | sections section
        ;

// section has 1, 2 or 3 parts
// any part can be empty but a nonempty part must appear in correct order
section:
       texBegin tex texEnd middleBegin middle mimddleEnd cBegin c cEnd
       | texBegin tex texEnd middleBegin middle mimddleEnd
       | texBegin tex texEnd cBegin c cEnd
       | texBegin tex texEnd
       ;

// tex part of a section begins with certain control codes
tex:
   "@space unstarred tex section" unstarredTexSectionBegin tex_contents unstarredTexSectionEnd
   | "@space unstarred tex section" unstarredTexSectionBegin unstarredTexSectionEnd
   | "@* starred tex section"  starredTexSectionBegin tex_contents starredTexSectionEnd
   | "@* starred tex section" starredTexSectionBegin starredTexSectionEnd
   ;

// tex part has any number of pieces of tex content
tex_contents:
            tex_content
            | tex_contents tex_content
            ;

// content allowed in tex part of section includes some control codes and tex text free of control codes
// inner c blocks are valid in tex content
tex_content:
           tex_control
           | inner_c
           | free_text_tex
           ;

// valid control codes in tex section
tex_control:
           control_text
           | include_file
           ;

// middle part of a section has pieces of middle content
middle:
      middle_contents
      ;

// any number of pieces of valid content for middle part
middle_contents:
               middle_content
               | middle_contents middle_content
               ;

// content allowed in middle part of section
middle_content:
              macroBegin "@d macro def" "macro name params" macroNameParamsEvent macro_contents macroEnd
              | macroBegin "@d macro def" "macro name params" macroNameParamsEvent macroEnd
              | "@f format def" formatDefBegin c_comment formatDefEnd
              | "@f format def" formatDefBegin formatDefEnd
              | "@s suppressed format def" formatDefBegin formatDefEnd
              ;

// macro has any number of pieces of macro content
macro_contents:
              macro_content
              | macro_contents macro_content
              ;

// macro allows some control codes and text free of control codes
// comments containing inner c contexts are allowed in macros
macro_content:
             control_text
             | non_tex_control_text
             | c_format_control
             | ctangle_control
             | comment
             | free_text_c
             ;

// the c part of a section begins with certain control codes
c:
 "@c/@p unnamed program section" unnamedProgramSectionBegin c_contents unnamedProgramSectionEnd
 | "@c/@p unnamed program section" unnamedProgramSectionBegin unnamedProgramSectionEnd
 | "@< named section definition @>=" namedSectionBegin c_contents namedSectionEnd
 | "@( file output section @>=" c_contents
 | "@< section name @>" sectionNameEvent c_contents
 | "@< section name @>" sectionNameEvent
 ;

// c part has any number of pieces of c content
c_contents:
          c_content
          | c_contents c_content
          ;

// content allowed in c part includes some control codes and free text
c_content:
         c_control
         | comment
         | c_string
         | cplusplus_rawstring
         | free_text_c
         ;

// valid control codes in c section
c_control:
         control_text
         | non_tex_control_text
         | c_format_control
         | ctangle_control
         | "@< section name @>" sectionNameEvent
         | "@h emit macros here" emitMacrosHereEvent
         | include_file
         ;

// set of control text codes allowed in c, macro, inner c, tex and middle sections
control_text:
            "@^ index entry @>" controlTexEvent
            | "@. index typewriter entry @>" controlTexEvent
            | "@: index tex9 entry @>" controlTexEvent
            | "@q comment @>" controlTexEvent
            | "@! index underline entry @>" controlTexEvent
            ;

// set of control text codes allowed in c, macro, inner c and middle sections but not in tex section
non_tex_control_text:
                    "@t hbox @>"
                    | "@= verbatim @>"
                    ;

// set of control codes to override c formatting for c, macro sections
c_format_control:
                "@, thin space" cFormatControlEvent
                | "@/ linebreak" cFormatControlEvent
                | "@| optional linebreak" cFormatControlEvent
                | "@# linebreak extra space" cFormatControlEvent
                | "@+ no linebreak" cFormatControlEvent
                | "@; invisible semicolon" cFormatControlEvent
                | "@[ open format expression" cFormatExpressionBegin c_content "@] close format expression" cFormatExpressionEnd
                | "@[ open format expression" cFormatExpressionBegin "@] close format expression" cFormatExpressionEnd
                ;

// set of ctangle-specific control codes allowed in c, macro and inner c sections
ctangle_control:
               "@' ascii char"
               | "@& nbsp"
               ;

// both c and c++ style comments are allowed in program code
comment:
       c_comment
       | cplusplus_comment
       ;

// c block comment spans lines
c_comment:
         "/*" cCommentBegin  comment_contents "*/" cCommentEnd
         ;

// c++ single line comment is only till the end of line
cplusplus_comment:
                 cplusplusCommentBegin "//" comment_contents "eol" cplusplusCommentEnd
                 ;

// comment has any number of pieces of content
comment_contents:
                comment_content
                | comment_contents comment_content
                ;

// comment content can have an inner c context block and free text
comment_content:
               free_text_tex
               | inner_c
               ;

c_string:
        cStringBegin "\"" free_text_c "\"" cStringEnd
        ;

cplusplus_rawstring:
                   "R\"" "c++ raw string delimiter" "free text" "c++ raw string delimiter" "\""
                   ;

// inner c context is delimited by pipes
inner_c:
       innerCBegin "|" inner_c_contents "|" innerCEnd
       ;

// inner c context has any number of pieces of content
inner_c_contents:
                inner_c_content
                | inner_c_contents inner_c_content
                ;

// some control codes and free text are allowed in inner c context
inner_c_content:
               control_text
               | non_tex_control_text
               | ctangle_control
               | "@< section name @>" sectionNameEvent
               | "@, thin space"
               | c_string
               | cplusplus_rawstring
               | free_text_c
               ;

free_text_tex:
         "free text" freeTextTexEvent
         ;

free_text_c:
         "free text" freeTextCEvent
         ;

//////////////////////////////////////////////////////////////////////////
// midrule actions
//////////////////////////////////////////////////////////////////////////

documentBegin: %empty {
  for(auto cb: publicConfig.cbs.documentBegin) {
    cb();
  }
}

documentEnd: %empty {
  for(auto cb: publicConfig.cbs.documentEnd) {
    cb();
  }
}

limboBegin: %empty {
  publicState.mode = Mode::limbo;
  for(auto cb: publicConfig.cbs.limboBegin) {
    cb();
  }
}

limboEnd: %empty {
  const Context context = {
    publicState.loc,
    ""
  };
  for(auto cb: publicConfig.cbs.limboEnd) {
    cb(context);
  }
}

texBegin:
        %empty {
  publicState.mode = Mode::tex;
}

texEnd: %empty {
}

starredTexSectionBegin: %empty {
  const auto& [title, text] = $<StarredTexSection>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.starredTexSectionBegin) {
    cb(title, context);
  }
}

starredTexSectionEnd: %empty {
}

unstarredTexSectionBegin: %empty {
  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.unstarredTexSectionBegin) {
    cb(context);
  }
}

unstarredTexSectionEnd: %empty {
}

middleBegin: %empty {
  publicState.mode = Mode::middle;
}

mimddleEnd: %empty {
}

cBegin: %empty {
  publicState.mode = Mode::c;
}

cEnd: %empty {
}

innerCBegin: %empty {
  publicState.nestedModes.push(publicState.mode);
  publicState.mode = Mode::inner_c;

  const auto& text = yyla.value.as<string>();
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.innerCBegin) {
    cb(context);
  }
}

innerCEnd: %empty {
  publicState.mode = publicState.nestedModes.top();
  publicState.nestedModes.pop();

  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.innerCBegin) {
    cb(context);
  }
}

cCommentBegin: %empty {
  publicState.nestedModes.push(publicState.mode);
  publicState.mode = Mode::c_comment;

  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.commentBegin) {
    cb(CommentType::c, context);
  }
}

cCommentEnd: %empty {
  publicState.mode = publicState.nestedModes.top();
  publicState.nestedModes.pop();

  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.commentEnd) {
    cb(CommentType::c, context);
  }
}

cplusplusCommentBegin: %empty {
  publicState.nestedModes.push(publicState.mode);
  publicState.mode = Mode::cplusplus_comment;
}

cplusplusCommentEnd: %empty {
  publicState.mode = publicState.nestedModes.top();
  publicState.nestedModes.pop();
}

cStringBegin: %empty {
  publicState.nestedModes.push(publicState.mode);
  publicState.mode = Mode::c_string;

  const auto& text = yyla.value.as<string>();
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.stringBegin) {
    cb(StringType::quotedC, context);
  }
}

cStringEnd: %empty {
  publicState.mode = publicState.nestedModes.top();
  publicState.nestedModes.pop();

  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.stringEnd) {
    cb(StringType::quotedC, context);
  }
}

freeTextTexEvent: %empty {
  const auto& info = $<string>0;
  const Context context = {
    publicState.loc,
    info
  };
  for(auto cb: publicConfig.cbs.text) {
    cb(info, context);
  }
  if(publicState.includeFileState == IncludeFileState::eof) {
    publicState.includeFile.close();
    publicState.includeFileState = IncludeFileState::closed;
  }
}

freeTextCEvent: %empty {
  const auto& info = $<string>0;
  const Context context = {
    publicState.loc,
    info
  };
  for(auto cb: publicConfig.cbs.text) {
    cb(info, context);
  }
}

includeFileBegin: %empty {
  const auto& info = yyla.value.as<IncludeFile>();
  const auto& [filename, trailingText, text, quoted] = yyla.value.as<IncludeFile>();
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.includeBegin) {
    cb(filename, quoted, trailingText, context);
  }

  string filepath = publicConfig.cwebdir + "/" + info.file;
  auto& file = publicState.includeFile;
  file.open(filepath);
  if(!file.is_open())
    print(stderr, "includeFileBegin: file \"{}\" is not open\n", filepath);
  publicState.includeFileState = IncludeFileState::open;
}

includeFileEnd: %empty {
}

formatDefBegin: %empty {
  const auto& [left, right, text, suppress] = $<FormatDefinition>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.formatDefinitionBegin) {
    cb(left, right, suppress, context);
  }
}

formatDefEnd: %empty {
}

unnamedProgramSectionBegin: %empty {
  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.programSectionBegin) {
    cb(context);
  }
}

unnamedProgramSectionEnd: %empty {
}

namedSectionBegin: %empty {
  const auto& [name, text, isPrefix, isContinuation] = $<NamedSection>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.namedSectionBegin) {
    cb(name, isPrefix, isContinuation, context);
  }
}

namedSectionEnd: %empty {
}

sectionNameEvent: %empty {
  const auto& [name, text, isPrefix, isContinuation] = $<NamedSection>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.sectionName) {
    cb(name, isPrefix, isContinuation, context);
  }
}

macroBegin: %empty {
  publicState.nestedModes.push(publicState.mode);
  publicState.mode = Mode::macro;

  const auto& text = yyla.value.as<string>();
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.macroBegin) {
    cb(context);
  }

}

macroNameParamsEvent: %empty {
  const auto& [name, params, text] = $<MacroName>0;

  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.macroNameParams) {
    cb(name, params, context);
  }
}

controlTexEvent: %empty {
  const auto& [entry, text] = $<IndexEntry>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.controlText) {
    cb(entry, context);
  }

}

macroEnd: %empty {
  publicState.mode = publicState.nestedModes.top();
  publicState.nestedModes.pop();
}

cFormatControlEvent: %empty {
  const auto& token = yystack_[0];

  FormatControlCode code;
  switch(token.kind()) {
  case symbol_kind::S_THIN_SPACE:
    code = FormatControlCode::thinSpace;
    break;
  case symbol_kind::S_LINEBREAK:
    code = FormatControlCode::linebreak;
    break;
  case symbol_kind::S_OPTIONAL_LINEBREAK:
    code = FormatControlCode::optionalLinebreak;
    break;
  case symbol_kind::S_FORCE_LINEBREAK:
    code = FormatControlCode::forceLinebreak;
    break;
  case symbol_kind::S_CANCEL_LINEBREAK:
    code = FormatControlCode::cancelLinebreak;
    break;
  case symbol_kind::S_INVISIBLE_SEMICOLON:
    code = FormatControlCode::invisibleSemicolon;
    break;
  default:
    break;
  }
  const auto& text = token.value.as<string>();
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.formatControl) {
    cb(code, context);
  }
}

emitMacrosHereEvent: %empty {
  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.emitMacrosHere) {
    cb(context);
  }
}

cFormatExpressionBegin: %empty {
  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.formatExpressionBegin) {
    cb(context);
  }

}

cFormatExpressionEnd: %empty {
  const auto& text = $<string>0;
  const Context context = {
    publicState.loc,
    text
  };
  for(auto cb: publicConfig.cbs.formatExpressionEnd) {
    cb(context);
  }

}

%%

// %code epilog block goes at bottom of generated .cpp file after namespace and parser implementation

#ifdef BUILD_MAIN

#include <unistd.h>
#include <getopt.h>

#include <string>
#include <iostream>
#include <optional>
#include <filesystem>

#include <fmt/format.h>

#include "flexlexer/v4/cweblexer.v4.h"
#include "cwebbisonparser.v4.bison.h"
#include "parserapi/v4/cwebparser_callbacks.v4.h"

using namespace std;
using namespace std::filesystem;

using namespace fmt;
using namespace cweb::v4;

int main(int argc, char* argv[])
{
  ios_base::sync_with_stdio(false);

  bool debug = false;
  string cwebfile = "stdin";
  string changefile;

  string* stringOpts[] = {
    &changefile
  };
  int stringOptsIndex = 0;

  option opts[] = {
    {"debug", no_argument, (int*)&debug, 1},
    {"changefile", required_argument, &stringOptsIndex, stringOptsIndex++},
    {0, 0, 0, 0}
  };

// just playing with getopt_long
  for(int i; getopt_long(argc, argv, "", opts, &i) != -1;) {
    if(i > 0) {
      *stringOpts[stringOptsIndex] = optarg;
    }
  }

  if(optind < argc)
    cwebfile = argv[optind];

  CWebLexer lexer;
  Callbacks cbs;
  BisonParserState bisonState;
  BisonParserConfig bisonConfig{cbs, cwebfile, path(cwebfile).parent_path()};

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);

  lexer.set_debug(debug);
  parser.set_debug_level(debug);

  if(auto ev = parser(); ev != 0) {
    print("parse failed\n");
    return ev;
  }

  return 0;
}

#endif
