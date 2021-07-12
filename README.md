# Untangling CWEB

This is a work in progress. It has various components meant to work with the CWEB code documentation system created by Donald Knuth and Silvio Levy.

The CWEB system comprises a document format language and tools for working with files in CWEB format. These tools have custom parsers and data structures.

This project, `cwebdraftapi`, is an attempt to create components that may be used to more easily write applications for CWEB documents. Some of these components are written from scratch. Others are derived from or based on source code and documentation of official CWEB tools.

The components are designed to be small, reusable and threadsafe. All components are written in C++.

The main categories of components are

- Parser

- Library of data structures

- Tools

## Getting Started

The discussions in https://github.com/gogotrango/cwebdraftapi/discussions are a good place to start while this project is in an early design and development phase. If you are interested in CWEB in any way this is a chance to let me know how this project may help you.

The CWEB grammar in https://github.com/gogotrango/cwebdraftapi/tree/main/grammar will help you understand the CWEB document format.

The CWEB parser API in https://github.com/gogotrango/cwebdraftapi/blob/main/cwebparser/src/parserapi/v4/cwebparser.v4.h will be the primary interface for working with CWEB documents. Sample applications of the API are in https://github.com/gogotrango/cwebdraftapi/tree/main/cwebparser/src/examples.

Data structures useful for representing and manipulating CWEB constructs may be found in https://github.com/gogotrango/cwebdraftapi/blob/main/cweblib.

