#pragma once

#ifdef SAUCA_EXPORT
	#define SAUCA_API __declspec(dllexport)
#else
	#define SAUCA_API __declspec(dllimport)	

#endif