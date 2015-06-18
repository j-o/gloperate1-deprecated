#include <gloperate-qtwidgets/VirtualTimeControlWidget.h>

#include <gloperate-qtwidgets/TimePlayerWidget.h>


using namespace widgetzeug;


namespace gloperate_qtwidgets
{

VirtualTimeControlWidget::VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, const QString & title, QWidget * parent, Qt::WindowFlags flags)
:   DockableScrollAreaWidget(title, parent, flags)
,   m_timePlayerWidget(new TimePlayerWidget(controller, this))
{
    m_timePlayerWidget->setWindowTitle("");
    addWidget(m_timePlayerWidget.get());
}

VirtualTimeControlWidget::VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent, Qt::WindowFlags flags)
:   VirtualTimeControlWidget(controller, "", parent, flags)
{
}

VirtualTimeControlWidget::~VirtualTimeControlWidget()
{
}

} /* namespace gloperate_qtwidgets */
