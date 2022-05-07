#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = 10;
	int nFieldHeight = 10;
	wxButton** btn;
	int* mField = nullptr;
	bool FirstClick = true;

	void OnClick(wxCommandEvent& evt);
	wxDECLARE_EVENT_TABLE();

};

