/// 2025 Z·Calculator.Derivative

# include "variable.h"

// Variable List Utilities

variable * * variable_list_initializer(variable * * list_){

    // initialize the variable list

    // [PARAMETER] [variable list]

    if(list_){
        size_t n = 0;
        while(list_[n]){
            free(list_[n]->symbol);
            free(list_[n]);
            n++;
        }
        free(list_);
    }
    list_ = malloc(sizeof(variable *));
    *list_ = NULL;
    return list_;

}

variable * * registerer(node * const node_, const char * const symbol_, variable * * list_){

    // look up the symbol in the variable list and if this symbol is
    // 1. already registered in the variable list : renew object's value
    // 2. not registered yet in the variable list : add it to the variable list and renew object's value

    // [PARAMETER] [object node], [symbol], [variable list]

    size_t n = 0;
    while(list_[n]){
        if(!strcmp(list_[n]->symbol, symbol_)){
            /* case 1 */
            node_->child_l = (node *)list_[n];
            return list_;
        }
        n++;
    }
    /* case 2 */
    list_ = realloc(list_, (n+2) * sizeof(variable *));
    list_[n] = malloc(sizeof(variable));
    list_[n]->symbol = malloc((strlen(symbol_)+1) * sizeof(char));
    strcpy(list_[n]->symbol, symbol_);
    list_[n+1] = NULL;
    node_->child_l = (node *)list_[n];
    return list_;

}
