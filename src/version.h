#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "11";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 4;
	static const long REVISION  = 65;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 171;
	#define RC_FILEVERSION 0,1,4,65
	#define RC_FILEVERSION_STRING "0, 1, 4, 65\0"
	static const char FULLVERSION_STRING [] = "0.1.4.65";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 5;
	

}
#endif //VERSION_H
