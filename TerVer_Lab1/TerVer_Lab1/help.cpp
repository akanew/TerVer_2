#include "help.h"

Help::Help(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Help::Help(int Type_Displayed_Page,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.Previous_Page, SIGNAL(clicked()), this, SLOT(Previous_Page()));
	connect(ui.Next_Page, SIGNAL(clicked()), this, SLOT(Next_Page()));

	Current_Page=0;
	Choice_Page_to_Show(Current_Page);
}

Help::~Help(){}

void Help::Choice_Page_to_Show(int Page_Number)
{
	if(Page_Number==1)
	{
		QPixmap image("image6.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==2)
	{
		QPixmap image("image7.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==3)
	{
		QPixmap image("image8.png");
		ui.label->setPixmap(image);
	}
	if(Page_Number==0)
	{
		QPixmap image("image5.png");
		ui.label->setPixmap(image);
	}
}

void Help::Next_Page()
{
	int Next_Page=Current_Page+1;

	if(Next_Page<4)Current_Page=Next_Page;
	else Current_Page=0;

	Choice_Page_to_Show(Current_Page);
}

void Help::Previous_Page()
{
	int Previous_Page=Current_Page-1;

	if(Previous_Page>=0) Current_Page=Previous_Page;
	else Current_Page=3;

	Choice_Page_to_Show(Current_Page);
}
