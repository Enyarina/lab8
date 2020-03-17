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

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

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
class My_begemot_is_drunk{
public:
    My_begemot_is_drunk(std::string _name):name(_name){
        log_init();
        io_service service;
        ip::tcp::endpoint ep( ip::address::from_string("127.0.0.1"), Port);
        sock = socket_ptr(new ip::tcp::socket(service));
        sock->connect(ep);
    }
    ~My_begemot_is_drunk(){}
    std::string receive_message(){
        char data[512];
        size_t read_bytes = sock->read_some(buffer(data));
        std::string read = data;
        if (read.find('\n') != std::string::npos)
            read.assign(read, 0, read.rfind('\n'));
        if (read_bytes > 0)
            BOOST_LOG_TRIVIAL(info) << "Received message:" << read;
        return read;
    }
    void knock_knock(){
        sock->write_some(buffer(name +"\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Name is sent";

        receive_message();

        sock->write_some(buffer("clients\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Clients request is sent";
        receive_message();

        for (uint32_t i = 0; i < 10; ++i){
            std::this_thread::__sleep_for(std::chrono::seconds{1},
                                          std::chrono::nanoseconds{0});
            sock->write_some(buffer("ping\r\n"));
            BOOST_LOG_TRIVIAL(info) << "Pinged";
            receive_message();
            BOOST_LOG_TRIVIAL(info) << "Ponged";
        }
        for (uint32_t i = 0; i < 5; ++i){
            std::this_thread::__sleep_for(std::chrono::seconds{1},
                                          std::chrono::nanoseconds{0});
        }
        sock->write_some(buffer("Bye\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Byed";
        while (true) continue;
    }

public:
    io_service service;
    socket_ptr sock;
    std::string name;
};
int main(){
    My_begemot_is_drunk client(std::string("Kirill"));
    client.knock_knock();

    return 0;
}