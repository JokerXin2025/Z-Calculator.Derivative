/// 2025 Z·Calculator.Derivative

# include "_Derivative.h"

// Constant Macros

# define D_FunctionCheck(Node,Type) Node->category == OPERATION && Node->type == &Derivative && Node->child_l->category == FUNCTION && Node->child_l->type == Type && Node->child_r->category == OBJECT && Node->child_r->type == &Variable

# define D_OperationCheck(Node,Type) Node->category == OPERATION && Node->type == &Derivative && Node->child_l->category == OPERATION && Node->child_l->type == Type && Node->child_r->category == OBJECT && Node->child_r->type == &Variable

// Function-like Macros

# define D_sequence_Set_0(Num,Name) \
    D_single_sequence[Num] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][0] = (void * * *)trans_invoke; \
    D_single_sequence[Num][1] = malloc(3 * sizeof(void *)); \
    D_single_sequence[Num][1][0] = (void * *)trans_format_p; \
    D_single_sequence[Num][1][1] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][1][1][0] = (void * *)D_##Name##_; \
    D_single_sequence[Num][1][1][1] = (void * *)D_##Name; \
    D_single_sequence[Num][1][2] = NULL

# define D_sequence_Set_1(Num,Name,PosSequence) \
    D_single_sequence[Num] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][0] = (void * * *)trans_invoke; \
    D_single_sequence[Num][1] = malloc(4 * sizeof(void *)); \
    D_single_sequence[Num][1][0] = (void * *)trans_format_p; \
    D_single_sequence[Num][1][1] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][1][1][0] = (void * *)D_##Name##_; \
    D_single_sequence[Num][1][1][1] = (void * *)D_##Name; \
    D_single_sequence[Num][1][2] = malloc(3 * sizeof(void *)); \
    D_single_sequence[Num][1][2][0] = Derivative_single; \
    D_single_sequence[Num][1][2][1] = PosSequence; \
    D_single_sequence[Num][1][2][2] = NULL; \
    D_single_sequence[Num][1][3] = NULL

# define D_sequence_Set_2(Num,Name,PosSequence1,PosSequence2) \
    D_single_sequence[Num] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][0] = (void * * *)trans_invoke; \
    D_single_sequence[Num][1] = malloc(5 * sizeof(void *)); \
    D_single_sequence[Num][1][0] = (void * *)trans_format_p; \
    D_single_sequence[Num][1][1] = malloc(2 * sizeof(void *)); \
    D_single_sequence[Num][1][1][0] = (void * *)D_##Name##_; \
    D_single_sequence[Num][1][1][1] = (void * *)D_##Name; \
    D_single_sequence[Num][1][2] = malloc(3 * sizeof(void *)); \
    D_single_sequence[Num][1][2][0] = Derivative_single; \
    D_single_sequence[Num][1][2][1] = PosSequence1; \
    D_single_sequence[Num][1][2][2] = NULL; \
    D_single_sequence[Num][1][3] = malloc(3 * sizeof(void *)); \
    D_single_sequence[Num][1][3][0] = Derivative_single; \
    D_single_sequence[Num][1][3][1] = PosSequence2; \
    D_single_sequence[Num][1][3][2] = NULL; \
    D_single_sequence[Num][1][4] = NULL

# define E_sequence_Set(Num,Name) \
    E_utmost_sequence[Num] = malloc(2 * sizeof(void *)); \
    E_utmost_sequence[Num][0] = (void * *)trans_format_p; \
    E_utmost_sequence[Num][1] = malloc(2 * sizeof(void *)); \
    E_utmost_sequence[Num][1][0] = E_##Name##_; \
    E_utmost_sequence[Num][1][1] = E_##Name

// Type Definitions

object_type Primer = {"Primer"};
object_type Variable = {"Variable"};
object_type Real = {"Real"};
object_type Parser_Primer = {"Parser's Primer"};

