#include "terver_lab1.h"

TerVer_Lab1::TerVer_Lab1(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	//Определение кодировки
	QTextCodec *codec = QTextCodec::codecForName("Windows-1251");
	QTextCodec::setCodecForCStrings (codec);

	//Переход между страницами
	connect(ui.Main_Page_Previous_Button, SIGNAL(clicked()), this, SLOT(Change_Stack_Main_Page_Previous()));
	connect(ui.Main_Page_Next_Button, SIGNAL(clicked()), this, SLOT(Change_Stack_Main_Page_Next()));
	//Переход между подстраницами
	connect(ui.Page_1_Previous_Button_A, SIGNAL(clicked()), this, SLOT(Change_Stack_Page_1()));
	connect(ui.Page_1_Next_Button_A, SIGNAL(clicked()), this, SLOT(Change_Stack_Page_1()));
	connect(ui.Page_1_Previous_Button_B, SIGNAL(clicked()), this, SLOT(Change_Stack_Page_1()));
	connect(ui.Page_1_Next_Button_B, SIGNAL(clicked()), this, SLOT(Change_Stack_Page_1()));
	//Открытие файлов
	connect(ui.Load_Button_for_Normal_Distribution, SIGNAL(clicked()), this, SLOT(Load_Data_from_File_for_Normal_Distribution()));
	connect(ui.Load_Button_for_Binomial_Distribution, SIGNAL(clicked()), this, SLOT(Load_Data_from_File_for_Binomial_Distribution()));
	connect(ui.Load_Button_for_Normal_Distribution_1, SIGNAL(clicked()), this, SLOT(Load_Data_from_File_for_Normal_Distribution_1()));
	connect(ui.Load_Button_for_Normal_Distribution_2, SIGNAL(clicked()), this, SLOT(Load_Data_from_File_for_Normal_Distribution_2()));
	connect(this, SIGNAL( Select_Array_SIGNAL(float*,int)), this, SLOT(Load_Data_from_File(float*,int)));
	//Формирование таблиц
	connect(ui.Create_Table_for_Normal_Distribution, SIGNAL(clicked()), this, SLOT(Build_Table_for_Normal_Distribution()));
	connect(ui.Calculate_Button, SIGNAL(clicked()), this, SLOT(Calculate_Action_for_Normal_Distribution()));
	connect(ui.Testing_Hypothesis_Normal_Distribution_Button, SIGNAL(clicked()), this, SLOT(Testing_Hypothesis_Normal_Distribution()));
	connect(ui.Testing_Hypothesis_Binomial_Distribution_Button, SIGNAL(clicked()), this, SLOT(Testing_Hypothesis_Binomial_Distribution()));
	connect(ui.Create_Table_for_Binomial_Distribution, SIGNAL(clicked()), this, SLOT(Build_Table_for_Binomial_Distribution()));
	connect(ui.Create_Table_for_Normal_Distribution_1, SIGNAL(clicked()), this, SLOT(Build_Table_for_Normal_Distribution_1()));
	connect(ui.Create_Table_for_Normal_Distribution_2, SIGNAL(clicked()), this, SLOT(Build_Table_for_Normal_Distribution_2()));
	connect(ui.Comparison_Two_Variances_for_Normal_Distributions_Button, SIGNAL(clicked()), this, SLOT(Comparison_Two_Variances_for_Normal_Distributions()));
	connect(ui.Show_Data_Table_Button, SIGNAL(clicked()), this, SLOT(Show_Data_Table()));
	connect(ui.Help_Button, SIGNAL(clicked()), this, SLOT(Show_Help()));
	connect(ui.Theoretical_Material_Button, SIGNAL(clicked()), this, SLOT(Show_Theoretical_Material()));
	
	Get_Laplace_Table(*Matrix_Table_Laplace);
	Get_Pearson_Table(*Matrix_Table_Pearson);

	//Начальные условия
	Table_is_Full_for_Normal_Distribution=false;
	Table_is_Full_to_Hands_for_Normal_Distribution=false;
	Negative_Numbers_in_Table_for_Normal_Distribution=false;
	Count_Elements_in_Array_for_Normal_Distribution=0;
	ui.Significance_Level_for_Normal_Distribution_1->setChecked(true);

	Table_is_Full_for_Binomial_Distribution=false;
	Table_is_Full_to_Hands_for_Binomial_Distribution=false;
	Negative_Numbers_in_Table_for_Binomial_Distribution=false;
	Count_Elements_in_Array_for_Binomial_Distribution=0;
	ui.Significance_Level_1_Page_3_Point_2->setChecked(true);

	Table_is_Full_for_Normal_Distribution_1=false;
	Negative_Numbers_in_Table_for_Normal_Distribution_1=false;
	Count_Elements_in_Array_for_Normal_Distribution_1=0;

	Table_is_Full_for_Normal_Distribution_2=false;
	Negative_Numbers_in_Table_for_Normal_Distribution_2=false;
	Count_Elements_in_Array_for_Normal_Distribution_2=0;

	Number_Degrees_Freedom=0;
	ui.Significance_Level_1_Page_3_Point_1->setChecked(true);
	ui.Competing_Hypothesis_1->setChecked(true);

	setWindowTitle("Первичная обработка статистических данных");
}

TerVer_Lab1::~TerVer_Lab1(){}

//=======================================================================================================================//
//================================ Обработка переходов между страницами и подстаницами ==================================//
//=======================================================================================================================//
//Переходы между страницами
void TerVer_Lab1::Change_Stack_Main_Page_Previous()
{
	int Current_Page=ui.stackedWidget->currentIndex();
	int Previous_Page=Current_Page-1;
	if(Previous_Page>=0)
		ui.stackedWidget->setCurrentIndex(Previous_Page);
	else ui.stackedWidget->setCurrentIndex(3);

	if(Previous_Page==1)setWindowTitle("Первичная обработка статистических данных");
	if(Previous_Page==2)setWindowTitle("Проверка гипотезы о нормальном распределении");
	if(Previous_Page==-1)setWindowTitle("Проверка гипотезы о биномиальном распределении");
	if(Previous_Page==0)setWindowTitle("Сравнение дисперсий двух нормальных распределений");
}

void TerVer_Lab1::Change_Stack_Main_Page_Next()
{
	int Current_Page=ui.stackedWidget->currentIndex();
	int Next_Page=Current_Page+1;
	if(Next_Page<4)
		ui.stackedWidget->setCurrentIndex(Next_Page);
	else ui.stackedWidget->setCurrentIndex(0);

	if(Next_Page==1)setWindowTitle("Первичная обработка статистических данных");
	if(Next_Page==2)setWindowTitle("Проверка гипотезы о нормальном распределении");
	if(Next_Page==3)setWindowTitle("Проверка гипотезы о биномиальном распределении");
	if(Next_Page==4)setWindowTitle("Сравнение дисперсий двух нормальных распределений");
}

//Первая страница(смена страниц у графиков)
void TerVer_Lab1::Change_Stack_Page_1()
{
	ui.stackedWidget_2->setCurrentIndex(!ui.stackedWidget_2->currentIndex());
}

//=======================================================================================================================//
//============================= Выбор массива для сохранения данных считанных из файла ==================================//
//=======================================================================================================================//
//Загрузка данных для нормального распределения (страница 1)
void TerVer_Lab1::Load_Data_from_File_for_Normal_Distribution()
{
	Clear_Data_for_Normal_Distribution();//Очистка данных о нормальном распределении
	Clear_Data_Table_for_Normal_Distribution();
	Count_Elements_in_Array_for_Normal_Distribution=Count_Elements_in_File();
	Array_Data_for_Normal_Distribution = (float*)malloc(sizeof(float)*Count_Elements_in_Array_for_Normal_Distribution);
    emit Select_Array_SIGNAL(Array_Data_for_Normal_Distribution,0);//Эмитация нового сигнала
}

//Загрузка данных для биномиального распределения (страница 3)
void TerVer_Lab1::Load_Data_from_File_for_Binomial_Distribution()
{
	Clear_Data_for_Binomial_Distribution();//Очистка данных о нормальном распределении
	Clear_Data_Table_for_Binomial_Distribution();
	Count_Elements_in_Array_for_Binomial_Distribution=Count_Elements_in_File();
	Array_Data_for_Binomial_Distribution = (float*)malloc(sizeof(float)*Count_Elements_in_Array_for_Binomial_Distribution);
    emit Select_Array_SIGNAL(Array_Data_for_Binomial_Distribution,1);//Эмитация нового сигнала
}

//Загрузка данных для нормального распределения (страница 4)
void TerVer_Lab1::Load_Data_from_File_for_Normal_Distribution_1()
{
	Clear_Data_Table_for_Normal_Distributions_1();//Очистка данных о нормальном распределении
	Clear_Data_Two_Variances_for_Normal_Distributions();
	Count_Elements_in_Array_for_Normal_Distribution_1=Count_Elements_in_File();
	Array_Data_for_Normal_Distribution_1 = (float*)malloc(sizeof(float)*Count_Elements_in_Array_for_Normal_Distribution_1);
    emit Select_Array_SIGNAL(Array_Data_for_Normal_Distribution_1,2);//Эмитация нового сигнала
}

//Загрузка данных для нормального распределения (страница 4)
void TerVer_Lab1::Load_Data_from_File_for_Normal_Distribution_2()
{
	Clear_Data_Table_for_Normal_Distributions_2();//Очистка данных о нормальном распределении
	Clear_Data_Two_Variances_for_Normal_Distributions();
	Count_Elements_in_Array_for_Normal_Distribution_2=Count_Elements_in_File();
	Array_Data_for_Normal_Distribution_2 = (float*)malloc(sizeof(float)*Count_Elements_in_Array_for_Normal_Distribution_2);
    emit Select_Array_SIGNAL(Array_Data_for_Normal_Distribution_2,3);//Эмитация нового сигнала
}
//=======================================================================================================================//
//=============================================== Чтение данных из файла ================================================//
//=======================================================================================================================//

//=========================================================================//
//============= Определение количества элементов в файле ==================//
//=========================================================================//
int TerVer_Lab1::Count_Elements_in_File()
{
	int Current_Element=0;

	File_Name = QFileDialog::getOpenFileName( this,QString("Открыть файл"), QString(),QString("Текстовые файлы (*.txt)"));
	QFile file(File_Name);

	if(file.open(QIODevice::ReadOnly))
	{
		QTextStream Data_from_File(&file);

		while(!Data_from_File.atEnd()) 
		{
			QString String = Data_from_File.readLine();

			if(String.length())
			{
				for(int i=0;i<=String.length();i++)
				{
					if(String[i]==' '||i==String.length())
					{
						Current_Element++;
					}
				}
			}
		}
	}
	return Current_Element;
}

//=========================================================================//
//===== Cчитывание данных из файла с именем хранящимся в File_Name ========//
//=========================================================================//
void TerVer_Lab1::Load_Data_from_File(float array[],int Number_Return_Data)
{
	QTableWidgetItem *item;
	QString Determine_Number;
	int Max_Count_Elements_in_String=0;
	int Row_Count=0;
	int Count_Elements_in_String=0;
	int Current_Element=0;
	float Remainder;
	int Array_Size=2,i=0;

	bool Error_Input_Data_Size=false;
	bool Error_Input_Data_Text=false;
	bool Table_is_Full=false;	
	bool Negative_Numbers_in_Table=false;

	QFile file(File_Name);

	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Файл с данными не был выбран!", file.errorString());
		Table_is_Full=false;
	}
	else Table_is_Full=true;

	QTextStream Data_from_File(&file);

	while(!Data_from_File.atEnd()) 
	{
		QString String = Data_from_File.readLine();

		if(String.length())
		{
			for(int i=0;i<=String.length();i++)
			{
				if(String[i]==' '||i==String.length())
				{
					if(Max_Count_Elements_in_String<=Count_Elements_in_String)
					{
						Max_Count_Elements_in_String=Count_Elements_in_String;
						Max_Count_Elements_in_String++;
					}

					array[Current_Element]=Determine_Number.toFloat();

					Determine_Number="";
					Count_Elements_in_String++;
					Current_Element++;
				}
				else 
				{
					if (String[i]=='-' || String[i]==',' || String[i]=='.' ||String[i].isNumber())
					{
						if(String[i]!=',' ) Determine_Number+=String[i];
						else Determine_Number+='.';
						if(String[i]=='-')
							Negative_Numbers_in_Table=true;
					}
					else 
						Error_Input_Data_Text=true;
				}	
			}
			//Проверка на наличие Error_Input_Data_Size (Определение остатка от деления)
			do
			{
				Remainder=Current_Element-Max_Count_Elements_in_String*i;
				i++;
			}
			while(Remainder >= Max_Count_Elements_in_String);

			if(Remainder)Error_Input_Data_Size=true;

			Count_Elements_in_String=0;
			Row_Count++;
		}		
	}

	int Count_Elements_in_Array=0;
	if(Number_Return_Data==0)
	{
		Count_Elements_in_Array=Count_Elements_in_Array_for_Normal_Distribution;
		Max_Count_Elements_in_String_in_Data_Table=Max_Count_Elements_in_String;
	}
	if(Number_Return_Data==1)
	{
		Count_Elements_in_Array=Count_Elements_in_Array_for_Binomial_Distribution;
		Error_Input_Data_Size=false;
	}
	if(Number_Return_Data==2)
	{
		Count_Elements_in_Array=Count_Elements_in_Array_for_Normal_Distribution_1;
		Error_Input_Data_Size=false;
	}
	if(Number_Return_Data==3)
	{
		Count_Elements_in_Array=Count_Elements_in_Array_for_Normal_Distribution_2;
		Error_Input_Data_Size=false;
	}
	if(!Count_Elements_in_Array && File_Name!="")QMessageBox::warning(0, "Ошибка при считывании данных из файла", "Возможно в файле содержатся неверные данные.\n  Пожалуйста, попробуйте выбрать другой файл\n           или исправьте ошибки в текущем.");
	else if(Error_Input_Data_Text && Error_Input_Data_Size)
	{
		Table_is_Full=false;
		QMessageBox::warning(0, "Ошибка при считывании данных из файла", "Возможно в файле содержатся неверные данные.\n  Пожалуйста, попробуйте выбрать другой файл\n           или исправьте ошибки в текущем.");
	}
	else
	{
		if(Error_Input_Data_Text)
		{
			QMessageBox::warning(0, "Ошибка при считывании данных из файла", "         В файле с данными был найден текст.\n  Пожалуйста, попробуйте выбрать другой файл\n            или исправьте ошибки в текущем.");
			Table_is_Full=false;
		}
		if(Error_Input_Data_Size)
		{
			QMessageBox::warning(0, "Ошибка при считывании данных из файла", "Количество данных полученных из файла не соответствуют\n                           размерности таблицы.");
			Table_is_Full=false;
		}
	}

	//Передача результата о считывании данных из файла в основную программу
	if(Number_Return_Data==0)
	{
		Show_Data_Table();
		if(Table_is_Full)QMessageBox::information(0, "Информация о данных", "            Данные из файла были успешно извлечены.\n Пожалуйста, введите значение в поле \"Количество интервалов\"\n                      и нажмите кнопку \"Вычислить\".");
		
		Table_is_Full_for_Normal_Distribution=Table_is_Full;
		Negative_Numbers_in_Table_for_Normal_Distribution=Negative_Numbers_in_Table;
		Count_Elements_in_Array_for_Normal_Distribution=Current_Element;
	}
	if(Number_Return_Data==1)
	{
		Table_is_Full_for_Binomial_Distribution=Table_is_Full;
		Negative_Numbers_in_Table_for_Binomial_Distribution=Negative_Numbers_in_Table;
		Count_Elements_in_Array_for_Binomial_Distribution=Current_Element;
		if(Table_is_Full)Calculate_Input_Data_for_Binomial_Distribution();
	}
	if(Number_Return_Data==2)
	{
		Table_is_Full_for_Normal_Distribution_1=Table_is_Full;
		Negative_Numbers_in_Table_for_Normal_Distribution_1=Negative_Numbers_in_Table;
		Count_Elements_in_Array_for_Normal_Distribution_1=Current_Element;
		if(Table_is_Full)Calculate_Input_Data_for_Normal_Distribution_1();
	}
	if(Number_Return_Data==3)
	{
		Table_is_Full_for_Normal_Distribution_2=Table_is_Full;
		Negative_Numbers_in_Table_for_Normal_Distribution_2=Negative_Numbers_in_Table;
		Count_Elements_in_Array_for_Normal_Distribution_2=Current_Element;
		if(Table_is_Full)Calculate_Input_Data_for_Normal_Distribution_2();
	}

	file.close();
}

