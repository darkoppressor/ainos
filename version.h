/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef version_h
#define version_h

#include <string>

namespace Version{
	//Build date
	static const char YEAR[]="2015";
	static const char MONTH[]="02";
	static const char DAY[]="13";

	//Version
	static const int MAJOR=1;
	static const int MINOR=1;
	static const int MICRO=0;

	//Status
	static const char STATUS[]="release";

	//Engine version
	static const std::string ENGINE_VERSION="1.2.3";

	//Engine date
	static const std::string ENGINE_DATE="2015-01-28";
}

#endif
