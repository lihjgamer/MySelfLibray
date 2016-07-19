#pragma  once

namespace lihj
{
	class CFileUtil
	{
	public:
		static int  GetCurWorkPath(char szPath[], int &nSize);
		static void ChangeWorkPathTo(const char szPath[]);

		static bool IsPathExist(const char szPath[]);
		static bool MakeDirIfNotExist(const char szPath[]);
		static bool MakeDir(const char szPath);
	public:
		CFileUtil(){};
		~CFileUtil(){};

	};

};