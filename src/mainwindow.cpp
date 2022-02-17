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
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->findbutton, SIGNAL(clicked()), this, SLOT(findText()));
    connect(ui->regexpEdit, SIGNAL(textChanged(const QString&)), this, SLOT(validRegExp()));
    connect(ui->m_patternSyntax, SIGNAL(currentIndexChanged(int)), this, SLOT(validRegExp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch(e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::findText()
{
    QString dest= ui->m_dstEdit->text();
    QRegularExpression exp(ui->regexpEdit->text());
    if(ui->m_minimal->isChecked())
        exp.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    // exp.setMinimal(ui->m_minimal->isChecked());
    if(!ui->m_caseSensitive->isChecked())
        exp.setPatternOptions(QRegularExpression::CaseInsensitiveOption);

    // exp.setPatternSyntax((QRegExp::PatternSyntax)ui->m_patternSyntax->currentIndex());

    QStringList elements;
    QString separator= "\n";
    if(ui->m_eachline->isChecked())
    {
        elements << ui->before->document()->toPlainText().split("\n");
        separator= ", ";
    }
    else
        elements << ui->before->document()->toPlainText();

    ui->after->clear();
    if(ui->m_exactMatch->isChecked())
    {
        for(auto line : elements)
        {
            auto match= exp.match(line);
            ui->after->insertPlainText(match.hasMatch() ? tr("true") : tr("false"));
            ui->after->insertPlainText("\n");
        }
    }
    else
    {

        for(auto line : elements)
        {
            bool endline= false;
            if(!ui->m_skipEmpty->isChecked())
                endline= true;
            int pos= 0;
            QStringList list;
            if(ui->m_showAllMatch->isChecked())
            {
                qDebug() << pos;
                auto it= exp.globalMatch(line);
                while(it.hasNext())
                {
                    auto match= it.next();
                    list << match.captured(1);
                }

                qDebug() << ".end while loop" << list;
                for(auto text : list)
                {
                    ui->after->insertPlainText(text);
                    ui->after->insertPlainText("\n");
                }
            }
        }
    }
}
void MainWindow::validRegExp()
{
    QRegularExpression exp(ui->regexpEdit->text());

    if((ui->regexpEdit->text().isEmpty()) || (!exp.isValid()))
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
