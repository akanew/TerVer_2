#include "data_table.h"

Data_Table::Data_Table(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Data_Table::Data_Table(float* Array_Data_for_Normal_Distribution,int Count_Elements_in_Array_for_Normal_Distribution,int Max_Count_Elements_in_String_in_Data_Table,QWidget *parent)
: QWidget(parent)
{
	ui.setupUi(this);

	int Column_Count=Max_Count_Elements_in_String_in_Data_Table;
	int Row_Count=Count_Elements_in_Array_for_Normal_Distribution/Max_Count_Elements_in_String_in_Data_Table;

	ui.Data_Table_for_Normal_Distribution->setRowCount(Row_Count);
	ui.Data_Table_for_Normal_Distribution->setColumnCount(Column_Count);

	QTableWidgetItem *item;
	int Current=0;

	for(int i=0;i<Row_Count;i++)
		for(int j=0;j<Column_Count;j++)
		{
			item = new  QTableWidgetItem(QString::number(Array_Data_for_Normal_Distribution[Current],'g',4));
			item->setTextAlignment(Qt::AlignCenter);
			ui.Data_Table_for_Normal_Distribution->setItem(i,j, item);

			Current++;
		}	
}

Data_Table::~Data_Table()
{

}