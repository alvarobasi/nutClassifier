#pragma once

#include <QtWidgets>
#include "math.h"
#include <opencv2/core.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/highgui.hpp>
#include "ui_CameraApp.h"
#include "BlobResult.h"
#include <cmath>

#define _USE_MATH_DEFINES
using namespace cv;
using namespace cv::ml;

class CameraApp : public QMainWindow
{
	Q_OBJECT

public:
	CameraApp(QWidget *parent = Q_NULLPTR);
	~CameraApp();
private:
	Ui::CameraAppClass ui;
	cv::VideoCapture *cap;

	bool capturing;

	std::vector<cv::Rect> threshold(cv::Mat img, cv::Mat1f &feature_mat);
	void extractLables(cv::Mat1f &feature_mat, cv::Mat *p);
	cv::Mat1f extractFeatures(cv::Mat img_roi, cv::Mat mask_roi, int num_hist_elements);
	double entropy(cv::Mat img_roi, cv::Mat mask_roi);
	void writeMatToFile(cv::Mat& m, const char* filename, bool cond);
	cv::Mat FiletoMat(const char* filename);

	private slots:

	void videoCapture();
	void imageCapture();
	void startStopCapture(bool start);
	void neuralNetworkSetting();
};
