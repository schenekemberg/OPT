#include "packgrasp.h"
#include <exception>

PackGRASP::PackGRASP()
{
    init_parameters();
}

void PackGRASP::optimize()
{
    initialize_states();
    pack(10);
}

/**
 * @brief PackGRASP::get_pre_parse_solution
 * @return
 * Return the outputSolutionGRASP, which is a pre-parsed
 * solution that the parser will turn into a json string
 * to output for users
 */
PackGRASP::OutputSolutionGRASP PackGRASP::get_pre_parse_solution()
{

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
        select_random_sequence(current_sol);
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

    while((xsol.total_unused_box > 0) && (xsol.l_sequence.back().s_unused_space.size() > 0))
    {
        //xsol.l_sequence.back().s_unused_space.top().;
        update_state_variables(xsol);
        create_new_state(xsol);
    }

    xsol.occupied_vol = get_sol_occupied_vol(xsol);
}

/**
 * @brief PackGRASP::get_sol_occupied_vol
 * @param xsol
 * @return
 * Calculates the total occupied volume from one solution
 */
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

/**
 * @brief PackGRASP::update_state_variables
 * Update all data in a state, that are "variables",
 *  Uses the last element of the l_sequence, (that
 * are already computed on the update_state_variables), and
 * creates a new state in the list, with the updating the
 * "state parameters"
 */
void PackGRASP::create_new_state(Solution &xsol)
{

}

/**
 * @brief PackGRASP::update_state_variables
 * @param xsol
 * Update the state variables:
 *       int box_type;
 *       int orientation;
 *       int num_box_col_l;
 *       int num_box_col_w;
 *       int num_box_h;
 *       std::vector<Space>* pv_rejected_space;
 *       bool is_occupied;
 */
void PackGRASP::update_state_variables(Solution &xsol)
{


}

