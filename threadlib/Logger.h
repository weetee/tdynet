#ifndef TDY_NET_LOGFILE_H
#define TDY_NET_LOGFILE_H

#include <string>
#include <fstream>
#include "Timer.h"

using namespace std;

namespace tdy
{

class TextDecorator
{
public:
	static string FileHeader(const string &p_title)
	{
		return 	"============================================\n" +
				p_title + "\n" +
				"============================================\n\n";
	}

	static string SessionOpen()
	{
		return "\n";
	}

	static string SessionClose()
	{
		return "\n";
	}

	static string Decorate(const string &p_string)
    {
        return p_string + "\n";
    }
};	//TextDecorator end

template<class decorator>
class Logger
{
public:
	Logger(	const string &p_filename,
			const string &p_logtitle);

	~Logger();
	void Log(const string &p_entry);

private:
	fstream m_logfile;

};	//Logger end


template<class decorator>
Logger<decorator>::Logger( const std::string& p_filename,
                           const std::string& p_logtitle,
                           bool p_timestamp,
                           bool p_datestamp )
{
    // now the tricky part... testing to see if a file is open or not.
    // stupid C++. You need to open a file in read mode, and if it doesn't
    // open correctly, you know that it doesn't exist.
    std::fstream filetester( p_filename.c_str(), std::ios::in );

    if( filetester.is_open() )
    {
        // the file exists, so just close the test file
        filetester.close();

        // open the real file
        m_logfile.open( p_filename.c_str(), std::ios::out | std::ios::app );
    }
    else
    {
        // file doesn't exist.
        m_logfile.open( p_filename.c_str(), std::ios::out );

        // print out a file header to the file
        m_logfile << decorator::FileHeader( p_logtitle );
    }

    // print out an opening statement. Make sure it is time-and-date-stamped
    // as well.
    m_timestamp = true;
    m_datestamp = true;
    m_logfile << decorator::SessionOpen();
    Log( "Session opened." );
    m_timestamp = p_timestamp;
    m_datestamp = p_datestamp;
}

template<class 

template< class decorator >
Logger< decorator >::~Logger()
{
    m_timestamp = true;
    m_datestamp = true;
    Log( "Session closed." );
    m_logfile << decorator::SessionClose();

}


template< class decorator >
void Logger< decorator >::Log( const std::string& p_entry )
{
    std::string message;

    if( m_datestamp )
    {
        message += "[" + DateStamp() + "] ";
    }
    if( m_timestamp )
    {
        message += "[" + TimeStamp() + "] ";
    }

    message += p_entry;
    m_logfile << decorator::Decorate( message );
    m_logfile.flush();
}


}	//namespace tdy end



#endif //TDY_NET_LOGFILE_H