function_type Root = {"Root", NULL};
function_type Square_Root = {"Square Root", "sqrt"};
function_type Cube_Root = {"Cube Root", "cbrt"};
function_type Natural_Exponent = {"Natural Exponent", "e^"};
function_type Decimal_Exponent = {"Decimal Exponent", "10^"};
function_type Natural_Logarithm = {"Natural Logarithm", "ln"};
function_type Decimal_Logarithm = {"Decimal Logarithm", "lg"};
function_type Sine = {"Sine", "sin"};
function_type Cosine = {"Cosine", "cos"};
function_type Tangent = {"Tangent", "tan"};
function_type Cotangent = {"Cotangent", "cot"};
function_type Secant = {"Secant", "sec"};
function_type Cosecant = {"Cosecant", "csc"};
function_type Inverse_Sine = {"Inverse Sine", "arcsin"};
function_type Inverse_Cosine = {"Inverse Cosine", "arccos"};
function_type Inverse_Tangent = {"Inverse Tangent", "arctan"};
function_type Inverse_Cotangent = {"Inverse Cotangent", "arccot"};
function_type Inverse_Secant = {"Inverse Secant", "arcsec"};
function_type Inverse_Cosecant = {"Inverse Cosecant", "arccsc"};

operation_type Addition = {"Addition", "sum", "+", ADD_PREC};
operation_type Subtraction = {"Subtraction", "difference", "-", ADD_PREC};
operation_type Multiplication = {"Multiplication", "product", "*", MUL_PREC};
operation_type Division = {"Division", "quotient", "/", MUL_PREC};
operation_type Power = {"Power", "power", "^", POW_PREC};
operation_type Derivative = {"Derivative", "D", "@", MAX_PREC};

const function_type * function_list[] = {

    &Square_Root,
    &Cube_Root,
    &Natural_Exponent,
    &Decimal_Exponent,
    &Natural_Logarithm,
    &Decimal_Logarithm,
    &Sine,
    &Cosine,
    &Tangent,
    &Cotangent,
    &Secant,
    &Cosecant,
    &Inverse_Sine,
    &Inverse_Cosine,
    &Inverse_Tangent,
    &Inverse_Cotangent,
    &Inverse_Secant,
    &Inverse_Cosecant,
    NULL

};

const operation_type * operation_list[] = {

    &Addition,
    &Subtraction,
    &Multiplication,
    &Division,
    &Power,
    &Derivative,
    NULL

};

// Transformation Format Sequences

int E_Left_Identity_Addition_(node * node_){

    return node_->category == OPERATION && node_->type == &Addition && node_->child_l->category == OBJECT && node_->child_l->type == &Real && !strcmp((char *)node_->child_l->child_l, "0");

}

void * E_Left_Identity_Addition[] = {

    OBJECT_s, &Primer, "r"

};

int E_Left_Identity_Multiplication_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_l->category == OBJECT && node_->child_l->type == &Real && !strcmp((char *)node_->child_l->child_l, "1");

}

void * E_Left_Identity_Multiplication[] = {

    OBJECT_s, &Primer, "r"

};

int E_Right_Identity_Addition_(node * node_){

    return node_->category == OPERATION && node_->type == &Addition && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "0");

}

void * E_Right_Identity_Addition[] = {

    OBJECT_s, &Primer, "l"

};

int E_Right_Identity_Subtraction_(node * node_){

    return node_->category == OPERATION && node_->type == &Subtraction && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "0");

}

void * E_Right_Identity_Subtraction[] = {

    OBJECT_s, &Primer, "l"

};

int E_Right_Identity_Multiplication_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "1");

}

void * E_Right_Identity_Multiplication[] = {

    OBJECT_s, &Primer, "l"

};

int E_Right_Identity_Division_(node * node_){

    return node_->category == OPERATION && node_->type == &Division && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "1");

}

void * E_Right_Identity_Division[] = {

    OBJECT_s, &Primer, "l"

};

int E_Right_Identity_Power_(node * node_){

    return node_->category == OPERATION && node_->type == &Power && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "1");

}

void * E_Right_Identity_Power[] = {

    OBJECT_s, &Primer, "l"

};

int E_Left_Zero_Multiplication_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_l->category == OBJECT && node_->child_l->type == &Real && !strcmp((char *)node_->child_l->child_l, "0");

}

void * E_Left_Zero_Multiplication[] = {

    OBJECT_s, &Real, "0"

};

int E_Left_Zero_Division_(node * node_){

    return node_->category == OPERATION && node_->type == &Division && node_->child_l->category == OBJECT && node_->child_l->type == &Real && !strcmp((char *)node_->child_l->child_l, "0");

}

void * E_Left_Zero_Division[] = {

    OBJECT_s, &Real, "0"

};

