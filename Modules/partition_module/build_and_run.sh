# File name     : build_and_run.sh
# Description   : 
# 
#


mkdir build

#===================================================================================================

clang++-19 -std=c++20 m-partA.cppm --precompile -o build/m-partA.pcm

clang++-19 -std=c++20 m-partB.cppm --precompile -o build/m-partB.pcm

clang++-19 -std=c++20 m.cppm --precompile -fprebuilt-module-path=./build/ -o build/m.pcm

clang++-19 -std=c++20 useBOnly.cppm --precompile -fprebuilt-module-path=./build/ -o build/useBOnly.pcm

clang++-19 -std=c++20 A.cppm --precompile -o build/A.pcm

clang++-19 -std=c++20 B.cppm --precompile -fprebuilt-module-path=./build/ -o build/B.pcm

#===================================================================================================

clang++-19 -std=c++20 Use.cpp -fprebuilt-module-path=./build/ -c -o build/Use.o

clang++-19 -std=c++20 main.cpp -fprebuilt-module-path=./build/ -c -o build/main.o

#===================================================================================================

clang++-19 -std=c++20 build/m-partA.pcm -fprebuilt-module-path=./build/ -c -o build/m-partA.o

clang++-19 -std=c++20 build/m-partB.pcm -fprebuilt-module-path=./build/ -c -o build/m-partB.o

clang++-19 -std=c++20 build/m.pcm -fprebuilt-module-path=./build/ -c -o build/m.o

clang++-19 -std=c++20 build/useBOnly.pcm -fprebuilt-module-path=./build/ -c -o build/useBOnly.o

clang++-19 -std=c++20 build/A.pcm -c -o build/A.o

clang++-19 -std=c+=20 build/B.pcm -fprebuilt-module-path=./build/ -c -o build/B.o

#===================================================================================================

clang++-19 build/*.o -o build/partition_module

#===================================================================================================

./build/partition_module

md5sum ./build/useBOnly.pcm

md5sum ./build/B.pcm