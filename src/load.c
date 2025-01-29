void gasm_load(gybfile_t *context, char *filename) {
    // Update the shared-state variables; used for erroring and stuffs
    assembler_section = '\0'; assembler_ln = 0; assembler_col = 0;
    assembler_filename = filename;
    // Load the file
    int size = file_size(filename);
    char *buffer = malloc(sizeof(size));
    file_read(filename, buffer, size);
    // process the file
    lexicon_t lexicon = lexer(buffer, size);
    parser(context, lexicon);
}