#include "fileutil/fileutil.h"

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <direct.h>

namespace lihj
{
	int CFileUtil::GetCurWorkPath(char szPath[], int &nSize)
	{	
		memset(szPath, 0, nSize);
		_getcwd(szPath, nSize);
		nSize = strlen(szPath);
		return nSize;
	}

	void CFileUtil::ChangeWorkPathTo(const char szPath[])
	{

	}

	bool CFileUtil::IsPathExist(const char szPath[])
	{
		if (!_access(szPath,0))
		{
			return true;
		}
		return false;
	}

	bool CFileUtil::MakeDirIfNotExist(const char szPath[])
	{
		bool bExist = IsPathExist(szPath);
		if (!bExist)
		{

		}
		return true;
	}

	bool CFileUtil::MakeDir(const char szPath)
	{
		return true;

	}

};