#include <ctime>
#include <vector>
#include <thread>
#include <cstdint>
#include <iostream>
#include <string>
#include <mutex>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/expressions/keyword.hpp>

using namespace boost::asio;
namespace logging = boost::log;
static const uint32_t SIZE_FILE = 10*1024*1024;
static const uint32_t Port = 2001;

void log_init(){
        boost::log::register_simple_formatter_factory
                <boost::log::trivial::severity_level, char>("Severity");
        /*logging::add_file_log
                (
                        logging::keywords::file_name = "log_%N.log",
                        logging::keywords::rotation_size = SIZE_FILE,
                        logging::keywords::time_based_rotation =
                              boost::log::sinks::file::rotation_at_time_point{0,
                                                                          0, 0},
                        logging::keywords::format =
                                "[%TimeStamp%] [%Severity%] %Message%");

        */logging::add_console_log(
                std::cout,
                logging::keywords::format
                        = "[%TimeStamp%] [%Severity%]: %Message%");
        logging::add_common_attributes();
}

int main(){
log_init();
io_service service;
ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), Port);
ip::tcp::socket sock(service);
sock.connect(ep);
sock.write_some(buffer("Kirill\r\n"));
BOOST_LOG_TRIVIAL(info) << "Name is sent";

char data[512];
size_t read_bytes = sock.read_some(buffer(data));
std::string read = data; 
if (read_bytes > 0)
	BOOST_LOG_TRIVIAL(info) << "Received message:" << read;

sock.write_some(buffer("clients\r\n"));
BOOST_LOG_TRIVIAL(info) << "Clients request is sent";

char another_data[512];
read_bytes = sock.read_some(buffer(another_data));
read = another_data;
if (read_bytes > 0)
	BOOST_LOG_TRIVIAL(info) << "Received message:" << read;
while(true) continue;
return 0;
}