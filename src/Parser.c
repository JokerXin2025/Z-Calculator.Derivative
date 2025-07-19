/// 2025 Z·Calculator.Derivative

# include "Parser.h"

// Function-like Macros

# define string_check(String,StaticString) (!strncmp(String, StaticString, strlen(StaticString)))
# define string_cover(String,StaticString) strncpy(String, StaticString, strlen(StaticString))

// Parser Utilities

size_t len_sequence(const void * const * const sequence_, const void * const end_){

    // measure the length of the sequence
    // [PARAMETER] [sequence], [sequence's last item]

    size_t _length = 0;
    while(sequence_[_length] != end_){
        _length++;
    }
    return _length;

}

void string_shift(char * const string_, const size_t start_, const size_t length_){

    // right-shift the substring starting from start point by a given length
    // [PARAMETER] [string], [start point's index], [shift length]

    for(size_t i = strlen(string_) + length_ - 1; i >= start_ + length_; i--){
        string_[i] = string_[i-length_];
    }
    return;

}

long left_bracket_index(const char * const input_, size_t index_){

    // find the nearest left bracket(or comma) in the input string
    // [PARAMETER] [input string], [datum index]
    // [REMARK] If there's no nearest left bracket, return -1

    long layer = 0, _index = index_;
    while(layer >= 0 && --_index >= 0){
        if(!layer && input_[_index] == ','){
            return _index;
        } else if(input_[_index] == '('){
            layer--;
        } else if(input_[_index] == ')'){
            layer++;
        }
    }
    return _index;

}

size_t right_bracket_index(const char * const input_, size_t index_){

    // find the nearest right bracket(or comma)'s index
    // [REMARK] If there's no nearest right bracket, return strlen(input_)

    int layer = 0;
    size_t length = strlen(input_);
    while(layer >= 0 && ++index_ < length){
        if(layer == 0 && input_[index_] == ','){
            return index_;
        } else if(input_[index_] == '('){
            layer++;
        } else if(input_[index_] == ')'){
            layer--;
        }
    }
    return index_;

}

int if_number(const char * string_){

    // check whether the string is a number

    do{
        if((*string_ < '0' || *string_ > '9') && *string_ != '.' && *string_ != '-'){
            return 0;
        }
    } while(*(++string_));
    return 1;

}

// Parser Applications

void Parser_operator(char * const input_){

    // convert operators to binary functions

    for(oper_precedence prec = MIN_PREC; prec < MAX_PREC; prec++){
        for(int n = 0; n < 6; n++){
            if(operation_list[n]->precedence == prec){
                for(size_t i = strlen(input_) - 1; i > 0; i--){
                    if(string_check(input_+i, operation_list[n]->infix)){
                        long index;
                        index = left_bracket_index(input_, i);
                        string_shift(input_, index+1, strlen(operation_list[n]->prefix)+1);
                        string_cover(input_+index+1, operation_list[n]->prefix);
                        string_cover(input_+index+strlen(operation_list[n]->prefix)+1, "(");
                        index = right_bracket_index(input_, i+strlen(operation_list[n]->prefix)+1);
                        string_shift(input_, index, 1);
                        string_cover(input_+index, ")");
                        input_[i+=(strlen(operation_list[n]->prefix)+1)] = ',';
                    }
                }
            }
        }
    }
    return;

}

