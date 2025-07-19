/// 2025 Z·Calculator.Derivative

# include "node_type.h"

// Node Type Utilities

const function_type * search_function_type(const char * const prefix_, const function_type * const * const list_){

    // search for the function type by its prefix
    // [REMARK] Return NULL when the function type does not exist in the function type list.

    // [PARAMETER] [prefix], [function type list]

    for(int i = 0; list_[i]; i++){
        if(!strcmp(list_[i]->prefix, prefix_)){
            return list_[i];
        }
    }
    return NULL;

}

const operation_type * search_operation_type(const char * const prefix_, const operation_type * const * const list_){

    // search for the operation type by its prefix
    // [REMARK] Return NULL when the operation type does not exist in the operation type list.

    // [PARAMETER] [prefix], [operation type list]

    for(int i = 0; list_[i]; i++){
        if(!strcmp(list_[i]->prefix, prefix_)){
            return list_[i];
        }
    }
    return NULL;

}
