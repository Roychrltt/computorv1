#include "../include/computor.hpp"

int main(int argc, char** argv)
{
	std::string s;
	if (argc == 1)
		std::getline(std::cin, s);
	else if (argc == 2) s = argv[1];
	else
	{
		std::cout << "Error: bad number of arguments" << std::endl;
		std::cout << "Usage: ./computor <equation to solve>" << std::endl;
		return 0;
	}

	std::regex term("([+-]?\\s*\\d*\\.?\\d*)\\s*\\*\\s*X\\^(\\d+)");
	std::map<int, double> coef;
	std::string left = s.substr(0, s.find('='));
	std::string right = s.substr(s.find('=') + 1);

	auto parse = [&](std::string part, int sign)
	{
		for (auto it = std::sregex_iterator(part.begin(), part.end(), term); it != std::sregex_iterator(); ++it)
		{
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

	int deg = coef.empty() ? 0 : coef.rbegin()->first;
	while (deg > 0 && std::abs(coef[deg]) < 1e-9) deg--;
	std::cout << "Reduced form: ";
	bool first = true;
	for (int i = 0; i <= deg; i++)
	{
		double c = coef[i];
		if (std::abs(c) < 1e-9) continue;
		if (!first) std::cout << (c >= 0 ? " + " : " - ");
		else if (c < 0) std::cout << "-";
		std::cout << std::fixed << std::setprecision(1) << std::abs(c) << " * X^" << i;
		first = false;
	}
	if (first) std::cout << "0 * X^0";
	std::cout << " = 0" << std::endl;
	std::cout << "Polynomial degree: " << deg << std::endl;

	if (deg > 2) std::cout << "The polynomial degree is greater than 2, I can't solve." << std::endl;
	else if (deg == 0)
	{
		if (std::abs(coef[0]) < 1e-9) std::cout << "Any real numbers is a solution." << std::endl;
		else std::cout << "No solution." << std::endl;
	}
	else if (deg == 1)
	{
		double a = coef[1], b = coef[0];
		double x = -b / a;
		std::cout << "The solution is:" << std::endl;
		std::cout << std::fixed << std::setprecision(6) << x << std::endl;
	}
	else
	{
		double a = coef[2], b = coef[1], c = coef[0];
		double d = b * b - 4 * a * c;
		if (std::abs(d) < 1e-9)
		{
			std::cout << "Discriminant is zero, the solution is:" << std::endl;
			std::cout << -b / (2 * a) << std::endl;
		}
		else if (d > 0)
		{
			double s = std::sqrt(d);
			double x1 = (-b + s) / (2 * a);
			double x2 = (-b - s) / (2 * a);
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			std::cout << std::fixed << std::setprecision(6) << x1 << "\n" << x2 << std::endl;
		}
		else
		{
			std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
			double r = -b / (2 * a), i = sqrt(-d) / (2 * a);
			std::cout << std::fixed << std::setprecision(6) << r << " + " << i << "i" << std::endl;
			std::cout << r << " - " << i << "i" << std::endl;
		}
	}
	__Made in France__
}
