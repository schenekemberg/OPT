#include "packgrasp.h"
#include <exception>

PackGRASP::PackGRASP()
{
    init_parameters();
}

void PackGRASP::optimize()
{
    initialize_states();
    pack();
}

/**
 * @brief PackGRASP::init_parameters
 * Initialize all pre-processed parameters
 */
void PackGRASP::init_parameters()
{
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

/**
 * @brief PackGRASP::initialize_states
 * Set the initial state of the solution from
 * the initial parameters
 */
void PackGRASP::initialize_states()
{

    State initial_state;
    initial_state.box_type = 0;
    initial_state.orientation = 0;
    initial_state.num_box_col_l = 0;
    initial_state.num_box_col_w = 0;
    initial_state.num_box_h = 0;
    initial_state.is_occupied = false;

    Space container_space(0.0,0.0,0.0,container_l,container_w,container_h);
    initial_state.s_unused_space.push(container_space);
    initial_state.v_rejected_space = std::vector<Space>();
    initial_state.v_remaining_boxes = this->v_box_b;
    initial_state.pv_rejected_space = &initial_state.v_rejected_space;

    best_sol.l_sequence.push_back(initial_state);
    best_sol.occupied_vol = 0.0;
    for(size_t i =0; i < this->v_box_b.size(); i++)
    {
      best_sol.total_unused_box += v_box_b[i];
    }


}

void PackGRASP::pack(int xn_improvement)
{
    int current_improment = 0;
    Solution current_sol;

    while(current_improment < xn_improvement)
    {

        current_sol = best_sol;
        //sorteio
        build(current_sol);
        if(current_sol.occupied_vol > best_sol.occupied_vol)
        {
            best_sol = current_sol;
        }
        current_improment++;
    }

}

void PackGRASP::build(PackGRASP::Solution &xsol)
{


    xsol.occupied_vol = get_sol_occupied_vol(xsol);
}

double PackGRASP::get_sol_occupied_vol(PackGRASP::Solution &xsol)
{

}

/**
 * @brief PackGRASP::select_random_sequence
 * @param xsol
 * Get a solution and selects RANDOMLY one element of the
 * l_sequence, erasing all the elements from the randomly selected
 * to the end of the list,  this should also updates the other
 * variables of the sequence
 */
void PackGRASP::select_random_sequence(PackGRASP::Solution &xsol)
{

}

