#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

using std::cout;
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
	      BOOST_FOREACH(char byte, buf){
		      printf("%x ",byte);
	      }
	      cout<<"\n";

	    }


}
