#ifndef MKTPASSWORD_H
#define MKTPASSWORD_H

#include "mktpassword_global.h"
#include <QFlag>
#include <QString>
#include <QVector>

class MKTPASSWORDSHARED_EXPORT MKTPassword
{

public:

    enum SymbolType {
        Lowercase = 0x01,
        Uppercase = 0x02,
        Digits = 0x04,
        Symbols = 0x08,
        Custom = 0x10
    };
    Q_DECLARE_FLAGS(SymbolTypes, SymbolType)

    enum PasswordHealth {
        Weak,
        Moderate,
        Strong
    };

    MKTPassword();

     QString encryptPassword(const QString &password) const;
     bool validPassword(const QString &password);

    QString generate(int length) const;
    PasswordHealth testPasswordHealth(const QString &password) const;


    SymbolTypes types() const;
    void setTypes(const SymbolTypes &types);

    void setCustomChars(const QVector<QChar> &customChars);
    void setCustomChars(const QString &customChars);

private:
    SymbolTypes m_types;
    QVector<QChar> m_customChars;

    char* toCStr(const QString &string) const;
};


#endif // MKTPASSWORD_H