int E_Left_Zero_Power_(node * node_){

    return node_->category == OPERATION && node_->type == &Power && node_->child_l->category == OBJECT && node_->child_l->type == &Real && !strcmp((char *)node_->child_l->child_l, "1");

}

void * E_Left_Zero_Power[] = {

    OBJECT_s, &Real, "1"

};

int E_Right_Zero_Multiplication_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_r->category == OBJECT && node_->child_r->type == &Real && !strcmp((char *)node_->child_r->child_l, "0");

}

void * E_Right_Zero_Multiplication[] = {

    OBJECT_s, &Real, "0"

};

int E_Subtraction_Merger_1_(node * node_){

    return node_->category == OPERATION && node_->type == &Addition && node_->child_l->category == OPERATION && node_->child_l->type == &Subtraction;

}

void * E_Subtraction_Merger_1[] = {

    OPERATION_s, &Subtraction,
        OPERATION_s, &Addition,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Primer, "r",
        OBJECT_s, &Primer, "lr"

};

int E_Subtraction_Merger_2_(node * node_){

    return node_->category == OPERATION && node_->type == &Addition && node_->child_r->category == OPERATION && node_->child_r->type == &Subtraction;

}

void * E_Subtraction_Merger_2[] = {

    OPERATION_s, &Subtraction,
        OPERATION_s, &Addition,
            OBJECT_s, &Primer, "l",
            OBJECT_s, &Primer, "rl",
        OBJECT_s, &Primer, "rr"

};

int E_Division_Merger_1_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_l->category == OPERATION && node_->child_l->type == &Division;

}

void * E_Division_Merger_1[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Primer, "r",
        OBJECT_s, &Primer, "lr"

};

int E_Division_Merger_2_(node * node_){

    return node_->category == OPERATION && node_->type == &Multiplication && node_->child_r->category == OPERATION && node_->child_r->type == &Division;

}

void * E_Division_Merger_2[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "l",
            OBJECT_s, &Primer, "rl",
        OBJECT_s, &Primer, "rr"

};

int E_Subtraction_Absorption_1_(node * node_){

    return node_->category == OPERATION && node_->type == &Subtraction && node_->child_l->category == OPERATION && node_->child_l->type == &Subtraction;

}

void * E_Subtraction_Absorption_1[] = {

    OPERATION_s, &Subtraction,
        OBJECT_s, &Primer, "ll",
        OPERATION_s, &Addition,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Primer, "r"

};

int E_Subtraction_Absorption_2_(node * node_){

    return node_->category == OPERATION && node_->type == &Subtraction && node_->child_r->category == OPERATION && node_->child_r->type == &Subtraction;

}

void * E_Subtraction_Absorption_2[] = {

    OPERATION_s, &Subtraction,
        OPERATION_s, &Addition,
            OBJECT_s, &Primer, "l",
            OBJECT_s, &Primer, "rr",
        OBJECT_s, &Primer, "rl"

};

int E_Division_Absorption_1_(node * node_){

    return node_->category == OPERATION && node_->type == &Division && node_->child_l->category == OPERATION && node_->child_l->type == &Division;

}

void * E_Division_Absorption_1[] = {

    OPERATION_s, &Division,
        OBJECT_s, &Primer, "ll",
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Primer, "r"

};

int E_Division_Absorption_2_(node * node_){

    return node_->category == OPERATION && node_->type == &Division && node_->child_r->category == OPERATION && node_->child_r->type == &Division;

}

void * E_Division_Absorption_2[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "l",
            OBJECT_s, &Primer, "rr",
        OBJECT_s, &Primer, "rl"

};

int E_Power_Absorption_(node * node_){

    return node_->category == OPERATION && node_->type == &Power && node_->child_l->category == OPERATION && node_->child_l->type == &Power;

}

void * E_Power_Absorption[] = {

    OPERATION_s, &Power,
        OBJECT_s, &Primer, "ll",
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Primer, "r"

};

int D_Element_Zero_(node * node_){

    return node_->category == OPERATION && node_->type == &Derivative && node_->child_l->category == OBJECT && node_->child_r->category == OBJECT && node_->child_r->type == &Variable && ((node_->child_l->type == &Variable && node_->child_l->child_l != node_->child_r->child_l) || node_->child_l->type == &Real);

}

void * D_Element_Zero[] = {

    OBJECT_s, &Real, "0"

};

