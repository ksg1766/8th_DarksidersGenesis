// 명령어		옵션		원본파일 위치					사본파일 저장 위치
	
xcopy		/y/s	.\Engine\Public\*.h						.\Reference\Headers\		
xcopy		/y/s	.\Engine\Public\*.inl					.\Reference\Headers\		
xcopy		/y		.\Engine\Bin\*.lib						.\Reference\Librarys\		
xcopy		/y		.\Engine\ThirdPartyLib\*.lib			.\Reference\Librarys\		
xcopy		/y		.\Engine\Bin\*.dll						.\Client\Bin\
