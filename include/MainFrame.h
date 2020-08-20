#pragma once
#include <memory>
#include <wx/wx.h>
#include "Interval.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString & title);

private:

    void onToogle0(wxCommandEvent & event);
    void onToogle1(wxCommandEvent & event);
    void onToogle2(wxCommandEvent & event);

    void onCalculate(wxCommandEvent & event);

    void onLoad(wxCommandEvent & event);

private:

    std::unique_ptr<wxPanel> _panel;

    // sizers

    std::unique_ptr<wxBoxSizer> _mainHbox;

    std::unique_ptr<wxBoxSizer> _vBoxLeft;
    std::unique_ptr<wxBoxSizer> _vBoxRight;

    std::unique_ptr<wxBoxSizer> _hboxl1;
    std::unique_ptr<wxBoxSizer> _hboxl2;
    std::unique_ptr<wxBoxSizer> _hboxl3;
    std::unique_ptr<wxBoxSizer> _hboxl4;
    std::unique_ptr<wxBoxSizer> _hboxl5;

    std::unique_ptr<wxBoxSizer> _hboxr1;

    // buttons

    std::unique_ptr<wxButton> _fileButton;
    std::unique_ptr<wxButton> _countButton;

    // textCtrls

    std::unique_ptr<wxTextCtrl> _loadedFileTCtr;
    std::unique_ptr<wxTextCtrl> _iterTCtr;
    std::unique_ptr<wxTextCtrl> _errTCtr;
    std::unique_ptr<wxTextCtrl> _omegaTCtr;
    std::unique_ptr<wxTextCtrl> _startsolTCtrl;

    // static text

    std::unique_ptr<wxStaticText> _iterSText;
    std::unique_ptr<wxStaticText> _errSText;
    std::unique_ptr<wxStaticText> _omegaSText;
    std::unique_ptr<wxStaticText> _startsolSText;
    std::unique_ptr<wxStaticText> _artSText;

    //checkbox

    std::unique_ptr<wxCheckBox> _chbox0;
    std::unique_ptr<wxCheckBox> _chbox1;
    std::unique_ptr<wxCheckBox> _chbox2;

};

const int ID_FILEBUTTON = 100;
const int ID_COUNTBUTTON = 101;

const int ID_CHBOX0 = 200;
const int ID_CHBOX1 = 201;
const int ID_CHBOX2 = 202;