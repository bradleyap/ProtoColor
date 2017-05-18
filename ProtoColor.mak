# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=ProtoColor - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to ProtoColor - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ProtoColor - Win32 Release" && "$(CFG)" !=\
 "ProtoColor - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProtoColor.mak" CFG="ProtoColor - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProtoColor - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ProtoColor - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "ProtoColor - Win32 Debug"
CPP=cl.exe
RSC=rc.exe
MTL=mktyplib.exe

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\Release
INTDIR=.\Release

ALL : "$(OUTDIR)\ProtoColor.exe" "$(OUTDIR)\ProtoColor.hlp"

CLEAN : 
	-@erase ".\Release\ProtoColor.exe"
	-@erase ".\Release\IntsEdit.obj"
	-@erase ".\Release\ProtoColor.pch"
	-@erase ".\Release\Bellows.obj"
	-@erase ".\Release\CBlockLayoutDlg.obj"
	-@erase ".\Release\Registrar.obj"
	-@erase ".\Release\PenObject.obj"
	-@erase ".\Release\ColorFormDlg.obj"
	-@erase ".\Release\ChildFrm.obj"
	-@erase ".\Release\Range.obj"
	-@erase ".\Release\MessDlg.obj"
	-@erase ".\Release\MailBox.obj"
	-@erase ".\Release\PerformLog.obj"
	-@erase ".\Release\Maestro.obj"
	-@erase ".\Release\MyOtherEdit.obj"
	-@erase ".\Release\AspectsBuffer.obj"
	-@erase ".\Release\SerioView.obj"
	-@erase ".\Release\RetractDlg.obj"
	-@erase ".\Release\ColorRange.obj"
	-@erase ".\Release\StrikeStatic.obj"
	-@erase ".\Release\CBlockDragStatic.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\ClickStatic.obj"
	-@erase ".\Release\AuthorizeDlg.obj"
	-@erase ".\Release\RegAspects.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\CellCount.obj"
	-@erase ".\Release\PanelStatic.obj"
	-@erase ".\Release\SerioDoc.obj"
	-@erase ".\Release\PinRect.obj"
	-@erase ".\Release\ViewControlDlg.obj"
	-@erase ".\Release\ToggleManager.obj"
	-@erase ".\Release\ProgressMgr.obj"
	-@erase ".\Release\EulaDlg.obj"
	-@erase ".\Release\BlockDragStatic.obj"
	-@erase ".\Release\ProgressBar.obj"
	-@erase ".\Release\CellAspectsDlg.obj"
	-@erase ".\Release\OrientDlg.obj"
	-@erase ".\Release\Frequency.obj"
	-@erase ".\Release\ProgressStatic.obj"
	-@erase ".\Release\ProtoColor.obj"
	-@erase ".\Release\SuggestBox.obj"
	-@erase ".\Release\QuickLayout.obj"
	-@erase ".\Release\DragStatic.obj"
	-@erase ".\Release\ArrowSpin.obj"
	-@erase ".\Release\Message.obj"
	-@erase ".\Release\BlockLayoutDlg.obj"
	-@erase ".\Release\Calc.obj"
	-@erase ".\Release\MyEdit.obj"
	-@erase ".\Release\Flash.obj"
	-@erase ".\Release\ProtoColor.res"
	-@erase ".\Release\ProtoColor.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_MBCS" /Fp"$(INTDIR)/ProtoColor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ProtoColor.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ProtoColor.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/ProtoColor.pdb" /machine:I386 /out:"$(OUTDIR)/ProtoColor.exe" 
