#include <iostream>
#include <filesystem>
#include "spdlog/spdlog.h"
#include <exception>
#include "spdlog/sinks/basic_file_sink.h"
#include <cstdlib>

namespace fs = std::filesystem;

fs::path get_root_path()
{
#ifdef _WIN32
  char *user_profile = std::getenv("USERPROFILE");
  if (user_profile)
  {
    return fs::path(user_profile);
  }
  else
  {
    throw std::runtime_error("Unable to locate USERPROFILE environment variable.");
  }
#elif __linux__
  char *home_profile = std::getenv("HOME");
  if (home_profile)
  {
    return fs::path(home_profile);
  }
  else
  {
    throw std::runtime_error("Unable to locate HOME environment variable.");
  }
#else
  throw std::runtime_error("Unsupported platform.");
#endif
}

void move_file(std::shared_ptr<spdlog::logger> logger)
{
  auto DOWNLOADS_PATH = get_root_path() / "Downloads";
  auto DOCUMENTS_PATH = get_root_path() / "Documents";

  if (!fs::exists(DOWNLOADS_PATH))
  {
    logger->error("Downloads path does not exist: {}", DOWNLOADS_PATH.string());
    return;
  }

  if (!fs::exists(DOCUMENTS_PATH))
  {
    logger->error("Documents path does not exist: {}", DOCUMENTS_PATH.string());
    return;
  }

  // TODO: Log if no pdf file
  for (auto const &file : fs::directory_iterator(DOWNLOADS_PATH))
  {
    try
    {
      if (file.path().extension() == ".pdf")
      {
        const auto copy_options = fs::copy_options::overwrite_existing | fs::copy_options::recursive;
        fs::copy(file.path(), DOCUMENTS_PATH / file.path().filename(), copy_options);
        fs::remove(file.path());
        logger->info("Moved file: {} to {}", file.path().filename().string(), DOCUMENTS_PATH.string());
      }
    }
    catch (const std::exception &e)
    {
      logger->error("Failed to move file {}: {}", file.path().filename().string(), e.what());
    }
  }
}

int main()
{
  try
  {
    auto logger = spdlog::basic_logger_mt("logger", "../logs/logs.txt");
    spdlog::set_level(spdlog::level::info);
    move_file(logger);
  }
  catch (const spdlog::spdlog_ex &ex)
  {
    std::cout << "Log init failed: " << ex.what() << std::endl;
  }
  catch (const std::exception &e)
  {
    spdlog::error("Unhandled exception : {}", e.what());
    return 1;
  }

  return 0;
}
