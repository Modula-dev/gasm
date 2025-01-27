#define argtype_instruction 'I' // USED BY LEXER ONLY
#define argtype_register    'R'
#define argtype_label       'L'
#define argtype_address     'A'
#define argtype_constant    'C'
#define argtype_any         '*'
#define argtype_optional    '?'

typedef struct {
    unsigned char args[6]; // NULL terminated list
    char name[10];
} operation_t;

const operation_t operations[255] = {
    [0x80] = { "RRRR\0", "interrupt" },
    [0x81] = { "****\0", "syscall" },
    [0xA0] = { "RR\0", "compare" },
    [0xA1] = { "RR\0", "add" },
    [0xA2] = { "RR\0", "sub" },
    [0xA3] = { "RR\0", "mul" },    // x86: mul cl
    [0xA4] = { "RR\0", "div" },    // x86: div cl
    [0xA5] = { "RR\0", "left" },   // x86: shl cl
    [0xA6] = { "RR\0", "right" },  // x86: shr cl
    [0xA7] = { "RR\0", "and" },
    [0xA8] = { "RR\0", "or" },
    [0xA9] = { "RR\0", "xor" },
    [0xAA] = { "R\0", "flip" },
    [0xA5] = { "R\0", "inc"},
    [0xA6] = { "R\0", "dec"},
    [0x50] = { "R\0", "push" },
    [0x51] = { "R\0", "pop" },
    [0xBF] = { "L\0", "goto" },
    [0xB1] = { "L\0", "if" },
    [0xB2] = { "L\0", "not" },
    [0xB3] = { "L\0", "lt" },
    [0xB4] = { "L\0", "gt" },
    [0xB5] = { "L\0", "le" },
    [0xB6] = { "L\0", "ge" },
    [0xF8] = { "R\0", "fcast" },   // cvttss2si rax, xmm0
    [0xF9] = { "R\0", "icast" },   // cvtsi2sd xmm0, rax
    [0xFA] = { "R\0", "fmov" },
    [0xFB] = { "R\0", "imov" },    // movd xmm0, rax
    [0xF1] = { "RR\0", "fadd" },   // addsd
    [0xF2] = { "RR\0", "fsub" },   // subsd
    [0xF3] = { "RR\0", "fmul" },   // mulsd
    [0xF4] = { "RR\0", "fdiv" },   // divsd
    [0x90] = { "RR\0", "move"},    // mov
    [0x91] = { "RA\0", "load"},    // mov
    [0x92] = { "RA\0", "store"},   // mov
    [0x93] = { "RC\0", "immediate"}// mov
};

const char registernames[][3] = {
    "ar\0",
    "br\0",
    "cr\0",
    "dr\0",
    "sr\0", // stack pointer
    "sb\0" // stack base pointer
};