#include "Repository.h"
#include <QTemporaryFile>
#include <QStandardPaths>
#include <memory>

Repository::Repository(QObject *parent)
    : Repository(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).filePath("repository"), parent)
{ }

Repository::Repository(QString path, QObject *parent)
    : QObject(parent)
    , directory(path)
    , hashMethod(MultiHash::Sha1)
{
    directory.mkpath(directory.path());
}

// Second, define the singleton type provider function (callback).
QObject *Repository::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return new Repository();
}

QByteArray Repository::store(QIODevice *content)
{
    MultiHash hash(hashMethod);

    QTemporaryFile file(directory.filePath("tmpXXXXXX"));
    if(file.open()) {
        char buffer[4*1024];
        int len;
        while((len = content->read(buffer, sizeof(buffer))) > 0) {
            hash.addData(buffer,len);
            file.write(buffer,len);
        }
        if(content->atEnd()) {
            QString path = directory.filePath(hash.result().toBase64());
            if(QFile::exists(path)) {
                /* this content is already stored? */
                return hash.result();
            } else if(file.rename(path)) {
                // successfully written, so rename to the hash and keep it after all.
                file.setAutoRemove(false);
                return hash.result();
            }
        }
    }
    abort();
}

QIODevice *Repository::read(QByteArray multihash)
{
    std::unique_ptr<QIODevice> file(new QFile(directory.filePath(multihash)));
    if(file->open(QIODevice::ReadOnly)) {
        return file.release();
    }

    return nullptr;
}

namespace {
    QCryptographicHash::Algorithm fromMultiHashMethod(MultiHash::Method method) {
        switch(method) {
        case MultiHash::Sha1    : return QCryptographicHash::Sha1;
        case MultiHash::Sha2_256: return QCryptographicHash::Sha256;
        case MultiHash::Sha2_512: return QCryptographicHash::Sha512;
        case MultiHash::Sha3_512: return QCryptographicHash::Sha3_512;
        case MultiHash::Sha3_384: return QCryptographicHash::Sha3_384;
        case MultiHash::Sha3_256: return QCryptographicHash::Sha3_256;
        case MultiHash::Sha3_224: return QCryptographicHash::Sha3_224;
        default: abort();
        }
    }
}

MultiHash::MultiHash(MultiHash::Method method)
    : QCryptographicHash(fromMultiHashMethod(method)),
      _method(method)
{ }
