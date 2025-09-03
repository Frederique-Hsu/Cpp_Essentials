# File name     : build_and_run.sh
# Description   : 
#
#



clang++-19 -std=c++20 Hello.cppm --precompile -o Hello.pcm

clang++-19 -std=c++20 use.cpp -fmodule-file=Hello=Hello.pcm Hello.pcm -o Hello.out

./Hello.out