/// 2025 Z·Calculator.Derivative

# include "trans.h"

// Tree Transformation Utilities

const void * const * format_subtree(node * const parent_, const int index_, const void * const * sequence_, const node * const base_){

    // new a subtree and format it by generation sequence

    // [PARAMETER] [new subtree's root node's parent node], [new subtree's root node's index], [new subtree's generation sequence], [base node]

    // [SEQUENCE] generation sequence
    // [REMARK] "[...]" requires conversion from (char *) to (int) when used
    // "[node's category]" -> [node's type] ->
    // OBJECT.Primer:   [template subroot's positioning sequence]
    // OBJECT.Variable: ([root node's positioning sequence] -> "[index]")/(NULL -> [root node] -> "[index]")/[template node's positioning sequence]/(NULL -> [template node])
    // OBJECT...:       [template value]
    // FUNCTION:        ...<left child node>...
    // OPERATION:       ...<left child node>... -> ...<right child node>...

    node * _node_;
    if(!index_){
        parent_->child_l = malloc(sizeof(node));
        _node_ = parent_->child_l;
    } else{
        parent_->child_r = malloc(sizeof(node));
        _node_ = parent_->child_r;
    }
    _node_->category = atoi((char *)*sequence_++);
    _node_->type = *sequence_++;
    _node_->parent = parent_;
    switch(_node_->category){
        case OBJECT:
            if(type_check((object_type *)_node_->type, "Primer")){
                /* free and then malloc for this node again */
                free(_node_);
                duplicate_subtree(parent_, index_, node_position_c(base_, (char *)*sequence_++));
            } else if(type_check((object_type *)_node_->type, "Variable")){
                const char * const sequence = (char *)*sequence_++;
                const node * const src_node = sequence ? node_position_c(base_, sequence) : (node *)*sequence_++;
                if(src_node->category == OBJECT){
                    _node_->child_l = src_node->child_l;
                } else{
                    _node_->child_l = (node *)((tree *)src_node->parent)->variable_list[atoi((char *)*sequence_++)];
                }
                _node_->child_r = NULL;
            } else{
                const char * const value = (char *)*sequence_++;

                _node_->child_l = malloc((strlen(value)+1) * sizeof(char));
                strcpy((char *)_node_->child_l, value);
                _node_->child_r = NULL;
            }
            break;
        case FUNCTION:
            sequence_ = format_subtree(_node_, 0, sequence_, base_);
            _node_->child_r = NULL;
            break;
        case OPERATION:
            sequence_ = format_subtree(_node_, 0, sequence_, base_);
            sequence_ = format_subtree(_node_, 1, sequence_, base_);
            break;
    }
    return sequence_;

}

void duplicate_subtree(node * const parent_, const int index_, const node * const template_){

    // new a subtree and format it by the template subtree

    // [PARAMETER] [new subtree's root node's parent node], [new subtree's root node's index], [template subtree's root node]

    node * _node_;
    if(!index_){
        parent_->child_l = malloc(sizeof(node));
        _node_ = parent_->child_l;
    } else{
        parent_->child_r = malloc(sizeof(node));
        _node_ = parent_->child_r;
    }
    _node_->category = template_->category;
    _node_->type = template_->type;
    _node_->parent = parent_;
    switch(template_->category){
        case OBJECT:
            if(type_check((object_type *)template_->type, "Variable")){
                _node_->child_l = template_->child_l;
            } else{
                _node_->child_l = malloc((strlen((char *)template_->child_l)+1) * sizeof(char));
                strcpy((char *)_node_->child_l, (char *)template_->child_l);
            }
            _node_->child_r = NULL;
            break;
        case FUNCTION:
            duplicate_subtree(_node_, 0, template_->child_l);
            _node_->child_r = NULL;
            break;
        case OPERATION:
            duplicate_subtree(_node_, 0, template_->child_l);
            duplicate_subtree(_node_, 1, template_->child_r);
            break;
    }

}

