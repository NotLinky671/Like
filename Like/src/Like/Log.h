#pragma once

#include "lkpch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Like {
	class LIKE_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define LK_CORE_TRACE(...) ::Like::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LK_CORE_INFO(...) ::Like::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LK_CORE_WARN(...) ::Like::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LK_CORE_ERROR(...) ::Like::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LK_CORE_FATAL(...) ::Like::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define LK_TRACE(...) ::Like::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LK_INFO(...) ::Like::Log::GetClientLogger()->info(__VA_ARGS__)
#define LK_WARN(...) ::Like::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LK_ERROR(...) ::Like::Log::GetClientLogger()->error(__VA_ARGS__)
#define LK_FATAL(...) ::Like::Log::GetClientLogger()->fatal(__VA_ARGS__)