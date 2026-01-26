const char* SHM_OBJECT_PREFIX = "player";
const char* REQUEST_SEM_PREFIX = "request";
const char* RESPONSE_SEM_PREFIX = "response";

enum move {
    ROCK,
    PAPER,
    SCISSORS,
};
typedef enum move move;

const char* move_string[] = {
    "ROCK",
    "PAPER",
    "SCISSORS", 
};

struct shared_data {
    move player_move;
    short tournament_over;
};
typedef struct shared_data shared_data;