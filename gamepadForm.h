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
 * This file was modified by Yurii Litvinov, Aleksei Alekseev and Mikhail Wall to make it comply with the requirements of trikRuntime
 * project. See git revision history for detailed changes. */

#pragma once

#include <QMediaPlayer>
#include <QVideoWidget>

#include <QtWidgets/QWidget>
#include <QtWidgets/QMenuBar>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QTimer>
#include <QtCore/QTranslator>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QShortcut>
#include "connectForm.h"

#include "connectionManager.h"
#include <QMovie>

#include "connectionThread.h"

namespace Ui {
class GamepadForm;
}

/// GUI for TRIK Gamepad. Also contains all logic, which is not good, but this code is meant to be simple.
class GamepadForm : public QWidget
{
	Q_OBJECT

public:
	/// Constructor.
	GamepadForm();
	~GamepadForm() override;

public slots:

	/// Slot for opening connect dialog
	void openConnectDialog();

	/// Slot for exit menu item
	void exit();

	/// Slot for about menu item
	void about();

private slots:

	/// Slots for gamepad "magic" buttons.
	void onButtonPressed(int buttonId);
	void handleDigitPress(QWidget*);
	void handleDigitRelease(QWidget*);

	/// Slots for pad buttons (Up, Down, Left, Right), triggered when button is pressed.
	void onPadPressed(const QString &action);
	void handlePadPress(QWidget*);

	/// Slots for pad buttons (Up, Down, Left, Right), triggered when button is released.
	void onPadReleased(int padId);
	void handlePadRelease(QWidget*);

	/// Slot for handle key pressing and releasing events
	bool eventFilter(QObject *obj, QEvent *event);

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

private:
	void setButtonChecked(const int &key, bool ckeckStatus);
	/// Helper method that enables or disables gamepad buttons depending on connection state.
	void setButtonsEnabled(bool enabled);
	void setButtonsCheckable(bool checkableStatus);
	void setUpControlButtonsHash();
	void setLabels();

	/// Field with GUI automatically generated by gamepadForm.ui.
	Ui::GamepadForm *mUi;

	/// For opening dialog from gamepadForm
	ConnectForm *mMyNewConnectForm;

	/// For creating menu bar
	QMenuBar *mMenuBar;

	/// For creating connection menu
	QMenu *mConnectionMenu;
	QMenu *mLanguageMenu;

	/// Menu actions
	QAction *mConnectAction;
	QAction *mExitAction;
	QAction *mAboutAction;

	/// Languages actions
	QAction *mRussianLanguageAction;
	QAction *mEnglishLanguageAction;
	QAction *mFrenchLanguageAction;
	QAction *mGermanLanguageAction;

	QActionGroup *mLanguages;

	/// For setting up translator in app
	QTranslator *mTranslator;

	/// Set for saving pressed keys
	QSet<int> mPressedKeys;

	QHash<int, QPushButton*> controlButtonsHash;

	QShortcut *shortcut;
	/// For changing language whem another language was chosen
	void retranslate();

	/// For catching up event when language was changed
	void changeEvent(QEvent *event);

	QHash<QWidget*, QVector<int>> mPadHashtable;
	QHash<QWidget*, int> mDigitHashtable;
	QSignalMapper *mMapperPadPressed;
	QSignalMapper *mMapperPadReleased;
	QSignalMapper *mMapperDigitPressed;
	QSignalMapper *mMapperDigitReleased;

	/// Class that handles network communication with TRIK.
	ConnectionManager connectionManager;
	QMediaPlayer *player;
	QVideoWidget *videoWidget;
	QMovie movie;

	ConnectionThread connectionThread;
};
