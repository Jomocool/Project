#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__

#include<string>
#include<stdint.h>
#include<memory>

namespace syalr {

	//日志事件
	class LogEvent {
	public:
		typedef std::shared_ptr<LogEvent>ptr;//智能指针指向事件
		LogEvent();
	private:
		//事件属性
		const char* m_file = nullptr;//文件名
		int32_t m_line = 0;//行号
		uint32_t m_elapse = 0;//程序启动到现在的毫秒数
		uint32_t m_threadId = 0;//线程id
		unit32_t m_fiberId = 0;//协程id
		uint64_t m_time;//时间戳
		std::string m_content;//消息
	};

	//日志级别，分类
	class LogLevel {
	public:
		enum Level {
			DEBUG = 1,
			INFO = 2,
			WARN = 3,
			ERROR = 4,
			FATAL = 5
		};
	};

	//日志格式器
	class LogFormatter {
	public:
		typedef std::shared_ptr<LogFormatter>ptr;
	std:string formatter(LogEvent::ptr event);//提供给Appender去输出
	private:
	};

	//日志输出地
	class LogAppender {
	public:
		typedef std::shared_ptr<LogAppender>ptr;
		virtual ~LogAppender() {}

		void log(LogLevel::Level level, LogEvent::ptr event);
	private:
		LogLevel::Level m_level;//日志输出地的级别，主要针对哪些日志来定义的级别
	};

	//日志器
	class Logger {
	public:
		typedef std::shared_ptr<Logger>ptr;//智能存储

		Logger(const std::string& name = "root");

		void log(LogLevel::Level level,  LogEvent::ptr event);//记录(动作)
	private:
		std::string m_name;
		LogLevel::Level level;//日志器的日志级别
		LogAppender::ptr;//输出地
	};

	//输出到控制台的Appender
	class StdoutLogAppender : public LogAppender {
	};

	//定义到输出文件的Appender
	class FileLogAppender : public LogAppender {
	};

}

#endif