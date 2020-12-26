/*
*------------------------------------------------------------------------
*test_xEyes.cpp
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
#include "libUtil/util.h"
#include "libCfg/Cfg.h"

#include "libRun/RunCap.h"
#include "libRun/RunGui.h"
//#include "libRun/RunXPlayer.h"

using namespace std;
using namespace xPlayer;
string locateCfgFile( int argc, char **argv);
void   startLog( const CfgPtr cfg );
void showUsage();

int test_xPlayer(int argc, char **argv)
{
	//figure out config file
	string cfgFile = locateCfgFile( argc, argv );
	printf("used cfg=<%s>\n", cfgFile.c_str());

	//read cfg file
	CfgPtr cfg( new Cfg() );
	try{
		cfg->readFromFile(cfgFile.c_str());
	}
	catch (const std::overflow_error& e){
		printf("%s\n", e.what());	
	}
	printf("cfg read successfully\n" );

	//start log thread
	startLog( cfg );
	
	//cudaDeviceInit(0, NULL);


	int appRet = 0;
	QApplication app(argc, argv);
	QFont font;
	font.setFamily(font.defaultFamily());
	font.setPointSize(9);
	app.setFont(font);

	int testFlag = 1;
	if (testFlag == 0) {
		RunCap x(cfg);
		x.start();
	}
	else if (testFlag == 1) {
		RunGui x(cfg);
		x.show();
		appRet = app.exec();
	}
	else if (testFlag == 2) {
		//RunXPlayer x(cfg);
		//x.show();
		//appRet = app.exec();
	}

	endLogThread();
	return 0;
}

string locateCfgFile( int argc, char **argv)
{
	string cfgFile="";
	if (argc < 2) {
		string f0 = "cfg_xPlayer.xml";
		string cfgFile1 = "./" + f0;            //for development
		if (boost::filesystem::exists(cfgFile1)) {
			cfgFile = cfgFile1;
		}
		else {								   //cfg at install folder
#if _WINDOWS
			cfgFile = "c:/Projects/xPlayer/src/unitTest/res/" + f0;            //for development
#else
			cfgFile = "/home/swu/projects/xPlayer/src/unitTest/res/" + f0;            //for development
#endif
		}
	}
	else { //from cmd line
		cfgFile = string(argv[1]);
	}

	if (!boost::filesystem::exists(cfgFile)){
		printf("Error: Config file <%s> does not exit!", cfgFile.c_str());
		showUsage();
	}
	return cfgFile;
}

void   startLog( const CfgPtr cfg )
{
	//--------------------------------------------------------------------
	//create log file
	//--------------------------------------------------------------------
	CfgLog log = cfg->getLog();
	myCreateDir( log.logFolder );
	string ymd0 = ""; // getPrettyTimeStamp();
	string logFile = log.logFolder + "/log" + ymd0 + ".txt";
	startLogThread(logFile, true, true);

	//dump current cfg into log file
	dumpLog("----------cfg----------------");
	string cfgStr = cfg->toString();
	std::vector<std::string> v;
	string_to_vector2(v, cfgStr, "\n", false);
	BOOST_FOREACH(const std::string &s, v){
		dumpLog(s);
	}
	//SetLoggerShowInConsoleFlag( log.ishowLogInConsole);
	//SetLoggerIsDumpFlag( log.isDumpLog);
	dumpLog("-------start main program ---------");
}
void showUsage()
{
	printf("usage: ./xplayer [cfg_file_path]\n");
	printf("Note:\n");
	printf("<./xplayer> will check config files by the following order:\n");
	printf("  [1] ~/Projects/xPlayer/src/unitTest/res/cfg_xPlayer.xml\n");
	printf("  [2] ./cfg_xPlayer.xml (from deployed machine)\n");
}

