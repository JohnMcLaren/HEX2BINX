#include <QtWidgets>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	setFixedSize(size());
}

MainWindow::~MainWindow()
{
	delete ui;
}
//----------------------------------------------------------------------------------------
void MainWindow::on_cmdLoadFile_clicked()
{
QString fileName = QFileDialog::getOpenFileName(this,
												tr("Open HEX file.."),
												0,
												tr("HEX Files (*.hex);;All Files (*.*)"));
	if (!fileName.isEmpty())
	{
	QFile file(fileName);

		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, "HEX2BINX",
								 tr("Cannot open file %1:\n%2.").arg(fileName).arg(file.errorString()));
		return;
		}

	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	ui->txtHEXTXT->clear();
	ui->txtHEXTXT->setTextColor(Qt::blue);
	ui->txtHEXTXT->insertPlainText(QFileInfo(fileName).fileName() + " --------------------------------------------------\n");
	ui->txtHEXTXT->setTextColor(Qt::black);
	QString sTMP("");
	dwLinAddr =0; dwSegAddr =0; dwNextAddr =0; NFrag =0; NError =0;
	ui->lblNFrags->setText(QString().sprintf("Fragments: %u", NFrag));
	ui->lblNErrors->setText(QString().sprintf("CRC Errors: %u", NError));

		/* Parse HEX file */
		while(!in.atEnd())
		{
			sTMP =parseHEXFileString(in.readLine());

			if(sTMP.left(12).compare("[Address: 0x", Qt::CaseSensitive) == 0)
			{
				ui->lblNFrags->setText(QString().sprintf("Fragments: %u", ++NFrag));
			}
				else
			if(sTMP.left(12).compare("<CRC Error!>", Qt::CaseSensitive) == 0)
			{
				ui->lblNErrors->setText(QString().sprintf("CRC Errors: %u", ++NError));
			}

			ui->txtHEXTXT->insertPlainText(sTMP);
		}

	QApplication::restoreOverrideCursor();

		setWindowFilePath("HEX2BINX converter v1.0 - " + QFileInfo(fileName).fileName());
		statusBar()->showMessage(tr("File loaded"), 2000);

	file.close();

	if(!NError)
		ui->cmdSaveBINX->setEnabled(TRUE);
	}
}
//-----------------------------------------------------------------------------------
QString MainWindow::parseHEXFileString(QString sHexFileStr)
{
QString sRes ="";
BYTE CRC8 =0;

	sHexFileStr.remove(':');

	for(int c =0; c < sHexFileStr.length(); c +=2)
	{
		CRC8 += sHexFileStr.mid(c, 2).toUShort(0, 16);
	}
//........................................................
	if(CRC8 == 0)
	{
	BYTE bLenData	=sHexFileStr.mid(0, 2).toULong(0, 16);
	DWORD dwOffsAddr=sHexFileStr.mid(2, 4).toULong(0, 16);
	BYTE bTypeRec	=sHexFileStr.mid(6, 2).toULong(0, 16);
	QWORD asd =NULL;
	DWORD dwData	=sHexFileStr.mid(8, bLenData * 2).toULong(0, 16);
	DWORD dwAddress = dwLinAddr + dwSegAddr + dwOffsAddr;

		switch(bTypeRec)
		{
		case 0: // Data

			if(!dwAddress || (dwAddress != dwNextAddr))
			{
				sRes ="[Address: 0x" + DWORD2Hex(dwAddress) + "]\n";
			}

			sRes += (sHexFileStr.mid(8, bLenData * 2) + "\n");
			break;

		case 1: // End Of File record
				sRes = "[End Of File]\n";
			break;

		case 2: // Extended Segment Address Record
				dwSegAddr = dwData << 4; // *16
			break;

		case 3: // Start Segment Address Record
				sRes ="[Start Segment Address: 0x" + DWORD2Hex(dwData) + "]\n";
			break;

		case 4: // Extended Linear Address Record
				dwLinAddr = dwData << 16; // *65536
			break;

		case 5: // Start Linear Address Record
				sRes ="[Start Linear Address: 0x" + DWORD2Hex(dwData) + "]\n";
			break;

		case 32: // ROM code, used by Samsung SAMA assembler
		case 34: // Extension code, used by Samsung Smart Studio microcontroller development system

		default:
			sRes ="<Unknown type record>\n";
		}

		dwNextAddr = dwAddress + bLenData;
	}
	else
		sRes ="<CRC Error!>\n";

return sRes;
}
//------------------------------------------------------------------------------------
void MainWindow::on_cmdSaveBINX_clicked()
{
QByteArray *pBINX;

	if(pBINX =getBINX(ui->txtHEXTXT->toPlainText()))
	{
	QFile file(QFileDialog::getSaveFileName(this, tr("Save BINX file.."), 0, tr("BINX Files (*.binx);;All Files (*.*)")));

		if(!file.fileName().isEmpty())
		{
		file.open(QFile::WriteOnly);

			file.write(*pBINX);

		file.close();
		statusBar()->showMessage(tr("File saved"), 2000);
		ui->cmdSaveBINX->setEnabled(FALSE);
		}

	delete pBINX;
	}
}
//------------------------------------------------------------------------------------
QByteArray* MainWindow::getBINX(QString sHEXTXT)
{
QByteArray* pBINX =NULL;
DWORD dwAddress;
DWORD dwSize =0;
USHORT CRC16;
int iStartBINX =0;
bool bHEXEnd, bParseEnd =false;
QString stmp;
QString sDataHEX;
QTextStream in(&sHEXTXT);

	while(!(bHEXEnd =in.atEnd()) || !bParseEnd)
	{
		if(QRegExp("[0-9A-Z]+").exactMatch(stmp =in.readLine()))	// если данные
		{
			/* add data to buff */
			sDataHEX.append(stmp);
		}
		else														// если директива
		{
		QRegExp regxp("(\\[Address: 0x)([0-9A-F]{8})");
		regxp.indexIn(stmp);

			if(!regxp.cap(1).isEmpty() || (bHEXEnd && !sDataHEX.isEmpty()))	// <[Address: 0x> <OR> <End HEX text>
			{

				if(!pBINX)
					pBINX = new QByteArray;

				if(!sDataHEX.isEmpty())
				{
					dwSize =pBINX->size();	// capt size
					/* add Data */
					pBINX->append(QByteArray::fromHex(sDataHEX.toLatin1()));
					/* calc BINX block size */
					dwSize =(pBINX->size() - dwSize) + (4 + 4 + 2); // Data size + BINX header size + CRC16 size
					//pBINX->replace(iStartBINX, 4, (char*)&dwSize, 4); // Qt equivalent memcpy
					memcpy(pBINX->data() + iStartBINX, &dwSize, 4); // set real BINX block size
					/* calc and add CRC BINX block */
					CRC16 =GetCRC16((BYTE*)(pBINX->data() + iStartBINX), dwSize - 2);
					pBINX->append((char*)&CRC16, 2);

					iStartBINX +=dwSize;
				/* clear data buff*/
				sDataHEX.clear();
				}

				/* construct BINX header */
				pBINX->append("\0\0\0\0", 4);				// insert BINX block size = 0

				if(!bHEXEnd)
				{
					dwAddress =regxp.cap(2).toUInt(0, 16);
					pBINX->append((char*)&dwAddress, 4);	// insert address for BINX data
				}
				else
					bParseEnd =true;	// HEX text finished
			}
		}
	}

return pBINX;
}
//-------------------------------------------------------
WORD MainWindow::GetCRC16(BYTE* pData, ULONG lData) // lData in bytes!
{
register DWORD sum =0;

	for(; lData > 1; lData -= 2)
	{
		sum += *(WORD*)pData++;
	}

	if(lData > 0)
		sum += *pData;

	/*  Fold 32-bit sum to 16 bits */
	while(sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

return((WORD)~sum);
}
//-------------------------------------------------------
