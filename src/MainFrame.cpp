#include "MainFrame.h"


MainFrame::MainFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(720,420))
{
    _panel = std::make_unique<wxPanel>(this, -1);

    _mainHbox = std::make_unique<wxBoxSizer>(wxHORIZONTAL);

    _vBoxLeft = std::make_unique<wxBoxSizer>(wxVERTICAL);
    _vBoxRight = std::make_unique<wxBoxSizer>(wxVERTICAL);

    _hboxl1 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _fileButton = std::make_unique<wxButton>(_panel.get(), ID_FILEBUTTON, wxT("Wczytaj plik dll"));
    _hboxl1->Add(_fileButton.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _loadedFileTCtr = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY, wxT("brak załadowanego pliku"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    _loadedFileTCtr->SetSize(200, _loadedFileTCtr->GetSize().GetY());
    _loadedFileTCtr->SetForegroundColour("rgb(255,0,0)");
    _hboxl1->Add(_loadedFileTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl1.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl2 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _iterSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Maksymalna ilość iteracji:"));
    _hboxl2->Add(_iterSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _iterTCtr = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY);
    _iterTCtr->SetSize(200, _iterTCtr->GetSize().GetY());
    _hboxl2->Add(_iterTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl2.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl3 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _errSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Żądana dokładność:"));
    _hboxl3->Add(_errSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _errTCtr = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY);
    _errTCtr->SetSize(200, _errTCtr->GetSize().GetY());
    _hboxl3->Add(_errTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl3.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl4 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _omegaSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Parametr omega:"));
    _hboxl4->Add(_omegaSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _omegaTCtr = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY);
    _omegaTCtr->SetSize(200, _omegaTCtr->GetSize().GetY());
    _hboxl4->Add(_omegaTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl4.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl5 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _startsolSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Punkt początkowy:"));
    _hboxl5->Add(_startsolSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _startsolTCtrl = std::make_unique<wxTextCtrl>(_panel.get(), wxID_ANY);
    _hboxl5->Add(_startsolTCtrl.get(), 1, wxEXPAND);
    _startsolTCtrl->SetSize(200, 300);
    _vBoxLeft->Add(_hboxl5.get(), 1, wxEXPAND | wxALL, 10);

    _mainHbox->Add(_vBoxLeft.get(), 1, wxEXPAND);

    _artSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Wybór arytmetyki"));
    _vBoxRight->Add(_artSText.get(), 1,  wxLEFT | wxRIGHT | wxTOP | wxALIGN_CENTER_HORIZONTAL, 10);

    _vBoxRight->Add(-1, 30);

    _hboxr1 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _chbox0 = std::make_unique<wxCheckBox>(_panel.get(), ID_CHBOX0, wxT("Zmiennoprzecinkowa"));
    _hboxr1->Add(_chbox0.get());
    _chbox1 = std::make_unique<wxCheckBox>(_panel.get(), ID_CHBOX1, wxT("Przedziałowa"));
    _hboxr1->Add(_chbox1.get(), 0, wxLEFT, 10);
    _vBoxRight->Add(_hboxr1.get(), 0, wxEXPAND | wxALL, 10);

    _vBoxRight->Add(-1, 10);

    _chbox2 = std::make_unique<wxCheckBox>(_panel.get(), ID_CHBOX2, wxT("Przedziałowa z wejściem przedziałowym"));
    _vBoxRight->Add(_chbox2.get(), 0, wxEXPAND | wxALL, 10);

    _vBoxRight->Add(-1, 10);

    _countButton = std::make_unique<wxButton>(_panel.get(), ID_COUNTBUTTON, wxT("OBLICZ"));
    _vBoxRight->Add(_countButton.get(), 0, wxLEFT | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 5);

    _mainHbox->Add(_vBoxRight.get(), 0);

    _panel->SetSizer(_mainHbox.get());

    _chbox0->SetValue(true);

    //EVENTS

    Connect(ID_CHBOX0, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainFrame::onToogle0));
    Connect(ID_CHBOX1, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainFrame::onToogle1));
    Connect(ID_CHBOX2, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainFrame::onToogle2));

    Connect(ID_COUNTBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onCalculate));
    Connect(ID_FILEBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onLoad));

    Centre();

}

void MainFrame::onToogle0(wxCommandEvent& WXUNUSED(event))
{
    if(_chbox0->GetValue())
    {
        _chbox1->SetValue(false);
        _chbox2->SetValue(false);
    }
    else
        _chbox0->SetValue(true);   
}

void MainFrame::onToogle1(wxCommandEvent& WXUNUSED(event))
{
    if(_chbox1->GetValue())
    {
        _chbox0->SetValue(false);
        _chbox2->SetValue(false);
    }
    else
        _chbox1->SetValue(true);   
}

void MainFrame::onToogle2(wxCommandEvent& WXUNUSED(event))
{
    if(_chbox2->GetValue())
    {
        _chbox1->SetValue(false);
        _chbox0->SetValue(false);
    }
    else
        _chbox2->SetValue(true);   
}

void MainFrame::onCalculate(wxCommandEvent& WXUNUSED(event))
{
    interval_arithmetic::Interval<double> a(1,2);
    std::string s,ss;
    a.IEndsToStrings(s, ss);
    auto dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Wynik:0"+s+ss ),wxT("Wynik"), wxOK);
    dial->ShowModal();
}

void MainFrame::onLoad(wxCommandEvent& WXUNUSED(event))
{
    auto dial = std::make_unique<wxFileDialog>(this);
    if(dial->ShowModal() == wxID_OK)
    {
        wxString fileName = dial->GetPath();
        _loadedFileTCtr->SetForegroundColour("rgb(0,255,0)");
        _loadedFileTCtr->SetValue(fileName);
    }
}
