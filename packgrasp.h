#ifndef PACKGRASP_H
#define PACKGRASP_H
#include <vector>
#include <stack>
#include <list>

#include "general_functions.h"
#include "optobject.h"

class PackGRASP:public OptObject
{
public:


    /**
     * @brief The OutputSolution struct
     * This solution is a "pre" parse for the json output.
     * For each state in the solution sequence, the stacks of boxes should
     * be extracted into individual boxes (orientations), in order for
     * the UI to be able to draw them
     * vv_out_packed_boxes    : [[ID_state,ID_Box,x,y,z,l,w,h],[...]}
     * vv_out_unpacked_boxes  : [[ID_box,total_unpacked_box],[...]]
     * vv_out_packed_states   : [[ID_state,ID_Box,x,y,z,l,w,h],[...]]
     */
    struct OutputSolutionGRASP
    {
        std::vector<std::vector<std::string>> vv_out_packed_boxes;
        std::vector<std::vector<std::string>> vv_out_packed_states;
        std::vector<std::vector<std::string>> vv_out_unpacked_boxes;
        std::string occupied_vol;
        std::string run_time;
        std::string status;
    };


    PackGRASP();
    ~PackGRASP(){}
    void optimize();
    OutputSolutionGRASP get_pre_parse_solution();

    //Initial Parameters
    std::vector<std::vector<double>> vv_box_lwh;
    std::vector<int> v_box_b;
    std::vector<std::string> v_box_ID;
    std::vector<std::vector<bool>> vv_box_allowed_orientation;
    double container_l = 0;
    double container_w = 0;
    double container_h = 0;
    int n_box_type = 0;
    double time_limit = 2;


    enum en_exceptions
    {
        INVALID_DATA,
    };

private:

    /**
     * @brief The Space struct
     * Structure that holds space information,
     * (x,y,z): Coordinates of the front bottom left corner
     * (l,w,h): space dimensions, length width and height
     */
    struct Space
    {
      //Constructio to initialize the values
      Space(double xx,double xy,double xz,double xl, double xw,double xh)
      {
           x = xx;
           y = xy;
           z = xz;
           l = xl;
           w = xw;
           h = xh;
      }
      double x;
      double y;
      double z;
      double l;
      double w;
      double h;
    };

    /**
     * @brief The State struct
     * Struct that controls all the information needed to recosntruct a pack at
     * the improvement phase. A state is composed of two parts, the first one
     * is "parameters", values that when, in that state, are not update, they are
     * updated on the creation of a new state. The second are variables that, using
     * the parameters are changed in the actual state. In the improvement phase, only
     * the "states variables" must be reinitialized.
     * is_occupied : If there were boxes placed in this state
     */
    struct State
    {
        //state parameters
        std::stack<Space> s_unused_space;
        std::vector<Space> v_rejected_space;
        std::vector<int> v_remaining_boxes;

        //state variables
        int box_type;
        int orientation;
        int num_box_col_l;
        int num_box_col_w;
        int num_box_h;
        std::vector<Space>* pv_rejected_space;
        bool is_occupied;

    };

    struct Solution
    {
        std::list<State> l_sequence;
        double occupied_vol;
        int total_unused_box; //flag that counts total boxes remaining to be packed (each state updates)

    };



    //Functions/ Routines
    void init_parameters();
    void initialize_states();
    void pack(int xn_improvement);
    void build(Solution &xsol);
    double get_sol_occupied_vol(Solution &xsol);
    void select_random_sequence(Solution &xsol);
    void create_new_state(Solution &xsol);
    void update_state_variables(Solution &xsol);


    //Data structures
    std::vector<std::vector<int>> vv_box_index_orientation;
    Solution best_sol;

};

#endif // PACKGRASP_H
