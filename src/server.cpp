#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

using std::cout;
using std::endl;
using boost::asio::ip::tcp;

int main(){
	cout << "gccraftbukkit\n";
	flush(cout);
	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 25565));
	 for (;;) {
	      tcp::socket socket(io_service);
	      acceptor.accept(socket);
	      cout << "got connection\n";
	      	flush(cout);
	      boost::system::error_code ignored_error;
	      boost::array<char, 128> buf;
	      boost::system::error_code error;

	      size_t len = socket.read_some(boost::asio::buffer(buf), error);
	      switch (buf[0]){
	      case 0x02:
	    	  short protocol_ver = buf[1];
	    	  cout << "protocol version: " << protocol_ver << endl;
	    	  short str_len = buf[2]+buf[3];
	    	  cout << "string length: " << str_len << endl;
	    	  char username_str[str_len];
	    	  int i;
	    	  for (i = 0; i < str_len; ++i) {
				username_str[i] = buf[(i*2)+4]+buf[(i*2)+5];
			}
	    	  cout << username_str << endl;

	      }
	      BOOST_FOREACH(char byte, buf){
		      printf("%x ",byte);
	      }
	      cout<<"\n";

	    }


}
