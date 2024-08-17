# Sistema de Cinema

Este projeto é um sistema de cinema desenvolvido em linguagem C, que simula a gestão de filmes e a venda de ingressos. O sistema permite o cadastro de usuários, a realização de login, a administração de filmes (inclusão, edição, exclusão), e a compra de ingressos pelos usuários.

## Funcionalidades

### 1. Cadastro e Login de Usuários
- **Cadastro de Usuários**: Os usuários podem se cadastrar fornecendo nome, email e senha.
- **Validação de Email**: O sistema valida o formato do email durante o cadastro, garantindo que ele contenha o símbolo `@` e que o domínio seja válido.
- **Login de Usuários**: Após o cadastro, os usuários podem fazer login para acessar as funcionalidades do sistema.

### 2. Administração de Filmes
- **Adicionar Filme**: O administrador pode adicionar novos filmes ao catálogo, definindo nome, duração, avaliação, preço do ingresso, horários de exibição e a quantidade de ingressos disponíveis para cada dia da semana.
- **Editar Filme**: O administrador pode editar as informações de um filme existente.
- **Excluir Filme**: O administrador pode excluir um filme do catálogo.
- **Listar Filmes**: O sistema permite listar todos os filmes disponíveis no catálogo, mostrando os detalhes de exibição.

### 3. Compra de Ingressos
- **Selecionar Filme**: Os usuários podem escolher um filme do catálogo para comprar ingressos.
- **Escolher Dia e Horário**: Após selecionar o filme, o usuário pode escolher o dia da semana e o horário da sessão para a qual deseja comprar ingressos.
- **Atualização de Ingressos**: A quantidade de ingressos disponíveis é atualizada automaticamente após a compra.

### 4. Persistência de Dados
- **Salvamento de Dados**: Os dados dos usuários e dos filmes são salvos em arquivos binários, permitindo a persistência das informações entre execuções do programa.
- **Carregamento de Dados**: Ao iniciar o sistema, os dados salvos anteriormente são carregados automaticamente.

## Estrutura de Dados

- **Usuario**: Estrutura que armazena nome, email e senha dos usuários.
- **Filme**: Estrutura que armazena nome, duração, avaliação, preço do ingresso, dias da semana de exibição, horários e quantidade de ingressos disponíveis para cada dia.

## Compilação Manual (Windows)

No Windows, abra o terminal (cmd) na pasta do projeto e execute os seguintes comandos para compilar cada arquivo `.c` separadamente:

```bash
gcc -c -o bin/usuario.o src/usuario.c -Iinclude
gcc -c -o bin/filme.o src/filme.c -Iinclude
gcc -c -o bin/sistema.o src/sistema.c -Iinclude
gcc -c -o bin/utils.o src/utils.c -Iinclude
gcc -c -o bin/main.o src/main.c -Iinclude
gcc -o bin/cinema.exe bin/usuario.o bin/filme.o bin/sistema.o bin/utils.o bin/main.o
./bin/cinema
```

## Estrutura do Projeto

- **src/**: Contém os arquivos `.c` com a implementação do sistema.
- **include/**: Contém os arquivos `.h` (cabeçalhos) com as definições das funções e estruturas.
- **data/**: Pasta onde os arquivos binários com os dados dos filmes e usuários são armazenados.
- **bin/**: Pasta onde os arquivos objetos e o executável do projeto são gerados.

## Notas Importantes

- **Login de Administrador**: O login do administrador é predefinido no sistema. Email: `admin@gmail.com`, Senha: `1234`.
- **Mensagens de Boas-Vindas**: Após o login, os usuários recebem uma mensagem de boas-vindas específica do cinema.

## Contribuições

Este projeto é aberto a contribuições. Para contribuir, por favor, faça um fork do repositório, crie um branch para sua feature ou correção de bug, e envie um pull request.

## Licença

Este projeto é distribuído sob a licença MIT. Veja o arquivo `LICENSE` para mais detalhes.
