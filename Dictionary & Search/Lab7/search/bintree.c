#include "bintree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lib/Lab6/stack/stack.h"
#include "lib/Lab6/queue/queue.h"
BinaryTree* bintree_initialize(int itemSize, char* type, int (*compare)(void*, void*), void (*print)(void*)) {

    BinaryTree* a = malloc(sizeof(BinaryTree));
    
    a->top = NULL;
    a->itemSize = itemSize;
    a->type = malloc(strlen(type)+1);
    strcpy(a->type, type);
    a->compare = compare;
    a->print = print;
    return a;
}

BinaryTreeNode* bintree_create_node(int itemSize, void* element) {\

    BinaryTreeNode* node = malloc(sizeof(BinaryTreeNode));
    node->data = malloc(itemSize);
  
    memcpy(node->data, element, itemSize);
    node->left = NULL;
    node->right = NULL;
    return node;
}

bool bintree_insert(BinaryTree* a, void* elem) {
    
    BinaryTreeNode* newnode = bintree_create_node(a->itemSize, elem);
    
    if (a->top == NULL) {

        a->top = newnode;
        return true;

    } else {
        
        return _bintree_insert_recursive(a->top, newnode, elem);
    }
}

bool bintree_search(BinaryTree* a, void* elem) {

     return _bintree_search_recursive(a, a->top, elem);
}

void bintree_print_in_order(BinaryTree* a) {

    if (a != NULL) {
        _bintree_in_order_recursive(a, a->top);
    }
   

}
void bintree_print_pre_order(BinaryTree* a) {

   if (a != NULL) {
        _bintree_pre_order_recursive(a, a->top);
    }

}

void bintree_print_post_order(BinaryTree* a) {

    if (a != NULL) {
        _bintree_post_order_recursive(a, a->top);
    }
}

void bintree_print_reverse_order(BinaryTree* a) {

    if (a != NULL) {
        _bintree_reverse_order_recursive(a, a->top);
    }
}


bool _bintree_insert_recursive(BinaryTreeNode* a, BinaryTreeNode* newnode,void* elem) {
    
    int comp = compare(a->data, newnode->data);
    
    if (comp < 0) {
   
        if (a->left == NULL) {
            a->left = newnode;
            return true;
        } else { 
            return _bintree_insert_recursive(a->left, newnode, elem);
        }

    } else if (comp >= 0) {
        if (a->right == NULL) {
            a->right = newnode;
            return true;
        } else {
            return _bintree_insert_recursive(a->right, newnode, elem);
        }
    } else {

        return false;
    }
}

bool _bintree_search_recursive(BinaryTree* a, BinaryTreeNode* node, void* elem) {
    if (node == NULL) {
        return false;
    }
    
    int cmp = a->compare(node->data,elem);
    
    if (cmp < 0) {
        return _bintree_search_recursive(a, node->left, elem);
    } else if (cmp > 0) {
        return _bintree_search_recursive(a, node->right, elem);
    } else {
        return true;
    }
}

void _bintree_in_order_recursive(BinaryTree* a, BinaryTreeNode* node) {
    
    if (a != NULL && node !=NULL) {
        _bintree_in_order_recursive(a, node->left);
        a->print(node->data);
        _bintree_in_order_recursive(a, node->right);
    }
}

void _bintree_pre_order_recursive(BinaryTree* a, BinaryTreeNode* node) {

    if (a!=NULL && node != NULL) {
        a->print(node->data);
        _bintree_pre_order_recursive(a, node->left);
        _bintree_pre_order_recursive(a, node->right);
    }
}

void _bintree_post_order_recursive(BinaryTree* a, BinaryTreeNode* node) {

    if (a!=NULL && node != NULL) {
    
    _bintree_post_order_recursive(a, node->left);
    _bintree_post_order_recursive(a, node->right);
    a->print(node->data);
    }
}

void _bintree_reverse_order_recursive(BinaryTree* a, BinaryTreeNode* node) {

    if (a!=NULL && node != NULL) {
        _bintree_reverse_order_recursive(a, node->right);
        a->print(node->data);
        _bintree_reverse_order_recursive(a, node->left);
    }
}
void bintree_print_breadth_first(BinaryTree* a){

	BinaryTreeNode* b=NULL;
	Queue* q=queue_initialize(sizeof(BinaryTreeNode),"BinaryTreeNode");
	queue_enqueue(q,a->top);

	while(queue_size(q)!=0){
		b=queue_dequeue(q);
  	        a->print(b->data);
		if (b->left != NULL) {
            	      queue_enqueue(q,b->left);
      		}
     		if (b->right != NULL) {
            	       queue_enqueue(q,b->right);
     		 }
	}
}

void bintree_print_depth_first(BinaryTree* a){
	BinaryTreeNode* b=NULL;
	Stack* s=stack_initialize(sizeof(BinaryTreeNode),"BinaryTreeNode");
	stack_push(s,a->top);
	while(stack_size(s)>0){
		b=stack_pop(s);
  	        a->print(b->data);
		if (b->right != NULL) {
                	stack_push(s,b->right);
      	}
		if (b->left != NULL) {
                	stack_push(s,b->left);
         
     		 }
	}
}

bool bintree_insert_replace(BinaryTree* a, void* elem) {
    
    BinaryTreeNode* newnode = bintree_create_node(a->itemSize, elem);
    
    if (a->top == NULL) {
        a->top = newnode;
        return true;
    } else {
        return _bintree_insert_replace_recursive(a->top, newnode, elem);
    }
}

bool _bintree_insert_replace_recursive(BinaryTreeNode* a, BinaryTreeNode* newnode, void* elem) {
    
    int comp = compare(a->data, newnode->data);
    
    if (comp < 0) {
        if (a->left == NULL) {
            a->left = newnode;
            return true;
        } else { 
            return _bintree_insert_replace_recursive(a->left, newnode, elem);
        }
    } else if (comp > 0) {
        if (a->right == NULL) {
            a->right = newnode;
            return true;
        } else {
            return _bintree_insert_replace_recursive(a->right, newnode, elem);
        }
    } else {
        memcpy(a->data, elem, sizeof(a->data));
        return true;
    }
}


int compare( void * a , void * b ) {

     return *(( int *) b ) - *(( int *) a ) ; 
}

void print( void * a ){

     printf ( " % d " , *(( int *) a ) ) ;

}