int D_Element_One_(node * node_){

    return node_->category == OPERATION && node_->type == &Derivative && node_->child_l->category == OBJECT && node_->child_l->type == &Variable && node_->child_r->category == OBJECT && node_->child_r->type == &Variable && node_->child_l->child_l == node_->child_r->child_l;

}

void * D_Element_One[] = {

    OBJECT_s, &Real, "1"

};

int D_Addition_(node * node_){

    return D_OperationCheck(node_,&Addition);

}

void * D_Addition[] = {

    OPERATION_s, &Addition,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Variable, "r"

};

int D_Subtraction_(node * node_){

    return D_OperationCheck(node_,&Subtraction);

}

void * D_Subtraction[] = {

    OPERATION_s, &Subtraction,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Variable, "r"

};

int D_Multiplication_(node * node_){

    return D_OperationCheck(node_,&Multiplication);

}

void * D_Multiplication[] = {

    OPERATION_s, &Addition,
        OPERATION_s, &Multiplication,
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Variable, "r",
            OBJECT_s, &Primer, "lr",
        OPERATION_s, &Multiplication,
            OBJECT_s, &Primer, "ll",
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "lr",
                OBJECT_s, &Variable, "r"

};

int D_Division_(node * node_){

    return D_OperationCheck(node_,&Division);

}

void * D_Division[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Subtraction,
            OPERATION_s, &Multiplication,
                OPERATION_s, &Derivative,
                    OBJECT_s, &Primer, "ll",
                    OBJECT_s, &Variable, "r"
                OBJECT_s, &Primer, "lr",
            OPERATION_s, &Multiplication,
                OBJECT_s, &Primer, "ll",
                OPERATION_s, &Derivative,
                    OBJECT_s, &Primer, "lr",
                    OBJECT_s, &Variable, "r",
        OPERATION_s, &Power,
            OBJECT_s, &Primer, "lr",
            OBJECT_s, &Real, "2"

};

int D_Power_(node * node_){

    return D_OperationCheck(node_,&Power);

}

void * D_Power[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Power,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Primer, "lr",
        OPERATION_s, &Derivative,
            OPERATION_s, &Multiplication,
                FUNCTION_s, &Natural_Logarithm,
                    OBJECT_s, &Primer, "ll",
                OBJECT_s, &Primer, "lr",
            OBJECT_s, &Variable, "r"

};

int D_Square_Root_(node * node_){

    return D_FunctionCheck(node_,&Square_Root);

}

void * D_Square_Root[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OPERATION_s, &Multiplication,
            OBJECT_s, &Real, "2",
            FUNCTION_s, &Square_Root,
                OBJECT_s, &Primer, "ll"

};

int D_Cube_Root_(node * node_){

    return D_FunctionCheck(node_,&Cube_Root);

}

void * D_Cube_Root[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Multiplication,
            FUNCTION_s, &Cube_Root,
                OBJECT_s, &Primer, "ll",
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Variable, "r",
        OPERATION_s, &Multiplication,
            OBJECT_s, &Real, "3",
            OBJECT_s, &Primer, "ll"

};

int D_Natural_Exponent_(node * node_){

    return D_FunctionCheck(node_,&Natural_Exponent);

}

