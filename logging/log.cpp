#include "log.hpp"
#include <stdexcept>
#include <string>
#include <iostream>




using namespace logging;

void File_log_policy::open_ostream(const std::string& name)
{
    m_pout_stream->open( name.c_str(), std::ios_base::binary|std::ios_base::out );
    if ( !m_pout_stream->is_open() )
    {
        throw(std::runtime_error("Logger: Unable to open an output stream "));
    }
}

void File_log_policy::close_ostream()
{
    if (m_pout_stream)
    {
        m_pout_stream->close();
    }
}

void File_log_policy::write(const std::string& msg)
{
    (*m_pout_stream)<<msg<<std::endl;
}

File_log_policy::~File_log_policy()
{
    if (m_pout_stream)
    {
        close_ostream();
    }
}

void Console_log_policy::write(const std::string& msg)
{
    std::cout << msg <<std::endl;
}
