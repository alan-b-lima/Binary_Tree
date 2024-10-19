const char NAME_LIST[][11] = {
   "Adriana", "Adriano", "Alan", "Alessandra", "Alex", "Alexandre", "Aline", "Amanda", "Amelia", "Ana", "Anderson", "Andre", "Andreia", "Angela",
   "Antonia", "Antonio", "Aparecida", "Augusto", "Beatriz", "Breno", "Bruna", "Bruno", "Camila", "Carla", "Carlos", "Claudia", "Claudio", "Cristiane",
   "Daiane", "Daniel", "Daniela", "Daniele", "Davi", "Debora", "Diego", "Douglas", "Edson", "Eduardo", "Elaine", "Eliane", "Fabiana", "Fabio", "Felipe",
   "Fernanda", "Fernando", "Flavio", "Francisca", "Francisco", "Gabriel", "Gabriela", "Geraldo", "Guilherme", "Gustavo", "Igor", "Isabel", "Jaqueline",
   "Jeferson", "Jessica", "Joana", "Jorge", "Jose", "Josefa", "João", "Juan", "Julia", "Juliana", "Julio", "Larissa", "Leandro", "Leonardo", "Leticia",
   "Luan", "Lucas", "Lucia", "Luciana", "Luciano", "Luis", "Luiz", "Luzia", "Manoel", "Manuel", "Marcelo", "Marcia", "Marcio", "Marcos", "Maria",
   "Mariana", "Mario", "Marlene", "Mateus", "Matheus", "Natalia", "Otavio", "Pablo", "Patricia", "Paulo", "Pedro", "Rafael", "Rafaela", "Raimunda",
   "Raimundo", "Raquel", "Regina", "Renata", "Renato", "Ricardo", "Rita", "Roberto", "Rodrigo", "Rogerio", "Ronaldo", "Rosa", "Rosangela", "Samuel",
   "Sandra", "Sara", "Sergio", "Simone", "Sonia", "Sueli", "Terezinha", "Thiago", "Tiago", "Vanessa", "Vera", "Vinicius", "Vitor", "Vitoria"
};

const char SURNAME_LIST[][11] = {
   "Almeida", "Alves", "Andrade", "Barbosa", "Barros", "Batista", "Borges", "Braga", "Brant", "Campos", "Calazans", "Cardoso", "Carvalho", "Castro",
   "Costa", "Dias", "Duarte", "Freitas", "Fernandes", "Ferreira", "Garcia", "Gomes", "Goncalves", "Lima", "Lopes", "Machado", "Marques", "Martins",
   "Medeiros", "Melo", "Mendes", "Miranda", "Monteiro", "Moraes", "Moreira", "Moura", "Nascimento", "Nunes", "Oliveira", "Pereira", "Ramos", "Reis",
   "Ribeiro", "Rocha", "Santana", "Santos", "Silva", "Soares", "Souza", "Teixeira", "Vieira"
};

const unsigned long NAME_ENTRY_SIZE = sizeof(NAME_LIST[0]);
const unsigned long SURNAME_ENTRY_SIZE = sizeof(SURNAME_LIST[0]);

const unsigned long NAME_LIST_SIZE = sizeof(NAME_LIST) / NAME_ENTRY_SIZE;
const unsigned long SURNAME_LIST_SIZE = sizeof(SURNAME_LIST) / SURNAME_ENTRY_SIZE;
