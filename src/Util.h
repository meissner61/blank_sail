#pragma once

#include <filesystem>
#include <string>
#include <random>


//    std::string raw_string = R"(Line 1\nLine 2)"; raw string literals \n is treated as a string

namespace sail
{
namespace Util
{

    inline std::string root_path = "NONE";
    inline std::filesystem::path working_directory;
    inline const std::string engine_name = "sail_blank";

    //  You can either supply a root directory(TODO), or the system will attempt to backtrack untill it finds it or fails
    inline void InitWorkingDirectory()
    {
        working_directory = std::filesystem::current_path();
        root_path = working_directory.u8string();
    }

    // inline float GetRandomF()
    // {
    //     return;
    // }

    inline void DisplayStartingDirectory()
    {
        std::cout << "Starting search: " << root_path << std::endl;
    }

    inline std::string GetDirectory()          //NOTE: Get Woring Directory, Not the location of the exe, rather where the exe was started from.
    {
        working_directory = std::filesystem::current_path();
        std::string path = working_directory.u8string();

        return path;
    }

    inline void DisaplyProjectRootPath()
    {
        std::cout <<"Root Path Found: " << root_path << std::endl;
    }

    inline std::string ConvertDirectoryToString(std::filesystem::path& directory)
    {
        std::string path = directory.u8string();

        return path;
    }



    inline std::string StemPath(std::filesystem::path path); // C:/dev/sail == sail
    inline std::string StemPath(std::string path);

    inline std::string StripFileNameExtension(std::string fileName)
    {
        std::filesystem::path path(fileName);
        fileName = path.stem().u8string();
        return fileName;
    }


// Warning: This assumes that you are nested somewhere inside the root path.
    inline void FindRootEnginePath() 
    {
        InitWorkingDirectory();
        DisplayStartingDirectory();
        std::string dirName = StripFileNameExtension(root_path);
        while(dirName != engine_name)
        {
            working_directory = working_directory.parent_path();
            root_path = ConvertDirectoryToString(working_directory);
            dirName = StripFileNameExtension(root_path);

            //TODO: Need to add a max depth for search to not be infinite.
        }
    }


}
}