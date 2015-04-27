#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/conversions.h>
#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>

typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;

PointCloud::Ptr cloud;
pcl::visualization::CloudViewer viewer("f33");
pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
pcl::PCLPointCloud2Ptr filter_copy;
pcl::PCLPointCloud2Ptr cloud_filtered;

void callback(const PointCloud::ConstPtr& msg)
{
    printf ("Cloud: width = %d, height = %d\n", msg->width, msg->height);

    // Create the filtering object
    pcl::toPCLPointCloud2(*msg, *filter_copy);

    sor.setInputCloud (filter_copy);
    sor.setLeafSize (0.01f, 0.01f, 0.01f);
    sor.filter (*cloud_filtered);

    pcl::fromPCLPointCloud2(*cloud_filtered, *cloud);

    viewer.showCloud(cloud);

}


int main (int argc, char** argv)
{

    ros::init(argc, argv, "tuto_node_rec");

    ros::NodeHandle node;

    ros::Subscriber sub = node.subscribe<pcl::PointCloud<pcl::PointXYZ> >("full_pc", 1, callback);

    ros::Publisher publisher = node.advertise<pcl::PointCloud<pcl::PointXYZ> >("filtered_pc", 2);

    ros::Rate loop_rate(30);

    cloud.reset(new PointCloud);

    filter_copy.reset(new pcl::PCLPointCloud2);
    cloud_filtered.reset(new pcl::PCLPointCloud2);




    while(!viewer.wasStopped() & ros::ok())
    {

        publisher.publish(cloud_filtered);

        ros::spinOnce();

        loop_rate.sleep();

    }


    return (0);
}
