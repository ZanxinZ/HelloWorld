#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

void tezheng(Mat image1, Mat image2);
void hsvreg(int, void*);
void main_1();

char filename[200],key;

int hmin, hmax, smin, smax, vmin, vmax;
int x = 0, t = 1, flag_hn = 0, flag_mf = 0;
int getpicture = 0;

Mat imageget, get_roi, frame,tz_out;
Mat image01, image02, image03, image04, image05, image06,image07;
int main(int argc, char *argv[])
{
	int count = 0;
	VideoCapture  capture(0);
	if (!capture.isOpened())
	{
		cout << "摄像头打开失败！" << endl;
		return -1;
	}
	namedWindow("【视频】", 1);
	namedWindow("【图片】", 1);

	image04 = imread("E:/tupian/购物/特仑苏模板.jpg");
	image05 = imread("E:/tupian/购物/雪花模板.jpg");
	image06 = imread("E:/tupian/购物/乐虎模板.jpg");
	image01 = imread("E:/tupian/购物/爽歪歪模板.jpg");
	image02 = imread("E:/tupian/购物/养乐多模板.jpg");
	image03 = imread("E:/tupian/购物/魔方模板1.jpg");

	//hmin = 160; hmax = 175;
	//smin = 43; smax = 255;
	//vmin = 0; vmax = 255;
	//imageget = imread("E:/tupian/购物/现场图片/5.jpg");
	//tz_out = imageget(Range(50, 400), Range(150, 500));
	//imwrite("E:/tupian/购物/养乐多模板.jpg", tz_out);
	//hsvreg(0,0);
	//waitKey(0);

	while (1)
	{
		key = waitKey(50);
		capture >> frame;
		imshow("【视频】", frame);
		if (key == 27)
			break;     //按ESC键退出程序
		if (key == 32)   //按空格键进行拍照
		{
			t = 1;
			getpicture = 0;
			count++;
			sprintf(filename, "E:/tupian/购物/现场图片/1%d.jpg", count);
			imwrite(filename, frame);//图片保存到本工程目录中
			imshow("【图片】", frame);
			waitKey(200);
			main_1();
		}
	}
	return 0;

}

void main_1() {
	imageget = imread(filename);
	//namedWindow("Thresholded Image", CV_WINDOW_AUTOSIZE);
	//createTrackbar("HL", "Thresholded Image", &hmin, 180, hsvreg);
	//createTrackbar("HH", "Thresholded Image", &hmax, 180, hsvreg);
	//createTrackbar("SL", "Thresholded Image", &smin, 360, hsvreg);
	//createTrackbar("SH", "Thresholded Image", &smax, 360, hsvreg);
	//resize(imageget, imageget, Size(480, 640), 0, 0, 1);

	//tz_out = imageget(Range(50, 400), Range(150, 500));
	//imwrite("E:/tupian/购物/雪花模板.jpg", tz_out);

	while (t < 7)
	{
		switch (t) {
		case 1:		//判断红木块+AD钙奶
		{
		hmin = 160; hmax = 175;
		smin = 43; smax = 255;
		vmin = 0; vmax = 255;
		hsvreg(0,0);
		t++;
		}break;
		case 2:		//判断绿木块
		{
		hmin = 45; hmax = 90;
		smin = 43; smax = 255;
		vmin = 0; vmax = 255;
		hsvreg(0,0);
		t++;
		}break;
		case 3:		//判断蓝木块
		{
		hmin = 100; hmax = 124;
		smin = 46; smax = 255;
		vmin = 43; vmax = 255;
		hsvreg(0,0);
		t++;
		}break;
		case 4:		//判断网球
		{
		hmin = 25; hmax = 45;
		smin = 43; smax = 255;
		vmin = 0; vmax = 255;
		hsvreg(0,0);
		t++;
		}break;
		case 5:		//判断乐虎
		{
		hmin = 0; hmax = 180;
		smin = 0; smax = 255;
		vmin = 0; vmax = 50;
		hsvreg(0,0);
		t++;
		}break;
		case 6:		//红牛预判断
		{
		hmin = 11; hmax = 30;
		smin = 43; smax = 255;
		vmin = 46; vmax = 255;
		hsvreg(0, 0);
		t++;
		}break;
		}
		if (getpicture == 1) {t = 7;}
	}

	if (getpicture == 0) {
		for (int m = 1;m < 8;m++) {
			x = 0;
			if (flag_mf == 1) { m = 7; }
			if (m == 4) {
				tezheng(imageget, image04);
				if (x > 5) {
					cout << "特仑苏" << endl;
					getpicture = 1;
					break;
				}
			}
			if (m == 1) {
				tezheng(imageget, image05);
				if (x >  3) {
					cout << "雪花" << endl;
					getpicture = 1;
					break;
				}
			}
			if (m == 5) {
				tezheng(imageget, image06);
				if (x >  5) {
					cout << "乐虎" << endl;
					getpicture = 1;
					break;
				}
			}
			if (m == 2) {
				tezheng(imageget, image01);
				if (x >  3) {
					cout << "爽歪歪" << endl;
					getpicture = 1;
					break;
				}
			}
			if (m == 3) {
				if (flag_hn) {
					cout << "红牛" << endl;
					getpicture = 1;
					flag_hn = 0;
					break;
				}
			}
			if (m == 7) {
				tezheng(imageget, image03);
				if (x >= 8) {
					cout << "魔方" << endl;
					getpicture = 1;
					break;
				}
			}
			if (m == 6) {
				tezheng(imageget, image02);
				if (x >  5) {
					cout << "养乐多" << endl;
					getpicture = 1;
					break;
				}
			}

		}
		if (getpicture == 0) { cout << "魔方" << endl; }
	}

	waitKey(10);
}

