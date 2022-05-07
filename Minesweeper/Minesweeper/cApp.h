#pragma once
#include "wx/wx.h"

class cMain;

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* cWindow;

public:
	virtual bool OnInit();
};

