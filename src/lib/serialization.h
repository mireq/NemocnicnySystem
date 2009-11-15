/*
 * =====================================================================================
 *
 *       Filename:  serialization.h
 *
 *        Version:  1.0
 *        Created:  13.11.2009 10:20:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miroslav Bendik
 *        Company:  LinuxOS.sk
 *
 * =====================================================================================
 */


#ifndef  SERIALIZATION_H
#define  SERIALIZATION_H


#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/binary_object.hpp>
#include <boost/serialization/nvp.hpp>

#include <fstream>
#include <QStringList>
#include <QDate>


typedef unsigned int SerializationVersion;


template <class T>
void SerializeClass(T &trieda, const char *name, const char *fileName)
{
	std::ofstream ofs(fileName);
	boost::archive::xml_oarchive oa(ofs);
	oa << boost::serialization::make_nvp(name, trieda);
}

template <class T>
T UnserializeClass(const char *name, const char *fileName)
{
	std::ifstream ifs(fileName);
	boost::archive::xml_iarchive ia(ifs);
	T nove;
	ia >> boost::serialization::make_nvp(name, nove);
	return nove;
}

namespace boost {
namespace serialization {


template<class Archive>
void save(Archive &archive, const QString &string, const unsigned int &)
{
	QByteArray text = string.toUtf8();
	int length = text.length();
	binary_object obj(text.data(), length);
	archive << make_nvp("length", length);
	archive << make_nvp("text", obj);
}


template<class Archive>
void load(Archive &archive, QString &string, const unsigned int &)
{
	int length;
	archive >> make_nvp("length", length);

	char *data = new char[length];
	binary_object obj(data, length);
	archive >> make_nvp("text", obj);

	string = QString::fromUtf8(data, length);
	delete[] data;
}


template<class Archive>
void save(Archive &archive, const QDate &date, const unsigned int &)
{
	bool valid = date.isValid();
	int day = date.toJulianDay();

	archive << make_nvp("valid", valid);
	archive << make_nvp("day", day);
}


template<class Archive>
void load(Archive &archive, QDate &date, const unsigned int &)
{
	bool valid = false;
	int day = 0;

	archive >> make_nvp("valid", valid);
	archive >> make_nvp("day", day);

	if (valid) {
		date = QDate::fromJulianDay(day);
	}
}


template<class Archive>
void save(Archive &archive, const QStringList &list, const unsigned int &)
{
	int size = list.size();

	archive << make_nvp("size", size);
	foreach (const QString &str, list) {
		archive << make_nvp("str", str);
	}
}


template<class Archive>
void load(Archive &archive, QStringList &list, const unsigned int &)
{
	int size = 0;
	list.clear();

	archive >> make_nvp("size", size);
	for (int i = 0; i < size; ++i) {
		QString str;
		archive >> make_nvp("str", str);
		list << str;
	}
}


} // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(QString)
BOOST_CLASS_TRACKING(QString, track_never)
BOOST_SERIALIZATION_SPLIT_FREE(QDate)
BOOST_CLASS_TRACKING(QDate, track_never)
BOOST_SERIALIZATION_SPLIT_FREE(QStringList)
BOOST_CLASS_TRACKING(QStringList, track_never)

#endif   /* ----- #ifndef SERIALIZATION_H  ----- */


