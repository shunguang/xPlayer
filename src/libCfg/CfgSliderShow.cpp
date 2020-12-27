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
	, frameInterval_ms_(1000)
	, frmQueSz_(10)
	, isRec_(true)
	, isDisp_(true)
	, mp4LocationAndPrefix_("./myRecFolder/tmp")
	, imgRootFolder_("c:/temp/img")
	, mp3RootFolder_("c:/temp/mp3")
	, frmNumLastTimePlayed_(0)
{
}

void CfgSliderShow::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	capImgSz_.w = pt.get<int>("capImgW");
	capImgSz_.h = pt.get<int>("capImgH");
	dspImgSz_.w = pt.get<int>("dspImgW");
	dspImgSz_.h = pt.get<int>("dspImgH");

	//frameInterval_ms_ 	= pt.get<int>("frameInterval_ms");
	imgRootFolder_ = pt.get<std::string>("imgRootFolder");
	mp3RootFolder_ = pt.get<std::string>("mp3RootFolder");
	frmNumLastTimePlayed_  = pt.get<uint64_t>("frmNumLastTimePlayed");
}

boost::property_tree::ptree CfgSliderShow::toPropertyTree()
{
	boost::property_tree::ptree pt;
	pt.put("capImgW", capImgSz_.w);
	pt.put("capImgH", capImgSz_.h);
	pt.put("dspImgW", dspImgSz_.w);
	pt.put("dspImgH", dspImgSz_.h);

	pt.put("imgRootFolder", imgRootFolder_);
	pt.put("mp3RootFolder", mp3RootFolder_);
	pt.put("frmNumLastTimePlayed", frmNumLastTimePlayed_);
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
