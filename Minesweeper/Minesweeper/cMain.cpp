#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(30,30), wxSize(800,800))
{
	btn = new wxButton * [nFieldWidth * nFieldHeight];
	wxGridSizer* grid = new wxGridSizer(nFieldWidth, nFieldHeight, 0, 0);

	mField = new int[nFieldWidth * nFieldHeight];

	for (int x = 0; x < nFieldWidth; ++x) {
		for (int y = 0; y < nFieldHeight; ++y) {
			btn[y * nFieldWidth + x] = new wxButton(this, 1000 + ( y* nFieldWidth + x));
			grid->Add(btn[y * nFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnClick, this);
			mField[y * nFieldWidth + x] = 0;
		}
	}
	this->SetSizer(grid);
	grid->Layout();

}

cMain::~cMain()
{
	delete[] btn;
}

void cMain::OnClick(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 1000) % nFieldWidth;
	int y = (evt.GetId() - 1000) / nFieldHeight;
	
	//Generate minefield on first click
	if (FirstClick) {
		int mines = 30;
		
		while (mines) {
			int rx = rand() % nFieldWidth;
			int ry = rand() % nFieldHeight;

			if (mField[ry * nFieldWidth + rx] == 0 && rx != x && ry != y) {
				mField[ry * nFieldWidth + rx] = -1;
				--mines;
			}
		}
		FirstClick = false;
	}
	
	//Disable Button
	btn[y * nFieldWidth + x]->Enable(false);

	//Check if player hit mine
	if (mField[y * nFieldWidth + x] == -1) {
		wxMessageBox("BOOOOOOM !! - Game Over");

		//reset game
		FirstClick = true;
		for (int x = 0; x < nFieldWidth; ++x) {
			for (int y = 0; y < nFieldHeight; ++y) {
				mField[y * nFieldWidth + x] = 0;
				btn[y * nFieldWidth + x]->SetLabel("");
				btn[y * nFieldWidth + x]->Enable(true);
			}
		}
	}
	else {
		//Count Neighboring mines
		int mine_count = 0;
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {

				if ((x + i >= 0) && (x + i < nFieldWidth) && (y + j >= 0) && (y + j < nFieldHeight)) {
					if (mField[(y + j) * nFieldWidth + (x + i) == -1])
						mine_count++;
				}
			}
		}
		//Update button label if mine_count is > 0
		if (mine_count > 0) {
			btn[y * nFieldWidth + x]->SetLabel(std::to_string(mine_count));
		}
	}

	evt.Skip();
}


