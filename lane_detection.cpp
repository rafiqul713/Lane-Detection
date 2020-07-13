#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdio>
#include <iostream>
using namespace cv;
using namespace std;


class LaneDetection{
    public:

          double lower_threshold,upper_threshold;
          Mat resulted_image, detected_edge;

          /*Vec4i is a structure for representing a vector with
            4 dimensions with each value is a integer
          */

          Vec4i point;
          vector<Vec4i> lines;

          void set_threshold(int,int);
          void lane_detect(Mat);

};


void LaneDetection::set_threshold(int l,int h){
    lower_threshold=l;
    upper_threshold=h;

}

void LaneDetection::lane_detect(Mat image){

    resulted_image = image.clone();
    //Edge detection with Canny edge detector
    Canny(image,detected_edge,lower_threshold,upper_threshold);
    /*  Hough Line Transform to detect straight line
        Here, parameters are:
        dst: Output of the edge detector
        lines: A vector that will store the parameters (r,\theta) of the detected lines
        rho : The resolution of the parameter r in pixels
        theta: The resolution of the parameter \theta in radians. Here use 1 degree (CV_PI/180)
        threshold: The minimum number of intersections to “detect” a line srn
        stn: Default parameters to zero.
    */
    HoughLinesP(detected_edge, lines, 2, CV_PI/180, 50, 30, 50);
    for(auto i = 0;i<lines.size();i++){
        point = lines[i];
        //A line is drawn on the detected point
        line(resulted_image,Point(point[0],point[1]),Point(point[2],point[3]),Scalar(255,0,0), 1, LINE_8);
    }

    //Show the lane detected image
    imshow("Lane detected ", resulted_image);


}



int main(int argc, char** argv){
  char* image_file = argv[1];
  Mat image, grayscale_image;
  LaneDetection obj;
  image = imread(image_file,1);

  if(image.empty()){
    cout << "Image file does not Exist "<<endl;
    return 9999;
  }

  obj.set_threshold(500,200); //Threshold values are selected based on trial and error method
  obj.lane_detect(image);
  waitKey(1000);
  destroyAllWindows();
}


