void lexicon_push(lexicon_t *lexicon, token_t token) {
    if ( lexicon->size <= sizeof(token_t)*(lexicon->index) ) {
        lexicon->size *= 2;
        lexicon->tokens = realloc(lexicon->tokens, lexicon->size);
    }   memcpy(&lexicon->tokens[lexicon->index], &token, sizeof(token_t));
}

int len_nonwsp(char *stream, int max) {
    int i; for(i=0;i<max;i++) {
    switch(stream[i]){ case ' ': case '\r': case '\t': case ',': case '\n': return i; }}
}

int len_whitespace(char *stream, int max) {
    int i; for(i=0;i<max;i++) {
        switch(stream[i]){
            case ' ': case '\r': case '\t': case ',':
                assembler_col++;
                break;
            case '\n':
                assembler_ln++;
                assembler_col=0;
                break;
            default: return i;
        }}
}

int len_string(char *stream, int max) {
    char c; int i=0;
    switch(stream[0]) {
        case '`': case '"': case '\'': c = stream[0]; break;
        default: return 0; }
    while(stream[i]!=0) {
        if ( stream[i] == c ) { return i+1; }
        i++; }
    // if we never get the ending quote, error
    assembler_error(asm_string_hanging);
}

int len_number(char *stream, int max) {
    bool hex=false; bool octal=false; int decimal=0;
    int i; for(i=0;i<max;i++) {
        if ( i == 0 && stream[i] == '-' ) { continue; }
        if ( i == 0 && stream[i] == '0' ) { continue; }
        if ( i == 1 && stream[i] == 'x' ) { hex = true; continue; }
        if ( i == 1 && stream[i] == 'o' ) { octal = true; continue; }
        if ( stream[i] <= '9' && stream[i] >= '0' ) { continue; }
        if ( stream[i] <= 'f' && stream[i] >= 'a' && hex == true ) { continue; }
        if ( stream[i] <= 'F' && stream[i] >= 'A' && hex == true ) { continue; }
        if ( hex == false && octal == false && stream[i] == '.' ) { decimal++; continue; }
    }   return i;
}

int value_number(char *stream, int max) {
    int base = 10; int cursor = 0; bool negative=false;
    int value = 0; int decimal = 0; int point = -1;
    if ( max > 2 ) { if (stream[0] == '0') {
        if ( stream[1] == 'x' ) { cursor = 2; base = 16; }
        if ( stream[1] == 'o' ) { cursor = 2; base = 8; }
    }}
    while(cursor < max) {
        if ( point == -1 ) { // integers
            if ( cursor == 0 && stream[cursor] == '-' ) { negative = true; cursor++; continue; }
            if ( stream[cursor] <= '0'-1+base && stream[cursor] >= '0' ) { value *= base; value += stream[cursor] - '0'; cursor++; continue; }
            if ( stream[cursor] <= 'f' && stream[cursor] >= 'a' && base == 16) { value *= base; value += stream[cursor] - 'a'+10; cursor++; continue; }
            if ( stream[cursor] <= 'F' && stream[cursor] >= 'A' && base == 16) { value *= base; value += stream[cursor] - 'A'+10; cursor++; continue; }
            if ( stream[cursor] == '.' && base == 10 ) { point = 1; continue; }
        } else {
            if ( stream[cursor] <= '9' && stream[cursor] >= '0' ) { decimal *= base; point*=10; decimal += stream[cursor] - '0'; cursor++; continue; }
            if ( stream[cursor] == '.' ) { assembler_error(asm_number_multidecimal); }
        }
        assembler_error(asm_number_badcharacter); // if we aren't doing a continue && aren't breaking out, then something is wrong
    }
    if ( point != -1 ) {
        float fvalue = ( value ) + ( decimal / point );
        memcpy(&fvalue, &value, sizeof(float));
    }
    return value;
}