LINK32_OBJS= \
	"$(INTDIR)/IntsEdit.obj" \
	"$(INTDIR)/Bellows.obj" \
	"$(INTDIR)/CBlockLayoutDlg.obj" \
	"$(INTDIR)/Registrar.obj" \
	"$(INTDIR)/PenObject.obj" \
	"$(INTDIR)/ColorFormDlg.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/Range.obj" \
	"$(INTDIR)/MessDlg.obj" \
	"$(INTDIR)/MailBox.obj" \
	"$(INTDIR)/PerformLog.obj" \
	"$(INTDIR)/Maestro.obj" \
	"$(INTDIR)/MyOtherEdit.obj" \
	"$(INTDIR)/AspectsBuffer.obj" \
	"$(INTDIR)/SerioView.obj" \
	"$(INTDIR)/RetractDlg.obj" \
	"$(INTDIR)/ColorRange.obj" \
	"$(INTDIR)/StrikeStatic.obj" \
	"$(INTDIR)/CBlockDragStatic.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ClickStatic.obj" \
	"$(INTDIR)/AuthorizeDlg.obj" \
	"$(INTDIR)/RegAspects.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/CellCount.obj" \
	"$(INTDIR)/PanelStatic.obj" \
	"$(INTDIR)/SerioDoc.obj" \
	"$(INTDIR)/PinRect.obj" \
	"$(INTDIR)/ViewControlDlg.obj" \
	"$(INTDIR)/ToggleManager.obj" \
	"$(INTDIR)/ProgressMgr.obj" \
	"$(INTDIR)/EulaDlg.obj" \
	"$(INTDIR)/BlockDragStatic.obj" \
	"$(INTDIR)/ProgressBar.obj" \
	"$(INTDIR)/CellAspectsDlg.obj" \
	"$(INTDIR)/OrientDlg.obj" \
	"$(INTDIR)/Frequency.obj" \
	"$(INTDIR)/ProgressStatic.obj" \
	"$(INTDIR)/ProtoColor.obj" \
	"$(INTDIR)/SuggestBox.obj" \
	"$(INTDIR)/QuickLayout.obj" \
	"$(INTDIR)/DragStatic.obj" \
	"$(INTDIR)/ArrowSpin.obj" \
	"$(INTDIR)/Message.obj" \
	"$(INTDIR)/BlockLayoutDlg.obj" \
	"$(INTDIR)/Calc.obj" \
	"$(INTDIR)/MyEdit.obj" \
	"$(INTDIR)/Flash.obj" \
	"$(INTDIR)/ProtoColor.res"

"$(OUTDIR)\ProtoColor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "$(OUTDIR)\ProtoColor.exe" "$(OUTDIR)\ProtoColor.hlp"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\ProtoColor.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase ".\Debug\ProtoColor.exe"
	-@erase ".\Debug\MailBox.obj"
	-@erase ".\Debug\Maestro.obj"
	-@erase ".\Debug\Calc.obj"
	-@erase ".\Debug\MyEdit.obj"
	-@erase ".\Debug\ChildFrm.obj"
	-@erase ".\Debug\PerformLog.obj"
	-@erase ".\Debug\Registrar.obj"
	-@erase ".\Debug\CellAspectsDlg.obj"
	-@erase ".\Debug\BlockDragStatic.obj"
	-@erase ".\Debug\CBlockLayoutDlg.obj"
	-@erase ".\Debug\ColorFormDlg.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\RetractDlg.obj"
	-@erase ".\Debug\ColorRange.obj"
	-@erase ".\Debug\ToggleManager.obj"
	-@erase ".\Debug\PinRect.obj"
	-@erase ".\Debug\MyOtherEdit.obj"
	-@erase ".\Debug\RegAspects.obj"
	-@erase ".\Debug\OrientDlg.obj"
	-@erase ".\Debug\QuickLayout.obj"
	-@erase ".\Debug\Flash.obj"
	-@erase ".\Debug\Frequency.obj"
	-@erase ".\Debug\EulaDlg.obj"
	-@erase ".\Debug\PanelStatic.obj"
	-@erase ".\Debug\SerioDoc.obj"
	-@erase ".\Debug\ViewControlDlg.obj"
	-@erase ".\Debug\StrikeStatic.obj"
	-@erase ".\Debug\CBlockDragStatic.obj"
	-@erase ".\Debug\AuthorizeDlg.obj"
	-@erase ".\Debug\CellCount.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\ArrowSpin.obj"
	-@erase ".\Debug\ProgressMgr.obj"
	-@erase ".\Debug\AspectsBuffer.obj"
	-@erase ".\Debug\Range.obj"
	-@erase ".\Debug\ProgressBar.obj"
	-@erase ".\Debug\MessDlg.obj"
	-@erase ".\Debug\ProtoColor.obj"
	-@erase ".\Debug\SuggestBox.obj"
	-@erase ".\Debug\ProgressStatic.obj"
	-@erase ".\Debug\Message.obj"
	-@erase ".\Debug\DragStatic.obj"
	-@erase ".\Debug\PenObject.obj"
	-@erase ".\Debug\Bellows.obj"
	-@erase ".\Debug\BlockLayoutDlg.obj"
	-@erase ".\Debug\ClickStatic.obj"
	-@erase ".\Debug\SerioView.obj"
	-@erase ".\Debug\IntsEdit.obj"
	-@erase ".\Debug\ProtoColor.res"
	-@erase ".\Debug\ProtoColor.ilk"
	-@erase ".\Debug\ProtoColor.pdb"
	-@erase ".\Debug\ProtoColor.hlp"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/ProtoColor.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
