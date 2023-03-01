#include "log.h"

namespace server{

Logger(const std::string& name)
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


void Logger::debug(LogEvent::ptr event){
}
void Logger::info(LogEvent::ptr event){
}
void Logger::warn(LogEvent::ptr event){
}
void Logger::error(LogEvent::ptr event){
}
void Logger::fatal(LogEvent::ptr event){
}
	

}
