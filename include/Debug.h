#pragma once

#include <fstream>
#include <SDL2/SDL.h>

static std::fstream debug_file_stream;
static const char* path = "OutputLog.txt";

struct Debug
{

private:

    static void dump(std::string content, bool new_line, bool output_time)
    {
        debug_file_stream.open(path, std::ios::app);

        if(debug_file_stream.is_open())
        {

            if(output_time)
            {
                debug_file_stream << SDL_GetTicks64();
                debug_file_stream << " ms: ";
            }

            debug_file_stream << content;

            if(new_line)
            {
                debug_file_stream << '\n';
            }

            debug_file_stream.close();
        }

        debug_file_stream.clear();
        }

public:

    static bool file_exists(const char* path)
    {

        FILE *fp = fopen(path, "r");
        bool is_exist = false;
        if (fp != NULL)
        {
            is_exist = true;
            fclose(fp); // close the file
        }
        return is_exist;
    }

    static void log(std::string content, bool new_line = true, 
        bool output_time = true)
    {
        dump(content, new_line, output_time);
    }

    static void log(int content, bool new_line = true, 
        bool output_time = true)
    {
        dump(std::to_string(content), new_line, output_time);
    }

    static void log(std::size_t content, bool new_line = true,
        bool output_time = true)
    {
        dump(std::to_string(content), new_line, output_time);
    }

    static void log(char content, bool new_line = true,
        bool output_time = true)
    {
        dump(std::string{content}, new_line, output_time);
    }
    
    static void log(std::pair<int,int> content, bool new_line = true,
        bool output_time = true)
    {
        dump("(", false, output_time);
        dump(std::to_string(content.first), false, false);
        dump(", ", false, false);
        dump(std::to_string(content.second), false, false);
        dump(")", new_line, false);
    }

    static void clear()
    {
        debug_file_stream.open(path, std::ios::out);
        debug_file_stream.close();
        debug_file_stream.clear();
    }
};
