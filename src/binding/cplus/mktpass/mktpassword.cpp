#include "mktpassword.h"

#include <QVector>
#include <QRandomGenerator>
#include <vector>
#include <sodium.h>
#include <string.h>



static QVector<QChar> lowercase  { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
static QVector<QChar> uppercase  { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                                   'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                                   'W', 'X', 'Y', 'Z'};
static QVector<QChar> digits  { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
static QVector<QChar> specialchars  { '&', '~', '#', '-', '_', '$', '%', '*', '!', '?' };


MKTPassword::MKTPassword()
{
}

QString MKTPassword::encryptPassword(const QString &password) const
{
    char hashed_password[crypto_pwhash_STRBYTES];
    char *cPassword = toCStr(password);

    if(sodium_init() < 0) {
        //TODO: show error
    }
    if (crypto_pwhash_str
            (hashed_password, cPassword, strlen(cPassword),
             crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0) {
        //TODO: show error
    }

    return QString(cPassword);
}

bool MKTPassword::validPassword(const QString &password)
{
    auto challengeHash = encryptPassword(password);
}

QString MKTPassword::generate(int length) const
{
    QString passwd(length);

    QVector<QChar> symbols;

    if (m_types.testFlag(Lowercase))
        symbols += lowercase;

    if (m_types.testFlag(Uppercase))
        symbols += uppercase;

    if (m_types.testFlag(Digits))
        symbols += digits;


    if (m_types.testFlag(Symbols))
        symbols += specialchars;


    if (m_types.testFlag(Custom))
        symbols += m_customChars;

    if (symbols.isEmpty())
        return QString();

    QRandomGenerator *rng = QRandomGenerator::global();

    for (int i = 0 ; i < length ; ++i) {
        int index = rng->bounded(symbols.length());
        passwd[i] = symbols[index];
    }

    return passwd;
}

MKTPassword::PasswordHealth MKTPassword::testPasswordHealth(const QString &password) const {
    bool hasLower = false, hasUpper = false;
    bool hasDigit = false, specialChar = false;

    int n = password.length();
    for (int i = 0; i < n; i++) {
        if(password[i].isLower()) hasLower = true;
        if(password[i].isUpper()) hasUpper = true;
        if(password[i].isDigit()) hasDigit = true;
        if(password[i].isSymbol()) specialChar = true;
    }

    if(hasDigit && hasUpper && specialChar && n > 8) return Strong;
    if((hasLower || hasLower) && specialChar && (n > 6)) return Moderate;
    return Weak;
}


MKTPassword::SymbolTypes MKTPassword::types() const
{
    return m_types;
}

void MKTPassword::setTypes(const SymbolTypes &types)
{
    m_types = types;
}

void MKTPassword::setCustomChars(const QVector<QChar> &customChars)
{
    m_customChars = customChars;
}

void MKTPassword::setCustomChars(const QString &customChars)
{
    m_customChars.clear();

    for (auto c: customChars)
        m_customChars.append(c);
}

char *MKTPassword::toCStr(const QString &string) const
{

}