const void * * Parser(const char * const input_, tree * tree_){

    // convert the input string into a generation sequence
    // [PARAMETER] [input string], [the host tree]
    // [REMARK] The last non-'\0' character is definitely ')' unless there's only an object.

    if(input_[strlen(input_)-1] == ')'){
        /* search for start index */
        size_t start_index = 0;
        while(input_[start_index++] != '('){}
        if(string_check(input_, "(")){
            /* prepare for subcontent */
            char * const subcontent = malloc((strlen(input_)-1) * sizeof(char));
            strncpy(subcontent, input_+1, strlen(input_)-2);
            subcontent[strlen(input_)-start_index-1] = '\0';
            /* prepare for sequence */
            const void * * const _sequence = Parser(subcontent, tree_);
            free(subcontent);
            return _sequence;
        } else{
            /* prepare for prefix */
            char * prefix = malloc(start_index * sizeof(char));
            strncpy(prefix, input_, start_index-1);
            prefix[start_index-1] = '\0';
            if(search_function_type(prefix, function_list)){
                /* prepare for subcontent */
                char * const subcontent = malloc((strlen(input_)-start_index) * sizeof(char));
                strncpy(subcontent, input_+start_index, strlen(input_)-start_index-1);
                subcontent[strlen(input_)-start_index-1] = '\0';
                /* prepare for subsequence */
                const void * * const subsequence = Parser(subcontent, tree_);
                const size_t length = len_sequence(subsequence, &Parser_Primer);
                /* format sequence */
                const void * * const _sequence = malloc((length+3) * sizeof(void *));
                _sequence[0] = FUNCTION_s;
                _sequence[1] = search_function_type(prefix, function_list);
                for(size_t n = 2; n < length + 2; n++){
                    _sequence[n] = subsequence[n-2];
                }
                _sequence[length + 2] = &Parser_Primer;
                /* free */
                free(prefix);
                free(subcontent);
                free(subsequence);
                return _sequence;
            } else{
                /* search for middle index */
                size_t mid_index = left_bracket_index(input_, strlen(input_)-1);
                /* prepare for subcontent */
                char * const subcontent_1 = malloc((mid_index-start_index+1) * sizeof(char));
                char * const subcontent_2 = malloc((strlen(input_)-mid_index-1) * sizeof(char));
                strncpy(subcontent_1, input_+start_index, mid_index-start_index);
                subcontent_1[mid_index-start_index] = '\0';
                strncpy(subcontent_2, input_+mid_index+1, strlen(input_)-mid_index-2);
                subcontent_2[strlen(input_)-mid_index-2] = '\0';
                /* prepare for subsequence */
                const void * * const subsequence_1 = Parser(subcontent_1, tree_);
                const size_t length_1 = len_sequence(subsequence_1, &Parser_Primer);
                const void * * const subsequence_2 = Parser(subcontent_2, tree_);
                const size_t length_2 = len_sequence(subsequence_2, &Parser_Primer);
                /* format sequence */
                const void * * const _sequence = malloc((length_1+length_2+3) * sizeof(void *));
                _sequence[0] = OPERATION_s;
                _sequence[1] = search_operation_type(prefix, operation_list);
                for(size_t n = 2; n < length_1 + 2; n++){
                    _sequence[n] = subsequence_1[n-2];
                }
                for(size_t n = length_1 + 2; n < length_1 + length_2 + 2; n++){
                    _sequence[n] = subsequence_2[n-length_1-2];
                }
                _sequence[length_1+length_2+2] = &Parser_Primer;
                /* free */
                free(prefix);
                free(subcontent_1);
                free(subcontent_2);
                free(subsequence_1);
                free(subsequence_2);
                return _sequence;
            }
        }
    } else if(if_number(input_)){
        /* prepare for object's value */
        char * const object_value = malloc((strlen(input_)+1) * sizeof(char));
        strcpy(object_value, input_);
        /* format sequence */
        const void * * const _sequence = malloc(4 * sizeof(void *));
        _sequence[0] = OBJECT_s;
        _sequence[1] = &Real;
        _sequence[2] = object_value;
        _sequence[3] = &Parser_Primer;
        return _sequence;
    } else{
        /* prepare for virtual Variable */
        node * const virtual_Variable = calloc(1, sizeof(node));
        virtual_Variable->category = OBJECT;
        virtual_Variable->type = &Variable;
        tree_->variable_list = registerer(virtual_Variable, input_, tree_->variable_list);
        /* format sequence */
        const void * * const _sequence = malloc(5 * sizeof(void *));
        _sequence[0] = OBJECT_s;
        _sequence[1] = &Variable;
        _sequence[2] = NULL;
        _sequence[3] = virtual_Variable;
        _sequence[4] = &Parser_Primer;
        return _sequence;
    }

}
