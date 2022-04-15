# compiler
2022 Compile-Principle Project

A tiny C compiler (maybe)
## Env
Dependence:
```
flex 2.6.4
bison 3.5.1
llvm 10.0.0
```
Tested in Ubuntu 20.04 for x86-64
## Build
For Linux:
```bash
sudo apt install flex bison llvm
make
```
## Reference
[1] Levine, J., 2009. flex & bison.

[2] BNF of C: [Reference 1](https://blog.csdn.net/PINBODEXIAOZHU/article/details/25394417) / [Reference 2](https://cs.wmich.edu/~gupta/teaching/cs4850/sumII06/The%20syntax%20of%20C%20in%20Backus-Naur%20form.htm)

[3] ISO/IEC 9899:1999 "Programming languages - C"

[4] [LLVM Documentation](https://www.llvm.org/docs/) / [LLVM tutorial](https://llvm.org/docs/tutorial/index.html)