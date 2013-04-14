objects = server.o
headers = 
binary = gccraftbukkit
CPPFLAGS = -g

$(binary): $(objects) 
	g++ -g -o $@ $(objects) -l boost_system

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)

