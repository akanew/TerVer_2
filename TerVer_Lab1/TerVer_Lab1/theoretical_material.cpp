#include "theoretical_material.h"

Theoretical_Material::Theoretical_Material(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Theoretical_Material::Theoretical_Material(int Type_Displayed_Page,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.Previous_Page, SIGNAL(clicked()), this, SLOT(Previous_Page_Emit()));
	connect(ui.Next_Page, SIGNAL(clicked()), this, SLOT(Next_Page_Emit()));
	connect(this, SIGNAL(Select_SIGNAL(int)), this, SLOT(Choice_Page_to_Show(int)));

	Choice_Page_to_Show(Type_Displayed_Page);
	Current_Page=Type_Displayed_Page;
}

void Theoretical_Material::Previous_Page_Emit()
{	
	int Previous_Page=Current_Page-1;
	if(Previous_Page>=0)
	{
		Current_Page=Previous_Page;
		emit Select_SIGNAL(Previous_Page);
	}
	else
	{
		Current_Page=3;
		emit Select_SIGNAL(3);
	}
}

void Theoretical_Material::Next_Page_Emit()
{
	int Next_Page=Current_Page+1;
	if(Next_Page<4)
	{
		Current_Page=Next_Page;
		emit Select_SIGNAL(Next_Page);
	}
	else
	{
		Current_Page=0;
		emit Select_SIGNAL(0);
	}
}

void Theoretical_Material::Choice_Page_to_Show(int Page_Number)
{
	if(Page_Number==1)
	{
		QPixmap image("image1.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==2)
	{
		QPixmap image("image2.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==3)
	{
		QPixmap image("image3.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==0)
	{
		QPixmap image("image4.png");
		ui.label->setPixmap(image);
	}
}


Theoretical_Material::~Theoretical_Material(){}
