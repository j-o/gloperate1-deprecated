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

class GLOPERATE_QTWIDGETS_API VirtualTimeControlWidget : public widgetzeug::DockableScrollAreaWidget
{
    Q_OBJECT

public:
    VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, const QString & title, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    virtual ~VirtualTimeControlWidget();

private:
    std::unique_ptr<TimePlayerWidget> m_timePlayerWidget;
};

} /* namespace gloperate_qtwidgets */
