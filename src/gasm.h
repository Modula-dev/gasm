#define register_t  unsigned char
#define label_t     uint32_t        // symbol hash, must be in E section
#define constant_t  uint32_t        // symbol hash, must be constant-type
#define address_t   uint32_t        // symbol hash, any section allowed
#define symbol_t    uint32_t        // symbol hash, any allowed

typedef struct {
    unsigned int ln; unsigned int col;
    unsigned char type; unsigned int value; // symbol, const, whatever
    char *string; // null terminated
} token_t;

typedef struct {
    int size; int index;
    token_t *tokens;
} lexicon_t;

void gasm_load(gybfile_t *context, char *filename);
void parser(gybfile_t *context, lexicon_t lexicon);
lexicon_t lexer(char *stream, int size);

unsigned char   assembler_section = 0;
unsigned char   assembler_datasize = 0;
unsigned int    assembler_ln;
unsigned int    assembler_col;
char           *assembler_filename = NULL;
