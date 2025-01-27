void assembler_error(token_t token, parse_t *context, const char *error) {
    printf("\e[0;31merror:\e[0;33m%s\e[0m, ln %d col %d\n%s",
        context->source,
        token.ln, token.col, error
    ); exit(1);
}

int assemble(char *filename, int srcn, char **srcs){
    gybfile_t object = bytecode_new();
    int i; for (i=0; i<srcn; i++) {
        parse_t local = gasm_load(srcs[i]);
    }
    return bytecode_save(filename, object);
}