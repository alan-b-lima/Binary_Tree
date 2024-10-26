const char NAME_LIST[][10] = {
   "Alan", "Alexandre", "Aline", "Amanda", "Amelia", "Ana", "Anderson", "André", "Andreia", "Antonio", "Aparecida", "Augusto", "Breno", "Bruno", "Camila", "Carla",
   "Carlos", "Cláudio", "Cristine", "Daiana", "Daniele", "Davi", "Diego", "Douglas", "Eduardo", "Elaine", "Fabiana", "Fabio", "Felipe", "Francisca", "Gabriel",
   "Guilherme", "Gustavo", "Isabelly", "João", "Juan", "Júlia", "Julio", "Leonardo", "Luan", "Lucas", "Luciana", "Luis", "Luiz", "Marcelo", "Marcia", "Marcos", "Maria",
   "Mariana", "Mateus", "Natalia", "Otávio", "Pablo", "Rafael", "Raquel", "Regina", "Renato", "Roberto", "Rodrigo", "Sandra", "Sergio", "Tiago", "Vitor", "Vitoria"
};

const char SURNAME_LIST[][11] = {
   "Almeida", "Alves", "Andrade", "Assis", "Barbosa", "Barros", "Batista", "Borges", "Braga", "Brant", "Campos", "Calazans", "Cardoso", "Carvalho", 
   "Castro", "Costa", "Dias", "Duarte", "Freitas", "Fernandes", "Ferreira", "Figueredo", "Filho", "Garcia", "Gomes", "Gonçalves", "Guimarães", "Henrique",
   "Júnior", "Lima", "Lopes", "Machado", "Marques", "Martins", "Martinelli", "Medeiros", "Melo", "Mendes", "Miranda", "Monteiro", "Moraes", "Moreira", "Moura",
   "Morelli", "Mozer", "Nascimento", "Nunes", "Oliveira", "Pereira", "Prado", "Ramos", "Reis", "Ribeiro", "Rocha", "Sales", "Santana", "Santos", "Silva", "Soares",
   "Souza", "Tavares", "Teixeira", "Veloso", "Vieira"
};

const unsigned long NAME_ENTRY_SIZE = sizeof(NAME_LIST[0]);
const unsigned long SURNAME_ENTRY_SIZE = sizeof(SURNAME_LIST[0]);

const unsigned long NAME_LIST_SIZE = sizeof(NAME_LIST) / NAME_ENTRY_SIZE;
const unsigned long SURNAME_LIST_SIZE = sizeof(SURNAME_LIST) / SURNAME_ENTRY_SIZE;
