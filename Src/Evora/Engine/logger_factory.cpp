#include "logger_factory.h"

std::shared_ptr<logging::logger> logging::logger_factory::get_logger(std::string name)
{
	if(name.empty())
	{
		return std::make_shared<logging::empty_logger>();
	}
	if(name == "0")
	{
		return std::make_shared<logging::avg_score_per_round>();
	}
	if(name == "1")
	{
		return std::make_shared<logging::win_percentage>();
	}
	return nullptr;
}
