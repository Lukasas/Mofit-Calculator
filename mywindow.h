#pragma once

/*
 * Standard XToolkit and OSF/Motif include files.
 */
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <X11/Xmu/Editres.h>

/*
 * Public include files for widgets used in this file.
 */
#include <Xm/MainW.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/DrawingA.h>
#include <Xm/RowColumn.h>
#include <Xm/Label.h>
#include <Xm/MessageB.h>
#include <Xm/MenuShell.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/Text.h>
#include <Xm/TextF.h>

#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

#include "controller.h"
#include "logic.h"


class MyWindow
{
private:

	XtAppContext m_appContext;
	Widget m_topLevel;
	Widget m_mainWindow;
	Widget m_frame;

	Widget m_row_column_frame;
	Widget m_row_column_holder;
	Widget m_row_column;
	Widget m_display;
	Widget m_text_field_input;
	Widget m_Question;

	const std::string allowed_input;

	bool button_pressed;

	Atom WM_DELETE;

	Controller<MyWindow> *m_c;

	std::string get_widget_label_text(Widget & w);
	void set_input_text(std::string & s);
	std::string get_input_text();
public:
	MyWindow(int, char*[]);

	void InitComponents();

	void RunLoop();

	void Calculate(Widget widget, XtPointer user_data, XtPointer call_data);

	void Verify_Input_Text(Widget widget, XtPointer user_data, XtPointer call_data);

	void ButtonAddChar(Widget widget, XtPointer user_data, XtPointer call_data);
	void ButtonBSChar(Widget widget, XtPointer user_data, XtPointer call_data);
	void ButtonClear(Widget widget, XtPointer user_data, XtPointer call_data);
	void ButtonEvent(Widget widget, XtPointer user_data, XEvent * event, Boolean * cont);

	void QuitDialogResult(Widget widget, XtPointer user_data, XtPointer call_data);
	void QuitDialogShow(Widget widget, XtPointer user_data, XtPointer call_data);

	void StatusChange();

	virtual ~MyWindow();
};