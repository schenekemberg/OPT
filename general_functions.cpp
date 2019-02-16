#include "general_functions.h"

/**
 * @brief get_int_random_between
 * @param xlower
 * @param xupper
 * @return Return a random integer between xlower and xupper,
 * return -1 = invalid data
 */
int get_int_random_between(int xlower, int xupper)
{

    int temp =-1;
    if(xlower <= xupper)
    {
        temp = rand() % (xupper - xlower + 1) + xlower;
    }
    return temp;
}
