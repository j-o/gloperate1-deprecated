#pragma once


#include <memory>

#include <widgetzeug/DockableScrollAreaWidget.h>

#include <gloperate-qtwidgets/gloperate-qtwidgets_api.h>


namespace gloperate
{
    class VirtualTimeController;
}  // namespace gloperate


namespace gloperate_qtwidgets
{

class TimePlayerWidget;

class VirtualTimeControlWidget : public widgetzeug::DockableScrollAreaWidget
{
    Q_OBJECT

public:
    VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent = nullptr);

private:
    std::unique_ptr<TimePlayerWidget> m_timePlayerWidget;
};

} /* namespace gloperate_qtwidgets */
