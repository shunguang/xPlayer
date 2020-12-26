/*
*------------------------------------------------------------------------
*ThreadQt.h
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
/*
*-------------------------------------------------------------------
* ThreadQt.h
* Copyright(c) 2019, The RgbVideoEditor Author (Shunguang Wu).
* All Rights Reserved.
* You may not use this file except in compliance with the License:
*      GNU GENERAL PUBLIC LICENSE (Version 3), 29 June 2007
*
* You may obtain a copy of the License at
*
*     https://www.gnu.org/licenses/gpl-3.0.en.html
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*-------------------------------------------------------------------
*/
#ifndef __THREAD_QT_H__
#define __THREAD_QT_H__

#include <QtCore/qthread.h>
#include "libUtil/util.h"
#include "libCfg/Cfg.h"
#include "libDc/DcUI.h"
#include "DspDefs.h"
namespace xPlayer {
	class DSP_EXPORT ThreadQt : public QThread {
		Q_OBJECT
	public:
		ThreadQt(const ThreadTaskId tid= THD_TASK_DSP, const int threadId=0, const std::string &name="unkn" );
		virtual ~ThreadQt();

		void forceQuit();        //force thread quit from its inifinity loop

		void wakeupToWork();     //wake up thread to  procNextTask()
		void goToSleep();        //ask thread go to sleep
		bool isExitedLoop();
		bool isSleepMode();

		void setCfg( CfgPtr  &cfg );
		void setDcUI( DcUIPtr &dcUI );

	protected:
		void setExitedLoopFlag(const bool f);
		void setRcvdExitLoopCmdFlag(const bool f);
		bool isRcvdExitLoopCmd();

		virtual void procNextTask() = 0;
		virtual bool procInit() = 0;

		void run() Q_DECL_OVERRIDE;            //must be named run() at here
		void initFrmFreq2Log( const ThreadTaskId id );

	public:
		ThreadTaskId	m_taskId;
		int 			m_threadId;		//for debugging purpose
		std::string		m_threadName;	//for debugging purpose

	protected:
		CfgPtr			m_cfg;			//cfg ptr
		DcUIPtr			m_dcUI;			//shared data pointer
		int             m_frmFreqToLog;

		bool    		m_isExitedLoop;
		bool			m_isSleepMode;
		bool    		m_rcvdExitLoopCmd;

		boost::mutex					 m_mutex4Working;
		boost::condition_variable		 m_condition4Working;
		boost::mutex					 m_mutexLocal;
	};
	typedef std::shared_ptr<ThreadQt>		ThreadQtPtr;
}
#endif
