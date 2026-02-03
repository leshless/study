from dataclasses import dataclass
from enum import Enum, auto

class InventoryType(Enum):
    THING = auto()
    TABLE = auto()
    COMPUTER = auto()

@dataclass(frozen=True)
class Inventory:
    id: str
    name: str
    number: int

@dataclass(frozen=True)
class Thing(Inventory):
    pass

@dataclass(frozen=True)
class Table(Inventory):
    pass

@dataclass(frozen=True)
class Computer(Inventory):
    pass
