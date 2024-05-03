# file: Makefile
# builds the password manager program

CXX = g++

CPPFLAGS += -I/usr/include

LDFLAGS += -L/usr/lib/x86_64-linux-gnu

LDLIBS += -lssl -lcrypto


# build the program executable, call it "passwordManager"
passwordManager: main.o 
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o passwordManager main.o $(LDLIBS)

# compile the object files
main.o: main.cpp main.h
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c main.cpp $(LDLIBS)

# clean obj and exe files
clean:
	rm *.o passwordManager
