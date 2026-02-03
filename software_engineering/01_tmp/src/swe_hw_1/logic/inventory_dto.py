from abc import ABC, abstractmethod
from dataclasses import dataclass
import swe_hw_1.domain.model as model

@dataclass
class CreateInventoryArgs:
    type: model.InventoryType
    name: str
    number: int

@dataclass
class CreateInventoryRes:
    id: str

@dataclass
class ListInventoriesArgs:
    pass 

@dataclass
class ListInventoriesRes:
    inventories: list[model.Inventory]