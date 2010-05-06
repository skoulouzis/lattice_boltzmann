/****************************************************************************
** qtRipp meta object code from reading C++ file 'qtripp.h'
**
** Created: Sat Feb 16 17:58:34 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "qtripp.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *qtRipp::className() const
{
    return "qtRipp";
}

QMetaObject *qtRipp::metaObj = 0;
static QMetaObjectCleanUp cleanUp_qtRipp( "qtRipp", &qtRipp::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString qtRipp::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "qtRipp", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString qtRipp::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "qtRipp", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* qtRipp::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"showControls", 0, 0 };
    static const QUMethod slot_1 = {"showVTK", 0, 0 };
    static const QUMethod slot_2 = {"render", 0, 0 };
    static const QUMethod slot_3 = {"toggleActor", 0, 0 };
    static const QUMethod slot_4 = {"incrementSpinBox", 0, 0 };
    static const QUMethod slot_5 = {"setValue", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "showControls()", &slot_0, QMetaData::Private },
	{ "showVTK()", &slot_1, QMetaData::Private },
	{ "render()", &slot_2, QMetaData::Private },
	{ "toggleActor()", &slot_3, QMetaData::Private },
	{ "incrementSpinBox()", &slot_4, QMetaData::Private },
	{ "setValue()", &slot_5, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"qtRipp", parentObject,
	slot_tbl, 6,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_qtRipp.setMetaObject( metaObj );
    return metaObj;
}

void* qtRipp::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "qtRipp" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool qtRipp::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: showControls(); break;
    case 1: showVTK(); break;
    case 2: render(); break;
    case 3: toggleActor(); break;
    case 4: incrementSpinBox(); break;
    case 5: setValue(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool qtRipp::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool qtRipp::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool qtRipp::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
