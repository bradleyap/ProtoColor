	//memset(&buffFile,0,sizeof(file));
	//memset(&buffPath,0,sizeof(path));
	
	//if(GetLastError()==ERROR_INSUFFICIENT_BUFFER) GetICMProfileA(
	//hdc,buffSize,buffPath);
	testProf = SetICMProfileA(hdc,buffPath);

	memset(&ColorSpace,0,sizeof(ColorSpace));
	
	hold = GetColorSpace(hdc);
	GetLogColorSpace((HCOLORSPACE)hold,&ColorSpace,
		sizeof(ColorSpace));
	//ColorSpace.lcsSignature = LCS_SIGNATURE;
	ColorSpace.lcsCSType = LCS_DEVICE_CMYK;//Macro not part of later
										   //documentation
	ColorSpace.lcsIntent = LCS_GM_GRAPHICS;

	holdnew = CreateColorSpace(&ColorSpace);

	BOOL testRet;
	testRet = SetICMProfile(hdc,buffPath);
