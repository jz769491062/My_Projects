#pragma once


#ifndef APPDLL1_EXPORTS
#define APPDLL __declspec( dllimport ) 
#else
#define APPDLL __declspec( dllexport ) 
#endif // !APPDLL1_EXPORTS

