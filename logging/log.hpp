#pragma once

#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <mutex>
#include <string>
#include <fstream>
#include <string>
#include <fstream>
#include <memory>

namespace logging
{

class Log_policy_interface
{
public:
    virtual void open_ostream( const std::string& name) = 0;
    virtual void close_ostream() = 0;
    virtual void write(const std::string& msg) = 0;
};

class File_log_policy : public Log_policy_interface
{
public:
    File_log_policy()
        :out_stream( new std::ofstream ) {}
    void open_ostream (const std::string& name) override;
    void close_ostream() override;
    void write(const std::string& msg) override;
    virtual ~File_log_policy();

private:
    std::ofstream  *out_stream;
};

class Console_log_policy : public Log_policy_interface
{
public:
    Console_log_policy(){}
    void open_ostream (const std::string& name) override {};
    void open_ostream () {}
    void close_ostream() {}
    void write(const std::string& msg) override;
    virtual ~Console_log_policy(){}
};

enum class severity_type : char
{
    debug   = 1,
    warning = 2,
    error   = 3
};

template < typename log_policy >
class Logger
{
private:
    unsigned          log_line_number;
    std::string       get_time();
    std::string       get_logline_header();
    std::stringstream log_stream;
    std::mutex        write_mutex;
    log_policy       *policy;

    void print_impl();
    template <typename First, typename...Rest>
        void print_impl(First parm1, Rest...parm);
public:
    template <severity_type severity, typename...Args >
        void print( Args...args );


    Logger()
    {
        log_line_number = 0;
        policy = new log_policy;

        if (!policy)
        {
            throw(std::runtime_error("Logger: unable to create Logger instance"));
        }
        policy->open_ostream( );
    }

    Logger( const std::string& name)
    {
        log_line_number = 0;
        policy = new log_policy;

        if (!policy)
        {
            throw(std::runtime_error("Logger: unable to create Logger instance"));
        }
        policy->open_ostream( name );
    }

    ~Logger()
    {
        if (policy)
        {
            policy->close_ostream();
            delete policy;
        }
    }
};

template< typename log_policy>
    template< severity_type severity, typename...Args >
void Logger< log_policy >::print( Args...args )
{
    std::lock_guard<std::mutex> lock(write_mutex);
    switch ( severity )
    {
        case severity_type::debug:
            log_stream<<" <DEBUG>: ";
            break;
        case severity_type::warning:
            log_stream<<" <WARNING>: ";
            break;
        case severity_type::error:
            log_stream<<" <ERROR>: ";
            break;
    }
    print_impl (args...);
}

template <typename log_policy>
void Logger< log_policy >::print_impl()
{
    policy->write( get_logline_header() + log_stream.str());
    log_stream.str("");
}

template < typename log_policy>
  template<typename First, typename...Rest >
void Logger< log_policy >::print_impl(First parm1, Rest...parm)
{
    log_stream<<parm1;
    print_impl(parm...);
}


template < typename log_policy >
std::string Logger < log_policy >::get_time()
{
    time_t raw_time;
    std::string time_str;
    time(&raw_time);
    time_str = ctime( &raw_time );

    //remove newline char
    return time_str.substr( 0, time_str.size() -1 );
}

template < typename log_policy >
std::string Logger < log_policy >::get_logline_header()
{
    std::stringstream header;
    header.str("");
    header.fill('0');
    header.width(7);
    header <<log_line_number++<<" < "<<get_time()<< " - ";
    header.fill('0');
    header.width(20);
    header <<clock()<< " > ~ ";
    return header.str();
}
}