RSC_PROJ=/l 0x409 /fo"$(INTDIR)/ProtoColor.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/ProtoColor.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/ProtoColor.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)/ProtoColor.exe" 
LINK32_OBJS= \
	"$(INTDIR)/MailBox.obj" \
	"$(INTDIR)/Maestro.obj" \
	"$(INTDIR)/Calc.obj" \
	"$(INTDIR)/MyEdit.obj" \
	"$(INTDIR)/ChildFrm.obj" \
	"$(INTDIR)/PerformLog.obj" \
	"$(INTDIR)/Registrar.obj" \
	"$(INTDIR)/CellAspectsDlg.obj" \
	"$(INTDIR)/BlockDragStatic.obj" \
	"$(INTDIR)/CBlockLayoutDlg.obj" \
	"$(INTDIR)/ColorFormDlg.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/RetractDlg.obj" \
	"$(INTDIR)/ColorRange.obj" \
	"$(INTDIR)/ToggleManager.obj" \
	"$(INTDIR)/PinRect.obj" \
	"$(INTDIR)/MyOtherEdit.obj" \
	"$(INTDIR)/RegAspects.obj" \
	"$(INTDIR)/OrientDlg.obj" \
	"$(INTDIR)/QuickLayout.obj" \
	"$(INTDIR)/Flash.obj" \
	"$(INTDIR)/Frequency.obj" \
	"$(INTDIR)/EulaDlg.obj" \
	"$(INTDIR)/PanelStatic.obj" \
	"$(INTDIR)/SerioDoc.obj" \
	"$(INTDIR)/ViewControlDlg.obj" \
	"$(INTDIR)/StrikeStatic.obj" \
	"$(INTDIR)/CBlockDragStatic.obj" \
	"$(INTDIR)/AuthorizeDlg.obj" \
	"$(INTDIR)/CellCount.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/ArrowSpin.obj" \
	"$(INTDIR)/ProgressMgr.obj" \
	"$(INTDIR)/AspectsBuffer.obj" \
	"$(INTDIR)/Range.obj" \
	"$(INTDIR)/ProgressBar.obj" \
	"$(INTDIR)/MessDlg.obj" \
	"$(INTDIR)/ProtoColor.obj" \
	"$(INTDIR)/SuggestBox.obj" \
	"$(INTDIR)/ProgressStatic.obj" \
	"$(INTDIR)/Message.obj" \
	"$(INTDIR)/DragStatic.obj" \
	"$(INTDIR)/PenObject.obj" \
	"$(INTDIR)/Bellows.obj" \
	"$(INTDIR)/BlockLayoutDlg.obj" \
	"$(INTDIR)/ClickStatic.obj" \
	"$(INTDIR)/SerioView.obj" \
	"$(INTDIR)/IntsEdit.obj" \
	"$(INTDIR)/ProtoColor.res"

