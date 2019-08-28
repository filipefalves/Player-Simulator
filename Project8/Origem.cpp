/*
1. Deve - se armazenar o nome do aluno, seu e - mail e seu RU. Para o armazenamento utilize uma estrutura heterog�nea de dados.
2. N�o � necess�rio fazer a leitura dos dados dos alunos manualmente.Voc� j� pode deixar pr� - cadastrado os dados no seu c�digo. Cadastre pelo menos uns 10 contatos de alunos na sua estrutura de dados.Um dos contatos dever� ser o seu pr�prio nome e o seu RU da UNINTER;
3. Em um menu na tela, pe�a para o usu�rio digitar um RU. O programa dever� realizar a busca por este RU na estrutura de dados e, caso localize o RU, dever� mostrar o nome correspondente do aluno e o e - mail deste contato. Caso n�o localize, uma mensagem de erro deve ser apresentada. 
4. Para testar o programa, teste a busca com o seu RU e coloque a captura de dela.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura feita para cadastro de aluno
struct ALUNO {
	char nome[20];
	char email[30];
	int ru;
	ALUNO *left, *right; //Ponteiros para ramos esquerdo e direito
};

int menu(); //Declara��o da fun��o para mostrar menu
void inserirAluno(ALUNO** scan, int r, char* n, char* e); //Declara��o da fun��o para inserir
ALUNO* buscaRU(ALUNO** b, int r); //Declara��o da fun��o para buscar RU
void listar(ALUNO* scan); //Declara��o da fun��o para mostrar a lista de cadastrados


int main(int argc, char* argv[]) {
	int op, ru, c; //Opera��o, RU e vari�vel c (para limpeza de buffer)
	char nome[20], email[30];

	//Aloca��o do ponteiro root na mem�ria
	ALUNO* root;
	root = (ALUNO*)malloc(sizeof(ALUNO));
	root = NULL;

	//Aloca��o do ponteiro buscado da estrutura ALUNO
	ALUNO* buscado;
	buscado = (ALUNO*)malloc(sizeof(ALUNO));

	//Loop infinito com switch dependendo da escolha do menu
	while (1) {
		op = menu();
		switch (op) {
		case 1: //Cadastro de aluno
			printf("\nInsira o RU do aluno: ");
			scanf_s("%d", &ru);
			while ((c = getchar()) != '\n' && c != EOF) {} //Limpeza do buffer
			printf("\nInsira o nome do aluno: ");
			fgets(nome, 20, stdin); //fgets para pegar string
			//Condicional para remover a inser��o autom�tica de nova linha pelo fgets
			if (nome[strlen(nome) - 1] == '\n')
			{
				nome[strlen(nome) - 1] = '\0';
			}
			printf("\nAgora, insira o e-mail deste aluno: ");
			fgets(email, 30, stdin);
			if (email[strlen(email) - 1] == '\n')
			{
				email[strlen(email) - 1] = '\0';
			}
			
			inserirAluno(&root, ru, nome, email); //Chamada da fun��o com par�metros obtidos
			break;
		
		case 2: //Buscar dados de aluno pelo RU
			printf("\nInsira o RU do aluno: ");
			scanf_s("%d", &ru);
			while ((c = getchar()) != '\n' && c != EOF) {}
			buscado = buscaRU(&root, ru); //Vari�vel buscado � o resultado do retorno da fun��o consultaRU
			//Condicional para checar se o RU existe no cadastro
			if (buscado != 0) {
				printf("\n*****Informacoes do aluno*****\n\nNome: %s\n\nE-mail: %s\n\n", buscado->nome, buscado->email);
			}
			else {
				printf("*****RU NAO ENCONTRADO*****.\n");
			}
			system("pause");
			break;
		
		case 3: //Consultar lista completa de alunos cadastrados
			listar(root); //Chamada da fun��o que lista os dados
			printf("\n");
			system("pause");
			break;

		case 4:
			return 0; //Fecha o programa

		default:
			printf("\n*****COMANDO INVALIDO*****\n"); //Valor fora do intervalo
		}
	}
	return 0; //Sai do while
}

//Fun��o de menu
int menu() {
	int op, c; //Opera��o e c (limpeza de buffer)

	system("cls"); //Limpa a tela

	printf("\n*****SISTEMA DE ARMAZENAMENTO DE DADOS DE ALUNOS*****\n");

	printf("\n1. Cadastrar aluno");
	printf("\n2. Buscar RU");
	printf("\n3. Consultar a lista de alunos");
	printf("\n4. Sair do programa\n");
	
	printf("\nEscolha uma opcao: ");
	scanf_s("%d", &op); //Armazena a op��o na vari�vel op
	while ((c = getchar()) != '\n' && c != EOF) {}

	system("cls");
	return op; //Retorna op para chamada no while loop

}

//Fun��o para inserir aluno no cadastro
void inserirAluno(ALUNO** scan, int r, char* n, char* e) {
	if (*scan == NULL) { //Se a primeira posi��o (raiz) estiver vazia faz aloca��o na mem�ria e declara ponteiros como NULL
		ALUNO* novo = NULL;
		novo = (ALUNO*)malloc(sizeof(ALUNO));
		novo->left = NULL;
		novo->right = NULL;
		//Atribui dados passados na chamada ao ponteiro da struct e retorna
		strcpy_s(novo->nome, n);
		strcpy_s(novo->email, e);
		novo->ru = r;
		*scan = novo;
		return;
	}

	//Se for achado algo na primeira posi��o, caso o RU seja menor vai para a esquerda, se for maior vai para a direita
	if (r < (*scan)->ru) {
		inserirAluno(&(*scan)->left, r, n, e);
	}
	else {
		if (r > (*scan)->ru) {
			inserirAluno(&(*scan)->right, r, n, e);
		}
		else if (r == (*scan)->ru) { //Se for igual imprime na tela
			printf("\n*****RU JA CADASTRADO*****\n");
			system("pause");
		}
	}
}

//Fun��o de busca
ALUNO* buscaRU(ALUNO** scan, int r) {
	if (*scan == NULL) { //Se n�o tiver nenhum registro com o RU buscado, retorna NULL
		return NULL;
	}

	//A busca � feita primeiro com o ramo da esquerda, chamando a fun��o recursivamente
	if (r < (*scan)->ru) {
		buscaRU(&((*scan)->left), r);
	}
	else { //Depois � feita uma chamada recursiva com o ramo da direita
		if (r > (*scan)->ru) {
			buscaRU(&((*scan)->right), r);
		}
		else { //No fim, se o RU buscado e o RU no registro forem iguais, o ponteiro � retornado
			if (r == (*scan)->ru) {
				return *scan;
			}
		}
	}
}

//Fun��o de lista para consulta
void listar(ALUNO* scan) {
	if (scan) { //Faz chamadas recursivas para listar todos os dados cadastrados
		listar(scan->left);
		printf("\nRU: %d\tNome: %s\tE-Mail: %s\t\n", scan->ru, scan->nome, scan->email);
		listar(scan->right);
	}
}