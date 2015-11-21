#include <iostream>
#include <iomanip>

void multab(int factor){
	for(int j = 1; j <= factor; j++){
		for(int i = 1; i <= factor;i++){
			std::cout << std::left << "||\t" << j	<< " * " << i  << " = " <<  '\t'
					<< (i*j) << "\t ||"<< '\n';
		}
		std::cout << "----------------------------------" << '\n';
	}
}

void fractab(int factor){
	for(double j = 1; j <= factor; j++){
		for(double i = 1; i <= factor;i++){
			std::cout << std::left << std::setprecision(2) << "||\t" << i	<< " / " << j  << " = " <<  '\t'
					<< (i/j) << "\t ||"<< '\n';
		}
		std::cout << "----------------------------------" << '\n';
	}
}
