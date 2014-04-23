/***************************************************************************
 *   Copyright (C) 2010 by Renaud Guezennec                                *
 *   http://renaudguezennec.homelinux.org/accueil,3.html                   *
 *                                                                         *
 *   RegExpEditor is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findbutton,SIGNAL(clicked()),this,SLOT(findText()));
    connect(ui->regexpEdit,SIGNAL(textChanged ( const QString &  )),this,SLOT(validRegExp()));
    connect(ui->m_patternSyntax,SIGNAL(currentIndexChanged(int)),this,SLOT(validRegExp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::findText()
{


    QString dest = ui->m_dstEdit->text();
    QRegExp exp(ui->regexpEdit->text());
    exp.setMinimal(ui->m_minimal->isChecked());
    if(ui->m_caseSensitive->isChecked())
        exp.setCaseSensitivity(Qt::CaseSensitive);
    else
        exp.setCaseSensitivity(Qt::CaseInsensitive);

    exp.setPatternSyntax((QRegExp::PatternSyntax)ui->m_patternSyntax->currentIndex());

    QStringList elements;
    QString separator="\n";
    if(ui->m_eachline->isChecked())
    {
       elements<<  ui->before->document()->toPlainText().split("\n");
       separator=", ";
    }
    else
        elements<<ui->before->document()->toPlainText();

    ui->after->clear();
    if(ui->m_exactMatch->isChecked())
    {
        for(int i = 0; i < elements.size(); ++i)
        {
            ui->after->insertPlainText(exp.exactMatch(elements.at(i)) ? tr("true") : tr("false"));
            ui->after->insertPlainText("\n");
        }
    }
    else
    {

        for(int i = 0; i < elements.size(); ++i)
        {
            bool endline =false;
            if(!ui->m_skipEmpty->isChecked())
                endline=true;
            int pos = exp.indexIn(elements.at(i));
            QStringList list = exp.capturedTexts();
            QStringList::iterator it = list.begin();
            dest = ui->m_dstEdit->text();

            ++it;
            qDebug() << list.size() << list;
//            while (it != list.end())
//            {



//                if(dest.isEmpty())
//                {
//                  if(!(*it).isEmpty())
//                  {
//                      endline =true;
//                      ui->after->insertPlainText(*it);
//                  }

//                 if((it != list.end())&&(endline))
//                 {
//                    ui->after->insertPlainText(separator);
//                 }
//                }
//                else
//                {
//                    qDebug() << (*it);
//                    if(!(*it).isEmpty())
//                    {
//                        dest=dest.arg(*it);
//                    }
//                }
//                ++it;

//             }
            QString result;
            for(int j=0;j<list.size();++j)
            {
                QString elem=list[j];
                if(dest.isEmpty())
                {
                    if(!elem.isEmpty())
                    {
                        endline =true;
                        result+=elem;
                        result+=separator;

                        //ui->after->insertPlainText(elem);
                    }
                }
                else
                {
                    if((j>0)&&(!elem.isEmpty()))
                    {
                        dest=dest.arg(elem);
                    }
                }
            }

            if(!result.isEmpty())
            {
                result.chop(separator.size());
                ui->after->insertPlainText(result);
            }
            else
            {


                if((!dest.isEmpty())&&(dest!=ui->m_dstEdit->text()))
                {
                    ui->after->insertPlainText(dest);
                }
                else if((ui->m_displayNotMatched->isChecked()))//&&(list.isEmpty())
                {
                    ui->after->insertPlainText(elements.at(i));
                }
            }

            if(endline)
            {
             ui->after->insertPlainText("\n");
            }
        }
    }
}
void MainWindow::validRegExp()
{
    QRegExp exp(ui->regexpEdit->text());
    exp.setPatternSyntax((QRegExp::PatternSyntax)ui->m_patternSyntax->currentIndex());
    if((ui->regexpEdit->text().isEmpty())||(!exp.isValid()))
    {
        ui->regexpEdit->setStyleSheet("background: #ff0000");
        if(!exp.isValid())
        {
           ui->after->clear();
           ui->after->insertPlainText(exp.errorString());
       }
    }
    else
    {
        ui->after->clear();
        ui->regexpEdit->setStyleSheet("background: #00ff00");
    }
}