void tezheng(Mat image1,Mat image2) {
	//提取特征点
	tz_out = image1(Range(50, 400), Range(150, 500));
	//imwrite("E:/tupian/购物/爽歪歪模板.jpg", tz_out);
	imshow("roi", tz_out);
	GaussianBlur(tz_out, tz_out, Size(3, 3), 0.5);
	GaussianBlur(image2, image2, Size(3, 3), 0.5);
	Ptr<SIFT> detector = SIFT::create(50);  //限定提起前15个特征点
	vector<KeyPoint> keyPoint1, keyPoint2;
	detector->detect(tz_out, keyPoint1);
	detector->detect(image2, keyPoint2);

	//绘制特征点
	//drawKeypoints(tz_out, keyPoint1, tz_out, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//drawKeypoints(image2, keyPoint2, image2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//namedWindow("KeyPoints of image1", 0);
	//namedWindow("KeyPoints of image2", 0);

	//imshow("KeyPoints of image1", image1);
	//imshow("KeyPoints of image2", image2);

	//特征点描述，为下边的特征点匹配做准备
	SiftDescriptorExtractor siftDescriptor;
	Mat imageDesc1, imageDesc2;
	detector->compute(tz_out, keyPoint1, imageDesc1);
	detector->compute(image2, keyPoint2, imageDesc2);

	////特征点匹配并显示匹配结果
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matchePoints;
	matcher.match(imageDesc1, imageDesc2, matchePoints, Mat());
	Mat imageOutput;
	//drawMatches(tz_out, keyPoint1, image2, keyPoint2, matchePoints, imageOutput);
	//namedWindow("Mathch Points", 0);
	//imshow("Mathch Points", imageOutput);

	double minMatch = 1;
	double maxMatch = 0;
	for (int i = 0;i<matchePoints.size();i++)
	{
		//匹配值最大最小值获取
		minMatch = minMatch>matchePoints[i].distance ? matchePoints[i].distance : minMatch;
		maxMatch = maxMatch<matchePoints[i].distance ? matchePoints[i].distance : maxMatch;
	}
	//最大最小值输出
	//cout << "最佳匹配值是： " << minMatch << endl;
	//cout << "最差匹配值是： " << maxMatch << endl;

	//获取排在前边的几个最优匹配结果
	vector<DMatch> goodMatchePoints;
	for (int i = 0;i<matchePoints.size();i++)
	{
		if (matchePoints[i].distance<minMatch + (maxMatch - minMatch) / 2.5)
		{
			x = x + 1;
			goodMatchePoints.push_back(matchePoints[i]);
		}
	}
	cout << "x= " << x << endl;
	//绘制最优匹配点
	Mat imageOutputgood;
	//drawMatches(tz_out, keyPoint1, image2, keyPoint2, goodMatchePoints, imageOutputgood, Scalar::all(-1),
		//Scalar::all(-1), vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
	//imshow("Mathch Points", imageOutputgood);
}

void hsvreg(int, void*) {
	Mat imgHSV, mask, imageget1;
	blur(imageget, imageget1, Size(7, 7));
	cvtColor(imageget1, imgHSV, COLOR_BGR2HSV);//转为HSV
	inRange(imgHSV, Scalar(hmin, smin, vmin), Scalar(hmax, smax, vmax), mask);
	imshow("imgHSV", mask);

	//寻找最外层轮廓
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, CV_RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	Mat imageContours = Mat::zeros(imageget.size(), CV_8UC3);    //最小外接矩形画布
	float area_max = 0;
	float width;
	float height;
	float x;
	float y;

	vector<Rect> boundRect(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		boundRect[i] = boundingRect(Mat(contours[i]));
		if (boundRect[i].area()>area_max) {
			area_max = boundRect[i].area();

			width = boundRect[i].width;
			height = boundRect[i].height;
			x = boundRect[i].x;
			y = boundRect[i].y;
		}
	}
	//cout << " width=" << width << endl;
	//cout << " height=" << height << endl;
	//cout << " area=" << area_max << endl;


	if (area_max > 3000) {
		if (t == 1) {
			if (area_max > 15000 && area_max < 35000) {
				if ((width / height) > 0.85 && (width / height) < 1.15) {
					cout << "红木块" << endl;
					getpicture = 1;
				}
			}
			if (area_max > 5000 && area_max < 10000) {
				if ((width / height) > 0.3 && (width / height) < 0.7) {
					cout << "AD钙奶" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 2) {
			if (area_max > 15000 && area_max < 35000) {
				if ((width / height) > 0.85 && (width / height) < 1.15) {
					cout << "绿木块" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 3) {
			if (area_max > 15000 && area_max < 35000) {
				if ((width / height) > 0.85 && (width / height) < 1.15) {
					cout << "蓝木块" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 4) {
			if (area_max > 20000 && area_max < 60000) {
				if ((width / height) > 0.7 && (width / height) < 1.4) {
					cout << "网球" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 5) {
			if (area_max > 40000 && area_max < 70000) {
				if ((width / height) > 0.3 && (width / height) < 1.0) {
					cout << "乐虎" << endl;
					getpicture = 1;
				}
			}
		}
		if (t == 6) {
			if (area_max > 33000 && area_max < 50000) {
				if ((width / height) > 0.6 && (width / height) < 0.9) {
					flag_hn = 1;
				}
			}
		}
	}

	if (getpicture) {
		cout << " width=" << width << endl;
		cout << " height=" << height << endl;
		cout << " area=" << area_max << endl;
		rectangle(imageContours, Rect(x, y, width, height), Scalar(0, 0, 255), 1, 8);
		imshow("颜色识别结果", imageContours);
	}
}
