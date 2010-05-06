/****************************************************************************
** FlowField meta object code from reading C++ file 'flowfield.h'
**
** Created: Sat Feb 16 17:58:31 2008
**      by: The Qt MOC ($Id: qt/moc_yacc.cpp   3.3.7   edited Oct 19 16:22 $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "flowfield.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *FlowField::className() const
{
    return "FlowField";
}

QMetaObject *FlowField::metaObj = 0;
static QMetaObjectCleanUp cleanUp_FlowField( "FlowField", &FlowField::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString FlowField::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FlowField", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString FlowField::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "FlowField", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* FlowField::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"FlowField", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_FlowField.setMetaObject( metaObj );
    return metaObj;
}

void* FlowField::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "FlowField" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool FlowField::qt_invoke( int _id, QUObject* _o )
{
    return QWidget::qt_invoke(_id,_o);
}

bool FlowField::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool FlowField::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool FlowField::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
