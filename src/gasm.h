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
    unsigned int size;
    token_t *tokens;
} lexicon_t;

typedef struct {
    char *source;
    symboltable_t symtable;
    lexicon_t lexicon;
} parse_t;

parse_t gasm_import(parse_t *parent, parse_t *child);
parse_t gasm_load(char *filename);
lexicon_t lexer(char *stream, unsigned int size);
parse_t parser(lexicon_t lexicon);