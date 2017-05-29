#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <stdio.h>
using namespace cv;
using namespace std;

int font_size, font_style, color, transparency = -70, no_of_items = 3;

int row_ratio = 5, column_ratio = 20;
int main()
{
	string input = "1.jpg";
	Mat input_img = imread(input, CV_LOAD_IMAGE_COLOR);
	int input_rows = input_img.rows;
	int input_cols = input_img.cols;

	cout << "Number of items: ";
	cin >> no_of_items;
	cout << "Enter the items:" << endl;
	cin.ignore();
	vector<string> text;
	string str;
	int max_str_length = 0;
	for(int i=0; i<no_of_items; i++)
	{
		getline(cin, str);
		if(str.length() > max_str_length)
			max_str_length = str.length();
		text.push_back(str);
	}

	for(int y=input_rows/row_ratio - 250;y<input_rows/row_ratio + 250*(no_of_items-1) + 100;y++)
	{
	    for(int x=input_cols/column_ratio;x<input_cols/column_ratio + 150*max_str_length + 300;x++)
	    {
	        // get pixel
	        Vec3b color = input_img.at<Vec3b>(Point(x,y));
	        for(int i=0; i<3; i++)
	        {
	        	int temp = color[i];
	        	int new_temp = temp + transparency;
	        	if(new_temp >= 0)
	        	{
	        		if(new_temp <=255)
	        		{
	        			color[i] = new_temp;
	        		}
	        		else
	        		{
	        			color[i] = 255;
	        		}
	        	}
	        	else
	        	{
	        		color[i] = 0;
	        	}
	        }
	        // ... do something to the color ....

	        // set pixel
	        input_img.at<Vec3b>(Point(x,y)) = color;
	    }
	}
	
	InputOutputArray input_ioa = _InputOutputArray(input_img); 
	for(int i=0; i<no_of_items; i++)
	{
		putText(input_ioa, text[i], cvPoint(input_cols/column_ratio, 250*i + input_rows/row_ratio), FONT_HERSHEY_SCRIPT_SIMPLEX, 9, cvScalar(255,255,255), 5, CV_AA, 0);	
	}
	


	namedWindow("Disp", WINDOW_AUTOSIZE);
	imshow("Disp", input_img);
	waitKey(0);
	imwrite("wallpaper.jpg", input_img);
}