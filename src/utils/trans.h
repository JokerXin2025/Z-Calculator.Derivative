/// 2025 Z·Calculator.Derivative

# pragma once

# include <stdlib.h>
# include <string.h>
# include "_node_type.h"
# include "_tree.h"
# include "_trans.h"
# include "node.h"

// Tree Transformation Utilities

const void * const * format_subtree(node *, int, const void * const *, const node *);
void duplicate_subtree(node *, int, const node *);
void remove_subtree(node *);

// Tree Transformation Applications

trans trans_format(node *, const void * const *);
trans trans_format_p(node *, const void * const *);
trans trans_invoke(node *, const void * const *);
trans trans_single(node *, const void * const *);
trans trans_utmost(node *, const void * const *);
