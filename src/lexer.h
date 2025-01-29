#define parsetype_macro     'M'
#define parsetype_sys       'S'
#define parsetype_instr     'I'
#define parsetype_size      '^'
#define parsetype_address   'A'
#define parsetype_label     'L'
#define parsetype_data      'D'

typedef struct {
    char name[16];
    unsigned char type; // used for parser matching
    unsigned char args;
    char *matches;
} assoc_t;

assoc_t section_names[] = {
    { "section",    'M', parsetype_macro, NULL },
    { "readable",   'M', symboltype_readable, NULL },
    { "writable",   'M', symboltype_writeable, NULL },
    { "executable", 'M', symboltype_executable, NULL }
};

assoc_t datasizes[] = {
    { "u8",  '^', 1, NULL },
    { "u16", '^', 2, NULL },
    { "u32", '^', 4, NULL },
    { "u64", '^', 8, NULL }
};

assoc_t syscalls[255] = {
    [0]     { "read",   'S', 3, NULL },
    [1]     { "write",  'S', 3, NULL },
    [2]     { "open",   'S', 2, NULL },
    [3]     { "close",  'S', 1, NULL },
    [12]    { "brk",    'S', 1, NULL },
    [57]    { "fork",   'S', 0, NULL },
    [59]    { "exec",   'S', 3, NULL },
    [60]    { "exit",   'S', 1, NULL }
};

assoc_t keywords[255] = {
    [gybh_move]     { "move",       'I', 2, "RR" },
    [gybh_load]     { "load",       'I', 2, "R^A" },
    [gybh_store]    { "store",      'I', 2, "R^A" },
    [gybh_imm]      { "immediate",  'I', 2, "RC" },
    [gybh_push]     { "push",       'I', 1, "R" },
    [gybh_pop]      { "pop",        'I', 1, "R" },
    [gybh_cmp]      { "compare",    'I', 2, "RR" },
    [gybh_add]      { "add",        'I', 2, "RR" },
    [gybh_sub]      { "sub",        'I', 2, "RR" },
    [gybh_mul]      { "mul",        'I', 2, "RR" },
    [gybh_div]      { "div",        'I', 2, "RR" },
    [gybh_left]     { "left",       'I', 2, "RR" },
    [gybh_right]    { "right",      'I', 2, "RR" },
    [gybh_and]      { "and",        'I', 2, "RR" },
    [gybh_or]       { "or",         'I', 2, "RR" },
    [gybh_xor]      { "xor",        'I', 2, "RR" },
    [gybh_flip]     { "flip",       'I', 1, "R" },
    [gybh_fadd]     { "fadd",       'I', 2, "RR" },
    [gybh_fsub]     { "fsub",       'I', 2, "RR" },
    [gybh_fmul]     { "fmul",       'I', 2, "RR" },
    [gybh_fdiv]     { "fdiv",       'I', 2, "RR" },
    [gybh_fmov]     { "fmov",       'I', 1, "R" },
    [gybh_fcast]    { "fcast",      'I', 1, "R" },
    [gybh_imov]     { "imov",       'I', 1, "R" },
    [gybh_icast]    { "icast",      'I', 1, "R" },
    [gybh_goto]     { "goto",       'I', 1, "L" },
    [gybh_if]       { "if",         'I', 1, "L" },
    [gybh_else]     { "else",       'I', 1, "L" },
    [gybh_lt]       { "lt",         'I', 1, "L" },
    [gybh_gt]       { "gt",         'I', 1, "L" },
    [gybh_le]       { "le",         'I', 1, "L" },
    [gybh_ge]       { "ge",         'I', 1, "L" },
    [gybh_sys1]     { "sys1",       'I', 1, "R" },
    [gybh_sys2]     { "sys2",       'I', 2, "RR" },
    [gybh_sys3]     { "sys3",       'I', 3, "RRR" },
    [gybh_sys4]     { "sys4",       'I', 4, "RRRR" }
};