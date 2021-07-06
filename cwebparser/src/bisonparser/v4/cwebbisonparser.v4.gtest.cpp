// cwebbisonparser.v4.gtest.cpp

#include <unistd.h>
#include <getopt.h>

#include <sstream>
#include <string>
#include <optional>
#include <fmt/format.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "flexlexer/v4/cweblexer.v4.h"
#include "bisonparser/v4/cwebbisonparser.v4.bison.h"

using namespace std;
using namespace placeholders;

using namespace ::testing;
using namespace fmt;

namespace {
  bool debugTest = false;
  ostringstream debugOut;
}

namespace cweb::v4::testing {

using ::testing::MockFunction;
using ::testing::NiceMock;

using Mode = BisonParserState::Mode;

// helper function to reduce code in each test that needs to test parts of the grammar directly without having to provide completely valid input for the entire grammar
// this is done by adding speical start state tokens that are used as starting tokens in special toplevel rules for the nonterminal you want to test
bool testAndUnsetState(CWebBisonParser::symbol_type& state) {
  if(!state.value.as<bool>())
    return false;
  state.value.destroy<bool>();
  state.value.emplace<bool>(false);
  return true;
}

TEST(CWebBisonParser_Limbo, test_0) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_Limbo, test_2) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993

\def\title{MILES\_\,SPAN}
\def\<#1>{$\langle${\rm#1}$\rangle$}

