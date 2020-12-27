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

		ImgSize getDispImgSz() {
			int w = maxGuiWinSz.w;
			int h = maxGuiWinSz.h - logoSz.h;
			return ImgSize(w, h);
		}

	public:
		int			minGuiWinW;     //minimum gui window width 
		ImgSize		maxGuiWinSz;    //maximu whole size of the gui windows
		ImgSize     logoSz;         //

		std::vector<std::string> vSpeadCombo;
		std::vector<uint32_t>	 vFrmInterval;
		
		int	minCtrlGrpH;	 //ctrl group min height
		int	minCtrlGrpW;	 //ctrl group min width
	};
	typedef std::shared_ptr<CfgGui>		CfgGuiPtr;
}
#endif
