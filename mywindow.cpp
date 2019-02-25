#include "mywindow.h"

MyWindow::MyWindow(int argc, char *argv[]) :
	m_c(new Controller<MyWindow>()),
	allowed_input("1234567890., /*-+()"),
	button_pressed(false)
{
	XtSetLanguageProc(NULL, (XtLanguageProc)NULL, NULL);

	// Closing question
	char *fall[] = {
		"*question.dialogTitle: Quitting",
		"*question.messageString: Are you sure you would like to exit?",
		"*question.okLabelString: Yes",
		"*question.cancelLabelString: No",
		"*question.messageAlignment: XmALIGNMENT_CENTER",
		"*bar.file.labelString: File",
		0};

	m_topLevel = XtVaAppInitialize(
		&m_appContext,
		"Calculator",
		NULL, 0,
		&argc, argv,
		fall,
		XmNdeleteResponse, XmDO_NOTHING,
		NULL);

	m_Question = XmCreateQuestionDialog(
		m_topLevel,
		"question",
		NULL,
		0);

	XtVaSetValues(
		m_Question,
		XmNdialogStyle,
		XmDIALOG_FULL_APPLICATION_MODAL,
		NULL);

	XtUnmanageChild(XmMessageBoxGetChild(m_Question, XmDIALOG_HELP_BUTTON));
	m_c->RegisterCallback(this, m_Question, XmNokCallback, &MyWindow::QuitDialogResult, (XtPointer)1);
	//m_c->RegisterCallback(this, m_Question, XmNcancelCallback, &MyWindow::QuitDialogResult, (XtPointer)0);

	m_mainWindow = XtVaCreateManagedWidget(
		"mainWin",
		xmMainWindowWidgetClass,
		m_topLevel,
		XmNcommandWindowLocation, XmCOMMAND_BELOW_WORKSPACE,
		XmNwidth, 800,
		XmNheight, 600,
		NULL);

	WM_DELETE = XInternAtom(XtDisplay(m_topLevel), "WM_DELETE_WINDOW", False);
	m_c->RegisterWMProtocolCallback(this, m_topLevel, WM_DELETE, &MyWindow::QuitDialogShow, NULL);
	XmActivateWMProtocol(m_topLevel, WM_DELETE);
	XtAddEventHandler(m_topLevel, 0, True, _XEditResCheckMessages, NULL);
}

void MyWindow::RunLoop()
{
	XtRealizeWidget(m_topLevel);
	XtAppMainLoop(m_appContext);
}

MyWindow::~MyWindow()
{
	if (m_c)
		delete m_c;
}