void * D_Natural_Exponent[] = {

    OPERATION_s, &Multiplication,
        FUNCTION_s, &Natural_Exponent,
            OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Decimal_Exponent_(node * node_){

    return D_FunctionCheck(node_,&Decimal_Exponent);

}

void * D_Decimal_Exponent[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Multiplication,
            FUNCTION_s, &Natural_Logarithm,
                OBJECT_s, &Real, "10",
            FUNCTION_s, &Decimal_Exponent,
                OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Natural_Logarithm_(node * node_){

    return D_FunctionCheck(node_,&Natural_Logarithm);

}

void * D_Natural_Logarithm[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OBJECT_s, &Primer, "ll"

};

int D_Decimal_Logarithm_(node * node_){

    return D_FunctionCheck(node_,&Decimal_Logarithm);

}

void * D_Decimal_Logarithm[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OPERATION_s, &Multiplication,
            FUNCTION_s, &Natural_Logarithm,
                OBJECT_s, &Real, "10",
            OBJECT_s, &Primer, "ll"

};

int D_Sine_(node * node_){

    return D_FunctionCheck(node_,&Sine);

}

void * D_Sine[] = {

    OPERATION_s, &Multiplication,
        FUNCTION_s, &Cosine,
            OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Cosine_(node * node_){

    return D_FunctionCheck(node_,&Cosine);

}

void * D_Cosine[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Real, "-1",
            FUNCTION_s, &Sine,
                OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Tangent_(node * node_){

    return D_FunctionCheck(node_,&Tangent);

}

void * D_Tangent[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Power,
            FUNCTION_s, &Secant,
                OBJECT_s, &Primer, "ll",
            OBJECT_s, &Real, "2",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Cotangent_(node * node_){

    return D_FunctionCheck(node_,&Cotangent);

}

void * D_Cotangent[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Real, "-1",
            OPERATION_s, &Power,
                FUNCTION_s, &Cosecant,
                    OBJECT_s, &Primer, "ll",
                OBJECT_s, &Real, "2",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Secant_(node * node_){

    return D_FunctionCheck(node_,&Secant);

}

void * D_Secant[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Multiplication,
            FUNCTION_s, &Secant,
                OBJECT_s, &Primer, "ll",
            FUNCTION_s, &Tangent,
                OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Cosecant_(node * node_){

    return D_FunctionCheck(node_,&Cosecant);

}

void * D_Cosecant[] = {

    OPERATION_s, &Multiplication,
        OPERATION_s, &Multiplication,
            OBJECT_s, &Real, "-1",
            OPERATION_s, &Multiplication,
                FUNCTION_s, &Cosecant,
                    OBJECT_s, &Primer, "ll",
                FUNCTION_s, &Cotangent,
                    OBJECT_s, &Primer, "ll",
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r"

};

int D_Inverse_Sine_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Sine);

}

void * D_Inverse_Sine[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        FUNCTION_s, &Square_Root,
            OPERATION_s, &Subtraction,
                OBJECT_s, &Real, "1",
                OPERATION_s, &Power,
                    OBJECT_s, &Primer, "ll",
                    OBJECT_s, &Real, "2"

};

int D_Inverse_Cosine_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Cosine);

}

void * D_Inverse_Cosine[] = {

    OPERATION_s, &Multiplication,
        OBJECT_s, &Real, "-1",
        OPERATION_s, &Division,
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Variable, "r",
            FUNCTION_s, &Square_Root,
                OPERATION_s, &Subtraction,
                    OBJECT_s, &Real, "1",
                    OPERATION_s, &Power,
                        OBJECT_s, &Primer, "ll",
                        OBJECT_s, &Real, "2"

};

int D_Inverse_Tangent_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Tangent);

}

void * D_Inverse_Tangent[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        OPERATION_s, &Addition,
            OBJECT_s, &Real, "1",
            OPERATION_s, &Power,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Real, "2"

};

int D_Inverse_Cotangent_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Cotangent);

}

void * D_Inverse_Cotangent[] = {

    OPERATION_s, &Multiplication,
        OBJECT_s, &Real, "-1",
        OPERATION_s, &Division,
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Variable, "r",
            OPERATION_s, &Addition,
                OBJECT_s, &Real, "1",
                OPERATION_s, &Power,
                    OBJECT_s, &Primer, "ll",
                    OBJECT_s, &Real, "2"

};

int D_Inverse_Secant_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Secant);

}

void * D_Inverse_Secant[] = {

    OPERATION_s, &Division,
        OPERATION_s, &Derivative,
            OBJECT_s, &Primer, "ll",
            OBJECT_s, &Variable, "r",
        FUNCTION_s, &Square_Root,
            OPERATION_s, &Subtraction,
                OPERATION_s, &Power,
                    OBJECT_s, &Primer, "ll",
                    OBJECT_s, &Real, "4",
                OPERATION_s, &Power,
                    OBJECT_s, &Primer, "ll",
                    OBJECT_s, &Real, "2"

};

int D_Inverse_Cosecant_(node * node_){

    return D_FunctionCheck(node_,&Inverse_Cosecant);

}

void * D_Inverse_Cosecant[] = {

    OPERATION_s, &Multiplication,
        OBJECT_s, &Real, "-1",
        OPERATION_s, &Division,
            OPERATION_s, &Derivative,
                OBJECT_s, &Primer, "ll",
                OBJECT_s, &Variable, "r",
            FUNCTION_s, &Square_Root,
                OPERATION_s, &Subtraction,
                    OPERATION_s, &Power,
                        OBJECT_s, &Primer, "ll",
                        OBJECT_s, &Real, "4",
                    OPERATION_s, &Power,
                        OBJECT_s, &Primer, "ll",
                        OBJECT_s, &Real, "2"

};

