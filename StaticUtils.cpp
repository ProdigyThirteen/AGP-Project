#include "StaticUtils.h"
#include <filesystem>

std::vector<std::string> StaticUtils::GetFilesInDirectory(const std::string& subdirectory, const std::string fileExtension)
{
	std::filesystem::path dirPath = std::filesystem::current_path() / subdirectory;
	std::vector<std::string> files;

	if (std::filesystem::exists(dirPath) && std::filesystem::is_directory(dirPath)) {
		for (const auto& entry : std::filesystem::directory_iterator(dirPath)) {
			if (entry.is_regular_file() && entry.path().extension() == fileExtension) {
				files.push_back(entry.path().filename().string());
			}
		}
	}

	return files;
}