/*
*------------------------------------------------------------------------
*RunXEyes.h
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
* RunGui.h
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
#ifndef __RUN_XEYES_H__
#define __RUN_XEYES_H__

#include "libCap/CapThreadBase.h"
#include "libDet/DetThreadBase.h"
#include "libDsp/DspThread.h"

#include "RunGui.h"

namespace xPlayer {
	class RunXEyes : public RunGui
	{
		Q_OBJECT

	public:
		//all the threads share the same cfg located at only one physical address
		RunXEyes(CfgPtr& cfg, QWidget* parent = 0);
		virtual ~RunXEyes();

	protected slots:
		virtual void on_actionExit_triggered();
		void		 respns_dispImg0();  //disp img from shared data: <m_sharedDC>
		void		 respns_dispImg1();  //disp img from shared data: <m_sharedDC>
		void		 respns_dispImg2();  //disp img from shared data: <m_sharedDC>
		void		 respns_dispImg3();  //disp img from shared data: <m_sharedDC>
	protected:
		void runAllThreads();
		void startCaptureThreads();
		void startDetectionThreads();
		void startDisplayThreads();

		void createCaptureThreads();
		void createDetectionThreads();
		void createDisplayThreads();

		void quitAllThreads();
		void dispImg( const int camIdx );

	protected:
		std::vector<CapThreadBasePtr>	m_vCapThreads;	//caprture thread
		std::vector<DetThreadBasePtr>	m_vDetThreads;	//detection threads
		std::vector<DspThreadPtr>		m_vDspThreads;	//detection threads

		std::vector<int>			m_vCamIds;             //camera IDs, cannot be changed after luanched
		
		std::vector<DspFrm_hPtr>	m_vDspFrm;
		int				 m_threadIdCnt;

	};
}
#endif 

