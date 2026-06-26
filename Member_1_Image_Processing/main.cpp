// WavefrontTracker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <fstream>

using namespace cv;
using namespace std;

// Helper function to find centroids in an image
vector<Point2f> getCentroids(Mat image) {
    Mat threshImage;
    threshold(image, threshImage, 100, 255, THRESH_BINARY);

    vector<vector<Point>> contours;
    findContours(threshImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point2f> centroids;
    for (size_t i = 0; i < contours.size(); i++) {
        Moments M = moments(contours[i]);
        if (M.m00 != 0) {
            centroids.push_back(Point2f(M.m10 / M.m00, M.m01 / M.m00));
        }
    }
    return centroids;
}

int main() {
    // 1. Prepare the CSV file for Person 2
    ofstream csvFile("spot_shifts.csv");
    csvFile << "Frame,Spot_ID,Ref_X,Ref_Y,Distorted_X,Distorted_Y,Shift_X,Shift_Y\n";

    // 2. Read the Golden Reference Frame (Update this path!)
    string basePath = "C:/Users/my pc/Documents/bah/dummy_sh_wfs_data/";
    Mat refImage = imread(basePath + "frame_000.bmp", IMREAD_GRAYSCALE);

    if (refImage.empty()) {
        cout << "Could not find reference image!" << endl;
        return -1;
    }

    // Get perfect reference coordinates
    vector<Point2f> refCentroids = getCentroids(refImage);
    cout << "Found " << refCentroids.size() << " reference spots." << endl;

    // 3. Loop through the distorted frames
    for (int frameIdx = 1; frameIdx < 100; frameIdx++) {
        // Format the filename (e.g., frame_001.bmp)
        char filename[100];
        sprintf_s(filename, "frame_%03d.bmp", frameIdx);

        Mat distImage = imread(basePath + filename, IMREAD_GRAYSCALE);
        if (distImage.empty()) continue; // Skip if file is missing

        vector<Point2f> distCentroids = getCentroids(distImage);

        // 4. Calculate the Shifts and save to CSV
        // (Assuming the spots are detected in the same order for this dummy data)
        for (size_t i = 0; i < min(refCentroids.size(), distCentroids.size()); i++) {
            float shiftX = distCentroids[i].x - refCentroids[i].x;
            float shiftY = distCentroids[i].y - refCentroids[i].y;

            csvFile << frameIdx << "," << i << ","
                << refCentroids[i].x << "," << refCentroids[i].y << ","
                << distCentroids[i].x << "," << distCentroids[i].y << ","
                << shiftX << "," << shiftY << "\n";
        }
    }

    csvFile.close();
    cout << "Success! Data saved to spot_shifts.csv" << endl;

    return 0;
}