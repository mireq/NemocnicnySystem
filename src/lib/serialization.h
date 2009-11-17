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
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/collection_traits.hpp>

#include <fstream>
#include <QList>
#include <QStringList>
#include <QDate>


typedef unsigned int SerializationVersion;

template <class T>
class Serializer {
public:
	// -------------------------------- FileAccessException --------------------------------
	class FileAccessException {
	public:
		enum AccessType {
			Read  = 0,
			Write = 1
		};
		AccessType type() const {return m_type; };

	private:
		FileAccessException(AccessType type): m_type(type) {};
		AccessType m_type;

	friend class Serializer;
	};

	// -------------------------------- FileFormatException --------------------------------
	class FileFormatException {
	private:
		FileFormatException() {};

	friend class Serializer;
	};

	static void serialize(T &trieda, const char *name, const char *fileName)
	{
		std::ofstream ofs(fileName);
		if (!ofs.is_open()) {
			throw FileAccessException(FileAccessException::Write);
		}
		boost::archive::xml_oarchive oa(ofs);
		oa << boost::serialization::make_nvp(name, trieda);
	}

	static void unserialize(T &trieda, const char *name, const char *fileName)
	{
		std::ifstream ifs(fileName);
		if (!ifs.is_open()) {
			throw FileAccessException(FileAccessException::Read);
		}
		try {
			boost::archive::xml_iarchive ia(ifs);
			ia >> boost::serialization::make_nvp(name, trieda);
		}
		catch (boost::archive::archive_exception &) {
			throw FileFormatException();
		}
	}
};

namespace boost {
namespace serialization {


template<class Archive>
inline void save(Archive &archive, const QString &string, const unsigned int &)
{
	QByteArray text = string.toUtf8();
	int length = text.length();
	binary_object obj(text.data(), length);
	archive << make_nvp("length", length);
	archive << make_nvp("text", obj);
}


template<class Archive>
inline void load(Archive &archive, QString &string, const unsigned int &)
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
inline void save(Archive &archive, const QDate &date, const unsigned int &)
{
	bool valid = date.isValid();
	int day = date.toJulianDay();

	archive << make_nvp("valid", valid);
	archive << make_nvp("day", day);
}


template<class Archive>
inline void load(Archive &archive, QDate &date, const unsigned int &)
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
inline void save(Archive &archive, const QStringList &list, const unsigned int &)
{
	int size = list.size();

	archive << make_nvp("size", size);
	foreach (const QString &str, list) {
		archive << make_nvp("str", str);
	}
}


template<class Archive>
inline void load(Archive &archive, QStringList &list, const unsigned int &)
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


template<class Archive, class T>
inline void save(Archive &archive, const QList<T> &l, const unsigned int /* version */)
{
	int count = l.size();
	archive << BOOST_SERIALIZATION_NVP(count);
	foreach (const T &item, l) {
		archive << BOOST_SERIALIZATION_NVP(item);
	}
}


template<class Archive, class T>
inline void load(Archive &archive, QList<T> &l, const unsigned int /* version */)
{
	l.clear();
	int count = 0;
	archive >> BOOST_SERIALIZATION_NVP(count);
	for (int i = 0; i < count; ++i) {
		T item;
		archive >> BOOST_SERIALIZATION_NVP(item);
		l.push_back(item);
	}
}


template<class Archive, class T>
inline void serialize(Archive &archive, QList<T> &l, const unsigned int file_version)
{
    boost::serialization::split_free(archive, l, file_version);
}


} // namespace serialization
} // namespace boost

BOOST_SERIALIZATION_SPLIT_FREE(QString)
BOOST_CLASS_TRACKING(QString, track_never)
BOOST_SERIALIZATION_SPLIT_FREE(QDate)
BOOST_CLASS_TRACKING(QDate, track_never)
BOOST_SERIALIZATION_SPLIT_FREE(QStringList)
BOOST_CLASS_TRACKING(QStringList, track_never)
BOOST_SERIALIZATION_COLLECTION_TRAITS(QList)

#endif   /* ----- #ifndef SERIALIZATION_H  ----- */


