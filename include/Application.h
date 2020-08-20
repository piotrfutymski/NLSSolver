#pragma once
#include <memory>
#include <wx/wx.h>
#include "MainFrame.h"

class Application : public wxApp
{
public:
    virtual bool OnInit();

private:

    std::unique_ptr<MainFrame> _mframe;
};