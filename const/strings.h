#define GPLV3Link "https://www.gnu.org/licenses/gpl-3.0.en.html"
#define copyright "Copyright (c) 2025 Modula.dev"
#define version "gasm 0.0.0\n"

const char contributors[] = "\
John Alex (Modula) <Modula.dev>\n";

const char notice[] = version copyright "\n\
This program is free software: you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, only under version 3 of this license.\n\n\
This program is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n\n";

const char help[] = version "\
\e[0;34mSYNOPSIS\e[0m\n\
\e[0;32m\
    gasm <dest> [sources]\n\
    gasm license\n\
\e[0;34mDESCRIPTION\e[0m\n\
\e[0;32m\
    creates garter bytecode from garter assembly code\n\
\e[0;34mLICENSE\e[0m\n\
\e[0;32m\
    GPLv3, \
\e[0;35m" GPLV3Link "\n\
\e[0m\
    Put briefly; you may redistribute and/or modify this software\n\
    under the terms of the GPLv3 License as published by \n\
    the Free Software Foundation if and only if \n\
    the license and our copyright notice is included:\n\
    \e[0;31m\"" copyright "\"\
\e[0m\n\0";

#define ERROR "\e[0;31merror:\e[0m"
#define HELPCMD "\e[0;32mgasm help\e[0m"
#define HELPDIAG " will bring up the help dialog\n"

const char cmd_help[] = "help";
const char cmd_version[] = "version";
const char cmd_license[] = "license";
const char cmd_contributors[] = "contributors";
const char noargs[] = ERROR " given no inputs, expected two\nrunning " HELPCMD HELPDIAG;
const char badargs[] = ERROR " invalid arguments\nrunning " HELPCMD HELPDIAG;
void printLicense() { printf("%s%s\n", notice, license); }

const char asm_error[] = ERROR " \e[0;35m\"%s\" \e[0mln %d, col %d\n%s\n";
const char asm_expected_instruction[] = "expected an instruction\n";
const char asm_wrong_type[] = "given argument of wrong type\n";
const char asm_redefinition[] = "redefinition of symbol\n";
const char asm_lexerstuck[] = "lexer stuck\n";
const char asm_string_hanging[] = "expected string to be closed\n";
const char asm_number_multidecimal[] = "number contains multiple decimal points\n";
const char asm_number_badcharacter[] = "number contains invalid character\n";
const char asm_symbol_badcharacter[] = "invalid symbol definition or unknown character\n";