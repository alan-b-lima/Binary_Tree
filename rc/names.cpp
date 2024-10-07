const char NAME_LIST[][11] = {
   "Jose", "Maria", "Joao", "Ana", "Antonio", "Francisca", "Francisco", "Antonia", "Carlos", "Adriana", "Paulo", "Juliana", "Pedro", "Marcia",
   "Lucas", "Fernanda", "Luiz", "Patricia", "Marcos", "Aline", "Luis", "Sandra", "Gabriel", "Camila", "Rafael", "Amanda", "Daniel", "Bruna",
   "Marcelo", "Jessica", "Bruno", "Leticia", "Eduardo", "Julia", "Felipe", "Luciana", "Raimundo", "Vanessa", "Rodrigo", "Mariana", "Manoel",
   "Gabriela", "Mateus", "Vera", "Otavio", "Andre", "Vitoria", "Alan", "Fernando", "Larissa", "Fabio", "Claudia", "Leonardo", "Beatriz",
   "Gustavo", "Luana", "Guilherme", "Rita", "Leandro", "Sonia", "Tiago", "Renata", "Juan", "Pablo", "Anderson", "Eliane", "Ricardo", "Breno",
   "Josefa", "Marcio", "Simone", "Jorge", "Natalia", "Sebastiao", "Cristiane", "Alexandre", "Carla", "Roberto", "Debora", "Edson", "Rosangela",
   "Diego", "Jaqueline", "Vitor", "Rosa", "Sergio", "Daniela", "Claudio", "Aparecida", "Matheus", "Marlene", "Thiago", "Terezinha", "Geraldo",
   "Raimunda", "Adriano", "Andreia", "Luciano", "Fabiana", "Julio", "Lucia", "Renato", "Raquel", "Alex", "Angela", "Vinicius", "Rafaela",
   "Rogerio", "Joana", "Samuel", "Luzia", "Ronaldo", "Elaine", "Mario", "Daniele", "Flavio", "Regina", "Igor", "Daiane", "Douglas", "Sueli",
   "Davi", "Alessandra", "Manuel", "Isabel", "Jeferson", "Sara"
};

const char SURNAME_LIST[][11] = {
   "Almeida", "Alves", "Andrade", "Barbosa", "Barros", "Batista", "Borges", "Campos", "Calazans", "Cardoso", "Carvalho", "Castro", "Costa",
   "Dias", "Duarte", "Freitas", "Fernandes", "Ferreira", "Garcia", "Gomes", "Goncalves", "Lima", "Lopes", "Machado", "Marques", "Martins",
   "Medeiros", "Melo", "Mendes", "Miranda", "Monteiro", "Moraes", "Moreira", "Moura", "Nascimento", "Nunes", "Oliveira", "Pereira", "Ramos",
   "Reis", "Ribeiro", "Rocha", "Santana", "Santos", "Silva", "Soares", "Souza", "Teixeira", "Vieira"
};

const unsigned long NAME_ENTRY_SIZE = sizeof(NAME_LIST[0]);
const unsigned long SURNAME_ENTRY_SIZE = sizeof(SURNAME_LIST[0]);

const unsigned long NAME_LIST_SIZE = sizeof(NAME_LIST) / NAME_ENTRY_SIZE;
const unsigned long SURNAME_LIST_SIZE = sizeof(SURNAME_LIST) / SURNAME_ENTRY_SIZE;
