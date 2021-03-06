; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSerioView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ProtoColor.h"
LastPage=0

ClassCount=6
Class1=CSerioApp
Class2=CSerioDoc
Class3=CSerioView
Class4=CMainFrame

ResourceCount=17
Resource1=IDD_ABOUTBOX
Resource2=IDR_COLOR_TOOLBAR
Resource3=IDD_MY_STATUS_BAR
Class5=CAboutDlg
Class6=CChildFrame
Resource4=IDD_FLASH_SCREEN
Resource5=IDD_PAGE_LAYOUT
Resource6=IDD_COLOR_ORIENTATION
Resource7=IDD_CBLOCK_LAYOUT
Resource8=IDD_VIEW_PAGE
Resource9=IDD_COLOR_FORMAT
Resource10=IDD_BLOCK_LAYOUT
Resource11=IDD_MESSAGE_BOX
Resource12=IDD_RETRACT_REQ
Resource13=IDD_AUTHORIZE
Resource14=IDD_EULA
Resource15=IDD_CELL_ASPECTS
Resource16=IDR_PROCOTYPE
Resource17=IDR_MAINFRAME

[CLS:CSerioApp]
Type=0
HeaderFile=ProtoColor.h
ImplementationFile=ProtoColor.cpp
Filter=N

[CLS:CSerioDoc]
Type=0
HeaderFile=SerioDoc.h
ImplementationFile=SerioDoc.cpp
Filter=N

[CLS:CSerioView]
Type=0
HeaderFile=SerioView.h
ImplementationFile=SerioView.cpp
Filter=C
LastObject=CSerioView

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M

[CLS:CAboutDlg]
Type=0
HeaderFile=ProtoColor.cpp
ImplementationFile=ProtoColor.cpp
Filter=D

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
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
Command6=ID_CONTEXT_HELP
CommandCount=6

[MNU:IDR_PROCOTYPE]
Type=1
Class=CSerioView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_COLOR_SPEC
Command12=ID_LAYOUT
Command13=ID_CELL_SPECS
Command14=ID_BLOCK_LAYOUT
Command15=ID_C_BLOCK_LAYOUT
Command16=ID_SPECIFY_ORIENT
Command17=ID_VIEW_TOOLBAR
Command18=ID_VIEW_STATUS_BAR
Command19=ID_VIEW_PAGEFINDER
Command20=ID_WINDOW_NEW
Command21=ID_WINDOW_CASCADE
Command22=ID_WINDOW_TILE_HORZ
Command23=ID_WINDOW_ARRANGE
Command24=ID_HELP_FINDER
Command25=ID_APP_ABOUT
CommandCount=25

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDD_COLOR_FORMAT]
Type=1
ControlCount=45
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_COLOR_HELP,button,1342242816
Control4=IDC_RADIO_RGB,button,1342373897
Control5=IDC_RADIO_CMYK,button,1342177289
Control6=IDC_RADIO_CMY,button,1342177289
Control7=IDC_MAX_STEPS,combobox,1344340226
Control8=IDC_OUTL_COLR,combobox,1344340226
Control9=IDC_START_RA_L2R,edit,1350631552
Control10=IDC_END_RA_L2R,edit,1350631552
Control11=IDC_START_RA_T2B,edit,1350631552
Control12=IDC_END_RA_T2B,edit,1350631552
Control13=IDC_START_RA_F2L,edit,1350631552
Control14=IDC_END_RA_F2L,edit,1350631552
Control15=IDC_START_RA_F2B,edit,1350631552
Control16=IDC_END_RA_F2B,edit,1350631552
Control17=IDC_HONOR_REQ,button,1342373897
Control18=IDC_PRESERVE_LAY,button,1342177289
Control19=IDC_AUTO_LOCK_RANGE,button,1342243843
Control20=IDC_COLOR_RESET,button,1342251008
Control21=IDC_COMPUTE_COLOR,button,1342242816
Control22=IDC_COLOR_JUMP,button,1342251008
Control23=IDC_STATIC,button,1342177287
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,button,1342177287
Control26=IDC_DYN_L2R,static,1342308352
Control27=IDC_DYN_T2B,static,1342308352
Control28=IDC_DYN_F2L,static,1342308352
Control29=IDC_DYN_F2B,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_LOCKED,button,1342177419
Control33=IDC_LOCKED2,button,1342177419
Control34=IDC_LOCKED3,button,1342177419
Control35=IDC_LOCKED4,button,1342177419
Control36=IDC_LOCKED5,button,1342177419
Control37=IDC_LOCKED6,button,1342177419
Control38=IDC_LOCKED7,button,1342177419
Control39=IDC_LOCKED8,button,1342177419
Control40=IDC_STATIC,button,1342177287
Control41=IDC_STATIC,button,1342177287
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,button,1342177287

