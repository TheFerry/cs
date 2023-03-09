targets : cls
cls: src/myls.cpp clean
	g++ src/myls.cpp -std=c++17 -o cls

clean:
	rm -rf cls

install:
	mv cls /usr/bin

uninstall:
	rm -rf /usr/bin/cls
