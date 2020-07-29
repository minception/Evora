#pragma once
#include "logger.h"

namespace logging
{
	class logger_factory
	{
	public:
		static std::shared_ptr<logger> get_logger(std::string name);
	};
}

