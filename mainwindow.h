#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "crosstypes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	QString parseHEXFileString(QString sHexFileStr);
	QByteArray* getBINX(QString sHEXTXT);

private slots:

	void on_cmdLoadFile_clicked();
	void on_cmdSaveBINX_clicked();

private:
	Ui::MainWindow *ui;

	DWORD	dwLinAddr, dwSegAddr, dwNextAddr, NFrag, NError;

	WORD	GetCRC16(BYTE* pData, ULONG lData);

	__inline BYTE		GetCRC8(BYTE* pData, ULONG lData, BYTE bCRC8=0)
						{
							while(lData--)bCRC8+=(*pData++);
						return(~bCRC8);
						}

	__inline QString	DWORD2Hex(DWORD dwValue)
						{
						return QString("0000000%1").arg(dwValue,0,16).right(8).toUpper();
						}
};

#endif // MAINWINDOW_H
