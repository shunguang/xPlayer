/*
*------------------------------------------------------------------------
*CvUtilFuncs.h
*
* This code was developed by Shunguang Wu in his spare time. No government
* or any client funds were used.
*
*
* THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
* EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
* WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
*
* IN NO EVENT SHALL THE AUTHOR OR DISTRIBUTOR BE LIABLE FOR
* ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
* OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
* WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
* LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
* OF THIS SOFTWARE.
*
* Permission to use, copy, modify, distribute, and sell this software and
* its documentation for any purpose is prohibited unless it is granted under
* the author's written notice.
*
* Copyright(c) 2020 by Shunguang Wu, All Right Reserved
*-------------------------------------------------------------------------
*/
#ifndef _CV_UTIL_FUNCS_H_
#define _CV_UTIL_FUNCS_H_

#include "DataTypes.h"
#include "Roi.h"
#include "FileUtil.h"
#include "UtilDefs.h"

namespace xPlayer {
	template<typename _Tp>
	_Tp UTIL_EXPORT sumVal(const cv::Mat &x);
	cv::Mat UTIL_EXPORT sumCols(const cv::Mat &x);
	cv::Mat UTIL_EXPORT sumRows(const cv::Mat &x);

	void UTIL_EXPORT gray2bgr(const cv::Mat &gray, cv::Mat &bgr);

	//for any type of given matrix $in$, convert it into a CV_8U type $out$ matrix
	void UTIL_EXPORT convert_to_CV_8U(const cv::Mat &in, cv::Mat &out);
	bool UTIL_EXPORT myCvInv(const cv::Mat &X, cv::Mat &invX, double &det);

	bool UTIL_EXPORT getCvImgRowStep(const IplImage *img, int &rowStep, int &row0);
	//put ROI image of $src$ into $des$ at $(desXo, desYo)$
	void UTIL_EXPORT setCvImg(IplImage *des, const int &desXo, const int &desYo, const IplImage *src, const int &srcRoiXo, const int &srcRoiYo, const int &srcRoiW, const int &srcRoiH);


	//void UTILS_EXPORT combineTwoImg_LR( const cv::Mat &imgLeft, const cv::Mat &imgRight, cv::Mat imgOut );

	float UTIL_EXPORT maskNonZeroPercent(const cv::Mat &mask, const int &xo, const int &yo, const int &xb, const int &yb, size_t &n);
	//void  UTILS_EXPORT cvMat2SwfMat( const cv::Mat &x, swfMat &y );
	//void  UTILS_EXPORT swfMat2cvMat( const swfMat &x, cv::Mat &y  );

	//dL>0: increase the size of $in$ by 2^dL 
	//dL<0: decrease the size of $in$ by 2^dL 
	void UTIL_EXPORT rectPyrLevelUpDown(const cv::Rect &in, const int dL, cv::Rect &out);

	//assume the channel order in <x> is BGR, since we call cv::imwrite()
	std::string UTIL_EXPORT genImgFilePath(const std::string &myPath, const std::string &fileNameWoExt, const uint64_t fn, const int L=0);
	void UTIL_EXPORT myImgWrite(const cv::Mat &x, const std::string &dir, const std::string &fname, const size_t fn, const size_t L = 0);
	void UTIL_EXPORT myImgWrite(const IplImage* cvTrkImg, const std::string &myPath, const std::string &fileNameWoExt, const size_t &fn);
	void UTIL_EXPORT dumpCvImgToTextFile(const IplImage *J, const std::string &fileName);

	void UTIL_EXPORT drawRect(cv::Mat &img, const Roi &rect, const uint32_t len, const cv::Scalar& color, int thickness, int lineType, int shift);
	void UTIL_EXPORT drawPluses(cv::Mat &img, const std::vector<cv::Point2f> &v, const uint32_t len, const cv::Scalar& color, int thickness, int lineType, int shift);
	void UTIL_EXPORT drawPluses(cv::Mat &img, const std::vector<cv::Point> &v, const uint32_t len, const cv::Scalar& color, int thickness, int lineType, int shift);

	void UTIL_EXPORT drawPlus(cv::Mat &img, const cv::Point2f &pt, const uint32_t len, const cv::Scalar& color, int thickness, int lineType, int shift);
	void UTIL_EXPORT drawPlus(cv::Mat &img, const cv::Point &pt, const uint32_t len, const cv::Scalar& color, int thickness, int lineType, int shift);
	void UTIL_EXPORT wrtieStrings(cv::Mat& img, const std::vector<std::string>& vStrs, const cv::Point &org, int fontFace, double fontScale, cv::Scalar color, int thickness, int lineType);
	void UTIL_EXPORT writeFrmNum(cv::Mat &img, const uint64_t frmNum, const cv::Point &org );
}

#endif
