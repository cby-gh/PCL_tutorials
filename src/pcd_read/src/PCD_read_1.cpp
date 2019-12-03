#include <ros/ros.h>
// PCL specific includes
#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
ros::Publisher pub;
sensor_msgs::PointCloud2 pcd_data;


int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "pub_a_pcd_data");
  ros::NodeHandle nh;
  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<sensor_msgs::PointCloud2> ("pcd_data", 1);
	
  pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2 ());
  pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2 ());
    ros::Rate loop_rate(50);
  while(ros::ok())
  {
  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("/home/cby/PCL_ws/src/pcd_read/PCD_files/table_scene_lms400.pcd", *cloud); // Remember to download the file first!
  //sensor_msgs::PointCloud2 pcd_data;
  pcl_conversions::fromPCL(*cloud, pcd_data);
  pcd_data.header.frame_id = "odom1";
  pub.publish (pcd_data);
  // Spin
  loop_rate.sleep();
  }
      return 0;
}
