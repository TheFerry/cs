
SRC := src/myls.cpp src/file/file.cpp
STDFLG := -std=c++17
OUTPUT := cs
targets : $(OUTPUT)
$(OUTPUT): $(SRC)
	g++ $(SRC) $(STDFLG) -o $(OUTPUT)

clean:
	rm -rf $(OUTPUT)

install:targets
	mv $(OUTPUT) /usr/bin

uninstall:
	rm -rf /usr/bin/$(OUTPUT)
