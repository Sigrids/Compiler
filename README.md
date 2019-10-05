# Compiler
translating a low level language with local scope into assembly language. 

Low level language
BNF
<program>  ->      <vars> <block>
  
<block>    ->      void <vars> <stats> return
  
<vars>     ->      empty | var Identifier : Integer <vars>
  
<expr>     ->      <A> + <expr> | <A> - <expr> | <A>
  
<A>        ->      <N> / <A> | <N>
  
<N>        ->      <M> * <N> | <M>
  
<M>        ->      % <M> |  <R>
  
<R>        ->      ( <expr> ) | Identifier | Integer
  
<stats>    ->      <stat> ; <mStat>
  
<mStat>    ->      empty |  <stat>  ;  <mStat>
  
<stat>     ->      <in> | <out> | <block> | <if> | <loop> | <assign>
  
<in>       ->      scan  Identifier
  
<out>      ->      print <expr>
  
<if>       ->      cond [ <expr> <RO> <expr> ] <stat>
  
<loop>     ->      iter [ <expr> <RO> <expr> ] <stat>
  
<assign>   ->      Identifier  = <expr> 
  
<RO>       ->      < | = <  | >  | = > | < >   |   =   
  
## Project definition

### Language Semantics

- Basic semantics as in C - program executes sequentially from the beginning to the end, one statement at a time
- Conditional statement is like the else-less if statement in C
- Loop statement is like the while loop in C
- Assignment evaluates the expression on the right and assigns to the ID on the left
- Relational and arithmetical operators have the standard meaning (% is negation)
- IO reads/prints a 2-byte signed integer
- All data is 2-byte signed integer 
  
### Target

Virtual machine based on simple accumulator-based assembler. Virtual Machine made by Dr. Janikow. The machine also supports stack operations needed to implement local scoping rules.

Instruction List
ADD (1, ACC = ACC +arg)
BR (1, jump to arg)
BRNEG (1, jump to arg if ACC <0)
BRZNEG (1, jump to arg if ACC <=0)
BRPOS (1, jump to arg if ACC >0)
BRZPOS (1, jump to arg if ACC >=0)
BRZERO (1, jump to arg if ACC ==0)
COPY (2, arg1 = arg2)
DIV (1, ACC = ACC / arg)
MULT (1, ACC = ACC * arg)
READ (1, arg=input integer)
WRITE (1, put arg to output as integer)
STOP (0, stop program)
STORE (1, arg = ACC)
SUB (1, ACC = ACC - arg)
NOOP (0, nothing)
LOAD (1, ACC=arg)
// ADD, DIV, MULT, WRITE, LOAD, SUB can take either variable or immediate value as the arg: immediate value is positive integer or negative integer
PUSH (0, tos++)
POP (0, tos--)
STACKW (1,stack[tos-arg]=ACC)
STACKR (1,ACC=stack[tos-arg])
// PUSH/POP are only means to reserve/delete automatic storage.
// STACKW/STACKR n - these are stack write/read instructions. 
// n must be a non-negative number, and the access is to nth element down from TOS
// NOTE: TOS points to the topmost element on the stack
