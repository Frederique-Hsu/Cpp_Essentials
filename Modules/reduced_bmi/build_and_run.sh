# File name     : build_and_run.sh
# Description   : 
# 
#


clang++-19 -std=c++20 M.cppm --precompile -o M.pcm

clang++-19 -std=c++20 M-impl.cpp -fprebuilt-module-path=. -c -o M-impl.o