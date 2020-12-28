/*
*------------------------------------------------------------------------
*RunXPlayer.cpp
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

#include "RunXPlayer.h"

using namespace std;
using namespace xPlayer;

RunXPlayer::RunXPlayer(CfgPtr& cfg, QWidget* parent)
	: RunGui(cfg, parent)
	, m_capThread()
	, m_dspThread()
	, m_dspFrm()
	, m_threadIdCnt(0)
{
	//Note: <m_dcUI> and <m_cfg> is assigned inside RunGui(cfg, parent)

	//init <DspFrm_h>
	CfgSliderShow prm = cfg->getSliderShow();
	m_dspFrm.reset(new DspFrm_h(prm.dspImgSz.w, prm.dspImgSz.h) );

	//gui initialized at this point

	//create threads: order matters: do not chg 
	createDspThread();
	createCapThread();


	QObject::connect( m_dspThread.get(), SIGNAL(sigReady2Disp()), this, SLOT(respns_dispImg()), MY_QT_CONN);

	startDspThread();
}


RunXPlayer::~RunXPlayer()
{
}



//create capture threads
void RunXPlayer::createCapThread()
{

	m_capThread.reset(new CapThread(0, "CapThread"));
	m_capThread->setCfg(m_cfg);
	m_capThread->setDcUI(m_dcUI);

	//set Dspplay thread
	m_capThread->setDspPtr(m_dspThread.get());

	m_threadIdCnt++;
}

void RunXPlayer::createDspThread()
{
	m_dspThread.reset(new DspThread(0, m_threadIdCnt, "DspThread") );
	m_dspThread->setCfg(m_cfg);
	m_dspThread->setDcUI(m_dcUI);

	m_threadIdCnt++;
}


void RunXPlayer::startCapThread()
{
	showLoadFilesPage();

	m_capThread->start();
	//make sure every capture thread was initialized
	while (1) {
		THREAD_SLEEP(10);
		if (m_capThread->isSleepMode()) {
			break;
		}
	}
	m_capThread->wakeupToWork();
	dumpLog("RunXPlayer::startCapThread(): ThreadId=%d, name=%s started.", m_capThread->m_threadId, m_capThread->m_threadName.c_str());
}

void RunXPlayer::startDspThread()
{
	m_dspThread->start();
	//make sure every capture thread was initialized
	while (1) {
		THREAD_SLEEP(10);
		if (m_dspThread->isSleepMode()) {
			break;
		}
	}
	//x->wakeupToWork();
	dumpLog("RunXPlayer::startDspThread(): ThreadId=%d, name=%s started.", m_dspThread->m_threadId, m_dspThread->m_threadName.c_str());
}


void RunXPlayer::quitAllThreads()
{
	
	m_quitProgDlg->setProgress(20, "Quit capture threads ...");
	m_capThread->forceQuit();

	dumpLog("Thread: id=%d, name=%s quited!", m_capThread->m_threadId, m_capThread->m_threadName.c_str());

	m_quitProgDlg->setProgress(80, "Quit didsplay threads ...");
	m_dspThread->forceQuit();
	dumpLog("Thread: id=%d, name=%s quited!", m_dspThread->m_threadId, m_dspThread->m_threadName.c_str());

	//update and save config for next time run
	boost::filesystem::path from("./cfg_xPlayer.xml");
	if (boost::filesystem::exists(from)) {
		boost::filesystem::path to("./cfg_xPlayer_old.xml");
		boost::filesystem::copy_file(from, to, boost::filesystem::copy_option::overwrite_if_exists);
	}

	uint64_t fn = m_capThread->getFrmNum();
	m_cfg->updateLastTimePlayedFrmNum(fn);
	m_cfg->writeToFile("./cfg_xPlayer.xml");

	m_quitProgDlg->setProgress(90, "all Quited ...");
}


void RunXPlayer::on_actionExit_triggered()
{
	createQuitDlg();
	quitAllThreads();
	closeQuitDlg();
	dumpLog("RunXPlayer::on_actionExit_triggered(): exited!");
}

void RunXPlayer::respns_dispImg()
{
	bool suc = m_dcUI->readDspFrmByGuiThread(m_dspFrm.get() );
	if (suc) {
		m_ui->showImg( m_dspFrm->m_img);
	}
}

void RunXPlayer::on_comboBoxPlaySpeed_currentIndexChanged(int idx)
{
	CfgGui p1 = m_cfg->getGui();
	int dt_ms = p1.vFrmInterval[idx];
	m_capThread->updateFrmInterval(dt_ms);

	CfgSliderShow p2 = m_cfg->getSliderShow();

}

void RunXPlayer::showLoadFilesPage()
{
	int w = m_dspFrm->m_img.width();
	int h = m_dspFrm->m_img.height();

	cv::Mat I(h, w, CV_8UC3);
	I.setTo(cv::Scalar(255, 0, 0));
	cv::putText(I, "Loading files structures ...", cv::Point( w/2-100, h/2 ),
		cv::FONT_HERSHEY_DUPLEX, 3, cv::Scalar(255, 255, 255), 2);

	m_dspFrm->m_img = xPlayer::cvMatToQPixmap(I);
	m_ui->showImg(m_dspFrm->m_img);
}