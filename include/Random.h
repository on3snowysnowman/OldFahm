#pragma once

#include <time.h>   
#include <algorithm>

#include <vector>

struct Random
{
    static void seed_random(int seed = -1){

        if(seed == -1)
        {
            srand(time(NULL));
            return;
        }

        srand(seed);
    }

    /**
     * @brief Returns a random number between the range of min, and max
     * 
     * @param min Minimium number
     * @param max Maximum number
     * @return Random number between min and max
     */
    static int get_random_num(int min, int max){

        return (rand() % (max + 1 - min)) + min;
    }

    // static int get_total_of_largest(int pick, int total, int min, int max)
    // {
    //     std::vector<int> all_nums;
    //     int total_largest = 0;

    //     for(int i = 0; i < total; i++)
    //     {
    //     all_nums.push_back(get_random_num(min, max));
    //     }

    //     std::sort(all_nums.begin(), all_nums.end(), std::greater<int>());

    //     for(int i = 0; i < pick; i++)
    //     {
    //         total_largest += all_nums.at(i);
    //     }

    //     return total_largest;
    // }

    // template<typename T>
    // static T& get_random_vector_element(std::vector<T> choices)
    // {
    //     /*
    //     Takes in a vector and returns a random element from its contents

    //     :param choices: Vector of elements to be chosen from

    //     :return: A random element from the passed vector 
    //     */

    //     int index = get_random_num(0, choices.size() - 1);
    //     return choices.at(index);
    // }
};
