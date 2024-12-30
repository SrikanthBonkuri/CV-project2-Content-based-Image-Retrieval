// Project2Task1.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    
    Mat image = imread("C:/Users/srika/Downloads/olympus/olympus/pic.1016.jpg");
    
    int a[9][9];
    int r = (image.rows/2) - 5;
    int c = (image.cols/2) - 5;
    int i1 = 0, j1 = 0;
    vector<int> v;
    for (int i = r, i1 = 0; i < r + 9; i++, i1++) {
        for (int j = c, j1 = 0; j < c + 9; j++, j1++) {
            int z = image.at<Vec3b>(i, j)[0];//blue
            int y = image.at<Vec3b>(i, j)[1];//green
            int x = image.at<Vec3b>(i, j)[2];//red
            a[i1][j1] = x + y + z;
            v.push_back(z); v.push_back(y); v.push_back(x);
        }
    }
    int n = 4;
    Mat result_images[4];
    long result_ssd[4];
    int k = 0;
    int iz = 1107;
    while (iz > 0) {
        if (iz == 1016) { iz = 1015; }
        if (iz == 420) { iz = 419; }
        string path = "C:/Users/srika/Downloads/olympus/olympus/";
        string tmp = "";
        std::string no = std::to_string(iz);
        if (no.length() == 1) { tmp = "000" + no; }
        else if (no.length() == 2) { tmp = "00" + no; }
        else if (no.length() == 3) { tmp = "0" + no; }
        else { tmp = no; }
        path = path + "pic." + tmp + ".jpg";
        Mat image1 = imread(path);
        int r1 = image1.rows / 2 - 4;
        int c1 = image1.cols / 2 - 4;
        long ssd = 0;
        vector<int> v1;
        for (int p = r; p < r + 9; p++) {
            j1 = 0;
            for (int q = c; q < c + 9; q++) {
                int a = image1.at<Vec3b>(p, q)[0];//blue
                int b = image1.at<Vec3b>(p, q)[1];//green
                int c = image1.at<Vec3b>(p, q)[2];//red
                v1.push_back(a); v1.push_back(b); v1.push_back(c);
            }
        }
        ssd = 0;
        for (int i = 0; i < v.size(); i++) {
            int d = v[i] - v1[i];
            ssd = ssd + (d * d);
        }
        if (k < n) {
            result_images[k] = image1;
            result_ssd[k] = ssd;
            k++;
        }
        else {
            int index = -1;
            for (int i = 0; i < n; i++) {
                if (result_ssd[i] > ssd) {
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
                result_ssd[index] = ssd;
            }
        }
        iz--;
    }

    for (int i = 0; i < n; i++) {
        std::string no1 = std::to_string(i);
        string c = "result" + no1 + ".jpg";
        imwrite(c, result_images[i]);
        imshow("Window" + to_string(i), result_images[i]);
    }
    
    waitKey(0);
    return 0;
}
