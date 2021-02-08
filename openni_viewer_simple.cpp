#include <pcl/io/openni2_grabber.h>
#include <pcl/visualization/cloud_viewer.h>
#include <thread>
#include <pcl/common/time.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

int main()
{
    pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGBA>);
    pcl::io::loadPCDFile("snap_pcd.pcd", *cloud);

    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    viewer.showCloud(cloud);
    getchar();
    return 0;
}



// CMAKE LISTS
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(openni_viewer_simple)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (openni_viewer_simple openni_viewer_simple.cpp)
target_link_libraries (openni_viewer_simple ${PCL_LIBRARIES})
