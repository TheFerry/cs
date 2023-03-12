SRC := src/core/run.cpp src/file/file.cpp src/core/flags.cpp src/core/arranger.cpp
STDFLG := -std=c++17
OUTPUT := cs

targets : $(OUTPUT) test
$(OUTPUT): $(SRC)
	g++ $(SRC) $(STDFLG) -o $(OUTPUT)

test:src/assets/test.cpp src/core/arranger.cpp
	g++ src/assets/test.cpp src/core/arranger.cpp -o test
clean:
	rm -rf $(OUTPUT) test

install:targets
	mv $(OUTPUT) /usr/bin

uninstall:
	rm -rf /usr/bin/$(OUTPUT)
