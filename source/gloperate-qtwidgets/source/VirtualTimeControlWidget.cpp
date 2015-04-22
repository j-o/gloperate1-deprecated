#include <gloperate-qtwidgets/VirtualTimeControlWidget.h>

#include <gloperate-qtwidgets/TimePlayerWidget.h>


using namespace widgetzeug;


namespace gloperate_qtwidgets
{

VirtualTimeControlWidget::VirtualTimeControlWidget(gloperate::VirtualTimeController * controller, QWidget * parent)
:   DockableScrollAreaWidget(parent)
,   m_timePlayerWidget(new TimePlayerWidget(controller, this))
{
    addWidget(m_timePlayerWidget.get());
}

} /* namespace gloperate_qtwidgets */
