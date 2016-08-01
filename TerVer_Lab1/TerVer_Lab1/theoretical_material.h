#ifndef THEORETICAL_MATERIAL_H
#define THEORETICAL_MATERIAL_H

#include <QWidget>
#include "ui_theoretical_material.h"

class Theoretical_Material : public QWidget
{
	Q_OBJECT

public:
	Theoretical_Material(QWidget *parent = 0);
	Theoretical_Material(int Type_Displayed_Page,QWidget *parent = 0);
	~Theoretical_Material();

	int Current_Page;

private:
	Ui::Theoretical_Material ui;

private slots:
	void Choice_Page_to_Show(int Page_Number);
	void Previous_Page_Emit();
	void Next_Page_Emit();

signals: 
     void Select_SIGNAL(int);
};

#endif // THEORETICAL_MATERIAL_H
