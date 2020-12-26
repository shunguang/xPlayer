/*
*------------------------------------------------------------------------
*DcUI.h
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
//----------------------------------------------------------------------------------------
//Shared data container interface for xEye system, typically holds multiple cameras
//----------------------------------------------------------------------------------------
#ifndef _DC_UI_H_
#define _DC_UI_H_

#include "libCfg/Cfg.h"

#include "RgbCircularQ_h.h"
#include "DspCircularQ_h.h"
#include "DcDefs.h"

namespace xPlayer {
	class DC_EXPORT DcUI{
	public:
		DcUI( CfgPtr &cfg );
		DcUI( const DcUI &x) = delete;
		DcUI& operator=(DcUI const&) = delete;
		~DcUI() = default;
		
		//only capture thread calls this function once for each frm
		bool wrtRgbFrmByCapThread(const RgbFrm_h *src)
		{
			return m_capFrmQ->wrt(src);
		}

		//only display thread calls this function once for each frm
		bool readRgbFrmByDspThread(RgbFrm_h *dst)
		{
			return m_capFrmQ->read(dst);
		}

		bool wrtDspFrmByDspThread(const DspFrm_h *src)    //add item
		{
			return m_dspFrmQ->wrt(src);
		}

		bool readDspFrmByGuiThread(DspFrm_h *dst)         //sink
		{
			return m_dspFrmQ->read(dst);
		}

	protected:
		//initial shared data container
		void initSharedDc();
		
	public:
		CfgPtr 					m_cfg;
		RgbCircularQ_hPtr		m_capFrmQ;       //captureed que
		DspCircularQ_hPtr		m_dspFrmQ;       //dsp que
	};
	typedef std::shared_ptr<DcUI> DcUIPtr;
}
#endif		
