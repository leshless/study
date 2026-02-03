class InventoryAlreadyExistsError(Exception):
    def __str__(self):
            return "Item already exists"

class UnkownInventoryTypeError(Exception):
    def __str__(self):
            return "Unknown item type"