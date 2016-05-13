#include <cstdio>
#include <cstddef>
#include <iostream>

#include <string>
#include <vector>
#include <memory>

#include "../../grib/map.hpp"
#include "../../grib/grib.hpp"

template<std::size_t Size, typename CharT>
std::vector<std::string> C_GetIndex(const std::basic_string<CharT> &indexFullFileName) {
	std::FILE *stream = fopen(indexFullFileName.c_str(), "r");

	std::vector<std::string> index;
	char cStrEntry[Size] = "";
	while (fscanf(stream, "%s", &cStrEntry) != EOF) {
		index.push_back(cStrEntry);
	}

	fclose(stream);
	return index;
}

template<typename CharT>
void C_ReadEntireBinary(const std::basic_string<CharT> &fullFileName) {
	
	int k = 0;
	return;
}

int main() {

	using std::size_t;
	using std::string;
	const string pathToIndex = "../../hirlam_sample_input";
	const string indexFileName = "index";

	string indexFullFileName = pathToIndex + "/" + indexFileName;
	const size_t GribFileNameSize = 80;
	std::vector<string> gribFileNames = C_GetIndex<GribFileNameSize>(indexFullFileName);

	for (const string& gribFileName : gribFileNames) {
		string gribFullFileName = pathToIndex + "/" + gribFileName;
		std::unique_ptr<char[]> content = grib::ReadEntire(gribFullFileName);
		char *beginPtr = content.get();
		auto grib = grib::ParseGrib(beginPtr);
	}

	

	return 0;
}