#pragma once
class CTookit
{
public:
	CTookit(void);
	~CTookit(void);
	static char * ZhuanHuan(CString soure);//将Cstring 转换成 char * 
	static void CopyCStringTToChar( char* pchDest, const CString& strSrc, int nDestLen );
	static void rand_id(char  * pDim);//产生流水帐号！
	static char * Zhongwen(CString cstr_name);
};

