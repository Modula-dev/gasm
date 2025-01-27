#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "include/libgyb.h"
#include "include/libgyb.c"
#include "const/license.h"
#include "const/strings.h"
#include "const/opcodes.h"
#include "src/gasm.h"
#include "src/load.c"
#include "src/assemble.c"
#include "src/lexer.c"
#include "src/parser.c"
#include "src/emit.c"

int main (int argc, char **argv) {
    if (argc == 1) { printf(badargs); exit(1); }
    if (argc == 2) {
        if ( argv[1][0]=='-' ) {
        switch(argv[1][1]) {
            case 'h': printf(help); exit(0);
            case 'v': printf(version); exit(0);
            case 'l': printLicense(); exit(0);
            case 'c': printf(contributors); exit(0);
            default: printf(badargs); exit(1);
        }}
        if ( strncmp(argv[1], cmd_help, sizeof(cmd_help))==0 ) { printf(help); exit(0); }
        if ( strncmp(argv[1], cmd_version, sizeof(cmd_version))==0 ) { printf(version); exit(0); }
        if ( strncmp(argv[1], cmd_license, sizeof(cmd_license))==0 ) { printLicense(); exit(0); }
        if ( strncmp(argv[1], cmd_contributors, sizeof(cmd_version))==0 ) { printf(contributors); exit(0); }
        printf(badargs); exit(1);
    }
    assemble(argv[1], argc-2, argv + 2);
}