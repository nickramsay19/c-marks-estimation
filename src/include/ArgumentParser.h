#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <stdlib.h>
#include "argp/argp.h"

// Used by main to communicate with parse_opt.
struct arguments
{
    char *args[2]; // arg1 & arg2 
    int silent, verbose;
    char *output_file;
};

// Parse a single option.
error_t parse_opt(int key, char *arg, struct argp_state *state);

#endif