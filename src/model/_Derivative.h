/// 2025 Z·Calculator.Derivative

# pragma once

# include "trans.h"

// Type External Declaration

extern object_type Variable;
extern object_type Real;
extern object_type Parser_Primer;
extern function_type Root;

extern const function_type * function_list[];
extern const operation_type * operation_list[];

// .Derivative

extern void * * * * E_utmost_sequence;
extern void * * * * * D_single_sequence;

void Derivative_initializer(void);
void Derivative_calculator(node *);
