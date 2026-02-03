from dataclasses import dataclass
from abc import ABC, abstractmethod
import threading
import swe_hw_1.domain.model as model
import swe_hw_1.domain.error as error

class Repository(ABC):
    @abstractmethod
    def list_alives() -> list[model.Alive]:
        pass
    
    @abstractmethod
    def insert_alive(alive: model.Alive) -> None:
        pass
    
    @abstractmethod
    def list_inventories() -> list[model.Inventory]:
        pass

    @abstractmethod
    def insert_inventory() -> None:
        pass

@dataclass
class RepositoryImpl(Repository):
    _alives: dict[str, model.Alive]
    _alives_lock: threading.RLock
    _inventories: dict[str, model.Inventory]
    _inventories_lock: threading.RLock

    def __init__(self):
        self._alives = {}
        self._alives_lock = threading.RLock()
        self._inventories = {}
        self._inventories_lock = threading.RLock()

    def list_alives(self) -> list[model.Alive]:
        with self._alives_lock:
            return list(self._alives.values())
    
    def insert_alive(self, alive: model.Alive) -> None:
        with self._alives_lock:
            if alive.id in self._alives:
                raise error.AliveAlreadyExistsError

            self._alives[alive.id] = alive
    
    def list_inventories(self) -> list[model.Inventory]:
        with self._inventories_lock:
            return list(self._inventories.values())

    def insert_inventory(self, inventory: model.Inventory) -> None:
        with self._inventories_lock:
            if inventory.id in self._inventories != None:
                raise error.InventoryAlreadyExistsError

            self._inventories[inventory.id] = inventory