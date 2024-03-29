/*
*------------------------------------------------------------------------
*CfgSliderShow.h
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
//config for single camera related stuff
#ifndef __CFG_SLIDERSHOW_H__
#define __CFG_SLIDERSHOW_H__

#include "CfgBase.h"
namespace xPlayer {
	class  CFG_EXPORT CfgSliderShow : public CfgBase {
	public:
		CfgSliderShow();
		CfgSliderShow( const CfgSliderShow &x )=default;
		CfgSliderShow& operator = (const CfgSliderShow &x)=default;
		virtual ~CfgSliderShow() {};

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);


		std::string  getRecFolder() const;
		virtual std::string toString();

	public:
		ImgSize		capImgSz;	   //capture output image size
		ImgSize		dspImgSz;	   //output image sz after H264 decoding regardless the original size from camera
		uint32_t	frameInterval_ms;

		//todo: add more
		int 		frmQueSz;				//que size for FrmInfo

		bool		isRec;
		std::string mp4LocationAndPrefix;   //"c:/temp/FamilyMov-"

		std::string	imgRootFolder;
		std::string	mp3RootFolder;
		uint64_t	frmNumLastTimePlayed;
	};
	typedef std::shared_ptr<CfgSliderShow>		CfgSliderShowPtr;
}

#endif
