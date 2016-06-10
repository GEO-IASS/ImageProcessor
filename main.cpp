#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main(){
    //enter ROI values
    int begin_pixel_y = 2330;
    int begin_pixel_x = 3200;
    int object_height = 30;
    int object_width = 1100;

    cv::Mat image; //container for original image
    cv::Mat cutimage; //container for ROI
    int average_value; //container for the average pixel value


    cv::Mat graph = cv::Mat::zeros(256, object_width, CV_8UC3); //container for the graph and reserving enough memory
    cv::Mat displayimage = cv::Mat::zeros(256+object_height, object_width, CV_8UC3); //container for the display and reserving memory


    image = cv::imread("images/image4.jpg", cv::IMREAD_COLOR); //reading the image and saving it in image container
    cutimage = image(cv::Rect(begin_pixel_x,begin_pixel_y,object_width, object_height)); //cutting the image to the ROI and saving it in cutimage

    //getting the average pixel value per column of the ROI
    for(int i = 0; i<object_width; i++){
        average_value = 0; //resetting average value
        for(int j = 0; j<object_height; j++){
            average_value += (cutimage.at<uchar>(j,i*3) + cutimage.at<uchar>(j,i*3+1) + cutimage.at<uchar>(j,i*3+2))/3; //taking values per color channel, adding up and dividing by 3
        }
        average_value /= object_height/3; //averaging per column
        graph.at<uchar>(255-average_value, i*3) = 255; //making a white line in the graph
        graph.at<uchar>(255-average_value, i*3+1) = 255;
        graph.at<uchar>(255-average_value, i*3+2) = 255;
    }

    cv::Mat ROI; //declaring a ROI for displayimage
    ROI = displayimage(cv::Rect(0,0,object_width,256)); //setting the ROI
    graph.copyTo(ROI); //copying the graph to the ROI
    ROI = displayimage(cv::Rect(0,256,object_width,object_height)); //setting new ROI
    cutimage.copyTo(ROI); //copying the ROI of the original image to the ROI of the display image

    //create a window, display the images and wait for user input
    cv::namedWindow("test");
    cv::imshow("test", displayimage);
    cv::waitKey(0);
    return(0);
}
