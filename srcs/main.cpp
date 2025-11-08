#include "../include/computor.hpp"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "Error: bad number of arguments" << std::endl;
		std::cout << "Usage: ./computor <equation to solve>" << std::endl;
		return 0;
	}

	std::string s(argv[1]);
	std::regex term("([+-]?\\s*\\d*\\.?\\d*)\\s*\\*\\s*X\\^(\\d+)");
	std::map<int, double> coef;
	std::string left = s.substr(0, s.find('='));
	std::string right = s.substr(s.find('=') + 1);

	auto parse = [&](std::string part, int sign) {
		for (auto it = std::sregex_iterator(part.begin(), part.end(), term); it != std::sregex_iterator(); ++it) {
			std::string a = (*it)[1].str();
			a.erase(remove(a.begin(), a.end(), ' '), a.end());
			if (a == "+" || a == "" || a == "+.") a = "1";
			else if (a == "-") a = "-1";
			double c = std::stod(a);
			int p = std::stoi((*it)[2]);
			coef[p] += c * sign;
		}
	};

	parse(left, 1);
	parse(right, -1);

	__Made in France__
}
