/*
*------------------------------------------------------------------------
*CfgGui.cpp
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
#include "CfgGui.h"

using namespace std;
using namespace xPlayer;

CfgGui::CfgGui()
: CfgBase()
, minGuiWinSz(720, 404)
, maxGuiWinSz(1920, 1080)
, logoSz(60, 60)
, menuBarH(21)
, vSpeadCombo {"5 sec/frame", "2 sec/fram", "1 sec/frame", "1 sec/5frames" }
, vFrmInterval{5000, 2000, 1000, 200}
{
}


void CfgGui::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	minGuiWinSz.w = pt.get<int>("minGuiWinW");
	minGuiWinSz.h = pt.get<int>("minGuiWinH");
	maxGuiWinSz.w = pt.get<int>("maxGuiWinW");
	maxGuiWinSz.h = pt.get<int>("maxGuiWinH");
	logoSz.w = pt.get<int>("logoSzW");
	logoSz.h = pt.get<int>("logoSzH");
}

boost::property_tree::ptree CfgGui::toPropertyTree() 
{
	boost::property_tree::ptree pt;

	pt.put("minGuiWinW", minGuiWinSz.w);
	pt.put("minGuiWinH", minGuiWinSz.h);
	pt.put("maxGuiWinW", maxGuiWinSz.w);
	pt.put("maxGuiWinH", maxGuiWinSz.h);
	pt.put("logoSzW",		logoSz.w);
	pt.put("logoSzH",		logoSz.h);
	return pt;
}

std::string CfgGui::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}
