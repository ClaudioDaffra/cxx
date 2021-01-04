
echo "building lib ... "

gcc -c -fpic  src/argParse.c 	-o obj/argParse.o
gcc -c -fpic  src/gc.c 			-o obj/gc.o
gcc -c -fpic  src/hashMap.c 	-o obj/hasmMap.o
gcc -c -fpic  src/stdio.c 		-o obj/stdio.o
gcc -c -fpic  src/string.c 		-o obj/string.o

echo "build dynamic lib"

gcc -shared obj/*.o -o lib/libcxx.so

echo "build static lib"

ar rcs lib/libcxx.a obj/*


