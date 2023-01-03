targets : ls.out
ls.out: myls.cpp clean
	g++ myls.cpp -std=c++17 -o ls.out

clean:
	rm -rf ls.out
