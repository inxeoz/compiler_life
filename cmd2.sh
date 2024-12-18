rm -rf build
mkdir "build"
cp code.ved ./build
cd build || exit
cmake ..
make

### getting input and saving ir to llvm file
./compiler_life code.ved > output.ll

###### start of dependent process for native (linux i guess)
ls
cat output.ll
llc -filetype=obj output.ll -o output.o
ls
clang output.o -o test_program -no-pie
ls
./test_program
#### end of dependent process



