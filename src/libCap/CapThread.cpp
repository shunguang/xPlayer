/*
*------------------------------------------------------------------------
*CapThread.cpp
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
#include "CapThread.h"
#include "libDsp/DspThread.h"
using namespace std;
using namespace xPlayer;
CapThread::CapThread( const int threadId, const std::string &threadName )
: ThreadX	( THD_TASK_CAP, threadId, threadName )
, m_frmNum(0)
, m_frmInterval_ms(1000)
, m_capSz(0,0)
, m_rgbFrm_h(0)
, m_dspPtr(NULL)
, m_vFilenames()
, m_nTotFrms(0)
{
	cout << "DetThreadBase::CapThread(): called" << endl;
}

CapThread::~CapThread()
{
}

void CapThread::setDspPtr( DspThread *p )
{
	m_dspPtr = p;
}


//only need to one frame 
//todo: compbine with RunThreadS::runLoop() for efficency 
void CapThread::procNextTask()
{
	const boost::posix_time::ptime start = APP_LOCAL_TIME;

	//read <m_rgbFrm_h> from file, make sure we read one
	while (1) {
		if (m_frmNum >= m_nTotFrms) {
			m_frmNum = 0;
		}
		const std::string &f = m_vFilenames[m_frmNum];
		if (loadImg(f)) {
			break;
		}
		m_frmNum++;
	}

	//wrt into queue
	m_dcUI->wrtRgbFrmByCapThread(m_rgbFrm_h.get());
	if (m_dspPtr) {
		m_dspPtr->wakeupToWork();
	}

	//decide if need to sleep
	uint32_t dt = timeIntervalMillisec(start);
	if (dt < m_frmInterval_ms.load() ) {
		THREAD_SLEEP(m_frmInterval_ms.load() - dt);
	}
	if (m_frmNum % m_frmFreqToLog == 0) {
		dumpLog("CapThreadSyn::procNextTask(): %s, fn=%llu, dt=%d", m_threadName.c_str(), m_frmNum, dt);
	}

	//---- for next frm ------------
	m_frmNum++;
}

bool CapThread::procInit()
{
	//get cfg 
	CfgSliderShow cfg = m_cfg->getSliderShow();
	m_capSz = cv::Size(cfg.capImgSz.w, cfg.capImgSz.h);

	//init currrent camera capture params
	m_frmInterval_ms = cfg.frameInterval_ms;
	
	m_rgbFrm_h.reset(new RgbFrm_h(cfg.capImgSz.w, cfg.capImgSz.h));
	//dumpLog( "Rgb: (w=%d,h=%d)", m_rgbFrm_h->w_, m_rgbFrm_h->h_);

	//get absolute filenames from <cfg.imgRoot> folder

	//fill <m_vFilenames>
	std::vector<std::string> vExt;
	vExt.push_back(".JPG");
	vExt.push_back(".PNG");
	vExt.push_back(".BMP");
	listDirRecursively( cfg.imgRootFolder.c_str(), vExt);

	m_nTotFrms = m_vFilenames.size();
	m_frmNum = cfg.frmNumLastTimePlayed;
	if (m_nTotFrms == 0) {
		myExit("CapThread::procInit(): no img files in folder:", cfg.imgRootFolder.c_str());
	}
	return true;
}

bool CapThread::loadImg( const std::string &f ) {

	if (!boost::filesystem::exists(boost::filesystem::path(f))) {
		myExit("CapThread::loadImg(): file <%s> does not exist!", f);
		return false;
	}

	cv::Mat I = cv::imread(f, CV_LOAD_IMAGE_COLOR);
	if (0 == I.rows || 0 == I.cols) {
		m_rgbFrm_h->I_.setTo(cv::Scalar(255, 0, 0));
		cv::putText(m_rgbFrm_h->I_, "Cannot load file:" + f, cv::Point(10, m_capSz.height/2), cv::FONT_HERSHEY_DUPLEX, 2, cv::Scalar(255, 255, 255), 2);
	}
	else {
		cv::resize(I, m_rgbFrm_h->I_, m_capSz);
		//dumpLog("CapThread::loadImg():fn=%d, f=%s, BGR: (w=%d,h=%d)", m_frmNum, f.c_str(), m_rgbFrm_h->I_.cols, m_rgbFrm_h->I_.rows);
	}

	cv::putText(m_rgbFrm_h->I_, std::to_string(m_frmNum) + "/" + std::to_string(m_nTotFrms), cv::Point(10, m_capSz.height- m_capSz.height/20), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 255, 255), 2);
	return true;
}


void CapThread::listDirRecursively(const char* rootDir, const std::vector<std::string> &vExt)
{
	m_vFilenames.clear();
	boost::filesystem::path targetDir(rootDir);
	boost::filesystem::recursive_directory_iterator iter(targetDir), eod;
	BOOST_FOREACH(boost::filesystem::path const& i, make_pair(iter, eod)) {
		if (is_regular_file(i)) {
			string iExt = i.extension().string();
			std::transform( iExt.begin(), iExt.end(), iExt.begin(), ::toupper);
			for (const auto &ext0 : vExt) {
				if ( 0==ext0.compare(iExt) ) {
					m_vFilenames.push_back(i.string());
					break;
				}
			}
		}
	}
}