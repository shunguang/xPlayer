/*
*------------------------------------------------------------------------
*RunGui.cpp
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
* RunGui.cpp
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
#include "RunGui.h"
using namespace std;
using namespace xPlayer;
RunGui::RunGui(CfgPtr& cfg, QWidget* parent)
	: m_cfg(cfg)
	, m_dcUI(0)
	, m_quitProgDlg(0)
	, m_guiReady(false)
	, m_ui(new AppGui())
{

	m_dcUI.reset(new DcUI(cfg));

	//--------------------------------------------------------------------
	//create other object
	//--------------------------------------------------------------------

	//start GUI
	m_ui->setupUi(this, m_cfg);

	//Menu item actions
	QObject::connect(m_ui->m_actionExit, SIGNAL(triggered()), this, SLOT(on_actionExit_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionAbout, SIGNAL(triggered()), this, SLOT(on_actionAbout_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionMinSz, SIGNAL(triggered()), this, SLOT(on_actionMinImgSz_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionMaxSz, SIGNAL(triggered()), this, SLOT(on_actionMaxImgSz_triggered()), MY_QT_CONN);
	QObject::connect(m_ui->m_actionHelp, SIGNAL(triggered()), this, SLOT(on_actionHelp_triggered()), MY_QT_CONN);
	
	QObject::connect(m_ui->m_vPushButtons[PB_START_EXIT], SIGNAL(clicked()), this, SLOT(on_pushButton_startExit_clicked()), MY_QT_CONN);
	QObject::connect(m_ui->m_vPushButtons[PB_IMG_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushButton_imgFolder_clicked()), MY_QT_CONN);
	QObject::connect(m_ui->m_vPushButtons[PB_MP3_FOLDER], SIGNAL(clicked()), this, SLOT(on_pushButton_mp3Folder_clicked()), MY_QT_CONN);

	QObject::connect(m_ui->m_vLineEdits[LE_IMG_FOLDER], SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_imgFolder_edited(const QString &)), MY_QT_CONN);
	QObject::connect(m_ui->m_vLineEdits[LE_MP3_FOLDER], SIGNAL(textEdited(const QString &)), this, SLOT(on_lineEdit_mp3Folder_edited(const QString &)), MY_QT_CONN);

	QObject::connect(m_ui->m_comboBoxPlaySpeed, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBoxPlaySpeed_currentIndexChanged(int)), MY_QT_CONN);


	THREAD_SLEEP(100);
	m_guiReady = true;
}


RunGui::~RunGui()
{
}


void RunGui::on_actionHelp_triggered()
{
	std::vector<std::string> v;

	v.push_back("=== xPlayer ===");
	v.push_back("  A frame work to play image/videos");
	v.push_back("with AI and internet searching ability.");
	v.push_back("           2020/12/28");

	std::string s = "\n";
	for (int i = 0; i < v.size(); ++i) {
		s += v[i] + "\n";
	}

	QMessageBox::information(this, POPUP_MSG_WIN_TITLE, QString::fromStdString(s));

}
void RunGui::on_actionAbout_triggered()
{
	QMessageBox::information(this, POPUP_MSG_WIN_TITLE, " xPlayer\n          Shunguang.Wu@gmail.com 2020.         ");
}


void RunGui::closeEvent(QCloseEvent* event)
{
	QMessageBox::StandardButton resBtn = QMessageBox::question(this, tr(POPUP_MSG_WIN_TITLE),
		tr("Do you really want to close?\n"),
		QMessageBox::No | QMessageBox::Yes,
		QMessageBox::Yes);

	if (resBtn != QMessageBox::Yes) {
		event->ignore();
	}
	else {
		on_actionExit_triggered();
		//event->accept();
	}
}

void RunGui::createQuitDlg()
{

	m_quitProgDlg.reset(new ProgDialog("Starting ...", 0, 0, 300, 100));
	m_quitProgDlg->reset();
	m_quitProgDlg->resize(200, 100);
	m_quitProgDlg->resetWinTitle("Preparing Quit");
}

void RunGui::closeQuitDlg()
{
	m_quitProgDlg->setProgress(100, "Successfully clean up!");
	boost::this_thread::sleep(boost::posix_time::milliseconds(100));
	QApplication::quit();
}

void RunGui::on_actionExit_triggered()
{
	createQuitDlg();
	m_quitProgDlg->setProgress(50, "Trerminal internal threads ...");
	//todo: clear up other stuff for future extention
	closeQuitDlg();
}

void RunGui::on_actionMinImgSz_triggered()
{
	m_ui->setGuiState(APP_GUI_MIN);
	m_ui->resetGui();
}

void RunGui::on_actionMaxImgSz_triggered()
{
	m_ui->setGuiState(APP_GUI_MAX);
	m_ui->resetGui();
}

//Control box buttons
void RunGui::on_comboBoxPlaySpeed_currentIndexChanged(int idx)
{
}

void RunGui::on_lineEdit_imgFolder_edited(const QString &s)
{
	m_cfg->updateImgRoodFolder( s.toStdString() );
}

void RunGui::on_lineEdit_mp3Folder_edited(const QString &s)
{
	m_cfg->updateMp3RoodFolder(s.toStdString());
}

void RunGui::on_pushButton_imgFolder_clicked()
{
	CfgSliderShow prm = m_cfg->getSliderShow();

	QString initFolder = QString::fromStdString( prm.imgRootFolder );
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Image Folder"), initFolder,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	m_ui->m_vLineEdits[LE_IMG_FOLDER]->setText(dir);

	on_lineEdit_imgFolder_edited(dir);
}

void RunGui::on_pushButton_mp3Folder_clicked()
{
	CfgSliderShow prm = m_cfg->getSliderShow();

	QString initFolder = QString::fromStdString(prm.mp3RootFolder);
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Mp3 Folder"), initFolder,
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	m_ui->m_vLineEdits[LE_MP3_FOLDER]->setText(dir);

	on_lineEdit_mp3Folder_edited(dir);
}

void RunGui::on_pushButton_startExit_clicked()
{
	if ('S' == m_ui->getStartExitState()) {
		m_ui->setStartExitState('E');
		startCapThread();
	}
	else {
		on_actionExit_triggered();
	}
}

//this viritual function is implemented in RunXPlayer class
void RunGui::startCapThread()
{
	return;
}