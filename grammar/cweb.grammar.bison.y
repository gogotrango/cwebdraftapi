// cweb.grammar.bison.y

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

%token UNSTARRED_TEX_BEGIN             "@space unstarred tex section"
%token STARRED_TEX_BEGIN               "@* starred tex section"

%token MACRO_BEGIN                     "@d macro def"
%token MACRO_NAME_PARAMS               "macro name params"

%token FORMAT_BEGIN                    "@f format def"
%token SUPPRESSED_FORMAT_DEF           "@s suppressed format def"
%token UNNAMED_C_SECTION_BEGIN         "@c/@p unnamed program section"

%token NAMED_SECTION_BEGIN             "@< named section definition @>="

%token SECTION_NAME                    "@< section name @>"
%token FILE_OUTPUT_C_SECTION_BEGIN     "@( file output section @>="
%token EMIT_MACROS_HERE                "@h emit macros here"

%token INDEX_ENTRY                     "@^ index entry @>"
%token INDEX_TYPEWRITER                "@. index typewriter entry @>"
%token INDEX_TEX9                      "@: index tex9 entry @>"
%token HBOX_TEXT                       "@t hbox @>"
%token VERBATIM_TEXT                   "@= verbatim @>"
%token COMMENT_TEXT                    "@q comment @>"
%token INDEX_UNDERLINE                 "@! index underline entry @>"

%token ASCII_CHAR                      "@' ascii char"
%token NBSP                            "@& nbsp"
%token LATIN_CHAR                      "@l latin char"

%token THIN_SPACE                      "@, thin space"
%token LINEBREAK                       "@/ linebreak"
%token OPTIONAL_LINEBREAK              "@| optional linebreak"
%token LINEBREAK_SPACE                 "@# linbreak extra space"
%token CANCEL_LINEBREAK                "@+ no linebreak"
%token INVISIBLE_SEMICOLON             "@; invisible semicolon"
%token FORMAT_C_EXPRESSION_BEGIN       "@[ open format expression"
%token FORMAT_C_EXPRESSION_END         "@] close format expression"

%token INCLUDE_FILE                    "@i include_file"

%token INNER_C_CONTEXT_DELIM           "|"

%token C_COMMENT_BEGIN                 "/*"
%token C_COMMENT_END                   "*/"

%token CPLUSPLUS_COMMENT_BEGIN         "//"
%token CPLUSPLUS_COMMENT_END           "eol"

// free means free of cweb control codes and other special characters depending on context
%token FREE_TEXT                       "free text"

%token SINGLE_QUOTE                    "'"
%token DOUBLE_QUOTE                    "\""
%token CPLUSPLUS_RAWSTRING_OPEN        "R\""
%token CPLUSPLUS_RAWSTRING_DELIMITER   "c++ raw string delimiter"

%start cweb

%%

// cweb document has sections with optional limbo prolog
cweb:
    limbo sections
    | limbo
    ;

// limbo has pieces of limbo content
limbo:
     %empty
     | limbo_contents
     ;

// any number of pieces of limbo content
limbo_contents:
              limbo_content
              | limbo_contents limbo_content
              ;

// piece of limbo content can be some control codes and tex text
limbo_content:
             limbo_control
             | "free text"
             ;

// control codes allowed in limbo
limbo_control:
             "@i include_file"
             | "@q comment @>"
             | "@s suppressed format def"
             | "@l latin char"
             ;

// main cweb document has any number of sections
sections:
        section
        | sections section
        ;

// section has 1, 2 or 3 parts
// any part can be empty but a nonempty part must appear in correct order
section:
       tex middle c
       | tex middle
       | tex c
       | tex
       ;

// tex part of a section begins with certain control codes
tex:
   "@space unstarred tex section" tex_contents
   | "@space unstarred tex section"
   | "@* starred tex section" tex_contents
   | "@* starred tex section"
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
           | "free text"
           ;

// valid control codes in tex section
tex_control:
           control_text
           | "@i include_file"
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
              "@d macro def" "macro name params" macro_contents
              | "@d macro def" "macro name params"
              | "@f format def"
              | "@s suppressed format def"
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
             | "free text"
             ;

// the c part of a section begins with certain control codes
c:
 "@c/@p unnamed program section" c_contents
 | "@c/@p unnamed program section"
 | "@< named section definition @>=" c_contents
 | "@( file output section @>=" c_contents
 | "@< section name @>" c_contents
 | "@< section name @>"
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
         | "free text"
         ;

// valid control codes in c section
c_control:
         control_text
         | non_tex_control_text
         | c_format_control
         | ctangle_control
         | "@< section name @>"
         | "@h emit macros here"
         | "@i include_file"
         ;

// set of control text codes allowed in c, macro, inner c, tex and middle sections
control_text:
            "@^ index entry @>"
            | "@. index typewriter entry @>"
            | "@: index tex9 entry @>"
            | "@q comment @>"
            | "@! index underline entry @>"
            ;

// control text codes allowed in c, macro, inner c and middle sections but not in tex section
non_tex_control_text:
                    "@t hbox @>"
                    | "@= verbatim @>"
                    ;

// set of control codes to override c formatting for c, macro sections
c_format_control:
                "@, thin space"
                | "@/ linebreak"
                | "@| optional linebreak"
                | "@# linbreak extra space"
                | "@+ no linebreak"
                | "@; invisible semicolon"
                | "@[ open format expression" c_content "@] close format expression"
                | "@[ open format expression" "@] close format expression"
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
         "/*" comment_contents "*/"
         ;

// c++ single line comment is only till the end of line
cplusplus_comment:
                 "//" comment_contents "eol"
                 ;

// comment has any number of pieces of content
comment_contents:
                comment_content
                | comment_contents comment_content
                ;

// comment content can have an inner c context block and free text
comment_content:
               "free text"
               | inner_c
               ;

c_string:
        "\"" "free text" "\""
        ;

cplusplus_rawstring:
                   "R\"" "c++ raw string delimiter" "free text" "c++ raw string delimiter" "\""
                   ;

// inner c context is delimited by pipes
inner_c:
       "|" inner_c_contents "|"
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
               | "@< section name @>"
               | "@, thin space"
               | c_string
               | cplusplus_rawstring
               | "free text"
               ;

