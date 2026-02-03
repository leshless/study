from abc import ABC, abstractmethod
from dataclasses import dataclass
import swe_hw_1.domain.model as model
import questionary
import termcolor
from .facade import *
from .dto import *
from .const import *

class Service(ABC):
    @abstractmethod
    def run():
        pass

@dataclass
class ServiceImpl(Service):
    _facade: Facade

    def _create_alive(self):
        answers = questionary.form(
            type=questionary.select(
                CREATE_ALIVE_TYPE_PROMPT,
                [alive_type.name for alive_type in model.AliveType],
                instruction=None
            ),
            name=questionary.text(
                CREATE_ALIVE_NAME_PROMPT,
                validate=lambda text: ALIVE_NAME_PATTERN.fullmatch(text) != None,
                instruction=None
            ),
            food=questionary.text(
                CREATE_ALIVE_FOOD_PROMPT,
                validate=lambda text: ALIVE_FOOD_PATTERN.fullmatch(text) != None,
                instruction=None
            ),
        ).ask()

        kindness = None
        if model.AliveType.MONKEY.name in answers["type"] or model.AliveType.RABBIT.name in answers["type"]:
            kindness=questionary.text(
                CREATE_ALIVE_KINDNESS_PROMPT,
                validate=lambda text: ALIVE_KINDNESS_PATTERN.fullmatch(text) != None,
                instruction=None
            ).ask()

        request = CreateAliveRequest(
            answers["type"], 
            answers["name"], 
            answers["food"], 
            kindness
        )

        try:
            response = self._facade.create_alive(request)
            print(f"\n{response}\n")
        except Exception as e:
            print(termcolor.colored("\nError: ", "red") + str(e) + "\n")


    def _list_alives(self):
        choices=questionary.checkbox(
            LIST_ALIVES_PROMPT,
            choices=[ONLY_FOR_CONTACT_ZOO_CHOICE],
            style=CHECKBOX_STYLE,
            instruction=None
        ).ask()

        request = ListAlivesRequest(ONLY_FOR_CONTACT_ZOO_CHOICE in choices)

        try:
            response = self._facade.list_alives(request)
            print(f"\n{response}\n")
        except Exception as e:
            print(termcolor.colored("\nError: ", "red") + str(e) + "\n")


    def _get_alive_food_consumption(self):
        request = GetAlivesFoodConsumptionRequest()

        try:
            response = self._facade.get_alives_food_consumption(request)
            print(f"\n{response}\n")
        except Exception as e:
            print(termcolor.colored("\nError: ", "red") + str(e) + "\n")

    def _create_inventory(self):
        answers = questionary.form(
            type=questionary.select(
                CREATE_INVENTORY_TYPE_PROMPT,
                [inventory_type.name for inventory_type in model.InventoryType],
                instruction=None
            ),
            name=questionary.text(
                CREATE_ALIVE_NAME_PROMPT,
                validate=lambda text: INVENTORY_NAME_PATTERN.fullmatch(text) != None,
                instruction=None
            ),
            number=questionary.text(
                CREATE_INVENTORY_NUMBER_PROMPT,
                validate=lambda text: INVENTORY_NUMBER_PATTERN.fullmatch(text) != None,
                instruction=None
            ),
        ).ask()

        request = CreateInventoryRequest(
            answers["type"], 
            answers["name"], 
            answers["number"]
        )

        try:
            response = self._facade.create_inventory(request)
            print(f"\n{response}\n")
        except Exception as e:
            print(termcolor.colored("\nError: ", "red") + str(e) + "\n")

    def _list_inventories(self):
        request = ListInventoriesRequest()

        try:
            response = self._facade.list_inventories(request)
            print(f"\n{response}\n")
        except Exception as e:
            print(termcolor.colored("\nError: ", "red") + str(e) + "\n")


    def _menu(self):
        option = questionary.select(
                "Select option",
                choices=[{"value": menu_option, "name": str(menu_option)} for menu_option in MenuOption],
                instruction=None,
            ).ask()
        
        match option:
            case MenuOption.CREATE_ALIVE:
                self._create_alive()
            case MenuOption.LIST_ALIVES:
                self._list_alives()
            case MenuOption.GET_ALIVES_FOOD_CONSUMPTION:
                self._get_alive_food_consumption()
            case MenuOption.CREATE_INVENTORY:
                self._create_inventory()
            case MenuOption.LIST_INVENTORIES:
                self._list_inventories()
            case _:
                raise InterruptedError

    def run(self):
        print("\nCLI service started\n")

        while True:
            try:
                self._menu()
            except Exception:
                break
        
        print("\nCLI service finished\n")