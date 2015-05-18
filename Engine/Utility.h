#pragma once

#include "Windows.h"
#include <string>

namespace utility
{
	int showErrorMessageBox(LPCTSTR lpText, LPCTSTR lpTitle = "Error", HWND hWnd = nullptr);
	int showWarningMessageBox(LPCTSTR lpText, LPCTSTR lpTitle = "Waring", HWND hWnd = nullptr);

	HRESULT readTextFile(const std::string& fileName, std::string& outText);

	std::wstring toWString(const std::string& str);
	std::wstring toWString(const char* const str);
}