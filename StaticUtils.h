#pragma once

#include <vector>
#include <string>

// Forward declarations
class Game;

class StaticUtils
{
private:
	StaticUtils() = delete;
	~StaticUtils() = delete;

public:
	static std::vector<std::string> GetFilesInDirectory(const std::string& subdirectory, const std::string fileExtension);

};

