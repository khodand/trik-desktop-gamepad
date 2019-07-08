/* Copyright 2015-2016 CyberTech Labs Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * This file was modified by Yurii Litvinov, Aleksei Alekseev, Mikhail Wall and Konstantin Batoev
 * to make it comply with the requirements of trikRuntime project.
 * See git revision history for detailed changes. */

#pragma once

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimediaWidgets/QVideoWidget>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenuBar>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QTimer>
#include <QtCore/QTranslator>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QShortcut>
#include <QtGui/QMovie>
#include <QtCore/QThread>

#include <QtMultimedia/QVideoProbe>
#include <QtGui/QClipboard>

#include "connectForm.h"

#include "connectionManager.h"
#include "strategy.h"

namespace Ui {
class GamepadForm;
}

/// GUI for TRIK Gamepad. Also contains all logic, which is not good, but this code is meant to be simple.
class GamepadForm : public QWidget
{
	Q_OBJECT

private:
	GamepadForm(const GamepadForm &other);
	GamepadForm & operator=(const GamepadForm &other);

public:
	/// Constructor.
	GamepadForm();
	~GamepadForm() override;
	/// method that sets up connection manager and connect to host
	void startController(QStringList args);

public slots:

	/// Slot for opening connect dialog
	void openConnectDialog();

	/// Slot for exit menu item
	void exit();

	/// Slot for about menu item
	void about();

private slots:

	/// Slots for pad buttons (Up, Down, Left, Right) and "magic" buttons, triggered when button is pressed.
	void handleButtonPress(QWidget*);

	/// Slots for pad buttons (Up, Down, Left, Right) and "magic" buttons, triggered when button is released.
	void handleButtonRelease(QWidget*);

	/// Slot for handle key pressing and releasing events
	bool eventFilter(QObject *obj, QEvent *event) override;

	/// Slot for creating menu bar
	void createMenu();

	/// Slot for creating connections between buttons and events
	void createConnection();

	/// Slot for changing languages, triggered when click on needed language
	void changeLanguage(const QString &language);

	/// Helper method for setting up gamepadForm
	void setUpGamepadForm();

	/// Helper method for setting Video Widget
	void setVideoController();

	void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);

	void startVideoStream();

	void checkSocket(QAbstractSocket::SocketState state);

	void startThread();

	void checkBytesWritten(int result);

	void showConnectionFailedMessage();

	void setFontToPadButtons();

	/// slot for sending command prepared by strategy to robot
	void sendCommand(const QString &command);

	/// slot is invoked when user presses mode actions
	void changeMode(Strategies type);

	/// handling application state
	void dealWithApplicationState(Qt::ApplicationState state);

	void saveImageToClipboard(QVideoFrame buffer);
	void requestImage();

signals:
	/// signal to send command
	void commandReceived(QString);
	/// signal to disconnect from host
	void programFinished();
	/// signal to connect to host
	void dataReceivedFromCommandLine();

private:
	void setButtonChecked(const int &key, bool checkStatus);
	/// Helper method that enables or disables gamepad buttons depending on connection state.
	void setButtonsEnabled(bool enabled);
	void setButtonsCheckable(bool checkableStatus);
	void setUpControlButtonsHash();
	void setLabels();
	void setImageControl();

	/// Field with GUI automatically generated by gamepadForm.ui.
	Ui::GamepadForm *mUi;

	/// For opening dialog from gamepadForm
	ConnectForm *mMyNewConnectForm; // TODO [Doesn't have | Has] ownership

	/// For creating menu bar
	QMenuBar *mMenuBar; // TODO [Doesn't have | Has] ownership

	/// For creating connection menu
	QMenu *mConnectionMenu; // TODO [Doesn't have | Has] ownership
	QMenu *mLanguageMenu; // TODO [Doesn't have | Has] ownership
	QMenu *mImageMenu; // TODO [Doesn't have | Has] ownership

	QMenu *mModeMenu; // TODO [Doesn't have | Has] ownership

	/// Menu actions
	QAction *mConnectAction; // TODO [Doesn't have | Has] ownership
	QAction *mExitAction; // TODO [Doesn't have | Has] ownership
	QAction *mAboutAction; // TODO [Doesn't have | Has] ownership

	/// Languages actions
	QAction *mRussianLanguageAction; // TODO [Doesn't have | Has] ownership
	QAction *mEnglishLanguageAction; // TODO [Doesn't have | Has] ownership
	QAction *mFrenchLanguageAction; // TODO [Doesn't have | Has] ownership
	QAction *mGermanLanguageAction; // TODO [Doesn't have | Has] ownership

	QActionGroup *mLanguages; // TODO [Doesn't have | Has] ownership

	/// Image Actions
	QAction *mTakeImageAction; // TODO [Doesn't have | Has] ownership

	/// Mode actions
	QAction *mStandartStrategyAction; // TODO [Doesn't have | Has] ownership
	QAction *mAccelerateStrategyAction; // TODO [Doesn't have | Has] ownership

	QActionGroup *mModesActions; // TODO [Doesn't have | Has] ownership

	/// For setting up translator in app
	QTranslator *mTranslator; // TODO [Doesn't have | Has] ownership

	/// object that encapsulates logic with commands
	Strategy *strategy; // TODO [Doesn't have | Has] ownership


	QHash<int, QPushButton*> controlButtonsHash;

	QShortcut *shortcut; // TODO [Doesn't have | Has] ownership
	/// For changing language whem another language was chosen
	void retranslate();

	/// For catching up event when language was changed
	void changeEvent(QEvent *event) override;

	QSignalMapper *mMapperButtonPressed; // TODO [Doesn't have | Has] ownership
	QSignalMapper *mMapperButtonReleased; // TODO [Doesn't have | Has] ownership

	/// Class that handles network communication with TRIK.
	ConnectionManager connectionManager;
	QThread thread;
	QMediaPlayer *player; // TODO [Doesn't have | Has] ownership
	QVideoWidget *videoWidget; // TODO [Doesn't have | Has] ownership
	QMovie movie;

	QClipboard *clipboard; // TODO [Doesn't have | Has] ownership
	QVideoProbe *probe; // TODO [Doesn't have | Has] ownership
	bool isFrameNecessary;

	QTimer mKeepaliveTimer;
};
