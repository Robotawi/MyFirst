#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <vector>

using namespace cv;
//Canny and essentials
	cv::Mat gray_image_1;
	cv::Mat gray_image_2;
	cv::Mat src, src_gray;
	cv::Mat dst, detected_edges;
	cv::Mat matEdge;
	//
	cv::Mat edgeFrame;
	cv::Mat grayImage;
	cv::Mat blurFrame;
	cv::Mat edgeImage;
	cv::Mat outputFrame;
	cv::Mat element;
	int dilation_size = 2;
	//
	int edgeThresh = 1;
	int lowThreshold;
	int const max_lowThreshold = 100;
	int ratio = 3;
	int kernel_size = 3;
	char* window_name = "Edge Map";

//Harris
	cv::Mat source_image_2;
	//cv::Mat src, src_gray;
	int thresh = 200;
	int max_thresh = 255;

	char* source_window = "Source image";
	char* corners_window = "Corners detected";
// function
void cornerHarris_demo( int, void* )
{

  cv::Mat dst, dst_norm, dst_norm_scaled;
  dst = cv::Mat::zeros( source_image_2.size(), CV_32FC1 );

  /// Detector parameters
  int blockSize = 2;
  int apertureSize = 3;
  double k = 0.04;

  /// Detecting corners
  cornerHarris( gray_image_2, dst, blockSize, apertureSize, k, cv::BORDER_DEFAULT );

  /// Normalizing
  normalize( dst, dst_norm, 0, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat() );
  convertScaleAbs( dst_norm, dst_norm_scaled );

  /// Drawing a circle around corners
  for( int j = 0; j < dst_norm.rows ; j++ )
     { for( int i = 0; i < dst_norm.cols; i++ )
          {
            if( (int) dst_norm.at<float>(j,i) > thresh )
              {
               circle( dst_norm_scaled, cv::Point( i, j ), 5,  cv::Scalar(0), 2, 8, 0 );
              }
          }
     }
  /// Showing the result
  //cv::namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
  cv::imshow( "view_2", dst_norm_scaled );
}
  
void imageCallback_1(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
    cv::cvtColor( cv_bridge::toCvShare(msg, "bgr8")->image, gray_image_1, CV_BGR2GRAY );
    //cv::imshow("view_1", cv_bridge::toCvShare(msg, "bgr8")->image);
    //cv::blur( gray_image_1, detected_edges, cv::Size(3,3) );
    cv::bilateralFilter(gray_image_1, blurFrame, 9,80, 80);
	//cv::Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
	cv::Canny(blurFrame, edgeImage,100, 500,5);
	//cv::Canny(blurFrame, edgeImage,100, 110,5);
	//cv::Canny(blurFrame, edgeImage,100, 110,5);

    cv::bilateralFilter(edgeImage, blurFrame, 21 , 80, 80);
	//cv::bilateralFilter(matEdge, edgeImage,21, 100, 150);
	
	//morphology transformation
    Size kernalSize (5,5);
	Mat element = getStructuringElement (MORPH_RECT, kernalSize, Point(1,1)  );
	morphologyEx( edgeImage, edgeImage, MORPH_CLOSE, element );
	cv::imshow("view_1", edgeImage);
	/*
	//getting the contours
	vector<vector<Point> > contours;
	findContours(edgeImage.clone(), contours, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

	// approximating the curves
	vector<Point> approx;
	//epsilon = 0.1 * arcLength(contours[0], true);
	approxPolyDP(Mat(contours[0]),approx, 5,true );
	drawContours(gray_image_1, approx, -1, (0, 255, 0), 3);
	cv::imshow("view_1", gray_image_1);
	*/
	
	// Draw contours
/*	Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
	for( int i = 0; i< contours.size(); i++ )
		{
			Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
			drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
		}
*/
  // Show in a window
  
//	for(int i = 0; i < contours.size(); i++)
//	{
//		approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(countours[i]), true) * 0.01, true);
//		
		
		////vector<vector<Point> > contours;
    ////findContours(edgeImage, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
    
	//element = getStructuringElement( cv::MORPH_ELLIPSE, cv::Size( 2*dilation_size + 1, 2*dilation_size+1 ), cv::Point( dilation_size, dilation_size ) );
	//dilate( edgeImage, outputFrame, element );
	
	//cv::imshow("view_1", edgeImage);
	/*
	cv::Mat matContour(edgeImage.size(), CV_8UC1);

    for (size_t k = 0; k < contours.size(); ++k)
    {
        const vector<Point>& contour = contours[k];
        for (size_t k2 = 0; k2 < contour.size(); ++k2)
        {
            const Point& p = contour[k2];
            matContour.at<uint8_t>(p) = 255;
        }
    }
	*/
    //cv::imshow("view_1", edgeImage);

	//From here we have the edge image and want the polygon
	//Not this way
	
	
	//epsilon = 0.1*cv::arcLength(cnt,True)
	//approx = cv::approxPolyDP(cnt,epsilon,True)
	
	
	//cv::imshow("view_1", outputFrame);
	//cv::imshow("view_1", detected_edges);
    //cv::imshow("view2", gray_image_1);
    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}

void imageCallback_2(const sensor_msgs::ImageConstPtr& msg)
{
  try
  {
	source_image_2 = cv_bridge::toCvShare(msg, "bgr8")->image; //the source 2
    cv::cvtColor( cv_bridge::toCvShare(msg, "bgr8")->image, gray_image_2, CV_BGR2GRAY );
    cv::imshow("view_2", cv_bridge::toCvShare(msg, "bgr8")->image);
    //cv::imshow("view_2", gray_image_2); this show the gray scaleimage
    //cornerHarris_demo( 0, 0 );

    cv::waitKey(30);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
  }
}
  

int main(int argc, char **argv)
{
  ros::init(argc, argv, "image_listener");
  ros::NodeHandle nh;

  cv::namedWindow("view_1");
  cv::namedWindow("view_2");
  cv::startWindowThread();
  image_transport::ImageTransport it(nh);
  image_transport::Subscriber sub_1 = it.subscribe("barrett/right/image_raw", 1, imageCallback_1);
  image_transport::Subscriber sub_2 = it.subscribe("barrett/left/image_raw", 1, imageCallback_2);
  ros::spin();
  cv::destroyWindow("view");
}
