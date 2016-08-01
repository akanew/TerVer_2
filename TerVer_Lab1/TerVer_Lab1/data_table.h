#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <QWidget>
#include "ui_data_table.h"

class Data_Table : public QWidget
{
	Q_OBJECT

public:
	Data_Table(QWidget *parent = 0);
	Data_Table(float* Array_Data_for_Normal_Distribution,int Count_Elements_in_Array_for_Normal_Distribution,int Max_Count_Elements_in_String_in_Data_Table,QWidget *parent = 0);
	~Data_Table();

private:
	Ui::Data_Table ui;
};

#endif // DATA_TABLE_H
