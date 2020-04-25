// Copyright 2019 dimakirol <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

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

namespace assio = boost::asio;
namespace logging = boost::log;
static const uint32_t SIZE_FILE = 10*1024*1024;
static const uint32_t Port = 2001;
static const std::string IP = "127.0.0.1";
static const uint32_t buf_size = 512;
static const uint32_t seconds_to_live = time(NULL) % 10 + 3;
static const uint32_t seconds_to_sleep = time(NULL) % 10 + 6;

typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

#endif // INCLUDE_HEADER_HPP_
