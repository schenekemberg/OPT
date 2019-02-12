#include "packgrasp.h"
#include <exception>
PackGRASP::PackGRASP()
{

}

void PackGRASP::optimize()
{


    if(n_box_type != 0)
    {
        init_parameters();
        //Optimization routines//
        //
        //
        //

    }else
    {
        throw INVALID_DATA;
    }

}

/**
 * @brief PackGRASP::init_parameters
 * Initialize all pre-processed parameters
 */
void PackGRASP::init_parameters()
{
    //vv_box_index_orientation = std::vector<std::vector<int>>(6,std::vector<int>(3));
    vv_box_index_orientation = std::vector<std::vector<int>>
    {
        {0,1,2},
        {0,2,1},
        {1,2,0},
        {1,0,2},
        {2,0,1},
        {2,1,0},
    };
}

