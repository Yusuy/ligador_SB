std::vector<std::string> link_file_reader(std::string input_file_name);
void link (int argc, std::vector<std::string> argv);
void link_file_generator(std::vector<std::string> code, std::string file_name);
std::string test_first(int argc, std::vector<std::string> argv);
std::vector<std::string> link_concat (std::vector<std::string> program_1, std::vector<std::string> program_2);

//lê arquivos para leitura
std::vector<std::string> link_file_reader(std::string input_file_name){

	std::ifstream input_file (input_file_name);
	std::vector<std::string> word;
	char c;
	std::vector<char> word_c;
	char word_aux[50];
	unsigned i, j, k;

	word.push_back(" \n ");
	//Rotina para salvar o código em um vetor de caracteres ignorando os comentátios
	if(input_file.is_open()){
		while (input_file.get(c)){
			if (c == ';'){
				while(c != '\n'){
					input_file.get(c);
				};
				c = '\n';
				word_c.push_back(c);
			}
			else {
				if(c == '\n'){
					word_c.push_back(' ');
					word_c.push_back('\n');
					word_c.push_back(' ');
				}
				else{
					word_c.push_back(toupper(c));
				};
			};
		};

		//Rotina para salvar o código em um vetor de strings ignorando espaços e quebras de linha
		i = 0;
		j = 0;
		k = 0;

		while((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n') && (i < word_c.size())){
				word_aux[j] = word_c[i];
				//std::cout << word_c[i] << "\n";
				i++;
				j++;
			};

		word_aux[i] = '\0';
		word.push_back(word_aux);
		//std::cout << word_aux << "\n";

		for(i = i; i < word_c.size(); i++){
			j = 0;
			if((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n')){
				while((word_c[i] != ' ') && (word_c[i] != '\t') && (word_c[i] != '\n') && (i < word_c.size())){
					word_aux[j] = word_c[i];
					i++;
					j++;
				}
				word.push_back(word_aux);
				//std::cout << word_aux << "\n";
			}

			else if (word_c[i] == '\n'){
				word_aux[j] = '\n';
				word.push_back(word_aux);
			};

			for(j=0;j<sizeof(word_aux);j++){
				word_aux[j] = '\0';
			};
			k++;
		};
	}

		else{
			printf("\nArquivo nao encontrado. Verifique se digitou o nome correto e se o arquivo está no mesmo diretório do programa.\n");
			word.push_back("");
		};

		return word;
}

//gera arquivo ligado com extensao .linked
void link_file_generator(std::vector<std::string> code, std::string file_name){

	std::ofstream newFile(file_name);
	unsigned i;

	for(i = 0; i < code.size(); i++) {
    newFile << code[i] << " ";
	};
}

//testa quem deve vir primeiro e retorna string com codigo
std::string test_first(int argc, std::vector<std::string> argv){

	std::string output;
  std::string aux_1 = argv[0];
  std::string aux_2 = argv[1];
  std::vector<std::string> program_1 = build_file_reader(aux_1);
  std::vector<std::string> program_2 = build_file_reader(aux_2);
	std::string name_1 = aux_1.substr(aux_1.find(".")+1, aux_1.size());
	name_1.append(":");
  std::string name_2 = aux_2.substr(aux_2.find(".")+1, aux_2.size());
	name_2.append(":");

  for(unsigned i = 0; i<program_1.size(); i++){
    if(program_1[i] == name_2 && program_1[i+1] == "EXTERN"){
      output = name_1;
		}
  }

  for(unsigned i = 0; i<program_2.size(); i++){
		if(program_2[i] == name_1 && program_2[i+1] == "EXTERN"){
      output = name_2;
		}
  }
  return output;
}

std::vector<std::string> link_concat (std::vector<std::string> program_1, std::vector<std::string> program_2){

	std::vector<std::string> aux;

	for(unsigned i = 0; i<program_1.size(); i++){
		aux.push_back(program_1[i]);
	}
	for(unsigned i = 0; i<program_2.size(); i++){
		aux.push_back(program_2[i]);
	}

	//for(unsigned i = 0; i<aux.size(); i++){
	//	std::cout << aux[i] << " ";
	//}

	std::vector<build_structure> table_general = get_symbols(aux);

	std::vector<std::string> output;

	output = builder(aux, "Linked", table_general);

	std::vector<std::string> true_output;
	for(unsigned i = 10; i<output.size(); i++){
		true_output.push_back(output[i]);
	}
	return true_output;
}

//Aqui é feita toda a logica de ligaçao
void link (int argc, std::vector<std::string> argv){

	//se houver só um código como argumento
  if(argc == 2){
    std::string aux = argv[0];
    std::vector<std::string> output;
    std::vector<std::string> program = link_file_reader(aux.append(".obj"));
    for(unsigned i = 11; i< program.size(); i++){
      output.push_back(program[i]);
    }
		std::string file_name = argv[0];
    link_file_generator(output, file_name.append(".linked"));
		std::cout << "Arquivo ligado salvo com nome: " << file_name << "\n";
  }
	//caso tenha 2 ou mais codigos, ele ligará os 2 primeiros
  else{
    std::string aux_1 = argv[0];
    std::string aux_2 = argv[1];
    std::vector<std::string> program_1 = link_file_reader(aux_1.append(".obj"));
    std::vector<std::string> program_2 = link_file_reader(aux_2.append(".obj"));
    std::string test = test_first(argc, argv);
		std::string aux_1_1 = argv[0];
		std::vector<std::string> pre_1 = build_file_reader(argv[0]);
		std::vector<std::string> pre_2 = build_file_reader(argv[1]);
		//std::cout << program_1[5];
		std::string name_1 = aux_1_1.substr(aux_1_1.find(".")+1, aux_1_1.size());
		name_1.append(":");
		if(test == name_1){
			std::vector<std::string> linked_program = link_concat(pre_1, pre_2);
			link_file_generator(linked_program, argv[0].append(".linked"));
			std::cout << "Arquivo ligado salvo com nome: " << argv[0] << "\n";
		}
		else{
			std::vector<std::string> linked_program = link_concat(pre_2, pre_1);
			link_file_generator(linked_program, argv[1].append(".linked"));
			std::cout << "Arquivo ligado salvo com nome: " << argv[1] << "\n";
		}
  }

}
