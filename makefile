# perche' mai stai guardango un makefile mah...
# NON mi dire ogni comando che esegui... ti prego...
.SILENT: 
build/test: build/newton.o build/eulero.o build/utils.o build/heun.o build/cnic.o src/main.c | build
	echo "Compilando..."
	gcc -Iinclude src/main.c build/newton.o build/eulero.o build/cnic.o build/heun.o build/utils.o -lm -o build/test 
.PHONY: debug
debug: build/newton.o build/eulero.o build/utils.o build/heun.o build/cnic.o src/main.c | build
	echo "Compilando versione debug..."
	gcc -Iinclude src/main.c build/newton.o build/eulero.o build/cnic.o build/heun.o build/utils.o -lm -o build/test -g
# eh gia
build:
	mkdir -p build
# 	target per gli object file :P
build/test.o: src/main.c | build
	gcc -Iinclude -c src/main.c -o build/test.o
build/newton.o: src/newton.c | build
	gcc -Iinclude -c src/newton.c -o build/newton.o
build/eulero.o: src/eulero.c | build
	gcc -Iinclude -c src/eulero.c -o build/eulero.o
build/cnic.o: src/cnic.c | build
	gcc -Iinclude -c src/cnic.c -o build/cnic.o
build/heun.o: src/heun.c | build
	gcc -Iinclude -c src/heun.c -o build/heun.o
build/utils.o: src/methods_utils.c | build
	gcc -Iinclude -c src/methods_utils.c -o build/utils.o
.PHONY: build_and_clean
build_and_clean: build/test clean_obj
	echo "ecco fatto!"
#   __________
# < PULIZIA!!! >
#   ----------
#          \   ^__^ 
#           \  (oo)\_______
#              (__)\       )\/\\
#                  ||----w |
#                  ||     ||  
.PHONY: clean
clean: 
	rm -r build
# se volessi solo rimuovere gli obj file dopo compilazione...
.PHONY: clean_obj
clean_obj:
	rm -r build/*.o