// Project2Task2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

    Mat image = imread("C:/Users/srika/Downloads/olympus/olympus/pic.0164.jpg");
    
    int hsize = 8;
    cv::Mat hist2d;
    int dim[3] = { hsize, hsize, hsize };
    //create 2d histogram
    hist2d = cv::Mat::zeros(3, dim, CV_32S);
    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            int y = image.at<Vec3b>(i, j)[1];//green
            int x = image.at<Vec3b>(i, j)[2]; //red
            int z = image.at<Vec3b>(i, j)[0];
            x = x / 32;
            y = y / 32;
            z = z / 32;
            hist2d.at<signed int>(x, y, z) = hist2d.at<signed int>(x, y, z) + 1;
        }
    }
    float sum = image.rows * image.cols;

    vector<float> v;
    //Normalize histogram
    for (int i = 0; i < hsize; i++) {
        for (int j = 0; j < hsize; j++) {
            for (int k = 0; k < hsize; k++) {
                float value = hist2d.at<signed int>(i, j, k) / sum;
                v.push_back(value);
            }
        }
    }
    int n = 4;
    Mat result_images[4];
    float result_ssd[4];
    int k = 0;
    int i = 1107;
    while (i > 0) {
        if (i == 420) { i = 419; }
        if (i == 164) { i = 163; }
        string path = "C:/Users/srika/Downloads/olympus/olympus/";
        string tmp = "";
        std::string no = std::to_string(i);
        if (no.length() == 1) { tmp = "000" + no; }
        else if (no.length() == 2) { tmp = "00" + no; }
        else if (no.length() == 3) { tmp = "0" + no; }
        else { tmp = no; }
        path = path + "pic." + tmp + ".jpg";
        Mat image1 = imread(path);
        int hsize = 8;
        cv::Mat hist2d;
        int dim[3] = { hsize, hsize, hsize };
        //create 2d histogram
        hist2d = cv::Mat::zeros(3, dim, CV_32S);
        for (int i = 0; i < image1.rows; i++) {
            for (int j = 0; j < image1.cols; j++) {
                int y = image1.at<Vec3b>(i, j)[1];//green
                int x = image1.at<Vec3b>(i, j)[2]; //red
                int z = image1.at<Vec3b>(i, j)[0];
                x = x / 32;
                y = y / 32;
                z = z / 32;
                hist2d.at<signed int>(x, y, z) = hist2d.at<signed int>(x, y, z) + 1;
            }
        }
        float sum = image1.rows * image1.cols;
        vector<float> v1;
        //Normalize histogram
        for (int i = 0; i < hsize; i++) {
            for (int j = 0; j < hsize; j++) {
                for (int k = 0; k < hsize; k++) {
                    float value = hist2d.at<signed int>(i, j, k) / sum;
                    v1.push_back(value);
                }
            }
        }
        float ssd = 0;
        for (int i = 0; i < v.size(); i++) {
            ssd = ssd + std::min(v[i], v1[i]);
        }
        if (k < n) {
            result_images[k] = image1;
            result_ssd[k] = ssd;
            k++;
        }
        else {
            int index = -1;
            for (int i = 0; i < n; i++) {
                if (result_ssd[i] < ssd) {
                    if (index == -1) {
                        index = i;
                    }
                    else if (result_ssd[i] < result_ssd[index]) {
                        index = i;
                    }
                }
            }
            if (index != -1) {
                result_images[index] = image1;
                result_ssd[index] = ssd;
            }
        }
        i--;
    }
    for (int i = 0; i < n; i++) {
        std::string no1 = std::to_string(i);
        string c = "task2result" + no1 + ".jpg";
        imwrite(c, result_images[i]);
        imshow("Result" + to_string(i), result_images[i]);
    }
    
    waitKey(0);
    return 0;
}