[DLG:IDD_PAGE_LAYOUT]
Type=1
ControlCount=40
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PAGEW_EDIT,edit,1350631552
Control7=IDC_UNIT_COMB,combobox,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_PAGEH_EDIT,edit,1350631552
Control10=IDC_UNIT_COMB2,combobox,1342242818
Control11=IDC_STATIC,static,1342308352
Control12=IDC_PAGE_COUNT,edit,1350631552
Control13=IDC_PAGINATE_CHK,button,1342242819
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_UPPER_M_EDIT,edit,1350762624
Control17=IDC_UNIT_COMB3,combobox,1342242818
Control18=IDC_STATIC,static,1342308352
Control19=IDC_LEFT_M_EDIT,edit,1350631552
Control20=IDC_UNIT_COMB4,combobox,1342242818
Control21=IDC_STATIC,static,1342308352
Control22=IDC_LOWER_M_EDIT,edit,1350631552
Control23=IDC_UNIT_COMB5,combobox,1342242818
Control24=IDC_STATIC,static,1342308352
Control25=IDC_RIGHT_M_EDIT,edit,1350631552
Control26=IDC_UNIT_COMB6,combobox,1342242818
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,static,1342308352
Control33=IDC_LAYOUT_RESET,button,1342251008
Control34=IDC_COMPUTE,button,1342242816
Control35=IDC_LAYOUT_JUMP,button,1342251008
Control36=IDC_LOCKED12,button,1342177291
Control37=IDC_LOCKED13,button,1342177291
Control38=IDC_LOCKED14,button,1342177291
Control39=IDC_LOCKED15,button,1342177291
Control40=IDC_CLICKABLE_STATIC,static,1342177280

[DLG:IDD_COLOR_ORIENTATION]
Type=1
ControlCount=23
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_ORIENT_HLP,button,1342242816
Control4=IDC_STATIC,button,1342177287
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_L2R_STATIC,static,1342308352
Control9=IDC_DIR_L2R,combobox,1344340226
Control10=IDC_T2B_STATIC,static,1342308352
Control11=IDC_F2L_STATIC,static,1342308352
Control12=IDC_DIR_T2B,combobox,1344340226
Control13=IDC_DIR_F2L,combobox,1344340226
Control14=IDC_DIR_F2B,combobox,1344340226
Control15=IDC_STATIC,static,1342308352
Control16=IDC_F2B_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_ORIENT,static,1342177280
Control22=IDC_STATIC,static,1342308352
Control23=IDC_SPIN1,msctls_updown32,1342177313

[DLG:IDD_CELL_ASPECTS]
Type=1
ControlCount=70
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTON1,button,1342242816
Control4=IDC_CNS_ROW,button,1342242819
Control5=IDC_CNS_COL,button,1342242819
Control6=IDC_CNS_BLK,button,1342242819
Control7=IDC_CNS_CBLK,button,1342242819
Control8=IDC_FRQ_ROW,edit,1350631552
Control9=IDC_FRQ_COL,edit,1350631552
Control10=IDC_FRQ_BLK,edit,1350631552
Control11=IDC_FRQ_CBLK,edit,1350631552
Control12=IDC_ROW_COUNT,edit,1350631552
Control13=IDC_COLUMN_COUNT,edit,1350631552
Control14=IDC_BLOCK_COUNT,edit,1350631552
Control15=IDC_C_BLOCK_COUNT,edit,1350631552
Control16=IDC_FROM_COLOR,button,1342251011
Control17=IDC_INT_SYNC,button,1342251011
Control18=IDC_UNIT_MEAS_COMB1,combobox,1344340226
Control19=IDC_CELL_HEIGHT,edit,1350631552
Control20=IDC_UNIT_MEAS_COMB2,combobox,1344340226
Control21=IDC_CELL_RATIO,button,1342242851
Control22=IDC_BLOCK_WIDTH,edit,1350631552
Control23=IDC_UNIT_MEAS_COMB3,combobox,1344340226
Control24=IDC_BLOCK_HEIGHT,edit,1350631552
Control25=IDC_UNIT_MEAS_COMB4,combobox,1344340226
Control26=IDC_CNGL_BLOCK_W,edit,1350631552
Control27=IDC_UNIT_MEAS_COMB5,combobox,1344340226
Control28=IDC_CNGL_BLOCK_H,edit,1350631552
Control29=IDC_UNIT_MEAS_COMB6,combobox,1344340226
Control30=IDC_RESET,button,1342251008
Control31=IDC_CALCULATE,button,1342251008
Control32=IDC_JUMP,button,1342251008
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_STATIC,button,1342177287
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,button,1342177287
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_START_RANGE,button,1342177287
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC,button,1342177287
Control50=IDC_STATIC,static,1342308352
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_STATIC,static,1342308352
Control54=IDC_STATIC,static,1342308352
Control55=IDC_STATIC,static,1342308352
Control56=IDC_STATIC,static,1342308352
Control57=IDC_STATIC,static,1342308352
Control58=IDC_LOCKED17,button,1342177291
Control59=IDC_LOCKED18,button,1342177291
Control60=IDC_LOCKED19,button,1342177291
Control61=IDC_LOCKED20,button,1342177291
Control62=IDC_LOCKED21,button,1342177291
Control63=IDC_LOCKED22,button,1342177291
Control64=IDC_LOCKED23,button,1342177291
Control65=IDC_LOCKED24,button,1342177291
Control66=IDC_LOCKED25,button,1342177291
Control67=IDC_LOCKED26,button,1342177291
Control68=IDC_STATIC,button,1342177287
Control69=IDC_CELL_COUNT_STATIC,static,1342308352
Control70=IDC_CELL_W,edit,1350631552

