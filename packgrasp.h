#ifndef PACKGRASP_H
#define PACKGRASP_H
#include "optobject.h"
#include <vector>
#include <stack>
#include <list>

class PackGRASP:public OptObject
{
public:
    PackGRASP();
    ~PackGRASP(){}
    void optimize();

private:

    /**
     * @brief The Space struct
     * Structure that holds space information,
     * (x,y,z): Coordinates of the front bottom left corner
     * (l,w,h): space dimensions, length width and height
     */
    struct Space
    {
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

    };

    class Solution
    {
        Solution();
        ~Solution();
        std::vector<State> v_sequence;
        std::vector<int> v_index_occupied_state;
        double occupied_vol;
    };

public:
    //Initial Parameters
    std::vector<double> v_box_l;
    std::vector<double> v_box_w;
    std::vector<double> v_box_h;
    std::vector<int> v_box_b;
    std::vector<int> v_box_ID;
    std::vector<std::vector<bool>> vv_box_orientation;



};

#endif // PACKGRASP_H
