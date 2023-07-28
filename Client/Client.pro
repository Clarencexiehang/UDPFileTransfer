LIBS +=/lib/lib/libcrypto-3-x64.dll /lib/lib/ws2_32.dll /lib/lib/libssl-3-x64.dll /lib/lib/zlibwapi.dll
LIBS += -lws2_32

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entity/requestbody.cpp \
    Service/clientservice.cpp \
    Service/clientservice.cpp \
    Util/caes/caes.cpp \
    Util/md5/md5.cpp \
    Util/md5/md5.cpp \
    Util/openssl/applink.c \
    Util/rsa/crsa.cpp \
    View/DownFileInfo.cpp \
    View/DownLoad.cpp \
    View/DownThread.cpp \
    View/Request.cpp \
    View/config.cpp \
    View/main.cpp \
    View/mainpage.cpp \
    View/mainwindow.cpp

HEADERS += \
    Entity/BreakPoint.h \
    Entity/requestbody.h \
    Service/clientservice.h \
    Service/clientservice.h \
    Util/compress/Decompression.h \
    Util/conf/crypto.h \
    Util/conf/ssl.h \
    Util/conf/status.h \
    Util/conf/zconf.h \
    Util/conf/zlib.h \
    Util/md5/md5.h \
    Util/md5/md5.h \
    Util/openssl/__DECC_INCLUDE_EPILOGUE.H \
    Util/openssl/__DECC_INCLUDE_PROLOGUE.H \
    Util/openssl/aes.h \
    Util/openssl/asn1.h \
    Util/openssl/asn1_mac.h \
    Util/openssl/asn1err.h \
    Util/openssl/asn1t.h \
    Util/openssl/async.h \
    Util/openssl/asyncerr.h \
    Util/openssl/bio.h \
    Util/openssl/bioerr.h \
    Util/openssl/blowfish.h \
    Util/openssl/bn.h \
    Util/openssl/bnerr.h \
    Util/openssl/buffer.h \
    Util/openssl/buffererr.h \
    Util/openssl/camellia.h \
    Util/openssl/cast.h \
    Util/openssl/cmac.h \
    Util/openssl/cmp.h \
    Util/openssl/cmp_util.h \
    Util/openssl/cmperr.h \
    Util/openssl/cms.h \
    Util/openssl/cmserr.h \
    Util/openssl/comp.h \
    Util/openssl/comperr.h \
    Util/openssl/conf.h \
    Util/openssl/conf_api.h \
    Util/openssl/conferr.h \
    Util/openssl/configuration.h \
    Util/openssl/conftypes.h \
    Util/openssl/core.h \
    Util/openssl/core_dispatch.h \
    Util/openssl/core_names.h \
    Util/openssl/core_object.h \
    Util/openssl/crmf.h \
    Util/openssl/crmferr.h \
    Util/openssl/crypto.h \
    Util/openssl/cryptoerr.h \
    Util/openssl/cryptoerr_legacy.h \
    Util/openssl/ct.h \
    Util/openssl/cterr.h \
    Util/openssl/decoder.h \
    Util/openssl/decodererr.h \
    Util/openssl/des.h \
    Util/openssl/dh.h \
    Util/openssl/dherr.h \
    Util/openssl/dsa.h \
    Util/openssl/dsaerr.h \
    Util/openssl/dtls1.h \
    Util/openssl/e_os2.h \
    Util/openssl/ebcdic.h \
    Util/openssl/ec.h \
    Util/openssl/ecdh.h \
    Util/openssl/ecdsa.h \
    Util/openssl/ecerr.h \
    Util/openssl/encoder.h \
    Util/openssl/encodererr.h \
    Util/openssl/engine.h \
    Util/openssl/engineerr.h \
    Util/openssl/err.h \
    Util/openssl/ess.h \
    Util/openssl/esserr.h \
    Util/openssl/evp.h \
    Util/openssl/evperr.h \
    Util/openssl/fips_names.h \
    Util/openssl/fipskey.h \
    Util/openssl/hmac.h \
    Util/openssl/http.h \
    Util/openssl/httperr.h \
    Util/openssl/idea.h \
    Util/openssl/kdf.h \
    Util/openssl/kdferr.h \
    Util/openssl/lhash.h \
    Util/openssl/macros.h \
    Util/openssl/md2.h \
    Util/openssl/md4.h \
    Util/openssl/md5.h \
    Util/openssl/mdc2.h \
    Util/openssl/modes.h \
    Util/openssl/obj_mac.h \
    Util/openssl/objects.h \
    Util/openssl/objectserr.h \
    Util/openssl/ocsp.h \
    Util/openssl/ocsperr.h \
    Util/openssl/opensslconf.h \
    Util/openssl/opensslv.h \
    Util/openssl/ossl_typ.h \
    Util/openssl/param_build.h \
    Util/openssl/params.h \
    Util/openssl/pem.h \
    Util/openssl/pem2.h \
    Util/openssl/pemerr.h \
    Util/openssl/pkcs12.h \
    Util/openssl/pkcs12err.h \
    Util/openssl/pkcs7.h \
    Util/openssl/pkcs7err.h \
    Util/openssl/prov_ssl.h \
    Util/openssl/proverr.h \
    Util/openssl/provider.h \
    Util/openssl/rand.h \
    Util/openssl/randerr.h \
    Util/openssl/rc2.h \
    Util/openssl/rc4.h \
    Util/openssl/rc5.h \
    Util/openssl/ripemd.h \
    Util/openssl/rsa.h \
    Util/openssl/rsaerr.h \
    Util/openssl/safestack.h \
    Util/openssl/seed.h \
    Util/openssl/self_test.h \
    Util/openssl/sha.h \
    Util/openssl/srp.h \
    Util/openssl/srtp.h \
    Util/openssl/ssl.h \
    Util/openssl/ssl2.h \
    Util/openssl/ssl3.h \
    Util/openssl/sslerr.h \
    Util/openssl/sslerr_legacy.h \
    Util/openssl/stack.h \
    Util/openssl/store.h \
    Util/openssl/storeerr.h \
    Util/openssl/symhacks.h \
    Util/openssl/tls1.h \
    Util/openssl/trace.h \
    Util/openssl/ts.h \
    Util/openssl/tserr.h \
    Util/openssl/txt_db.h \
    Util/openssl/types.h \
    Util/openssl/ui.h \
    Util/openssl/uierr.h \
    Util/openssl/whrlpool.h \
    Util/openssl/x509.h \
    Util/openssl/x509_vfy.h \
    Util/openssl/x509err.h \
    Util/openssl/x509v3.h \
    Util/openssl/x509v3err.h \
    Util/rsa/Rsa.h \
    Util/rsa/crsa.h \
    View/DownFileInfo.h \
    View/DownLoad.h \
    View/DownThread.h \
    View/Request.h \
    View/config.h \
    View/mainpage.h \
    View/mainwindow.h

FORMS += \
    View/mainpage.ui \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MainWindow/mainWindow.qss \
    Util/lib/libcrypto.lib \
    Util/lib/libssl-3-x64.dll \
    Util/lib/libssl.lib \
    Util/lib/ws2_32.dll \
    Util/lib/zlibwapi.dll \
    Util/lib/zlibwapi.lib \
    View/mainWindow.qss \
    qss/mainWindow.qss

RESOURCES += \
    Resource/Resource.qrc
