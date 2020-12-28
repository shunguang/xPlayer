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
	, capImgSz(1920,1080)
	, dspImgSz(1920,1080)
	, frameInterval_ms(1000)
	, frmQueSz(10)
	, isRec(true)
	, mp4LocationAndPrefix("./myRecFolder/tmp")
	, imgRootFolder("c:/temp/img")
	, mp3RootFolder("c:/temp/mp3")
	, frmNumLastTimePlayed(0)
{
}

void CfgSliderShow::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	capImgSz.w = pt.get<int>("capImgW");
	capImgSz.h = pt.get<int>("capImgH");
	dspImgSz.w = pt.get<int>("dspImgW");
	dspImgSz.h = pt.get<int>("dspImgH");

	//frameInterval_ms 	= pt.get<int>("frameInterval_ms");
	imgRootFolder = pt.get<std::string>("imgRootFolder");
	mp3RootFolder = pt.get<std::string>("mp3RootFolder");
	frmNumLastTimePlayed  = pt.get<uint64_t>("frmNumLastTimePlayed");
}

boost::property_tree::ptree CfgSliderShow::toPropertyTree()
{
	boost::property_tree::ptree pt;
	pt.put("capImgW", capImgSz.w);
	pt.put("capImgH", capImgSz.h);
	pt.put("dspImgW", dspImgSz.w);
	pt.put("dspImgH", dspImgSz.h);

	pt.put("imgRootFolder", imgRootFolder);
	pt.put("mp3RootFolder", mp3RootFolder);
	pt.put("frmNumLastTimePlayed", frmNumLastTimePlayed);
	return pt;
}

std::string CfgSliderShow::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}

//mp4LocationAndPrefix = "/home/rec/FrontDoor/rec" or ""
std::string  CfgSliderShow::getRecFolder() const
{
	if (mp4LocationAndPrefix.empty()){
		return "";
	}

	std::string fDir, fName;
	splitFolder(mp4LocationAndPrefix, fDir, fName);
	return fDir;
}
