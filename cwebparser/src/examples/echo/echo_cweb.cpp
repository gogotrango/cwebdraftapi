// echo_cweb.cpp

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

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <string>
#include <iostream>
#include <fstream>

#include "parserapi/v4/cwebparser.v4.h"
#include "echo_cweb_callbacks.h"

using namespace std;

using namespace cweb::v4;
using namespace echo_cweb;

void usage()
{
  puts("Usage: echo_cweb [file]");
  puts("Echo CWEB file to stdout");
  puts("");
  puts("file: CWEB file, default is stdin");
  puts("");
  puts("Examples");
  puts("echo_cweb < miles_span.w");
  puts("echo_cweb miles_span.w");
}

int main(int argc, char* argv[])
{

  ios_base::sync_with_stdio(false);

  bool debug = false;
  option opts[] = {
    {"debug", no_argument, (int*)&debug, 1},
    {"help", no_argument, nullptr, 'h'},
    {0, 0, 0, 0}
  };

  for(int c, i; (c = getopt_long(argc, argv, "dh", opts, &i)) != -1;) {
    switch(c) {
      case 'h':
        usage();
        exit(0);
      case '?':
        usage();
        exit(1);
    }
  }

// set config property to not escape macro newlines
  CWebParser cweb({false});
  EchoCallbacks echoCallbacks;

  cweb.debug(debug);

  if(optind >= argc) {
    return cweb.parse(cin, echoCallbacks);
  }

  ifstream file(argv[optind]);
  if(!file.is_open())
    return 1;
  return cweb.parse(file, echoCallbacks);

}

