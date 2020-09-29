#include "QBoxLayout"
#include "QPushButton"

#include "settemplatedialog.h"

SetTemplateDialog::SetTemplateDialog(QWidget* parent) : QDialog(parent)
{
    QBoxLayout* layout = new QHBoxLayout;
    m_edit = new QLineEdit;
    layout->addWidget( m_edit );

    QPushButton* okBtn = new QPushButton("ОК");
    connect(okBtn, SIGNAL(clicked()), SLOT(accept()));
    layout->addWidget( okBtn );

    QPushButton* applyBtn = new QPushButton("Apply");
    connect(applyBtn, SIGNAL(clicked()), SIGNAL(applied()));
    layout->addWidget(applyBtn);

    QPushButton* cancelBtn = new QPushButton("Cancel");
    connect(cancelBtn, SIGNAL(clicked()), SLOT(reject()));
    layout->addWidget(cancelBtn);

    setLayout( layout );
}



QStringList SetTemplateDialog::getInput() const{
    QStringList answ;
    answ.push_back(m_edit->text());
    return answ;
}
