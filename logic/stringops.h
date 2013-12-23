#pragma once

namespace Stantos{
	static class StringOps
	{
	public:
		static size_t _MultiBytesToWideChar(wchar_t *dest, const char *src, size_t destSize, int iCodePage = CP_ACP){
			size_t converted = 0;
			converted =::MultiByteToWideChar(iCodePage, 0, src, -1, dest, static_cast<int>(destSize));

			if ( converted > 0 ){
				if ( converted < destSize ){
					dest[converted] = 0;
				}
				else{
					dest[converted-1] = 0;
				}
			}
			else{
				dest[0] = 0;
			}

			return converted;
		}

		static std::wstring _Utf8String2WString(const char* pcszSrc, size_t length){
			size_t w = length + 1;
			wchar_t* szBuff = (wchar_t*)malloc(w<<1);
			_MultiBytesToWideChar(szBuff, pcszSrc, w, CP_UTF8);
			std::wstring str = (szBuff);
			free(szBuff);
			return str;
		}
	};
}