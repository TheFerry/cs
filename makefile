SRC := src/core/run.cpp src/file/file.cpp src/core/flags.cpp src/core/arranger.cpp
FLG := -std=c++17
OUTPUT := cs

targets : $(OUTPUT) test
$(OUTPUT): $(SRC)
	g++ $(SRC) $(FLG) -o $(OUTPUT)

test:src/assets/test.cpp src/core/arranger.cpp
	g++ src/assets/test.cpp src/core/flags.cpp src/core/arranger.cpp -o test
clean:
	rm -rf $(OUTPUT) test

install:$(OUTPUT)
	mv $(OUTPUT) /usr/bin


uninstall:
	rm -rf /usr/bin/$(OUTPUT)
