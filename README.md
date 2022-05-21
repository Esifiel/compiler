# compiler
2022 Compile-Principle Project

A tiny C compiler
## Env
Dependence of compilation:
```bash
# flex 2.6.4
# bison 3.5.1
# llvm 10.0.0
# clang 10.0.0
sudo apt install flex bison clang llvm
```
For visualization of AST, [Graphviz](https://graphviz.org/) is used:
```bash
# graphviz 0.19.2
pip install graphviz
```
(Tested in Ubuntu 20.04 for x86-64)
## Build
```bash
make
```
## Reference
[1] Levine, J., 2009. flex & bison.

[2] BNF of C: http://www.cs.man.ac.uk/~pjj/bnf/c_syntax.bnf / http://www.quut.com/c/ANSI-C-grammar-y-1995.html#direct-declarator

[3] LLVM Documentation and tutorial: https://www.llvm.org/docs/ / https://llvm.org/docs/tutorial/index.html