FLG := -std=c++17
OUTPUT := cs

targets : $(OUTPUT) test
$(OUTPUT):file.o flags.o arranger.o src/core/run.cpp
	g++ file.o flags.o arranger.o src/core/run.cpp $(FLG) -o $(OUTPUT)
file.o:src/file/file.cpp src/file/file.h
	g++ -c src/file/file.cpp $(FLG) -o file.o
flags.o:src/core/flags.cpp src/core/flags.h
	g++ -c src/core/flags.cpp $(FLG) -o flags.o
arranger.o:src/core/arranger.cpp src/core/arranger.h
	g++ -c src/core/arranger.cpp  $(FLG) -o arranger.o

test:src/assets/test.cpp 	arranger.o flags.o
	g++ src/assets/test.cpp arranger.o flags.o  $(FLG) -o test

clean:
	rm -rf $(OUTPUT) test *.o

install:$(OUTPUT)
	mv $(OUTPUT) /usr/bin


uninstall:
	rm -rf /usr/bin/$(OUTPUT)
