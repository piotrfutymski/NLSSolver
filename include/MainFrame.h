#pragma once
#include <memory>
#include <dlfcn.h>
#include <wx/wx.h>
#include "Solver.h"
#include "Interval.h"

struct APIs{
double (*f_x)(const std::vector<double> & X, int n);
double (*df_x)(const std::vector<double> & X, int n);
interval_arithmetic::Interval<double> (*fi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n);
interval_arithmetic::Interval<double> (*dfi_x)(const std::vector<interval_arithmetic::Interval<double>> & X, int n);
};

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString & title);

private:

    void onToogle0(wxCommandEvent & event);
    void onToogle1(wxCommandEvent & event);

    void onCalculate(wxCommandEvent & event);

    void onLoad(wxCommandEvent & event);

    void onIterChanged(wxCommandEvent & event);
    void onErrChanged(wxCommandEvent & event);
    void onOmegaChanged(wxCommandEvent & event);
    void onStartSolutionChanged(wxCommandEvent & event);

    int wxStringToStartSolD(const wxString & s);
    int wxStringToStartSolI(const wxString & s);

    static wxString resToString(const std::vector<double> & res);
    static wxString resToString(const std::vector<interval_arithmetic::Interval<double>> & res);

private:

    bool _functionsLoaded = false;
    APIs * f_table;

    bool _iterSet = false;
    int _iterNum;

    bool _errSet = false;
    double _errV;

    bool _omegaSet = false;
    double _omegaV;

    bool _startSolutionSet = false;
    std::vector<double> _startSolutionD;
    std::vector<interval_arithmetic::Interval<double>> _startSolutionI;

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

};

const int ID_FILEBUTTON = 100;
const int ID_COUNTBUTTON = 101;

const int ID_CHBOX0 = 200;
const int ID_CHBOX1 = 201;

const int ID_TEXT0 = 300;
const int ID_TEXT1 = 301;
const int ID_TEXT2 = 302;
const int ID_TEXT3 = 303;
