
#include <iostream>
#include <fstream>
#include <math.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


bool lie_inside_1(int j, int i, int width, int height, int ans_width, int ans_height, float tan_alpha, float tan_beta)
{
	if(((float)i/(float)(ans_width - 1 - j))>tan_alpha && ((float)(ans_height - 1 - i)/(float)(j)>abs(tan_beta)))
		return true;
	else
		return false;

}

bool lie_inside_2(int j, int i, int width, int height, int ans_width, int ans_height, float tan_alpha, float tan_beta)
{
	if(((float)i/(float)(ans_width - 1 - j))>tan_alpha && ((float)(ans_height - 1 - i)/(float)(ans_width - 1 - j)>abs(tan_beta)))
		return true;
	else
		return false;

}

bool lie_inside_3(int j, int i, int width, int height, int ans_width, int ans_height, float tan_alpha, float tan_beta)
{
	if(((float)i/(float)(j))>abs(tan_alpha) && ((float)(ans_height - 1 - i)/(float)(j)>tan_beta))
		return true;
	else
		return false;

}

bool lie_inside_4(int j, int i, int width, int height, int ans_width, int ans_height, float tan_alpha, float tan_beta)
{
	if(((float)i/(float)(j))>abs(tan_alpha) && ((float)(ans_height - 1 - i)/(float)(ans_width - 1 - j)>abs(tan_beta)))
		return true;
	else
		return false;

}


int main()
{
	float tan_alpha, tan_beta;
	cout << "Enter the tan of the angle to be made from the top edge with respect to the x axis:";
	cin >> tan_alpha;
	cout << "Enter the tan of the angle to be made from the lower edge with respect to the x axis:";
	cin >> tan_beta;
	char src[] = "image.ppm";
	char type[5];
	int width, height;
	int max_val;
	ifstream file;
	file.open(src,ios::in);
	file >> type;
	file >> width >> height;
	file >> max_val;
	int pixel_values[height][width][3];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			file >> pixel_values[i][j][0] >> pixel_values[i][j][1] >> pixel_values[i][j][2];
		}		
	}
	file.close();

	ofstream fout;
	char des[] = "parallelogram.ppm";
	int ans_width = width;
	int ans_height;
	if(tan_alpha>=0)
	{
		if(tan_beta>=0)
		{
			ans_height = height + ((int)(width*tan_alpha));
		}
		else
		{
			ans_height = height + ((int)(width*tan_alpha)) + ((int)(width*abs(tan_beta)));
		}
	}
	else
	{
		if(tan_beta>=0)
		{
			ans_height = height;
		}
		else
		{
			ans_height = height + ((int)(width*abs(tan_beta)));
		}
	}
	fout.open("ans.ppm",ios::out);
	fout << type << "\n";
	fout << ans_width << " " << ans_height << "\n";
	fout << max_val << "\n";


	if(tan_alpha>=0)
	{
		if(tan_beta>=0)
		{
			for(int i=0;i<ans_height;i++)
			{
				for(int j=0;j<ans_width;j++)
				{
					if(lie_inside_1(j, i, width, height, ans_width, ans_height, tan_alpha, tan_beta))
					{
						int f =  (int)((i - (int)((ans_width - 1 - j)*tan_alpha))*(((float)height/(float)(ans_height - (ans_width - 1 - j)*tan_alpha - (j)*tan_beta))));
						fout << pixel_values[f][j][0] << " " << pixel_values[f][j][1] << " " << pixel_values[f][j][2] << " ";
					}
					else
						fout << max_val << " " << max_val << " " << max_val << " ";
				}
				//cout << i << endl;	
				fout << "\n";	
			}
		}
		else
		{
			for(int i=0;i<ans_height;i++)
			{
				for(int j=0;j<ans_width;j++)
				{
					if(lie_inside_2(j, i, width, height, ans_width, ans_height, tan_alpha, tan_beta))
					{
						int f =  (int)((i - (int)((ans_width - 1 - j)*tan_alpha))*(((float)height/(float)(ans_height - (ans_width - 1 - j)*tan_alpha - (ans_width - 1 - j)*abs(tan_beta)))));
						fout << pixel_values[f][j][0] << " " << pixel_values[f][j][1] << " " << pixel_values[f][j][2] << " ";
					}
					else
						fout << max_val << " " << max_val << " " << max_val << " ";
				}
				//cout << i << endl;	
				fout << "\n";	
			}
		}
	}
	else
	{
		if(tan_beta>=0)
		{
			for(int i=0;i<ans_height;i++)
			{
				for(int j=0;j<ans_width;j++)
				{
					if(lie_inside_3(j, i, width, height, ans_width, ans_height, tan_alpha, tan_beta))
					{
						int f =  (int)((i - (int)((j)*abs(tan_alpha)))*((float)height/(float)(ans_height - (j)*abs(tan_alpha) - (j)*tan_beta)));
						fout << pixel_values[f][j][0] << " " << pixel_values[f][j][1] << " " << pixel_values[f][j][2] << " ";
					}
					else
						fout << max_val << " " << max_val << " " << max_val << " ";
				}
				//cout << i << endl;	
				fout << "\n";	
			}
		}
		else
		{
			for(int i=0;i<ans_height;i++)
			{
				for(int j=0;j<ans_width;j++)
				{
					if(lie_inside_4(j, i, width, height, ans_width, ans_height, tan_alpha, tan_beta))
					{
						int f =  (int)((i - (int)((j)*abs(tan_alpha)))*((float)height/(float)(ans_height - (j)*abs(tan_alpha) - (ans_width - 1 - j)*abs(tan_beta))));
						fout << pixel_values[f][j][0] << " " << pixel_values[f][j][1] << " " << pixel_values[f][j][2] << " ";
					}
					else
						fout << max_val << " " << max_val << " " << max_val << " ";
				}
				//cout << i << endl;	
				fout << "\n";	
			}
		}
	}
	
	fout.close();
	return 0;
}
