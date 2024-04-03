#pragma once
#include <chrono>
#include <string>
#include <fstream>
#include <iostream>

#define THROW_RIFT_EXCEPTION(msg,type) throw RiftException((msg),(type), __FILE__, __FUNCTION__, __LINE__)

namespace rift2d
{

	enum class RiftExceptionType
	{
		Error, Warning, Info
	};

	class RiftException final
	{
		
	public:
		

		RiftException(std::string what, const RiftExceptionType& type, std::string file, std::string function, int line):
			m_what(std::move(what)),m_exType(type), m_file(std::move(file)),m_function(std::move(function)),m_line(line){}

		const char* what() const noexcept
		{
			return m_what.c_str();
		}

		void logToFile() const
		{
			std::ofstream logFile("error.log", std::ios::app);
			if(!logFile)
			{
				std::cerr << "Couldn't log to file\n";
				return;
			}

			const auto now = std::chrono::system_clock::now();
			auto nowTimeT = std::chrono::system_clock::to_time_t(now);

			// Convert system time to tm as local time
			std::tm bt{};
#if defined(_WIN32) || defined(_WIN64)
			localtime_s(&bt, &nowTimeT);
#else
			localtime_r(&nowTimeT, &bt); // POSIX
#endif

			logFile << std::put_time(&bt, "%Y-%m-%d %H:%M:%S")
				<< " [" << type() << "] " << what() << " [FILE]: " << m_file << " [FUNCTION] " << m_function << " [LINE] " << m_line << '\n';
		}
		
	private:
		std::string m_what{};
		RiftExceptionType m_exType{};
		std::string m_file{};
		std::string m_function{};
		int m_line{};

		const char* type() const noexcept
		{
			switch (m_exType)
			{
			case RiftExceptionType::Error:
				return "ERROR";
			case RiftExceptionType::Warning:
				return "WARNING";
			case RiftExceptionType::Info:
				return "INFO";
			}

			return "N/A";
		}
	};

}
