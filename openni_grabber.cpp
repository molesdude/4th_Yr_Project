#include <iostream>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//edit R.Moles
//#include <pcl/io/openni_grabber.h>
#include <pcl/io/openni2_grabber.h>
//edit R.Moles

#include <pcl/common/time.h>

// for viewer
#include <pcl/visualization/cloud_viewer.h>

// for snapshot
#include <pcl/io/pcd_io.h>
static bool once = 1;

class SimpleOpenNIProcessor
{
public:
    //for viewer
    pcl::visualization::CloudViewer viewer;
    SimpleOpenNIProcessor() : viewer("PCL OpenNI Viewer") {}
    //

  void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
  {
      // for viewer
      if (!viewer.wasStopped())
      {
          viewer.showCloud(cloud);
          if (once == 1)
          {
              pcl::io::savePCDFile("snap_pcd.pcd", *cloud);
              once = 0;
          }
      }
      //
    static unsigned count = 0;
    static double last = pcl::getTime ();
    if (++count == 30)
    {
        double now = pcl::getTime();
        std::cout << "distance of center pixel :" << cloud->points[(cloud->width >> 1) * (cloud->height + 1)].z << " mm. Average framerate: " << double(count) / double(now - last) << " Hz" << std::endl;
        count = 0;
        last = now;
    }
  }
  
  void run()
  {
    // create a new grabber for OpenNI devices
      // R.Moles suggestion from https://github.com/PointCloudLibrary/pcl/issues/3290
    //pcl::Grabber* interface = new pcl::OpenNIGrabber();
      pcl::Grabber* interface = new pcl::io::OpenNI2Grabber();
      // R.Moles

    // make callback function from member function
    boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =
      boost::bind (&SimpleOpenNIProcessor::cloud_cb_, this, _1);

    // connect callback function for desired signal. In this case its a point cloud with color values
    boost::signals2::connection c = interface->registerCallback (f);

    // start receiving point clouds
    interface->start ();

    // wait until user quits program with Ctrl-C, but no busy-waiting -> sleep (1);
    while (!viewer.wasStopped()) // edited for viewer previously (true)
      boost::this_thread::sleep (boost::posix_time::seconds (1));

    // stop the grabber
    interface->stop ();
  }
};

int main ()
{
  SimpleOpenNIProcessor v;
  v.run();
  return (0);
}
