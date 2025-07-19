/// 2025 Z·Calculator.Derivative

# include "Printer.h"

// Constant Macros

# define if_functioned(Node) (Node->parent->category == FUNCTION && !type_check((function_type *)Node->parent->type, "Root"))

// Printer Utility

void print(const char * const string_){

    // print a normal string

    fputs(string_, stdout);

}

// Printer Application

void Print_s(const node * const subroot_){

    // print a subtree

    if(subroot_){
        switch(subroot_->category){
            case OBJECT:
                if(type_check((object_type *)subroot_->type, "Variable")){
                    PRINT_BOLD;
                    print(((variable *)subroot_->child_l)->symbol);
                    PRINT_RESET;
                } else{
                    print((char *)subroot_->child_l);
                }
                break;
            case FUNCTION:
                if(type_check((function_type *)subroot_->type, "Root")){
                    print("\n-> ");
                    Print_s(subroot_->child_l);
                    print("\n");
                } else{
                    if(if_functioned(subroot_)){
                        print("(");
                    }
                    print(((function_type *)subroot_->type)->prefix);
                    Print_s(subroot_->child_l);
                    if(if_functioned(subroot_)){
                        print(")");
                    }
                }
                break;
            case OPERATION:
                if(if_functioned(subroot_) || (subroot_->parent->category == OPERATION && ((operation_type *)subroot_->type)->precedence <= ((operation_type *)subroot_->parent->type)->precedence)){
                    print("(");
                }
                Print_s(subroot_->child_l);
                print(((operation_type *)subroot_->type)->infix);
                Print_s(subroot_->child_r);
                if(if_functioned(subroot_) || (subroot_->parent->category == OPERATION && ((operation_type *)subroot_->type)->precedence <= ((operation_type *)subroot_->parent->type)->precedence)){
                    print(")");
                }
                break;
        }
    }  else{
        print("[EMPTY]");
    }

}
