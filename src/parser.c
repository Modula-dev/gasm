int parser_consume(parse_t *state, token_t *stream, int depth){
    // Sections and other high-level state commands

    // Definitions; bytes, symbols, et

    // System Call instructions

    // Regular assembly instructions
}

parse_t parser(lexicon_t lexicon) {
    parse_t yield; int cursor;
    while(cursor < lexicon.size) {
        int step = parser_consume(&yield, lexicon.tokens + cursor, lexicon.size-cursor);
        cursor += step;
    }   return yield;
}