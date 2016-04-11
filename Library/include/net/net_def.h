#pragma once

namespace lihj
{
	enum SessionStatus
	{
		NetNone = 0,
		NetInit = 1,
	};

#pragma pack(push,1)

	enum IOCompletionStatus
	{
		IOCS_ACCEPT = 0,	// ����������ɻ������������
		IOCS_READ = 1,		// ���������
		IOCS_WRITE = 2,		// д�������
		IOCS_MAX = 3,
	};

	struct noverlappedex 
	{
		OVERLAPPED ov;
		IOCompletionStatus status;

		noverlappedex() : status(IOCS_MAX)
		{
			ov.Internal = 0;
			ov.InternalHigh = 0;
			ov.Offset = 0;
			ov.OffsetHigh = 0;
			ov.hEvent = 0;
		}
	};
#pragma pack(pop)
}
