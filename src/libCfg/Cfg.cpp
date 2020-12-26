/*
*------------------------------------------------------------------------
*Cfg.cpp
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
#include "Cfg.h"
using namespace std;
using namespace xPlayer;

Cfg::Cfg()
	: m_sliderShow(new CfgSliderShow())
	, m_log(new CfgLog())
{
}

void Cfg::readFromFile(const char *fname)
{
	boost::property_tree::ptree pt;
	boost::property_tree::xml_parser::read_xml( fname, pt);
	this->fromPropertyTree(pt.get_child("cfg"));
	printf("xml read done!\n");
}

void Cfg::writeToFile(const char *fname)
{
	boost::property_tree::ptree pt = toPropertyTree();
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(fname, pt, std::locale(), settings);
}

std::string Cfg::toString()
{
	boost::property_tree::ptree pt = toPropertyTree();

	std::ostringstream oss;
	boost::property_tree::xml_parser::xml_writer_settings<std::string> settings(' ', 4);
	boost::property_tree::xml_parser::write_xml(oss, pt, settings);
	return oss.str();
}

void Cfg::fromPropertyTree(const boost::property_tree::ptree &pt0)
{
	m_sliderShow->fromPropertyTree(pt0.get_child("slidershow"));
	m_log->fromPropertyTree(pt0.get_child("log"));
}


boost::property_tree::ptree Cfg::toPropertyTree()
{
	boost::property_tree::ptree ptLog = m_log->toPropertyTree();
	boost::property_tree::ptree ptSliderShow = m_sliderShow->toPropertyTree();
	boost::property_tree::ptree pt;
	pt.add_child("cfg.slidershow", ptSliderShow);
	pt.add_child("cfg.log", ptLog);

	return pt;
}


CfgLog Cfg::getLog() 
{
	CfgLog ret;
	{
		boost::mutex::scoped_lock lock(m_mutex);
		ret = *(m_log.get());
	}
	return ret;
}

CfgSliderShow Cfg::getSliderShow()
{
	CfgSliderShow ret;
	{
		boost::mutex::scoped_lock lock(m_mutex);
		ret = *(m_sliderShow.get());
	}
	return ret;
}
