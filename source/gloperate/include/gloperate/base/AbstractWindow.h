#pragma once

#include <gloperate/gloperate_api.h>

#include <memory>


namespace gloperate
{

class VirtualTimeController;

class GLOPERATE_API AbstractWindow {
public:
    AbstractWindow();
    virtual ~AbstractWindow();

    VirtualTimeController * virtualTimeController() const;

protected:
    std::unique_ptr<VirtualTimeController> m_virtualTime;
};

} /* namespace gloperate */
