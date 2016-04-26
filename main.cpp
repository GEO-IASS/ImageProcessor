#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main(){
    int imagecount = 10;
    cv::Mat image[imagecount]; //make arrays to store images
    cv::Mat scaledimage[imagecount];

    //load the images, resize them and then delete the original images to free up memory
    for(int i = 0; i<imagecount; i++){
        image[i] = cv::imread(cv::format("images/test%d.png", i+1));
        cv::resize(image[i], scaledimage[i], cv::Size(1000, 1000));
        image[i].release();
    }


    //cut all the images into 10 pieces
    cv::Mat cutimage[imagecount][10];
    for(int x = 0; x<imagecount; x++){
        for (int i =0; i<10; i++){
            cutimage[x][i] = cv::Mat(scaledimage[x], cv::Rect(0, i*100, 1000, 100));
        }
    }


    //combine 10 slices into one image
    cv::Mat combinedimage(1000, 1000, cutimage[0][0].type());
    for(int i =0; i<10; i++){
        cv::Mat slice = combinedimage(cv::Rect(0, i*100, 1000, 100));
        cutimage[i][i].copyTo(slice);
    }

    //create a window, display the images and wait for user input
    cv::namedWindow("test");
    cv::imshow("test", combinedimage);
    cv::waitKey(0);

    return(0);
}
