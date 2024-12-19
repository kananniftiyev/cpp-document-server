#include <iostream>
#include <filesystem>
#include "spdlog/spdlog.h"
#include <exception>

namespace fs = std::filesystem;

// TODO: Auto finding of folders
const fs::path DOWNLOADS_PATH{"/home/kananniftiyev/Downloads"};
const fs::path DOCUMENTS_PATH{"/home/kananniftiyev/Documents"};

void move_file()
{
  if (!fs::exists(DOWNLOADS_PATH))
  {
    spdlog::error("Downloads path does not exist: {}", DOWNLOADS_PATH.string());
    return;
  }

  if (!fs::exists(DOCUMENTS_PATH))
  {
    spdlog::error("Documents path does not exist: {}", DOCUMENTS_PATH.string());
    return;
  }

  for (auto file : fs::directory_iterator(DOWNLOADS_PATH))
  {
    try
    {
      if (file.path().extension() == ".pdf")
      {
        fs::rename(file.path(), DOCUMENTS_PATH / file.path().filename());
        spdlog::info("Moved file: {} to {}", file.path().filename().string(), DOCUMENTS_PATH.string());
      }
    }
    catch (const std::exception &e)
    {
      spdlog::error("Failed to move file {}: {}", file.path().filename().string(), e.what());
    }
  }
}

int main()
{
  try
  {
    move_file();
  }
  catch (const std::exception &e)
  {
    spdlog::error("Unhandled exception : {}", e.what());
    return 1;
  }

  return 0;
}
