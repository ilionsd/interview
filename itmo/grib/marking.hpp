#ifndef _GRIB_MARKING_HPP_
#define _GRIB_MARKING_HPP_

#include <cstddef>
#include <map>
#include <string>
#include <limits>

#include "map.hpp"


namespace grib {

	using std::size_t;
	using std::map;
	using std::string;

	typedef unsigned marking_map_key;
	using octets_map = map<marking_map_key, size_t> ;

	struct marking {

		enum struct size : size_t {
			//-- Flag for fields with unspecified size --
			UNSPECIFIED = std::numeric_limits<size_t>::max()
		};

		// NATIONAL/INTERNATIONAL
		// ORIGINATING CENTERS
		// (Assigned By The WMO)
		// (PDS Octet 5)
		enum struct international_originating_centers : unsigned {
			US_WEATHER_SERVICE_NATIONAL_MET_CENTER = 7,
			US_WEATHER_SERVICE_NWS_TELECOMMS_GATEWAY = 8,
			US_WEATHER_SERVICE_FIELD_STATIONS = 9,
			JAPANESE_METHEOROLOGICAL_AGENCY_TOKYO = 34,
			NATIONAL_HURRICANE_CENTER_MIAMI = 52,
			CANADIAN_METEOROLOGICAL_SERVICE_MONREAL = 54,
			US_AIR_FORCE_GLOBAL_WEATHER_CENTER = 57,
			US_NAVY_FLEET_NUMERICAL_OCEANOGRAPHY_CENTER = 58,
			NOAA_FORECAST_SYSTEMS_LAB_BOULDER_CO = 59,
			UK_MET_OFFICE_BRACKNELL = 74,
			FRENCH_WEATHER_SERVICE_TOULOUSE = 85,
			EUROPEAN_SpACE_AGENCY_ESA = 97,
			EUROPEAN_CENTER_FOR_MEDIUM_rANGE_WEATHER_FORECASTS_READING = 98,
			DEBILT_NETHERLANDS = 99
		};

		enum struct GDS_Inclusion : unsigned char {
			FLAG		= 0b10000000,
			INCLUDED	= 0b10000000,
			OMITTED		= 0b00000000
		};

		enum struct BMS_Inclusion : unsigned char {
			FLAG		= 0b01000000,
			INCLUDED	= 0b01000000,
			OMITTED		= 0b00000000
		};

		//-- section 0 (THE INDICATOR SECTION) --
		enum struct IS : marking_map_key {
			GRIB_HEADER = 0,
			GRIB_SIZE = 1,
			EDITION_NUMBER = 2
		};
		//-- section 1 (THE PRODUCT DEFINITION SECTION) --
		enum struct PDS : marking_map_key {
			// 1-3 Length in octets of the Product Definition Section
			PDS_SIZE = 3,

			// 4 Parameter Table Version number.
			// Currently Version 2 for international exchange.
			// Parameter table version numbers 128 - 254 are reserved for local use.
			PARAMETER_TABLE_VERSION_NUMBER = 4,

			// 5 Identification of center (Table 0 - Part 1)
			IDENTIFICATION_OF_CENTER = 5,

			// Generating process ID number
			// (allocated by the originating center; See Table A)
			GENERATING_PROCESS_ID_NUMBER = 6,

			// Grid Identification (geographical location and area; See Table B)
			GRID_IDENTIFICATION = 7,

			// Flag specifying the presence or absence of a GDS or a BMS (See Table 1)
			GDS_AND_BMS_FLAG = 8,

			// Indicator of parameter and units (Table 2)
			INDICATOR_OF_PARAMETER_AND_UNITS = 9,

			// Indicator of type of level or layer (See Tables 3 & 3a)
			INDICATOR_OF_TYPE_OF_LEVEL_OR_LAYER = 10,

			// Height, pressure, etc. of the level or layer (See Table 3)
			HEIGHT_PRESSURE_ETC_OF_LEVEL_OR_LAYER = 11,

			// Year of century
			YEAR_OF_CENTURY = 12,

			// Month of year 
			MONTH_OF_YEAR = 13,

			// Day of month
			DAY_OF_MONTH = 14,

			// Hour of day
			HOUR_OF_DAY = 15,

			// Minute of hour
			MINUTE_OF_HOUR = 16,

			// Forecast time unit (see Table 4)
			FORECATS_TIME_UNIT = 17,

			// P1 - Period of time (Number of time units)
			// (0 for analysis or initialized analysis.)
			// Units of time given by content of octet 18.
			P1 = 18,

			// P2 - Period of time (Number of time units) or
			// Time interval between successive analyses, successive initialized analyses, or forecasts, undergoing averaging or accumulation.Units given by octet 18.
			P2 = 19,

			// Time range indicator (See Table 5)
			TIME_RANGE_INDICATOR = 20,

			// Number included in average, when octet 21 (Table 5) indicates an average or accumulation; otherwise set to zero.
			NUMBER_INCLUDED_IN_AVERAGE = 21,

			// Number Missing from averages or accumulations.
			NUMBER_MISSING_FROM_AVERAGES_OR_ACCUMULATIONS = 22,

