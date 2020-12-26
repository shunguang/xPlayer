/*
*------------------------------------------------------------------------
*CfgSliderShow.cpp
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
#include "CfgSliderShow.h"

using namespace std;
using namespace xPlayer;

CfgSliderShow::CfgSliderShow()
	: CfgBase()
	, capImgSz_(1920,1080)
	, dspImgSz_(1920,1080)
	, fps_(10, 1)
	, frmQueSz_(10)
	, isRec_(true)
	, isDisp_(true)
	, mp4LocationAndPrefix_("./myRecFolder/tmp")
	, imgRootFolder("c:/temp/img")
	, mp3RootFolder("c:/temp/mp3")

{
}

void CfgSliderShow::fromPropertyTree(const boost::property_tree::ptree &pt)
{
#if 0
	dspImgSz_.w 	= pt.get<int>("imgW");
	dspImgSz_.h 	= pt.get<int>("imgH");
	fps_.num 	= pt.get<int>("fpsNum");
	fps_.den 	= pt.get<int>("fpsDen");
#endif
}

boost::property_tree::ptree CfgSliderShow::toPropertyTree()
{
	boost::property_tree::ptree pt;
#if 0
	pt.put("imgW", imgSz_.w);
	pt.put("imgH", imgSz_.h);
	pt.put("fpsNum", fps_.num);
	pt.put("fpsDen", fps_.den);
	pt.put("frmQueSz", frmQueSz_);
	pt.put( "mp4LocationAndPrefix", mp4LocationAndPrefix_);
#endif

	return pt;
}

std::string CfgSliderShow::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}

//mp4LocationAndPrefix_ = "/home/rec/FrontDoor/rec" or ""
std::string  CfgSliderShow::getRecFolder() const
{
	if (mp4LocationAndPrefix_.empty()){
		return "";
	}

	std::string fDir, fName;
	splitFolder(mp4LocationAndPrefix_, fDir, fName);
	return fDir;
}
