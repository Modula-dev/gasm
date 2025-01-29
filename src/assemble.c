void assembler_error(const char *error) {
    printf(asm_error,
        assembler_filename, assembler_ln, assembler_col, error
    ); exit(1);
}

int assemble(char *filename, int srcn, char **srcs){
    gybfile_t object = gyb_bytecode_new();
    int i; for (i=0; i<srcn; i++) { gasm_load(&object, srcs[i]); }
    return gyb_bytecode_save(filename, object);
}