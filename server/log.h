#ifndef __SERVER_LOG_H__
#define __SERVER_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <fstream>
namespace server{

//日志事件
class LogEvent {
public:
	typedef std::shared_ptr<LogEvent> ptr;
private:
	const char* m_file = nullptr;	//文件名
	int32_t m_line = 0;		//行号
	uint32_t m_elapse = 0;		//程序运行开始到现在的毫秒数
	uint32_t m_threadID = 0;	//线程ID
	uint32_t m_fiberID = 0;		//协程ID
	uint64_t m_time = 0;		//时间戳
	std::string m_content;		//日志内容
};

//日志级别
class LogLevel {
public:
	enum Level {
		DEBUG = 1,
		INFO = 2;
		WARN = 3;
		ERROR = 4;
		FATAL = 5
	};
};

//日志格式器
class LogFormatter {
public:
	typedef std::shared_ptr<LogFormatter> ptr;

	std::string format(LogEvent::ptr event);
};

//日志输出地G
class LogAppender {
public:
	typedef std::shared_ptr<LogAppender> ptr;
	virtual ~LogAppender() {}

	virtual void log(LogLevel::Level level,LogEvent::ptr event) = 0;

	void setFormatter(LogFormatter::ptr val) {m_formatter = val; }
	LogFormatter::ptr getFormatter() const { return m_formatter; }

private:
	LogLevel::Level m_level;
	LogFormatter::ptr m_formatter;
};

//日志器
class Logger {
public:
	typedef std::shared_ptr<Logger> ptr;

	Logger();
	Logger(const std::string& name = "root");
	void log(LogLevel::Level level,LogEvent::ptr event);

	void debug(LogEvent::ptr event);
	void info(LogEvent::ptr event);
	void warn(LogEvent::ptr event);
	void error(LogEvent::ptr event);
	void fatal(LogEvent::ptr event);
	
	void addAppender(LogAppender::ptr appender);
	void delAppender(LogAppender::ptr appender);

	LogLevel::Level getLevel() const {return m_level;}
	void setLevel(LogLevel::Level val) {m_level = val;}
private:
	std::string m_name;		//日志名称
	LogLevel::Level m_level;	//日志级别
	std::list<LogAppender::ptr> m_appender; //appender集合
}；

//输出到控制台
class StdoutLogAppender: public LogAppender {
public:
	typedef std::shared_ptr<StdoutLogAppender> ptr;
	void log(LogLevel::Level level,LogEvent::ptr event);
};

//输出到文件
class FileLogAppender: public LogAppender {
public:
	typedef shared_ptr<FileLogAppender> ptr;
	FileLogAppender(){};
	FileLogAppender(const std::string& filename);
	void log(LogLevel::Level level,LogEvent::ptr event);
	bool reopen();
private:
	std::string m_filename;
	std::ofstream m_filestream;
};
}
