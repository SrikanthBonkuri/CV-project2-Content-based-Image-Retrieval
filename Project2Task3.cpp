// Project2Task3.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;
// Driver code
int main(int argc, char** argv)
{
    
    Mat image = imread("C:/Users/srika/Downloads/olympus/olympus/pic.0274.jpg");
   
    int hsize = 8;
    cv::Mat hist3d;
    cv::Mat hist3d1;
    int dim3[3] = { hsize, hsize, hsize };
    //create 3d histogram
    hist3d = cv::Mat::zeros(3, dim3, CV_32S);
    hist3d1 = cv::Mat::zeros(3, dim3, CV_32S);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            int z = image.at<Vec3b>(i, j)[0];//blue
            int y = image.at<Vec3b>(i, j)[1];//green
            int x = image.at<Vec3b>(i, j)[2];//red
            x = x / 32;
            y = y / 32;
            z = z / 32;
            if (i < image.rows / 2) {
                hist3d.at<signed int>(x, y, z) = hist3d.at<signed int>(x, y, z) + 1;
            }
            else {
                hist3d1.at<signed int>(x, y, z) = hist3d1.at<signed int>(x, y, z) + 1;
            }
        }
    }
    float hist1sum = 0;
    float hist2sum = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                hist1sum = hist1sum + hist3d.at<signed int>(i, j, k);
            }
        }
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                hist2sum = hist2sum + hist3d1.at<signed int>(i, j, k);
            }
        }
    }
    vector<float> v;
    vector<float> v1;
    //Normalize histogram
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                float value = hist3d.at<signed int>(i, j, k) / hist1sum;

                v.push_back(value);
            }
        }
        //printf("\n");
    }
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                float value = hist3d1.at<signed int>(i, j, k) / hist2sum;
                v1.push_back(value);
            }
        }
    }
    int n = 5;
    Mat result_images[5];
    float result_ssd[5];
    int k = 0;
    int i = 1107;
    while (i > 0) {
        if (i == 420) { i = 419; }
        //if (i == 274) { i = 273; }
        string path = "C:/Users/srika/Downloads/olympus/olympus/";
        string tmp = "";
        std::string no = std::to_string(i);
        if (no.length() == 1) { tmp = "000" + no; }
        else if (no.length() == 2) { tmp = "00" + no; }
        else if (no.length() == 3) { tmp = "0" + no; }
        else { tmp = no; }
        path = path + "pic." + tmp + ".jpg";
        Mat image1 = imread(path);
        cv::Mat tmphist3d;
        cv::Mat tmphist3d1;
        tmphist3d = cv::Mat::zeros(3, dim3, CV_32S);
        tmphist3d1 = cv::Mat::zeros(3, dim3, CV_32S);
        for (int i = 0; i < image1.rows; i++) {
            for (int j = 0; j < image1.cols; j++) {
                int z = image1.at<Vec3b>(i, j)[0];//blue
                int y = image1.at<Vec3b>(i, j)[1];//green
                int x = image1.at<Vec3b>(i, j)[2];//red
                x = x / 32;
                y = y / 32;
                z = z / 32;
                if (i < image1.rows / 2) {
                    tmphist3d.at<signed int>(x, y, z) = tmphist3d.at<signed
                        int>(x, y, z) + 1;
                }
                else {
                    tmphist3d1.at<signed int>(x, y, z) = tmphist3d1.at<signed
                        int>(x, y, z) + 1;
                }
            }
        }
        float tmphist1sum = 0;
        float tmphist2sum = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    tmphist1sum = tmphist1sum + tmphist3d.at<signed int>(i, j, k);
                }
            }
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    tmphist2sum = tmphist2sum + tmphist3d1.at<signed int>(i, j, k);
                }
            }
        }
        vector<float> tmpv;
        vector<float> tmpv1;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    float value = tmphist3d.at<signed int>(i, j, k) / tmphist1sum;
                    tmpv.push_back(value);
                }
            }
        }
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int k = 0; k < 8; k++) {
                    float value = tmphist3d1.at<signed int>(i, j, k) / tmphist2sum;
                    tmpv1.push_back(value);
                }
            }
        }
        float diff = 0;
        float diff1 = 0;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] >= tmpv[i]) {
                diff = diff + (v[i] - tmpv[i]);
            }
            else {
                diff = diff + (tmpv[i] - v[i]);
            }
        }
        for (int i = 0; i < v1.size(); i++) {
            if (v1[i] >= tmpv1[i]) {
                diff1 = diff1 + (v1[i] - tmpv1[i]);
            }
            else {
                diff1 = diff1 + (tmpv1[i] - v1[i]);
            }
        }
        float finaldiff = 0.75 * diff + 0.25 * diff1;
        if (k < n) {
            result_images[k] = image1;
            result_ssd[k] = finaldiff;
            k++;
        }
        else {
            int index = -1;
            for (int i = 0; i < n; i++) {
                if (result_ssd[i] > finaldiff) {
                    if (index == -1) {
                        index = i;
                    }
                    else if (result_ssd[i] > result_ssd[index]) {
                        index = i;
                    }
                }
            }
            if (index != -1) {
                result_images[index] = image1;
                result_ssd[index] = finaldiff;
            }
        }
 
        i--;
    }
    for (int i = 0; i < n; i++) {
        std::string no1 = std::to_string(i);
        string c = "task3result" + no1 + ".jpg";
        imwrite(c, result_images[i]);
    }
  
    waitKey(0);
    return 0;
}
