// cwebparser.v4.gtest.cpp

#include <unistd.h>
#include <getopt.h>

#include <sstream>
#include <string>
#include <optional>
#include <fmt/format.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "cwebparser.v4.h"

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

TEST(CWebParser, test_0) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");

  CWebParser parser;
  EXPECT_EQ(parser.parse(s), 0);
}

TEST(CWebParser, test_1) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");

  CWebParser parser;
  string result;

  struct MyFuncs {
    function<bool(const string&, const Context&)> text;
  } myfuncs = {
    [&result](const string& text, const Context&) {
      result = text;
      return true;
    }
  };

  EXPECT_EQ(parser.parse(s, myfuncs), 0);
  EXPECT_EQ(result, R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");

}

TEST(CWebParser, test_2) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");

  CWebParser parser;

  struct MyFuncs {
    function<bool(const string&, const Context&)> text = [](const string&, const Context&) {
      return true;
    };
  } myfuncs;

  EXPECT_EQ(parser.parse(s, myfuncs), 0);
}

TEST(CWebParser, test_3) {
  stringstream s(R"%(% This file is part of the Stanford GraphBase (c) Stanford University 1993
)%");

  CWebParser parser;
  auto result = false;

  struct MyFuncs {
    function<bool(const Context&)> documentBegin;
  } myfuncs = {
    [&result](const Context&) {
      result = true;
      return true;
    }
  };

  EXPECT_EQ(parser.parse(s, myfuncs), 0);
  EXPECT_TRUE(result);
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

