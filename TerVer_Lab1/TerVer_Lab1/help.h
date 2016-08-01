#ifndef HELP_H
#define HELP_H

#include <QWidget>
#include "ui_help.h"

class Help : public QWidget
{
	Q_OBJECT

public:
	Help(QWidget *parent = 0);
	Help(int Type_Displayed_Page,QWidget *parent = 0);
	~Help();

	int Current_Page;

private:
	Ui::Help ui;

private slots:
	void Choice_Page_to_Show(int Page_Number);
	void Previous_Page();
	void Next_Page();
};

#endif // HELP_H
