#include "log.h"

namespace server{

Logger::Logger(const std::string& name)
{
	this->m_name = name;
}

void Logger::addAppender(LogAppender::ptr appender){
	m_appender.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
	for(auto it = m_appender.begin();
		it !=m_appender.end(); ++it){
		if(*it == appender) {
			m_appender.erase(it);
			break;
		}
	}
}

void Logger::log(LogLevel::Level level,LogEvent::ptr event){
	if(level >= m_level ) {
		for(auto& i : m_appender)
		{
			i->log(level,event);
		}
	}
}


//各个级别的日志事件
void Logger::debug(LogEvent::ptr event){
}
void Logger::info(LogEvent::ptr event){
}
void Logger::warn(LogEvent::ptr event){
}
void Logger::error(LogEvent::ptr event){
}
void Logger::fatal(LogEvent::ptr event){
	debug(LogLevel::FATAL,event);
}

//控制台输出
void StdoutLogAppender::log(LogLevel::Level level,LogEvent::ptr event){
	if(m_level >= level) {
		std::cout << m_formatter.format(event);
	}
}//文件输出	
FileLogAppender::FileLogAppender(const std::string& filename):m_filename(filename){

}

void FileLogAppender::log(LogLevel::Level level,LogEvent::ptr event){
	if(m_level >= level)
	{
		m_filestream << m_formatter.format(event);
	}
}
bool FileLogAppender::reopen(){
}
	if(m_filestream) {
		m_filestream.close();
	}

	m_filestream.open(m_filename);
	return !!m_filestream;
}
