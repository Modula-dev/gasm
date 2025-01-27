token_t lexer_consume(char *stream, int max){
    // Data types, ex. bytes

    // Keywords: registers, constants, et cetera

    // Symbolic Names

    // Instructions
}

lexicon_t lexer(char *stream, unsigned int size){
    lexicon_t yield;
    int cursor=0; while(cursor < size) {
        token_t token = lexer_consume(stream + cursor, size - cursor);
        cursor += strlen(token.string);
    }   return yield;
}