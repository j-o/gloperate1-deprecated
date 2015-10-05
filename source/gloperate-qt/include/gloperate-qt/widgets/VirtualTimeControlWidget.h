#pragma once


#include <memory>

#include <widgetzeug/DockableScrollAreaWidget.h>

#include <gloperate-qt/gloperate-qt_api.h>


namespace gloperate
{
    class VirtualTimeController;
}  // namespace gloperate


namespace gloperate_qt
{

class TimePlayerWidget;

class GLOPERATE_QT_API VirtualTimeControlWidget : public widgetzeug::DockableScrollAreaWidget
{
    Q_OBJECT

public:
    VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, const QString & title, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent = nullptr, Qt::WindowFlags flags = 0);
    virtual ~VirtualTimeControlWidget();

private:
    std::unique_ptr<TimePlayerWidget> m_timePlayerWidget;
};

} /* namespace gloperate_qt */
