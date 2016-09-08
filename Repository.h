#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QObject>
#include <QDir>
#include <QCryptographicHash>
#include <QtQml>

//https://github.com/multiformats/multihash
class MultiHash : public QCryptographicHash
{
    Q_GADGET
    Q_ENUMS(Method Encoding)
    Q_PROPERTY(Method method READ method)
    public:

    enum Method {
        identity = 0,
        Sha1 = 0x11, // QCryptographicHash::Sha1
        Sha2_256 = 0x12, // QCryptographicHash::Sha256
        Sha2_512 = 0x13, // QCryptographicHash::Sha512
        Sha3_512 = 0x14, // QCryptographicHash::Sha3_512
        Sha3_384 = 0x15, // QCryptographicHash::Sha3_384
        Sha3_256 = 0x16, // QCryptographicHash::Sha3_256
        Sha3_224 = 0x17  // QCryptographicHash::Sha3_224
    } _method;

    MultiHash(Method method);

    Method method() { return _method; }

    Q_INVOKABLE QByteArray result() const {
        QByteArray value = QCryptographicHash::result();
        value.prepend(value.length());
        value.prepend(_method);
        return value;
    }
};

class Repository : public QObject
{
    Q_OBJECT
    QDir directory;
public:
    explicit Repository(QObject *parent = 0);
    explicit Repository(QString path, QObject *parent = 0);

signals:

public slots:
    QByteArray store(QIODevice *content);
    QByteArray store(QByteArray content) {
        QBuffer buffer(&content);
        buffer.open(QIODevice::ReadOnly);
        return store(&buffer);
    }
    QByteArray store(QString content) { return store(content.toUtf8()); }

    QIODevice *read(QByteArray multihash);

    static QObject *singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    MultiHash::Method hashMethod;
};

#endif // REPOSITORY_H
