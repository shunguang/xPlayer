/*
*------------------------------------------------------------------------
*DcUI.cpp
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
#include "DcUI.h"
using namespace std;
using namespace xPlayer;
DcUI::DcUI(CfgPtr &cfg)
	: m_cfg(cfg)
	, m_capFrmQ(0)
	, m_dspFrmQ(0)
{
	initSharedDc();
}

//initial shared data container
void DcUI::initSharedDc()
{
	CfgSliderShow  cfg = m_cfg->getSliderShow();
	
	m_capFrmQ.reset(new RgbCircularQ_h(cfg.capImgSz.w, cfg.capImgSz.h, cfg.frmQueSz, 0, "CapFrmQ"));
	m_dspFrmQ.reset(new DspCircularQ_h(cfg.dspImgSz.w, cfg.dspImgSz.h, cfg.frmQueSz, 0, "DspFrmQ"));
}
