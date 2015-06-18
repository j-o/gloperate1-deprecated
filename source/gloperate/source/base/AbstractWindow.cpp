#include <gloperate/base/AbstractWindow.h>
#include <gloperate/base/make_unique.hpp>
#include <gloperate/tools/VirtualTimeController.h>


namespace gloperate
{

AbstractWindow::AbstractWindow()
: m_virtualTime(make_unique<VirtualTimeController>(nullptr))
{
}

AbstractWindow::~AbstractWindow()
{
}

VirtualTimeController * AbstractWindow::virtualTimeController() const
{
    return m_virtualTime.get();
}

} /* namespace gloperate */
