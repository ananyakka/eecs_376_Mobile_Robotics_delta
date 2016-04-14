/*
EECS 476 final project
This header is used with move_jinx.cpp
Written by Ananya, 4/14/16, 14:25
*/

#ifndef MOVEJINX_H_
#define MOVEJINX_H_
#include <ros/ros.h> //generic C++ stuff

// define a class, including a constructor, member variables and member functions
class MoveJinx
{
public:
    MoveJinx(ros::NodeHandle* nodehandle);//"main" will need to instantiate a ROS nodehandle, then pass it to the constructor
    // may choose to define public methods or public variables, if desired
    bool move2LT(); // move to the left table;
    bool moveBack(); // move to the initial position;
    bool move2RT();  // move to the right table;


private:

ros::NodeHandle nh_;

} ;

#endif