//=======================================================================================================================//
//======================== Создание таблиц характеристик интервального статистического ряда =============================//
//=======================================================================================================================//
void TerVer_Lab1::Create_Table_for_Normal_Distribution()
{
	QTableWidgetItem *item;
//=========================================================================//
// Создание таблицы характеристик интервального статистического ряда стр.1 //
//=========================================================================//
	//Очистка таблицы 
	ui.Table_for_Normal_Distribution_Page_1->setRowCount(0);
	ui.Table_for_Normal_Distribution_Page_1->setColumnCount(0);

	//Создание таблицы
	if(ui.Count_for_Normal_Distribution->value())
	{
		ui.Table_for_Normal_Distribution_Page_1->setRowCount(3);
		ui.Table_for_Normal_Distribution_Page_1->setColumnCount(ui.Count_for_Normal_Distribution->value()+1);

		for(int i=1;i<ui.Count_for_Normal_Distribution->value();i++)
		{
			item = new  QTableWidgetItem("[ ; )");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_1->setItem(0,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_1->setItem(1,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_1->setItem(2,i, item);
		}

		item = new  QTableWidgetItem("[ ; ]");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(0,ui.Count_for_Normal_Distribution->value(), item);

		item = new  QTableWidgetItem("");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(1,ui.Count_for_Normal_Distribution->value(), item);

		item = new  QTableWidgetItem("");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(2,ui.Count_for_Normal_Distribution->value(), item);

		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(0,0, item);

		item = new  QTableWidgetItem("Mi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(1,0, item);

		item = new  QTableWidgetItem("Wi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_1->setItem(2,0, item);
	}
//=========================================================================//
// Создание таблицы характеристик интервального статистического ряда стр.2 //
//=========================================================================//
	//Очистка таблицы 
	ui.Table_for_Normal_Distribution_Page_2->setRowCount(0);
	ui.Table_for_Normal_Distribution_Page_2->setColumnCount(0);

	//Создание таблицы
	if(ui.Count_for_Normal_Distribution->value())
	{
		ui.Table_for_Normal_Distribution_Page_2->setRowCount(3);
		ui.Table_for_Normal_Distribution_Page_2->setColumnCount(ui.Count_for_Normal_Distribution->value()+1);

		for(int i=1;i<ui.Count_for_Normal_Distribution->value();i++)
		{
			item = new  QTableWidgetItem("[ ; )");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_2->setItem(0,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_2->setItem(1,i, item);
			ui.Table_for_Normal_Distribution_Page_2->setItem(2,i, item);
		}

		item = new  QTableWidgetItem("[ ; ]");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_2->setItem(0,ui.Count_for_Normal_Distribution->value(), item);

		item = new  QTableWidgetItem("");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_2->setItem(1,ui.Count_for_Normal_Distribution->value(), item);
		ui.Table_for_Normal_Distribution_Page_2->setItem(2,ui.Count_for_Normal_Distribution->value(), item);

		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_2->setItem(0,0, item);

		item = new  QTableWidgetItem("Mi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_2->setItem(1,0, item);

		item = new  QTableWidgetItem("Wi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_Page_2->setItem(2,0, item);
	}
}

//=======================================================================================================================//
//====================================== Проверка ошибок для введенных данных ===========================================//
//=======================================================================================================================//
void TerVer_Lab1::Error_Checking_for_Normal_Distribution()
{
	int Count_of_Filled_Slots_in_First_Row=0;
	int Count_of_Filled_Slots_in_Second_Row=0;
	int Count_of_Filled_Slots_in_Third_Row=0;

	Error_Fill_Table_for_Normal_Distribution=false;
	Error_Fill_Count_for_Normal_Distribution=false;
	Error_Fill_Sum_for_Normal_Distribution=false;
	Error_Fill_Row_Intervals_for_Normal_Distribution=false;
	Error_Fill_Row_Frequency_for_Normal_Distribution=false;
	Error_Fill_Row_Relative_Frequency_for_Normal_Distribution=false;

	if(!ui.Table_for_Normal_Distribution_Page_1->columnCount() && !ui.Table_for_Normal_Distribution_Page_1->rowCount())	Error_Fill_Table_for_Normal_Distribution=true;
	if(!ui.Count_for_Normal_Distribution->value())Error_Fill_Count_for_Normal_Distribution=true;
	if(ui.Sum_for_Normal_Distribution_Page_1->text()=="" || !ui.Sum_for_Normal_Distribution_Page_1->text().toInt())Error_Fill_Sum_for_Normal_Distribution=true;

	for(int j=1;j<ui.Table_for_Normal_Distribution_Page_1->columnCount();j++)
	{
		if(ui.Table_for_Normal_Distribution_Page_1->item(0,j)->text()!="[ ; )" && ui.Table_for_Normal_Distribution_Page_1->item(0,j)->text()!="[ ; ]" && ui.Table_for_Normal_Distribution_Page_1->item(0,j)->text()!="[;)" && ui.Table_for_Normal_Distribution_Page_1->item(0,j)->text()!="[;]" && ui.Table_for_Normal_Distribution_Page_1->item(0,j)->text()!="")
			Count_of_Filled_Slots_in_First_Row++;

		if(ui.Table_for_Normal_Distribution_Page_1->item(1,j)->text()!="")
			Count_of_Filled_Slots_in_Second_Row++;

		if(ui.Table_for_Normal_Distribution_Page_1->item(2,j)->text()!="")
			Count_of_Filled_Slots_in_Third_Row++;
	}

	if(Count_of_Filled_Slots_in_First_Row==ui.Table_for_Normal_Distribution_Page_1->columnCount()-1) Error_Fill_Row_Intervals_for_Normal_Distribution=false;
	else Error_Fill_Row_Intervals_for_Normal_Distribution=true;
	if(Count_of_Filled_Slots_in_Second_Row==ui.Table_for_Normal_Distribution_Page_1->columnCount()-1) Error_Fill_Row_Frequency_for_Normal_Distribution=false;
	else Error_Fill_Row_Frequency_for_Normal_Distribution=true;
	if(Count_of_Filled_Slots_in_Third_Row==ui.Table_for_Normal_Distribution_Page_1->columnCount()-1) Error_Fill_Row_Relative_Frequency_for_Normal_Distribution=false;
	else Error_Fill_Row_Relative_Frequency_for_Normal_Distribution=true;
}


void TerVer_Lab1::Error_Checking_for_Binomial_Distribution()
{
	int Count_of_Filled_Slots_in_First_Row=0;
	int Count_of_Filled_Slots_in_Second_Row=0;
	int Count_of_Filled_Slots_in_Third_Row=0;

	Error_Fill_Table_for_Binomial_Distribution=false;
	Error_Fill_Count_for_Binomial_Distribution=false;
	Error_Fill_Sum_for_Binomial_Distribution=false;
	Error_Fill_Row_Intervals_for_Binomial_Distribution=false;
	Error_Fill_Row_Frequency_for_Binomial_Distribution=false;
	Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution=false;
	
	int Previous_Value=0;

	if(!ui.Table_for_Binomial_Distribution->columnCount() && !ui.Table_for_Binomial_Distribution->rowCount())	Error_Fill_Table_for_Binomial_Distribution=true;
	if(!ui.Count_for_Binomial_Distribution->value())Error_Fill_Count_for_Binomial_Distribution=true;
	if(ui.Sum_for_Binomial_Distribution->text()=="" || !ui.Sum_for_Binomial_Distribution->text().toInt())Error_Fill_Sum_for_Binomial_Distribution=true;

	for(int j=1;j<ui.Table_for_Binomial_Distribution->columnCount();j++)
	{
		if(j!=1)Previous_Value=ui.Table_for_Binomial_Distribution->item(0,j-1)->text().toInt();
		
		if(ui.Table_for_Binomial_Distribution->item(0,j)->text()!="" && (Previous_Value<ui.Table_for_Binomial_Distribution->item(0,j)->text().toInt() || !ui.Table_for_Binomial_Distribution->item(0,j)->text().toInt()))
			Count_of_Filled_Slots_in_First_Row++;

		if(ui.Table_for_Binomial_Distribution->item(1,j)->text()!="")
			Count_of_Filled_Slots_in_Second_Row++;

		if(ui.Table_for_Binomial_Distribution->item(2,j)->text()!="")
			Count_of_Filled_Slots_in_Third_Row++;
	}

	if(Count_of_Filled_Slots_in_First_Row==ui.Table_for_Binomial_Distribution->columnCount()-1) Error_Fill_Row_Intervals_for_Binomial_Distribution=false;
	else Error_Fill_Row_Intervals_for_Binomial_Distribution=true;
	if(Count_of_Filled_Slots_in_Second_Row==ui.Table_for_Binomial_Distribution->columnCount()-1) Error_Fill_Row_Frequency_for_Binomial_Distribution=false;
	else Error_Fill_Row_Frequency_for_Binomial_Distribution=true;
	if(Count_of_Filled_Slots_in_Third_Row==ui.Table_for_Binomial_Distribution->columnCount()-1) Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution=false;
	else Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution=true;
}

//=======================================================================================================================//
//=========== Формирование таблицы характеристик для интервального нормального распределения ============================//
//=======================================================================================================================//
void TerVer_Lab1::Formation_Table_of_Characteristics_for_Normal_Distribution()
{
	QTableWidgetItem *item;
	QString tmp_str,tmp_str_1,tmp_str_2,string_item;
	int Count_of_Occurrences=0;

	Error_Checking_for_Normal_Distribution();

	//Для данных считанных из файла или для набранной вручную таблицы экспериментальных данных
	if(Table_is_Full_for_Normal_Distribution && !Table_is_Full_to_Hands_for_Normal_Distribution)
	{
//=========================================================================//
//===================== Определение первичных данных ======================//
//=========================================================================//
		float min=Array_Data_for_Normal_Distribution[0];
		float max=Array_Data_for_Normal_Distribution[0];

		for(int i=0;i<Count_Elements_in_Array_for_Normal_Distribution;i++)
		{
			min=(Array_Data_for_Normal_Distribution[i]<min)?Array_Data_for_Normal_Distribution[i]:min;
			max=(Array_Data_for_Normal_Distribution[i]>max)?Array_Data_for_Normal_Distribution[i]:max;
		}

		h=(max-min)/ui.Count_for_Normal_Distribution->value();
		x0=min;//x0=min-(h/2);

		if(!Error_Fill_Count_for_Normal_Distribution)
		{
			Create_Table_for_Normal_Distribution();
//=========================================================================//
//Заполнение таблицы характеристик интервального статистического ряда стр.1//
//=========================================================================//
			for(int x=0;x<ui.Count_for_Normal_Distribution->value();x++)
			{
				//Вывод интервалов
				if(x!=ui.Count_for_Normal_Distribution->value()-1) tmp_str=("["+QString::number(x0+x*h,  'g',  4)+" ; "+QString::number(x0+(x+1)*h,  'g',  4)+")");
				else tmp_str=("["+QString::number(x0+x*h,  'g',  4)+" ; "+QString::number(x0+(x+1)*h,  'g',  4)+"]");

				item = new  QTableWidgetItem(tmp_str);
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_Page_1->setItem(0,x+1, item);

				//Определение частоты появления в интервале
				for(int i=0;i<Count_Elements_in_Array_for_Normal_Distribution;i++)
				{
					if(x!=ui.Count_for_Normal_Distribution->value()-1)
					{
						if( ((x0+x*h)<=Array_Data_for_Normal_Distribution[i]) && (Array_Data_for_Normal_Distribution[i]<(x0+(x+1)*h)) )
							Count_of_Occurrences++;
					}
					else
					{
						if( ((x0+x*h)<=Array_Data_for_Normal_Distribution[i]) && (Array_Data_for_Normal_Distribution[i]<=(x0+(x+1)*h)) )
							Count_of_Occurrences++;
					}
				}

				//Вывод частоты появления в интервале
				item = new  QTableWidgetItem(QString::number(Count_of_Occurrences));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_Page_1->setItem(1,x+1, item);

				//Вывод частостей появления в интервале
				item = new  QTableWidgetItem(QString::number((float)Count_of_Occurrences/(float)Count_Elements_in_Array_for_Normal_Distribution,  'g',  2));//Возможно не 2?!
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_Page_1->setItem(2,x+1, item);

				Count_of_Occurrences=0;
			}
			ui.Sum_for_Normal_Distribution_Page_1->setText(QString::number(Count_Elements_in_Array_for_Normal_Distribution));
		}
		else QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Количество интервалов\" было заполнено неверно");
	}
	else //Для данных набранных вручную в таблицы частот и частостей
	{
		if(!Error_Fill_Table_for_Normal_Distribution || !Error_Fill_Row_Intervals_for_Normal_Distribution || !Error_Fill_Row_Frequency_for_Normal_Distribution || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution)
		{
			if(!Error_Fill_Row_Intervals_for_Normal_Distribution && (!Error_Fill_Row_Frequency_for_Normal_Distribution || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution))
			{
				Negative_Numbers_in_Table_for_Normal_Distribution=false;

				if(ui.Count_for_Normal_Distribution->value()!=ui.Table_for_Normal_Distribution_Page_1->columnCount()-1)
				{
					QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
					ui.Count_for_Normal_Distribution->setValue(ui.Table_for_Normal_Distribution_Page_1->columnCount()-1);
				}
//=========================================================================//
//========== Заполнение недостающих строк в таблице характеристик =========//
//=========================================================================//
				if(!Error_Fill_Sum_for_Normal_Distribution)
				{
					if(Error_Fill_Row_Relative_Frequency_for_Normal_Distribution)
					{
						for(int x=1;x<ui.Table_for_Normal_Distribution_Page_1->columnCount();x++)
						{
							item = new  QTableWidgetItem(QString::number((ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()), 'g', 2));
							item->setTextAlignment(Qt::AlignCenter);
							ui.Table_for_Normal_Distribution_Page_1->setItem(2,x, item);
						}
						Error_Fill_Row_Relative_Frequency_for_Normal_Distribution=false;
					}

					if(Error_Fill_Row_Frequency_for_Normal_Distribution)
					{
						for(int x=1;x<ui.Table_for_Normal_Distribution_Page_1->columnCount();x++)
						{
							item = new  QTableWidgetItem(QString::number((int)((ui.Table_for_Normal_Distribution_Page_1->item(2,x)->text().toFloat()*ui.Sum_for_Normal_Distribution_Page_1->text().toFloat())+0.5), 'g', 1));//0.5 - поправочный коэффициент, для округления в большую сторону
							item->setTextAlignment(Qt::AlignCenter);
							ui.Table_for_Normal_Distribution_Page_1->setItem(1,x, item);
						}
						Error_Fill_Row_Frequency_for_Normal_Distribution=false;
					}

					if(!Error_Fill_Row_Intervals_for_Normal_Distribution && !Error_Fill_Row_Frequency_for_Normal_Distribution && !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution)
					{
//=========================================================================//
//===================== Определение первичных данных ======================//
//=========================================================================//
						Table_is_Full_for_Normal_Distribution=true;
						Table_is_Full_to_Hands_for_Normal_Distribution=true;

						int i;
						Count_Elements_in_Array_for_Normal_Distribution=0;
						for(int x=1;x<ui.Table_for_Normal_Distribution_Page_1->columnCount();x++)
						{
							Count_Elements_in_Array_for_Normal_Distribution+=ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat();
							string_item = ui.Table_for_Normal_Distribution_Page_1->item(0,x)->text();//Строка в ячейке
							for(i=0;i<string_item.size() && string_item[i]!=';';i++) if(string_item[i]=='-') Negative_Numbers_in_Table_for_Normal_Distribution=true;
							for(int j=i+1;j<string_item.size() && string_item[j]!=')' && string_item[j]!=']';j++)if(string_item[j]=='-') Negative_Numbers_in_Table_for_Normal_Distribution=true;
						}

						ui.Sum_for_Normal_Distribution_Page_1->setText(QString::number(Count_Elements_in_Array_for_Normal_Distribution));

						string_item = ui.Table_for_Normal_Distribution_Page_1->item(0,1)->text();//Строка в первой ячейке частот
						for(i=0;i<string_item.size() && string_item[i]!=';';i++)
							if(string_item[i]!='['&&string_item[i]!=' ') tmp_str_1+=string_item[i];

						for(int j=i+1;j<string_item.size() && string_item[j]!=')' && string_item[j]!=']';j++)
							if(string_item[j]!=' ')tmp_str_2+=string_item[j];

						h=(tmp_str_2.toFloat()-tmp_str_1.toFloat());
						x0=tmp_str_1.toFloat();
					}
					else 
					{
						QMessageBox::warning(0, "Ошибка при считывании данных", "Возможно в программе содержатся неверные данные.\n  Пожалуйста, исправьте ошибки и попробуйте снова.");
						Table_is_Full_for_Normal_Distribution=false;
					}
				}
				else QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Сумма частот (N)\" было заполнено неверно");
			}
			else
			{
				QMessageBox::warning(0, "Ошибка при считывании данных", "Возможно в программе содержатся неверные данные.\n  Пожалуйста, исправьте ошибки и попробуйте снова.");
				Table_is_Full_for_Normal_Distribution=false;
			}
		}
		else 
		{
			QMessageBox::warning(0, "Ошибка при считывании данных", "Не было найдено никаких данных.");
			Table_is_Full_for_Normal_Distribution=false;
		}
	}
}

//=======================================================================================================================//
//====================== Очистка основных данных для интервального нормального распределения ============================//
//=======================================================================================================================//
void TerVer_Lab1::Clear_Data_Table_for_Normal_Distribution()
{
	Table_is_Full_for_Normal_Distribution=false;
	Table_is_Full_to_Hands_for_Normal_Distribution=false;

	ui.Table_for_Normal_Distribution_Page_1->setRowCount(0);
	ui.Table_for_Normal_Distribution_Page_1->setColumnCount(0);
	ui.Table_for_Normal_Distribution_Page_2->setRowCount(0);
	ui.Table_for_Normal_Distribution_Page_2->setColumnCount(0);

	ui.Sum_for_Normal_Distribution_Page_1->clear();
	ui.Count_for_Normal_Distribution->setValue(0);
}

//=======================================================================================================================//
//====================== Очистка расчётных данных для интервального нормального распределения ===========================//
//=======================================================================================================================//
void TerVer_Lab1::Clear_Data_for_Normal_Distribution()
{
	ui.Intervals_Table_for_Normal_Distribution->setRowCount(0);
	ui.Intervals_Table_for_Normal_Distribution->setColumnCount(0);
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setRowCount(0);
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setColumnCount(0);
	
	ui.X_for_Normal_Distribution->clear();
	ui.D_for_Normal_Distribution->clear();
	ui.S_for_Normal_Distribution->clear();
	ui.A_for_Normal_Distribution_Page_1->clear();
	ui.Sigma_for_Normal_Distribution_Page_1->clear();
	
	ui.Result_Testing_Hypothesis_Normal_Distribution->clear();
	ui.A_for_Normal_Distribution_Page_2->clear();
	ui.Sigma_for_Normal_Distribution_Page_2->clear();
	ui.Count_for_Normal_Distribution_Page_2->clear();
	ui.Sum_for_Normal_Distribution_Page_2->clear();
	ui.label_97->setText("= ... ;");//197
	ui.label_58->setText("X       =     ...");//186
	ui.label_100->setText("критич.");//203//206 pf
	ui.label_99->setText("X          = X          = ... ;");//205
	ui.label_107->setText("X          =   ...");//181

	//Отрисовка системы координат
	QGraphicsScene *scene;
	scene = new QGraphicsScene(ui.Histogram_Browser);   
	scene->clear();
	ui.Histogram_Browser->setScene(scene);
	ui.Polygon_Browser->setScene(scene);
	ui.Empirical_Function_Browser->setScene(scene);
	ui.Graphic_Empirical_Function_Browser->setScene(scene);
	scene = new QGraphicsScene(ui.P_Browser_for_Normal_Distribution);
	ui.P_Browser_for_Normal_Distribution->setScene(scene);
}

//=======================================================================================================================//
//========= Создание таблиц характеристик интервального статистического ряда (Сформировать таблицу) =====================//
//=======================================================================================================================//
void TerVer_Lab1::Build_Table_for_Normal_Distribution()
{
	int Count_Intervals;
	if(ui.Count_for_Normal_Distribution->value()) Count_Intervals=ui.Count_for_Normal_Distribution->value();
	Clear_Data_Table_for_Normal_Distribution();
	Clear_Data_for_Normal_Distribution();
	ui.Count_for_Normal_Distribution->setValue(Count_Intervals);
	Create_Table_for_Normal_Distribution();

	for (int i=0;i<Count_Elements_in_Array_for_Normal_Distribution;i++)
		*(Array_Data_for_Normal_Distribution+i)=0;

	Count_Elements_in_Array_for_Normal_Distribution=0;
	Negative_Numbers_in_Table_for_Normal_Distribution=false;
	Table_is_Full_for_Normal_Distribution=false;
}

//=======================================================================================================================//
//============================================== Первичная обработка данных =============================================//
//=======================================================================================================================//
void TerVer_Lab1::Calculate_Action_for_Normal_Distribution()
{
	Formation_Table_of_Characteristics_for_Normal_Distribution();

	if(ui.Sum_for_Normal_Distribution_Page_1->text()!="" && ui.Sum_for_Normal_Distribution_Page_1->text().toInt() && Table_is_Full_for_Normal_Distribution)
	{
		Calculation_of_Averages_for_Normal_Distribution();	
		Copy_Data_to_Page_2_for_Normal_Distribution();
		Drawing_Task_6_for_Normal_Distribution();
		Drawing_Graphics_for_Normal_Distribution();
		Clear_Data_Page_2_for_Normal_Distribution();
	}
}

//=======================================================================================================================//
//============ Вычисление основных величин (среднее значение, дисперсия, среднеквадратическое отклонение) ===============//
//=======================================================================================================================//
void TerVer_Lab1::Calculation_of_Averages_for_Normal_Distribution()
{
	float Sum=0;
	int i=0;
	float ty[2][30]={{2.78,2.57,2.45,2.37,2.31,2.26,2.23,2.2,2.18,2.16,2.15,2.13,2.12,2.11,2.1,2.093,2.064,2.045,2.032,2.023,2.016,2.009,2.001,1.996,1.001,1.987,1.984,1.98,1.96},{5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,60,70,80,90,100,120,0}};
	float qy[2][30]={{1.37,1.09,0.92,0.8,0.71,0.65,0.59,0.55,0.52,0.48,0.46,0.44,0.42,0.4,0.39,0.37,0.32,0.28,0.26,0.24,0.22,0.21,0.188,0.174,0.161,0.151,0.143,0.115,0.099,0.089},{5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25,30,35,40,45,50,60,70,80,90,100,150,200,250}};
//=========================================================================//
	//Среднее статистическое X
	for(int x=1;x<=ui.Count_for_Normal_Distribution->value();x++)
	{
		Sum+=(((x0+(x-1)*h)+(x0+(x)*h))/2)*ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat();
	}
	ui.X_for_Normal_Distribution->setText(QString::number((Sum/ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()), 'g', 4));
//=========================================================================//
	Sum=0;
	//Дисперсия
	for(int x=1;x<=ui.Count_for_Normal_Distribution->value();x++)
	{
		Sum+=pow(((((x0+(x-1)*h)+(x0+(x)*h))/2)-ui.X_for_Normal_Distribution->text().toFloat()),2)*ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat();
	}
	ui.D_for_Normal_Distribution->setText(QString::number((ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()<30)?(1/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()-1)*Sum):(Sum/ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()), 'g', 4));
//=========================================================================//
	//Средне квадратическое S
	ui.S_for_Normal_Distribution->setText(QString::number(sqrt(ui.D_for_Normal_Distribution->text().toFloat()),'g', 4));
//=========================================================================//
	// Интервал А
	for(i=0;i<30;i++)
		if(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()<ty[1][i])break;
	i--;

	float Eps=(ui.S_for_Normal_Distribution->text().toFloat()*ty[0][i])/sqrt(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat());
	ui.A_for_Normal_Distribution_Page_1->setText("["+QString::number(ui.X_for_Normal_Distribution->text().toFloat()-Eps,'g', 4)+" ; "+QString::number(ui.X_for_Normal_Distribution->text().toFloat()+Eps,'g', 4)+"]");
//=========================================================================//
	//Интервал Sigma
	for(i=0;i<30;i++)
		if(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()<qy[1][i])break;
	i--;
	ui.Sigma_for_Normal_Distribution_Page_1->setText("["+QString::number(ui.S_for_Normal_Distribution->text().toFloat()*(1-qy[0][i]),'g', 4)+" ; "+QString::number(ui.S_for_Normal_Distribution->text().toFloat()*(1+qy[0][i]),'g', 4)+"]");
//=========================================================================//
}

//=======================================================================================================================//
//====================== Перенос данных на страницу проверки гипотезы о нормальном распределении ========================//
//=======================================================================================================================//
void TerVer_Lab1::Copy_Data_to_Page_2_for_Normal_Distribution()
{
	QTableWidgetItem *item;
	
	for(int i=0;i<ui.Table_for_Normal_Distribution_Page_1->rowCount();i++)
		for(int j=1;j<ui.Table_for_Normal_Distribution_Page_1->columnCount();j++)
		{
			item = new  QTableWidgetItem(ui.Table_for_Normal_Distribution_Page_1->item(i,j)->text());
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_Page_2->setItem(i,j, item);
		}

	ui.Count_for_Normal_Distribution_Page_2->setText(QString::number(ui.Count_for_Normal_Distribution->value()));
	ui.Sum_for_Normal_Distribution_Page_2->setText(ui.Sum_for_Normal_Distribution_Page_1->text());

	ui.A_for_Normal_Distribution_Page_2->setText(ui.X_for_Normal_Distribution->text());
	ui.Sigma_for_Normal_Distribution_Page_2->setText(ui.S_for_Normal_Distribution->text());
}

//=======================================================================================================================//
//================== Отрисовка дифференциальной и интегральной функции нормального распределения ========================//
//=======================================================================================================================//
void TerVer_Lab1::Drawing_Task_6_for_Normal_Distribution()
{
	ui.label_72->setText("(x - "+(QString::number(ui.X_for_Normal_Distribution->text().toFloat(), 'g', 3))+")");
	ui.label_85->setText("(x - "+(QString::number(ui.X_for_Normal_Distribution->text().toFloat(), 'g', 3))+")");

	ui.label_87->setText((QString::number((ui.S_for_Normal_Distribution->text().toFloat()),'g', 3)));
	ui.label_83->setText((QString::number((ui.S_for_Normal_Distribution->text().toFloat()),'g', 3)));
	ui.label_76->setText((QString::number(2*(ui.S_for_Normal_Distribution->text().toFloat()),'g', 3)));
}

//=======================================================================================================================//
//===== Отрисовка графиков гистограммы и полигона частот, определение эмпирической функции и построение её графика ======//
//=======================================================================================================================//
void TerVer_Lab1::Drawing_Graphics_for_Normal_Distribution()
{
	QGraphicsTextItem* text;
	QGraphicsScene *scene_1;
	QGraphicsScene *scene_2;
	QGraphicsScene *scene_3;
	QGraphicsScene *scene_4;

	//Цвета перьев
	QPen pen(Qt::black);
	QPen pen2(Qt::blue);
	QPen pen3(Qt::gray);
	QPen pen4(Qt::cyan);

	int start_point=-60;
	int finish_point=200;

	float yy_max;
	float Sum;
//=========================================================================//
//=== Определение коэффициентов сопоставления (для отрисовки графиков) ====//
//=========================================================================//

	//Определение границ для сопоставления по оси Х
	float start_graphics=x0-h/2;
	float finish_graphics=(x0+(ui.Count_for_Normal_Distribution->value()*h)+h/2);

	//Коэффициент сопоставления по оси Х
	coefficient_x=270/(finish_graphics-start_graphics);

	//Поиск максимальной высоты у прямоугольников графика гистограммы
	float y_max=ui.Table_for_Normal_Distribution_Page_1->item(1,1)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h);

	for(int x=2;x<=ui.Count_for_Normal_Distribution->value();x++)
		if(y_max<ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h))y_max=ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h);

	//Коэффициент сопоставления по оси Y
	coefficient_y=230/y_max;
	yy_max=y_max;

	//Ориентация графиков
	if(!Negative_Numbers_in_Table_for_Normal_Distribution)
	{
		start_point=-60;
		finish_point=200;
	}
	else 
	{
		start_point=200;
		finish_point=-60;
	}
//=========================================================================//
//============== Отрисовка графика гистограммы частот =====================//
//=========================================================================//
	scene_1 = new QGraphicsScene(ui.Histogram_Browser); 

	//Отрисовка системы координат
	scene_1->addLine(-60,230,200,230,pen);//Ось X
	scene_1->addLine(start_point,0,start_point,230,pen);//Ось y
	scene_1->addLine(start_point,0,start_point+5,5,pen);//Стрелка - ось y
	scene_1->addLine(start_point,0,start_point-5,5,pen);//Стрелка - ось y
	if(!Negative_Numbers_in_Table_for_Normal_Distribution)
	{
		scene_1->addLine(finish_point-5,225,finish_point,230,pen);//Стрелка - ось X
		scene_1->addLine(finish_point-5,235,finish_point,230,pen);//Стрелка - ось X
	}

	text = scene_1->addText("0", QFont("Arial", 6 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-74:214,230);

	text = scene_1->addText("...", QFont("Arial", 10 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-64:200,225);

	for(int x=1;x<=ui.Count_for_Normal_Distribution->value();x++)
	{
		for(int i=-60-h/2*coefficient_x+h*coefficient_x*x+1;i<-60+h/2*coefficient_x+h*coefficient_x*x;i++)
			scene_1->addLine(i,229,i,229-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen4);//Закраска "прямоугольника"

		scene_1->addLine(-60-h/2*coefficient_x+h*coefficient_x*x,229,-60-h/2*coefficient_x+h*coefficient_x*x,229-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen2);//Левая грань "прямоугольника"
		scene_1->addLine(-60+h/2*coefficient_x+h*coefficient_x*x,229,-60+h/2*coefficient_x+h*coefficient_x*x,229-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen2);//Правая грань "прямоугольника"
		scene_1->addLine(-60-h/2*coefficient_x+h*coefficient_x*x,229-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,-60+h/2*coefficient_x+h*coefficient_x*x,229-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen2);//Макушка "прямоугольника"

		//Отображение значений кооржинат вдоль оси X
		text = scene_1->addText(QString::number((x0+((x-1)*h)),  'g',  4), QFont("Arial", 6 ));
		text->setPos(-66-h/2*coefficient_x+h*coefficient_x*x,230);

		//Отображение значений кооржинат вдоль оси Y
		text = scene_1->addText(QString::number(ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h),  'g',  2), QFont("Arial", 6 ));
		text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-84:200,224-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y);
	}

	//Отображение значений кооржинат вдоль оси X - последнее значение
	text = scene_1->addText(QString::number((x0+((ui.Count_for_Normal_Distribution->value())*h)),  'g',  4), QFont("Arial", 6 ));
	text->setPos(-66-h/2*coefficient_x+h*coefficient_x*(ui.Count_for_Normal_Distribution->value()+1),230);

	ui.Histogram_Browser->setScene(scene_1);
//=========================================================================//
//================= Отрисовка графика полигона частот =====================//
//=========================================================================//
	scene_2 = new QGraphicsScene(ui.Polygon_Browser); 

	//Отрисовка системы координат
	scene_2->addLine(-60,230,200,230,pen);//Ось X
	scene_2->addLine(start_point,0,start_point,230,pen);//Ось y
	scene_2->addLine(start_point,0,start_point+5,5,pen);//Стрелка - ось y
	scene_2->addLine(start_point,0,start_point-5,5,pen);//Стрелка - ось y
	if(!Negative_Numbers_in_Table_for_Normal_Distribution)
	{
		scene_2->addLine(finish_point-5,225,finish_point,230,pen);//Стрелка - ось X
		scene_2->addLine(finish_point-5,235,finish_point,230,pen);//Стрелка - ось X
	}

	text = scene_2->addText("0", QFont("Arial", 6 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-74:214,230);//

	text = scene_2->addText("...", QFont("Arial", 10 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-64:200,225);//

	for(int x=1;x<=ui.Count_for_Normal_Distribution->value();x++)
	{
		scene_2->addLine(-60+h*coefficient_x*x,230,-60+h*coefficient_x*x,230-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen3);//Левая грань "прямоугольника"
		if(x!=ui.Count_for_Normal_Distribution->value())scene_2->addLine(-60+h*coefficient_x*x,230-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,-60+h*coefficient_x*(x+1),230-ui.Table_for_Normal_Distribution_Page_1->item(1,x+1)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y,pen2);//Макушка "прямоугольника"

		//Отображение значений кооржинат вдоль оси X
		text = scene_2->addText(QString::number((h/2+x0+((x-1)*h)),  'g',  4), QFont("Arial", 6 ));
		text->setPos(-66+h*coefficient_x*x,230);//

		//Отображение значений кооржинат вдоль оси Y
		text = scene_2->addText(QString::number(ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/ui.Sum_for_Normal_Distribution_Page_1->text().toFloat(),  'g',  2), QFont("Arial", 6 ));
		text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-84:200,224-ui.Table_for_Normal_Distribution_Page_1->item(1,x)->text().toFloat()/(ui.Sum_for_Normal_Distribution_Page_1->text().toFloat()*h)*coefficient_y);
	}

	ui.Polygon_Browser->setScene(scene_2);
//=========================================================================//
//================ Отрисовка эмпирической функции распределения ===========//
//=========================================================================//
	scene_3 = new QGraphicsScene(ui.Empirical_Function_Browser); 
	QByteArray Function="";
	Function="";//QString Function="";
	Sum=0;

	Function+="             /   0 при x < "+QString::number((x0+h)/*(x0)*/, 'g', 4)+"\n";

	for(int x=1;x<ui.Count_for_Normal_Distribution->value();x++)
	{
		Sum+=ui.Table_for_Normal_Distribution_Page_1->item(2,x)->text().toFloat();

		if((x+1)!=(ui.Count_for_Normal_Distribution->value()+2)/2) Function+="             |   "+QString::number(Sum, 'g', 4)+" при "+QString::number((x0+((x)/*(x-1)*/*h)), 'g', 4)+" <= x < "+QString::number(((x0+((x+1)/*(x)*/*h))), 'g', 4)+"\n";
		else Function+="F(x)= <    "+QString::number(Sum, 'g', 4)+" при "+QString::number((x0+(((x))/*(x-1)*/*h)), 'g', 4)+" <= x < "+QString::number(((x0+((x+1)/*(x)*/*h))), 'g', 4)+"\n";
	}
	Function+="             \\   "+QString::number(1, 'g', 4)+" при x >= "+QString::number(((x0+((ui.Count_for_Normal_Distribution->value()/*-1*/)*h))), 'g', 4)+"\n";

	scene_3->addText(Function);

	ui.Empirical_Function_Browser->setScene(scene_3);
//=========================================================================//
//======== Отрисовка графика эмпирической функции распределения ===========//
//=========================================================================//
	//Коэффициент сопоставления по оси Y
	coefficient_y=230/1;

	scene_4 = new QGraphicsScene(ui.Graphic_Empirical_Function_Browser);

	//Отрисовка системы координат
	scene_4->addLine(-60,230,200,230,pen);//Ось X
	scene_4->addLine(start_point,0,start_point,230,pen);//Ось y
	scene_4->addLine(start_point,0,start_point+5,5,pen);//Стрелка - ось y
	scene_4->addLine(start_point,0,start_point-5,5,pen);//Стрелка - ось y
	if(!Negative_Numbers_in_Table_for_Normal_Distribution)
	{
		scene_4->addLine(finish_point-5,225,finish_point,230,pen);//Стрелка - ось X
		scene_4->addLine(finish_point-5,235,finish_point,230,pen);//Стрелка - ось X
	}

	text = scene_4->addText("0", QFont("Arial", 6 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-74:214,230);

	text = scene_4->addText("...", QFont("Arial", 10 ));
	text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-64:200,225);

	Sum=0;

	scene_4->addLine(-60,230-Sum*coefficient_y,-60+h/2*coefficient_x,+230-Sum*coefficient_y,pen2);//Горизонтальная прямая

	for(int x=1;x<=ui.Count_for_Normal_Distribution->value();x++)
	{
		//Отображение значений координат вдоль оси X
		text = scene_4->addText(QString::number((x0+(x)*h/*(x-1)*/), 'g', 4), QFont("Arial", 6 ));
		text->setPos(-66-h/2*coefficient_x+h*coefficient_x*(x),230);

		Sum+=ui.Table_for_Normal_Distribution_Page_1->item(2,x)->text().toFloat();

		//Отображение значений кооржинат вдоль оси Y
		text = scene_4->addText(QString::number(Sum,  'g',  2), QFont("Arial", 6 ));
		text->setPos((!Negative_Numbers_in_Table_for_Normal_Distribution)?-84:200,224-Sum*coefficient_y);

		scene_4->addLine(-60-h/2*coefficient_x+h*coefficient_x*(x),230-Sum*coefficient_y,-60+h/2*coefficient_x+h*coefficient_x*(x),230-Sum*coefficient_y,pen2);//Горизонтальная прямая
		scene_4->addLine(-60+h/2*coefficient_x+h*coefficient_x*(x-1),230,-60+h/2*coefficient_x+h*coefficient_x*(x-1),230-Sum*coefficient_y,pen3);//Вертикальная прямая

		scene_4->addLine(-60-h/2*coefficient_x+h*coefficient_x*(x),230-Sum*coefficient_y,-60-h/2*coefficient_x+h*coefficient_x*(x)+5,230-Sum*coefficient_y+5,pen2);//Стрелка на горизонтальной прямой
		scene_4->addLine(-60-h/2*coefficient_x+h*coefficient_x*(x),230-Sum*coefficient_y,-60-h/2*coefficient_x+h*coefficient_x*(x)+5,230-Sum*coefficient_y-5,pen2);//Стрелка на горизонтальной прямой
	}
	ui.Graphic_Empirical_Function_Browser->setScene(scene_4);
}

//=======================================================================================================================//
//======================================== Считывание из файла таблицы Лапласа ==========================================//
//=======================================================================================================================//
void TerVer_Lab1::Get_Laplace_Table(float *Matrix_Table_Laplace)
{
	bool Error_Input_Data_Size=false;
	bool Error_Input_Data_Text=false;

	bool Even_Numbered_Column=false;
	int index=0;
	QString tmp;

	QFile file("Table_Laplace.txt");	

	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Файл с данными не был найден!", "Файл \"Table_Laplace.txt\" не был найден");
	}

	QTextStream in(&file);

	while(!in.atEnd()) 
	{
		QString line = in.readLine();

		if(line.length())
		{
			for(int i=0;i<=line.length();i++)
			{
				if(line[i]==' '||i==line.length())
				{
					if(Even_Numbered_Column==false)//Считывание в Matrix_Table_Laplace[0][i] чисел из нечетных столбцов, и в Matrix_Table_Laplace[1][i] четных
						*(Matrix_Table_Laplace+index)=tmp.toFloat();
					else 
					{
						*(Matrix_Table_Laplace+250+index)=tmp.toFloat();
						index++;
					}

					tmp="";
					Even_Numbered_Column=!Even_Numbered_Column;
				}
				else 
				{
					if (line[i]==',' || line[i]=='.' ||line[i].isNumber())
					{
						if(line[i]!=',' ) tmp+=line[i];
						else tmp+='.';
					}
					else 
						Error_Input_Data_Text=true;
				}
			}
		}
	}

	if(Error_Input_Data_Text && Error_Input_Data_Size)
	{
		QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Laplace.txt\"", "Возможно в файле содержатся неверные данные.\n  Пожалуйста, попробуйте выбрать другой файл\n           или исправьте ошибки в текущем.");
	}
	else
	{
		if(Error_Input_Data_Text)QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Laplace.txt\"", "В файле с данными был найден текст, который был удален при считывании.\n           Пожалуйста, проверьте полученные данные на правильность.");
		if(Error_Input_Data_Size)QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Laplace.txt\"", "Количество данных полученных из файла не соответствуют\n                           размерности таблицы.");
	}

	// Сортировка матрицы по возрастанию
	float temp=0;
	for(int z=0;z<2;z++)
		for(int i=0;i<250;i++)
		{
			for (int j=i+1;j<=250-1;j++) 
			{
				if(i!=0)
				{
					if (*(Matrix_Table_Laplace+i+z*250)>*(Matrix_Table_Laplace+j+z*250))
					{
						temp=*(Matrix_Table_Laplace+i+z*250);
						*(Matrix_Table_Laplace+i+z*250)=*(Matrix_Table_Laplace+j+z*250);
						*(Matrix_Table_Laplace+j+z*250)=temp;
					}
				}
			}
		}
		file.close();
}

