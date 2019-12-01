struct code{
	unsigned addr;
  int opcode;
};

int get_value_by_addr(int opcode, std::vector<code> object);
std::vector<std::string> file_reader_sim(std::string input_file_name);

std::vector<std::string> file_reader_sim(std::string input_file_name){

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

int get_value_by_addr(int opcode, std::vector<code> object){
	for(unsigned i = 0; i<object.size(); i++){
		if(object[i].addr == opcode){
			return object[i].opcode;
		};
	};
}

int validate (std::string input){
	int size;
	size = input.size();
	if(size == 0){
		return 0;
	}
	else{
		for(char& c : input) {
    	if(!std::isalnum(c)){
				return 0;
			}
		}
	}
	return 1;
}
