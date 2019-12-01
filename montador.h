std::vector<std::string> build_file_reader(std::string input_file_name);
std::vector<build_structure> get_symbols(std::vector<std::string> input_file_name);
std::string get_address(std::string var, std::vector<build_structure> sym_tb);
std::vector<std::string> builder(std::vector<std::string> input_file_name, std::string file_name, std::vector<build_structure> table_of_sym);
void build (int argc, std::vector<std::string> program);
int begin_check (std::vector<std::string> pre_processed);
int end_check (std::vector<std::string> pre_processed);
void file_generator_b(std::vector<std::string> code, std::string file_name);
void table_generator(std::vector<build_structure> table_of_sym, std::string file_name);

std::vector<std::string> build_file_reader(std::string input_file_name){
  std::ifstream input_file (input_file_name.append(".pre"));
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

std::vector<build_structure> get_symbols(std::vector<std::string> input_file_name){

  std::vector<build_structure> table;
  build_structure aux;
  std::string str_aux;
  int address = 0;
  for (unsigned i = 0; i < input_file_name.size(); i++) {
    //std::cout << "Add: " << address << "\n";
    if(input_file_name[i] == "ADD" || input_file_name[i] ==  "SUB"|| input_file_name[i] == "MULT" || input_file_name[i] == "DIV" || input_file_name[i] == "JMP" || input_file_name[i] == "JMPN" || input_file_name[i] == "JMPP" || input_file_name[i] == "JMPZ" || input_file_name[i] == "LOAD" || input_file_name[i] == "STORE" || input_file_name[i] == "INPUT" || input_file_name[i] == "OUTPUT"){
      address+=2;
      while(input_file_name[i] != "\n"){
        i++;
      }
    }
    else if (input_file_name[i] == "COPY") {
      address+=3;
      while(input_file_name[i] != "\n"){
        i++;
      }
    }
    else if (input_file_name[i] == "STOP" || input_file_name[i] == "SPACE" || input_file_name[i] == "CONST") {
      address+=1;
    }
    else if (input_file_name[i] == "CONST") {
      address+=1;
    }

    if(input_file_name[i].back() == ':'){
      str_aux = input_file_name[i];
      str_aux.resize(str_aux.size()-1);
      aux.name = str_aux;
      aux.address = address;
      if(input_file_name[i+1] == "EXTERN"){
        aux.is_extern = 1;
        aux.address = 0;
      }
      else{
        aux.is_extern = 0;
      }
      //std::cout << "Carreguei " << aux.name << " com address " << aux.address << " e externo " << aux.is_extern << "\n";
      table.push_back(aux);
    }
  }

  return table;
}

std::string get_address(std::string var, std::vector<build_structure> sym_tb){
  std::string output;
  for (unsigned i = 0; i < sym_tb.size(); i++) {
    if(sym_tb[i].name == var){
      output = std::to_string(sym_tb[i].address);
      //std::cout << "Retornei " << output << "\n";
      return output;
    }
  }
}

std::vector<std::string> builder(std::vector<std::string> input_file_name, std::string file_name, std::vector<build_structure> table_of_sym){

  int address = 0;
  std::vector<std::string> output;
  std::string bit_map;
  std::vector<build_structure> symbol_table;
  std::string aux, aux_sum;
  int a, b=0;
  //output.push_back(file_name);
  //output.push_back("\n");

  for (unsigned i = 0; i < input_file_name.size(); i++) {
    if (input_file_name[i] == "ADD") {
      output.push_back("1");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "SUB") {
      output.push_back("2");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "MULT") {
      output.push_back("3");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "DIV") {
      output.push_back("4");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "JMP") {
      output.push_back("5");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "JMPN") {
      output.push_back("6");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "JMPP") {
      output.push_back("7");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "JMPZ") {
      output.push_back("8");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "COPY") {
      output.push_back("9");
      address+=2;
      bit_map.append("100");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //std::cout << "Estou " << input_file_name[i] << "\n";
      //std::cout << "End " << aux << "\n";
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum << "\n";
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux << "\n";
      }
      i+=2;
      aux = get_address(input_file_name[i], table_of_sym);
      //std::cout << "Estou " << input_file_name[i] << "\n";
      //std::cout << "End " << aux << "\n";
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum << "\n";
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux << "\n";
      }

    }
    else if (input_file_name[i] == "LOAD") {
      output.push_back("10");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "STORE") {
      output.push_back("11");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "INPUT") {
      output.push_back("12");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "OUTPUT") {
      output.push_back("13");
      address++;
      bit_map.append("10");
      i++;
      aux = get_address(input_file_name[i], table_of_sym);
      //i++;
      if(input_file_name[i+1] == "+"){
        i+=2;
        a = std::stoi(aux);
        b = std::stoi(input_file_name[i]);
        aux_sum = std::to_string(a+b);
        output.push_back(aux_sum);
        //std::cout << "Salvei " << aux_sum;
      }
      else{
        output.push_back(aux);
        //std::cout << "Salvei " << aux;
      }
    }
    else if (input_file_name[i] == "STOP") {
      output.push_back("14");
      address++;
      bit_map.append("1");
    }
    else if (input_file_name[i] == "CONST") {
      output.push_back(input_file_name[i+1]);
      address++;
      bit_map.append("1");
    }
    else if (input_file_name[i] == "SPACE") {
      output.push_back("0");
      address++;
      bit_map.append("1");
    };
  }

  address = output.size();
  output.insert(output.begin(), "H:");
  output.insert(output.begin()+1, file_name);
  output.insert(output.begin()+2, "\n");
  output.insert(output.begin()+3, "H:");
  output.insert(output.begin()+4, std::to_string(address));
  output.insert(output.begin()+5, "\n");
  output.insert(output.begin()+6, "H:");
  output.insert(output.begin()+7, bit_map);
  output.insert(output.begin()+8, "\n");
  output.insert(output.begin()+9, "T:");
  output.push_back("\n");
  return output;
}

