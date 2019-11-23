#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "estruturas.h"
#include "pre_processador.h"

int main (int argc, char **argv){
	//printf("Digite o nome do código fonte a ser lido (sem extensao .asm): ");

	if(argc == 2){
		std::string file_name = argv[1];
		std::string aux = file_name.substr(file_name.find('.')+1, file_name.size());

		if (aux == "asm"){
			file_name.resize(file_name.find('.'));
			pre_process(file_name);
		}
		else{
			std::cout << "Extensão inválida\n";
		};
	}
	else if(argc == 3){
		std::string file_name_1 = argv[1];
		std::string aux_1 = file_name_1.substr(file_name_1.find('.')+1, file_name_1.size());
		std::string file_name_2 = argv[2];
		std::string aux_2 = file_name_2.substr(file_name_2.find('.')+1, file_name_2.size());

		if (aux_1 == "asm" && aux_2 == "asm"){
			file_name_1.resize(file_name_1.find('.'));
			pre_process(file_name_1);
			file_name_2.resize(file_name_2.find('.'));
			pre_process(file_name_2);
		}
		else{
			std::cout << "Extensão inválida\n";
		};
	}
	else{
		std::cout << "Quantidade inválida de argumentos\n";
	}

}
