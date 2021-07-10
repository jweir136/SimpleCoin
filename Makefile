build:
	g++ $(CPPFLAGS) $(CFLAGS) -std=c++11 -I. SimpleCoin/*.cpp -o app

check:
	g++ $(CPPFLAGS) $(CFLAGS) -std=c++11 -I. test/*.test.cpp -o test/testapp
	./test/testapp
	rm ./test/testapp
run:
	g++ $(CPPFLAGS) $(CFLAGS) -std=c++11 -I. SimpleCoin/*.cpp -o app
	./app
check_cryptography:
	g++ $(CPPFLAGS) $(CFLAGS) -std=c++11 -I. test/Cryptography/*.test.cpp -o test/testapp -lcrypto
	./test/testapp
	rm ./test/testapp