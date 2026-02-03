from dataclasses import dataclass
import swe_hw_1.logic as logic
import swe_hw_1.domain.model as model

@dataclass
class CreateAliveRequest:
    type: str
    name: str
    food: str
    kindness: str

    def to_args(self) -> logic.CreateAliveArgs:
        if self.kindness != None:
            return logic.CreateAliveArgs(
                type=model.AliveType[self.type],
                name=self.name,
                food=int(self.food),
                kindness=int(self.kindness),
            )
        
        return logic.CreateAliveArgs(
                type=model.AliveType[self.type],
                name=self.name,
                food=int(self.food),
                kindness=None,
            )
    
@dataclass
class ListAlivesRequest:
    is_contact: bool

    def to_args(self) -> logic.ListAlivesArgs:
        return logic.ListAlivesArgs(is_contact=self.is_contact)

@dataclass
class GetAlivesFoodConsumptionRequest:

    def to_args(self) -> logic.GetAlivesFoodConsumptionArgs:
            return logic.GetAlivesFoodConsumptionArgs()

@dataclass
class CreateInventoryRequest:
    type: str
    name: str
    number: str

    def to_args(self) -> logic.CreateInventoryArgs:
        return logic.CreateInventoryArgs(
            type=model.InventoryType[self.type],
            name=self.name,
            number=int(self.number),
        )

@dataclass
class ListInventoriesRequest:
    def to_args(self) -> logic.ListInventoriesArgs:
        return logic.ListInventoriesArgs()
    
def create_alive_res_to_response(res: logic.CreateAliveRes) -> str:
    return f"Sucessfully created new animal {res.id}"

def list_alives_res_to_response(res: logic.ListAlivesRes) -> str:
    def alive_to_str(alive: model.Alive) -> str:
        if isinstance(alive, model.Tiger):
            return f"🐯 {alive.id} \"{alive.name}\", food consumption: {alive.food}"
        if isinstance(alive, model.Wolf):
            return f"🐺 {alive.id} \"{alive.name}\", food consumption: {alive.food}"
        if isinstance(alive, model.Rabbit):
            return f"🐰 {alive.id} \"{alive.name}\", food consumption: {alive.food}, kindness: {alive.kindness}"
        if isinstance(alive, model.Monkey):
            return f"🐵 {alive.id} \"{alive.name}\", food consumption: {alive.food}, kindness: {alive.kindness}"

    if len(res.alives) == 0:
        return "Animals list is empty"
    
    response = "Animals:\n"
    response += "\n".join(list(map(alive_to_str, res.alives)))

    return response

def get_alives_food_consumption_res_to_response(res: logic.GetAlivesFoodConsumptionRes) -> str:
    return f"Total food consumption: {res.food}"

def create_inventory_res_to_response(res: logic.CreateInventoryRes) -> str:
    return f"Sucessfully created new item: {res.id}"

def list_inventories_res_to_response(res: logic.ListInventoriesRes) -> str:
    def inventory_to_str(inventory: model.Inventory) -> str:
        if isinstance(inventory, model.Thing):
            return f"📦 {inventory.id} {inventory.name} №{inventory.number}"
        if isinstance(inventory, model.Table):
            return f"📥 {inventory.id} {inventory.name} №{inventory.number}"
        if isinstance(inventory, model.Computer):
            return f"💻 {inventory.id} {inventory.name} №{inventory.number}"
        
    if len(res.inventories) == 0:
        return "Items list is empty"

    response = "Items:\n"
    response += "\n".join(list(map(inventory_to_str, res.inventories)))

    return response