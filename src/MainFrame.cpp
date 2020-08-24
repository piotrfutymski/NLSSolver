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
    _iterTCtr = std::make_unique<wxTextCtrl>(_panel.get(), ID_TEXT0);
    _iterTCtr->SetSize(200, _iterTCtr->GetSize().GetY());
    _hboxl2->Add(_iterTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl2.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl3 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _errSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Żądana dokładność:"));
    _hboxl3->Add(_errSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _errTCtr = std::make_unique<wxTextCtrl>(_panel.get(), ID_TEXT1);
    _errTCtr->SetSize(200, _errTCtr->GetSize().GetY());
    _hboxl3->Add(_errTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl3.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl4 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _omegaSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Parametr omega:"));
    _hboxl4->Add(_omegaSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _omegaTCtr = std::make_unique<wxTextCtrl>(_panel.get(), ID_TEXT2);
    _omegaTCtr->SetSize(200, _omegaTCtr->GetSize().GetY());
    _hboxl4->Add(_omegaTCtr.get(), 1, wxEXPAND);
    _vBoxLeft->Add(_hboxl4.get(), 1, wxEXPAND | wxALL, 10);

    _vBoxLeft->Add(-1, 10);

    _hboxl5 = std::make_unique<wxBoxSizer>(wxHORIZONTAL);
    _startsolSText = std::make_unique<wxStaticText>(_panel.get(), wxID_ANY, wxT("Punkt początkowy:"));
    _hboxl5->Add(_startsolSText.get(), 0, wxLEFT | wxRIGHT | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
    _startsolTCtrl = std::make_unique<wxTextCtrl>(_panel.get(), ID_TEXT3);
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

    _countButton = std::make_unique<wxButton>(_panel.get(), ID_COUNTBUTTON, wxT("OBLICZ"));
    _vBoxRight->Add(_countButton.get(), 0, wxLEFT | wxBOTTOM | wxALIGN_CENTER_HORIZONTAL, 5);

    _mainHbox->Add(_vBoxRight.get(), 0);

    _panel->SetSizer(_mainHbox.get());

    _chbox0->SetValue(true);

    //EVENTS

    Connect(ID_CHBOX0, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainFrame::onToogle0));
    Connect(ID_CHBOX1, wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MainFrame::onToogle1));

    Connect(ID_COUNTBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onCalculate));
    Connect(ID_FILEBUTTON, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::onLoad));
    
    Connect(ID_TEXT0, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::onIterChanged));
    Connect(ID_TEXT1, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::onErrChanged));
    Connect(ID_TEXT2, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::onOmegaChanged));
    Connect(ID_TEXT3, wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MainFrame::onStartSolutionChanged));

    Centre();

}

void MainFrame::onToogle0(wxCommandEvent& WXUNUSED(event))
{
    if(_chbox0->GetValue())
    {
        _chbox1->SetValue(false);
    }
    else
    {
        _chbox0->SetValue(true);      
    }
    wxCommandEvent nullevent{};
    onStartSolutionChanged(nullevent);
          
}

void MainFrame::onToogle1(wxCommandEvent& WXUNUSED(event))
{
    if(_chbox1->GetValue())
    {
        _chbox0->SetValue(false);
    }
    else
    {
         _chbox1->SetValue(true); 
    }
    wxCommandEvent nullevent{};
    onStartSolutionChanged(nullevent);
         
}

void MainFrame::onCalculate(wxCommandEvent& WXUNUSED(event))
{
    std::vector<double> res;
    std::vector<interval_arithmetic::Interval<double>> ires;
    int r_val;
    if(_iterSet && _functionsLoaded && _errSet && _omegaSet && _startSolutionSet)
    {
        if(_chbox0->GetValue())
            r_val = solveEquations(res, f_table->f_x, f_table->df_x, _startSolutionD, _iterNum, _errV, _omegaV);
        else
            r_val = solveEquations(ires, f_table->fi_x, f_table->dfi_x, _startSolutionI, _iterNum, _errV, _omegaV);   
    }
    else
    {
        auto dialErr = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie ustawiono wszystkich parametrów"),wxT("Wynik"), wxOK | wxICON_ERROR);
        dialErr->ShowModal();
        return;
    }     
    if(r_val == 0)
    {
        if(_chbox0->GetValue())
        {
            auto dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Wynik:\n") + resToString(res), wxT("Wynik"), wxOK);
            dial->ShowModal();
        }
        else
        {
            auto dial = std::make_unique<wxMessageDialog>(nullptr, wxT("Wynik:\n") + resToString(ires), wxT("Wynik"), wxOK);
            dial->ShowModal();
        }
    }
    if(r_val == 1)
    {
        auto dialErr = std::make_unique<wxMessageDialog>(nullptr, wxT("Przekroczono dopuszczalną liczbę iteracji"),wxT("Wynik"), wxOK | wxICON_ERROR);
        dialErr->ShowModal();
    }
    if(r_val == 2)
    {
        auto dialErr = std::make_unique<wxMessageDialog>(nullptr, wxT("Nie udało się uzyskać wyniku - pochodna wynosiła 0 lub nastąpiło wyjście poza dziedzinę funkcji"),wxT("Wynik"), wxOK | wxICON_ERROR);
        dialErr->ShowModal();
    }
}

