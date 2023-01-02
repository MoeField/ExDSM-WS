//strCoder.h
#pragma once

#include "Winsock2.h"
#include "windows.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <locale>
#include <codecvt>
#include <string>


void string2num(std::string str, double& num) {
	std::stringstream ss; ss << str; ss >> num;
}

std::string StringToUTF8(const std::string& gbkData)
{
	const char* GBK_LOCALE_NAME = "CHS";
	//GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

	std::wstring_convert<std::codecvt<wchar_t, char, mbstate_t>>
		conv(new std::codecvt<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
	std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

	std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
	std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8

	return utf8str;
}


std::string UTF8ToString(const std::string& utf8Data)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	std::wstring wString = conv.from_bytes(utf8Data);    // utf-8 => wstring

	std::wstring_convert<std::codecvt< wchar_t, char, std::mbstate_t>>
		convert(new std::codecvt< wchar_t, char, std::mbstate_t>("CHS"));
	std::string str = convert.to_bytes(wString);     // wstring => string

	return str;
}


std::string UnicodeToUTF8(const std::wstring& wstr)
{
	std::string ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.to_bytes(wstr);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}


std::wstring UTF8ToUnicode(const std::string& str)
{
	std::wstring ret;
	try {
		std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
		ret = wcv.from_bytes(str);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return ret;
}


std::string UnicodeToANSI(const std::wstring& wstr)
{
	std::string ret;
	std::mbstate_t state = {};
	const wchar_t* src = wstr.data();
	size_t len = std::wcsrtombs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< char[] > buff(new char[len + 1]);
		len = std::wcsrtombs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}


std::wstring ANSIToUnicode(const std::string& str)
{
	std::wstring ret;
	std::mbstate_t state = {};
	const char* src = str.data();
	size_t len = std::mbsrtowcs(nullptr, &src, 0, &state);
	if (static_cast<size_t>(-1) != len) {
		std::unique_ptr< wchar_t[] > buff(new wchar_t[len + 1]);
		len = std::mbsrtowcs(buff.get(), &src, len, &state);
		if (static_cast<size_t>(-1) != len) {
			ret.assign(buff.get(), len);
		}
	}
	return ret;
}


std::string UTF8ToANSI(const std::string& str)
{
	return UnicodeToANSI(UTF8ToUnicode(str));
}


std::string ANSIToUTF8(const std::string& str)
{
	return UnicodeToUTF8(ANSIToUnicode(str));
}