int begin_check (std::vector<std::string> pre_processed){
  int check = 0;
  int line = 1;
  for(unsigned i=0; i<pre_processed.size();i++){
    if(pre_processed[i] == "\n"){
      line++;
    }
    else if(pre_processed[i] == "BEGIN"){
      return line;
    }
  }
  return check;
}

int end_check (std::vector<std::string> pre_processed){
  int check = 0;
  int line = 1;
  for(unsigned i=0; i<pre_processed.size();i++){
    if(pre_processed[i] == "\n"){
      line++;
    }
    else if(pre_processed[i] == "END"){
      return line;
    }
  }
  return check;
}

void file_generator_b(std::vector<std::string> code, std::string file_name){

	std::ofstream newFile(file_name.append(".obj"));
	unsigned i;

	for(i = 0; i < code.size(); i++) {
    newFile << code[i] << " ";
	};
}

void table_generator(std::vector<build_structure> table_of_sym, std::string file_name){

	std::ofstream newFile(file_name.append(".table"));
	unsigned i;

	for(i = 0; i < table_of_sym.size(); i++) {
    newFile << table_of_sym[i].name << " " << table_of_sym[i].address << " " << table_of_sym[i].is_extern << "\n";
	};
}

void build (int argc, std::vector<std::string> program){
  int c_begin[2] = {0,0};
  int c_end[2] = {0,0};
  for(unsigned i = 0; i<argc-1; i++){
    std::vector<std::string> pre_processed = build_file_reader(program[i]);
    std::vector<build_structure> table_of_sym = get_symbols(pre_processed);
    std::vector<std::string> built = builder(pre_processed, program[i], table_of_sym);
    c_begin[i] = begin_check(pre_processed);
    c_end[i] = end_check(pre_processed);
    file_generator_b(built, program[i]);
    table_generator(table_of_sym, program[i]);

    //for(unsigned i=0; i<built.size();i++)
    	//	std::cout << built[i] << ' ';
  }
  std::cout << '\n';
  if(argc == 2){
    if(c_begin[0] != 0){
        std::cout << "ERRO SEMÂNTICO: BEGIN NÃO ESPERADO NA LINHA " << c_begin[0] << "\n";
    }
    if (c_begin[1] != 0) {
      std::cout << "ERRO SEMÂNTICO: BEGIN NÃO ESPERADO NA LINHA " << c_begin[1] << "\n";
    }
    if (c_end[0] != 0) {
      std::cout << "ERRO SEMÂNTICO: END NÃO ESPERADO NA LINHA " << c_end[0] << "\n";
    }
    if (c_end[1] != 0) {
      std::cout << "ERRO SEMÂNTICO: END NÃO ESPERADO NA LINHA " << c_end[1] << "\n";
    };
  }
  else{
    if((c_begin[0] != 0 || c_end[0] != 0) && (c_begin[1] != 0 || c_end[1] != 0)){
      std::cout << "ERRO SEMÂNTICO: MÚLTIPLAS DECLARAÇÕES DE BEGIN E END" << "\n";
    }
    if (c_begin[0] != 0 && c_end[0] == 0) {
      std::cout << "ERRO SEMÂNTICO: BEGIN SEM DECLARAÇÃO DE END EM " << "'" << program[0] << "' LINHA " << c_begin[0] << "\n";
    }
    if (c_begin[1] != 0 && c_end[1] == 0) {
      std::cout << "ERRO SEMÂNTICO: BEGIN SEM DECLARAÇÃO DE END EM " << "'" << program[1] << "' LINHA " << c_begin[1] << "\n";
    }
    if (c_begin[0] == 0 && c_end[0] != 0) {
      std::cout << "ERRO SEMÂNTICO: END SEM DECLARAÇÃO DE BEGIN EM " << "'" << program[0] << "' LINHA " << c_end[0] << "\n";
    }
    if (c_begin[1] == 0 && c_end[1] != 0) {
      std::cout << "ERRO SEMÂNTICO: END SEM DECLARAÇÃO DE BEGIN EM " << "'" << program[1] << "' LINHA " << c_end[1] << "\n";
    }
    if((c_begin[0] == 0 && c_end[0] == 0) && (c_begin[1] == 0 && c_end[1] == 0)){
      std::cout << "ERRO SEMÂNTICO: BEGIN E END NÃO DECLARADOS" << "\n";
    }
  }
}
