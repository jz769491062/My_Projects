#pragma once
#include "export___.h"
class APPDLL baseTest
{
public:
	baseTest();
	~baseTest();
};

class APPDLL MyTest : public baseTest
{
public:
	MyTest();
	~MyTest();
};

class APPDLL TestAdmin
{
public:
	TestAdmin();
	baseTest * test;
};

