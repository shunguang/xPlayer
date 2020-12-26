/*
*------------------------------------------------------------------------
*RunCap.cpp
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
#include "RunCap.h"

using namespace std;
using namespace xPlayer;
using namespace boost::posix_time;
RunCap::RunCap(CfgPtr &cfg)
	: m_cfg(cfg)
	, m_dcUI(0)
	, m_capThread(0)
	, m_mainLoopExited(false)
	, m_exitMainLoop(false)
{
	dumpLog( "RunCap::RunCap(): start!" );
	CfgLog logCfg = m_cfg->getLog();
	myCreateDir( logCfg.logFolder );

	cout << "RunCap::RunCap(): cfg=" << cfg->toString() << endl;
	m_dcUI.reset( new DcUI(cfg) );

	//get cam ids from cfg

	//create capture threads
	int threadId=0;

	m_capThread.reset(new CapThread(0,  "CapThread") );
	m_capThread->setCfg( m_cfg );
	m_capThread->setDcUI( m_dcUI );
	dumpLog( "RunCap::RunCap(): done!" );
}

RunCap::~RunCap()
{
}

void RunCap::start()
{
	m_exitMainLoop = false;
	m_mainLoopExited = false;

	dumpLog( "RunCap::runAllThreads(): start!" );

	m_capThread->start();
	//make sure every capture thread was initialized
	while (1) {
		THREAD_SLEEP(10);
		if (m_capThread->isSleepMode()) {
			break;
		}
	}
	m_capThread->wakeupToWork();
	dumpLog("RunCap::startThreads(): ThreadId=%d, name=%s started.", m_capThread->m_threadId, m_capThread->m_threadName.c_str());

	//waiting for input from keyboard
	char c;
	cin >> c;
	while(c != 'q'){
		cin >> c;
	}

	quit();
	m_mainLoopExited = true;
	dumpLog("RunCap::startThreads(): exited!");
}


void RunCap::quit()
{
	m_capThread->forceQuit();
	dumpLog("Thread: id=%d, name=%s quited!", m_capThread->m_threadId, m_capThread->m_threadName.c_str());
	m_exitMainLoop = true;
}