//=======================================================================================================================//
//======================================== Считывание из файла таблицы Пирсона ==========================================//
//=======================================================================================================================//
void TerVer_Lab1::Get_Pearson_Table(float *Matrix_Table_Pearson)
{
	bool Error_Input_Data_Size=false;
	bool Error_Input_Data_Text=false;

	bool Even_Numbered_Column=false;
	int index_i=0,index_j=0;
	QString tmp;

	QFile file("Table_Pearson.txt");	

	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(0, "Файл с данными не был найден!", "Файл \"Table_Pearson.txt\" не был найден");
	}

	QTextStream in(&file);

	while(!in.atEnd()) 
	{
		QString line = in.readLine();

		if(line.length())
		{
			for(int i=0;i<=line.length();i++)
			{
				if(line[i]==' '||i==line.length())
				{
					*(Matrix_Table_Pearson+index_j+index_i*13)=tmp.toFloat();
					if(index_j==12)
					{
						index_i++;
						index_j=0;
					}
					else index_j++;
					tmp="";
				}
				else 
				{
					if (line[i]==',' || line[i]=='.' ||line[i].isNumber())
					{
						if(line[i]!=',' ) tmp+=line[i];
						else tmp+='.';
					}
					else 
						Error_Input_Data_Text=true;
				}
			}
		}
	}

	if(Error_Input_Data_Text && Error_Input_Data_Size)
	{
		QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Pearson.txt\"", "Возможно в файле содержатся неверные данные.\n  Пожалуйста, попробуйте выбрать другой файл\n           или исправьте ошибки в текущем.");
	}
	else
	{
		if(Error_Input_Data_Text)QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Pearson.txt\"", "В файле с данными был найден текст, который был удален при считывании.\n           Пожалуйста, проверьте полученные данные на правильность.");
		if(Error_Input_Data_Size)QMessageBox::warning(0, "Ошибка при считывании данных из файла \"Table_Pearson.txt\"", "Количество данных полученных из файла не соответствуют\n                           размерности таблицы.");
	}
}

