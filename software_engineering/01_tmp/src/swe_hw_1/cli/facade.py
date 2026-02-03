from abc import ABC, abstractmethod
from dataclasses import dataclass
import swe_hw_1.logic as logic
from .dto import *

class Facade(ABC):
    @abstractmethod
    def create_alive(requst: CreateAliveRequest) -> str:
        pass

    @abstractmethod
    def list_alives(requst: ListAlivesRequest) -> str:
        pass

    @abstractmethod
    def get_alives_food_consumption(requst: GetAlivesFoodConsumptionRequest) -> str:
        pass

    @abstractmethod
    def create_inventory(requst: CreateInventoryRequest) -> str:
        pass

    @abstractmethod
    def list_inventories(requst: ListInventoriesRequest) -> str:
        pass

@dataclass
class FacadeImpl(Facade):
    _alive_controller: logic.AliveController
    _inventory_controller: logic.InventoryController

    def create_alive(self, requst: CreateAliveRequest) -> str:
        res = self._alive_controller.create_alive(requst.to_args())
        return create_alive_res_to_response(res)

    def list_alives(self, requst: ListAlivesRequest) -> str:
        res = self._alive_controller.list_alives(requst.to_args())
        return list_alives_res_to_response(res)

    def get_alives_food_consumption(self, requst: GetAlivesFoodConsumptionRequest) -> str:
        res = self._alive_controller.get_alives_food_consumption(requst.to_args())
        return get_alives_food_consumption_res_to_response(res)

    def create_inventory(self, requst: CreateInventoryRequest) -> str:
        res = self._inventory_controller.create_inventory(requst.to_args())
        return create_inventory_res_to_response(res)

    def list_inventories(self, requst: ListInventoriesRequest) -> str:
        res = self._inventory_controller.list_inventories(requst.to_args())
        return list_inventories_res_to_response(res)


    