#ifndef _GRIB_GRIB_HPP_
#define _GRIB_GRIB_HPP_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <cstdio>
#include <map>
#include <string>

#include "marking.hpp" 

namespace grib {

	using std::size_t;
	using std::map;
	using std::string;
	using std::unique_ptr;

	class grib;

	unique_ptr<char[]> ReadEntire(const string &fullFileName);

	std::pair<grib, const char*> ParseGrib(char *octets);

	class grib {
	public:
		grib() {};
	};	//-- class grib --


	unique_ptr<char[]> ReadEntire(const string &fullFileName) {
		std::FILE *file = fopen(fullFileName.c_str(), "rb");
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		rewind(file);
		size_t octetsSize = fileSize + 1;
		unique_ptr<char[]> octets = std::make_unique<char[]>(octetsSize);
		fread(octets.get(), sizeof(char), octetsSize, file);
		return octets;
	};

	std::pair<grib, const char*> ParseGrib(char *octets) {
		char *pos = octets;
		size_t headerSize = marking::enum_map[marking::IS::GRIB_HEADER];
		if (marking::FILE_HEADER.compare(0, headerSize, pos) != 0) {
			//-- not grib file --
		}
	};

};	//-- namespace grib --

#endif	//-- _GRIB_GRIB_HPP_ --
