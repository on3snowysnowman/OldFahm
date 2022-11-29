#pragma once 

#include <fstream>
#include <iostream>

#include "nlohmann/json.hpp"
#include "Debug.h"

static std::fstream jloader_file_stream;

/**
 * @brief Handles loading and dumping to json files
 * 
 */
struct Jloader
{

    static nlohmann::json get(const char* path)
    {
        if(!Debug::file_exists(path))
        {
            Debug::log("[FAIL] Jloader.get -> Failed to open file: ", 
                false, true);
            Debug::log(path, true, false);
            Debug::log("[OUT] Exiting...");
            exit(0);
        }

        nlohmann::json json_obj;

        jloader_file_stream.open(path, std::ios::in);

        if(jloader_file_stream.is_open())
        {
            jloader_file_stream >> json_obj;
            jloader_file_stream.close();
        }
        jloader_file_stream.clear();

        return json_obj;
    }

    static void dump(const char* path, nlohmann::json& json_obj)
    {
        if(!Debug::file_exists(path))
        {
            Debug::log("[FAIL] Jloader.dump -> Failed to open file: ", 
                false, true);
            Debug::log(path, true, false);
            Debug::log("[OUT] Exiting...");
            exit(0);
        }

        jloader_file_stream.open(path, std::ios::out);

        if(jloader_file_stream.is_open())
        {
            jloader_file_stream << json_obj.dump(4);
            jloader_file_stream.close();
        }
        jloader_file_stream.clear();
    }
    
    static void clear(const char* path)
    {
        if(!Debug::file_exists(path))
        {
            Debug::log("[FAIL] Jloader.clear -> Failed to open file: ", 
                false, true);
            Debug::log(path, true, false);
            Debug::log("[OUT] Exiting...");
            exit(0);
        }

        jloader_file_stream.open(path, std::ios::out);
        
        if(jloader_file_stream.is_open())
        {
            nlohmann::json json_obj;

            json_obj = nlohmann::json::object({});

            jloader_file_stream << json_obj.dump(4);

            jloader_file_stream.close();
        }

        jloader_file_stream.clear();
    }
};
