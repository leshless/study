from enum import Enum, auto
import questionary
import re

MENU_PROMPT = "Select option:"
CREATE_ALIVE_TYPE_PROMPT = "Type:"
CREATE_ALIVE_NAME_PROMPT = "Name:"
CREATE_ALIVE_FOOD_PROMPT = "Food consumption (1-1000):"
CREATE_ALIVE_KINDNESS_PROMPT = "Kindness (1-10):"
LIST_ALIVES_PROMPT = "Options:"
CREATE_INVENTORY_TYPE_PROMPT = "Type:"
CREATE_INVENTORY_NAME_PROMPT = "Name:"
CREATE_INVENTORY_NUMBER_PROMPT = "Number (1-1000):"

ONLY_FOR_CONTACT_ZOO_CHOICE = "Only suitable for contact zoo"

ALIVE_NAME_PATTERN = re.compile(r"[a-zA-Z ]{2,30}")
ALIVE_FOOD_PATTERN = re.compile(r"[1-9][0-9]{,2}|1000")
ALIVE_KINDNESS_PATTERN = re.compile(r"[1-9]|10")

INVENTORY_NAME_PATTERN = re.compile(r"[a-zA-Z ]{2,30}")
INVENTORY_NUMBER_PATTERN = re.compile(r"[1-9][0-9]{,2}|1000")

CHECKBOX_STYLE = questionary.Style([

    ('selected', 'noreverse'),
    ('highlighted', 'noreverse'),
])

class MenuOption(Enum):
    CREATE_ALIVE = auto()
    LIST_ALIVES = auto()
    GET_ALIVES_FOOD_CONSUMPTION = auto()
    CREATE_INVENTORY = auto()
    LIST_INVENTORIES = auto()
    EXIT = auto()

    def __str__(self) -> str:
        match self.name:
            case 'CREATE_ALIVE':
                return "🐍Create Animal"
            case 'LIST_ALIVES':
                return "📋List Animals"
            case "GET_ALIVES_FOOD_CONSUMPTION":
                return "🥩Get Food Consumption"
            case "CREATE_INVENTORY":
                return "📦Create Item"
            case "LIST_INVENTORIES":
                return "📋List Items"
            case "EXIT":
                return "❌Exit"