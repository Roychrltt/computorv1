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

	std::cout << "\nInput equation: " << s << std::endl;
	std::cout << "Left side: " << left << std::endl;
	std::cout << "Right side: " << right << std::endl;
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
	std::cout << "\n---------- Computor working -----------" << std::endl;
	std::cout << "\nStep 1: subtract right side from left side" << std::endl;
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
	std::cout << "Coefficients after reduction:" << std::endl;
	for (auto& [pp, cc] : coef)
		if (std::abs(cc) > 1e-9) std::cout << "X^" << pp << ": " << cc << std::endl;
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
		std::cout << "\nStep 2: compute the solution: " << std::endl;
		std::cout << "x = -b / a = " << -b << " / " << a << " = ";
		std::cout << std::fixed << std::setprecision(6) << x << std::endl;
	}
	else
	{
		std::cout << "\nStep 2: compute discriminant" << std::endl;
		double a = coef[2], b = coef[1], c = coef[0];
		double d = b * b - 4 * a * c;
		std::cout << "D = b^2 - 4ac = " << b * b << " - 4 * " << a << " * " << c << " = " << d << std::endl;
		if (std::abs(d) < 1e-9)
		{
			std::cout << "\nStep 3: discriminant is zero, we have only one answer" << std::endl;
			std::cout << "\nStep 4: compute the answer" << std::endl;
			std::cout << "Solution: x = -b / (2 * a) = " << -b / (2 * a) << std::endl;
		}
		else if (d > 0)
		{
			double sq = std::sqrt(d);
			double x1 = (-b + sq) / (2 * a);
			double x2 = (-b - sq) / (2 * a);
			std::cout << "\nStep 3: compute sqrt(D)" << std::endl;
			std::cout << "sqrt(D) = " << sq << std::endl;
			std::cout << "\nStep 4: compute solutions:" << std::endl;
			std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			std::cout << "x1 = (-b + sqrt(D)) / (2a) = " << std::fixed << std::setprecision(6) << x1 << std::endl;
			std::cout << "x2 = (-b - sqrt(D)) / (2a) = " << std::fixed << std::setprecision(6) << x2 << std::endl;
		}
		else
		{
			std::cout << "\nStep 3: Discriminant is strictly negative, there are two complex solutions" << std::endl;
			std::cout << "\nStep 4: compute solutions:" << std::endl;
			double r = -b / (2 * a), i = std::sqrt(-d) / (2 * a);
			std::cout << "compute real part = -b / (2a) = " << -b << " / " << 2 * a << " = " << r << std::endl;
			std::cout << "compute imaginary part = sqrt(-D) / (2a) = " << std::sqrt(-d) << " / " << 2 * a << " = " << i << std::endl;
			std::cout << "x1 = real + imaginary * i = " << std::fixed << std::setprecision(6) << r << " + " << i << "i" << std::endl;
			std::cout << "x2 = real - imaginary * i = " << std::fixed << std::setprecision(6) << r << " - " << i << "i" << std::endl;
		}
	}
	__Made in France__
}
