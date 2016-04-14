/*
The MIT License (MIT)
Copyright (c) 2016 Zhiang Chen

This package is for CWRU EECS376 final project.
It provides the functions to search a coke can on the table.
*/
#ifndef CAN_SEARCHER_H_
#define CAN_SEARCHER_H_

#include <pcl_utils/pcl_utils.h>
#include <ros/ros.h> //generic C++ stuff
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

#include <Eigen/Eigen> //for the Eigen library
#include <Eigen/Dense>
#include <Eigen/Geometry>
#include <Eigen/Eigenvalues>

#include <sensor_msgs/PointCloud2.h> //useful ROS message types
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/TransformStamped.h>


#include <tf/transform_listener.h>  // transform listener headers
#include <tf/transform_broadcaster.h>

#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>  //point-cloud library headers; likely don't need all these
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/ros/conversions.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/extract_indices.h>
#include <pcl_ros/transforms.h>
#include <pcl-1.7/pcl/impl/point_types.hpp>

#define TableHeight 0.5
#define TableTol 0.01
#define TableBottom 0.2
#define TableTop 1
#define TableLeft -1
#define TableRight 1
#define TableRed 23
#define TableGreen 45
#define TableBlue 45
#define ClrTol 50
#define TableLength 1
#define TableWidth 1
#define CanHeight 0.1

class CanSearcher
{
public:
	CanSearcher(ros::NodeHandle* nodehandle);
	void takeAPic();
	bool searchTable();
	bool searchCan(Eigen::Vector3f &centroid);
	
	void publishPoints();
	void setAffine(Eigen::Affine3f af){kinect_wrt_torso_=af;};
	void savePCD();
private:
	ros::NodeHandle nh_;
	PclUtils Pclutils_;
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr tf_downsampled_ptr_;
	Eigen::Affine3f kinect_wrt_torso_;

	bool got_table_;
	Eigen::Vector3f table_centroid_;


	ros::Publisher pubSPKinect_;
	ros::Publisher pubTable_;
	ros::Publisher pubCanTop_;
	sensor_msgs::PointCloud2 kinect_cloud_, table_cloud_, can_top_cloud_;

};


#endif