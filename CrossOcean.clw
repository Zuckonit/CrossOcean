; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCrossOceanView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CrossOcean.h"
LastPage=0

ClassCount=6
Class1=CCrossOceanApp
Class2=CCrossOceanDoc
Class3=CCrossOceanView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=GAMESET
Resource3=IDD_DIALOG1

[CLS:CCrossOceanApp]
Type=0
HeaderFile=CrossOcean.h
ImplementationFile=CrossOcean.cpp
Filter=N

[CLS:CCrossOceanDoc]
Type=0
HeaderFile=CrossOceanDoc.h
ImplementationFile=CrossOceanDoc.cpp
Filter=N

[CLS:CCrossOceanView]
Type=0
HeaderFile=CrossOceanView.h
ImplementationFile=CrossOceanView.cpp
Filter=C
LastObject=CCrossOceanView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=IDM_SAVE




[CLS:CAboutDlg]
Type=0
HeaderFile=CrossOcean.cpp
ImplementationFile=CrossOcean.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=IDM_START
Command2=IDM_PLAYAGAIN
Command3=IDM_PAUSE
Command4=IDB_PLAY
Command5=IDB_MUSICPAUSE
Command6=IDM_GAMESET
Command7=IDM_SAVE
Command8=IDM_EXIT
Command9=ID_APP_ABOUT
Command10=IDM_BLOG
CommandCount=10

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_DIALOG1]
Type=1
Class=GAMESET
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_EDITDIFF,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDITNUM,edit,1350631552

[CLS:GAMESET]
Type=0
HeaderFile=GAMESET.h
ImplementationFile=GAMESET.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDM_PLAYAGAIN

