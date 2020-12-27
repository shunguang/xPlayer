/*
*------------------------------------------------------------------------
*CapThreadBase.h
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
//This is teh base class for capture threads
#ifndef __CAP_THREAD_H__
#define __CAP_THREAD_H__
#include "libUtil/util.h"
#include "libDc/ThreadX.h"
#include "libDc/RgbFrm_h.h"
#include "CapDefs.h"
namespace xPlayer {
	class DspThread;
	class CAP_EXPORT CapThread : public ThreadX
	{
	public:
		CapThread( const int threadId=0, const std::string &threadName="unkn");
		CapThread( const CapThread &x) = delete;
		virtual ~CapThread();
		void setDspPtr( DspThread *p );

		void updateFrmInterval(int dt_ms) {
			m_frmInterval_ms = dt_ms;
		}

	protected:
		//set <isEmitSignal> as false when doing single thread none GUI test
		virtual void procNextTask();
		virtual bool procInit();
		bool loadImg(const std::string &f);
		void listDirRecursively(const char* rootDir, const std::vector<std::string> &vExt);

	protected:
		uint64_t		m_frmNum;
		std::atomic<uint32_t> m_frmInterval_ms;
		cv::Size		m_capSz;

		RgbFrm_hPtr		m_rgbFrm_h;   //output/captured frm from this camera
		DspThread*		m_dspPtr;
		std::vector<std::string> m_vFilenames;
		uint64_t		m_nTotFrms;
	};
	typedef std::shared_ptr<CapThread> CapThreadPtr;
}
#endif 
