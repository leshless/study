from dataclasses import dataclass
from enum import Enum, auto

class AliveType(Enum):
    MONKEY = auto()
    RABBIT = auto()
    TIGER = auto()
    WOLF = auto()

@dataclass(frozen=True)
class Alive:
    id: str
    name: str
    food: int
    
@dataclass(frozen=True)
class Herbo(Alive):
    kindness: int

@dataclass(frozen=True)
class Predator(Alive):
    pass

@dataclass(frozen=True)
class Monkey(Herbo):
    pass

@dataclass(frozen=True)
class Rabbit(Herbo):
    pass

@dataclass(frozen=True)
class Tiger(Predator):
    pass

@dataclass(frozen=True)
class Wolf(Predator):
    pass

