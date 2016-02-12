#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>

std::string input_file;
std::string output_file = "result.tif";
std::string kernel_file;
bool should_resize_kernel = false;
int resize_len = 31;
bool should_gauss_kernel = false;
double gaussian_sigma = 2.0;
double gamma = 2.2;
bool show_result = false;

#define DO_LINEAR_IMAGE_OUTPUT

float calc_gamma(float val,double gm) {
	CV_Assert(val >= 0.);
	
	if(val > 1.0)
		val = 1.0;
	
	return((float)pow(val, gm));
}

void usage() {
	std::cout << "bokeh_emu [-i src file] [-k kernel file] [-o output file(optional)] " <<
		"[-r kernel resize(optional)] [-b gaussian sigma of kernel(optional)] " << 
		"[-g gamma (optional)] [-s(optional)] " << std::endl;
}

int main(int argc, char *argv[]) {
	int result;
	
	if(argc < 2) {
		usage();
		return -1;
	}
	
	{
		while((result=getopt(argc,argv,"i:o:k:r:g:b:vsh"))!=-1){
			std::istringstream is;
			std::string str;
			
			if(optarg) {
				str = (optarg);
				is.str(str);
			}
			
			switch(result){
			case 'i':
				is >> input_file;
				break;
			case 'o':
				is >> output_file;
				break;
			case 'k':
				is >> kernel_file;
				break;
			case 'r':
				is >> resize_len;
				should_resize_kernel = true;
				break;
			case 'b':
				is >> gaussian_sigma;
				should_gauss_kernel = true;
			case 'g':
				is >> gamma;
				break;
			case 's':
				show_result = true;
				break;
			case 'h':
			default:
				usage();
				return -1;
			break;
			}
		}
		
		std::cout << "input file: " << input_file << std::endl;
		std::cout << "output file: " << output_file << std::endl;
		std::cout << "kernel file: " << kernel_file << std::endl;
		std::cout << "resize kernel?: " << should_resize_kernel << std::endl;
		if(should_resize_kernel) std::cout << "length of kernel resize: " << output_file << std::endl;
		std::cout << "gaussian blur to kernel?: " << should_gauss_kernel << std::endl;
		if(should_gauss_kernel) std::cout << "kernel gaussian sigma: " << gaussian_sigma << std::endl;
		std::cout << "gamma: " << gamma << std::endl;
	}
	
    cv::Mat src_img = cv::imread(input_file);
    CV_Assert(!src_img.empty());
	cv::Mat dest_img = cv::Mat::zeros(cv::Size(src_img.size().width, src_img.size().height), CV_8UC3);
	
    cv::Mat kernel =cv::imread(kernel_file);
    CV_Assert(!kernel.empty());
    cv::Mat f_kernel;
    
    cv::cvtColor(kernel, kernel, CV_BGR2GRAY);
    if(should_gauss_kernel) cv::GaussianBlur(kernel, kernel, cv::Size(0,0), gaussian_sigma);
    if(should_resize_kernel) cv::resize(kernel, kernel,cv::Size(resize_len,resize_len), 0,0, cv::INTER_LINEAR);
	kernel.convertTo(f_kernel, CV_32F, 1.0/255.);
	cv::normalize(f_kernel, f_kernel, 1.0, 0, CV_L1);
	
	cv::Mat fsrc_img;
	src_img.convertTo(fsrc_img, CV_32FC3, 1.0/255.);
	
	cv::Mat fsrc_img_gamma = cv::Mat(fsrc_img.size(), fsrc_img.type());
	
    {
		cv::MatIterator_<cv::Vec3f> it = fsrc_img.begin<cv::Vec3f>(), it_end = fsrc_img.end<cv::Vec3f>();
		cv::MatIterator_<cv::Vec3f> itg = fsrc_img_gamma.begin<cv::Vec3f>();
		for(; it != it_end; ++it,++itg) {
			cv::Vec3f pix = *it,pix_gm;
			
			pix_gm[0] = calc_gamma(pix[0],gamma);
			pix_gm[1] = calc_gamma(pix[1],gamma);
			pix_gm[2] = calc_gamma(pix[2],gamma);
			
			*itg = pix_gm;
		}
	}
	
#ifdef DO_LINEAR_IMAGE_OUTPUT
	cv::Mat gamma_img;
	fsrc_img_gamma.convertTo(gamma_img, CV_8UC3, 255.);
	cv::imwrite("linear.tif", gamma_img);
#endif
	
	cv::Mat fdst_img = fsrc_img_gamma.clone();	
    cv::filter2D(fsrc_img_gamma, fdst_img, -1, f_kernel);
	cv::Mat fdst_img_ungamma = cv::Mat::zeros(fdst_img.size(), fdst_img.type());
	
    {
		double gm = 1.0 / gamma;
		cv::MatIterator_<cv::Vec3f> it = fdst_img.begin<cv::Vec3f>(), it_end = fdst_img.end<cv::Vec3f>();
		cv::MatIterator_<cv::Vec3f> itg = fdst_img_ungamma.begin<cv::Vec3f>();
		for(; it != it_end; ++it,++itg) {
			cv::Vec3f pix = *it,pix_gm;
			
			pix_gm[0] = calc_gamma(pix[0],gm);
			pix_gm[1] = calc_gamma(pix[1],gm);
			pix_gm[2] = calc_gamma(pix[2],gm);
			
			*itg = pix_gm;
		}
	}
	
	fdst_img_ungamma.convertTo(dest_img, CV_8UC3, 255.);
	cv::imwrite(output_file, dest_img);
    
    if(show_result) {
		cv::namedWindow("src", cv::WINDOW_NORMAL);
		cv::namedWindow("kernel", cv::WINDOW_NORMAL);
		cv::namedWindow("result", cv::WINDOW_NORMAL);
	 
		cv::imshow("src", src_img);
		cv::imshow("kernel", kernel);
		cv::imshow("result", dest_img);

	#ifdef DO_LINEAR_IMAGE_OUTPUT
		cv::namedWindow("linear", cv::WINDOW_NORMAL);
		cv::imshow("linear", gamma_img);
	#endif
		cv::waitKey(0);
	}

    return 0;
}
