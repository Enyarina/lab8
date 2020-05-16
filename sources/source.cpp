// Copyright 2019 enrina <your_email>

#include <header.hpp>

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
class SuperClient{
public:
    explicit SuperClient(std::string _name):name(_name){
        log_init();
        assio::io_service service;
        assio::ip::tcp::endpoint ep(assio::ip::address::from_string(IP), Port);
        sock = socket_ptr(new assio::ip::tcp::socket(service));
        sock->connect(ep);
    }
    ~SuperClient(){}
    std::string receive_message(){
        char data[512];
        size_t read_bytes = sock->read_some(assio::buffer(data));
        std::string read = data;
        if (read_bytes > 0) {
            if (read.find('\n') != std::string::npos) {
                read.assign(read, 0, read.rfind('\n'));
            } else {
                throw std::logic_error("Received wrong message");
            }
        } else {
            throw std::logic_error("Received empty message");
        }
        return read;
    }
    void ping(){
        sock->write_some(assio::buffer("ping\n"));
        BOOST_LOG_TRIVIAL(info) << "Pinged";
        std::string message = receive_message();
        if (message == std::string("client_list_changed")) {
            sock->write_some(assio::buffer("clients\n"));
            BOOST_LOG_TRIVIAL(info) << "Clients request is sent";
            BOOST_LOG_TRIVIAL(info) << "Clients:" << receive_message();
        } else if (message == std::string("too_late")) {
            BOOST_LOG_TRIVIAL(fatal) << "Too late ping"
                                     << std::endl << "Exiting server";
            throw std::exception();
        } else {
            BOOST_LOG_TRIVIAL(info) << "Received message:" << message;
        }
    }
    void knock_knock(){
        sock->write_some(assio::buffer(name + "\n"));
        BOOST_LOG_TRIVIAL(info) << "Name is sent " << name;

        receive_message();

        sock->write_some(assio::buffer("clients\n"));
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
    assio::io_service service;
    socket_ptr sock;
    std::string name;
};
int  main(int argc, char* argv[]){
    std::string client_name;
    if (argc == 2) {
        client_name = argv[1];
    } else {
        BOOST_LOG_TRIVIAL(fatal) << "No name mentioned"
        << "Type client name as the first argument";
        return -1;
    }
    try {
        SuperClient client(client_name);
        client.knock_knock();
    } catch (std::logic_error const& e) {
        BOOST_LOG_TRIVIAL(fatal) << "Received strange message";
    } catch (std::exception const& e){
        if (e.what() == std::string("read_some: End of file")){
            BOOST_LOG_TRIVIAL(fatal) <<
            "The connection to the server has been lost";
        } else {
            if (e.what() != std::string("std::exception"))
                BOOST_LOG_TRIVIAL(fatal) << e.what();
        }
    }
    return 0;
}
