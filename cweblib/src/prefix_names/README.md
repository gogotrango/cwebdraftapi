# PrefixNames

`PrefixNames` is a class based on the `name_info` data structure used for storing names of sections in the CWEB system for code documentation. It stores strings called names that can be looked up and updated by any unique prefix. Each name has associated user data. Names may be entered and looked up by any prefix before the complete name is known.

## The CWEB Code Documentation System

CWEB is a document format language created by Donald Knuth and Silvio Levy. It combines C or C++ source code with documentation written in the TeX typesetting language. The main idea is to develop a narrative for the program that incorporates source code as it is written. Then the CWEB file maybe used to produce high-quality documentation or compilable source files. CWEB is maintained at https://github.com/ascherer/cweb.

## The Structure of a CWEB Document

A CWEB document has sections. Each section has a TeX part and a code part. The code part can have a name that is taken as the name of the section. The C/C++ source code is called the replacement of the section.

Here is a section named `"Check if next token is |include|"`

```c++
@<Check if next token is |include|@>=
while(loc <= buffer_end - 7 && xisspace(*loc)) {
  loc++;
}
if(loc <= buffer_end - 6 && strncmp(loc, "include", 7) == 0) {
  sharp_include_line = true;
}
```

This section can be used by name in other sections. Here the `"Check if next token is |include|"` section  is used in a section called `"Raise prep..."`. The three dots or ellipsis at the end of a name indicate it is a prefix of some name.

```c++
@<Raise prep...@>= {
  preprocessing = true;
  @<Check if next token is |include|@>;
  return left_preproc;
}
```

A section need not be defined in one place. It may be defined in pieces at multiple locations. The pieces are concatenated in the order they appear in the document to form the complete replacement of the section.

A section may be called by any prefix of its name as shown above. Here's the full name for the `"Raise prep..."` section, `"Raise preprocessor flag"`, that occurs in another section.

```c++
if( c=='#' && loc == buffer + 1) @<Raise preprocessor flag@>
```

A section may be used before it is defined. Also it may be used or defined by a prefix before its complete name occurs in the document.

## How are Section Names Used?

There are two main uses of a CWEB document. One is to generate a valid source code file that can be compiled. The other is to generate a TeX file for documentation that can be rendered to a high-quality publishing format like PDF.

Section names are treated differently depending on the outcome. If the goal is to generate a source code file to compile, all the replacements for a section name are joined and output together wherever the section name is used. On the other hand if the result is meant to be published, section names are displayed in the output along with cross-references and are included in the index.

This means the data associated with a section name can be markedly different depending on the application.

## Features of Section Names

Now that we've seen the meaning of a section name in a CWEB document and how sections are used, let's go over the features needed to support section names.

- A name can be a string of any length
- A name can have any kind of characters
- Any unique prefix of the name may be used to refer to the same name
- A name and its prefixes may occur in the document in any order any number of times
- A name can have any kind of associated data
- There can be any number of names in a CWEB document

## Representing Section Names in CWEB Tools

Section names are implemented in the CWEB system with the `name_info` data structure and the `name_dir` API.

### The name_info data structure

The `name_info` data structure is a combined linked list and binary search tree for storing and retrieving section names.

```c++
typedef struct name_info {
  char *byte_start;              /* beginning of the name in |byte_mem| */
  struct name_info *link;        /* aka llink, left link in binary search tree */
  union {
    struct name_info *Rlink;     /* aka rlink, right link in binary search tree for section names */
    char Ilk;                    /* used by identifiers in \.{CWEAVE} only */
  } dummy;
  void *equiv_or_xref;           /* info corresponding to names */
} name_info;                     /* contains information about an identifier or section name */
```

### The name_dir directory of names and its API

All names in a CWEB document are entered into the global `name_dir` array of `name_info` objects

```c++
name_info name_dir[max_names];       /* information about names */
typedef name_info *name_pointer;     /* pointer into array of \&{name\_info}s */
```

There is just a single API, `section_lookup`

```c++
name_pointer section_lookup(         /* find or install section name in tree */
char *first, char *last,             /* first and last characters of new name */
boolean ispref)                      /* is the new name a prefix or a full name? */
```

`section_lookup` returns the `name_info` entry for the given name. The entry may be newly created if the name did not match any existing entry.

### More about name_info fields

### The name string - byte_start

The `byte_start` field points to the start of the name string in a big array that contains strings for all names stored next to each other.

### A linked list of chunks of a single name - link

The `link` field of `name_info` forms a linked list of `name_info` nodes. Each `name_info` node is a chunk of the complete name. The complete name is formed by starting at the first node in the linked list and following the nodes for each chunk till the end.

### A binary search tree of all names - llink and rlink

The `link` and `Rlink` fields of `name_info` form a binary tree of `name_info` nodes. When used for tree traversal `link` is known as `llink` for left child link and `Rlink` is known as `rlink` for right child link. Each `name_info` node in the tree is the first node of a name. The binary tree is ordered lexicographically with the left child less than the node and right child greater than the node.

### User data - equiv_or_xref

The `void* equiv_or_xref` field holds user data initialized by the application. Since only two CWEB applications exist so far, the field is named after both uses - but only one or the other is used in one program. CTANGLE uses it as `equiv` and CWEAVE calls it `xref`.

### Clever tricks

There are a few clever tricks at play in `name_info`!

### `link` and its alter ego `llink`
The first puzzling question is how can a single field serve double duty?

If `link` can sometimes point to the next chunk of the same name, how can it point to a different name another time. There is no tag field or extra information in `name_info` itself to tell whether `link` represents a linked list or it's actually `llink` representing the binary search tree.

The answer is in the way a new name is added to the directory.

If the name is complete and not a prefix, it means no future chunks will occur and `link` is always `llink` in the tree.

On the the other hand if the name is a prefix, at least one more chunk is expected. In this case the API reserves the next `name_info` entry in the directory for this name. And again `link` in the first node can safely be used for the tree.

This means the complete string is not formed by strictly following the `link` field in every node. The linked list if needed actually starts with the second node. And the second node is the one following the first node in `name_dir`.

### Prefix or not?

This begs the second question. How do we know when to use the second node and when not?

The second node is only needed if the first chunk is incomplete and is a prefix. Again there is no field in `name_info` that stores this information. Instead this is encoded in the string. A prefix string is stored with a trailing space character. So for any name, checking the character just before the name string begins for the following `name_info` entry tells us if this name is a prefix or not.

The same technique of using the starting string point of the following entry is used to determine the length of the name string

### Shortest prefix

The final trick is used to efficiently compare two names without following the chunks of an existing name

This is done by comparing a given name with the shortest prefix seen thus far of an existing name. If the name being looked up matches the shortest prefix it is taken to be the same name. Otherwise it is a new name and its relative position in the binary search tree is known.

Yet again we notice there is no field in `name_info` that stores information about the shortest prefix. Again the answer lies in the name string. The first two bytes of the stored string actually make up a 16-bit length of the shortest prefix. These two bytes are updated whenever a shorter prefix of a name is found.

