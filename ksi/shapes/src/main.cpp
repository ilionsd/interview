
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>


#include "../include/shapes.hpp"

using std::cin;
using std::cout;
using std::endl;

typedef void(*menu_navigation)();

void main_menu();
void help_main();
void view_list();
void delete_item();
void create_item();


std::vector<std::unique_ptr<shapes::shape>> list;

std::vector<shapes::make_shape_f> createF = {
	&shapes::make_cylinder,
	&shapes::make_cuboid,
	&shapes::make_cube,
	&shapes::make_pyramid
};

std::vector<std::string> shapeTypes = {
	"Cylinder",
	"Cuboid",
	"Cube",
	"Pyramid"
};

std::vector<std::string> argsOrder = {
	"<Base radius, Height>",
	"<Width, Height, Length>",
	"<Side>",
	"<Side(1;2), Side(2;3), ... , Side(N,1), Angle1, Angle2, ... , AngleN, Height, Tolerance = 1e-6 (Optional)>"
};

std::vector<std::string> helpMain = {
	"Quit",
	"View",
	"Create",
	"Delete",
	"Help"
};

int main() {
    cout << "Hello world!" << endl;

	shapes::make_shape_f make_pyramid_f = &shapes::make_pyramid;
	

    auto pyramid = shapes::make_pyramid({2, sqrt(5), 1}, {M_PI / 2.0, asin(1.0 / sqrt(5)), asin(2.0 / sqrt(5))}, 3);
    cout << pyramid->to_string() << endl;


	main_menu();



    return 0;
}

void main_menu() {
	cout << "";
	while (1) {
		cout << ">";
		unsigned option;
		cin >> option;
		switch (option) {
			//-- quit --
		case 0: return;
			break;
			//-- list --
		case 1: view_list();
			break;
			//-- create --
		case 2: create_item();
			break;
			//-- delete --
		case 3: delete_item();
			break;
			//-- help --
		default: help_main();
			break;
		}
	}
}

void help_main() {
	cout << "------------" << endl;
	cout << "List of commands of main menu:" << endl;
	for (std::size_t k = 0; k < helpMain.size(); ++k)
		cout << k << " - " << helpMain[k] << endl;
	cout << "------------" << endl;
}

void view_list() {
	cout << "List of shapes (" << list.size() << " items):" << endl;
	for (std::size_t k = 0; k < list.size(); ++k)
		cout << k + 1 << " - " << list[k]->to_string() << endl;
}

void delete_item() {
	cout << "Choose item from 1 to " << list.size() << " (Any other value - Quit) ";
	std::size_t index;
	cin >> index;
	cout << endl;
	if (index <= 0 || index > list.size())
		cout << "Quit" << endl;
	else {
		list.erase(list.cbegin() + index - 1);
		cout << index << " deleted" << endl;
	}
}

void help_shapes() {
	cout << "------------" << endl;
	cout << "Shapes types (" << createF.size() << " types)" << endl;
	for (std::size_t k = 0; k < createF.size(); ++k)
		cout << k + 1 << " - " << shapeTypes[k] << endl;
	cout << "------------" << endl;
}

std::vector<double> get_args(const std::string &line) {
	std::size_t index;
	std::string subStr = line;
	std::vector<double> vals;
	while (!subStr.empty()) {
		double val = std::stod(subStr, &index);
		vals.push_back(val);
		subStr = subStr.substr(index);
	}
	return vals;
}

void create_item() {
	help_shapes();
	cout << "Choose shape type from 1 to " << createF.size() << " (0 - Quit, any other value - help) ";
	std::size_t index;
	cin >> index;
	cout << endl;
	if (index < 0 || index > createF.size())
		help_shapes();
	else if (index == 0)
		cout << "Quit" << endl;
	else {
		cout << argsOrder[index - 1] << endl;
		std::vector<double> args;
		do {
			double val;
			cin >> val;
			args.push_back(val);
		} while (cin.peek() != '\n');
		
		try {
			auto shape = createF[index - 1](args);
			list.push_back(std::move(shape));
		}
		catch (std::invalid_argument e) {
			cout << "Invalid arguments: " << e.what() << endl;
		}
		catch (std::exception e) {
			cout << "Unexpected error: " << e.what() << endl;
		}
		
	}
}
