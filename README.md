# mini-lisp
# MINI-LISP

The language that your project’s interpreter will process is a subset of **LISP**, which we call it Mini-LISP for convenience. This handout first offers a general description, then goes into details such as lexical structure and grammar of the subset


## Overview

LISP is an ancient programming language based on **S-expressions** and **lambda calculus**. All operations in Mini-LISP are written in parenthesized **prefix notation**. For example, a simple mathematical formula “(1 + 2) * 3” written in Mini-LISP is: 
(* (+ 1 2) 3) 
As a simplified language, Mini-LISP has only three types (**Boolean**, **number** and **function**) and a few operations.

## Type Definition
**Boolean**: Boolean type includes two values, #t for true and #f for false. 

**Number**: 
*Signed integer* from $$ −(2^{31}) $$ to $$2^{31} – 1$$ behavior out of this range is not defined. 

**Function**: See **wiki**. 

Casting: Not allowed, but type checking is a bonus feature.
## Operation Overview

**Numerical Operators**
|Name  |Symbol|Example|
|----------------|-------------------------------|-----------------------------|
|Plus|+            |`(+ 1 2) => 3`             |
|Minus          |-           |`(- 1 2) => -1`           |
|Multiply          |*|`(* 2 3) => 6`|
|Divide          |/|`(/ 6 3) => 2`|
|Modulus          |mod|`(mod 8 3) => 2`|
|Greater          |>|`(> 1 2) => #f`|
|Smaller          |<|`(< 1 2) => #t`|
|Equal            |=                              |     `(= 1 2) => #f` |      

**Logical Operators**
  |Name  |Symbol|Example|
|----------------|-------------------------------|-----------------------------|
|And|and           |`(and #t #f) => #f`             |
|Or          |or           |`(or #t #f) => #t`           |
|Not         |not|`(not #t) => #f`|

## Lexical Details


Preliminary Definitions: 

separator ::= ‘\t’(tab) | ‘\n’ | ‘\r’ | ‘ ’(space) 
letter ::= [a-z] 
digit ::= [0-9] 

Token Definitions: 

number ::= 0 | [1-9]digit* | -[1-9]digit* 
*Examples*: `0, 1, -23, 123456`
 ID ::= letter (letter | digit | ‘-’)* 
*Examples*: `x, y, john, cat-food bool-val ::= #t | #f`




                   
## Grammar Overview
PROGRAM ::= STMT+ 

STMT ::= EXP | DEF-STMT | PRINT-STMT 

PRINT-STMT ::= (print-num EXP) | (print-bool EXP) 

EXP ::= bool-val | number | VARIABLE | NUM-OP | LOGICAL-OP | FUN-EXP | FUN-CALL | IF-EXP 

NUM-OP ::= PLUS | MINUS | MULTIPLY | DIVIDE | MODULUS | GREATER | SMALLER | EQUAL 

PLUS ::= (+ EXP EXP+) 
MINUS ::= (- EXP EXP)
MULTIPLY ::= (* EXP EXP+) 
DIVIDE ::= (/ EXP EXP) 
MODULUS ::= (mod EXP EXP) 
GREATER ::= (> EXP EXP) 
SMALLER ::= (< EXP EXP) 
EQUAL ::= (= EXP EXP+) 

LOGICAL-OP ::= AND-OP | OR-OP | NOT-OP 

AND-OP ::= (and EXP EXP+) 
OR-OP ::= (or EXP EXP+) 
NOT-OP ::= (not EXP)

    

## Code

    int main () {
      while(EOF){
        if(stmts()){
          print answer;
        }
        else{
        }
      }      
    }
    
    bool stmts(){
      if(文法) return true;
      else return false ;
    }
    bool Pstmt(){
      if(文法) return true;
      else return false ;
    }
    bool EXP(){
      if(文法) return true;
      else return false ;
    }
    bool NOP(){
      if(文法) return true;
      else return false ;
    }