void remove_subtree(node * const subroot_){

    // remove the subtree

    // [PARAMETER] [subtree's root node]

    if(subroot_){
        switch(subroot_->category){
            case OBJECT:
                if(!type_check((object_type *)subroot_->type, "Variable")){
                    free(subroot_->child_l);
                }
                break;
            case FUNCTION:
                remove_subtree(subroot_->child_l);
                break;
            case OPERATION:
                remove_subtree(subroot_->child_l);
                remove_subtree(subroot_->child_r);
                break;
        }
        if(subroot_->parent && subroot_ == subroot_->parent->child_l){
            subroot_->parent->child_l = NULL;
        } else if (subroot_->parent && subroot_ == subroot_->parent->child_r){
            subroot_->parent->child_r = NULL;
        }
        free(subroot_);
    }

}

// Tree Transformation Applications

trans trans_format(node * const node_, const void * const * const sequence_){

    // execute a transformation (unconditionally)

    // [PARAMETER] [argument node], [new subtree's generation sequence]

    __node___record(node_);
    node * board = malloc(sizeof(node));
    format_subtree(board, 0, sequence_, node_);
    board->child_l->parent = __parent__;
    __node___assign(board->child_l);
    remove_subtree(node_);
    free(board);
    return SUCCEED;

}

trans trans_format_p(node * const node_, const void * const * const sequence_){

    // execute a transformation (under permission)

    // [PARAMETER] [argument node], [argument sequence]

    // [SEQUENCE] argument sequence
    // [transformation's permission], [new subtree's generation sequence]

    if(((trans_p)sequence_[0])·(node_)){
        __node___record(node_);
        node * board = malloc(sizeof(node));
        format_subtree(board, 0, (const void * const *)sequence_[1], node_);
        board->child_l->parent = __parent__;
        __node___assign(board->child_l);
        remove_subtree(node_);
        free(board);
        return SUCCEED;
    } else{
        return PASS;
    }

}

trans trans_invoke(node * const node_, const void * const * sequence_){

    // run the first transformation and invoke the others if successful
    // [REMARK] Return PASS when the first transformations return PASS, FAIL when at least one transformation return FAIL, else SUCCEED.

    // [PARAMETER] [argument node], [argument sequence]

    // [SEQUENCE] argument sequence
    // [transformation 0], [argument sequence 0], ...({[transformation n], [argument node's positioning sequence n], [argument sequence n]})..., NULL

    __node___record(node_);
    __trans___start(((trans_f)sequence_[0])·(node_, (const void * *)sequence_[1]));
    if(__trans__ == SUCCEED){
        __trans__ = PASS;
        sequence_ += 2;
        while(*sequence_){
            __trans__ *= !(((trans_f *)*sequence_)[0])·(node_position(__node__, ((char * *)*sequence_)[1]), ((const void * * *)*sequence_)[2]);
            sequence_++;
        }
        if(!__trans__){
            return FAIL;
        } else{
            return SUCCEED;
        }
    } else{
        return __trans__;
    }

}

trans trans_single(node * const node_, const void * const * sequence_){

    // try every transformation in order until one succeeds
    // [REMARK] Return the product of all tried transformations' return values.

    // [PARAMETER] [argument node], [argument sequence]

    // [SEQUENCE] argument sequence
    // {[transformation 0], [argument sequence 0]}, ...({[transformation n], [argument sequence n]})..., NULL

    __trans___start(PASS);
    do{
        __trans__ *= (((trans_f *)*sequence_)[0])·(node_, ((const void * * *)*sequence_)[1]);
    } while( /* short-circuit evaluation */ __trans__ != SUCCEED && *(++sequence_) );
    return __trans___value;

}

trans trans_utmost(node * const subroot_, const void * const * sequence_){

    // try every transformation for every node in the subtree and keep repeating until all pass

    // [PARAMETER] [argument node], [argument sequence]

    // [SEQUENCE] argument sequence
    // {[transformation 0], [argument sequence 0]}, ...({[transformation n], [argument sequence n]})..., NULL

    __node___record(subroot_);
    __trans___start(PASS);
    do{
        __trans__ = PASS;
        switch(__node__->category){
            case OBJECT:
                break;
            case FUNCTION:
                __trans__ *= trans_utmost(__node__->child_l, sequence_);
                break;
            case OPERATION:
                __trans__ *= trans_utmost(__node__->child_l, sequence_);
                __trans__ *= trans_utmost(__node__->child_r, sequence_);
                break;
        }
        __trans__ *= (((trans_f *)*sequence_)[0])·(__node__, ((const void * * *)*sequence_)[1]);
    } while( /* short-circuit evaluation */ __trans__ == SUCCEED || *(++sequence_) );
    return __trans___value;

}
