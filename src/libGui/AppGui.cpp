/*
*------------------------------------------------------------------------
*AppGui.cpp
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
#include "AppGui.h"

using namespace std;
using namespace xPlayer;

AppGui::AppGui()
	: m_cfg(0)
	, m_startExitState('S')
	, m_guiState(APP_GUI_MIN)
{
	//defined in appGuiRc.qrc
	//Q_INIT_RESOURCE(appGuiRc);
	initMyResource();  //this way solve the name space issue

	//some of them are not used, but would like to keep for future extentions
	m_vQPixmap[RES_IMG_RED_BOX]	= QPixmap(QString::fromUtf8(":/Resource/red_box.png"));
	m_vQPixmap[RES_IMG_GRN_BOX]	= QPixmap(QString::fromUtf8(":/Resource/green_box.png"));
	m_vQPixmap[RES_IMG_YEL_BOX] = QPixmap(QString::fromUtf8(":/Resource/yellow_box.png"));
	m_vQPixmap[RES_IMG_GRY_BOX] = QPixmap(QString::fromUtf8(":/Resource/gray_box.png"));
	m_vQPixmap[RES_IMG_LOGO]	= QPixmap(QString::fromUtf8(":/Resource/appLogo.png"));
	m_vQPixmap[RES_IMG_INIT]	= QPixmap(QString::fromUtf8(":/Resource/initScreen.jpg"));
	m_vQPixmap[RES_IMG_DEFAULT] = QPixmap(QString::fromUtf8(":/Resource/defaultImg.jpg"));
}

void AppGui::resetGui()
{
	//CfgGui prm = m_cfg->getGui();
	resizeGuiWin( m_guiState );
	resizeLogoAndCtrlPanel( m_guiState );
}

void AppGui::setupUi(QMainWindow *mainWin, CfgPtr &cfg)
{
	m_mainWin = mainWin;
	m_cfg = cfg;

	//define main window 
	if (m_mainWin->objectName().isEmpty()) {
		m_mainWin->setObjectName(QStringLiteral("mainWin"));
	}

	m_mainWin->setAnimated(false);

	//set central Widget
	m_centralWidget = new QWidget(m_mainWin);
	m_centralWidget->setObjectName(QStringLiteral("m_centralWidget"));
	m_mainWin->setCentralWidget(m_centralWidget);

	setupMenu();
	setupGroupBoxs();
	setupGuiTexts();

	initSettings();

	//after setup
	setGuiState(APP_GUI_MIN);
	resetGui();
	QMetaObject::connectSlotsByName(mainWin);
}

void AppGui::setupGroupBoxs()
{
	for (int i = 0; i < GRP_BOX_CUNT; i++) {
		m_vGrpBoxs[i] = new QGroupBox(m_centralWidget);
		m_vGrpBoxs[i]->setObjectName(QString::fromStdString(g_vGrpBoxName[i]));
	}

	QString name;
	m_imgLabel = new ImgLabel(m_vGrpBoxs[GRP_BOX_IMG]);
	m_imgLabel->setObjectName(QStringLiteral("m_imgLabel"));
	m_imgLabel->setEnabled(true);

	//bottom right panel
	m_labelLogo = new QLabel(m_vGrpBoxs[GRP_BOX_CTRL]);
	m_labelLogo->setObjectName(QStringLiteral("m_labelLogo"));
	m_labelLogo->setEnabled(true);
	m_labelLogo->setCursor(QCursor(Qt::ArrowCursor));
	//m_labelLogo->setAutoFillBackground(true);
	m_labelLogo->setScaledContents(true);
	m_labelLogo->setAlignment(Qt::AlignCenter);

	//pushbuttons
	QGroupBox *pGrpBoxCtrl = m_vGrpBoxs[GRP_BOX_CTRL];
	for (int i = 0; i < PB_CUNT; ++i) {
		m_vPushButtons[i] = new QPushButton(pGrpBoxCtrl);
		m_vPushButtons[i]->setObjectName( QString::fromStdString(g_vPushButtonName[i]) );
	}
	
	//line edits
	for (int i = 0; i < LE_CUNT; ++i) {
		m_vLineEdits[i] = new QLineEdit(pGrpBoxCtrl);
		m_vLineEdits[i]->setObjectName(QString::fromStdString(g_vLineEditName[i]));
	}

	//comb
	m_comboBoxPlaySpeed = new QComboBox(pGrpBoxCtrl);
}

void AppGui::initSettings()
{
	CfgGui prm = m_cfg->getGui();
	CfgSliderShow pp = m_cfg->getSliderShow();

	for (const auto &e : prm.vSpeadCombo ) {
		m_comboBoxPlaySpeed->addItem(QString::fromStdString(e) );
	}
	m_comboBoxPlaySpeed->setCurrentIndex(1);
	m_cfg->updateFrameInterval(prm.vFrmInterval[1]);

	m_labelLogo->setPixmap(m_vQPixmap[RES_IMG_LOGO].scaled(prm.logoSz.w, prm.logoSz.h, Qt::IgnoreAspectRatio));

	m_vLineEdits[LE_IMG_FOLDER]->setText( QString::fromStdString(pp.imgRootFolder) );
	m_vLineEdits[LE_MP3_FOLDER]->setText(QString::fromStdString(pp.mp3RootFolder) );
}

void AppGui::setupMenu()
{
	//menu actions
	m_actionExit = new QAction(m_mainWin);
	m_actionExit->setObjectName(QStringLiteral("m_actionExit"));
	m_actionExit->setCheckable(false);
	QIcon icon;
	icon.addFile(QStringLiteral(":/libGui/Resources/exit_icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
	m_actionExit->setIcon(icon);

	m_actionAbout = new QAction(m_mainWin);
	m_actionAbout->setObjectName(QStringLiteral("m_actionAbout"));
	m_actionAbout->setCheckable(true);

	m_actionHelp = new QAction(m_mainWin);
	m_actionHelp->setObjectName(QStringLiteral("m_actionHelp"));
	m_actionHelp->setCheckable(true);

	m_actionMinSz = new QAction(m_mainWin);
	m_actionMinSz->setObjectName(QStringLiteral("m_actionMinSz"));
	m_actionMinSz->setCheckable(true);

	m_actionMaxSz = new QAction(m_mainWin);
	m_actionMaxSz->setObjectName(QStringLiteral("m_actionMaxSz"));
	m_actionMaxSz->setCheckable(true);

	//menu bar
	m_menuBar = new QMenuBar(m_mainWin);
	m_menuBar->setObjectName(QStringLiteral("m_menuBar"));
	m_menuBar->setNativeMenuBar(false);

	//File
	m_menuFile = new QMenu(m_menuBar);
	m_menuFile->setObjectName(QStringLiteral("m_menuFile"));

	//Help
	m_menuHelp = new QMenu(m_menuBar);
	m_menuHelp->setObjectName(QStringLiteral("m_menuHelp"));

	m_mainWin->setMenuBar(m_menuBar);
	//mainToolBar = new QToolBar(mainWin);
	//mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
	//mainWin->addToolBar(Qt::TopToolBarArea, mainToolBar);
	//statusBar = new QStatusBar(mainWin);
	//statusBar->setObjectName(QStringLiteral("statusBar"));
	//mainWin->setStatusBar(statusBar);

	//add actions to menu bar
	m_menuBar->addAction(m_menuFile->menuAction());
	m_menuBar->addAction(m_menuHelp->menuAction());

	m_menuFile->addAction(m_actionExit);

	m_menuHelp->addAction(m_actionHelp);
	m_menuHelp->addAction(m_actionMinSz);
	m_menuHelp->addAction(m_actionMaxSz);
	m_menuHelp->addSeparator();
	m_menuHelp->addAction(m_actionAbout);
}

void AppGui::setupGuiTexts()
{
	m_mainWin->setWindowTitle(QApplication::translate("mainWin", "XPlayer (v1.0)", 0));
	m_actionExit->setText(QApplication::translate("mainWin", "E&xit", 0));
	m_actionAbout->setText(QApplication::translate("mainWin", "A&bout", 0));
	m_actionHelp->setText(QApplication::translate("mainWin", "H&elp", 0));
	m_actionMinSz->setText(QApplication::translate("mainWin", "Mi&nimum Size", 0));
	m_actionMaxSz->setText(QApplication::translate("mainWin", "M&aximum Size", 0));

	m_menuFile->setTitle(QApplication::translate("mainWin", "&File", 0));
	m_menuHelp->setTitle(QApplication::translate("mainWin", "&Help", 0));

	for (int i = 0; i < PB_CUNT; ++i) {
		m_vPushButtons[i]->setText(QApplication::translate("mainWin", g_vPushButtonName[i].c_str(), 0));
	}
}

void AppGui::resizeLogoAndCtrlPanel(const AppGuiState state)
{
	const int buttonW = 110;

	int x=0, y=0, h=25;
	int b = 5;
	int w = 100;				 //button width
	
	CfgGui prm = m_cfg->getGui();

	const int ctrlGrpW = m_vGrpBoxs[GRP_BOX_CTRL]->width();
	const int ctrlGrpH = m_vGrpBoxs[GRP_BOX_CTRL]->height();
	const int lineEditW = ctrlGrpW - prm.logoSz.w - 2*w - 6*b-20;	//line edit width

	//bottom left -- logo
	x = b; y = b; 
	m_labelLogo->setGeometry(0, 0, prm.logoSz.w, prm.logoSz.h);

	const int x1 = b + prm.logoSz.w + b;

	//image folder
	x = x1; y = b; w = buttonW;
	m_vPushButtons[PB_IMG_FOLDER]->setGeometry(x, y, w, h);
	x += w+b;
	m_vLineEdits[LE_IMG_FOLDER]->setGeometry(x, y, lineEditW, h);
	
	//mp3 folder
	x = x1;  y += h;
	m_vPushButtons[PB_MP3_FOLDER]->setGeometry(x, y, w, h);
	x += w+b;
	m_vLineEdits[LE_MP3_FOLDER]->setGeometry(x, y, lineEditW, h);
	
	//combBox
	const int x2 = x1 +  b + buttonW + b + lineEditW + b;
	x = x2; y = b;
	m_comboBoxPlaySpeed->setGeometry(x, y, w, h);

	//start/exit button
	y += h;
	m_vPushButtons[PB_START_EXIT]->setGeometry(x, y, w, h);
}

//need to update <m_lv> before calling this function
void AppGui::resizeGuiWin( const AppGuiState state )
{
	CfgGui prm = m_cfg->getGui();

	ImgSize szGui;		//sz of the whole gui
	ImgSize szImg;		//sz of dsp img
	ImgSize ctrlGrpSz;		//sz of dsp img
	if (APP_GUI_MIN == state) {
		szGui = prm.minGuiWinSz;
		szImg = prm.getMinDispImgSz();
		ctrlGrpSz = prm.getMinCtrlGrpSz();
	}
	else {
		szGui = prm.maxGuiWinSz;
		szImg = prm.getMaxDispImgSz();
		ctrlGrpSz = prm.getMaxCtrlGrpSz();
	}

	int b = 2;
	int x = b, y = b;
	
	m_mainWin->setGeometry( 0, 0, szGui.w, szGui.h );
	m_mainWin->setMaximumSize(szGui.w, szGui.h);
	m_mainWin->setMinimumSize(prm.minGuiWinSz.w, prm.minGuiWinSz.h);
	m_mainWin->resize(szGui.w, szGui.h);

	m_centralWidget->setGeometry(0, 0, szImg.w, szImg.h);
	m_menuBar->setGeometry(QRect(b, b, szGui.w, prm.menuBarH));

	m_vGrpBoxs[GRP_BOX_IMG]->setGeometry(0, 0, szImg.w, szImg.h);

	x = b; 
	y = m_vGrpBoxs[GRP_BOX_IMG]->height() + b;
	m_vGrpBoxs[GRP_BOX_CTRL]->setGeometry(x, y, ctrlGrpSz.w, ctrlGrpSz.h);

	m_imgLabel->setGeometry(0, 0, szImg.w, szImg.h);
	m_imgLabel->setPixmap(m_vQPixmap[RES_IMG_INIT].scaled(szImg.w, szImg.h, Qt::IgnoreAspectRatio));
}

void AppGui::showImg( const QPixmap &x)
{
	m_imgLabel->setPixmap(x);
}
