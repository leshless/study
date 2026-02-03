from dataclasses import dataclass
from .inventory_dto import *
import swe_hw_1.util.rng as rng
import swe_hw_1.domain.error as error
import swe_hw_1.domain.model as model
import swe_hw_1.repository as repository

class InventoryController(ABC):
    @abstractmethod
    def create_inventory(args: CreateInventoryArgs) -> CreateInventoryRes:
        pass

    @abstractmethod
    def list_inventories(args: ListInventoriesArgs) -> ListInventoriesRes:
        pass

@dataclass
class InventoryControllerImpl(InventoryController):
    _rng: rng.RNG
    _repository: repository.Repository

    def create_inventory(self, args: CreateInventoryArgs) -> CreateInventoryRes:
        inventory_id = self._rng.ulid()

        match args.type:
            case model.InventoryType.THING:
                inventory = model.Thing(inventory_id, args.name, args.number)
            case model.InventoryType.COMPUTER:
                inventory = model.Computer(inventory_id, args.name, args.number)
            case model.InventoryType.TABLE:
                inventory = model.Table(inventory_id, args.name, args.number)
            case _:
                raise error.UnkownInventoryTypeError
        
        self._repository.insert_inventory(inventory)

        return CreateInventoryRes(inventory_id)
    
    def list_inventories(self, args: ListInventoriesArgs) -> ListInventoriesRes:
        inventories = self._repository.list_inventories()

        inventories.sort(key = lambda inventory : inventory.number)
        
        return ListInventoriesRes(inventories)