int len_symbol(char *stream, int max) {
    int i; for(i=0;i<max;i++){
        if ( stream[i] >= 'a' && stream[i] <= 'z' ) { continue; }
        if ( stream[i] >= 'A' && stream[i] <= 'Z' ) { continue; }
        if ( stream[i] >= '0' && stream[i] <= '9' && i != 0 ) { continue; }
        if ( stream[i] == '_' || stream[i] == '$' ) { continue; }
    }   return i;
}

unsigned int lexer_fetch(lexicon_t *lexicon, char *stream, int max){
    int len; int i;
    // skip over whitespace
    len=len_whitespace(stream, max); while( len !=0 ) { stream+=len; max-=len; len=len_whitespace(stream, max); }
    // if NULL, break
    if ( stream[0]==0 ) { return 0; }
    // prep token
    token_t result = { .ln = assembler_ln, .col = assembler_col, };
    // check string
    len = len_string(stream, max); if ( len != 0 ) {
        result.type = parsetype_data;
        result.string = stream + 1; // skip the first quote
        result.value = assembler_datasize;
        stream[len-1] = '\0'; // && null terminate it
        lexicon_push(lexicon, result);
        return len;
    }
    // check numbers
    len = len_number(stream, max); if ( len != 0 ) {
        result.type = parsetype_data;
        result.string = stream;
        result.value = value_number(stream, len);
        stream[len+1] = '\0';
        lexicon_push(lexicon, result);
        return len + 1;
    }
    // check for sections
    for(i=0;i<4;i++) {
    if ( strncmp(section_names[i].name, stream, len_nonwsp(stream, max))==0 ) {
        result.type = parsetype_macro; result.string = section_names[i].name; result.value = section_names[i].args;
        stream[len] = '\0'; lexicon_push(lexicon, result); return len+1;
    }}
    // check for data sizes
    for(i=0;i<4;i++) {
    if ( strncmp(datasizes[i].name, stream, len_nonwsp(stream, max))==0 ) {
        result.type = parsetype_size; result.string = section_names[i].name; result.value = section_names[i].args;
        stream[len] = '\0'; lexicon_push(lexicon, result); return len+1;
    }}
    // check for syscalls
    for(i=0;i<255;i++) {
    if ( syscalls[i].type != 'S' ) { continue; }
    if ( strncmp(syscalls[i].name, stream, len_nonwsp(stream, max))==0 ) {
        result.type = parsetype_sys; result.string = syscalls[i].name; result.value = syscalls[i].args;
        stream[len] = '\0'; lexicon_push(lexicon, result); return len+1;
    }}
    // check for keywords
    for(i=0;i<255;i++) {
    if ( keywords[i].type != 'I' ) { continue; }
    if ( strncmp(keywords[i].name, stream, len_nonwsp(stream, max))==0 ) {
        result.type = parsetype_sys; result.string = keywords[i].name; result.value = keywords[i].args;
        stream[len] = '\0'; lexicon_push(lexicon, result); return len+1;
    }}
    // if none of those things, we're probably looking at a symbol
    len = len_symbol(stream, max); i = len_nonwsp(stream, max);
    if ( len != i ) { assembler_error(asm_symbol_badcharacter); }
    // make a note of the section its in
    if ( assembler_section == section_executable ) { result.type = parsetype_label; }
    else { result.type = parsetype_address; }
    // redefinition checks happen during parsing, not lexing
    result.string = stream; stream[len] = '\0'; result.value = symbolhash(stream);
    lexicon_push(lexicon, result); return len+1;
}

lexicon_t lexer(char *stream, int streamlen){
    lexicon_t lexicon;
    unsigned int cursor=0; while(cursor < streamlen) {
        unsigned int n = lexer_fetch(&lexicon, stream + cursor, streamlen - cursor);
        if ( n == 0) { assembler_error(asm_lexerstuck); exit(1); }
        cursor += n; assembler_ln += n;
    }   return lexicon;
}