// .Derivative

void * * * * E_utmost_sequence;
void * * * * * D_single_sequence;

trans Derivative_single(node * node_, void * * sequence_){

    // [REMARK] The argument sequence will always be NULL.

    if(node_->category == OPERATION && (operation_type *)node_->type == &Derivative){
        if(node_->child_l->category == OPERATION && (operation_type *)node_->child_l->type == &Derivative){
            ///
        } else{
            __node___record(node_);
            trans_utmost(__node__->child_l, (void * *)E_utmost_sequence);
            trans_single(__node__, (void * *)D_single_sequence);
        }
    }
    return SUCCEED;

}

void Derivative_initializer(void){

    D_single_sequence = malloc(26 * sizeof(void *));
    D_sequence_Set_0(0, Element_Zero);
    D_sequence_Set_0(1, Element_One);
    D_sequence_Set_2(2, Addition, "l", "r");
    D_sequence_Set_2(3, Subtraction, "l", "r");
    D_sequence_Set_2(4, Multiplication, "ll", "rr");
    D_sequence_Set_2(5, Division, "lll", "lrr");
    D_sequence_Set_1(6, Power, "r");
    D_sequence_Set_1(7, Square_Root, "l");
    D_sequence_Set_1(8, Cube_Root, "lr");
    D_sequence_Set_1(9, Natural_Exponent, "r");
    D_sequence_Set_1(10, Decimal_Exponent, "r");
    D_sequence_Set_1(11, Natural_Logarithm, "l");
    D_sequence_Set_1(12, Decimal_Logarithm, "l");
    D_sequence_Set_1(13, Sine, "r");
    D_sequence_Set_1(14, Cosine, "r");
    D_sequence_Set_1(15, Tangent, "r");
    D_sequence_Set_1(16, Cotangent, "r");
    D_sequence_Set_1(17, Secant, "r");
    D_sequence_Set_1(18, Cosecant, "r");
    D_sequence_Set_1(19, Inverse_Sine, "l");
    D_sequence_Set_1(20, Inverse_Cosine, "rl");
    D_sequence_Set_1(21, Inverse_Tangent, "l");
    D_sequence_Set_1(22, Inverse_Cotangent, "rl");
    D_sequence_Set_1(23, Inverse_Secant, "l");
    D_sequence_Set_1(24, Inverse_Cosecant, "rl");
    D_single_sequence[25] = NULL;

    E_utmost_sequence = malloc(21 * sizeof(void *));
    E_sequence_Set(0, Left_Identity_Addition);
    E_sequence_Set(1, Left_Identity_Multiplication);
    E_sequence_Set(2, Right_Identity_Addition);
    E_sequence_Set(3, Right_Identity_Subtraction);
    E_sequence_Set(4, Right_Identity_Multiplication);
    E_sequence_Set(5, Right_Identity_Division);
    E_sequence_Set(6, Right_Identity_Power);
    E_sequence_Set(7, Left_Zero_Multiplication);
    E_sequence_Set(8, Left_Zero_Division);
    E_sequence_Set(9, Left_Zero_Power);
    E_sequence_Set(10, Right_Zero_Multiplication);
    E_sequence_Set(11, Subtraction_Merger_1);
    E_sequence_Set(12, Subtraction_Merger_2);
    E_sequence_Set(13, Division_Merger_1);
    E_sequence_Set(14, Division_Merger_2);
    E_sequence_Set(15, Subtraction_Absorption_1);
    E_sequence_Set(16, Subtraction_Absorption_2);
    E_sequence_Set(17, Division_Absorption_1);
    E_sequence_Set(18, Division_Absorption_2);
    E_sequence_Set(19, Power_Absorption);
    E_utmost_sequence[20] = NULL;

}

void Derivative_calculator(node * node_){

    if(node_){
        switch(node_->category){
            case OBJECT:
                break;
            case FUNCTION:
                Derivative_calculator(node_->child_l);
                break;
            case OPERATION:
                if((operation_type *)node_->type == &Derivative){
                    Derivative_single(node_, NULL);
                }
                Derivative_calculator(node_->child_l);
                Derivative_calculator(node_->child_r);
                break;
        }
    }

}
