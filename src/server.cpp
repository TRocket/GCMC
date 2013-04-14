#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/foreach.hpp>

using std::cout;
using std::endl;
using std::string;
using boost::asio::ip::tcp;
using namespace boost;

char read_byte(tcp::socket &sock){
	char data[1];
	asio::read(sock, asio::buffer(data, 1));
	return data[0];
}

short read_short(tcp::socket &sock){
	unsigned char data[2];
	asio::read(sock, asio::buffer(data, 2));
	return (data[0]<<8) + data[1];
}

int read_int(tcp::socket &sock){
	unsigned char data[4];
	asio::read(sock, asio::buffer(data, 4));
	return (data[0]<<24) + (data[1]<<16) + (data[2]<<8) + data[3];
}

string read_string(tcp::socket &sock){
	short str_len = read_short(sock);
	cout << "string length: " << str_len << "\n";
	flush(cout);
	char str[str_len];
	int i;
	for (i = 0; i < str_len; ++i) {
					str[i] = read_short(sock);
				}
	return str;
}

void write_byte(tcp::socket &sock, char bytedata){
	unsigned char data[1];
	data[0] = bytedata;
	asio::write(sock, asio::buffer(data, 1));
}

void write_short(tcp::socket &sock, short shortdata){
	unsigned char data[2];
	data[0] = shortdata;
	data[1] = shortdata >> 8 ;
	cout << "data: " << data << endl;
	asio::write(sock, asio::buffer(data, sizeof(data)));
}

void write_int(tcp::socket &sock, int intdata){
	unsigned char data[4];
	data[0] = intdata;
	data[1] = intdata >> 8;
	data[2] = intdata >> 16;
	data[3] = intdata >> 24;
	asio::write(sock, asio::buffer(data));
}

void write_string(tcp::socket &sock, string str){
	short str_len = str.length();
	str_len = 4;
	write_short(sock, str_len);
	str[str_len];
	for (int i = 0; i < str_len; ++i) {
		write_byte(sock, str[i]);
	}
}

int main(){
	cout << sizeof(char) << endl;
	cout << "gccraftbukkit\n";
	flush(cout);
	boost::asio::io_service io_service;
	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 25565));
	 for (;;) {
	      tcp::socket socket(io_service);
	      acceptor.accept(socket);
	      cout << "got connection\n";
	      flush(cout);
	      boost::system::error_code error;

	      //size_t len = socket.read_some(boost::asio::buffer(buf), error);
	      short protocol_ver;
	      short str_len;
	      char packetID = read_byte(socket);
	      std::string username_str;
	      std::string serveraddr_str;
	      int port;
	      cout << "packet ID" << std::hex << packetID << endl;
	      switch (packetID){
	      case 0x02:
	    	  protocol_ver = read_byte(socket);
	    	  cout << "protocol version: " << protocol_ver << endl;
	    	  username_str = read_string(socket);
	    	  cout << username_str << endl;
	    	  serveraddr_str = read_string(socket);
	    	  cout << serveraddr_str << endl;
	    	  port = read_int(socket);
	    	  cout << port << endl;

	    	  //write_byte(socket, 0xFD);
	    	  write_string(socket, "GCMC");
	    	  write_short(socket, 5);
	    	  write_byte(socket, 0xA);write_byte(socket, 0xB);write_byte(socket, 0xC);write_byte(socket, 0xD);write_byte(socket, 0xE);
	    	  write_short(socket, 4);
	    	  write_byte(socket, 0xF);write_byte(socket, 0x11);write_byte(socket, 0xF);write_byte(socket, 0x11);

	    	  break;
	      default:
	    	  cout << packetID;
	    	  cout << " unknown packet id\n";

	      }

	      //BOOST_FOREACH(char byte, buf){
		  //    printf("%x ",byte);
	      //}
	      //cout<<"\n";

	    }


}
