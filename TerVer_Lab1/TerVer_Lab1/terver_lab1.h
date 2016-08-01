#ifndef TERVER_LAB1_H
#define TERVER_LAB1_H

#include <QtGui/QMainWindow>
#include "ui_terver_lab1.h"
#include "QFileDialog.h"
#include "QMessageBox.h"
#include "QTextStream.h"
#include <QTextCodec>
#include <QGraphicsItem>
#include <QPalette>
#include "math.h"
#include "data_table.h"
#include "help.h"
#include "theoretical_material.h"

class TerVer_Lab1 : public QMainWindow
{
	Q_OBJECT

public:
	TerVer_Lab1(QWidget *parent = 0, Qt::WFlags flags = 0);
	~TerVer_Lab1();

	float h;
	float x0;
	float* Array_Data_for_Normal_Distribution;
	int Max_Count_Elements_in_String_in_Data_Table;
	float* Array_Data_for_Binomial_Distribution;
	QString File_Name;
	bool Table_is_Full_for_Normal_Distribution;
	bool Negative_Numbers_in_Table_for_Normal_Distribution;
	int Count_Elements_in_Array_for_Normal_Distribution;
	float coefficient_x;
	float coefficient_y;
	float Matrix_Table_Laplace[2][250];
	float Matrix_Table_Pearson[30][13];
	bool Error_Fill_Table_for_Normal_Distribution;
	bool Error_Fill_Count_for_Normal_Distribution;
	bool Error_Fill_Sum_for_Normal_Distribution;
	bool Error_Fill_Row_Intervals_for_Normal_Distribution;
	bool Error_Fill_Row_Frequency_for_Normal_Distribution;
	bool Error_Fill_Row_Relative_Frequency_for_Normal_Distribution;
	bool Table_is_Full_to_Hands_for_Normal_Distribution;
	///////////////////////////////////////////////////
	bool Table_is_Full_for_Binomial_Distribution;
	bool Negative_Numbers_in_Table_for_Binomial_Distribution;
	int Count_Elements_in_Array_for_Binomial_Distribution;
	bool Table_is_Full_to_Hands_for_Binomial_Distribution;
	bool Error_Fill_Table_for_Binomial_Distribution;
	bool Error_Fill_Count_for_Binomial_Distribution;
	bool Error_Fill_Sum_for_Binomial_Distribution;
	bool Error_Fill_Row_Intervals_for_Binomial_Distribution;
	bool Error_Fill_Row_Frequency_for_Binomial_Distribution;
	bool Error_Fill_Row_Relative_Frequency_for_Binomial_Distribution;
	int Number_Degrees_Freedom;
	/////////////////////////////////////////////////////
	int Count_Elements_in_Array_for_Normal_Distribution_1;
	bool Negative_Numbers_in_Table_for_Normal_Distribution_1;
	bool Table_is_Full_for_Normal_Distribution_1;
	float* Array_Data_for_Normal_Distribution_1;

	int Count_Elements_in_Array_for_Normal_Distribution_2;
	bool Negative_Numbers_in_Table_for_Normal_Distribution_2;
	bool Table_is_Full_for_Normal_Distribution_2;
	float* Array_Data_for_Normal_Distribution_2;

	bool Error_Fill_Table_for_Normal_Distribution_1;
	bool Error_Fill_Count_for_Normal_Distribution_1;
	bool Error_Fill_Sum_for_Normal_Distribution_1;
	bool Error_Fill_Row_Intervals_for_Normal_Distribution_1;
	bool Error_Fill_Row_Frequency_for_Normal_Distribution_1;
	bool Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_1;

