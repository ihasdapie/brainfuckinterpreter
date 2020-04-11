
bool shift_right(struct interpreterStruct* interpreter, int tape[]);
bool shift_left(struct interpreterStruct* interpreter, int tape[]);
bool increment(struct interpreterStruct* interpreter, int tape[]);
bool decrement(struct interpreterStruct* interpreter, int tape[]);
bool take_input(struct interpreterStruct* interpreter, int tape[]);
bool output(struct interpreterStruct* interpreter, int tape[]);
bool jump_back(struct interpreterStruct* interpreter);
bool set_loop(struct interpreterStruct* interpreter);

void disp_tape(int tape[], int tape_size);
void t_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file);
void f_runInterpreter(struct interpreterStruct* interptr, int tape[], FILE* input_file, FILE* output_file);



