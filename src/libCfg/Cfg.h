/*
*------------------------------------------------------------------------
*Cfg.h
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
#ifndef __CFG_H__
#define __CFG_H__

#include "CfgLog.h"
#include "CfgSliderShow.h"
#include "CfgGui.h"
#include "CfgDefs.h"
namespace xPlayer {
	class CFG_EXPORT Cfg {
	public:
		Cfg();

		void readFromFile(const char *fname);
		void writeToFile(const char *fname);
		std::string toString();

		CfgLog			getLog();
		CfgSliderShow	getSliderShow();
		CfgGui			getGui();

		void updateImgRoodFolder(const std::string &newFolder) {
			boost::mutex::scoped_lock lock(m_mutex);
			m_sliderShow->imgRootFolder_ = newFolder;
		}

		void updateMp3RoodFolder(const std::string &newFolder) {
			boost::mutex::scoped_lock lock(m_mutex);
			m_sliderShow->mp3RootFolder_ = newFolder;
		}

		void updateFrameInterval( const int dt_ms) {
			boost::mutex::scoped_lock lock(m_mutex);
			m_sliderShow->frameInterval_ms_ = dt_ms;
		}

	private:
		boost::property_tree::ptree toPropertyTree();
		void fromPropertyTree(const boost::property_tree::ptree &pt) ;

	protected:
		CfgSliderShowPtr			m_sliderShow;   //slider Show
		CfgLogPtr					m_log;   		//log
		CfgGuiPtr					m_gui;
		boost::mutex				m_mutex;
	};

	typedef std::shared_ptr<Cfg>		CfgPtr;
}
#endif