void MyWindow::InitComponents()
{
	Widget holder;
	m_frame = XtVaCreateManagedWidget(
		"frame",
		xmFrameWidgetClass,
		m_mainWindow,
		NULL);

	m_row_column_frame = XtVaCreateManagedWidget(
		"rowColumn_frame",
		xmRowColumnWidgetClass,
		m_frame,
		XmNentryAlignment, XmALIGNMENT_CENTER,
		XmNorientation, XmVERTICAL,
		NULL);

	m_display = XtVaCreateManagedWidget(
		"label",
		xmLabelWidgetClass,
		m_row_column_frame,
		NULL);

	m_text_field_input = XmCreateScrolledText(m_row_column_frame, "scroll", NULL, 0);
	XtVaSetValues(m_text_field_input,
				XmNwordWrap, False,
				XmNmaxLength, 10000,
				XmNheight, 35,
				XmNwidth, 800,
				NULL);
	XtManageChild(m_text_field_input);


	m_row_column_holder = XtVaCreateManagedWidget(
		"rowColumn_holder",
		xmRowColumnWidgetClass,
		m_row_column_frame,
		XmNorientation, XmVERTICAL,
		XmNentryAlignment, XmALIGNMENT_CENTER,
		NULL);

	// ( ) CLEAR
	m_row_column = XtVaCreateManagedWidget(
		"rowColumn_row",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmHORIZONTAL,
		NULL);

	holder = XtVaCreateManagedWidget(
		"(",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		")",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);

	holder = XtVaCreateManagedWidget(
		"CL",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonClear, NULL);

	m_row_column_holder = XtVaCreateManagedWidget(
		"rowColumn",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmHORIZONTAL,
		NULL);

	m_row_column = XtVaCreateManagedWidget(
		"rowColumn",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmVERTICAL,
		NULL);

	holder = XtVaCreateManagedWidget(
		"7",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"4",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"1",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		".",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);

	m_row_column = XtVaCreateManagedWidget(
		"rowColumn",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmVERTICAL,
		NULL);

	holder = XtVaCreateManagedWidget(
		"8",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"5",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"2",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"0",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	m_row_column = XtVaCreateManagedWidget(
		"rowColumn",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmVERTICAL,
		NULL);

	holder = XtVaCreateManagedWidget(
		"9",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"6",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"3",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"BS",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonBSChar, NULL);


	m_row_column = XtVaCreateManagedWidget(
		"rowColumn",
		xmRowColumnWidgetClass,
		m_row_column_holder,
		XmNorientation, XmVERTICAL,
		NULL);

	holder = XtVaCreateManagedWidget(
		"/",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);

	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"*",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"-",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	holder = XtVaCreateManagedWidget(
		"+",
		xmPushButtonWidgetClass,
		m_row_column,
		NULL);
	m_c->RegisterCallback(this, holder, XmNactivateCallback, &MyWindow::ButtonAddChar, NULL);
	XmMainWindowSetAreas(m_mainWindow, NULL, NULL, NULL, NULL, m_frame);

	/*m_c->RegisterCallback(this, m_btnClear, XmNactivateCallback, &MyWindow::ClearButton, NULL);
	m_c->RegisterCallback(this, m_btnQuit, XmNactivateCallback, &MyWindow::QuitButton, NULL);
*/
	m_c->RegisterCallback(this, m_text_field_input, XmNvalueChangedCallback, &MyWindow::Calculate, NULL);
	m_c->RegisterCallback(this, m_text_field_input, XmNmodifyVerifyCallback, &MyWindow::Verify_Input_Text, NULL);

	StatusChange();
}

void MyWindow::Calculate(Widget widget, XtPointer user_data, XtPointer call_data)
{
	// Call Calculation
	StatusChange();
}

void MyWindow::Verify_Input_Text(Widget widget, XtPointer user_data, XtPointer call_data)
{
	XmTextVerifyCallbackStruct *ver = (XmTextVerifyCallbackStruct*)call_data;
	XmTextBlock verText = ver->text;
	std::string test_input = std::string(verText->ptr);
	if (allowed_input.find(test_input) == std::string::npos)
	{
		if (!button_pressed)
		{
			ver->doit = False;
		}
	}
	button_pressed = false;
}

void MyWindow::ButtonAddChar(Widget widget, XtPointer user_data, XtPointer call_data)
{
	std::string input = get_input_text();
	input.append(get_widget_label_text(widget));
	button_pressed = true;
	set_input_text(input);
}

void MyWindow::ButtonBSChar(Widget widget, XtPointer user_data, XtPointer call_data)
{
	std::string input = get_input_text();
	input.pop_back();
	button_pressed = true;
	set_input_text(input);
}

void MyWindow::ButtonClear(Widget widget, XtPointer user_data, XtPointer call_data)
{
	std::string input = "";
	set_input_text(input);
}

void MyWindow::ButtonEvent(Widget widget, XtPointer user_data, XEvent *event, Boolean *cont)
{

}


void MyWindow::QuitDialogResult(Widget widget, XtPointer user_data, XtPointer call_data)
{
	exit(0);
}

void MyWindow::QuitDialogShow(Widget widget, XtPointer user_data, XtPointer call_data)
{
	XtManageChild(m_Question);
}

void MyWindow::StatusChange()
{
	std::string out;
	char * test = XmTextGetString(m_text_field_input);
	out = test;
	XtFree(test);
	try
	{
		out = Make_Calculation(out);
	}
	catch (const int err)
	{
		switch (err)
		{
			case 1:
				out = "Missing brackets !";
			break;
			case 2:
				out = "Syntax Error";
			break;
			default:
				out = "Unknown Error";
			break;
		}
	}

	XmString Output = XmStringCreate((char *)out.c_str(), XmFONTLIST_DEFAULT_TAG);
	XtVaSetValues(m_display, XmNlabelString, Output, NULL);
	XmStringFree(Output);
}

std::string MyWindow::get_widget_label_text(Widget & w)
{
	std::string out;
	XmString str;
	XtVaGetValues(w, XmNlabelString, &str, NULL);
	char * temp = XmCvtXmStringToCT(str);
	out = temp;
	XtFree(temp);
	return out;
}

void MyWindow::set_input_text(std::string & s)
{
	XmTextSetString(m_text_field_input, (char*)s.c_str());
}

std::string MyWindow::get_input_text()
{
	std::string out;
	char * test = XmTextGetString(m_text_field_input);
	out = test;
	XtFree(test);
	return out;
}