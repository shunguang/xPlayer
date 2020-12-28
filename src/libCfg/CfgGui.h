/*
*------------------------------------------------------------------------
*CfgGui.h
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
//config for display
#ifndef __CFG_GUI_H__
#define __CFG_GUI_H__

#include "CfgBase.h"
namespace xPlayer {
	class  CFG_EXPORT CfgGui : public CfgBase {
	public:
		CfgGui();
		CfgGui( const CfgGui &x ) = default;
		CfgGui& operator = (const CfgGui &x) = default;
		virtual ~CfgGui()= default;

		virtual boost::property_tree::ptree toPropertyTree();
		virtual void fromPropertyTree(const boost::property_tree::ptree &pt);
		virtual std::string toString();


		ImgSize getMaxDispImgSz() const {
			int w = maxGuiWinSz.w;
			int h = maxGuiWinSz.h;
			return ImgSize(w, h);
		}

		ImgSize getMaxCtrlGrpSz() const {
			ImgSize ret(maxGuiWinSz.w, 0 /*getCtrlGrpH()*/);
			return ret;
		}

		ImgSize getMinDispImgSz() const {
			int w = minGuiWinSz.w;
			int h = minGuiWinSz.h - getCtrlGrpH();
			return ImgSize(w, h);
		}

		ImgSize getMinCtrlGrpSz() const {
			ImgSize ret( minGuiWinSz.w, getCtrlGrpH() );
			return ret;
		}

	
		int getCtrlGrpH() const {
			return std::max<int>(logoSz.h, 85);
		}
	public:
		ImgSize		minGuiWinSz;     //minimum gui window Height 
		ImgSize		maxGuiWinSz;    //maximu whole size of the gui windows
		ImgSize     logoSz;         //
		int			menuBarH;

		std::vector<std::string> vSpeadCombo;
		std::vector<uint32_t>	 vFrmInterval;
	};
	typedef std::shared_ptr<CfgGui>		CfgGuiPtr;
}
#endif