\prerequisite{GB\_\,MILES}
@* Minimum spanning trees.
A classic paper by R. L. Graham and Pavol Hell about the history of
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_Starred, test_03) {
  stringstream s(R"%(@* Minimum spanning trees.
A classic paper by R. L. Graham and Pavol Hell about the history of
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_Starred, test_04) {
  stringstream s(R"%(@* Minimum spanning trees.
A classic paper by R. L. Graham and Pavol Hell about the history of
@^Graham, Ronald Lewis@>
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_05) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993

\def\title{MILES\_\,SPAN}
\def\<#1>{$\langle${\rm#1}$\rangle$}

\prerequisite{GB\_\,MILES}
@* Minimum spanning trees.
A classic paper by R. L. Graham and Pavol Hell about the history of
@^Graham, Ronald Lewis@>
@^Hell, Pavol@>
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_4) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993

\def\title{MILES\_\,SPAN}
\def\<#1>{$\langle${\rm#1}$\rangle$}

\prerequisite{GB\_\,MILES}
@* Minimum spanning trees.
A classic paper by R. L. Graham and Pavol Hell about the history of
@^Graham, Ronald Lewis@>
@^Hell, Pavol@>
algorithms to find the minimum-length spanning tree of a graph
[{\sl Annals of the History of Computing \bf7} (1985), 43--57]
describes three main approaches to that problem. Algorithm~1,
``two nearest fragments,'' repeatedly adds a shortest edge that joins
two hitherto unconnected fragments of the graph; this algorithm was
first published by J.~B. Kruskal in 1956. Algorithm~2, ``nearest
@^Kruskal, Joseph Bernard@>
neighbor,'' repeatedly adds a shortest edge that joins a particular
fragment to a vertex not in that fragment; this algorithm was first
published by V. Jarn\'{\i}k in 1930. Algorithm~3, ``all nearest
@^Jarn{\'\i}k, Vojt\u ech@>
fragments,'' repeatedly adds to each existing fragment the shortest
edge that joins it to another fragment; this method, seemingly the
most sophisticated in concept, also turns out to be the oldest,
being first published by Otakar Bor{\accent23u}vka in 1926.
@^Bor{\accent23u}vka, Otakar@>
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_005) {
  stringstream s(R"%(@p
#include "gb_graph.h" /* the GraphBase data structures */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_C_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_0055) {
  stringstream s(R"%(@ @p
#include "gb_save.h" /* |restore_graph| */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  lexer.set_debug(debugTest);
  parser.set_debug_level(debugTest);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_0057) {
  stringstream s(R"%(@p
#include "gb_save.h" /* |restore_graph| */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_C_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  lexer.set_debug(debugTest);
  parser.set_debug_level(debugTest);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_006) {
  stringstream s(R"%(@p
#include "gb_graph.h" /* the GraphBase data structures */
#include "gb_save.h" /* |restore_graph| */
#include "gb_miles.h" /* the |miles| routine */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_C_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  lexer.set_debug(debugTest);
  parser.set_debug_level(debugTest);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_007) {
  stringstream s(R"%(@ The graphs we will deal with are produced by the |miles| subroutine,

@p
#include "gb_graph.h" /* the GraphBase data structures */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  lexer.set_debug(debugTest);
  parser.set_debug_level(debugTest);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser, test_5) {
  stringstream s(R"%(@ The graphs we will deal with are produced by the |miles| subroutine,
found in the {\sc GB\_\,MILES} module. As explained there,
|miles(n,north_weight,west_weight,pop_weight,0,max_degree,seed)| produces a
graph of |n<=128| vertices based on the driving distances between
North American cities. By default we take |n=100|, |north_weight=west_weight
=pop_weight=0|, and |max_degree=10|; this gives billions of different sparse
graphs, when different |seed| values are specified, since a different
random number seed generally results in the selection of another
one of the $\,128\,\choose100$ possible subgraphs.

@^UNIX dependencies@>

Here is the overall layout of this \CEE/ program:

@p
#include "gb_graph.h" /* the GraphBase data structures */
#include "gb_save.h" /* |restore_graph| */
#include "gb_miles.h" /* the |miles| routine */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_CPart, test_009) {
  stringstream s(R"%(@p
#include "gb_graph.h" /* the GraphBase data structures */
#include "gb_save.h" /* |restore_graph| */
#include "gb_miles.h" /* the |miles| routine */
@h@#
@<Global variables@>@;
@<Procedures to be declared early@>@;
@<Priority queue subroutines@>@;
@<Subroutines@>@;
main(argc,argv)
  int argc; /* the number of command-line arguments */
  char *argv[]; /* an array of strings containing those arguments */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_C_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_Macros, test_010) {
  stringstream s(R"%(@d o mems++

)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_MIDDLE_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_Macros, test_013) {
  stringstream s(R"%(@ @d qsib b.A /* pointer to next larger sibling, or from largest to smallest */

@ A special header node is used at the head of a binomial queue, to represent
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebBisonParser_FormatC, test_011) {
  stringstream s(R"%(@<Glob...@>=
void @[@] (*init_queue)(); /* create an empty priority queue */
)%");
  CWebLexer lexer(&s);
  BisonParserState bisonState{Mode::tex};
  BisonParserConfig bisonConfig;

  auto startState = CWebBisonParser::make_TEST_PARSE_C_PART(true, location{});
  CWebBisonParser parser([&lexer, &startState](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return testAndUnsetState(startState)? startState: lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  lexer.set_debug(debugTest);
  parser.set_debug_level(debugTest);
  EXPECT_EQ(parser(), 0);
}

TEST(CWebParser, test_014) {
  stringstream s(R"%(@ @ @ @ @ @ @ @ @c@ )%");
  CWebLexer lexer(&s);
  BisonParserState bisonState;
  BisonParserConfig bisonConfig;

  CWebBisonParser parser([&lexer](BisonParserState& parserState) -> CWebBisonParser::symbol_type {
    return lexer.yylex(parserState);
  }, bisonState, bisonConfig);
  EXPECT_EQ(parser(), 0);
}


}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  option opts[] = {
    {"debug", no_argument, NULL, 0},
    {0, 0, 0, 0}
  };
  if(getopt_long(argc, argv, "", opts, NULL) != -1) {
    debugTest = true;
  }

  return RUN_ALL_TESTS();
}

