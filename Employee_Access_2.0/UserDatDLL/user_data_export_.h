#pragma once

#ifndef USER_DATA_EXPORT_
#define USER_DATA_EXPORT_ _declspec(dllimport)
#else
#define USER_DATA_EXPORT_ _declspec(dllexport)
#endif // !1

