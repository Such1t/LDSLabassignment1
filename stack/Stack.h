#ifndef STACK_H_INCLUDE 
#define STACK_H_INCLUDE
#include <stdint.h>      // Added: This defines uint32_t and int32_t
#define MAX_DEPTH 32
struct _stack_ {
  uint32_t size;
  int32_t top;
  float data[MAX_DEPTH];

};

typedef struct _stack_ *Stack;

#define STACK_OK 1
#define STACK_FULL 2
#define STACK_EMPTY 3

struct _stack_result_{
  float data;
  uint32_t status;
};

typedef struct _stack_result_ StackResult;

Stack stack_new(uint32_t size);
void stack_delete(Stack stk);
uint32_t stack_full(Stack stk);
uint32_t stack_empty(Stack stk);
Stack stack_push(Stack stk,float ele,StackResult *res);
Stack stack_pop(Stack stk,StackResult *res);
Stack stack_peek(Stack stk,StackResult *res);

#endif 



