#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std; 
using namespace cv;

/* INTERNAL CAM TEST CODE */
/* REF: https://www.youtube.com/watch?v=HqNJbx0uAv0 */
/*
class cam_test{
  public:
    cam_test()
    {
      VideoCapture cap(0); // OPENT THE VIDEO CAMERO NO. 0

	if(!cap.isOpened()) //if not success, exit program
	{
		cout<<"Cannot open the video cam" << endl;
	}

	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of te video
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Frame size: " << dWidth << " x " << dHeight << endl;

	namedWindow("MyVideo", CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

	while(1)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video
	
		if(!bSuccess) // if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		imshow("My video", frame);

		if (waitKey(30) == 27) // wait for 'esc' key press form 30 ms
		{
			cout << "ESC key pressed by user"<< endl;
			break;
		}
	}
    }

    ~cam_test()
    {
	cvDestroyWindow("Camera_Output"); // Destroy Window
    }
};

int main(int argc, char **argv)
{
  //SetUP ROS.
  ros::init(argc, argv, "opencv_tutorial");
  cam_test cam_object;

  ROS_INFO("Cam Tested!");
}
*/

// flip image

	int main(int argc, char *argv[]) {
	/*	int flip_code=0;
		 String imageName("test_1.png"); // by default
    if( argc > 1)
    {
        imageName = argv[1];
    }
    image = imread( imageName, IMREAD_COLOR );
    
		Mat out_image; // Output image
		if (argc != 4){//Check args. number
			cout << "Usage: <cmd> <flip_code> <file_in> <file_out>\n";
			return -1;
	    } 
	    Mat in_image = imread("test_1.png", CV_LOAD_IMAGE_GRAYSCALE);
	    if (in_image.empty()) { // Check if read
			cout << "Error! Input image cannot be read…\n";
			return -1;
        }
        
        //sscanf(argv[1], "%d", &flip_code); // Read flip code
        //flip(in_image, out_image, flip_code);
        //imwrite(argv[3], out_image); // Write image to file
        namedWindow("win"); // Creates a window
        imshow("win",image); // Shows output image on window
        cout << "Press any key to exit…\n";
        waitKey(); // Wait infinitely for key press return 0;
        */
	}
