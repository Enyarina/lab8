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
static const std::string IP = "127.0.0.1";
static const uint32_t buf_size = 512;
static const uint32_t seconds_to_live = 10;
static const uint32_t seconds_to_sleep = 5;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

void log_init(){
        boost::log::register_simple_formatter_factory
                <boost::log::trivial::severity_level, char>("Severity");
        logging::add_file_log
                (
                        logging::keywords::file_name = "log_%N.log",
                        logging::keywords::rotation_size = SIZE_FILE,
                        logging::keywords::time_based_rotation =
                              boost::log::sinks::file::rotation_at_time_point{0,
                                                                          0, 0},
                        logging::keywords::format =
                                "[%TimeStamp%] [%Severity%] %Message%");

        logging::add_console_log(
                std::cout,
                logging::keywords::format
                        = "[%TimeStamp%] [%Severity%]: %Message%");
        logging::add_common_attributes();
}
class SUClient{
public:
    SUClient(std::string _name):name(_name){
        log_init();
        io_service service;
        ip::tcp::endpoint ep(ip::address::from_string(IP), Port);
        sock = socket_ptr(new ip::tcp::socket(service));
        sock->connect(ep);
    }
    ~SUClient(){}
    std::string receive_message(){
        char data[buf_size];
        size_t read_bytes = sock->read_some(buffer(data));
        std::string read = data;
        if (read_bytes > 0) {
            if (read.find('\n') != std::string::npos) {
                read.assign(read, 0, read.rfind('\n'));
                BOOST_LOG_TRIVIAL(info) << "Received message:" << read;
            }
            else
                throw std::logic_error("Received wrong message");
        }
        else
            throw std::logic_error("Received empty message");
        return read;
    }
    void ping(){
        sock->write_some(buffer("ping\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Pinged";
        std::string message = receive_message();
        if (message == std::string("client_list_changed")){
            sock->write_some(buffer("clients\r\n"));
            BOOST_LOG_TRIVIAL(info) << "Clients request is sent";
            receive_message();
        }
        else if (message == std::string("too_late")){
            BOOST_LOG_TRIVIAL(fatal) << "Too late ping" << "Exiting server";
            throw std::exception();
        }
    }
    void knock_knock(){
        sock->write_some(buffer(name + "\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Name is sent";

        receive_message();

        sock->write_some(buffer("clients\r\n"));
        BOOST_LOG_TRIVIAL(info) << "Clients request is sent";
        receive_message();

        for (uint32_t i = 0; i < seconds_to_live; ++i) {
            std::this_thread::__sleep_for(std::chrono::seconds{1},
                                          std::chrono::nanoseconds{0});
            ping();
        }
        for (uint32_t i = 0; i < seconds_to_sleep; ++i) {
            std::this_thread::__sleep_for(std::chrono::seconds{1},
                                          std::chrono::nanoseconds{0});
        }
        ping();
    }

public:
    io_service service;
    socket_ptr sock;
    std::string name;
};
int  main(int argc, char* argv[]){
    if (argc)
        std::string client_name = argv[0];
    else{
        BOOST_LOG_TRIVIAL(fatal) << "No name mentioned"
        << "Type client name as the first argument";
        return -1;
    }
    try {
        SUClient client(client_name);
        client.knock_knock();
    } catch (std::logic_error const& e){
        BOOST_LOG_TRIVIAL(fatal) << "Received strange message";
    } catch (std::exception const& e){
        if (e.what() == std::string("read_some: End of file")){
            BOOST_LOG_TRIVIAL(fatal) <<
            "The connection to the server has been lost";
        }
        else{
            BOOST_LOG_TRIVIAL(fatal) << e.what();
        }
    }
    return 0;
}//P.S. SUClient -- means Super Ultra Client