#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/conversions.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>


int main (int argc, char** argv)
{

    ros::init(argc, argv, "tuto_node");

    ros::NodeHandle node;

    ros::Publisher publisher = node.advertise<pcl::PointCloud<pcl::PointXYZ> >("full_pc", 2);

    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());

    ros::Rate loop_rate(30);

    // Fill in the cloud data
    pcl::PCDReader reader;
    // Replace the path below with the path where you saved your file
    reader.read ("table_scene_lms400.pcd", *cloud); // Remember to download the file first!

    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height
              << " data points (" << pcl::getFieldsList (*cloud) << ").";


    pcl::visualization::CloudViewer viewer("ff");

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud2( new pcl::PointCloud<pcl::PointXYZ>());

    pcl::fromPCLPointCloud2(*cloud, *cloud2);

    viewer.showCloud(cloud2);

    cloud2->header.frame_id = "some_frame";

    while(!viewer.wasStopped() & ros::ok())
    {

        publisher.publish(*cloud2);

        ros::spinOnce();

        loop_rate.sleep();

    }


    return (0);
}
