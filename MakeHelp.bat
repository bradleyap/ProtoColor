@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by PROTOCOLOR.HPJ. >"hlp\ProtoColor.hm"
echo. >>"hlp\ProtoColor.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\ProtoColor.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\ProtoColor.hm"
echo. >>"hlp\ProtoColor.hm"
echo // Prompts (IDP_*) >>"hlp\ProtoColor.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\ProtoColor.hm"
echo. >>"hlp\ProtoColor.hm"
echo // Resources (IDR_*) >>"hlp\ProtoColor.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\ProtoColor.hm"
echo. >>"hlp\ProtoColor.hm"
echo // Dialogs (IDD_*) >>"hlp\ProtoColor.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\ProtoColor.hm"
echo. >>"hlp\ProtoColor.hm"
echo // Frame Controls (IDW_*) >>"hlp\ProtoColor.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\ProtoColor.hm"
REM -- Make help for Project PROTOCOLOR


echo Building Win32 Help files
start /wait hcrtf -x "hlp\ProtoColor.hpj"
echo.
if exist Debug\nul copy "hlp\ProtoColor.hlp" Debug
if exist Debug\nul copy "hlp\ProtoColor.cnt" Debug
if exist Release\nul copy "hlp\ProtoColor.hlp" Release
if exist Release\nul copy "hlp\ProtoColor.cnt" Release
echo.


