#include <can_searcher/can_searcher.h>
#include <move_jinx/move_jinx.h>
#include <move_arm/move_arm.h>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
    ros::init(argc, argv, "process_frame");
    ros::NodeHandle nh;
    CanSearcher Cansearcher(&nh);
    MoveJinx Movejinx(&nh);
    MoveArm Movearm(&nh);
    Eigen:Vector3f centroid;
    bool got_table = false;
    bool got_can = false;

    Movearm.setPrepose();
    Movejinx.move2LT();
    Cansearcher.takeAPic();
    got_table = Cansearcher.searchTable();
    if (got_table)
    {
    	got_can = Cansearcher.searchCan2(centroid);
    }
    else
    {
    	ROS_ERROR("Failed to find the left table.");
	Movejinx.moveBack();
    	return 0;
    }
    if (got_can)
    {
    	ROS_INFO("Got the can on the left table. Picking it up.");
    		Movearm.graspCan(centroid);
		Movearm.moveCan();
		Movearm.dropCan();
		return 0;
    }
    else
    {
    	ROS_INFO("Cannot find a coke can on the left table.");
    	ROS_INFO("Moving to the right table...");
    	Movejinx.moveBack();
	Movejinx.move2RT();
    	Cansearcher.takeAPic();
    	got_table = false;
    	got_table = Cansearcher.searchTable();
    	if (got_table)
    	{
    		got_can = false;
    		got_can = Cansearcher.searchCan2(centroid);
    	}
    	else
    	{
	     	ROS_ERROR("Failed to find the right table.");
		Movejinx.moveBack();
	    	return 0;   		
    	}
    	if(got_can)
    	{
	    	ROS_INFO("Got the can on the right table. Picking it up.");
	    	Movearm.graspCan(centroid);
		Movearm.moveCan();
		Movearm.dropCan();
		Movejinx.moveBack();
		return 0;
    	}
    	else
    	{
    		ROS_INFO("Cannot find a coke can on the right table.");
		Movejinx.moveBack();
    		return 0;
    	}
    }

}


