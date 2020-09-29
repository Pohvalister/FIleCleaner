#ifndef SETTEMPLATEDIALOG_H
#define SETTEMPLATEDIALOG_H

#include "QDialog"
#include "QLineEdit"


class SetTemplateDialog : public QDialog
{
    Q_OBJECT
public:
    SetTemplateDialog(QWidget* parent = 0);

    QStringList getInput() const;

signals:
    void applied();

private:
    QLineEdit* m_edit;
};

#endif // SETTEMPLATEDIALOG_H
