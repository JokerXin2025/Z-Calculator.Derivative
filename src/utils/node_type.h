/// 2025 Z·Calculator.Derivative

# pragma once

# include <string.h>
# include "_node_type.h"

// Node Type Utilities

const function_type * search_function_type(const char *, const function_type * const *);
const operation_type * search_operation_type(const char *, const operation_type * const *);
