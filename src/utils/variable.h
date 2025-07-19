/// 2025 Z·Calculator.Derivative

# pragma once

# include <stdlib.h>
# include <string.h>
# include "_variable.h"
# include "_node.h"

// Variable List Utilities

variable * * variable_list_initializer(variable * *);
variable * * registerer(node *, const char *, variable * *);
