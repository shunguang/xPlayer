/*
*------------------------------------------------------------------------
*CfgLocalView.cpp
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
#include "CfgLocalView.h"

using namespace std;
using namespace xPlayer;

CfgLocalView::CfgLocalView()
: CfgBase()
, minGuiWinW_(720)
, minCtrlGrpH_(118)
, minCtrlGrpW_M(430)
, minCtrlGrpW_R(160)
, logoSz_(100,100)
, maxGuiWinSz_(1920,1080)
, dispQueSz_(10)
, dispPyrLev_(2)
, maxPyrLev_(3)
, nNumOfCams_(4)
, imgSz_L0_(1920,1080)
{
}

CfgLocalView& CfgLocalView::operator = (const CfgLocalView& x)
{
	//todo: m-thread unsafe
	if (this != &x) {
		CfgBase::operator=(x);
		maxGuiWinSz_=x.maxGuiWinSz_;
		dispQueSz_=x.dispQueSz_;
		dispPyrLev_=x.dispPyrLev_;
		maxPyrLev_ = x.maxPyrLev_;
		nNumOfCams_=x.nNumOfCams_;
		imgSz_L0_ = x.imgSz_L0_;
		vDispPyrLev_ =  x.vDispPyrLev_;
		logoSz_ = x.logoSz_;
	}
	return *this;
}


void CfgLocalView::fromPropertyTree(const boost::property_tree::ptree &pt)
{
	dispQueSz_	= pt.get<int>("dispQueSz");
	dispPyrLev_	= pt.get<int>("dispPyrLev");
}

boost::property_tree::ptree CfgLocalView::toPropertyTree() 
{
	boost::property_tree::ptree pt;

	pt.put( "dispQueSz", 	dispQueSz_ );
	pt.put( "dispPyrLev", 	dispPyrLev_ );
	return pt;
}

std::string CfgLocalView::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();
	return CfgBase::toString(pt);
}


ImgSize CfgLocalView::getCentralWidgetSz() const
{
	int w0=0, h0=0, b = 2;
	ImgSize sz = getDispImgSz();
	if (nNumOfCams_ == 1) {
		w0 = sz.w;
		h0 = sz.h;
	}
	else if (nNumOfCams_ == 2) {
		w0 = 2*sz.w + b;
		h0 = sz.h;
	}
	else if (nNumOfCams_ == 3 || nNumOfCams_ == 4) {
		w0 = 2 * sz.w + b;
		h0 = 2 * sz.h + b;
	}
	else{
		myAssert( 0, "CfgLocalView::getCentralWidgetSz(): cannot supprot more than 4 cameras!");
	}
	
	w0 += 2*b;  //add extra space
	w0 = APP_MAX(w0, minCtrlGrpW_M + minCtrlGrpW_R + logoSz_.w + 20);
	if (w0 < minGuiWinW_) {
		w0 = minGuiWinW_;
	}
	if (w0 > maxGuiWinSz_.w) {
		w0 = maxGuiWinSz_.w;
	}

	//control pannel size
	h0 += APP_MAX(logoSz_.h + 4, minCtrlGrpH_) + 5;
	if (h0 > maxGuiWinSz_.h) {
		h0 = maxGuiWinSz_.h;
	}

	return ImgSize(w0, h0);
}
