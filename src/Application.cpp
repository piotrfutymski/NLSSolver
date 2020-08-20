#include "Application.h"

bool Application::OnInit()
{
    _mframe = std::make_unique<MainFrame>( wxT("NLSSolver"));
    _mframe->Show( true );
    return true;
}
