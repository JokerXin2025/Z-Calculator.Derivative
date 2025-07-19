/// 2025 Z·Calculator.Derivative

# pragma once

# include <stdio.h>
# include <string.h>
# include "_variable.h"
# include "_node_type.h"
# include "_node.h"

// Printer Macros

# define PRINT_RESET    printf("\033[0m")
# define PRINT_BOLD     printf("\033[1m")
# define PRINT_CLS      printf("\033[2J\033[H")

// Printer Utility

void print(const char *);

// Printer Application

void Print_s(const node *);
