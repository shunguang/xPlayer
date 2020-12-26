/*
*------------------------------------------------------------------------
*ThreadX.cpp
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
#include "ThreadX.h"
using namespace std;
using namespace xPlayer;

ThreadX::ThreadX(const ThreadTaskId tid, const int threadId, const std::string &name)
	: m_cfg(0)
	, m_dcUI(0)
	, m_taskId(tid)
	, m_threadId( threadId )
	, m_threadName(name)
	, m_frmFreqToLog(100)
	, m_isExitedLoop(true)
	, m_isSleepMode(true)
	, m_rcvdExitLoopCmd(false)
	, m_threadX(0)
	, m_mutex4Working()
	, m_mutexLocal()
	, m_condition4Working()
{
	//cout << "ThreadX::ThreadX(): called" << endl;
}


ThreadX::~ThreadX()
{
	if (m_threadX) {
		m_threadX->join();
	}
}

void ThreadX::setCfg(CfgPtr &cfg)
{
	//cout << "ThreadX::setCfg(): AAA" << endl;
	m_cfg = cfg;
	initFrmFreq2Log( m_taskId );
	//cout << "ThreadX::setCfg(): called" << endl;
}


void ThreadX::setDcUI(DcUIPtr &dcUI )
{
	m_dcUI = dcUI;
	//cout << "ThreadX::setDC(): called" << endl;
}

void ThreadX::start()
{
	procInit();
	m_threadX.reset(new boost::thread(boost::bind(&ThreadX::runLoop, this)));
}

void ThreadX::runLoop()
{
	setExitedLoopFlag(false);
	bool quitLoop = false;
	while (!quitLoop) {
		{
			boost::mutex::scoped_lock lock(m_mutex4Working);
			while (m_isSleepMode) {
				//dumpLog("ThreadX::runLoop(): in sleep mode--%s", m_threadName.c_str());
				m_condition4Working.wait(lock);
			}
			//dumpLog("ThreadX::runLoop(): waked up--%s", m_threadName.c_str());
		}

		quitLoop = isRcvdExitLoopCmd();
		if (quitLoop) {
			break;
		}

		procNextTask();

		quitLoop = isRcvdExitLoopCmd();
	}
	dumpLog("ThreadX::run(): exit loop--%s", m_threadName.c_str());
	setExitedLoopFlag(true);
}

void ThreadX::forceQuit()
{
	setRcvdExitLoopCmdFlag(true);
	if ( isSleepMode() ) {
		wakeupToWork();
	}

	int cnt = 0;
	while (!isExitedLoop()) {
		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		++cnt;
		if (cnt > 500) {
			dumpLog(" stuck at: forceThreadQuit() at thread %s", m_threadName.c_str());
			cnt = 0;
		}
	}

}

void ThreadX::setExitedLoopFlag( const bool f)
{
	boost::mutex::scoped_lock lock(m_mutexLocal);
	m_isExitedLoop = f;
}

bool ThreadX::isExitedLoop()
{
	bool f;
	{
		boost::mutex::scoped_lock lock(m_mutexLocal);
		f = m_isExitedLoop;
	}
	return f;
}

bool ThreadX::isRcvdExitLoopCmd()
{
	bool f;
	{
		boost::mutex::scoped_lock lock(m_mutexLocal);
		f = m_rcvdExitLoopCmd;
	}
	return f;
}

void ThreadX::setRcvdExitLoopCmdFlag(const bool f)
{
	boost::mutex::scoped_lock lock(m_mutexLocal);
	m_rcvdExitLoopCmd = true;
}

bool ThreadX::isSleepMode()
{
	bool f;
	{
		boost::mutex::scoped_lock lock(m_mutex4Working);
		f = m_isSleepMode;
	}
	return f;
}


void ThreadX::wakeupToWork()
{
	boost::mutex::scoped_lock lock(m_mutex4Working);
	m_isSleepMode = false;
	m_condition4Working.notify_one();
}

void ThreadX::goToSleep()
{
	boost::mutex::scoped_lock lock(m_mutex4Working);
	m_isSleepMode = true;
}

void ThreadX::initFrmFreq2Log(const ThreadTaskId tid )
{
	CfgLog cfg = m_cfg->getLog();
	if (tid >= 0 && tid < THD_TASK_COUNT) {
		m_frmFreqToLog = cfg.vFrmFreqToLog[tid];
	}
	else{
		m_frmFreqToLog = 1000;
	}
}