			// Century of Initial (Reference) time (=20 until Jan. 1, 2001)
			CENTURY_OF_INITIAL_TIME = 23,

			// Identification of sub-center (Table 0 - Part 2)
			IDENTIFICATION_OF_SUBCENTER = 24,

			// The decimal scale factor D. A negative value is indicated by setting the high order bit (bit No. 1) in octet 27 to 1 (on).
			DECIMAL_SCALE_FACTOR_D = 25,

			// Reserved (need not be present)
			RESERVED = 26,

			// Reserved for originating center use.
			RESERVED_FOR_ORIGINATING_CENTER_USE = 27
	
		};

		//-- section 2 (GRID DESCRIPTION SECTION) --
		enum struct GDS : marking_map_key {

			// Length in octets of the Grid Description Section
			GDS_SIZE = 28,

			// NV, the number of vertical coordinate parameters
			NV = 29


		};

		static const string FILE_HEADER;

		static const octets_map octets;

		static const enumkey_map<marking_map_key, size_t, map> enum_map;
	
	};	//-- struct marking --

	const enumkey_map<marking_map_key, size_t, map> marking::enum_map = {
		{ static_cast<marking_map_key>(marking::IS::GRIB_HEADER), 4 },
		{ static_cast<marking_map_key>(marking::IS::GRIB_SIZE), 3 }
	};

	const string marking::FILE_HEADER = string("GRIB");

	const octets_map marking::octets = {

	//-- section 0 (IS) --

		// 1-4
		{static_cast<marking_map_key>(marking::IS::GRIB_HEADER), 4},
		// 5-7 
		{ static_cast<marking_map_key>(marking::IS::GRIB_SIZE), 3},
		// 8 
		{ static_cast<marking_map_key>(marking::IS::EDITION_NUMBER), 1},
		
	//-- section 1 (PDS) --

		// 1-3 
		{ static_cast<marking_map_key>(marking::PDS::PDS_SIZE), 3},
		// 4
		{ static_cast<marking_map_key>(marking::PDS::PARAMETER_TABLE_VERSION_NUMBER), 1},
		// 5
		{ static_cast<marking_map_key>(marking::PDS::IDENTIFICATION_OF_CENTER), 1},
		// 6
		{ static_cast<marking_map_key>(marking::PDS::GENERATING_PROCESS_ID_NUMBER), 1},
		// 7
		{ static_cast<marking_map_key>(marking::PDS::GRID_IDENTIFICATION), 1},
		// 8
		{ static_cast<marking_map_key>(marking::PDS::GDS_AND_BMS_FLAG), 1},
		// 9
		{ static_cast<marking_map_key>(marking::PDS::INDICATOR_OF_PARAMETER_AND_UNITS), 1},
		// 10
		{ static_cast<marking_map_key>(marking::PDS::INDICATOR_OF_TYPE_OF_LEVEL_OR_LAYER), 1},
		// 11-12
		{ static_cast<marking_map_key>(marking::PDS::HEIGHT_PRESSURE_ETC_OF_LEVEL_OR_LAYER), 2},
		// 13
		{ static_cast<marking_map_key>(marking::PDS::YEAR_OF_CENTURY), 1},
		// 14
		{ static_cast<marking_map_key>(marking::PDS::MONTH_OF_YEAR), 1},
		// 15
		{ static_cast<marking_map_key>(marking::PDS::DAY_OF_MONTH), 1},
		// 16
		{ static_cast<marking_map_key>(marking::PDS::HOUR_OF_DAY), 1},
		// 17
		{ static_cast<marking_map_key>(marking::PDS::MINUTE_OF_HOUR), 1},
		// 18
		{ static_cast<marking_map_key>(marking::PDS::FORECATS_TIME_UNIT), 1},
		// 19
		{ static_cast<marking_map_key>(marking::PDS::P1), 1},
		// 20
		{ static_cast<marking_map_key>(marking::PDS::P2), 1},
		// 21
		{ static_cast<marking_map_key>(marking::PDS::TIME_RANGE_INDICATOR), 1},
		// 22-23
		{ static_cast<marking_map_key>(marking::PDS::NUMBER_INCLUDED_IN_AVERAGE), 2},
		// 24
		{ static_cast<marking_map_key>(marking::PDS::NUMBER_MISSING_FROM_AVERAGES_OR_ACCUMULATIONS), 1},
		// 25
		{ static_cast<marking_map_key>(marking::PDS::CENTURY_OF_INITIAL_TIME), 1},
		// 26
		{ static_cast<marking_map_key>(marking::PDS::IDENTIFICATION_OF_SUBCENTER), 1},
		// 27-28
		{ static_cast<marking_map_key>(marking::PDS::DECIMAL_SCALE_FACTOR_D), 2},
		// 29-40
		{ static_cast<marking_map_key>(marking::PDS::RESERVED), 12},
		// 41-..
		{ static_cast<marking_map_key>(marking::PDS::RESERVED_FOR_ORIGINATING_CENTER_USE), static_cast<size_t>(marking::size::UNSPECIFIED)}

	//-- secton 2 (GRID DESCRIPTION SECTION) --
	};

};	//-- namespace grib --

#endif	//-- _GRIB_MARKING_HPP_ --
