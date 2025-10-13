# File name     : build_and_run.sh
# Description   :
#
#


# Precompiling the module
clang++-19 -v -std=c++20 -g interface_part.cppm --precompile -o M-interface_part.pcm
echo
echo

clang++-19 -v -std=c++20 -g impl_part.cppm --precompile -fprebuilt-module-path=. -o M-impl_part.pcm
echo
echo

clang++-19 -v -std=c++20 -g M.cppm --precompile -fprebuilt-module-path=. -o M.pcm
echo
echo

# 注意： 模块 M.cppm 的预编译依赖于 interface_part.cppm 和 impl_part.cppm， 有编译顺序的要求。
#       因为interface_part和impl_part是模块M的两个分部. 
#       所以分部要先于模块编译。

# clang++-19 -v -std=c++20 M.cppm --precompile -fmodule-file=M:interface_part=M-interface_part.pcm -fmodule-file=M:impl_part=M-impl_part.pcm -o M.pcm

clang++-19 -v -std=c++20 -g Impl.cpp -fprebuilt-module-path=. -c -o Impl.o
echo
echo

# Compiling the User
clang++-19 -v -std=c++20 -g User.cpp -fprebuilt-module-path=. -c -o User.o
echo
echo

# Compiling the module and linking them together
clang++-19 -v -std=c++20 -g M-interface_part.pcm -fprebuilt-module-path=. -c -o M-interface_part.o
echo
echo

clang++-19 -v -std=c++20 -g M-impl_part.pcm -fprebuilt-module-path=. -c -o M-impl_part.o
echo
echo

clang++-19 -v -std=c++20 -g M.pcm -fprebuilt-module-path=. -c -o M.o
echo
echo

clang++-19 -v User.o Impl.o M-interface_part.o M-impl_part.o M.o -o complex_hello_world_module
echo