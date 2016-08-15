#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <mutex>
#include <string>
#include <fstream>
#include <string>
#include <fstream>
#include <memory>


// make_unique added for gcc 4.9.0
// Test for GCC < 4.9.0
#if GCC_VERSION < 40900

#include <cstddef>
#include <type_traits>
#include <utility>

namespace std {
    template<class T> struct _Unique_if {
            typedef unique_ptr<T> _Single_object;
        };

    template<class T> struct _Unique_if<T[]> {
            typedef unique_ptr<T[]> _Unknown_bound;
        };

    template<class T, size_t N> struct _Unique_if<T[N]> {
            typedef void _Known_bound;
        };

    template<class T, class... Args>
        typename _Unique_if<T>::_Single_object
        make_unique(Args&&... args) {
                    return unique_ptr<T>(new T(std::forward<Args>(args)...));
                }

    template<class T>
        typename _Unique_if<T>::_Unknown_bound
        make_unique(size_t n) {
                    typedef typename remove_extent<T>::type U;
                    return unique_ptr<T>(new U[n]());
                }

    template<class T, class... Args>
        typename _Unique_if<T>::_Known_bound
        make_unique(Args&&...) = delete;
}
#endif

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
    {
        m_pout_stream = std::make_unique<std::ofstream>();
    }
    void open_ostream (const std::string& name) override;
    void close_ostream() override;
    void write(const std::string& msg) override;
    virtual ~File_log_policy();

private:
    std::unique_ptr<std::ofstream>  m_pout_stream;
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
    unsigned                    m_log_line_number;
    std::string                 get_time();
    std::string                 get_logline_header();
    std::stringstream           m_log_stream;
    std::mutex                  m_write_mutex;
    std::unique_ptr<log_policy> m_ppolicy;

    void print_impl();
    template <typename First, typename...Rest>
        void print_impl(First parm1, Rest...parm);
public:
    template <severity_type severity, typename...Args >
        void print( Args...args );


    Logger()
    {
        m_log_line_number = 0;
        m_ppolicy = std::make_unique<log_policy>();

        if (!m_ppolicy)
        {
            throw(std::runtime_error("Logger: unable to create Logger instance"));
        }
        m_ppolicy->open_ostream( );
    }

    Logger( const std::string& name)
    {
        m_log_line_number = 0;
        m_ppolicy = std::make_unique<log_policy>();

        if (!m_ppolicy)
        {
            throw(std::runtime_error("Logger: unable to create Logger instance"));
        }
        m_ppolicy->open_ostream( name );
    }

    ~Logger()
    {
        if (m_ppolicy)
        {
            m_ppolicy->close_ostream();
        }
    }
};

template< typename log_policy>
    template< severity_type severity, typename...Args >
void Logger< log_policy >::print( Args...args )
{
    std::lock_guard<std::mutex> lock(m_write_mutex);
    switch ( severity )
    {
        case severity_type::debug:
            m_log_stream<<" <DEBUG>: ";
            break;
        case severity_type::warning:
            m_log_stream<<" <WARNING>: ";
            break;
        case severity_type::error:
            m_log_stream<<" <ERROR>: ";
            break;
    }
    print_impl (args...);
}

template <typename log_policy>
void Logger< log_policy >::print_impl()
{
    m_ppolicy->write( get_logline_header() + m_log_stream.str());
    m_log_stream.str("");
}

template < typename log_policy>
  template<typename First, typename...Rest >
void Logger< log_policy >::print_impl(First parm1, Rest...parm)
{
    m_log_stream<<parm1;
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
    header <<m_log_line_number++<<" < "<<get_time()<< " - ";
    header.fill('0');
    header.width(20);
    header <<clock()<< " > ~ ";
    return header.str();
}
}