"$(OUTDIR)\ProtoColor.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "ProtoColor - Win32 Release"
# Name "ProtoColor - Win32 Debug"

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoColor.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PROTO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\SerioDoc.h"\
	".\SerioView.h"\
	".\EulaDlg.h"\
	".\AuthorizeDlg.h"\
	".\Flash.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ProtoColor.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PROTO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MainFrm.h"\
	".\ChildFrm.h"\
	".\SerioDoc.h"\
	".\SerioView.h"\
	".\EulaDlg.h"\
	".\AuthorizeDlg.h"\
	".\Flash.h"\
	

"$(INTDIR)\ProtoColor.obj" : $(SOURCE) $(DEP_CPP_PROTO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS"\
 /Fp"$(INTDIR)/ProtoColor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ProtoColor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_STDAF=\
	".\StdAfx.h"\
	
# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_MBCS" /Fp"$(INTDIR)/ProtoColor.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\ProtoColor.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MainFrm.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MainFrm.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ChildFrm.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CHILD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ChildFrm.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SerioDoc.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_SERIO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ViewControlDlg.h"\
	".\BlockLayoutDlg.h"\
	".\CBlockLayoutDlg.h"\
	".\ColorFormDlg.h"\
	".\QuickLayout.h"\
	".\CellAspectsDlg.h"\
	".\OrientDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\ClickStatic.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\SerioDoc.obj" : $(SOURCE) $(DEP_CPP_SERIO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_SERIO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ViewControlDlg.h"\
	".\BlockLayoutDlg.h"\
	".\CBlockLayoutDlg.h"\
	".\ColorFormDlg.h"\
	".\QuickLayout.h"\
	".\CellAspectsDlg.h"\
	".\OrientDlg.h"\
	".\ClickStatic.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\SerioDoc.obj" : $(SOURCE) $(DEP_CPP_SERIO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SerioView.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_SERIOV=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\SerioView.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\SerioView.obj" : $(SOURCE) $(DEP_CPP_SERIOV) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_SERIOV=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\SerioView.h"\
	

"$(INTDIR)\SerioView.obj" : $(SOURCE) $(DEP_CPP_SERIOV) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoColor.rc
DEP_RSC_PROTOC=\
	".\res\ProtoColor.ico"\
	".\res\SerioDoc.ico"\
	".\res\Toolbar.bmp"\
	".\res\toolbar1.bmp"\
	".\res\OpenLockUp.bmp"\
	".\res\OpenLockDn.bmp"\
	".\res\ClosedLockDn.bmp"\
	".\res\ClosedLockUp.bmp"\
	".\res\ar.bmp"\
	".\res\ar_tl.bmp"\
	".\res\ar_tb.bmp"\
	".\res\ar_tlb.bmp"\
	".\res\ar_tlbr.bmp"\
	".\res\ar_tr.bmp"\
	".\res\ar_br.bmp"\
	".\res\ar_tbr.bmp"\
	".\res\ar_lr.bmp"\
	".\res\ar_lb.bmp"\
	".\res\ar_rlb.bmp"\
	".\res\ar_tlr.bmp"\
	".\res\ar_tr_lb.bmp"\
	".\res\ar_tl_rb.bmp"\
	".\res\ar_tb_lr.bmp"\
	".\res\cmyk.bmp"\
	".\res\rgb.bmp"\
	".\res\cmy.bmp"\
	".\res\lockedx.bmp"\
	".\res\unlockedx.bmp"\
	".\res\soldier.BMP"\
	".\res\ColorToolBar.bmp"\
	".\res\ProtoColor.rc2"\
	

"$(INTDIR)\ProtoColor.res" : $(SOURCE) $(DEP_RSC_PROTOC) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\hlp\ProtoColor.hpj

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

# Begin Custom Build - Making help file...
OutDir=.\Release
ProjDir=.
TargetName=ProtoColor
InputPath=.\hlp\ProtoColor.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

# Begin Custom Build - Making help file...
OutDir=.\Debug
ProjDir=.
TargetName=ProtoColor
InputPath=.\hlp\ProtoColor.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
   "$(ProjDir)\makehelp.bat"

# End Custom Build

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ViewControlDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_VIEWC=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ViewControlDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ViewControlDlg.obj" : $(SOURCE) $(DEP_CPP_VIEWC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_VIEWC=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ViewControlDlg.h"\
	

"$(INTDIR)\ViewControlDlg.obj" : $(SOURCE) $(DEP_CPP_VIEWC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AspectsBuffer.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_ASPEC=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\AspectsBuffer.obj" : $(SOURCE) $(DEP_CPP_ASPEC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_ASPEC=\
	".\StdAfx.h"\
	

"$(INTDIR)\AspectsBuffer.obj" : $(SOURCE) $(DEP_CPP_ASPEC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthorizeDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_AUTHO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\AuthorizeDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\AuthorizeDlg.obj" : $(SOURCE) $(DEP_CPP_AUTHO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_AUTHO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\AuthorizeDlg.h"\
	

"$(INTDIR)\AuthorizeDlg.obj" : $(SOURCE) $(DEP_CPP_AUTHO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bellows.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_BELLO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Bellows.h"\
	".\Maestro.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Bellows.obj" : $(SOURCE) $(DEP_CPP_BELLO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_BELLO=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Bellows.h"\
	".\Maestro.h"\
	

"$(INTDIR)\Bellows.obj" : $(SOURCE) $(DEP_CPP_BELLO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BlockDragStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_BLOCK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\BlockDragStatic.obj" : $(SOURCE) $(DEP_CPP_BLOCK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_BLOCK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	

"$(INTDIR)\BlockDragStatic.obj" : $(SOURCE) $(DEP_CPP_BLOCK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BlockLayoutDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_BLOCKL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\BlockLayoutDlg.h"\
	".\SerioDoc.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\BlockLayoutDlg.obj" : $(SOURCE) $(DEP_CPP_BLOCKL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_BLOCKL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\BlockLayoutDlg.h"\
	".\SerioDoc.h"\
	

"$(INTDIR)\BlockLayoutDlg.obj" : $(SOURCE) $(DEP_CPP_BLOCKL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Calc.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CALC_=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RetractDlg.h"\
	".\Registrar.h"\
	".\Maestro.h"\
	".\Bellows.h"\
	".\ProgressBar.h"\
	".\ToggleManager.h"\
	".\SerioDoc.h"\
	".\MessDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\PanelStatic.h"\
	".\StrikeStatic.h"\
	".\ProgressStatic.h"\
	

"$(INTDIR)\Calc.obj" : $(SOURCE) $(DEP_CPP_CALC_) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CALC_=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RetractDlg.h"\
	".\Registrar.h"\
	".\Maestro.h"\
	".\Bellows.h"\
	".\ProgressBar.h"\
	".\ToggleManager.h"\
	".\SerioDoc.h"\
	".\MessDlg.h"\
	".\PanelStatic.h"\
	".\StrikeStatic.h"\
	".\ProgressStatic.h"\
	

"$(INTDIR)\Calc.obj" : $(SOURCE) $(DEP_CPP_CALC_) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBlockDragStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CBLOC=\
	".\StdAfx.h"\
	".\SerioDoc.h"\
	".\ProtoColor.h"\
	".\CBlockDragStatic.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\CBlockDragStatic.obj" : $(SOURCE) $(DEP_CPP_CBLOC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CBLOC=\
	".\StdAfx.h"\
	".\SerioDoc.h"\
	".\ProtoColor.h"\
	".\CBlockDragStatic.h"\
	

"$(INTDIR)\CBlockDragStatic.obj" : $(SOURCE) $(DEP_CPP_CBLOC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBlockLayoutDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CBLOCK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\CBlockLayoutDlg.h"\
	".\SerioDoc.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\CBlockLayoutDlg.obj" : $(SOURCE) $(DEP_CPP_CBLOCK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CBLOCK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\CBlockLayoutDlg.h"\
	".\SerioDoc.h"\
	

"$(INTDIR)\CBlockLayoutDlg.obj" : $(SOURCE) $(DEP_CPP_CBLOCK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CellAspectsDlg.cpp
DEP_CPP_CELLA=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\CellAspectsDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\CellAspectsDlg.obj" : $(SOURCE) $(DEP_CPP_CELLA) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CellCount.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CELLC=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\CellCount.obj" : $(SOURCE) $(DEP_CPP_CELLC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CELLC=\
	".\StdAfx.h"\
	

"$(INTDIR)\CellCount.obj" : $(SOURCE) $(DEP_CPP_CELLC) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClickStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_CLICK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ClickStatic.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ClickStatic.obj" : $(SOURCE) $(DEP_CPP_CLICK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_CLICK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ClickStatic.h"\
	

"$(INTDIR)\ClickStatic.obj" : $(SOURCE) $(DEP_CPP_CLICK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorFormDlg.cpp
DEP_CPP_COLOR=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\ColorFormDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ColorFormDlg.obj" : $(SOURCE) $(DEP_CPP_COLOR) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorRange.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_COLORR=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ColorRange.obj" : $(SOURCE) $(DEP_CPP_COLORR) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_COLORR=\
	".\StdAfx.h"\
	

"$(INTDIR)\ColorRange.obj" : $(SOURCE) $(DEP_CPP_COLORR) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_DRAGS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\DragStatic.obj" : $(SOURCE) $(DEP_CPP_DRAGS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_DRAGS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\DragStatic.obj" : $(SOURCE) $(DEP_CPP_DRAGS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EulaDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_EULAD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\EulaDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\EulaDlg.obj" : $(SOURCE) $(DEP_CPP_EULAD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_EULAD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\EulaDlg.h"\
	

"$(INTDIR)\EulaDlg.obj" : $(SOURCE) $(DEP_CPP_EULAD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Flash.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_FLASH=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Flash.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Flash.obj" : $(SOURCE) $(DEP_CPP_FLASH) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_FLASH=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Flash.h"\
	

"$(INTDIR)\Flash.obj" : $(SOURCE) $(DEP_CPP_FLASH) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Frequency.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_FREQU=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Frequency.obj" : $(SOURCE) $(DEP_CPP_FREQU) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_FREQU=\
	".\StdAfx.h"\
	

"$(INTDIR)\Frequency.obj" : $(SOURCE) $(DEP_CPP_FREQU) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntsEdit.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_INTSE=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\IntsEdit.obj" : $(SOURCE) $(DEP_CPP_INTSE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_INTSE=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	

"$(INTDIR)\IntsEdit.obj" : $(SOURCE) $(DEP_CPP_INTSE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Maestro.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MAEST=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Maestro.h"\
	".\Registrar.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Maestro.obj" : $(SOURCE) $(DEP_CPP_MAEST) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MAEST=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Maestro.h"\
	".\Registrar.h"\
	

"$(INTDIR)\Maestro.obj" : $(SOURCE) $(DEP_CPP_MAEST) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MailBox.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MAILB=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\MailBox.obj" : $(SOURCE) $(DEP_CPP_MAILB) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MAILB=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	

"$(INTDIR)\MailBox.obj" : $(SOURCE) $(DEP_CPP_MAILB) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Message.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MESSA=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Message.obj" : $(SOURCE) $(DEP_CPP_MESSA) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MESSA=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	

"$(INTDIR)\Message.obj" : $(SOURCE) $(DEP_CPP_MESSA) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MessDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MESSD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MessDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\MessDlg.obj" : $(SOURCE) $(DEP_CPP_MESSD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MESSD=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\MessDlg.h"\
	

"$(INTDIR)\MessDlg.obj" : $(SOURCE) $(DEP_CPP_MESSD) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyEdit.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MYEDI=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\CellAspectsDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\MyEdit.obj" : $(SOURCE) $(DEP_CPP_MYEDI) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MYEDI=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\CellAspectsDlg.h"\
	

"$(INTDIR)\MyEdit.obj" : $(SOURCE) $(DEP_CPP_MYEDI) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyOtherEdit.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_MYOTH=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\MyOtherEdit.obj" : $(SOURCE) $(DEP_CPP_MYOTH) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_MYOTH=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	

"$(INTDIR)\MyOtherEdit.obj" : $(SOURCE) $(DEP_CPP_MYOTH) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OrientDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_ORIEN=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\OrientDlg.h"\
	".\SerioDoc.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\OrientDlg.obj" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_ORIEN=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\OrientDlg.h"\
	".\SerioDoc.h"\
	".\DragStatic.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\OrientDlg.obj" : $(SOURCE) $(DEP_CPP_ORIEN) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PanelStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PANEL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\PanelStatic.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\PanelStatic.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PANEL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\PanelStatic.h"\
	

"$(INTDIR)\PanelStatic.obj" : $(SOURCE) $(DEP_CPP_PANEL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PenObject.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PENOB=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\PenObject.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\PenObject.obj" : $(SOURCE) $(DEP_CPP_PENOB) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PENOB=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\PenObject.h"\
	

"$(INTDIR)\PenObject.obj" : $(SOURCE) $(DEP_CPP_PENOB) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PerformLog.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PERFO=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\PerformLog.obj" : $(SOURCE) $(DEP_CPP_PERFO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PERFO=\
	".\StdAfx.h"\
	

"$(INTDIR)\PerformLog.obj" : $(SOURCE) $(DEP_CPP_PERFO) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PinRect.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PINRE=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\PinRect.obj" : $(SOURCE) $(DEP_CPP_PINRE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PINRE=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	

"$(INTDIR)\PinRect.obj" : $(SOURCE) $(DEP_CPP_PINRE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressBar.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PROGR=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ProgressBar.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\ProgressStatic.h"\
	

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PROGR=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ProgressBar.h"\
	".\ProgressStatic.h"\
	

"$(INTDIR)\ProgressBar.obj" : $(SOURCE) $(DEP_CPP_PROGR) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressMgr.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PROGRE=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ProgressMgr.obj" : $(SOURCE) $(DEP_CPP_PROGRE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PROGRE=\
	".\StdAfx.h"\
	

"$(INTDIR)\ProgressMgr.obj" : $(SOURCE) $(DEP_CPP_PROGRE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_PROGRES=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ProgressStatic.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ProgressStatic.obj" : $(SOURCE) $(DEP_CPP_PROGRES) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_PROGRES=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ProgressStatic.h"\
	

"$(INTDIR)\ProgressStatic.obj" : $(SOURCE) $(DEP_CPP_PROGRES) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QuickLayout.cpp
DEP_CPP_QUICK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\SerioDoc.h"\
	".\QuickLayout.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\ClickStatic.h"\
	

"$(INTDIR)\QuickLayout.obj" : $(SOURCE) $(DEP_CPP_QUICK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Range.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_RANGE=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Range.obj" : $(SOURCE) $(DEP_CPP_RANGE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_RANGE=\
	".\StdAfx.h"\
	

"$(INTDIR)\Range.obj" : $(SOURCE) $(DEP_CPP_RANGE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegAspects.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_REGAS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RegAspects.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\RegAspects.obj" : $(SOURCE) $(DEP_CPP_REGAS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_REGAS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RegAspects.h"\
	

"$(INTDIR)\RegAspects.obj" : $(SOURCE) $(DEP_CPP_REGAS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Registrar.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_REGIS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Registrar.h"\
	".\Bellows.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\Registrar.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_REGIS=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\Registrar.h"\
	".\Bellows.h"\
	

"$(INTDIR)\Registrar.obj" : $(SOURCE) $(DEP_CPP_REGIS) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RetractDlg.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_RETRA=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RetractDlg.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	".\PanelStatic.h"\
	".\StrikeStatic.h"\
	

"$(INTDIR)\RetractDlg.obj" : $(SOURCE) $(DEP_CPP_RETRA) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_RETRA=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\RetractDlg.h"\
	".\PanelStatic.h"\
	".\StrikeStatic.h"\
	

"$(INTDIR)\RetractDlg.obj" : $(SOURCE) $(DEP_CPP_RETRA) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StrikeStatic.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_STRIK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\StrikeStatic.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\StrikeStatic.obj" : $(SOURCE) $(DEP_CPP_STRIK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_STRIK=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\StrikeStatic.h"\
	

"$(INTDIR)\StrikeStatic.obj" : $(SOURCE) $(DEP_CPP_STRIK) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuggestBox.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_SUGGE=\
	".\StdAfx.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\SuggestBox.obj" : $(SOURCE) $(DEP_CPP_SUGGE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_SUGGE=\
	".\StdAfx.h"\
	

"$(INTDIR)\SuggestBox.obj" : $(SOURCE) $(DEP_CPP_SUGGE) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToggleManager.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_TOGGL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ToggleManager.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ToggleManager.obj" : $(SOURCE) $(DEP_CPP_TOGGL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_TOGGL=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ToggleManager.h"\
	

"$(INTDIR)\ToggleManager.obj" : $(SOURCE) $(DEP_CPP_TOGGL) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArrowSpin.cpp

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

DEP_CPP_ARROW=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ArrowSpin.h"\
	".\Aspects.h"\
	".\AspectsBuffer.h"\
	".\Message.h"\
	".\SuggestBox.h"\
	".\MailBox.h"\
	".\PinRect.h"\
	".\PerformLog.h"\
	".\Range.h"\
	".\ProgressMgr.h"\
	".\ColorRange.h"\
	".\CellCount.h"\
	".\Frequency.h"\
	".\Calc.h"\
	".\MyOtherEdit.h"\
	".\MyEdit.h"\
	".\IntsEdit.h"\
	".\BlockDragStatic.h"\
	

"$(INTDIR)\ArrowSpin.obj" : $(SOURCE) $(DEP_CPP_ARROW) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

DEP_CPP_ARROW=\
	".\StdAfx.h"\
	".\ProtoColor.h"\
	".\ArrowSpin.h"\
	

"$(INTDIR)\ArrowSpin.obj" : $(SOURCE) $(DEP_CPP_ARROW) "$(INTDIR)"\
 "$(INTDIR)\ProtoColor.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\WordString.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Aspects.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AspectsBuffer.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\AuthorizeDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Bellows.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BlockDragStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\BlockLayoutDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Calc.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBlockDragStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CBlockLayoutDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CellAspectsDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\CellCount.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ChildFrm.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ClickStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorFormDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ColorRange.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DragStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EulaDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Flash.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Frequency.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Globals.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\IntsEdit.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Maestro.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MailBox.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Message.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MessDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyEdit.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MyOtherEdit.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OrientDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PanelStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PenObject.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PerformLog.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\PinRect.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressBar.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressMgr.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProgressStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ProtoColor.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\QuickLayout.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Range.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RegAspects.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Registrar.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\resource.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\RetractDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SerioDoc.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SerioView.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StrikeStatic.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\SuggestBox.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ToggleManager.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ViewControlDlg.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ArrowSpin.h

!IF  "$(CFG)" == "ProtoColor - Win32 Release"

!ELSEIF  "$(CFG)" == "ProtoColor - Win32 Debug"

!ENDIF 

# End Source File
# End Target
# End Project
################################################################################