//=======================================================================================================================//
//========================================== Создание таблиц второй страницы ============================================//
//=======================================================================================================================//
void TerVer_Lab1::Create_Tables_Page_2_for_Normal_Distribution()
{
	QTableWidgetItem *item;
//=========================================================================//
//=============== Создание таблицы альтернативных интервалов ==============//
//=========================================================================//
	//Очистка таблицы
	ui.Intervals_Table_for_Normal_Distribution->setRowCount(0);
	ui.Intervals_Table_for_Normal_Distribution->setColumnCount(0);//Очистка таблицы

	if(ui.Count_for_Normal_Distribution_Page_2->text().toInt())
	{
		ui.Intervals_Table_for_Normal_Distribution->setRowCount(2);
		ui.Intervals_Table_for_Normal_Distribution->setColumnCount(ui.Count_for_Normal_Distribution_Page_2->text().toInt()+1);

		for(int i=1;i<ui.Count_for_Normal_Distribution_Page_2->text().toInt();i++)
		{
			item = new  QTableWidgetItem("[ ; )");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Intervals_Table_for_Normal_Distribution->setItem(0,i, item);
		}

		item = new  QTableWidgetItem("[ ; ]");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Intervals_Table_for_Normal_Distribution->setItem(0,ui.Count_for_Normal_Distribution_Page_2->text().toInt(), item);

		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Intervals_Table_for_Normal_Distribution->setItem(0,0, item);

		item = new  QTableWidgetItem("Alt. Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Intervals_Table_for_Normal_Distribution->setItem(1,0, item);
	}
//=========================================================================//
//================ Создание таблицы теоретических частот ==================//
//=========================================================================//
	//Очистка таблицы
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setRowCount(0);
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setColumnCount(0);//Очистка таблицы

	//Создание таблицы частот
	if(ui.Count_for_Normal_Distribution_Page_2->text().toInt())
	{
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setRowCount(4);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setColumnCount(ui.Count_for_Normal_Distribution_Page_2->text().toInt()+1);

		for(int i=1;i<ui.Count_for_Normal_Distribution_Page_2->text().toInt();i++)
		{
			item = new  QTableWidgetItem("[ ; )");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(0,i, item);
		}

		item = new  QTableWidgetItem("[ ; ]");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(0,ui.Count_for_Normal_Distribution_Page_2->text().toInt(), item);

		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(0,0, item);

		item = new  QTableWidgetItem("n'");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(1,0, item);

		item = new  QTableWidgetItem("ni-n'");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(2,0, item);

		item = new  QTableWidgetItem("((ni-n')^2)/n'");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(3,0, item);
	}
}

//=======================================================================================================================//
//==================================== Проверка гипотезы о нормальном распределении =====================================//
//=======================================================================================================================//
void TerVer_Lab1::Testing_Hypothesis_Normal_Distribution()
{
	if(Table_is_Full_for_Normal_Distribution)
	{
		Create_Tables_Page_2_for_Normal_Distribution();
		Fill_Table_Point_Estimates_for_Normal_Distribution();
		Fill_Table_Alternative_for_Normal_Distribution();
		Definition_of_Point_Estimates_for_Normal_Distribution();
		Drawing_Probabilities_for_Normal_Distribution();
		Definition_Result_Testing_Hypothesis_Normal_Distribution();
	}
}

//=======================================================================================================================//
//================================= Заполнение шапки таблицы точечных оценок ============================================//
//=======================================================================================================================//
void TerVer_Lab1::Fill_Table_Point_Estimates_for_Normal_Distribution()
{	
	QTableWidgetItem *item;

	for(int j=1;j<ui.Table_for_Normal_Distribution_Page_2->columnCount();j++)
	{
		item = new  QTableWidgetItem(ui.Table_for_Normal_Distribution_Page_2->item(0,j)->text());
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(0,j, item);
	}
}

//=======================================================================================================================//
//================================= Заполнение таблицы альтернативных интервалов ========================================//
//=======================================================================================================================//
void TerVer_Lab1::Fill_Table_Alternative_for_Normal_Distribution()
{
	QString tmp_str;
	QTableWidgetItem *item;

	for(int x=0;x<ui.Count_for_Normal_Distribution_Page_2->text().toInt();x++)
	{
		//Вывод интервала
		if(x!=ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1) tmp_str=("["+QString::number(x0+x*h,  'g',  4)+" ; "+QString::number(x0+(x+1)*h,  'g',  4)+")");//Возможно не 4?!
		else tmp_str=("["+QString::number(x0+x*h,  'g',  4)+" ; "+QString::number(x0+(x+1)*h,  'g',  4)+"]");//Возможно не 4?!

		item = new  QTableWidgetItem(tmp_str);
		item->setTextAlignment(Qt::AlignCenter);
		ui.Intervals_Table_for_Normal_Distribution->setItem(0,x+1, item);

		if(x==0)
		{
			tmp_str="[-inf ; "+QString::number(((((x0+(1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+"]";					
			item = new  QTableWidgetItem(tmp_str);
			item->setTextAlignment(Qt::AlignCenter);
			ui.Intervals_Table_for_Normal_Distribution->setItem(1,1, item);
		}
		else if(x==ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1)
		{
			tmp_str="["+QString::number(((((x0+(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+" ; inf]";
			item = new  QTableWidgetItem(tmp_str);
			item->setTextAlignment(Qt::AlignCenter);
			ui.Intervals_Table_for_Normal_Distribution->setItem(1,ui.Count_for_Normal_Distribution_Page_2->text().toInt(), item);
		}
		else
		{
			tmp_str=("["+QString::number(((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+" ; "+QString::number(((((x0+(x+1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+"]");//Возможно не 4?!
			item = new  QTableWidgetItem(tmp_str);
			item->setTextAlignment(Qt::AlignCenter);
			ui.Intervals_Table_for_Normal_Distribution->setItem(1,x+1, item);
		}
	}
}

//=======================================================================================================================//
//========================================= Определение точечных оценок =================================================//
//=======================================================================================================================//
void TerVer_Lab1::Definition_of_Point_Estimates_for_Normal_Distribution()
{
	float f1,f2,P;
	bool F1_is_Negative=false;
	bool F2_is_Negative=false;
	QTableWidgetItem *item;

	for(int x=0;x<ui.Count_for_Normal_Distribution_Page_2->text().toInt();x++)
	{
		if((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat())/ui.S_for_Normal_Distribution->text().toFloat())<0) F1_is_Negative=true;
		else F1_is_Negative=false;
		if(((((x0+((x+1))*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat())<0)F2_is_Negative=true;
		else F2_is_Negative=false;

		for(int p=0;p<250;p++)
		{
			if(!x)f1=-0.5;
			else if(Matrix_Table_Laplace[0][p]<=abs((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()))
					f1=Matrix_Table_Laplace[1][p];

			if(x==ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1)f2=0.5;
			else if(Matrix_Table_Laplace[0][p]<=abs((((x0+((x+1))*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()))
					f2=Matrix_Table_Laplace[1][p];
		}

		if(F1_is_Negative && x!=0)f1*=-1;
		if(F2_is_Negative && (x!=ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1))f2*=-1;

		P=f2-f1;

		item = new  QTableWidgetItem(QString::number(P*ui.Sum_for_Normal_Distribution_Page_2->text().toInt(),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(1,x+1, item);

		item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_Page_2->item(1,x+1)->text().toFloat()-ui.Table_Theoretical_Frequency_for_Normal_Distribution->item(1,x+1)->text().toFloat(),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(2,x+1, item);
		
		item = new  QTableWidgetItem(QString::number(pow((ui.Table_for_Normal_Distribution_Page_2->item(1,x+1)->text().toFloat()-ui.Table_Theoretical_Frequency_for_Normal_Distribution->item(1,x+1)->text().toFloat()),2)/ui.Table_Theoretical_Frequency_for_Normal_Distribution->item(1,x+1)->text().toFloat(),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Normal_Distribution->setItem(3,x+1, item);
	}
}

//=======================================================================================================================//
//=========================================== Отрисовка расчета вероятностей ============================================//
//=======================================================================================================================//
void TerVer_Lab1::Drawing_Probabilities_for_Normal_Distribution()
{
	float SS=0;
	QGraphicsScene *scene_5;
	scene_5 = new QGraphicsScene(ui.P_Browser_for_Normal_Distribution);
	QByteArray Function="";

	float f1,f2,P;
	bool F1_is_Negative=false;
	bool F2_is_Negative=false;
	QTableWidgetItem *item;

	for(int x=0;x<ui.Count_for_Normal_Distribution_Page_2->text().toInt();x++)
	{
		if((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat())/ui.S_for_Normal_Distribution->text().toFloat())<0) F1_is_Negative=true;
		else F1_is_Negative=false;
		if(((((x0+((x+1))*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat())<0)F2_is_Negative=true;
		else F2_is_Negative=false;

		for(int p=0;p<250;p++)
		{
			if(!x)f1=-0.5;
			else if(Matrix_Table_Laplace[0][p]<=abs((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()))
					f1=Matrix_Table_Laplace[1][p];

			if(x==ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1)f2=0.5;
			else if(Matrix_Table_Laplace[0][p]<=abs((((x0+((x+1))*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()))
					f2=Matrix_Table_Laplace[1][p];
		}

		if(F1_is_Negative && x!=0)f1*=-1;
		if(F2_is_Negative && (x!=ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1))f2*=-1;

		if(x==0)Function+="P(-inf < x < "+QString::number(((((x0+(x+1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") = Ф("+QString::number(((((x0+(x+1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") - Ф(-inf) = "+QString::number(f2,  'f',  2)+"+0.5 = "+QString::number(f2+0.5,  'f',  2)+"\n";
		else if(x==ui.Count_for_Normal_Distribution_Page_2->text().toInt()-1)Function+="P("+QString::number(((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+" < x < inf) = Ф(inf) - Ф("+QString::number(((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") = 0.5"+((f1<0)?"+":"-")+QString::number((f1<0)? abs(f1):f1,  'f',  2)+" = "+QString::number(0.5-f1,  'f',  2)+"\n";
		else Function+="P("+QString::number(((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+" < x < "+QString::number(((((x0+(x+1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") = Ф("+QString::number(((((x0+(x+1)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") - Ф("+QString::number(((((x0+(x)*h)-ui.X_for_Normal_Distribution->text().toFloat()))/ui.S_for_Normal_Distribution->text().toFloat()),  'f',  2)+") = "+QString::number(f2,  'f',  2)+((f1<0)?"+":"-")+QString::number((f1<0)? abs(f1):f1,  'f',  2)+" = "+QString::number(f2-f1,  'f',  2)+"\n";
	}
	scene_5->addText(Function);
	ui.P_Browser_for_Normal_Distribution->setScene(scene_5);
}

//=======================================================================================================================//
//================= Расчет нормального значения Хи-квадрата Пирсона и вывод результата ==================================//
//=======================================================================================================================//
void TerVer_Lab1::Definition_Result_Testing_Hypothesis_Normal_Distribution()
{
	float Observed_Value=0;

	for(int i=1;i<=ui.Count_for_Normal_Distribution_Page_2->text().toInt();i++)
	{
		Observed_Value+=ui.Table_Theoretical_Frequency_for_Normal_Distribution->item(3,i)->text().toFloat();
	}
	ui.label_97->setText("= "+QString::number(Observed_Value,'g',4)+" ;");
	ui.label_58->setText("X       = "+QString::number(Observed_Value,'g',4));

	if(ui.Significance_Level_for_Normal_Distribution_1->isChecked())
	{
		ui.label_100->setText("(0.005;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][12],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][12],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][12])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][12])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_2->isChecked())
	{
		ui.label_100->setText("(0.01;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][11],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][11],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][11])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][11])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_3->isChecked())
	{
		ui.label_100->setText("(0.025;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][10],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][10],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][10])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][10])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_4->isChecked())
	{
		ui.label_100->setText("(0.05;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][9],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][9],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][9])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][9])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_5->isChecked())
	{
		ui.label_100->setText("(0.1;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][8],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][8],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][8])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][8])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_6->isChecked())
	{
		ui.label_100->setText("(0.25;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][7],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][7],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][7])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][7])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_7->isChecked())
	{
		ui.label_100->setText("(0.5;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][6],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][6],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][6])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][6])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_8->isChecked())
	{
		ui.label_100->setText("(0.75;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][5],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][5],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][5])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][5])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_9->isChecked())
	{
		ui.label_100->setText("(0.9;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][4],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][4],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][4])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][4])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_10->isChecked())
	{
		ui.label_100->setText("(0.95;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][3],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][3],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][3])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][3])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_11->isChecked())
	{
		ui.label_100->setText("(0.975;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][2],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][2],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][2])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][2])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_12->isChecked())
	{
		ui.label_100->setText("(0.99;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");

		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][1],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][1],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][1])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][1])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
	else if(ui.Significance_Level_for_Normal_Distribution_13->isChecked())
	{
		ui.label_100->setText("(0.995;"+QString::number(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)+")");
		ui.label_99->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][0],'f',3)+";");
		ui.label_107->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][0],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][0])
		{
			ui.label_108->setText("<");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Нет оснований отвергнуть гипотезу о нормальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Normal_Distribution_Page_2->text().toInt()-3)-1][0])
		{
			ui.label_108->setText(">");
			ui.Result_Testing_Hypothesis_Normal_Distribution->setText("Гипотеза о нормальном распределении отвергается");
		}
		else ui.label_108->setText("=");
	}
}

//=======================================================================================================================//
//=========================================== Очистка данных второй страницы ============================================//
//=======================================================================================================================//
void TerVer_Lab1::Clear_Data_Page_2_for_Normal_Distribution()
{
	//Очистка таблиц
	ui.Intervals_Table_for_Normal_Distribution->setRowCount(0);
	ui.Intervals_Table_for_Normal_Distribution->setColumnCount(0);
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setRowCount(0);
	ui.Table_Theoretical_Frequency_for_Normal_Distribution->setColumnCount(0);
	ui.Result_Testing_Hypothesis_Normal_Distribution->clear();
	ui.label_97->setText("= ... ;");
	ui.label_58->setText("X       =     ...");
	ui.label_100->setText("критич.");
	ui.label_99->setText("X          = X          = ... ;");
	ui.label_107->setText("X          =   ...");

	//Отрисовка системы координат
	QGraphicsScene *scene;
	scene = new QGraphicsScene(ui.P_Browser_for_Normal_Distribution);
	ui.P_Browser_for_Normal_Distribution->setScene(scene);
}

void TerVer_Lab1::Create_Table_for_Binomial_Distribution()
{
	QTableWidgetItem *item;

	//Очистка таблицы 
	ui.Table_for_Binomial_Distribution->setRowCount(0);
	ui.Table_for_Binomial_Distribution->setColumnCount(0);

	//Создание таблицы
	if(ui.Count_for_Binomial_Distribution->value())
	{
		ui.Table_for_Binomial_Distribution->setRowCount(3);
		ui.Table_for_Binomial_Distribution->setColumnCount(ui.Count_for_Binomial_Distribution->value()+1);

		for(int i=1;i<=ui.Count_for_Binomial_Distribution->value();i++)
		{
			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Binomial_Distribution->setItem(0,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Binomial_Distribution->setItem(1,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Binomial_Distribution->setItem(2,i, item);
		}
		
		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Binomial_Distribution->setItem(0,0, item);

		item = new  QTableWidgetItem("Mi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Binomial_Distribution->setItem(1,0, item);

		item = new  QTableWidgetItem("Wi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Binomial_Distribution->setItem(2,0, item);
	}
}

void TerVer_Lab1::Build_Table_for_Binomial_Distribution()
{
	int Count_Intervals;
	if(ui.Count_for_Binomial_Distribution->value()) Count_Intervals=ui.Count_for_Binomial_Distribution->value();
	Clear_Data_Table_for_Binomial_Distribution();
	Clear_Data_for_Binomial_Distribution();
	ui.Count_for_Binomial_Distribution->setValue(Count_Intervals);
	Create_Table_for_Binomial_Distribution();

	for (int i=0;i<Count_Elements_in_Array_for_Binomial_Distribution;i++)
		*(Array_Data_for_Binomial_Distribution+i)=0;

	Count_Elements_in_Array_for_Binomial_Distribution=0;
	Negative_Numbers_in_Table_for_Binomial_Distribution=false;
	Table_is_Full_for_Binomial_Distribution=false;
}

void TerVer_Lab1::Clear_Data_for_Binomial_Distribution()
{
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setRowCount(0);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setColumnCount(0);
	ui.Significance_Level_1_Page_3_Point_2->setChecked(true);
	ui.n->setValue(0);
	ui.p->setValue(0);
	ui.q->setValue(0);
	ui.Result_Testing_Hypothesis_Binomial_Distribution->clear();
	ui.label_197->setText("= ... ;");
	ui.label_186->setText("X       =     ...");
	ui.label_203->setText("критич.");
	ui.label_205->setText("X          = X          = ... ;");
	ui.label_181->setText("X          =   ...");

	//Отрисовка системы координат
	QGraphicsScene *scene;
	scene = new QGraphicsScene(ui.P_Browser_for_Binomial_Distribution);
	ui.P_Browser_for_Binomial_Distribution->setScene(scene);	
}

void TerVer_Lab1::Clear_Data_Table_for_Binomial_Distribution()
{
	Table_is_Full_for_Binomial_Distribution=false;
	Table_is_Full_to_Hands_for_Binomial_Distribution=false;

	ui.Table_for_Binomial_Distribution->setRowCount(0);
	ui.Table_for_Binomial_Distribution->setColumnCount(0);

	ui.Sum_for_Binomial_Distribution->clear();
	ui.Count_for_Binomial_Distribution->setValue(0);
}

void TerVer_Lab1::Calculate_Input_Data_for_Binomial_Distribution()
{
	int Count_of_Occurrences=0;
	int Sum_for_Binomial_Distribution=0;
	QTableWidgetItem *item;

//=========================================================================//
//======== Заполнение таблицы частост для первого распределения ===========//
//=========================================================================//
	ui.Count_for_Binomial_Distribution->setValue(1);
	Create_Table_for_Binomial_Distribution();

	item = new  QTableWidgetItem(QString::number(Array_Data_for_Binomial_Distribution[0]));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Binomial_Distribution->setItem(0,1, item);

	item = new  QTableWidgetItem(QString::number(1));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Binomial_Distribution->setItem(1,1, item);

	for(int i=0;i<Count_Elements_in_Array_for_Binomial_Distribution;i++)
	{
		Count_of_Occurrences=0;
		for(int j=1;j<ui.Table_for_Binomial_Distribution->columnCount();j++)
		{
			if(Array_Data_for_Binomial_Distribution[i] != ui.Table_for_Binomial_Distribution->item(0,j)->text().toFloat())Count_of_Occurrences++;
			else 
			{
				if(!(i==0 && j==1))
				{
					item = new  QTableWidgetItem(QString::number(ui.Table_for_Binomial_Distribution->item(1,j)->text().toFloat()+1));
					item->setTextAlignment(Qt::AlignCenter);
					ui.Table_for_Binomial_Distribution->setItem(1,j, item);
				}
			}
			if(Count_of_Occurrences==ui.Count_for_Binomial_Distribution->value())
			{
				ui.Count_for_Binomial_Distribution->setValue(ui.Count_for_Binomial_Distribution->value()+1);
				ui.Table_for_Binomial_Distribution->setColumnCount(ui.Count_for_Binomial_Distribution->value()+1);

				item = new  QTableWidgetItem(QString::number(Array_Data_for_Binomial_Distribution[i]));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(0,ui.Count_for_Binomial_Distribution->value(), item);

				item = new  QTableWidgetItem(QString::number(1));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(1,ui.Count_for_Binomial_Distribution->value(), item);

				break;
			}
		}
	}

	for(int i=1;i<ui.Table_for_Binomial_Distribution->columnCount();i++) 
		Sum_for_Binomial_Distribution+=ui.Table_for_Binomial_Distribution->item(1,i)->text().toInt();

	ui.Sum_for_Binomial_Distribution->setText(QString::number(Sum_for_Binomial_Distribution));

	for(int i=1;i<ui.Table_for_Binomial_Distribution->columnCount();i++)
	{
		item = new  QTableWidgetItem(QString::number(ui.Table_for_Binomial_Distribution->item(1,i)->text().toFloat()/ui.Sum_for_Binomial_Distribution->text().toFloat(),'g',4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Binomial_Distribution->setItem(2,i, item);
	}
//=========================================================================//
//======== Сортировка таблицы частост для первого распределения ===========//
//=========================================================================//
	float Temp_Value,Temp_Count;
	for(int j=ui.Table_for_Binomial_Distribution->columnCount()-1;j>=1;j--)
		for(int i=1;i<j;i++)
		{
			if(ui.Table_for_Binomial_Distribution->item(0,i)->text().toFloat()>ui.Table_for_Binomial_Distribution->item(0,i+1)->text().toFloat())
			{
				Temp_Value=ui.Table_for_Binomial_Distribution->item(0,i)->text().toFloat();
				Temp_Count=ui.Table_for_Binomial_Distribution->item(1,i)->text().toFloat();

				item = new  QTableWidgetItem(QString::number(ui.Table_for_Binomial_Distribution->item(0,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(0,i, item);
				item = new  QTableWidgetItem(QString::number(ui.Table_for_Binomial_Distribution->item(1,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(1,i, item);

				item = new  QTableWidgetItem(QString::number(Temp_Value));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(0,i+1, item);
				item = new  QTableWidgetItem(QString::number(Temp_Count));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Binomial_Distribution->setItem(1,i+1, item);
			}
		}
}

void TerVer_Lab1::Formation_Table_of_Characteristics_for_Binomial_Distribution()
{
	QTableWidgetItem *item;

	if(!Table_is_Full_for_Binomial_Distribution)
	{
		if(!Error_Fill_Table_for_Binomial_Distribution || !Error_Fill_Row_Intervals_for_Binomial_Distribution || !Error_Fill_Row_Frequency_for_Binomial_Distribution || !Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution)
		{
			if(!Error_Fill_Row_Intervals_for_Binomial_Distribution && (!Error_Fill_Row_Frequency_for_Binomial_Distribution || !Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution))
			{
				if(ui.Count_for_Binomial_Distribution->value()!=ui.Table_for_Binomial_Distribution->columnCount()-1)
				{
					QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
					ui.Count_for_Binomial_Distribution->setValue(ui.Table_for_Binomial_Distribution->columnCount()-1);
				}
//=========================================================================//
//========== Заполнение недостающих строк в таблице характеристик =========//
//=========================================================================//
				if(Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution)
				{
					int Sum_for_Binomial_Distribution=0;
					for(int x=1;x<ui.Table_for_Binomial_Distribution->columnCount();x++)
						Sum_for_Binomial_Distribution+=ui.Table_for_Binomial_Distribution->item(1,x)->text().toInt();

					ui.Sum_for_Binomial_Distribution->setText(QString::number(Sum_for_Binomial_Distribution));

					for(int x=1;x<ui.Table_for_Binomial_Distribution->columnCount();x++)
					{
						item = new  QTableWidgetItem(QString::number((ui.Table_for_Binomial_Distribution->item(1,x)->text().toFloat()/ui.Sum_for_Binomial_Distribution->text().toFloat()), 'g', 2));
						item->setTextAlignment(Qt::AlignCenter);
						ui.Table_for_Binomial_Distribution->setItem(2,x, item);
					}
					Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution=false;
				}

				if(Error_Fill_Row_Frequency_for_Binomial_Distribution)
				{
					if(!Error_Fill_Sum_for_Binomial_Distribution)
					{
						for(int x=1;x<ui.Table_for_Binomial_Distribution->columnCount();x++)
						{
							item = new  QTableWidgetItem(QString::number((int)((ui.Table_for_Binomial_Distribution->item(2,x)->text().toFloat()*ui.Sum_for_Binomial_Distribution->text().toFloat())+0.5), 'g', 1));//0.5 - поправочный коэффициент, для округления в большую сторону
							item->setTextAlignment(Qt::AlignCenter);
							ui.Table_for_Binomial_Distribution->setItem(1,x, item);
						}
					}
					else 
					{
						QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Сумма частот (N)\" было заполнено неверно");
						Error_Fill_Row_Frequency_for_Binomial_Distribution=true;
					}
					Error_Fill_Row_Frequency_for_Binomial_Distribution=false;
				}

				if(!Error_Fill_Row_Intervals_for_Binomial_Distribution && !Error_Fill_Row_Frequency_for_Binomial_Distribution && !Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution)
					Table_is_Full_for_Binomial_Distribution=true;
			}
			else
			{
				QMessageBox::warning(0, "Ошибка при считывании данных", "Возможно в программе содержатся неверные данные.\n  Пожалуйста, исправьте ошибки и попробуйте снова.");
				Table_is_Full_for_Binomial_Distribution=false;
			}
		}
		else 
		{
			QMessageBox::warning(0, "Ошибка при считывании данных", "Не было найдено никаких данных.");
			Table_is_Full_for_Binomial_Distribution=false;
		}
	}
}

bool TerVer_Lab1::Calculating_Probability()
{
	if(ui.p->value() || ui.q->value())
	{
		if(ui.p->value() && ui.q->value())
		{
			if(ui.p->value()+ui.q->value()==1) return true;
			else QMessageBox::warning(0, "Ошибка при считывании данных", "Значения p и q были введены некорректно.\nПожалуйста, исправьте ошибки и попробуйте снова.");
		}
		else 
		{
			if(ui.p->value() && !ui.q->value())
			{
				ui.q->setValue(1-ui.p->value()); 
				return true;
			}

			if(!ui.p->value() && ui.q->value())
			{
				ui.p->setValue(1-ui.q->value()); 
				return true;
			}
		}
	}
	else
	{
		float Temp_Sum=0;
		Number_Degrees_Freedom=2;
		for(int x=1;x<ui.Table_for_Binomial_Distribution->columnCount();x++)
			Temp_Sum+=ui.Table_for_Binomial_Distribution->item(0,x)->text().toFloat()*ui.Table_for_Binomial_Distribution->item(1,x)->text().toFloat();

		ui.p->setValue(Temp_Sum/(ui.Sum_for_Binomial_Distribution->text().toFloat()*ui.n->value()));
		ui.q->setValue(1-ui.p->value()); 

		return true;
	}

	return false;
}

void TerVer_Lab1::Drawing_Probabilities_for_Binomial_Distribution()
{
	QTableWidgetItem *item;
	QGraphicsScene *scene_6;
	QByteArray Function="";
	float C=0;

	scene_6 = new QGraphicsScene(ui.P_Browser_for_Binomial_Distribution);

	for(int x=0;x<ui.Count_for_Binomial_Distribution->value();x++)
	{
		if(ui.n->text().toInt()>x)///???????????
		{
			int Temp=ui.n->text().toInt()-x;
			C=Factorial(ui.n->text().toInt())/(Factorial(x)*Factorial(Temp));
		}
		else if(ui.n->text().toInt()==x)C=1;///???????????

		Function+="P("+QString::number(x)+") = "+QString::number(C,'f',3)+" * "+QString::number((pow(ui.p->value(),x)),'f',3)+" * "+QString::number((pow(ui.q->value(),ui.n->value()-x)),'f',3)+" = "+QString::number((C*pow(ui.p->value(),x)*pow(ui.q->value(),ui.n->value()-x)),'f',4)+"\n";
	}

	scene_6->addText(Function);
	ui.P_Browser_for_Binomial_Distribution->setScene(scene_6);
}

int TerVer_Lab1::Factorial(int number)
{
	int result=1;
	if(number<=1)return 1;
	else
		for(int i=1;i<=number;i++)
		{
			result*=i;
		}
	return result;
}

void TerVer_Lab1::Testing_Hypothesis_Binomial_Distribution()
{
	Error_Checking_for_Binomial_Distribution();
	Formation_Table_of_Characteristics_for_Binomial_Distribution();

	if(Table_is_Full_for_Binomial_Distribution)
	{
		if(ui.Count_for_Binomial_Distribution->value()!=ui.Table_for_Binomial_Distribution->columnCount()-1)
		{
			QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
			ui.Count_for_Binomial_Distribution->setValue(ui.Table_for_Binomial_Distribution->columnCount()-1);
		}
		else
		{
			int Sum_for_Binomial_Distribution=0;

			for(int i=1;i<ui.Table_for_Binomial_Distribution->columnCount();i++) 
				Sum_for_Binomial_Distribution+=ui.Table_for_Binomial_Distribution->item(1,i)->text().toInt();

			if(ui.Sum_for_Binomial_Distribution->text().toInt()!=Sum_for_Binomial_Distribution)
			{
				QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество повторений (n)\" не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее данным таблицы.");
				ui.Sum_for_Binomial_Distribution->setText(QString::number(Sum_for_Binomial_Distribution));		
			}
		}

		if(ui.n->value())
		{
			if(Calculating_Probability())
			{
				Drawing_Probabilities_for_Binomial_Distribution();
				Definition_of_Point_Estimates_for_Binomial_Distribution();
				Definition_Result_Testing_Hypothesis_Binomial_Distribution();
			}
		}
		else
		{
			QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Количество повторений (n)\" было заполнено неверно");
		}
	}
}

void TerVer_Lab1::Definition_of_Point_Estimates_for_Binomial_Distribution()
{
	QTableWidgetItem *item;
	float C=0;
	
	//Создание таблицы
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setRowCount(4);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setColumnCount(ui.Count_for_Binomial_Distribution->value()+1);

	//Шапка таблицы
	item = new  QTableWidgetItem("n'");
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(0,0, item);

	item = new  QTableWidgetItem("ni-n'");
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(1,0, item);

	item = new  QTableWidgetItem("(ni-n')^2'");
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(2,0, item);

	item = new  QTableWidgetItem("((ni-n')^2)/n'");
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(3,0, item);

	for(int x=0;x<ui.Count_for_Binomial_Distribution->value();x++)
	{
		if(ui.n->text().toInt()>x)///???????????
		{
			int Temp=ui.n->text().toInt()-x;
			C=Factorial(ui.n->text().toInt())/(Factorial(x)*Factorial(Temp));
		}
		else if(ui.n->text().toInt()==x)C=1;///???????????

		item = new  QTableWidgetItem(QString::number(((C*pow(ui.p->value(),x)*pow(ui.q->value(),ui.n->value()-x))*ui.Sum_for_Binomial_Distribution->text().toFloat()),'f',3));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(0,x+1, item);

		item = new  QTableWidgetItem(QString::number(ui.Table_for_Binomial_Distribution->item(1,x+1)->text().toFloat()-ui.Table_Theoretical_Frequency_for_Binomial_Distribution->item(0,x+1)->text().toFloat(),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(1,x+1, item);

		item = new  QTableWidgetItem(QString::number(pow((ui.Table_for_Binomial_Distribution->item(1,x+1)->text().toFloat()-ui.Table_Theoretical_Frequency_for_Binomial_Distribution->item(0,x+1)->text().toFloat()),2),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(2,x+1, item);

		item = new  QTableWidgetItem(QString::number(pow((ui.Table_for_Binomial_Distribution->item(1,x+1)->text().toFloat()-ui.Table_Theoretical_Frequency_for_Binomial_Distribution->item(0,x+1)->text().toFloat()),2)/ui.Table_Theoretical_Frequency_for_Binomial_Distribution->item(0,x+1)->text().toFloat(),  'g',  4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_Theoretical_Frequency_for_Binomial_Distribution->setItem(3,x+1, item);

	}
}

//=======================================================================================================================//
//================= Расчет биномиального значения Хи-квадрата Пирсона и вывод результата ==================================//
//=======================================================================================================================//
void TerVer_Lab1::Definition_Result_Testing_Hypothesis_Binomial_Distribution()
{
	float Observed_Value=0;

	for(int i=1;i<=ui.Count_for_Binomial_Distribution->text().toInt();i++)
	{
		Observed_Value+=ui.Table_Theoretical_Frequency_for_Binomial_Distribution->item(3,i)->text().toFloat();
	}
	ui.label_197->setText("= "+QString::number(Observed_Value,'g',4)+" ;");
	ui.label_186->setText("X       = "+QString::number(Observed_Value,'g',4));

	if(ui.Significance_Level_1_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.005;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][12],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][12],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][12])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][12])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_2_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.01;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][11],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][11],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][11])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][11])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_3_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.025;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][10],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][10],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][10])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][10])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_4_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.05;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][9],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][9],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][9])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][9])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_5_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.1;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][8],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][8],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][8])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][8])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_6_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.25;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][7],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][7],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][7])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][7])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_7_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.5;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][6],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][6],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][6])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][6])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_8_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.75;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][5],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][5],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][5])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][5])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_9_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.9;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][4],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][4],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][4])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][4])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_10_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.95;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][3],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][3],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][3])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][3])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_11_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.975;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][2],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][2],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][2])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][2])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_12_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.99;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");

		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][1],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][1],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][1])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][1])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
	else if(ui.Significance_Level_13_Page_3_Point_2->isChecked())
	{
		ui.label_203->setText("(0.995;"+QString::number(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)+")");
		ui.label_205->setText("X          = X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][0],'f',3)+";");
		ui.label_181->setText("X          = "+QString::number(Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][0],'f',3));
		if(Observed_Value<Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][0])
		{
			ui.label_182->setText("<");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Нет оснований отвергнуть гипотезу о биномиальном распределении");
		}
		else if(Observed_Value>Matrix_Table_Pearson[(ui.Count_for_Binomial_Distribution->text().toInt()-1-Number_Degrees_Freedom)-1][0])
		{
			ui.label_182->setText(">");
			ui.Result_Testing_Hypothesis_Binomial_Distribution->setText("Гипотеза о биномиальном распределении отвергается");
		}
		else ui.label_182->setText("=");
	}
}
//////////////////////////////////////////////////////////////////////////
void TerVer_Lab1::Create_Table_for_Normal_Distribution_1()
{
	QTableWidgetItem *item;

	//Очистка таблицы 
	ui.Table_for_Normal_Distribution_1->setRowCount(0);
	ui.Table_for_Normal_Distribution_1->setColumnCount(0);

	//Создание таблицы
	if(ui.Count_for_Normal_Distribution_1->value())
	{
		ui.Table_for_Normal_Distribution_1->setRowCount(3);
		ui.Table_for_Normal_Distribution_1->setColumnCount(ui.Count_for_Normal_Distribution_1->value()+1);

		for(int i=1;i<=ui.Count_for_Normal_Distribution_1->value();i++)
		{
			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_1->setItem(0,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_1->setItem(1,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_1->setItem(2,i, item);
		}
		
		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_1->setItem(0,0, item);

		item = new  QTableWidgetItem("Mi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_1->setItem(1,0, item);

		item = new  QTableWidgetItem("Wi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_1->setItem(2,0, item);
	}
}

void TerVer_Lab1::Build_Table_for_Normal_Distribution_1()
{
	int Count_Intervals;
	if(ui.Count_for_Normal_Distribution_1->value()) Count_Intervals=ui.Count_for_Normal_Distribution_1->value();
	Clear_Data_Table_for_Normal_Distributions_1();
	Clear_Data_Two_Variances_for_Normal_Distributions();
	ui.Count_for_Normal_Distribution_1->setValue(Count_Intervals);
	Create_Table_for_Normal_Distribution_1();

	for (int i=0;i<Count_Elements_in_Array_for_Normal_Distribution_1;i++)
		*(Array_Data_for_Normal_Distribution_1+i)=0;

	Count_Elements_in_Array_for_Normal_Distribution_1=0;
	Negative_Numbers_in_Table_for_Normal_Distribution_1=false;
	Table_is_Full_for_Normal_Distribution_1=false;
}

void TerVer_Lab1::Calculate_Input_Data_for_Normal_Distribution_1()
{
	int Count_of_Occurrences=0;
	int Sum_for_Normal_Distribution_1=0;
	QTableWidgetItem *item;

//=========================================================================//
//======== Заполнение таблицы частост для первого распределения ===========//
//=========================================================================//
	ui.Count_for_Normal_Distribution_1->setValue(1);
	Create_Table_for_Normal_Distribution_1();

	item = new  QTableWidgetItem(QString::number(Array_Data_for_Normal_Distribution_1[0]));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Normal_Distribution_1->setItem(0,1, item);

	item = new  QTableWidgetItem(QString::number(1));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Normal_Distribution_1->setItem(1,1, item);

	for(int i=0;i<Count_Elements_in_Array_for_Normal_Distribution_1;i++)
	{
		Count_of_Occurrences=0;
		for(int j=1;j<ui.Table_for_Normal_Distribution_1->columnCount();j++)
		{
			if(Array_Data_for_Normal_Distribution_1[i] != ui.Table_for_Normal_Distribution_1->item(0,j)->text().toFloat())Count_of_Occurrences++;
			else 
			{
				if(!(i==0 && j==1))
				{
					item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_1->item(1,j)->text().toFloat()+1));
					item->setTextAlignment(Qt::AlignCenter);
					ui.Table_for_Normal_Distribution_1->setItem(1,j, item);
				}
			}
			if(Count_of_Occurrences==ui.Count_for_Normal_Distribution_1->value())
			{
				ui.Count_for_Normal_Distribution_1->setValue(ui.Count_for_Normal_Distribution_1->value()+1);
				ui.Table_for_Normal_Distribution_1->setColumnCount(ui.Count_for_Normal_Distribution_1->value()+1);

				item = new  QTableWidgetItem(QString::number(Array_Data_for_Normal_Distribution_1[i]));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(0,ui.Count_for_Normal_Distribution_1->value(), item);

				item = new  QTableWidgetItem(QString::number(1));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(1,ui.Count_for_Normal_Distribution_1->value(), item);

				break;
			}
		}
	}

	for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++) 
		Sum_for_Normal_Distribution_1+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();

	ui.Sum_for_Normal_Distribution_1->setText(QString::number(Sum_for_Normal_Distribution_1));

	for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++)
	{
		item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_1->item(1,i)->text().toFloat()/ui.Sum_for_Normal_Distribution_1->text().toFloat(),'g',4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_1->setItem(2,i, item);
	}
//=========================================================================//
//======== Сортировка таблицы частост для первого распределения ===========//
//=========================================================================//
	float Temp_Value,Temp_Count;
	for(int j=ui.Table_for_Normal_Distribution_1->columnCount()-1;j>=1;j--)
		for(int i=1;i<j;i++)
		{
			if(ui.Table_for_Normal_Distribution_1->item(0,i)->text().toFloat()>ui.Table_for_Normal_Distribution_1->item(0,i+1)->text().toFloat())
			{
				Temp_Value=ui.Table_for_Normal_Distribution_1->item(0,i)->text().toFloat();
				Temp_Count=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toFloat();

				item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_1->item(0,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(0,i, item);
				item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_1->item(1,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(1,i, item);

				item = new  QTableWidgetItem(QString::number(Temp_Value));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(0,i+1, item);
				item = new  QTableWidgetItem(QString::number(Temp_Count));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_1->setItem(1,i+1, item);
			}
		}
}

void TerVer_Lab1::Create_Table_for_Normal_Distribution_2()
{
	QTableWidgetItem *item;

	//Очистка таблицы 
	ui.Table_for_Normal_Distribution_2->setRowCount(0);
	ui.Table_for_Normal_Distribution_2->setColumnCount(0);

	//Создание таблицы
	if(ui.Count_for_Normal_Distribution_2->value())
	{
		ui.Table_for_Normal_Distribution_2->setRowCount(3);
		ui.Table_for_Normal_Distribution_2->setColumnCount(ui.Count_for_Normal_Distribution_2->value()+1);

		for(int i=1;i<=ui.Count_for_Normal_Distribution_2->value();i++)
		{
			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_2->setItem(0,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_2->setItem(1,i, item);

			item = new  QTableWidgetItem("");
			item->setTextAlignment(Qt::AlignCenter);
			ui.Table_for_Normal_Distribution_2->setItem(2,i, item);
		}
		
		//Шапка таблицы
		item = new  QTableWidgetItem("Xi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_2->setItem(0,0, item);

		item = new  QTableWidgetItem("Mi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_2->setItem(1,0, item);

		item = new  QTableWidgetItem("Wi");
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_2->setItem(2,0, item);
	}
}

void TerVer_Lab1::Build_Table_for_Normal_Distribution_2()
{
	int Count_Intervals;
	if(ui.Count_for_Normal_Distribution_2->value()) Count_Intervals=ui.Count_for_Normal_Distribution_2->value();
	Clear_Data_Table_for_Normal_Distributions_2();
	Clear_Data_Two_Variances_for_Normal_Distributions();
	ui.Count_for_Normal_Distribution_2->setValue(Count_Intervals);
	Create_Table_for_Normal_Distribution_2();

	for (int i=0;i<Count_Elements_in_Array_for_Normal_Distribution_2;i++)
		*(Array_Data_for_Normal_Distribution_2+i)=0;

	Count_Elements_in_Array_for_Normal_Distribution_2=0;
	Negative_Numbers_in_Table_for_Normal_Distribution_2=false;
	Table_is_Full_for_Normal_Distribution_2=false;
}

void TerVer_Lab1::Calculate_Input_Data_for_Normal_Distribution_2()
{
	int Count_of_Occurrences=0;
	int Sum_for_Normal_Distribution_2=0;
	QTableWidgetItem *item;

//=========================================================================//
//======== Заполнение таблицы частост для первого распределения ===========//
//=========================================================================//
	ui.Count_for_Normal_Distribution_2->setValue(1);
	Create_Table_for_Normal_Distribution_2();

	item = new  QTableWidgetItem(QString::number(Array_Data_for_Normal_Distribution_2[0]));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Normal_Distribution_2->setItem(0,1, item);

	item = new  QTableWidgetItem(QString::number(1));
	item->setTextAlignment(Qt::AlignCenter);
	ui.Table_for_Normal_Distribution_2->setItem(1,1, item);

	for(int i=0;i<Count_Elements_in_Array_for_Normal_Distribution_2;i++)
	{
		Count_of_Occurrences=0;
		for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)
		{
			if(Array_Data_for_Normal_Distribution_2[i] != ui.Table_for_Normal_Distribution_2->item(0,j)->text().toFloat())Count_of_Occurrences++;
			else 
			{
				if(!(i==0 && j==1))
				{
					item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_2->item(1,j)->text().toFloat()+1));
					item->setTextAlignment(Qt::AlignCenter);
					ui.Table_for_Normal_Distribution_2->setItem(1,j, item);
				}
			}
			if(Count_of_Occurrences==ui.Count_for_Normal_Distribution_2->value())
			{
				ui.Count_for_Normal_Distribution_2->setValue(ui.Count_for_Normal_Distribution_2->value()+1);
				ui.Table_for_Normal_Distribution_2->setColumnCount(ui.Count_for_Normal_Distribution_2->value()+1);

				item = new  QTableWidgetItem(QString::number(Array_Data_for_Normal_Distribution_2[i]));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(0,ui.Count_for_Normal_Distribution_2->value(), item);

				item = new  QTableWidgetItem(QString::number(1));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(1,ui.Count_for_Normal_Distribution_2->value(), item);

				break;
			}
		}
	}

	for(int i=1;i<ui.Table_for_Normal_Distribution_2->columnCount();i++) 
		Sum_for_Normal_Distribution_2+=ui.Table_for_Normal_Distribution_2->item(1,i)->text().toInt();

	ui.Sum_for_Normal_Distribution_2->setText(QString::number(Sum_for_Normal_Distribution_2));

	for(int i=1;i<ui.Table_for_Normal_Distribution_2->columnCount();i++)
	{
		item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_2->item(1,i)->text().toFloat()/ui.Sum_for_Normal_Distribution_2->text().toFloat(),'g',4));
		item->setTextAlignment(Qt::AlignCenter);
		ui.Table_for_Normal_Distribution_2->setItem(2,i, item);
	}
//=========================================================================//
//======== Сортировка таблицы частост для первого распределения ===========//
//=========================================================================//
	float Temp_Value,Temp_Count;
	for(int j=ui.Table_for_Normal_Distribution_2->columnCount()-1;j>=1;j--)
		for(int i=1;i<j;i++)
		{
			if(ui.Table_for_Normal_Distribution_2->item(0,i)->text().toFloat()>ui.Table_for_Normal_Distribution_2->item(0,i+1)->text().toFloat())
			{
				Temp_Value=ui.Table_for_Normal_Distribution_2->item(0,i)->text().toFloat();
				Temp_Count=ui.Table_for_Normal_Distribution_2->item(1,i)->text().toFloat();

				item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_2->item(0,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(0,i, item);
				item = new  QTableWidgetItem(QString::number(ui.Table_for_Normal_Distribution_2->item(1,i+1)->text().toFloat()));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(1,i, item);

				item = new  QTableWidgetItem(QString::number(Temp_Value));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(0,i+1, item);
				item = new  QTableWidgetItem(QString::number(Temp_Count));
				item->setTextAlignment(Qt::AlignCenter);
				ui.Table_for_Normal_Distribution_2->setItem(1,i+1, item);
			}
		}
}

void TerVer_Lab1::Error_Checking_for_Two_Normal_Distributions()
{
//=========================================================================//
//========= Проверка данных для первой генеральной совокупности ===========//
//=========================================================================//
	int Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_1=0;
	int Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_1=0;
	int Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_1=0;

	Error_Fill_Table_for_Normal_Distribution_1=false;
	Error_Fill_Count_for_Normal_Distribution_1=false;
	Error_Fill_Sum_for_Normal_Distribution_1=false;
	Error_Fill_Row_Intervals_for_Normal_Distribution_1=false;
	Error_Fill_Row_Frequency_for_Normal_Distribution_1=false;
	Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1=false;
	
	int Previous_Value=0;

	if(!ui.Table_for_Normal_Distribution_1->columnCount() && !ui.Table_for_Normal_Distribution_1->rowCount())	Error_Fill_Table_for_Normal_Distribution_1=true;
	if(!ui.Count_for_Normal_Distribution_1->value())Error_Fill_Count_for_Normal_Distribution_1=true;
	if(ui.Sum_for_Normal_Distribution_1->text()=="" || !ui.Sum_for_Normal_Distribution_1->text().toInt())Error_Fill_Sum_for_Normal_Distribution_1=true;

	for(int j=1;j<ui.Table_for_Normal_Distribution_1->columnCount();j++)
	{
		if(j!=1)Previous_Value=ui.Table_for_Normal_Distribution_1->item(0,j-1)->text().toInt();
		
		if(ui.Table_for_Normal_Distribution_1->item(0,j)->text()!="" /*&& (Previous_Value<ui.Table_for_Normal_Distribution_1->item(0,j)->text().toInt() || !ui.Table_for_Normal_Distribution_1->item(0,j)->text().toInt())*/)
			Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_1++;

		if(ui.Table_for_Normal_Distribution_1->item(1,j)->text()!="")
			Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_1++;

		if(ui.Table_for_Normal_Distribution_1->item(2,j)->text()!="")
			Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_1++;
	}

	if(Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_1==ui.Table_for_Normal_Distribution_1->columnCount()-1) Error_Fill_Row_Intervals_for_Normal_Distribution_1=false;
	else Error_Fill_Row_Intervals_for_Normal_Distribution_1=true;
	if(Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_1==ui.Table_for_Normal_Distribution_1->columnCount()-1) Error_Fill_Row_Frequency_for_Normal_Distribution_1=false;
	else Error_Fill_Row_Frequency_for_Normal_Distribution_1=true;
	if(Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_1==ui.Table_for_Normal_Distribution_1->columnCount()-1) Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1=false;
	else Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1=true;
//=========================================================================//
//========= Проверка данных для второй генеральной совокупности ===========//
//=========================================================================//
	int Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_2=0;
	int Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_2=0;
	int Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_2=0;

	Error_Fill_Table_for_Normal_Distribution_2=false;
	Error_Fill_Count_for_Normal_Distribution_2=false;
	Error_Fill_Sum_for_Normal_Distribution_2=false;
	Error_Fill_Row_Intervals_for_Normal_Distribution_2=false;
	Error_Fill_Row_Frequency_for_Normal_Distribution_2=false;
	Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2=false;
	
	Previous_Value=0;

	if(!ui.Table_for_Normal_Distribution_2->columnCount() && !ui.Table_for_Normal_Distribution_2->rowCount())	Error_Fill_Table_for_Normal_Distribution_2=true;
	if(!ui.Count_for_Normal_Distribution_2->value())Error_Fill_Count_for_Normal_Distribution_2=true;
	if(ui.Sum_for_Normal_Distribution_2->text()=="" || !ui.Sum_for_Normal_Distribution_2->text().toInt())Error_Fill_Sum_for_Normal_Distribution_2=true;

	for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)
	{
		if(j!=1)Previous_Value=ui.Table_for_Normal_Distribution_2->item(0,j-1)->text().toInt();
		
		if(ui.Table_for_Normal_Distribution_2->item(0,j)->text()!="" /*&& (Previous_Value<ui.Table_for_Normal_Distribution_2->item(0,j)->text().toInt() || !ui.Table_for_Normal_Distribution_2->item(0,j)->text().toInt())*/)
			Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_2++;

		if(ui.Table_for_Normal_Distribution_2->item(1,j)->text()!="")
			Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_2++;

		if(ui.Table_for_Normal_Distribution_2->item(2,j)->text()!="")
			Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_2++;
	}

	if(Count_of_Filled_Slots_in_First_Row_for_Normal_Distribution_2==ui.Table_for_Normal_Distribution_2->columnCount()-1) Error_Fill_Row_Intervals_for_Normal_Distribution_2=false;
	else Error_Fill_Row_Intervals_for_Normal_Distribution_2=true;
	if(Count_of_Filled_Slots_in_Second_Row_for_Normal_Distribution_2==ui.Table_for_Normal_Distribution_2->columnCount()-1) Error_Fill_Row_Frequency_for_Normal_Distribution_2=false;
	else Error_Fill_Row_Frequency_for_Normal_Distribution_2=true;
	if(Count_of_Filled_Slots_in_Third_Row_for_Normal_Distribution_2==ui.Table_for_Normal_Distribution_2->columnCount()-1) Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2=false;
	else Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2=true;
}

void TerVer_Lab1::Formation_Table_of_Characteristics_for_Two_Normal_Distributions()
{
	QTableWidgetItem *item;
	Error_was_Found=false;

	if(!Table_is_Full_for_Normal_Distribution_1 || !Table_is_Full_for_Normal_Distribution_2)
	{
		if(!Table_is_Full_for_Normal_Distribution_1 && !Table_is_Full_for_Normal_Distribution_2)
		{
			if(Error_Fill_Table_for_Normal_Distribution_1 && Error_Fill_Row_Intervals_for_Normal_Distribution_1 && Error_Fill_Row_Frequency_for_Normal_Distribution_1 && Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1 && Error_Fill_Table_for_Normal_Distribution_2 && Error_Fill_Row_Intervals_for_Normal_Distribution_2 && Error_Fill_Row_Frequency_for_Normal_Distribution_2 && Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2)
			{
				QMessageBox::warning(0, "Ошибка при считывании данных", "Не было найдено никаких данных.");
				Table_is_Full_for_Normal_Distribution_1=false;
				Table_is_Full_for_Normal_Distribution_2=false;
				Error_was_Found=true;
			}
		}

		if(!Table_is_Full_for_Normal_Distribution_1)
		{
			if(!Error_Fill_Table_for_Normal_Distribution_1 || !Error_Fill_Row_Intervals_for_Normal_Distribution_1 || !Error_Fill_Row_Frequency_for_Normal_Distribution_1 || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1)
			{
				if(!Error_Fill_Row_Intervals_for_Normal_Distribution_1 && (!Error_Fill_Row_Frequency_for_Normal_Distribution_1 || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1))
				{
					if(ui.Count_for_Normal_Distribution_1->value()!=ui.Table_for_Normal_Distribution_1->columnCount()-1)
					{
						if(!Error_was_Found)
						{
							QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" для первого распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
							Error_was_Found=true;
						}
						ui.Count_for_Normal_Distribution_1->setValue(ui.Table_for_Normal_Distribution_1->columnCount()-1);
					}
//=========================================================================//
//========== Заполнение недостающих строк в таблице характеристик =========//
//=========================================================================//
					if(Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1)
					{
						int Sum_for_Normal_Distribution_1=0;
						for(int x=1;x<ui.Table_for_Normal_Distribution_1->columnCount();x++)
							Sum_for_Normal_Distribution_1+=ui.Table_for_Normal_Distribution_1->item(1,x)->text().toInt();

						ui.Sum_for_Normal_Distribution_1->setText(QString::number(Sum_for_Normal_Distribution_1));

						for(int x=1;x<ui.Table_for_Normal_Distribution_1->columnCount();x++)
						{
							item = new  QTableWidgetItem(QString::number((ui.Table_for_Normal_Distribution_1->item(1,x)->text().toFloat()/ui.Sum_for_Normal_Distribution_1->text().toFloat()), 'g', 2));
							item->setTextAlignment(Qt::AlignCenter);
							ui.Table_for_Normal_Distribution_1->setItem(2,x, item);
						}
						Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1=false;
					}

					if(Error_Fill_Row_Frequency_for_Normal_Distribution_1)
					{
						if(!Error_Fill_Sum_for_Normal_Distribution_1)
						{
							for(int x=1;x<ui.Table_for_Normal_Distribution_1->columnCount();x++)
							{
								item = new  QTableWidgetItem(QString::number((int)((ui.Table_for_Normal_Distribution_1->item(2,x)->text().toFloat()*ui.Sum_for_Normal_Distribution_1->text().toFloat())+0.5), 'g', 1));//0.5 - поправочный коэффициент, для округления в большую сторону
								item->setTextAlignment(Qt::AlignCenter);
								ui.Table_for_Normal_Distribution_1->setItem(1,x, item);
							}
						}
						else 
						{
							if(!Error_was_Found)
							{
								QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Сумма частот (N)\" для первого распределения было заполнено неверно");
								Error_was_Found=true;
							}
							Error_Fill_Row_Frequency_for_Normal_Distribution_1=true;
						}
						Error_Fill_Row_Frequency_for_Normal_Distribution_1=false;
					}

					if(!Error_Fill_Row_Intervals_for_Normal_Distribution_1 && !Error_Fill_Row_Frequency_for_Normal_Distribution_1 && !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1)
						Table_is_Full_for_Normal_Distribution_1=true;
				}
				else
				{
					if(!Error_was_Found)
					{
						QMessageBox::warning(0, "Ошибка при считывании данных", "В таблице для первого распределения содержатся неверные данные.\n             Пожалуйста, исправьте ошибки и попробуйте снова.");
						Error_was_Found=true;
					}
					Table_is_Full_for_Normal_Distribution_1=false;
				}
			}
			else 
			{
				if(!Error_was_Found)
				{
					QMessageBox::warning(0, "Ошибка при считывании данных", "Для первого распределения не было найдено никаких данных.");
					Error_was_Found=true;
				}
				Table_is_Full_for_Normal_Distribution_1=false;
			}
		}

		if(!Table_is_Full_for_Normal_Distribution_2)
		{
			if(!Error_Fill_Table_for_Normal_Distribution_2 || !Error_Fill_Row_Intervals_for_Normal_Distribution_2 || !Error_Fill_Row_Frequency_for_Normal_Distribution_2 || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2)
			{
				if(!Error_Fill_Row_Intervals_for_Normal_Distribution_2 && (!Error_Fill_Row_Frequency_for_Normal_Distribution_2 || !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2))
				{
					if(ui.Count_for_Normal_Distribution_2->value()!=ui.Table_for_Normal_Distribution_2->columnCount()-1)
					{
						if(!Error_was_Found)
						{
							QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" для второго распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
							Error_was_Found=true;
						}
						ui.Count_for_Normal_Distribution_2->setValue(ui.Table_for_Normal_Distribution_2->columnCount()-1);
					}
//=========================================================================//
//========== Заполнение недостающих строк в таблице характеристик =========//
//=========================================================================//
					if(Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2)
					{
						int Sum_for_Normal_Distribution_2=0;
						for(int x=1;x<ui.Table_for_Normal_Distribution_2->columnCount();x++)
							Sum_for_Normal_Distribution_2+=ui.Table_for_Normal_Distribution_2->item(1,x)->text().toInt();

						ui.Sum_for_Normal_Distribution_2->setText(QString::number(Sum_for_Normal_Distribution_2));

						for(int x=1;x<ui.Table_for_Normal_Distribution_2->columnCount();x++)
						{
							item = new  QTableWidgetItem(QString::number((ui.Table_for_Normal_Distribution_2->item(1,x)->text().toFloat()/ui.Sum_for_Normal_Distribution_2->text().toFloat()), 'g', 2));
							item->setTextAlignment(Qt::AlignCenter);
							ui.Table_for_Normal_Distribution_2->setItem(2,x, item);
						}
						Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2=false;
					}

					if(Error_Fill_Row_Frequency_for_Normal_Distribution_2)
					{
						if(!Error_Fill_Sum_for_Normal_Distribution_2)
						{
							for(int x=1;x<ui.Table_for_Normal_Distribution_2->columnCount();x++)
							{
								item = new  QTableWidgetItem(QString::number((int)((ui.Table_for_Normal_Distribution_2->item(2,x)->text().toFloat()*ui.Sum_for_Normal_Distribution_2->text().toFloat())+0.5), 'g', 1));//0.5 - поправочный коэффициент, для округления в большую сторону
								item->setTextAlignment(Qt::AlignCenter);
								ui.Table_for_Normal_Distribution_2->setItem(1,x, item);
							}
						}
						else 
						{
							if(!Error_was_Found)
							{
								QMessageBox::warning(0, "Ошибка ввода данных", "Поле \"Сумма частот (N)\" для второго распределения было заполнено неверно");
								Error_was_Found=true;
							}
							Error_Fill_Row_Frequency_for_Normal_Distribution_2=true;
						}
						Error_Fill_Row_Frequency_for_Normal_Distribution_2=false;
					}

					if(!Error_Fill_Row_Intervals_for_Normal_Distribution_2 && !Error_Fill_Row_Frequency_for_Normal_Distribution_2 && !Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2)
						Table_is_Full_for_Normal_Distribution_2=true;
				}
				else
				{
					if(!Error_was_Found)
					{
						QMessageBox::warning(0, "Ошибка при считывании данных", "В таблице для второго распределения содержатся неверные данные.\n             Пожалуйста, исправьте ошибки и попробуйте снова.");
						Error_was_Found=true;
					}
					Table_is_Full_for_Normal_Distribution_2=false;
				}
			}
			else 
			{
				if(!Error_was_Found)
				{
					QMessageBox::warning(0, "Ошибка при считывании данных", "Для второго распределения не было найдено никаких данных.");
					Error_was_Found=true;
				}
				Table_is_Full_for_Normal_Distribution_2=false;
			}
		}
	}
}

void TerVer_Lab1::Comparison_Two_Variances_for_Normal_Distributions()
{
	Error_Checking_for_Two_Normal_Distributions();
	Formation_Table_of_Characteristics_for_Two_Normal_Distributions();

	if(Table_is_Full_for_Normal_Distribution_1 && Table_is_Full_for_Normal_Distribution_2)
	{
		Edit_Sum_and_Count_Two_Variances_for_Normal_Distributions();
		Calculate_Two_Variances_for_Normal_Distributions();
				
		float Fk=0,Fn=0;
		int k1=0,k2=0;
		int Significance_Level=0;
		float K_Matrix[2][17][12]={
			{{4052,4999,5403,5625,5764,5889,5928,5981,6022,6056,6082,6106},
			{98.49,99.01,99.17,99.25,99.3,99.33,99.34,99.36,99.38,99.4,99.41,99.42},
			{34.12,30.81,29.46,28.17,28.24,27.91,27.67,27.49,27.34,27.23,27.13,27.05},
			{21.2,18,16.69,15.98,15.52,15.21,14.98,14.8,14.66,14.54,14.45,24.37},
			{16.26,13.27,12.06,11.39,10.97,10.67,10.45,10.27,10.15,10.05,9.96,9.89},
			{13.74,10.92,9.78,9.15,8.75,8.47,8.26,8.1,7.98,7.87,7.79,7.72},
			{12.25,0.55,8.45,7.85,7.46,7.19,7,6.84,6.71,6.62,6.54,6.47},
			{11.26,8.65,7.59,7.01,6.63,6.37,6.19,6.03,5.91,5.82,5.74,5.67},
			{10.56,8.02,6.99,6.42,6.06,5.8,5.62,5.47,5.35,5.26,5.18,5.11},
			{10.04,7.56,6.55,5.99,5.64,5.39,5.21,5.06,4.95,4.85,4.78,4.71},
			{9.86,7.2,6.22,5.67,5.32,5.07,4.88,4.74,4.63,4.54,4.46,4.4},
			{9.33,6.93,5.95,5.41,5.06,4.82,4.65,4.5,4.39,4.3,4.22,4.16},
			{9.07,6.7,5.74,5.2,4.86,4.62,4.44,4.3,4.19,4.1,4.02,3.96},
			{8.86,6.51,5.56,5.03,4.69,4.46,4.28,4.14,4.03,3.94,3.86,3.8},
			{8.68,6.36,5.42,4.89,4.56,4.32,4.14,4,3.89,3.8,3.73,3.69},
			{8.53,6.23,5.29,4.77,4.44,4.2,4.03,3.89,3.78,3.69,3.61,3.55},
			{8.4,6.11,5.18,4.67,4.34,4.1,3.93,3.79,3.68,3.59,3.52,3.45}},

			{{161,200,216,225,230,234,237,239,241,242,243,244},
			{18.51,19,19.16,19.25,19.3,19.33,19.36,19.37,19.38,19.39,19.4,19.41},
			{10.13,9.55,9.28,9.21,9.01,8.94,8.88,8.84,8.81,8.78,8.76,8.74},
			{7.71,6.94,6.59,6.39,6.26,6.16,6.09,6.04,6,5.96,5.93,5.91},
			{6.61,5.79,5.41,5.19,5.05,4.95,4.88,4.82,4.78,4.74,4.7,4.68},
			{5.99,5.14,4.76,4.53,4.39,4.28,4.21,4.15,4.1,4.06,4.03,4},
			{5.59,4.74,4.35,4.12,3.97,3.87,3.79,3.73,3.68,3.63,3.6,3.57},
			{5.32,4.46,4.07,3.84,3.69,3.58,3.5,3.44,3.39,3.34,3.31,3.28},
			{5.12,4.26,3.86,3.63,3.48,3.37,3.29,3.23,3.18,3.13,3.1,3.07},
			{4.96,4.1,3.71,3.48,3.33,3.22,3.14,3.07,3.02,2.97,2.94,2.91},
			{4.84,3.98,3.59,3.36,3.2,3.09,3.01,2.95,2.9,2.86,2.82,2.79},
			{4.75,3.88,3.49,3.26,3.11,3,2.92,2.85,2.8,2.76,2.72,2.69},
			{4.67,3.8,3.41,3.18,3.02,2.92,2.84,2.77,2.72,2.67,2.63,2.6},
			{4.6,3.74,3.34,3.11,2.96,2.85,2.77,2.7,2.65,2.6,2.56,2.53},
			{4.54,3.68,3.29,3.06,2.9,2.79,2.7,2.64,2.59,2.55,2.51,2.48},
			{4.49,3.63,3.24,3.01,2.85,2.74,2.66,2.59,2.54,2.49,2.45,2.42},
			{4.45,3.59,3.2,2.96,2.81,2.7,2.62,2.55,2.5,2.45,2.41,2.38}}};

		if(ui.D_for_Normal_Distribution_1->text().toFloat()<ui.D_for_Normal_Distribution_2->text().toFloat())
			Fn=(ui.D_for_Normal_Distribution_2->text().toFloat()/ui.D_for_Normal_Distribution_1->text().toFloat());
		else Fn=(ui.D_for_Normal_Distribution_1->text().toFloat()/ui.D_for_Normal_Distribution_2->text().toFloat());

		if(ui.Significance_Level_1_Page_3_Point_1->isChecked())Significance_Level=0;
		if(ui.Significance_Level_2_Page_3_Point_1->isChecked())Significance_Level=1;

		if(ui.Competing_Hypothesis_1->isChecked())
		{
			if(ui.D_for_Normal_Distribution_1->text().toFloat()<ui.D_for_Normal_Distribution_2->text().toFloat())
			{
				//k1=ui.Count_for_Normal_Distribution_2->value()-1;
				//k2=ui.Count_for_Normal_Distribution_1->value()-1;
				for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++)k2+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();
				for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)k1+=ui.Table_for_Normal_Distribution_2->item(1,j)->text().toInt();

			}
			else 
			{
				//k1=ui.Count_for_Normal_Distribution_1->value()-1;
				//k2=ui.Count_for_Normal_Distribution_2->value()-1;
				for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++)k1+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();
				for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)k2+=ui.Table_for_Normal_Distribution_2->item(1,j)->text().toInt();
			}
		}
		if(ui.Competing_Hypothesis_2->isChecked())
		{
			if(ui.D_for_Normal_Distribution_1->text().toFloat()<ui.D_for_Normal_Distribution_2->text().toFloat())
			{
				//k1=ui.Count_for_Normal_Distribution_2->value()-1;
				//k2=ui.Count_for_Normal_Distribution_1->value()-1;
				for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++)k2+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();
				for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)k1+=ui.Table_for_Normal_Distribution_2->item(1,j)->text().toInt();
			}
			else 
			{
				//k1=ui.Count_for_Normal_Distribution_1->value()-1;
				//k2=ui.Count_for_Normal_Distribution_2->value()-1;
				for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++)k1+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();
				for(int j=1;j<ui.Table_for_Normal_Distribution_2->columnCount();j++)k2+=ui.Table_for_Normal_Distribution_2->item(1,j)->text().toInt();
			}
		}

		k1--;
		k2--;
		(k1<17)?k1:k1=16;
		(k2<12)?k2:k2=11;

		Fk=K_Matrix[Significance_Level][k2-1][k1-1];

		ui.label_166->setText((ui.D_for_Normal_Distribution_1->text().toFloat()<ui.D_for_Normal_Distribution_2->text().toFloat())?ui.D_for_Normal_Distribution_2->text():ui.D_for_Normal_Distribution_1->text());//QString::number()
		ui.label_165->setText((ui.D_for_Normal_Distribution_1->text().toFloat()<ui.D_for_Normal_Distribution_2->text().toFloat())?ui.D_for_Normal_Distribution_1->text():ui.D_for_Normal_Distribution_2->text());//QString::number()
		ui.label_156->setText(QString::number(Fn,'g',4)+";");
		if(!Significance_Level) ui.label_162->setText("(0.01,"+QString::number(k1)+","+QString::number(k2)+")");
		else ui.label_162->setText("(0.05,"+QString::number(k1)+","+QString::number(k2)+")");
		ui.label_187->setText("F          = F            = "+QString::number(Fk,'g',4)+";");
		ui.label_149->setText("F       = "+QString::number(Fn,'g',4));
		ui.label_144->setText("F          = "+QString::number(Fk,'g',4));
		ui.label_145->setText((Fn>Fk)?">":"<");
		
		if(Fn<Fk)ui.Result_Comparison_Two_Variances_for_Normal_Distributions->setText("Нет оснований отвергнуть нулевую гипотезу");//ui.Result_2->setText("Нет оснований отвергнуть гипотезу о равенстве дисперсий двух нормальных распределений");
		else ui.Result_Comparison_Two_Variances_for_Normal_Distributions->setText("Нулевая гипотеза отвергается");//else ui.Result_2->setText("Нулевая гипотеза о равенстве дисперсий двух нормальных распределений отвергается");
	}
}

void TerVer_Lab1::Clear_Data_Table_for_Normal_Distributions_1()
{
	Table_is_Full_for_Normal_Distribution_1=false;

	ui.Table_for_Normal_Distribution_1->setRowCount(0);
	ui.Table_for_Normal_Distribution_1->setColumnCount(0);

	ui.Sum_for_Normal_Distribution_1->clear();
	ui.Count_for_Normal_Distribution_1->setValue(0);
}

void TerVer_Lab1::Clear_Data_Table_for_Normal_Distributions_2()
{
	Table_is_Full_for_Normal_Distribution_2=false;

	ui.Table_for_Normal_Distribution_2->setRowCount(0);
	ui.Table_for_Normal_Distribution_2->setColumnCount(0);

	ui.Sum_for_Normal_Distribution_2->clear();
	ui.Count_for_Normal_Distribution_2->setValue(0);
}

void TerVer_Lab1::Clear_Data_Two_Variances_for_Normal_Distributions()
{
	ui.Significance_Level_1_Page_3_Point_1->setChecked(true);
	ui.Competing_Hypothesis_1->setChecked(true);
	ui.D_for_Normal_Distribution_1->clear();
	ui.D_for_Normal_Distribution_2->clear();

	ui.label_166->setText("  D (X)");
	ui.label_165->setText("  D (Y)");
	ui.label_156->setText("= ... ;");
	ui.label_162->setText("критич.");
	ui.label_187->setText("F          = F             = ... ;");
	ui.label_149->setText("F       =     ...");
	ui.label_144->setText("F          =   ...");
	ui.label_145->setText("<");
}

void TerVer_Lab1::Calculate_Two_Variances_for_Normal_Distributions()
{
	float Average_X1=0;
	float Average_X2=0;
	float Temp_Sum=0;

	//for(int x=1;x<=ui.K_Page_3_of_Normal_Distribution_1->value();x++)
	Temp_Sum=0;
	for(int x=1;x<ui.Table_for_Normal_Distribution_1->columnCount();x++)
	{
		Temp_Sum+=ui.Table_for_Normal_Distribution_1->item(0,x)->text().toFloat()*ui.Table_for_Normal_Distribution_1->item(1,x)->text().toFloat();
	}
	Average_X1=Temp_Sum/ui.Sum_for_Normal_Distribution_1->text().toFloat();

	Temp_Sum=0;
	for(int x=1;x<ui.Table_for_Normal_Distribution_1->columnCount();x++)
	{
		Temp_Sum+=pow((ui.Table_for_Normal_Distribution_1->item(0,x)->text().toFloat()-Average_X1),2)*ui.Table_for_Normal_Distribution_1->item(1,x)->text().toFloat();
	}
	ui.D_for_Normal_Distribution_1->setText(QString::number((Temp_Sum/ui.Sum_for_Normal_Distribution_1->text().toFloat()), 'g', 4));//ui.D_1->setText(QString::number((ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()<30)?(1/(ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()-1)*sum):(sum/ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()), 'g', 4));

	//for(int x=1;x<=ui.K_Page_3_of_Normal_Distribution_1->value();x++)
	Temp_Sum=0;
	for(int x=1;x<ui.Table_for_Normal_Distribution_2->columnCount();x++)
	{
		Temp_Sum+=ui.Table_for_Normal_Distribution_2->item(0,x)->text().toFloat()*ui.Table_for_Normal_Distribution_2->item(1,x)->text().toFloat();
	}
	Average_X1=Temp_Sum/ui.Sum_for_Normal_Distribution_2->text().toFloat();

	Temp_Sum=0;
	for(int x=1;x<ui.Table_for_Normal_Distribution_2->columnCount();x++)
	{
		Temp_Sum+=pow((ui.Table_for_Normal_Distribution_2->item(0,x)->text().toFloat()-Average_X1),2)*ui.Table_for_Normal_Distribution_2->item(1,x)->text().toFloat();
	}
	ui.D_for_Normal_Distribution_2->setText(QString::number((Temp_Sum/ui.Sum_for_Normal_Distribution_2->text().toFloat()), 'g', 4));//ui.D_1->setText(QString::number((ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()<30)?(1/(ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()-1)*sum):(sum/ui.Sum_Page_3_of_Normal_Distribution_1->text().toFloat()), 'g', 4));
}

void TerVer_Lab1::Edit_Sum_and_Count_Two_Variances_for_Normal_Distributions()
{
	if(ui.Count_for_Normal_Distribution_1->value()!=ui.Table_for_Normal_Distribution_1->columnCount()-1)
	{
		QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" для первого распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
		ui.Count_for_Normal_Distribution_1->setValue(ui.Table_for_Normal_Distribution_1->columnCount()-1);
	}
	else
	{
		int Sum_for_Normal_Distribution_1=0;

		for(int i=1;i<ui.Table_for_Normal_Distribution_1->columnCount();i++) 
			Sum_for_Normal_Distribution_1+=ui.Table_for_Normal_Distribution_1->item(1,i)->text().toInt();

		if(ui.Sum_for_Normal_Distribution_1->text().toInt()!=Sum_for_Normal_Distribution_1)
		{
			QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество повторений (n)\" для первого распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее данным таблицы.");
			ui.Sum_for_Normal_Distribution_1->setText(QString::number(Sum_for_Normal_Distribution_1));		
		}
	}

	if(ui.Count_for_Normal_Distribution_2->value()!=ui.Table_for_Normal_Distribution_2->columnCount()-1)
	{
		QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество интервалов\" для второго распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее таблице.");
		ui.Count_for_Normal_Distribution_2->setValue(ui.Table_for_Normal_Distribution_2->columnCount()-1);
	}
	else
	{
		int Sum_for_Normal_Distribution_2=0;

		for(int i=1;i<ui.Table_for_Normal_Distribution_2->columnCount();i++) 
			Sum_for_Normal_Distribution_2+=ui.Table_for_Normal_Distribution_2->item(1,i)->text().toInt();

		if(ui.Sum_for_Normal_Distribution_2->text().toInt()!=Sum_for_Normal_Distribution_2)
		{
			QMessageBox::warning(0, "Ошибка ввода данных", "    Значение поля \"Количество повторений (n)\" для второго распределения не соответствует\n                                   размерности таблицы.\nПрограмма заменила его на значение соответствующее данным таблицы.");
			ui.Sum_for_Normal_Distribution_2->setText(QString::number(Sum_for_Normal_Distribution_2));		
		}
	}
}

void TerVer_Lab1::Show_Data_Table()
{
	if(Count_Elements_in_Array_for_Normal_Distribution)
	{
		Data_Table *mm = new Data_Table(Array_Data_for_Normal_Distribution,Count_Elements_in_Array_for_Normal_Distribution,Max_Count_Elements_in_String_in_Data_Table,0);
		mm->show();
	}
}

void TerVer_Lab1::Show_Help()
{
	int Current_Page=ui.stackedWidget->currentIndex();

	Help *mm = new Help(Current_Page,0);
	mm->show();
}

void TerVer_Lab1::Show_Theoretical_Material()
{
	int Current_Page=ui.stackedWidget->currentIndex();

	Theoretical_Material *mm = new Theoretical_Material(Current_Page,0);
	mm->show();
}