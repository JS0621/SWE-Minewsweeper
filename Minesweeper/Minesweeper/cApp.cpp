#include "cApp.h"
#include "cMain.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	cWindow = new cMain();
	cWindow->Show();
	return true;
}
