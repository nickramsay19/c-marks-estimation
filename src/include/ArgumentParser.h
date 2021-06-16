#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>
#include "argp/argp.h"

//const char *argp_program_version = "argp-ex3 1.0";
//const char *argp_program_bug_address = "<bug-gnu-utils@gnu.org>";

// Program documentation.
char doc[] = "Argp example #3 -- a program with options and arguments using argp";

// A description of the arguments we accept.
char args_doc[] = "ARG1 ARG2";

// The options we understand.
struct argp_option options[] = {
  {"verbose",  'v', 0,      0,  "Produce verbose output" },
  {"quiet",    'q', 0,      0,  "Don't produce any output" },
  {"silent",   's', 0,      OPTION_ALIAS },
  {"output",   'o', "FILE", 0,
   "Output to FILE instead of standard output" },
  { 0 }
};

// Used by main to communicate with parse_opt.
struct arguments
{
  char *args[2]; // arg1 & arg2 
  int silent, verbose;
  char *output_file;
};

// Parse a single option.
error_t parse_opt(int key, char *arg, struct argp_state *state);

// Our argp parser
struct argp Argp = { options, parse_opt, args_doc, doc };

#endif