	bool Error_Fill_Table_for_Normal_Distribution_2;
	bool Error_Fill_Count_for_Normal_Distribution_2;
	bool Error_Fill_Sum_for_Normal_Distribution_2;
	bool Error_Fill_Row_Intervals_for_Normal_Distribution_2;
	bool Error_Fill_Row_Frequency_for_Normal_Distribution_2;
	bool Error_Fill_Row_Relative_Frequency_for_Normal_Distribution_2;
	bool Error_was_Found;

private:
	Ui::TerVer_Lab1Class ui;

private slots:
//=========================================================================//
//=============================== Общие слоты =============================//
//=========================================================================//
	// Управляющие слоты
	void Load_Data_from_File_for_Normal_Distribution();
	void Load_Data_from_File_for_Binomial_Distribution();
	// Смена страниц
	void Change_Stack_Main_Page_Previous();
	void Change_Stack_Main_Page_Next();
	void Change_Stack_Page_1();
	// Работа с файлами
	int Count_Elements_in_File();
	void Load_Data_from_File(float*,int);
	// Получение таблиц Пирсона и Лапласа
	void Get_Laplace_Table(float *Matrix_Table_Laplace);
	void Get_Pearson_Table(float *Matrix_Table_Pearson);
//=========================================================================//
//=============== Нормальное распределение (интервальное) =================//
//=========================================================================//
	// Основные таблицы
	void Create_Table_for_Normal_Distribution();
	void Formation_Table_of_Characteristics_for_Normal_Distribution();
	void Build_Table_for_Normal_Distribution();
	void Create_Tables_Page_2_for_Normal_Distribution();
	void Copy_Data_to_Page_2_for_Normal_Distribution();
	// Очистка данных
	void Clear_Data_for_Normal_Distribution();
	void Clear_Data_Table_for_Normal_Distribution();
	void Clear_Data_Page_2_for_Normal_Distribution();
	// Первичная обработка данных
	void Calculate_Action_for_Normal_Distribution();
	void Error_Checking_for_Normal_Distribution();
	void Calculation_of_Averages_for_Normal_Distribution();
	void Drawing_Task_6_for_Normal_Distribution();
	void Drawing_Graphics_for_Normal_Distribution();
	// Проверка сатистической гипотезы
	void Testing_Hypothesis_Normal_Distribution();
	void Definition_Result_Testing_Hypothesis_Normal_Distribution();
	void Drawing_Probabilities_for_Normal_Distribution();
	// Расчётные таблицы
	void Fill_Table_Point_Estimates_for_Normal_Distribution();
	void Fill_Table_Alternative_for_Normal_Distribution();
	void Definition_of_Point_Estimates_for_Normal_Distribution();
//=========================================================================//
	void Testing_Hypothesis_Binomial_Distribution();
	void Create_Table_for_Binomial_Distribution();
	void Build_Table_for_Binomial_Distribution();
	void Clear_Data_for_Binomial_Distribution();
	void Clear_Data_Table_for_Binomial_Distribution();
	void Calculate_Input_Data_for_Binomial_Distribution();
	void Error_Checking_for_Binomial_Distribution();
	void Formation_Table_of_Characteristics_for_Binomial_Distribution();
	void Drawing_Probabilities_for_Binomial_Distribution();
	bool Calculating_Probability();
	int Factorial(int number);
	void Definition_of_Point_Estimates_for_Binomial_Distribution();
	void Definition_Result_Testing_Hypothesis_Binomial_Distribution();
//=========================================================================//
	void Build_Table_for_Normal_Distribution_1();
	void Create_Table_for_Normal_Distribution_1();
	void Load_Data_from_File_for_Normal_Distribution_1();
	void Calculate_Input_Data_for_Normal_Distribution_1();
	void Build_Table_for_Normal_Distribution_2();
	void Create_Table_for_Normal_Distribution_2();
	void Load_Data_from_File_for_Normal_Distribution_2();
	void Calculate_Input_Data_for_Normal_Distribution_2();
	void Comparison_Two_Variances_for_Normal_Distributions();
	void Error_Checking_for_Two_Normal_Distributions();
	void Formation_Table_of_Characteristics_for_Two_Normal_Distributions();
	void Clear_Data_Table_for_Normal_Distributions_1();
	void Clear_Data_Table_for_Normal_Distributions_2();
	void Clear_Data_Two_Variances_for_Normal_Distributions();
	void Calculate_Two_Variances_for_Normal_Distributions();
	void Edit_Sum_and_Count_Two_Variances_for_Normal_Distributions();
	void Show_Data_Table();
	/////////////////////////
	void Show_Help();
	void Show_Theoretical_Material();

signals: 
     void Select_Array_SIGNAL(float*,int);
};

#endif // TERVER_LAB1_H