void MainFrame::onLoad(wxCommandEvent& WXUNUSED(event))
{
    auto dial = std::make_unique<wxFileDialog>(this);
    if(dial->ShowModal() == wxID_OK)
    {
        wxString fileName = dial->GetPath();

        void * so = dlopen(fileName, RTLD_NOW);   

        if(so == NULL)
        {
            auto dialErr = std::make_unique<wxMessageDialog>(nullptr, wxT("Wczytano nieprawidłowy plik"),wxT("Błąd"), wxOK | wxICON_ERROR);
            dialErr->ShowModal();
        }
        else
        {
            f_table = (APIs *)(dlsym(so, "api_table"));

            if(f_table == NULL)
            {
                auto dialErr = std::make_unique<wxMessageDialog>(nullptr, wxT("Brak odpowiedniej struktury w pliku .so"),wxT("Błąd"), wxOK | wxICON_ERROR);
                dialErr->ShowModal();
            }
            else
            {
                _loadedFileTCtr->SetForegroundColour("rgb(0,255,0)");
                _loadedFileTCtr->SetValue(fileName);
                _functionsLoaded = true;
            }     
        }
       
    }
}

void MainFrame::onIterChanged(wxCommandEvent& WXUNUSED(event))
{
    if(_iterTCtr->GetValue() == wxString(""))
    {
        _iterSet = false;
    }
    else
    {
        long v;
        if(!_iterTCtr->GetValue().ToLong(&v))
        {
            _iterSet = false;
            _iterTCtr->SetForegroundColour("rgb(255,0,0)");
        }
        else
        {
            _iterSet = true;
            _iterTCtr->SetForegroundColour("rgb(0,0,0)");
            _iterNum = v;
        }
        
    }
}

void MainFrame::onErrChanged(wxCommandEvent& WXUNUSED(event))
{
    if(_errTCtr->GetValue() == wxString(""))
    {
        _errSet = false;
    }
    else
    {
        double v;
        if(!_errTCtr->GetValue().ToDouble(&v))
        {
            _errSet = false;
            _errTCtr->SetForegroundColour("rgb(255,0,0)");
        }
        else
        {
            _errSet = true;
            _errTCtr->SetForegroundColour("rgb(0,0,0)");
            _errV = v;
        }
        
    }
}

void MainFrame::onOmegaChanged(wxCommandEvent& WXUNUSED(event))
{
    if(_omegaTCtr->GetValue() == wxString(""))
    {
        _omegaSet = false;
    }
    else
    {
        double v;
        if(!_omegaTCtr->GetValue().ToDouble(&v))
        {
            _omegaSet = false;
            _omegaTCtr->SetForegroundColour("rgb(255,0,0)");
        }
        else
        {
            _omegaSet = true;
            _omegaTCtr->SetForegroundColour("rgb(0,0,0)");
            _omegaV = v;
        }
        
    }
}

void MainFrame::onStartSolutionChanged(wxCommandEvent& WXUNUSED(event))
{
    if(_startsolTCtrl->GetValue() == wxString(""))
    {
        _startSolutionSet = false;
    }
    else
    {
       if(_chbox0->GetValue())
        {
            int status = wxStringToStartSolD(_startsolTCtrl->GetValue());
            if(status == 1)
            {
                _startSolutionSet = false;
                _startsolTCtrl->SetForegroundColour("rgb(255,0,0)");
            }
            else
            {
                _startSolutionSet = true;
                _startsolTCtrl->SetForegroundColour("rgb(0,0,0)");
            }
        }
        else
        {
            int status = wxStringToStartSolI(_startsolTCtrl->GetValue());
            if(status == 1)
            {
                _startSolutionSet = false;
                _startsolTCtrl->SetForegroundColour("rgb(255,0,0)");
            }
            else
            {
                _startSolutionSet = true;
                _startsolTCtrl->SetForegroundColour("rgb(0,0,0)");
            }
        }
        
    }
    
    
}


int MainFrame::wxStringToStartSolD(const wxString & s)
{
    auto tmp = s;
    _startSolutionD.clear();

    while(tmp.Len() != 0)
    {
        wxString rest;
        auto sub = tmp.BeforeFirst(';',&rest);
        tmp = rest;

        double v;

        if(!sub.ToDouble(&v))
            return 1;
        else
            _startSolutionD.push_back(v);
    }
    return 0;
}

int MainFrame::wxStringToStartSolI(const wxString & s)
{
    auto tmp = s;
    _startSolutionI.clear();

    while(tmp.Len() != 0)
    {
        wxString rest;
        auto sub = tmp.BeforeFirst('[',&rest);
        tmp = rest;
        sub = tmp.BeforeFirst(';', &rest);
        tmp = rest;

        double a,b;

        if(!sub.ToDouble(&a))
            return 1;

        sub = tmp.BeforeFirst(']',&rest);
        tmp = rest;

        if(!sub.ToDouble(&b))
            return 1;

        sub = tmp.BeforeFirst(';', &rest);
        tmp = rest;

        _startSolutionI.push_back({a,b});
    }
    return 0;
}


wxString MainFrame::resToString(const std::vector<double> & res)
{
    wxString rstring;
    for(auto & x: res)
    {
        auto ix = interval_arithmetic::Interval<double>{x};

        std::string l,r;
        ix.IEndsToStrings(l,r);
        rstring += wxString(l);
        rstring += "\n";
    }
    return rstring;
}

wxString MainFrame::resToString(const std::vector<interval_arithmetic::Interval<double>> & res)
{
    wxString rstring;
    for(auto & x: res)
    {
        auto v = x;
        std::string l,r;
        v.IEndsToStrings(l,r);
        rstring += "[";
        rstring += wxString(l);
        rstring += " ; ";
        rstring += wxString(r);
        rstring += "]";
        rstring += "\n";
    }
    return rstring;
}
