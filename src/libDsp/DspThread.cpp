/*
*------------------------------------------------------------------------
*DspThread.cpp
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
#include "DspThread.h"

using namespace std;
using namespace xPlayer;
DspThread::DspThread( const int camId, const int threadId, const std::string &threadName )
: ThreadQt	( THD_TASK_DSP, threadId, threadName )
, m_capSz(320, 240)
, m_dspSz(320, 240)
, m_capFrm_h(0)
, m_dspFrm_h(0)
, m_dspImg(320,240, CV_8UC3)
{
	cout << "DspThread::DspThread(): called" << endl;
}

DspThread::~DspThread()
{
}

//only need to one frame 
//todo: compbine with RunThreadS::runLoop() for efficency 
void DspThread::procNextTask()
{
	const boost::posix_time::ptime start = APP_LOCAL_TIME;

	//read new frm from detection result Queue
	bool hasDetFrm = m_dcUI->readRgbFrmByDspThread( m_capFrm_h.get() );
	if (!hasDetFrm) {
		this->goToSleep();
		//dumpLog("DspThread():%s, go to sleep", m_threadName.c_str());
		return;
	}

	//do change detection
	bool suc = prepareDspImg();

	//wrt results into output queue
	m_dcUI->wrtDspFrmByDspThread(m_dspFrm_h.get());
	emit sigReady2Disp();

	if (m_dspFrm_h->m_fn % m_frmFreqToLog == 0) {
		uint32_t dt = timeIntervalMillisec(start);
		dumpLog("DspThread::procNextTask(): %s, fn=%llu, dt=%d", m_threadName.c_str(),m_dspFrm_h->m_fn, dt);
	}
}

bool DspThread::prepareDspImg()
{
#if DSP_USE_QPIXMAP		
	if( m_capSz.width == m_dspSz.width && m_capSz.height == m_dspSz.height ){
		m_dspFrm_h->m_img = cvMatToQPixmap( m_capFrm_h->I_ );
	}
	else{
		cv::resize( m_capFrm_h->I_, m_dspImg, m_dspSz, 0, 0, CV_INTER_LINEAR);
		m_dspFrm_h->m_img = cvMatToQPixmap(m_dspImg);
	}	
#else
	myExit("DspThread::prepareDspImg():  todo!");
#endif	
	return true;
}

bool DspThread::procInit()
{
	CfgSliderShow cfg = m_cfg->getSliderShow();
	
	m_capSz = cv::Size(cfg.capImgSz_.w, cfg.capImgSz_.h);
	m_capFrm_h.reset(new RgbFrm_h(m_capSz.width, m_capSz.height));

	m_dspSz = cv::Size(cfg.dspImgSz_.w, cfg.dspImgSz_.h);
	m_dspFrm_h.reset(new DspFrm_h(m_dspSz.width, m_dspSz.height));
	
	m_dspImg.create(m_dspSz, 0);

	dumpLog("DspThread::procInit(): capSz(w=%d,h=%d), dspSz=(w=%d,h=%d)", m_capSz.width, m_capSz.height,m_dspSz.width, m_dspSz.height);
	return true;
}

void DspThread::dumpFrm(const std::string &folderPath)
{
	m_dspFrm_h->dump(folderPath);
}
