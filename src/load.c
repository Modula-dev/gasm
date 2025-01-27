parse_t gasm_import(parse_t *parent, parse_t *child) {
    // Clone in the symbols

    // Clone in the lexicon
}
parse_t gasm_load(char *filename) {
    // Read and perform lexical analysis
    unsigned int source_length = file_size(filename);
    char *buffer = malloc(sizeof(char)*source_length);
    file_read(filename, buffer, source_length);
    lexicon_t lexicon = lexer(buffer, source_length);
    free(buffer);
    // Then parse
    parse_t yield = parser(lexicon);
    yield.source = filename;
    return yield;
}