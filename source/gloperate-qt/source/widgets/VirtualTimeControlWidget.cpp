#include <gloperate-qt/widgets/VirtualTimeControlWidget.h>

#include <gloperate-qt/widgets/TimePlayerWidget.h>


using namespace widgetzeug;


namespace gloperate_qt
{

VirtualTimeControlWidget::VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, const QString & title, QWidget * parent, Qt::WindowFlags flags)
:   DockableScrollAreaWidget(title, parent, flags)
,   m_timePlayerWidget(new TimePlayerWidget(controller, this))
{
    addWidget(m_timePlayerWidget.get());
}

VirtualTimeControlWidget::VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent, Qt::WindowFlags flags)
:   VirtualTimeControlWidget(controller, "", parent, flags)
{
}

VirtualTimeControlWidget::~VirtualTimeControlWidget()
{
}

} /* namespace gloperate_qt */