[DLG:IDD_VIEW_PAGE]
Type=1
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_CUR_PAGE_EDIT,edit,1350631552

[DLG:IDD_CBLOCK_LAYOUT]
Type=1
ControlCount=21
Control1=IDC_CBLOCK_ROWS_EDIT,edit,1350631552
Control2=IDC_CBLOCK_COLS_EDIT,edit,1350631552
Control3=IDC_CB_COLSP_EDIT,edit,1350631552
Control4=IDC_CB_ROWSP_EDIT,edit,1350631552
Control5=IDC_V_FRM_W_EDIT,edit,1350631552
Control6=IDC_V_FRM_H_EDIT,edit,1350631552
Control7=IDC_CB_W_EDIT,edit,1350631552
Control8=IDC_CB_H_EDIT,edit,1350631552
Control9=IDC_CBL_RESET_BN,button,1342242816
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816
Control12=IDC_HELP_BN,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_CBLOCK_STATIC,static,1342308352

[DLG:IDD_BLOCK_LAYOUT]
Type=1
ControlCount=21
Control1=IDC_BCOLS_EDIT,edit,1350631552
Control2=IDC_BROWS_EDIT,edit,1350631552
Control3=IDC_B_COLSPACE_EDIT,edit,1350631552
Control4=IDC_B_ROWSPACE_EDIT,edit,1350631552
Control5=IDC_FRAME_W_EDIT,edit,1350631552
Control6=IDC_FRAME_H_EDIT,edit,1350631552
Control7=IDC_BLOCKW_EDIT,edit,1350631552
Control8=IDC_BLOCKH_EDIT,edit,1350631552
Control9=IDC_BL_RESET_BN,button,1342242816
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816
Control12=IDC_HELP,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_BLK_LAYOUT_STATIC,static,1342308352

[DLG:IDD_MESSAGE_BOX]
Type=1
ControlCount=4
Control1=IDCANCEL,button,1342242816
Control2=IDC_NO_BN,button,1342242816
Control3=IDC_YES_BN,button,1342242816
Control4=IDC_MESS_STATIC,static,1342308352

[DLG:IDD_RETRACT_REQ]
Type=1
ControlCount=40
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_F1_STATIC,static,1342308352
Control8=IDC_F5_STATIC,static,1342308352
Control9=IDC_F2_STATIC,static,1342308352
Control10=IDC_F4_STATIC,static,1342308352
Control11=IDC_ITEM2,static,1342308352
Control12=IDC_REQ_VAL2,static,1342308352
Control13=IDC_VAL2,static,1342308352
Control14=IDC_ITEM3,static,1342308352
Control15=IDC_REQ_VAL3,static,1342308352
Control16=IDC_VAL3,static,1342308352
Control17=IDC_ITEM4,static,1342308352
Control18=IDC_REQ_VAL4,static,1342308352
Control19=IDC_VAL4,static,1342308352
Control20=IDC_ITEM5,static,1342308352
Control21=IDC_REQ_VAL5,static,1342308352
Control22=IDC_VAL5,static,1342308352
Control23=IDC_ITEM6,static,1342308352
Control24=IDC_REQ_VAL6,static,1342308352
Control25=IDC_VAL6,static,1342308352
Control26=IDC_ITEM,static,1342308352
Control27=IDC_REQ_VAL,static,1342308352
Control28=IDC_VAL,static,1342308352
Control29=IDC_DEL2,static,1342308352
Control30=IDC_DEL3,static,1342308352
Control31=IDC_DEL4,static,1342308352
Control32=IDC_DEL5,static,1342308352
Control33=IDC_DEL6,static,1342308352
Control34=IDC_DEL1,static,1342308352
Control35=IDC_RETRACT_CHECK1,button,1342242819
Control36=IDC_RETRACT_CHECK2,button,1342242819
Control37=IDC_RETRACT_CHECK3,button,1342242819
Control38=IDC_RETRACT_CHECK4,button,1342242819
Control39=IDC_RETRACT_CHECK5,button,1342242819
Control40=IDC_RETRACT_CHECK6,button,1342242819

[DLG:IDD_AUTHORIZE]
Type=1
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_KEY_EDIT,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352

[DLG:IDD_EULA]
Type=1
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EULA_EDIT,edit,1352730628

[DLG:IDD_FLASH_SCREEN]
Type=1
ControlCount=0

[DLG:IDD_MY_STATUS_BAR]
Type=1
ControlCount=2
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PROGRESS_STATIC,static,1342177287

[TB:IDR_COLOR_TOOLBAR]
Type=1
Command1=ID_RGB_BUTTON
Command2=ID_CMYK_BUTTON
Command3=ID_CMY_BUTTON
CommandCount=3

