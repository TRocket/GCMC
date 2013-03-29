objects = server.o
headers = 
binary = gccraftbukkit

$(binary): $(objects) 
	g++ -o $@ $(objects) -l boost_system

$(objects): $(headers)

.PHONY: clean
clean:
	rm -f $(objects) $(binary)

